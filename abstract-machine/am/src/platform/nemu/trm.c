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
  int vendor, arch;
  asm volatile("csrr %0, mvendorid" : "=r"(vendor));
  asm volatile("csrr %0, marchid"   : "=r"(arch));
  char vendor_str[5];
  for(int i = 0; i < 4; i++)
      vendor_str[i] = (vendor >> (24 - 8*i)) & 0xFF;
  vendor_str[4] = '\0';
  printf("mvendorid = \"%s\"\n", vendor_str);
  printf("marchid   = %u\n", arch);
}

void _trm_init() {
  _csr_info();
  int ret = main(mainargs);
  halt(ret);
}
