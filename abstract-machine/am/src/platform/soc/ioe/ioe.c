#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#define SOC_CLOCK_HZ 100000000ull

static uint64_t read_cycle(void) {
  uint32_t hi, lo, hi_again;
  do {
    asm volatile("csrr %0, mcycleh" : "=r"(hi));
    asm volatile("csrr %0, mcycle" : "=r"(lo));
    asm volatile("csrr %0, mcycleh" : "=r"(hi_again));
  } while (hi != hi_again);
  return ((uint64_t)hi << 32) | lo;
}

static void puthex32(uint32_t value) {
  static const char hex[] = "0123456789abcdef";
  for (int shift = 28; shift >= 0; shift -= 4)
    putch(hex[(value >> shift) & 0xf]);
  putch('\n');
}

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
        (AM_TIMER_CONFIG_T) { .present = true, .has_rtc = false };
      return;
    case AM_TIMER_UPTIME:
      ((AM_TIMER_UPTIME_T *)buf)->us =
        read_cycle() / (SOC_CLOCK_HZ / 1000000ull);
      return;
    case AM_TIMER_RTC:
      *(AM_TIMER_RTC_T *)buf = (AM_TIMER_RTC_T) {
        .year = 1900, .month = 1, .day = 1,
        .hour = 0, .minute = 0, .second = 0,
      };
      return;
    case AM_INPUT_CONFIG:
      *(AM_INPUT_CONFIG_T *)buf = (AM_INPUT_CONFIG_T) { .present = false };
      return;
    case AM_INPUT_KEYBRD:
      *(AM_INPUT_KEYBRD_T *)buf =
        (AM_INPUT_KEYBRD_T) { .keydown = false, .keycode = AM_KEY_NONE };
      return;
    case AM_GPU_CONFIG:
      *(AM_GPU_CONFIG_T *)buf = (AM_GPU_CONFIG_T) { .present = false };
      return;
    case AM_GPU_STATUS:
      *(AM_GPU_STATUS_T *)buf = (AM_GPU_STATUS_T) { .ready = false };
      return;
    case AM_AUDIO_CONFIG:
      *(AM_AUDIO_CONFIG_T *)buf = (AM_AUDIO_CONFIG_T) { .present = false };
      return;
    case AM_AUDIO_STATUS:
      *(AM_AUDIO_STATUS_T *)buf = (AM_AUDIO_STATUS_T) { .count = 0 };
      return;
    case AM_DISK_CONFIG:
      *(AM_DISK_CONFIG_T *)buf = (AM_DISK_CONFIG_T) { .present = false };
      return;
    case AM_DISK_STATUS:
      *(AM_DISK_STATUS_T *)buf = (AM_DISK_STATUS_T) { .ready = false };
      return;
    case AM_NET_CONFIG:
      *(AM_NET_CONFIG_T *)buf = (AM_NET_CONFIG_T) { .present = false };
      return;
    case AM_NET_STATUS:
      *(AM_NET_STATUS_T *)buf =
        (AM_NET_STATUS_T) { .rx_len = 0, .tx_len = 0 };
      return;
    default:
      putstr("unsupported soc IOE read: ");
      puthex32(reg);
      putstr("caller: ");
      puthex32((uintptr_t)__builtin_return_address(0));
      halt(1);
  }
}

void ioe_write(int reg, void *buf) {
  if (reg == AM_UART_TX) {
    putch(((AM_UART_TX_T *)buf)->data);
    return;
  }
  putstr("unsupported soc IOE write: ");
  puthex32(reg);
  halt(1);
}
