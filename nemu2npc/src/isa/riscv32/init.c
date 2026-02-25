/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NPC is licensed under Mulan PSL v2.
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

#include <isa.h>
#include <memory/paddr.h>

// this is not consistent with uint8_t
static const uint32_t img [] = {
  0x00000297,  // 0x00 // auipc t0,0
  0x00500513,  // 0x04 // li a0, 5
  0x00300593,  // 0x08 // li a1, 3
  0x00b50633,  // 0x0C // add a2, a0, a1
  0x40b506b3,  // 0x10 // sub a3, a0, a1
  0x00b51733,  // 0x14 // and a4, a0, a1
  0x00b567b3,  // 0x18 // or  a5, a0, a1
  0x00b54733,  // 0x1C // xor a6, a0, a1
  0x00028823,  // 0x20 // sb  zero, 16(t0)
  0x0102c503,  // 0x24 // lbu a0, 16(t0)
  0x00100073,  // 0x28 // ebreak
  0xdeadbeef,  // 0x2C // some data
};

static void restart() {
  /* Set the initial program counter. */
  cpu.pc = RESET_VECTOR;
  /* The zero register is always 0. */
  cpu.gpr[0] = 0;
}

void init_isa() {
  /* Load built-in image. */
  memcpy(guest_to_host(RESET_VECTOR), img, sizeof(img));
  /* Initialize this virtual computer system. */
  restart();
}
