#include <common.h>
#include <utils.h>
#include <device/map.h>
#include <memory/host.h>
#include <memory/paddr.h>

#ifndef CONFIG_TARGET_AM
#include <fcntl.h>
#include <unistd.h>
#endif

#define SRAM_BASE   CONFIG_SOC_SRAM_BASE
#define SRAM_SIZE   CONFIG_SOC_SRAM_SIZE
#define UART_BASE   CONFIG_SOC_UART_MMIO
#define UART_SIZE   CONFIG_SOC_UART_SIZE
#define SPI_BASE    CONFIG_SOC_SPI_MMIO
#define SPI_SIZE    CONFIG_SOC_SPI_SIZE
#define GPIO_BASE   CONFIG_SOC_GPIO_MMIO
#define GPIO_SIZE   CONFIG_SOC_GPIO_SIZE
#define PS2_BASE    CONFIG_SOC_PS2_MMIO
#define PS2_SIZE    CONFIG_SOC_PS2_SIZE
#define VGA_BASE    CONFIG_SOC_VGA_ADDR
#define VGA_MAP_SIZE CONFIG_SOC_VGA_SIZE
#define PSRAM_BASE  CONFIG_SOC_PSRAM_BASE
#define PSRAM_SIZE  CONFIG_SOC_PSRAM_SIZE
#define SDRAM_BASE  CONFIG_SOC_SDRAM_BASE
#define SDRAM_SIZE  CONFIG_SOC_SDRAM_SIZE
#define FLASH_BASE  CONFIG_SOC_FLASH_BASE
#define FLASH_SIZE  CONFIG_SOC_FLASH_SIZE

#define UART_RBR 0
#define UART_THR 0
#define UART_DLL 0
#define UART_DLM 1
#define UART_FCR 2
#define UART_LCR 3
#define UART_MCR 4
#define UART_LSR 5
#define UART_LCR_DLAB 0x80
#define UART_LSR_DR   0x01
#define UART_LSR_THRE 0x20
#define UART_LSR_TEMT 0x40

#define SPI_TX0 0x00
#define SPI_TX1 0x04
#define SPI_CTRL 0x10
#define SPI_SS 0x18
#define SPI_GO (1u << 8)

#define QUEUE_LEN 1024

#ifdef CONFIG_HAS_SERIAL
static uint8_t *uart_regs;
#endif
#ifdef CONFIG_HAS_SPI
static uint32_t *spi_regs;
#endif
#ifdef CONFIG_HAS_GPIO
static uint8_t *gpio_regs;
static uint16_t gpio_input = CONFIG_SOC_GPIO_INPUT;
#endif
#ifdef CONFIG_HAS_KEYBOARD
static uint8_t *ps2_regs;
#endif
#ifdef CONFIG_HAS_VGA
static uint32_t *vga_fb;
#endif
static uint8_t *sram_mem;
static uint8_t *psram_mem;
static uint8_t *sdram_mem;

void *soc_memory_host_ptr(paddr_t addr, size_t len) {
  uint64_t end = (uint64_t)addr + len;
  if (addr >= SRAM_BASE && end <= (uint64_t)SRAM_BASE + SRAM_SIZE)
    return sram_mem + (addr - SRAM_BASE);
  if (addr >= PSRAM_BASE && end <= (uint64_t)PSRAM_BASE + PSRAM_SIZE)
    return psram_mem + (addr - PSRAM_BASE);
  if (addr >= SDRAM_BASE && end <= (uint64_t)SDRAM_BASE + SDRAM_SIZE)
    return sdram_mem + (addr - SDRAM_BASE);
  return NULL;
}

#ifdef CONFIG_HAS_SERIAL
static uint8_t uart_queue[QUEUE_LEN];
static unsigned uart_front, uart_rear;
#endif
#ifdef CONFIG_HAS_KEYBOARD
static uint8_t ps2_queue[QUEUE_LEN];
static unsigned ps2_front, ps2_rear;
#endif

