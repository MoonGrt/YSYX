/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
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
// but it is ok since we do not access the array directly
// static const uint32_t img [] = {
//   0x00000297,  // auipc t0,0
//   0x00028823,  // sb  zero,16(t0)
//   0x0102c503,  // lbu a0,16(t0)
//   0x00100073,  // ebreak (used as nemu_trap)
//   0xdeadbeef,  // some data
// };

static const uint32_t img [] = {
  0x00000297,  // auipc t0,0
  0x00500513,  // li a0, 5
  0x00300593,  // li a1, 3
  0x00b50633,  // add a2, a0, a1
  0x40b506b3,  // sub a3, a0, a1
  0x00b51733,  // and a4, a0, a1
  0x00b567b3,  // or  a5, a0, a1
  0x00b54733,  // xor a6, a0, a1
  0x00028823,  // sb  zero, 16(t0)
  0x0102c503,  // lbu a0, 16(t0)
  0x00100073,  // ebreak
  0xdeadbeef,  // some data
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
