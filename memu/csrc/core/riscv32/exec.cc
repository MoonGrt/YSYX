#include <common.h>
#include <utils.h>
#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <memory/paddr.h>
#include <memory/host.h>
#include <device/mmio.h>

#ifdef CONFIG_CORE_minirv
#include "VMiniRVTOP.h"
VMiniRVTOP *top = new VMiniRVTOP;
#elif  CONFIG_CORE_riscv32e
#include "VRiscv32ETOP.h"
VRiscv32ETOP *top = new VRiscv32ETOP;
#elif  CONFIG_CORE_riscv32
#elif  CONFIG_CORE_riscv64
#endif

#ifdef CONFIG_WAVE
#include <verilated.h>
#ifdef CONFIG_WAVE_VCD
#include <verilated_vcd_c.h>
VerilatedVcdC *tfp = new VerilatedVcdC;
#elif  CONFIG_WAVE_FST
#include <verilated_fst_c.h>
VerilatedFstC *tfp = new VerilatedFstC;
#endif
#endif

extern uint64_t g_nr_guest_inst;
bool wave_enable() {
  return MUXDEF(CONFIG_WAVE, (g_nr_guest_inst >= CONFIG_WAVE_START) &&
         (g_nr_guest_inst < CONFIG_WAVE_END), false);
}

Decode rtlDecode;

extern "C" {
  void mtrace(bool is_write, paddr_t addr, int len, word_t data);

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
    if (likely(in_pmem(addr))) {
      word_t data = pmem_read(addr, len);
      IFDEF(CONFIG_MTRACE, mtrace(false, addr, len, data));
      return data;
    }
    IFDEF(CONFIG_DEVICE, return mmio_read(addr, len));
    return 0;
  }
  void dpi_paddr_write(int addr, char len, int data){
    if (addr == 0) return;
    IFDEF(CONFIG_MTRACE, mtrace(true, addr, len, data));
    if (likely(in_pmem(addr))) { pmem_write(addr, len, data); return; }
    IFDEF(CONFIG_DEVICE, mmio_write(addr, len, data); return);
  }
  void dpi_diff(int pc, int npc, int inst, int* gpr, int* csr) {
    // Decode
    rtlDecode.pc = pc;
    rtlDecode.snpc = pc + 4;
    rtlDecode.dnpc = npc;
    rtlDecode.isa.inst = inst;
    // CPU_state
    cpu.pc = pc;
    cpu.csr.mstatus = csr[0];
    cpu.csr.mepc = csr[1];
    cpu.csr.mcause = csr[2];
    cpu.csr.mtvec = csr[3];
    cpu.csr.mcycle = csr[4];
    cpu.csr.mcycleh = csr[5];
    cpu.csr.mvendorid = csr[6];
    cpu.csr.marchid = csr[7];
    for (int i = 0; i < 32; i++)
      cpu.gpr[i] = gpr[i];
  }
}

static vluint64_t sim_time = 0;
static void wave_tracer() {
  if (!wave_enable()) return;
#ifdef CONFIG_WAVE
  tfp->dump(sim_time++);
  tfp->flush();
#endif
}
static void tick(){
  // ======== 下降沿 ========
  top->clock = 0;
  top->eval();
#ifdef CONFIG_WAVE
  wave_tracer();
#endif
  // ======== 上升沿 ========
  top->clock = 1;
  top->eval();
#ifdef CONFIG_WAVE
  wave_tracer();
#endif
}

static void reset(){
  // printf("[MEMU] Resetting ...\n");
  top->reset = 1;
  tick();
  top->reset = 0;
}

void exit(void) {
#ifdef CONFIG_WAVE
  if (tfp) {
    tfp->close();
    delete tfp;
    tfp = nullptr;
  }
#endif
}

extern "C" {
  void rtl_init(int argc, char *argv[]) {
    // 初始化仿真对象
    Verilated::commandArgs(argc, argv);
    // 创建 build 目录（如果不存在）
    Verilated::mkdir("build");
#ifdef CONFIG_WAVE
    // 创建波形对象
    Verilated::traceEverOn(true);  // 必须先打开 trace
    top->trace(tfp, 99);  // 99 是 trace depth
    tfp->open("build/wave.vcd");
#endif
    // 复位
    reset();
  }
  void rtl_step() {
    tick();
  }
  void rtl_exit() {
    exit();
  }
}
