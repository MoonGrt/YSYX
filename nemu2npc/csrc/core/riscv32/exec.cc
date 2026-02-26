#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VMiniRVSOC.h"

#include "local-include/reg.h"
#include <cpu/cpu.h>
#include <cpu/ifetch.h>
#include <cpu/decode.h>
#include <memory/paddr.h>

#define DEBUG

VMiniRVSOC *top = new VMiniRVSOC;
VerilatedVcdC *tfp = new VerilatedVcdC;

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
#ifdef DEBUG
    printf("paddr_read:  addr=0x%08x", raddr);
#endif
    raddr = raddr & ~0x3u;
    word_t data= paddr_read(raddr, 4);
#ifdef DEBUG
    printf(",   data=0x%08x\n", data);
#endif
    return data;
  }
  void pmem_write(int waddr, char wmask, int wdata){
#ifdef DEBUG
    printf("paddr_write: addr=0x%08x, mask=0x%x, data=0x%08x\n", waddr, wmask, wdata);
#endif
    waddr = waddr & ~0x3u;
    paddr_write(waddr, wmask, wdata);
  }
}

static vluint64_t sim_time = 0;
static void tick(){
  // ======== 上升沿 ========
  top->clock = 0;
  top->eval();
  tfp->dump(sim_time++);
  // ======== 下降沿 ========
  top->clock = 1;
  top->eval();
  tfp->dump(sim_time++);
}

static void reset(){
  printf("[NPC] Resetting ...\n");
  top->reset = 1;
  tick();
  top->reset = 0;
}

extern "C" {
  void rtl_init(int argc, char *argv[]) {
    // 初始化仿真对象
    Verilated::commandArgs(argc, argv);
    Verilated::mkdir("logs");
    // 创建 build 目录（如果不存在）
    Verilated::mkdir("build");
    // 创建 VCD 波形对象
    Verilated::traceEverOn(true);  // 必须先打开 trace
    top->trace(tfp, 99);  // 99 是 trace depth
    tfp->open("build/wave.vcd");
  }
  void rtl_reset() {
    reset();
  }
  void rtl_step() {
    tick();
  }
}
