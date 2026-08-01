#include <stdint.h>

#define PSRAM_BASE 0x80000000u
#ifndef TEST_SIZE
#define TEST_SIZE  0x1000u
#endif

static volatile uint32_t initialized_data = 0x13579bdfu;
static volatile uint32_t zeroed_bss;

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
  if (initialized_data != 0x13579bdfu || zeroed_bss != 0)
    fail();
  initialized_data = 0x2468ace0u;
  zeroed_bss = initialized_data;
  if (initialized_data != 0x2468ace0u || zeroed_bss != 0x2468ace0u)
    fail();

  for (uint32_t offset = 0; offset < TEST_SIZE; offset += 4)
    *(volatile uint32_t *)(PSRAM_BASE + offset) =
        0x5a000000u ^ offset ^ (offset << 8);

  for (uint32_t offset = 0; offset < TEST_SIZE; offset += 4) {
    uint32_t expected = 0x5a000000u ^ offset ^ (offset << 8);
    uint32_t actual = *(volatile uint32_t *)(PSRAM_BASE + offset);
    if (actual != expected) {
      puthex(offset);
      puthex(actual);
      puthex(expected);
      fail();
    }
  }

  for (uint32_t offset = 0; offset < 256; offset++) {
    *(volatile uint8_t *)(PSRAM_BASE + offset) = (uint8_t)(offset ^ 0xa5);
    uint8_t actual = *(volatile uint8_t *)(PSRAM_BASE + offset);
    if (actual != (uint8_t)(offset ^ 0xa5)) {
      puthex(offset);
      puthex(actual);
      puthex((uint8_t)(offset ^ 0xa5));
      puthex(*(volatile uint32_t *)PSRAM_BASE);
      fail();
    }
  }
  return 0;
}
