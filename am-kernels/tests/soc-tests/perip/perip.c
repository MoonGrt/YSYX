#include <am.h>
#include <klib-macros.h>
#include <soc-device.h>
#include <stdint.h>

#define GPIO_LED    (*(volatile uint16_t *)(GPIO_BASE + 0x0))
#define GPIO_SWITCH (*(volatile uint16_t *)(GPIO_BASE + 0x4))
#define GPIO_SEG    (*(volatile uint32_t *)(GPIO_BASE + 0x8))
#define UART_MCR    (*(volatile uint8_t *)(UART_BASE + 0x4))

static uint32_t pixels[16 * 8];

int main(void) {
  ioe_init();

  // Exercise UART RX without an interactive terminal by enabling 16550
  // internal loopback for one byte.
  UART_MCR = 0x10;
  io_write(AM_UART_TX, 'U');
  AM_UART_RX_T rx = { .data = (char)-1 };
  for (int i = 0; i < 10000 && rx.data == (char)-1; i++)
    rx = io_read(AM_UART_RX);
  UART_MCR = 0;
  if (rx.data != 'U') return 1;

  GPIO_LED = 0x0001;
  if (GPIO_LED != 0x0001) return 2;
  GPIO_LED = 0x8000;
  if (GPIO_LED != 0x8000) return 3;
  if (GPIO_SWITCH != 0) return 4;

  uint32_t student_id;
  asm volatile("csrr %0, marchid" : "=r"(student_id));
  if (student_id != 26010030u) return 5;
  GPIO_SEG = student_id;
  if (GPIO_SEG != student_id) return 6;

  AM_GPU_CONFIG_T cfg = io_read(AM_GPU_CONFIG);
  if (!cfg.present || cfg.width != 640 || cfg.height != 480 ||
      cfg.vmemsz < 640 * 480 * 4) return 7;

  for (int y = 0; y < 8; y++)
    for (int x = 0; x < 16; x++)
      pixels[y * 16 + x] = ((uint32_t)(x * 16) << 16) |
                           ((uint32_t)(y * 32) << 8) | 0x5a;
  io_write(AM_GPU_FBDRAW, 7, 9, pixels, 16, 8, true);

  volatile uint32_t *fb = (volatile uint32_t *)VGA_BASE;
  for (int y = 0; y < 8; y++)
    for (int x = 0; x < 16; x++)
      if (fb[(y + 9) * 640 + x + 7] != pixels[y * 16 + x]) return 8;

  AM_INPUT_CONFIG_T input = io_read(AM_INPUT_CONFIG);
  AM_INPUT_KEYBRD_T key = io_read(AM_INPUT_KEYBRD);
  if (!input.present || key.keycode != AM_KEY_NONE) return 9;
  while (1);
  return 0;
}
