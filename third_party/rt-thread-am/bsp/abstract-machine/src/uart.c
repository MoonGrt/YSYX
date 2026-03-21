/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtdevice.h>
#include <rtthread.h>
#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#define UART_DEFAULT_BAUDRATE 115200

struct device_uart {
  rt_ubase_t hw_base;
  rt_uint32_t irqno;
};

static void *uart0_base = (void*)0x10000000;
static struct rt_serial_device serial0;
static struct device_uart uart0;

static rt_err_t _uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg) {
  return (RT_EOK);
}

static rt_err_t _uart_control(struct rt_serial_device *serial, int cmd, void *arg) {
  return (RT_EOK);
}

static int _uart_putc(struct rt_serial_device *serial, char c) {
  putch(c);
  return 1;
}

#define AM_KEY_CHAR_MAP(key, normal, shifted) \
  case AM_KEY_##key: return shift ? (shifted) : (normal);

#define AM_KEY_TO_CHAR(_) \
  _(RETURN, '\n', '\n') \
  _(SPACE, ' ', ' ') \
  _(BACKSPACE, '\b', '\b') \
  _(TAB, '\t', '\t') \
  \
  _(A, 'a', 'A') _(B, 'b', 'B') _(C, 'c', 'C') _(D, 'd', 'D') \
  _(E, 'e', 'E') _(F, 'f', 'F') _(G, 'g', 'G') _(H, 'h', 'H') \
  _(I, 'i', 'I') _(J, 'j', 'J') _(K, 'k', 'K') _(L, 'l', 'L') \
  _(M, 'm', 'M') _(N, 'n', 'N') _(O, 'o', 'O') _(P, 'p', 'P') \
  _(Q, 'q', 'Q') _(R, 'r', 'R') _(S, 's', 'S') _(T, 't', 'T') \
  _(U, 'u', 'U') _(V, 'v', 'V') _(W, 'w', 'W') _(X, 'x', 'X') \
  _(Y, 'y', 'Y') _(Z, 'z', 'Z') \
  \
  _(0, '0', ')') \
  _(1, '1', '!') \
  _(2, '2', '@') \
  _(3, '3', '#') \
  _(4, '4', '$') \
  _(5, '5', '%') \
  _(6, '6', '^') \
  _(7, '7', '&') \
  _(8, '8', '*') \
  _(9, '9', '(') \
  \
  _(MINUS, '-', '_') \
  _(EQUALS, '=', '+') \
  _(LEFTBRACKET, '[', '{') \
  _(RIGHTBRACKET, ']', '}') \
  _(BACKSLASH, '\\', '|') \
  _(SEMICOLON, ';', ':') \
  _(APOSTROPHE, '\'', '"') \
  _(COMMA, ',', '<') \
  _(PERIOD, '.', '>') \
  _(SLASH, '/', '?')

static bool has_uart, has_kbd;
static int _uart_getc(struct rt_serial_device *serial) {
  /* 0 自动脚本 */
  static const char *p =
    "help\ndate\nversion\nfree\nps\npwd\nls\nmemtrace\nmemcheck\nutest_list\n";
  if (*p != '\0') return *(p++);
  /* 1 UART */
  if (has_uart) {
    AM_UART_RX_T rx = io_read(AM_UART_RX);
    if (rx.data != (char)-1)
      return rx.data;
  }
  /* 2 Keyboard */
  if (has_kbd) {
    static int shift = 0;
    AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
    if (ev.keycode == AM_KEY_LSHIFT || ev.keycode == AM_KEY_RSHIFT) {
      shift = ev.keydown;
      return 0;
    }
    if (ev.keydown) {
      switch (ev.keycode) {
        AM_KEY_TO_CHAR(AM_KEY_CHAR_MAP)
        default: return 0;
      }
    }
  }
  return -1;
}

const struct rt_uart_ops _uart_ops = {
  _uart_configure,
  _uart_control,
  _uart_putc,
  _uart_getc,
  // TODO: add DMA support
  RT_NULL};

/*
 * UART Initiation
 */
int rt_hw_uart_init(void) {
  has_uart = io_read(AM_UART_CONFIG).present;
  has_kbd  = io_read(AM_INPUT_CONFIG).present;

  struct rt_serial_device *serial;
  struct device_uart *uart;
  struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
  // register device
  serial = &serial0;
  uart = &uart0;

  serial->ops = &_uart_ops;
  serial->config = config;
  serial->config.baud_rate = UART_DEFAULT_BAUDRATE;
  uart->hw_base = (rt_ubase_t)uart0_base;
  uart->irqno = 0x0a;

  rt_hw_serial_register(serial,
      RT_CONSOLE_DEVICE_NAME,
      RT_DEVICE_FLAG_STREAM | RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
      uart);
  return 0;
}

/* WEAK for SDK 0.5.6 */
rt_weak void uart_debug_init(int uart_channel)
{
}
