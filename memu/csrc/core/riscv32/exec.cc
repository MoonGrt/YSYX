#include <common.h>
#include <utils.h>
#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <cpu/difftest.h>
#include <memory/paddr.h>
#include <memory/host.h>
#include <device/mmio.h>
#include <csignal>
#include <elf.h>

#if defined(CONFIG_SOC) && defined(CONFIG_HAS_SERIAL) && \
    defined(CONFIG_SOC_UART_INPUT) && !defined(CONFIG_TARGET_AM)
#include <unistd.h>
#endif

#ifndef CONFIG_SOC_UART_MMIO
#define CONFIG_SOC_UART_MMIO 0x10000000u
#endif
#ifndef CONFIG_SOC_UART_SIZE
#define CONFIG_SOC_UART_SIZE 0x1000u
#endif
#ifndef CONFIG_SOC_SPI_MMIO
#define CONFIG_SOC_SPI_MMIO 0x10001000u
#endif
#ifndef CONFIG_SOC_SPI_SIZE
#define CONFIG_SOC_SPI_SIZE 0x1000u
#endif
#ifndef CONFIG_SOC_GPIO_MMIO
#define CONFIG_SOC_GPIO_MMIO 0x10002000u
#endif
#ifndef CONFIG_SOC_GPIO_SIZE
#define CONFIG_SOC_GPIO_SIZE 0x10u
#endif
#ifndef CONFIG_SOC_PS2_MMIO
#define CONFIG_SOC_PS2_MMIO 0x10011000u
#endif
#ifndef CONFIG_SOC_PS2_SIZE
#define CONFIG_SOC_PS2_SIZE 0x8u
#endif
#ifndef CONFIG_SOC_VGA_ADDR
#define CONFIG_SOC_VGA_ADDR 0x21000000u
#endif
#ifndef CONFIG_SOC_VGA_SIZE
#define CONFIG_SOC_VGA_SIZE 0x200000u
#endif
#ifndef CONFIG_SOC_FLASH_BASE
#define CONFIG_SOC_FLASH_BASE 0x30000000u
#endif
#ifndef CONFIG_SOC_FLASH_SIZE
#define CONFIG_SOC_FLASH_SIZE 0x1000000u
#endif
#ifndef CONFIG_SOC_SDRAM_BASE
#define CONFIG_SOC_SDRAM_BASE 0xa0000000u
#endif
#ifndef CONFIG_SOC_SDRAM_SIZE
#define CONFIG_SOC_SDRAM_SIZE 0x02000000u
#endif
#ifndef CONFIG_SOC_PSRAM_BASE
#define CONFIG_SOC_PSRAM_BASE 0x80000000u
#endif
#ifndef CONFIG_SOC_PSRAM_SIZE
#define CONFIG_SOC_PSRAM_SIZE 0x00400000u
#endif

#ifdef CONFIG_NVBOARD
#include <nvboard.h>
class VSoCTop;
void nvboard_bind_all_pins(VSoCTop *top);
#endif

#ifndef CONFIG_SOC
  #ifdef CONFIG_CORE_RVMINI
  #include "VMiniRVTop.h"
  VMiniRVTop *top = new VMiniRVTop;
  #elif  CONFIG_CORE_RV32E
  #include "VRiscv32ETop.h"
  VRiscv32ETop *top = new VRiscv32ETop;
  #endif
#else
#include "VSoCTop.h"
VSoCTop *top = new VSoCTop;
#endif

#if defined(CONFIG_WAVE_ABSOLUTE) || defined(CONFIG_WAVE_RELATIVE)

extern uint64_t g_nr_guest_inst;
#if defined(CONFIG_WAVE_VCD)
#include <verilated_vcd_c.h>
VerilatedVcdC *tfp;
#else
#include <verilated_fst_c.h>
VerilatedFstC *tfp;
#endif

#endif

bool wave_enable() {
#ifdef CONFIG_WAVE_ABSOLUTE
  return MUXDEF(CONFIG_WAVE_ABSOLUTE, (g_nr_guest_inst >= CONFIG_WAVE_ABS_START) &&
    (g_nr_guest_inst < CONFIG_WAVE_ABS_END), false);
#else
  return false;
#endif
}

