#include <soc-device.h>

#define UART_TX 0

#ifdef BARE_METAL
void _start() {
  *(volatile char *)(UART_BASE + UART_TX) = 'A';
  *(volatile char *)(UART_BASE + UART_TX) = '\n';
  while (1);
}
#else
int main(void) {
  *(volatile char *)(UART_BASE + UART_TX) = 'A';
  *(volatile char *)(UART_BASE + UART_TX) = '\n';
  // while (1);
  return 0;
}
#endif