#if defined(CONFIG_HAS_SERIAL) || defined(CONFIG_HAS_KEYBOARD)
static void queue_push(uint8_t *queue, unsigned *front, unsigned *rear,
                       uint8_t value) {
  unsigned next = (*rear + 1) % QUEUE_LEN;
  Assert(next != *front, "SoC input queue overflow");
  queue[*rear] = value;
  *rear = next;
}

static int queue_pop(uint8_t *queue, unsigned *front, unsigned rear) {
  if (*front == rear) return -1;
  uint8_t value = queue[*front];
  *front = (*front + 1) % QUEUE_LEN;
  return value;
}

static bool queue_empty(unsigned front, unsigned rear) {
  return front == rear;
}
#endif

#ifdef CONFIG_HAS_SERIAL
static void uart_poll_stdin(void) {
#if !defined(CONFIG_TARGET_AM) && defined(CONFIG_SOC_UART_INPUT)
  uint8_t input;
  if (queue_empty(uart_front, uart_rear) &&
      read(STDIN_FILENO, &input, 1) == 1)
    queue_push(uart_queue, &uart_front, &uart_rear, input);
#endif
}
#endif

#ifdef CONFIG_HAS_SPI
#ifdef CONFIG_SOC_SPI_FLASH
static uint32_t bswap32(uint32_t value) {
  return __builtin_bswap32(value);
}
#endif

#ifdef CONFIG_SOC_SPI_BITREV
static uint8_t reverse8(uint8_t value) {
  value = (value >> 4) | (value << 4);
  value = ((value & 0xcc) >> 2) | ((value & 0x33) << 2);
  return ((value & 0xaa) >> 1) | ((value & 0x55) << 1);
}
#endif
#endif

#ifdef CONFIG_HAS_SERIAL
static void uart_handler(paddr_t offset, int len, bool is_write) {
  Assert(len == 1 || len == 2 || len == 4, "invalid UART access size %d", len);
  offset &= 7;
  bool dlab = uart_regs[UART_LCR] & UART_LCR_DLAB;

  if (is_write && offset == UART_THR && !dlab) {
    uint8_t ch = uart_regs[UART_THR];
    if (uart_regs[UART_MCR] & 0x10)
      queue_push(uart_queue, &uart_front, &uart_rear, ch);
    else {
      putc(ch, stderr);
      fflush(stderr);
    }
  }

  if (!is_write && offset == UART_LSR) {
    uart_poll_stdin();
    uart_regs[UART_LSR] = UART_LSR_THRE | UART_LSR_TEMT |
        (queue_empty(uart_front, uart_rear) ? 0 : UART_LSR_DR);
  }

  if (!is_write && offset == UART_RBR && !dlab) {
    uart_poll_stdin();
    int ch = queue_pop(uart_queue, &uart_front, uart_rear);
    uart_regs[UART_RBR] = ch < 0 ? 0xff : (uint8_t)ch;
  }
}
#endif

#ifdef CONFIG_HAS_SPI
static void spi_handler(paddr_t offset, int len, bool is_write) {
  Assert(len == 1 || len == 2 || len == 4, "invalid SPI access size %d", len);
  if (!is_write || offset != SPI_CTRL || !(spi_regs[SPI_CTRL / 4] & SPI_GO))
    return;

  uint32_t selected = spi_regs[SPI_SS / 4];
  if (selected & 1) {
#ifdef CONFIG_SOC_SPI_FLASH
    uint32_t command = spi_regs[SPI_TX1 / 4];
    Assert((command >> 24) == 0x03, "unsupported SPI flash command 0x%02x",
           command >> 24);
    uint32_t flash_offset = command & 0x00ffffffu;
    Assert(flash_offset <= FLASH_SIZE - 4, "SPI flash address out of range");
    uint32_t data = host_read(guest_to_host(FLASH_BASE + flash_offset), 4);
    spi_regs[SPI_TX0 / 4] = bswap32(data);
#else
    panic("SPI flash slave is disabled");
#endif
  } else if (selected & (1u << 7)) {
#ifdef CONFIG_SOC_SPI_BITREV
    uint8_t input = (spi_regs[SPI_TX0 / 4] >> 8) & 0xff;
    spi_regs[SPI_TX0 / 4] =
        (spi_regs[SPI_TX0 / 4] & ~0xffu) | reverse8(input);
#else
    panic("SPI bit-reversal slave is disabled");
#endif
  } else {
    panic("unsupported SPI slave selection 0x%08x", selected);
  }
  spi_regs[SPI_CTRL / 4] &= ~SPI_GO;
}
#endif

