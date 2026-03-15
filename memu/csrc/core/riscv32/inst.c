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

enum {
  TYPE_I, TYPE_U, TYPE_S, TYPE_R, TYPE_J, TYPE_B,
  TYPE_N,  // none
};

#define src1R() do { *src1 = R(rs1); } while (0)
#define src2R() do { *src2 = R(rs2); } while (0)
#define immI() do { *imm = SEXT(BITS(i, 31, 20), 12); } while(0)
#define immU() do { *imm = SEXT(BITS(i, 31, 12), 20) << 12; } while(0)
#define immS() do { *imm = (SEXT(BITS(i, 31, 25), 7) << 5) | BITS(i, 11, 7); } while(0)
#define immJ() do { *imm = (SEXT(BITS(i, 31, 31), 1) << 20) | BITS(i, 19, 12) << 12 | BITS(i, 20, 20) << 11 | BITS(i, 30, 21) << 1; } while(0)
#define immB() do { *imm = (SEXT(BITS(i, 31, 31), 1) << 12) | BITS(i, 7, 7) << 11 | BITS(i, 30, 25) << 5 | BITS(i, 11, 8) << 1; } while(0)

static void decode_operand(Decode *s, int *rd, word_t *src1, word_t *src2, word_t *imm, int type) {
  uint32_t i = s->isa.inst;
  int rs1 = BITS(i, 19, 15);
  int rs2 = BITS(i, 24, 20);
     *rd  = BITS(i, 11, 7);
  switch (type) {
    case TYPE_I: src1R();          immI(); break;
    case TYPE_U:                   immU(); break;
    case TYPE_S: src1R(); src2R(); immS(); break;
    case TYPE_R: src1R(); src2R();         break;
    case TYPE_J:                   immJ(); break;
    case TYPE_B: src1R(); src2R(); immB(); break;
    case TYPE_N:                           break;  // none
    default: panic("unsupported type = %d", type);
  }
}

static int step(Decode *s) {
  *s = rtlDecode;
  rtl_step();

#define INSTPAT_INST(s) ((s)->isa.inst)
#define INSTPAT_MATCH(s, name, type, ... /* execute body */ ) { \
  int rd = 0; \
  word_t src1 = 0, src2 = 0, imm = 0; \
  decode_operand(s, &rd, &src1, &src2, &imm, concat(TYPE_, type)); \
  __VA_ARGS__ ; \
}
  INSTPAT_START();
  INSTPAT("??????? ????? ????? 000 ????? 1100111", jalr  , I, s->dnpc = (src1 + imm) & ~(uint32_t)0x1; R(rd) = s->snpc; 
  IFDEF(CONFIG_FTRACE, {
    if (s->isa.inst == 0x00008067)
      ftrace_ret(s->pc);  // ret -> jalr x0, 0(x1)
    else if (rd == 1)
      ftrace_call(s->pc, s->dnpc, false);
    else if (rd == 0 && imm == 0)
      ftrace_call(s->pc, s->dnpc, true);  // jr rs1 -> jalr x0, 0(rs1), which may be other control flow e.g. 'goto','for'
  }));
  INSTPAT("??????? ????? ????? ??? ????? 1101111", jal   , J, R(rd) = s->pc + 4; s->dnpc = s->pc + imm; 
  IFDEF(CONFIG_FTRACE, { 
    if (rd == 1)  // x1: return address for jumps
      ftrace_call(s->pc, s->dnpc, false);
  }));
  INSTPAT("0000000 00000 00000 000 00000 1110011", ecall , N, IFDEF(CONFIG_ETRACE, etrace_exec(s->pc)); s->dnpc = isa_raise_intr(17, s->pc));
  INSTPAT_END();
  return 0;
}

int isa_exec_once(Decode *s) {

  // // jalr -> ftrace
  // IFDEF(CONFIG_FTRACE, {
  //   if (s->isa.inst == 0x00008067)
  //     ftrace_ret(s->pc);  // ret -> jalr x0, 0(x1)
  //   else if (rd == 1)
  //     ftrace_call(s->pc, s->dnpc, false);
  //   else if (rd == 0 && imm == 0)
  //     ftrace_call(s->pc, s->dnpc, true);  // jr rs1 -> jalr x0, 0(rs1), which may be other control flow e.g. 'goto','for'
  // });
  // jal -> ftrace
  // IFDEF(CONFIG_FTRACE, { 
  //   if (rd == 1)  // x1: return address for jumps
  //     ftrace_call(s->pc, s->dnpc, false);
  // });
  // ecall -> etrace_exec
  // IFDEF(CONFIG_ETRACE, if (s->isa.inst == 0x00000073) etrace_exec(s->pc));
  return step(s);
}
