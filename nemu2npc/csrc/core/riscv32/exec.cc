#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VMiniRVSOC.h"

// #define DEBUG

VMiniRVSOC *top = new VMiniRVSOC;
VerilatedVcdC *tfp = new VerilatedVcdC;

typedef uint32_t word_t;
typedef uint32_t paddr_t;

#define MEM_BASE 0x80000000L
#define MEM_SIZE 0x01000000L
uint8_t *mem = NULL;

static inline bool in_mem(paddr_t addr){
  return addr - MEM_BASE <= MEM_SIZE && addr >= MEM_BASE;
}
uint8_t* guest_to_host(paddr_t paddr){
  if (in_mem(paddr)) return mem + paddr - MEM_BASE;
  else return NULL;
}
word_t paddr_read(paddr_t addr, int len){
  uint8_t *host = guest_to_host(addr);
  if (!host) return 0;
  word_t result = 0;
  switch (len) {
    case 1: result = *host; break;
    case 2: result = *(uint16_t *)host; break;
    case 4: result = *(uint32_t *)host; break;
    default: return 0;
  }
#ifdef DEBUG
  printf("paddr_read:  addr=0x%08x,  len=%d,   data=0x%08x\n", addr, len, result);
#endif
  return result;
}
void paddr_write(paddr_t addr, int mask, word_t data){
#ifdef DEBUG
  printf("paddr_write: addr=0x%08x, mask=0x%x, data=0x%08x\n", addr, mask, data);
#endif
  if (addr < MEM_BASE || addr >= MEM_BASE + MEM_SIZE) return;
  for(int i = 0; i < 4; i++)
    if(mask & (1 << i)) *guest_to_host(addr + i) = (data >> (i * 8)) & 0xff;
}

extern "C" {
  #define EBREAK_CODE    0
  #define ZERO_INST_CODE 1
  #define OTHER_E_CODE   2
  #define UNIMPL_CODE    3
  bool is_ebreak;
  void ebreak(uint8_t code) {
    // 异常信息映射：颜色 + 消息
    is_ebreak = (code == EBREAK_CODE);
    struct {
      const char* color;
      const char* msg;
    } exc_info[] = {
      [EBREAK_CODE]  = {"\33[1;32m", "EBREAK: HIT GOOD TRAP"},
      [ZERO_INST_CODE]= {"\33[1;34m", "ALL ZERO INSTRUCTION"},
      [OTHER_E_CODE] = {"\33[1;33m", "E-INSTRUCTION EXCEPTION"},
      [UNIMPL_CODE]  = {"\33[1;31m", "UNIMPLEMENTED INSTRUCTION"},
    };
    // 默认异常（安全）
    const char* color = "\33[1;31m";
    const char* msg   = "UNKNOWN EXCEPTION";
    if (code <= ZERO_INST_CODE) {
      color = exc_info[code].color;
      msg   = exc_info[code].msg;
    }
    // 统一打印
    printf("[NPC] %s%s\33[0m at pc = 0x%08x -> ", color, msg, top->io_pc);
    printf("\33[1;35mInstruction\33[0m = 0x%08x\n", top->io_inst);
    // 停止仿真
    Verilated::gotFinish(true);
  }
  int pmem_read(int raddr){
    raddr = raddr & ~0x3u;
    word_t data= paddr_read(raddr, 4);
    return data;
  }
  void pmem_write(int waddr, char wmask, int wdata){
    waddr = waddr & ~0x3u;
    paddr_write(waddr, wmask, wdata);
  }
}

extern "C" {
  void rtl_init(int argc, char *argv[]) {
    Verilated::commandArgs(argc, argv);
    Verilated::mkdir("logs");
  }
  void rtl_step() {
    top->clock = 0; top->eval();
    top->clock = 1; top->eval();
  }
}