#ifdef CONFIG_WAVE_RELATIVE
#include <utils.h>
#include <lightsss.h>
LightSSS *lightsss = new LightSSS;
bool have_initial_fork = false;
#endif

static constexpr size_t FLASH_SIZE = CONFIG_SOC_FLASH_SIZE;
static uint8_t flash_mem[FLASH_SIZE];

extern "C" {
  static bool resync_after_mmio_commit = false;

  void mtrace(bool is_write, paddr_t addr, int len, word_t data);
  void etrace(uint32_t epc, uint32_t ecode);

  #define EBREAK_CODE    0
  #define ECALL_CODE     1
  #define ZERO_INST_CODE 2
  #define UNIMPL_CODE    3
  void exception(uint8_t code) {
    switch (code) {
      case EBREAK_CODE:
        printf("%s\n", ANSI_FMT("[MEMU] EBREAK exception", ANSI_FG_GREEN));
        MEMUTRAP(cpu.pc, code);
        break;
      case ECALL_CODE:
        IFDEF(CONFIG_ETRACE, etrace(decode.pc, 11));
        // ECALL is a guest exception, not a simulator termination request.
        // The RTL core redirects execution to mtvec and later returns with
        // MRET, so keep Verilator running while the trap is handled.
        return;
      case ZERO_INST_CODE:
        printf("%s\n", ANSI_FMT("[MEMU] Zero instruction exception", ANSI_FG_RED));
        INV(cpu.pc, decode.isa.inst);
        break;
      case UNIMPL_CODE:
        printf("%s\n", ANSI_FMT("[MEMU] Unimplemented instruction exception", ANSI_FG_RED));
        INV(cpu.pc, decode.isa.inst);
        break;
      default:
        printf("%s %d\n", ANSI_FMT("[MEMU] Unknown exception code", ANSI_FG_RED), code);
        break;
    }
    Verilated::gotFinish(true);
  }
  int dpi_paddr_read(int addr) {
    if (addr == 0) return 0;
    if (likely(in_pmem(addr))) {
      word_t data = pmem_read(addr, 4);
      IFDEF(CONFIG_MTRACE, mtrace(false, addr, 4, data));
      return data;
    }
    IFDEF(CONFIG_DEVICE, return mmio_read(addr, 4));
    return 0;
  }
  void dpi_paddr_write(int addr, char mask, int data) {
    if (addr == 0) return;
    IFDEF(CONFIG_MTRACE, mtrace(true, addr, 4, data));
    for (int i = 0; i < 4; i++) {
      if (mask & (1 << i)) {
        int byte_addr = addr + i;
        int byte_data = (data >> (i * 8)) & 0xFF;
        if (likely(in_pmem(byte_addr))) {
          pmem_write(byte_addr, 1, byte_data);
        } else {
          // The reference model has no devices, so it must not execute this
          // MMIO store.  This callback has the resolved address and is more
          // reliable than reconstructing it from commit-time register state.
          IFDEF(CONFIG_DIFFTEST, difftest_skip_ref());
          resync_after_mmio_commit = true;
          IFDEF(CONFIG_DEVICE, mmio_write(byte_addr, 1, byte_data));
        }
      }
    }
  }
#ifdef CONFIG_SOC_FAST_SDRAM
  int soc_sdram_read(int addr) {
    word_t data = mmio_read((paddr_t)addr, 4);
    IFDEF(CONFIG_MTRACE, mtrace(false, (paddr_t)addr, 4, data));
    return data;
  }
  void soc_sdram_write(int addr, char mask, int data) {
    IFDEF(CONFIG_MTRACE, mtrace(true, (paddr_t)addr, 4, data));
    for (int i = 0; i < 4; i++) {
      if (mask & (1 << i))
        mmio_write((paddr_t)addr + i, 1, (data >> (i * 8)) & 0xff);
    }
  }
#endif
#ifdef CONFIG_SOC_FAST_PSRAM
  int soc_psram_read(int addr) {
    word_t data = mmio_read((paddr_t)addr, 4);
    IFDEF(CONFIG_MTRACE, mtrace(false, (paddr_t)addr, 4, data));
    return data;
  }
  void soc_psram_write(int addr, char mask, int data) {
    IFDEF(CONFIG_MTRACE, mtrace(true, (paddr_t)addr, 4, data));
    for (int i = 0; i < 4; i++) {
      if (mask & (1 << i))
        mmio_write((paddr_t)addr + i, 1, (data >> (i * 8)) & 0xff);
    }
  }
#endif
  void flash_read(int32_t addr, int32_t *data) {
#ifndef CONFIG_SOC
    assert(0);
#endif
    // flash.v sends the 24-bit address carried by the SPI transaction, i.e.
    // an offset inside the flash chip rather than the configured XIP address.
    uint32_t offset = (uint32_t)addr;
    if (offset > FLASH_SIZE - sizeof(*data)) {
      fprintf(stderr, "flash read out of bounds: 0x%08x\n", (uint32_t)addr);
      abort();
    }
    memcpy(data, flash_mem + offset, sizeof(*data));
  }
  void init_flash(const char *img_file) {
    memset(flash_mem, 0xff, sizeof(flash_mem));
    if (img_file == nullptr) {
      // init_isa() has already installed the built-in test image in pmem.
      // The SoC fetches through the flash model, so mirror the same image
      // there when `make run` is invoked without IMG.
      memcpy(flash_mem, guest_to_host(RESET_VECTOR), 4096);
      return;
    }
    FILE *fp = fopen(img_file, "rb");
    if (fp == nullptr) {
      fprintf(stderr, "Can not open flash image '%s'\n", img_file);
      abort();
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    if (size < 0 || (size_t)size > FLASH_SIZE) {
      fprintf(stderr, "flash image is too large: %ld bytes\n", size);
      abort();
    }
    fseek(fp, 0, SEEK_SET);
    size_t nr = fread(flash_mem, 1, size, fp);
    if (nr != (size_t)size) {
      fprintf(stderr, "failed to load flash image '%s'\n", img_file);
      abort();
    }
    fclose(fp);
    // printf("Flash image loaded at [0x30000000, 0x%08x]\n",
    //     0x30000000u + (uint32_t)(size == 0 ? 0 : size - 1));
  }
#if defined(CONFIG_SOC_FAST_BOOT) || defined(CONFIG_SOC_PSRAM_PRELOAD)
#define FAST_BOOT_CHECK(condition, ...) do { \
  if (!(condition)) { \
    fprintf(stderr, __VA_ARGS__); \
    fputc('\n', stderr); \
    abort(); \
  } \
} while (0)

  static bool elf_range_valid(size_t offset, size_t size, size_t file_size) {
    return offset <= file_size && size <= file_size - offset;
  }

  static uint32_t elf_find_symbol(const uint8_t *image, size_t image_size,
                                  const Elf32_Ehdr *eh, const char *name) {
    if (!elf_range_valid(eh->e_shoff,
                         (size_t)eh->e_shnum * eh->e_shentsize, image_size))
      return 0;
    const Elf32_Shdr *sections =
      (const Elf32_Shdr *)(image + eh->e_shoff);
    for (unsigned i = 0; i < eh->e_shnum; i++) {
      const Elf32_Shdr *symbols = &sections[i];
      if (symbols->sh_type != SHT_SYMTAB || symbols->sh_link >= eh->e_shnum ||
          symbols->sh_entsize != sizeof(Elf32_Sym) ||
          !elf_range_valid(symbols->sh_offset, symbols->sh_size, image_size))
        continue;
      const Elf32_Shdr *strings = &sections[symbols->sh_link];
      if (!elf_range_valid(strings->sh_offset, strings->sh_size, image_size))
        continue;
      const char *strtab = (const char *)(image + strings->sh_offset);
      const Elf32_Sym *table =
        (const Elf32_Sym *)(image + symbols->sh_offset);
      size_t count = symbols->sh_size / sizeof(*table);
      for (size_t j = 0; j < count; j++) {
        if (table[j].st_name < strings->sh_size &&
            strcmp(strtab + table[j].st_name, name) == 0)
          return table[j].st_value;
      }
    }
    return 0;
  }

  void soc_fast_boot(const char *elf_file) {
    if (elf_file == nullptr) {
      printf("[MEMU] Fast boot disabled: no ELF file was provided\n");
      return;
    }
    FILE *fp = fopen(elf_file, "rb");
    FAST_BOOT_CHECK(fp != nullptr, "Can not open ELF '%s'", elf_file);
    fseek(fp, 0, SEEK_END);
    long file_size_long = ftell(fp);
    FAST_BOOT_CHECK(file_size_long >= (long)sizeof(Elf32_Ehdr),
                    "Invalid ELF file");
    size_t file_size = file_size_long;
    fseek(fp, 0, SEEK_SET);
    uint8_t *image = (uint8_t *)malloc(file_size);
    FAST_BOOT_CHECK(image != nullptr, "Can not allocate ELF buffer");
    FAST_BOOT_CHECK(fread(image, 1, file_size, fp) == file_size,
                    "Can not read ELF");
    fclose(fp);

    const Elf32_Ehdr *eh = (const Elf32_Ehdr *)image;
    FAST_BOOT_CHECK(memcmp(eh->e_ident, ELFMAG, SELFMAG) == 0 &&
                    eh->e_ident[EI_CLASS] == ELFCLASS32 &&
                    eh->e_machine == EM_RISCV,
                    "Fast boot requires a 32-bit RISC-V ELF");
    FAST_BOOT_CHECK(eh->e_phentsize == sizeof(Elf32_Phdr) &&
                    elf_range_valid(
                      eh->e_phoff,
                      (size_t)eh->e_phnum * eh->e_phentsize, file_size),
                    "Invalid ELF program headers");

    extern void *soc_memory_host_ptr(paddr_t addr, size_t len);
    const Elf32_Phdr *programs =
      (const Elf32_Phdr *)(image + eh->e_phoff);
    for (unsigned i = 0; i < eh->e_phnum; i++) {
      const Elf32_Phdr *segment = &programs[i];
      if (segment->p_type != PT_LOAD || segment->p_memsz == 0) continue;
      void *dest = soc_memory_host_ptr(segment->p_vaddr, segment->p_memsz);
      if (dest == nullptr) continue;
      FAST_BOOT_CHECK(
        segment->p_filesz <= segment->p_memsz &&
        elf_range_valid(segment->p_offset, segment->p_filesz, file_size),
        "Invalid ELF load segment");
      memcpy(dest, image + segment->p_offset, segment->p_filesz);
      memset((uint8_t *)dest + segment->p_filesz, 0,
             segment->p_memsz - segment->p_filesz);
    }

    uint32_t entry = elf_find_symbol(image, file_size, eh, "_trm_init");
    FAST_BOOT_CHECK(entry != 0, "Fast boot can not find _trm_init in ELF");
    free(image);

    bool fast_target = false;
    uint32_t stack = 0;
#ifdef CONFIG_SOC_FAST_BOOT
    if (entry >= CONFIG_SOC_SDRAM_BASE &&
        entry < CONFIG_SOC_SDRAM_BASE + CONFIG_SOC_SDRAM_SIZE) {
      fast_target = true;
      stack = CONFIG_SOC_SDRAM_BASE + CONFIG_SOC_SDRAM_SIZE;
    }
#endif
#ifdef CONFIG_SOC_PSRAM_PRELOAD
    if (entry >= CONFIG_SOC_PSRAM_BASE &&
        entry < CONFIG_SOC_PSRAM_BASE + CONFIG_SOC_PSRAM_SIZE) {
      fast_target = true;
      stack = CONFIG_SOC_PSRAM_BASE + CONFIG_SOC_PSRAM_SIZE;
    }
#endif
    if (!fast_target) {
      printf("[MEMU] ELF preload skipped: target entry 0x%08x is not enabled\n",
             entry);
      return;
    }

    uint32_t entry_hi = (entry + 0x800) >> 12;
    int32_t entry_lo = (int32_t)(entry - (entry_hi << 12));
    uint32_t trampoline[] = {
      (stack & 0xfffff000u) | (2u << 7) | 0x37u,
      (entry_hi << 12) | (5u << 7) | 0x37u,
      0x00000013u,
      0x00000013u,
      0x00000013u,
      (((uint32_t)entry_lo & 0xfffu) << 20) | (5u << 15) | 0x67u,
    };
    memcpy(flash_mem, trampoline, sizeof(trampoline));
    memcpy(guest_to_host(CONFIG_SOC_FLASH_BASE), trampoline,
           sizeof(trampoline));
    printf("[MEMU] Fast boot preloaded ELF; entry = 0x%08x\n", entry);
  }
#undef FAST_BOOT_CHECK
#endif
  void mrom_read(int32_t addr, int32_t *data) {
#ifndef CONFIG_SOC
    assert(0);
#endif
    // *data = 0x00100073;  // ebreak
    *data = dpi_paddr_read(addr);
    // printf("0x%08x\n", (unsigned int)(*data));
  }
  void dpi_diffpc(int pc, int npc, int inst) {
    // printf("pc: %x, npc: %x, inst: %08x\n", pc, npc, inst);
    // Decode
    decode.pc = pc;
    decode.snpc = pc + 4;
    decode.dnpc = npc;
    decode.isa.inst = inst;
    // CPU_state
    cpu.pc = pc;
    // The reference model has no device mappings.  MMIO stores are skipped by
    // their memory/peripheral DPI callbacks.  Detect loads here because their
    // RTL result must be synchronized after writeback.
    uint32_t opcode = inst & 0x7f;
    if (opcode == 0x03) {
      int rs1 = (inst >> 15) & 0x1f;
      int32_t imm = (int32_t)inst >> 20;
      word_t addr = rs1 < MUXDEF(CONFIG_RVE, 16, 32)
                      ? cpu.gpr[rs1] + imm : 0;
      bool is_mmio = (addr >= CONFIG_SOC_UART_MMIO &&
                      addr < CONFIG_SOC_UART_MMIO + CONFIG_SOC_UART_SIZE) ||
                     (addr >= CONFIG_SOC_SPI_MMIO &&
                      addr < CONFIG_SOC_SPI_MMIO + CONFIG_SOC_SPI_SIZE) ||
                     (addr >= CONFIG_SOC_GPIO_MMIO &&
                      addr < CONFIG_SOC_GPIO_MMIO + CONFIG_SOC_GPIO_SIZE) ||
                     (addr >= CONFIG_SOC_PS2_MMIO &&
                      addr < CONFIG_SOC_PS2_MMIO + CONFIG_SOC_PS2_SIZE) ||
                     (addr >= CONFIG_SOC_VGA_ADDR &&
                      addr < CONFIG_SOC_VGA_ADDR + CONFIG_SOC_VGA_SIZE) ||
                     (addr >= CONFIG_SOC_FLASH_BASE &&
                      addr < CONFIG_SOC_FLASH_BASE + CONFIG_SOC_FLASH_SIZE);
      if (is_mmio) {
        IFDEF(CONFIG_DIFFTEST, difftest_skip_ref());
        // dpi_diffpc observes a load before its write-back state is visible
        // through dpi_diffgpr. Synchronize the load result on the next
        // callback.
        resync_after_mmio_commit = true;
      }
    }
    // reference step
    if (pc != 0) IFDEF(CONFIG_DIFFTEST, difftest_step());
    // difftest_step() above skips the MMIO instruction using the pre-commit
    // state.  Schedule one more skip so the next callback copies the committed
    // PC and any load result into the reference before it resumes.
    if (resync_after_mmio_commit) {
      IFDEF(CONFIG_DIFFTEST, difftest_skip_ref());
      resync_after_mmio_commit = false;
    }
  }
  void dpi_diffgpr(int* gpr) {
    // printf("dpi_diffgpr\n");
    for (int i = 0; i < MUXDEF(CONFIG_RVE, 16, 32); i++)
      cpu.gpr[i] = gpr[i];
  }
  void dpi_diffcsr(int* csr) {
    // printf("dpi_diffcsr\n");
    cpu.csr.mstatus = csr[0];
    cpu.csr.mepc = csr[1];
    cpu.csr.mcause = csr[2];
    cpu.csr.mtvec = csr[3];
    cpu.csr.mcycle = csr[4];
    cpu.csr.mcycleh = csr[5];
    cpu.csr.mvendorid = csr[6];
    cpu.csr.marchid = csr[7];
  }
  void dpi_diffmem(int addr, char mask, int wdata) {
#ifdef CONFIG_DIFFTEST
    if (ref_difftest_memcpy == nullptr) return;
    for (int i = 0; i < 4; i++) {
      if ((mask & (1 << i)) == 0) continue;
      uint8_t data = ((uint32_t)wdata >> (i * 8)) & 0xff;
      ref_difftest_memcpy((paddr_t)(uint32_t)addr + i, &data, 1,
                          DIFFTEST_TO_REF);
    }
#endif
  }
  void dpi_diffskip(void) {
    IFDEF(CONFIG_DIFFTEST, difftest_skip_ref());
    // RTL peripherals such as UART bypass dpi_paddr_write().  Mark their
    // instruction for a second synchronization after it commits.
    resync_after_mmio_commit = true;
  }
}

