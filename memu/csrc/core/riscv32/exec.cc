#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VMiniRVSOC.h"

#include <common.h>
#include <utils.h>
#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <memory/paddr.h>
#include <memory/host.h>
#include "../../utils/local-include/itrace.h"

VMiniRVSOC *top = new VMiniRVSOC;
VerilatedVcdC *tfp = new VerilatedVcdC;

extern "C" {
  #define EBREAK_CODE    0
  #define ZERO_INST_CODE 1
  #define OTHER_E_CODE   2
  #define UNIMPL_CODE    3
  void ebreak(uint8_t code) {
    if (code == EBREAK_CODE) MEMUTRAP(cpu.pc, code);
    else INV(cpu.pc);
    Verilated::gotFinish(true);
  }
  int pmem_read(int raddr){
    raddr = raddr & ~0x3u;
    if (in_pmem(raddr)) {
      IFDEF(CONFIG_MTRACE, display_pread(raddr, 4));
      return host_read(guest_to_host(raddr), 4);
    } else return 0;
  }
  void pmem_write(int waddr, char wmask, int wdata){
    waddr = waddr & ~0x3u;
    if (in_pmem(waddr)) {
      if (wmask == 0xF) {
        IFDEF(CONFIG_MTRACE, display_pwrite(waddr, 4, wdata));
        host_write(guest_to_host(waddr), 4, wdata);
      } else {
      for(int i = 0; i < 4; i++)
        if (wmask & (1 << i)) {
          IFDEF(CONFIG_MTRACE, display_pwrite(waddr + i, 4, (waddr >> (i * 8)) & 0xff));
          host_write(guest_to_host(waddr + i), 4, (waddr >> (i * 8)) & 0xff);
        }
      }
    }
  }
  void diff(int pc, int npc, int inst, int* gpr, int* csr) {
    cpu.pc = pc;
    cpu.npc = npc;
    cpu.inst = inst;
    cpu.csr.mstatus = csr[0];
    cpu.csr.mepc = csr[1];
    cpu.csr.mcause = csr[2];
    cpu.csr.mtvec = csr[3];
    for (int i = 0; i < 32; i++)
      cpu.gpr[i] = gpr[i];
  }
}

static vluint64_t sim_time = 0;
static void tick(){
  // ======== 下降沿 ========
  top->clock = 0;
  top->eval();
  tfp->dump(sim_time++);
  // ======== 上升沿 ========
  top->clock = 1;
  top->eval();
  tfp->dump(sim_time++);
  // ======== 刷新 ========
  tfp->flush();
}

static void reset(){
  // printf("[MEMU] Resetting ...\n");
  top->reset = 1;
  tick();
  top->reset = 0;
}

void exit(void) {
  tfp->close();
  delete tfp;
  delete top;
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
    // 复位
    reset();
  }
  void rtl_reset() {
    reset();
  }
  void rtl_step() {
    tick();
  }
  void rtl_exit() {
    exit();
  }
}
