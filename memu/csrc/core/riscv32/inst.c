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
#include "../../utils/local-include/itrace.h"
#if defined(CONFIG_NEMU)

#elif defined(CONFIG_NPC)
#include "../../core/riscv32/local-include/exec.h"
#endif

extern Decode rtlDecode;
int isa_exec_once(Decode *s) {
  *s = rtlDecode;
  IFDEF(CONFIG_ITRACE, trace_inst(s->pc, s->isa.inst));
  rtl_step();
  return 0;
}
