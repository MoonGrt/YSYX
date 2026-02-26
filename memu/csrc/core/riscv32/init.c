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

#include <isa.h>
#include <memory/paddr.h>
#if defined(CONFIG_NEMU)

#elif defined(CONFIG_NPC)
#include "../../core/riscv32/local-include/exec.h"
#endif

// this is not consistent with uint8_t
static const uint32_t img [] = {
  0x00500513,  // 0x00 addi a0, zero, 5; a0 = 5
  0x00300593,  // 0x04 addi a1, zero, 3; a1 = 3
  0x00b50633,  // 0x08 add a2, a0, a1  ; a2 = a0 + a1
  0x00028823,  // 0x0c sb  zero, 16(t0); 存储 0 到 t0+16
  0x0102c503,  // 0x10 lbu a0, 16(t0)  ; 从 t0+16 读一个字节
  0x00100073,  // 0x04 ebreak
  0xdeadbeef,  // 0x08 deadbeef
};

void init_isa() {
  /* Load built-in image. */
  memcpy(guest_to_host(RESET_VECTOR), img, sizeof(img));
}