#ifdef CONFIG_HAS_GPIO
static void gpio_handler(paddr_t offset, int len, bool is_write) {
  Assert(len == 1 || len == 2 || len == 4, "invalid GPIO access size %d", len);
  if (!is_write && offset >= 4 && offset < 8)
    host_write(gpio_regs + 4, 2, gpio_input);
}
#endif

#ifdef CONFIG_HAS_KEYBOARD
static void ps2_handler(paddr_t offset, int len, bool is_write) {
  Assert(!is_write, "PS/2 registers are read-only");
  Assert(len == 1 || len == 2 || len == 4, "invalid PS/2 access size %d", len);
  if (offset == 0) {
    int value = queue_pop(ps2_queue, &ps2_front, ps2_rear);
    ps2_regs[0] = value < 0 ? 0 : (uint8_t)value;
  }
}
#endif

#ifdef CONFIG_HAS_VGA
static void vga_handler(paddr_t offset, int len, bool is_write) {
  const uint32_t visible_size = 640 * 480 * sizeof(uint32_t);
  // The RTL maps a 2 MiB APB window but only implements the visible pixels;
  // accesses in the remaining mapped padding read as zero and ignore writes.
  if (offset + len > visible_size)
    host_write((uint8_t *)vga_fb + offset, len, 0);
}
#endif

static void *alloc_map(const char *name, paddr_t base, uint32_t size,
                       io_callback_t callback) {
  void *space = calloc(1, size);
  Assert(space != NULL, "cannot allocate %s", name);
  add_mmio_map(name, base, space, size, callback);
  return space;
}

void init_soc_device() {
#if defined(CONFIG_HAS_SERIAL) && defined(CONFIG_SOC_UART_INPUT) && \
    !defined(CONFIG_TARGET_AM)
  int flags = fcntl(STDIN_FILENO, F_GETFL);
  if (flags >= 0) fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
#endif
#ifdef CONFIG_HAS_GPIO
  const char *gpio_env = getenv("MEMU_GPIO_INPUT");
  if (gpio_env != NULL) gpio_input = strtoul(gpio_env, NULL, 0) & 0xffff;
#endif

  sram_mem = alloc_map("soc-sram", SRAM_BASE, SRAM_SIZE, NULL);
  psram_mem = alloc_map("soc-psram", PSRAM_BASE, PSRAM_SIZE, NULL);
  sdram_mem = alloc_map("soc-sdram", SDRAM_BASE, SDRAM_SIZE, NULL);
#ifdef CONFIG_HAS_SERIAL
  uart_regs = alloc_map("soc-uart16550", UART_BASE, UART_SIZE, uart_handler);
#endif
#ifdef CONFIG_HAS_SPI
  spi_regs = alloc_map("soc-spi", SPI_BASE, SPI_SIZE, spi_handler);
#endif
#ifdef CONFIG_HAS_GPIO
  gpio_regs = alloc_map("soc-gpio", GPIO_BASE, GPIO_SIZE, gpio_handler);
#endif
#ifdef CONFIG_HAS_KEYBOARD
  ps2_regs = alloc_map("soc-ps2", PS2_BASE, PS2_SIZE, ps2_handler);
#endif
#ifdef CONFIG_HAS_VGA
  vga_fb = alloc_map("soc-vga", VGA_BASE, VGA_MAP_SIZE, vga_handler);
#endif
#ifdef CONFIG_HAS_SERIAL
  uart_regs[UART_LSR] = UART_LSR_THRE | UART_LSR_TEMT;
#endif

}