void wave_init() {
#if defined(CONFIG_WAVE_ABSOLUTE) || defined(CONFIG_WAVE_RELATIVE)
  Verilated::traceEverOn(true);
#if defined(CONFIG_WAVE_VCD)
  tfp = new VerilatedVcdC;
#else
  tfp = new VerilatedFstC;
#endif
  top->trace(tfp, 99);  // 99 是 trace depth
#ifdef WAVEOUT
  tfp->open(WAVEOUT "/wave.vcd");
#else
  tfp->open("./wave.vcd");
#endif
#endif
}

bool force_dump_wave = false;
uint32_t inst_last = 0;

#if defined(CONFIG_SOC) && defined(CONFIG_HAS_SERIAL) && \
    defined(CONFIG_SOC_UART_INPUT) && !defined(CONFIG_TARGET_AM)
// AM initializes the 16550 divisor latch to 1.  The OpenCores receiver uses
// 16 enable pulses per serial bit, so hold every 8N1 frame bit for 16 RTL
// clocks. stdin is made non-blocking by init_soc_device().
static constexpr unsigned UART_RX_CLOCKS_PER_BIT = 16;
static uint16_t uart_rx_frame = 0x3ff;
static unsigned uart_rx_bit = 10;
static unsigned uart_rx_clocks_left = 0;

