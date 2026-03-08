#include <am.h>
#include <nemu.h>
#include <stdio.h>

extern char _heap_start;
int main(const char *args);

Area heap = RANGE(&_heap_start, PMEM_END);
static const char mainargs[MAINARGS_MAX_LEN] = TOSTRING(MAINARGS_PLACEHOLDER); // defined in CFLAGS

void putch(char ch) {
  outb(SERIAL_PORT, ch);
}

int getch(void) {
  return inb(SERIAL_PORT);
}

void halt(int code) {
  nemu_trap(code);
  while (1);
}

static inline void write_csr(uint32_t csr, uint32_t value) {
  asm volatile ("csrw %0, %1" :: "i"(csr), "r"(value));
}

static inline void _csr_info() {
  int vendor, arch;
  asm volatile("csrr %0, mvendorid" : "=r"(vendor));
  asm volatile("csrr %0, marchid"   : "=r"(arch));
  char vendor_str[5];
  for(int i = 0; i < 4; i++)
    vendor_str[i] = (vendor >> (24 - 8*i)) & 0xFF;
  vendor_str[4] = '\0';
  printf("-----------------\n");
  printf("\"%s\" - %u\n", vendor_str, arch);
  printf("-----------------\n");
}

void _trm_init() {
  write_csr(0xF11, 0x79737978);
  write_csr(0xF12, 0x018CE26E);
  // _csr_info();
  int ret = main(mainargs);
  halt(ret);
}
