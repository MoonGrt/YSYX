#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VMiniRVTOP.h"

#include <common.h>
#include <utils.h>
#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <memory/paddr.h>
#include <memory/host.h>
#include <device/mmio.h>
#include "../../utils/local-include/itrace.h"

VMiniRVTOP *top = new VMiniRVTOP;
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
  int dpi_paddr_read(int addr, char len){
    if (addr == 0) return 0;
    IFDEF(CONFIG_MTRACE, display_pread(addr, len));
    if (likely(in_pmem(addr))) return pmem_read(addr, len);
    IFDEF(CONFIG_DEVICE, return mmio_read(addr, len));
    return 0;
  }
  void dpi_paddr_write(int addr, char len, int data){
    IFDEF(CONFIG_MTRACE, display_pwrite(addr, len, data));
    if (likely(in_pmem(addr))) { pmem_write(addr, len, data); return; }
    IFDEF(CONFIG_DEVICE, mmio_write(addr, len, data); return);
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