static void uart_rx_tick() {
  if (top->reset) {
    uart_rx_frame = 0x3ff;
    uart_rx_bit = 10;
    uart_rx_clocks_left = 0;
    top->externalPins_uart_rx = 1;
    return;
  }

  if (uart_rx_clocks_left == 0) {
    if (uart_rx_bit < 10) uart_rx_bit++;

    if (uart_rx_bit == 10) {
      uint8_t data;
      if (read(STDIN_FILENO, &data, 1) == 1) {
        // bit 0: start (0), bits 1..8: data LSB first, bit 9: stop (1)
        uart_rx_frame = (1u << 9) | ((uint16_t)data << 1);
        uart_rx_bit = 0;
      }
    }
    uart_rx_clocks_left = UART_RX_CLOCKS_PER_BIT;
  }

  top->externalPins_uart_rx =
      uart_rx_bit < 10 ? ((uart_rx_frame >> uart_rx_bit) & 1u) : 1;
  uart_rx_clocks_left--;
}
#endif

static vluint64_t sim_time = 0;
static void wave_tracer() {
#if defined(CONFIG_WAVE_ABSOLUTE) || defined(CONFIG_WAVE_RELATIVE)
  if (wave_enable() | force_dump_wave) {
    tfp->dump(sim_time++);
    tfp->flush();
  }
#endif
}

