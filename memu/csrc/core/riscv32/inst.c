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

static void decode_operand(Decode *s, int *rd, word_t *src1, word_t *src2, word_t *imm, int type) {
  uint32_t i = s->isa.inst;
  int rs1 = BITS(i, 19, 15);
  int rs2 = BITS(i, 24, 20);
     *rd  = BITS(i, 11, 7);
}

static int step(Decode *s) {
  rtl_step();

#define INSTPAT_INST(s) ((s)->isa.inst)
#define INSTPAT_MATCH(s, name, type, ... /* execute body */ ) { \
  int rd = 0; \
  word_t src1 = 0, src2 = 0, imm = 0; \
  decode_operand(s, &rd, &src1, &src2, &imm, concat(TYPE_, type)); \
  __VA_ARGS__ ; \
}
  INSTPAT_START();
  INSTPAT("??????? ????? ????? 000 ????? 1100111", jalr  , I, 
  IFDEF(CONFIG_FTRACE, {
    if (s->isa.inst == 0x00008067)
      ftrace_ret(s->pc);  // ret -> jalr x0, 0(x1)
    else if (rd == 1)
      ftrace_call(s->pc, s->dnpc, false);
    else if (rd == 0 && imm == 0)
      ftrace_call(s->pc, s->dnpc, true);  // jr rs1 -> jalr x0, 0(rs1), which may be other control flow e.g. 'goto','for'
  }));
  INSTPAT("??????? ????? ????? ??? ????? 1101111", jal   , J, 
  IFDEF(CONFIG_FTRACE, { 
    if (rd == 1)  // x1: return address for jumps
      ftrace_call(s->pc, s->dnpc, false);
  }));
  INSTPAT("0000000 00000 00000 000 00000 1110011", ecall , N, IFDEF(CONFIG_ETRACE, etrace_exec(s->pc)); s->dnpc = isa_raise_intr(17, s->pc));
  INSTPAT_END();
  return 0;
}

int isa_exec_once(Decode *s) {
  *s = rtlDecode;
  rtl_step();
  return 0;
}
