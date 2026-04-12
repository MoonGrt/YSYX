/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* MEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <utils.h>
#include <device/map.h>

/* http://en.wikibooks.org/wiki/Serial_Programming/8250_UART_Programming */
// NOTE: this is compatible to 16550

#define CH_OFFSET 0

static uint8_t *serial_base = NULL;

static void serial_putc(char ch) {
  MUXDEF(CONFIG_TARGET_AM, putch(ch), putc(ch, stderr));
}

static int serial_getc(void) {
  return MUXDEF(CONFIG_TARGET_AM, getch(), getc(stdin));
}

static void serial_io_handler(uint32_t offset, int len, bool is_write) {
  assert(len == 1 || len == 4);  // After memory alignment, NPC only support `len=4`
  switch (offset) {
    /* We bind the serial port with the host stderr in MEMU. */
    case CH_OFFSET:
      if (is_write) serial_putc(serial_base[0]);
      else serial_base[0] = (uint8_t)serial_getc();
      break;
    default: panic("do not support offset = %d", offset);
  }
}

#ifndef CONFIG_TARGET_AM
#include <fcntl.h> 
#include <unistd.h>
#endif
void init_serial() {
  serial_base = new_space(8);
#ifdef CONFIG_HAS_PORT_IO
  add_pio_map ("serial", CONFIG_SERIAL_PORT, serial_base, 8, serial_io_handler);
#else
#ifndef CONFIG_TARGET_AM
  int ret = fcntl(STDIN_FILENO, F_GETFL);
  assert(ret != -1);
  int flag = ret | O_NONBLOCK;
  ret = fcntl(STDIN_FILENO, F_SETFL, flag);
  assert(ret != -1);
#endif
  add_mmio_map("serial", CONFIG_SERIAL_MMIO, serial_base, 8, serial_io_handler);
#endif
}