#ifdef CONFIG_WAVE_RELATIVE
void fork_child_init() {
  FORK_PRINTF("the oldest checkpoint start to dump wave...\n")
  wave_init();
  force_dump_wave = true;
}
#endif

static void tick(){
#if defined(CONFIG_SOC) && defined(CONFIG_HAS_SERIAL) && \
    defined(CONFIG_SOC_UART_INPUT) && !defined(CONFIG_TARGET_AM)
  uart_rx_tick();
#endif
#ifdef CONFIG_NVBOARD
  nvboard_update();
#endif
  top->clock = 0;
  top->eval();
  wave_tracer();
  top->clock = 1;
  top->eval();
  wave_tracer();

#ifdef CONFIG_WAVE_RELATIVE
  if (lightsss->is_child() && g_nr_guest_inst != 0)
    if (g_nr_guest_inst == lightsss->get_end_cycles())
      FORK_PRINTF("checkpoint has reached the main process abort point: %lu\n", g_nr_guest_inst)
  if ((g_nr_guest_inst - inst_last == CONFIG_WAVE_REL_INTERVAL || !have_initial_fork) && !lightsss->is_child()) {
    if (!have_initial_fork) printf("%s\n", ANSI_FMT("[Lightsss] do_fork", ANSI_FG_GREEN));
    have_initial_fork = true;
    switch (lightsss->do_fork()) {
      case FORK_ERROR:
        printf("%s\n", ANSI_FMT("[Lightsss] error", ANSI_FG_RED));
        return;
      case FORK_CHILD:
        // printf("%s\n", ANSI_FMT("[Lightsss] fork_child_init", ANSI_FG_GREEN));
        fork_child_init();
      default: break;
    }
    inst_last = g_nr_guest_inst;
  }
#endif
}

