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

void _csr_info() {
  uint32_t vendor, arch;
  asm volatile("csrr %0, mvendorid" : "=r"(vendor));
  asm volatile("csrr %0, marchid"   : "=r"(arch));
  printf("mvendorid = 0x%x\n", vendor);
  printf("marchid   = %u\n", arch);
}

void _trm_init() {
  int ret = main(mainargs);
  halt(ret);
}
