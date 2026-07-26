#include <am.h>
#include <stdint.h>

static volatile uint32_t initialized_data = 0x13579bdf;
static volatile uint32_t zeroed_bss;

static int test_u8(uintptr_t start, uintptr_t end) {
  for (uintptr_t addr = start; addr < end; addr += sizeof(uint8_t))
    *(volatile uint8_t *)addr = (uint8_t)addr;
  for (uintptr_t addr = start; addr < end; addr += sizeof(uint8_t))
    if (*(volatile uint8_t *)addr != (uint8_t)addr) return 1;
  return 0;
}

static int test_u16(uintptr_t start, uintptr_t end) {
  for (uintptr_t addr = start; addr < end; addr += sizeof(uint16_t))
    *(volatile uint16_t *)addr = (uint16_t)addr;
  for (uintptr_t addr = start; addr < end; addr += sizeof(uint16_t))
    if (*(volatile uint16_t *)addr != (uint16_t)addr) return 2;
  return 0;
}

static int test_u32(uintptr_t start, uintptr_t end) {
  for (uintptr_t addr = start; addr < end; addr += sizeof(uint32_t))
    *(volatile uint32_t *)addr = (uint32_t)addr;
  for (uintptr_t addr = start; addr < end; addr += sizeof(uint32_t))
    if (*(volatile uint32_t *)addr != (uint32_t)addr) return 3;
  return 0;
}

static int test_u64(uintptr_t start, uintptr_t end) {
  for (uintptr_t addr = start; addr < end; addr += sizeof(uint64_t))
    *(volatile uint64_t *)addr = (uint64_t)addr;
  for (uintptr_t addr = start; addr < end; addr += sizeof(uint64_t))
    if (*(volatile uint64_t *)addr != (uint64_t)addr) return 4;
  return 0;
}

int main(void) {
  if (initialized_data != 0x13579bdf || zeroed_bss != 0) return 6;
  initialized_data = 0x2468ace0;
  zeroed_bss = initialized_data;
  if (initialized_data != 0x2468ace0 || zeroed_bss != 0x2468ace0) return 7;

  uintptr_t start = (uintptr_t)heap.start;
  uintptr_t end = (uintptr_t)heap.end;

  if (start >= end ||
      (start & (sizeof(uint64_t) - 1)) != 0 ||
      (end & (sizeof(uint64_t) - 1)) != 0)
    return 5;

  int result;
  if ((result = test_u8(start, end)) != 0) return result;
  if ((result = test_u16(start, end)) != 0) return result;
  if ((result = test_u32(start, end)) != 0) return result;
  if ((result = test_u64(start, end)) != 0) return result;

  return 0;
}