static void reset(){
  top->reset = 1;
  tick();
  top->reset = 0;
}

void exit(void) {
  delete top;
#if defined(CONFIG_WAVE_ABSOLUTE) || defined(CONFIG_WAVE_RELATIVE)
  if (tfp) {
    tfp->close();
    delete tfp;
  }
#ifdef CONFIG_WAVE_RELATIVE
  if (!lightsss->is_child()) {  // parent process
    bool need_wakeup = 
      (memu_state.state == MEMU_ABORT) ||
      (memu_state.state == MEMU_END && memu_state.halt_ret != 0);
    if (need_wakeup) {
      printf(ANSI_FMT("\n\n[Lightsss] wakeup_child\n", ANSI_FG_GREEN));
      lightsss->wakeup_child(g_nr_guest_inst);
    } else {
      printf(ANSI_FMT("[Lightsss] do_clear\n", ANSI_FG_GREEN));
      lightsss->do_clear();
    }
    delete lightsss;
  } else {  // child process
    printf(ANSI_FMT("[Lightsss] do_clear\n", ANSI_FG_RED));
    lightsss->do_clear();
  }
#endif
#endif
}

// void signal_handler(int signum) {
//   Verilated::gotFinish(true);
//   memu_state.state = MEMU_QUIT;
// }

