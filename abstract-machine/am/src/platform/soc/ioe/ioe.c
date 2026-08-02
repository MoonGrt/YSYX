#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <soc.h>

#define SOC_CLOCK_HZ 100000000ull
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

static const uint8_t ps2_to_am[256] = {
  [0x76] = AM_KEY_ESCAPE,
  [0x05] = AM_KEY_F1, [0x06] = AM_KEY_F2, [0x04] = AM_KEY_F3,
  [0x0c] = AM_KEY_F4, [0x03] = AM_KEY_F5, [0x0b] = AM_KEY_F6,
  [0x83] = AM_KEY_F7, [0x0a] = AM_KEY_F8, [0x01] = AM_KEY_F9,
  [0x09] = AM_KEY_F10, [0x78] = AM_KEY_F11, [0x07] = AM_KEY_F12,
  [0x0e] = AM_KEY_GRAVE,
  [0x16] = AM_KEY_1, [0x1e] = AM_KEY_2, [0x26] = AM_KEY_3,
  [0x25] = AM_KEY_4, [0x2e] = AM_KEY_5, [0x36] = AM_KEY_6,
  [0x3d] = AM_KEY_7, [0x3e] = AM_KEY_8, [0x46] = AM_KEY_9,
  [0x45] = AM_KEY_0, [0x4e] = AM_KEY_MINUS, [0x55] = AM_KEY_EQUALS,
  [0x66] = AM_KEY_BACKSPACE, [0x0d] = AM_KEY_TAB,
  [0x15] = AM_KEY_Q, [0x1d] = AM_KEY_W, [0x24] = AM_KEY_E,
  [0x2d] = AM_KEY_R, [0x2c] = AM_KEY_T, [0x35] = AM_KEY_Y,
  [0x3c] = AM_KEY_U, [0x43] = AM_KEY_I, [0x44] = AM_KEY_O,
  [0x4d] = AM_KEY_P, [0x54] = AM_KEY_LEFTBRACKET,
  [0x5b] = AM_KEY_RIGHTBRACKET, [0x5d] = AM_KEY_BACKSLASH,
  [0x58] = AM_KEY_CAPSLOCK,
  [0x1c] = AM_KEY_A, [0x1b] = AM_KEY_S, [0x23] = AM_KEY_D,
  [0x2b] = AM_KEY_F, [0x34] = AM_KEY_G, [0x33] = AM_KEY_H,
  [0x3b] = AM_KEY_J, [0x42] = AM_KEY_K, [0x4b] = AM_KEY_L,
  [0x4c] = AM_KEY_SEMICOLON, [0x52] = AM_KEY_APOSTROPHE,
  [0x5a] = AM_KEY_RETURN, [0x12] = AM_KEY_LSHIFT,
  [0x1a] = AM_KEY_Z, [0x22] = AM_KEY_X, [0x21] = AM_KEY_C,
  [0x2a] = AM_KEY_V, [0x32] = AM_KEY_B, [0x31] = AM_KEY_N,
  [0x3a] = AM_KEY_M, [0x41] = AM_KEY_COMMA, [0x49] = AM_KEY_PERIOD,
  [0x4a] = AM_KEY_SLASH, [0x59] = AM_KEY_RSHIFT,
  [0x14] = AM_KEY_LCTRL, [0x11] = AM_KEY_LALT, [0x29] = AM_KEY_SPACE,
};

static const uint8_t ps2_ext_to_am[256] = {
  [0x5f] = AM_KEY_APPLICATION, [0x11] = AM_KEY_RALT,
  [0x14] = AM_KEY_RCTRL, [0x75] = AM_KEY_UP, [0x72] = AM_KEY_DOWN,
  [0x6b] = AM_KEY_LEFT, [0x74] = AM_KEY_RIGHT,
  [0x70] = AM_KEY_INSERT, [0x71] = AM_KEY_DELETE,
  [0x6c] = AM_KEY_HOME, [0x69] = AM_KEY_END,
  [0x7d] = AM_KEY_PAGEUP, [0x7a] = AM_KEY_PAGEDOWN,
};

static bool ps2_extended;
static bool ps2_break;

static AM_INPUT_KEYBRD_T read_key(void) {
  uint8_t scan = inb(PS2_BASE);
  AM_INPUT_KEYBRD_T result = { .keydown = false, .keycode = AM_KEY_NONE };
  if (scan == 0) return result;
  if (scan == 0xe0) {
    ps2_extended = true;
    return result;
  }
  if (scan == 0xf0) {
    ps2_break = true;
    return result;
  }
  result.keycode = ps2_extended ? ps2_ext_to_am[scan] : ps2_to_am[scan];
  result.keydown = !ps2_break;
  ps2_extended = false;
  ps2_break = false;
  return result;
}

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
      *(AM_INPUT_CONFIG_T *)buf = (AM_INPUT_CONFIG_T) { .present = true };
      return;
    case AM_INPUT_KEYBRD:
      *(AM_INPUT_KEYBRD_T *)buf = read_key();
      return;
    case AM_GPU_CONFIG:
      *(AM_GPU_CONFIG_T *)buf = (AM_GPU_CONFIG_T) {
        .present = true, .has_accel = false,
        .width = SCREEN_WIDTH, .height = SCREEN_HEIGHT,
        .vmemsz = SCREEN_WIDTH * SCREEN_HEIGHT * 4,
      };
      return;
    case AM_GPU_STATUS:
      *(AM_GPU_STATUS_T *)buf = (AM_GPU_STATUS_T) { .ready = true };
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
  if (reg == AM_GPU_FBDRAW) {
    AM_GPU_FBDRAW_T *ctl = buf;
    if (ctl->pixels == NULL || ctl->w <= 0 || ctl->h <= 0) return;
    int x0 = ctl->x < 0 ? 0 : ctl->x;
    int y0 = ctl->y < 0 ? 0 : ctl->y;
    int x1 = ctl->x + ctl->w;
    int y1 = ctl->y + ctl->h;
    if (x1 > SCREEN_WIDTH) x1 = SCREEN_WIDTH;
    if (y1 > SCREEN_HEIGHT) y1 = SCREEN_HEIGHT;
    if (x0 >= x1 || y0 >= y1) return;
    uint32_t *src = ctl->pixels;
    volatile uint32_t *fb = (volatile uint32_t *)(uintptr_t)VGA_BASE;
    for (int y = y0; y < y1; y++) {
      int src_y = y - ctl->y;
      for (int x = x0; x < x1; x++)
        fb[y * SCREEN_WIDTH + x] = src[src_y * ctl->w + x - ctl->x];
    }
    return;
  }
  putstr("unsupported soc IOE write: ");
  puthex32(reg);
  halt(1);
}
