#include <am.h>
#include <klib.h>
#include <klib-macros.h>

bool ioe_init(void) {
  return true;
}

void ioe_read(int reg, void *buf) {
  switch (reg) {
    case AM_UART_CONFIG:
      *(AM_UART_CONFIG_T *)buf = (AM_UART_CONFIG_T) { .present = true };
      return;
    case AM_UART_RX:
      ((AM_UART_RX_T *)buf)->data = getch();
      return;
    case AM_TIMER_CONFIG:
      *(AM_TIMER_CONFIG_T *)buf =
        (AM_TIMER_CONFIG_T) { .present = false, .has_rtc = false };
      return;
    case AM_INPUT_CONFIG:
      *(AM_INPUT_CONFIG_T *)buf = (AM_INPUT_CONFIG_T) { .present = false };
      return;
    case AM_GPU_CONFIG:
      *(AM_GPU_CONFIG_T *)buf = (AM_GPU_CONFIG_T) { .present = false };
      return;
    case AM_AUDIO_CONFIG:
      *(AM_AUDIO_CONFIG_T *)buf = (AM_AUDIO_CONFIG_T) { .present = false };
      return;
    case AM_DISK_CONFIG:
      *(AM_DISK_CONFIG_T *)buf = (AM_DISK_CONFIG_T) { .present = false };
      return;
    case AM_NET_CONFIG:
      *(AM_NET_CONFIG_T *)buf = (AM_NET_CONFIG_T) { .present = false };
      return;
    default:
      panic("unsupported ysyxsoc IOE read");
  }
}

void ioe_write(int reg, void *buf) {
  if (reg == AM_UART_TX) {
    putch(((AM_UART_TX_T *)buf)->data);
    return;
  }
  panic("unsupported ysyxsoc IOE write");
}