extern "C" {
  void rtl_init(int argc, char *argv[]) {
    Verilated::commandArgs(argc, argv);
    IFDEF(CONFIG_WAVE_ABSOLUTE, wave_init());
#ifdef CONFIG_SOC
    top->externalPins_gpio_in = 0;
    top->externalPins_ps2_clk = 1;
    top->externalPins_ps2_data = 1;
    top->externalPins_uart_rx = 1;
#endif
#ifdef CONFIG_NVBOARD
    nvboard_bind_all_pins(top);
    // The VGA controller advances one pixel every four SoC clock cycles.
    nvboard_init(4);
#ifndef CONFIG_NVBOARD_VGA_CAPTURE
    // Keep keyboard/UART/event handling active without sampling every VGA
    // pixel. This is useful for long-running software simulations.
    static uint8_t nvboard_vga_disabled = 0;
    extern uint8_t *vga_blank_n_ptr;
    vga_blank_n_ptr = &nvboard_vga_disabled;
#endif
#endif
    // signal(SIGINT, signal_handler);
    reset();
  }
  void rtl_reset() {
    reset();
  }
  #define CYCLE_NUM 2
  void rtl_step() {
    // for (int i = 0; i < CYCLE_NUM; i++)
      tick();
  }
  void rtl_exit() {
#ifdef CONFIG_NVBOARD
    nvboard_quit();
#endif
    exit();
  }
}
