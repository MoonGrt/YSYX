#include <am.h>
#include <klib.h>
#include <soc.h>

extern char _heap_start;
int main(const char *args);

Area heap = RANGE(&_heap_start, HEAP_END);
static const char mainargs[MAINARGS_MAX_LEN] =
  TOSTRING(MAINARGS_PLACEHOLDER);

enum {
  UART_RBR = 0,
  UART_THR = 0,
  UART_DLL = 0,
  UART_DLM = 1,
  UART_FCR = 2,
  UART_LCR = 3,
  UART_LSR = 5,
  UART_LCR_DLAB = 0x80,
  UART_LSR_DR = 0x01,
  UART_LSR_THRE = 0x20,
};

static void uart_init(void) {
  outb(UART_BASE + UART_LCR, UART_LCR_DLAB);
  for (int i = 0; i < 8; i++) asm volatile("nop");
  outb(UART_BASE + UART_DLL, 1);
  outb(UART_BASE + UART_DLM, 0);
  outb(UART_BASE + UART_LCR, 0x03);
  for (int i = 0; i < 8; i++) asm volatile("nop");
  outb(UART_BASE + UART_FCR, 0x07);
}

void putch(char ch) {
  while ((inb(UART_BASE + UART_LSR) & UART_LSR_THRE) == 0);
  outb(UART_BASE + UART_THR, ch);
}

int getch(void) {
  if ((inb(UART_BASE + UART_LSR) & UART_LSR_DR) == 0) return -1;
  return inb(UART_BASE + UART_RBR);
}

void halt(int code) {
  soc_trap(code);
  while (1);
}

static inline void csr_info() {
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

void _trm_init(void) {
  uart_init();
  // csr_info();
  halt(main(mainargs));
}
