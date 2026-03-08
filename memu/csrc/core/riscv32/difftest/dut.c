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
#include <cpu/difftest.h>
#include "../local-include/reg.h"

#define CHECKDIFF(p) \
  if (ref_r->p != cpu.p) { \
    printf("difftest fail at " #p ", expect " FMT_WORD " got " FMT_WORD "\n", ref_r->p, cpu.p); \
    result = false; \
  }

#define CHECKDIFF_FMT(p, fmt, ...) \
  if ((ref_r->p != cpu.p) && ((cpu.p != 0x79737978) || (cpu.p != 0x018ce26e))) { \
    printf("difftest fail at " fmt ", expect " FMT_WORD " got " FMT_WORD "\n", ## __VA_ARGS__, ref_r->p, cpu.p); \
    result = false; \
  }

#define CSR_LIST(_) \
  _(mepc)           \
  _(mstatus)        \
  _(mcause)         \
  _(mtvec)          \
  _(mvendorid)      \
  _(marchid)        \

#define CHECKDIFF_CSR(p) \
  if (ref_r->csr.p != cpu.csr.p) { \
    printf("difftest fail at csr." #p ", expect " FMT_WORD " got " FMT_WORD "\n", \
           ref_r->csr.p, cpu.csr.p); \
    result = false; \
  }

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  bool result = true;
  CHECKDIFF(pc);
  for (int i = 0; i < 32; i++)
    CHECKDIFF_FMT(gpr[i], "gpr[%d]", i);
#define _(x) CHECKDIFF_CSR(x);
  CSR_LIST(_)
#undef _
  return result;
}

void isa_difftest_attach() {
}
