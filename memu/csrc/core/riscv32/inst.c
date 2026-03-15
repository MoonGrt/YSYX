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

#include <cpu/decode.h>

void rtl_step(void);
void ftrace_ret(paddr_t pc);
void ftrace_call(paddr_t pc, paddr_t target, bool is_tail);
void etrace_exec(uint32_t pc);
extern Decode rtlDecode;

int isa_exec_once(Decode *s) {
  *s = rtlDecode;
  rtl_step();
  // // jalr -> ftrace
  // IFDEF(CONFIG_FTRACE, {
  //   if (s->isa.inst == 0x00008067)
  //     ftrace_ret(s->pc);  // ret -> jalr x0, 0(x1)
  //   else if (rd == 1)
  //     ftrace_call(s->pc, s->dnpc, false);
  //   else if (rd == 0 && imm == 0)
  //     ftrace_call(s->pc, s->dnpc, true);  // jr rs1 -> jalr x0, 0(rs1), which may be other control flow e.g. 'goto','for'
  // });
  // // jal -> ftrace
  // IFDEF(CONFIG_FTRACE, { 
  //   if (rd == 1)  // x1: return address for jumps
  //     ftrace_call(s->pc, s->dnpc, false);
  // });
  // ecall -> etrace_exec
  IFDEF(CONFIG_ETRACE, if (s->isa.inst == 0x00000073) etrace_exec(s->pc));
  return 0;
}
