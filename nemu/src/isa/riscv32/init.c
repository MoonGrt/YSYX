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

// static const uint32_t img[] = {
//   /* 0x0000 */ 0x00000297, // auipc t0,0              ; t0 = PC
//   /* 0x0004 */ 0x02028293, // addi  t0,t0,32          ; t0 = t0 + 32 (数据区偏移)

//   /* 存储和加载测试 */
//   /* 0x0008 */ 0x12300313, // li t1,0x123             ; t1 = 0x123
//   /* 0x000c */ 0x00030023, // sw t1,0(t0)             ; 存 t1 -> [t0+0]
//   /* 0x0010 */ 0x0002a303, // lw t1,0(t0)             ; 读回 t1
//   /* 0x0014 */ 0x00130313, // addi t1,t1,1            ; t1 = t1 + 1

//   /* 算术测试 */
//   /* 0x0018 */ 0x00b303b3, // add t2,t1,t1            ; t2 = t1 + t1
//   /* 0x001c */ 0x40b383b3, // sub t2,t2,t1            ; t2 = t2 - t1
//   /* 0x0020 */ 0x02b303b3, // mul t2,t1,t1            ; t2 = t1 * t1 (需要 M 扩展)
//   /* 0x0024 */ 0x02b353b3, // div t2,t1,t1            ; t2 = t1 / t1 (结果 1)

//   /* 分支测试 */
//   /* 0x0028 */ 0x00630363, // beq t1,t1,+12           ; 跳转到 0x0038
//   /* 0x002c */ 0x00100313, // addi t1,zero,1          ; (不执行)
//   /* 0x0030 */ 0x00200313, // addi t1,zero,2          ; (不执行)
//   /* 0x0034 */ 0x00000013, // nop
//   /* 0x0038 */ 0x00300313, // addi t1,zero,3          ; (跳转到这里)

//   /* 条件不等跳转 */
//   /* 0x003c */ 0x00631263, // bne t1,zero,+20         ; 跳过接下来的几条
//   /* 0x0040 */ 0x00400313, // addi t1,zero,4
//   /* 0x0044 */ 0x00500313, // addi t1,zero,5
//   /* 0x0048 */ 0x00000013, // nop

//   /* jal/jalr 测试 */
//   /* 0x004c */ 0x010000ef, // jal ra,0x005c           ; 跳转并保存返回地址
//   /* 0x0050 */ 0x00600313, // addi t1,zero,6          ; (不执行)
//   /* 0x0054 */ 0x00000013, // nop
//   /* 0x0058 */ 0x00000013, // nop
//   /* 0x005c */ 0x00700313, // addi t1,zero,7          ; jal 目标
//   /* 0x0060 */ 0x00008067, // jalr zero,0(ra)         ; 返回

//   /* 0x0064 */ 0x00100073, // ebreak (used as nemu_trap)

//   /* 数据区（在 t0+32 开始） */
//   /* 0x0064 */ 0x00100073, // ebreak (trap)
//   /* 0x0068 */ 0xdeadbeef, // 数据
//   /* 0x006c */ 0x00000000,
//   /* 0x0070 */ 0x00000000,
//   /* 0x0074 */ 0x00000000,
// };

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
