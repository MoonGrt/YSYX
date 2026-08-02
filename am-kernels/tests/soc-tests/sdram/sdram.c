#include <stdint.h>

#ifndef TEST_SIZE
#define TEST_SIZE  0x1000u
#endif

extern void putch(char);
static void puthex(uint32_t value) {
  const char hex[] = "0123456789abcdef";
  for (int i = 7; i >= 0; i--) putch(hex[(value >> (i * 4)) & 0xf]);
  putch('\n');
}

static void fail(void) {
  __asm__ volatile(".word 0");
}

int main(void) {
  for (uint32_t offset = 0; offset < TEST_SIZE; offset += 4)
    *(volatile uint32_t *)(SDRAM_BASE + offset) =
        0xc35a0000u ^ offset ^ (offset << 7);

  for (uint32_t offset = 0; offset < TEST_SIZE; offset += 4) {
    uint32_t expected = 0xc35a0000u ^ offset ^ (offset << 7);
    uint32_t actual = *(volatile uint32_t *)(SDRAM_BASE + offset);
    if (actual != expected) {
      puthex(offset);
      puthex(actual);
      puthex(expected);
      fail();
    }
  }

  for (uint32_t offset = 0; offset < 256; offset++) {
    *(volatile uint8_t *)(SDRAM_BASE + offset) = (uint8_t)(offset ^ 0x3c);
    if (*(volatile uint8_t *)(SDRAM_BASE + offset) !=
        (uint8_t)(offset ^ 0x3c))
      fail();
  }
  return 0;
}
