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
  void etrace(uint32_t epc, uint32_t ecode);

  #define EBREAK_CODE    0
  #define ECALL_CODE     1
  #define ZERO_INST_CODE 2
  #define UNIMPL_CODE    3
  void exception(uint8_t code) {
    switch (code) {
      case EBREAK_CODE:
        printf("[MEMU] EBREAK exception\n");
        MEMUTRAP(cpu.pc, code);
        break;
      case ECALL_CODE:
        IFDEF(CONFIG_ETRACE, etrace(s->pc, 11));
        break;
      case ZERO_INST_CODE:
        printf("[MEMU] Zero instruction exception\n");
        INV(cpu.pc);
        break;
      case UNIMPL_CODE:
        printf("[MEMU] Unimplemented instruction exception\n");
        INV(cpu.pc);
        break;
      default:
        printf("[MEMU] Unknown exception code %d\n", code);
        break;
    }
    Verilated::gotFinish(true);
  }
  int dpi_paddr_read(int addr){
    if (addr == 0) return 0;
    if (likely(in_pmem(addr))) {
      word_t data = pmem_read(addr, 4);
      IFDEF(CONFIG_MTRACE, mtrace(false, addr, 4, data));
      return data;
    }
    IFDEF(CONFIG_DEVICE, return mmio_read(addr, 4));
    return 0;
  }
  void dpi_paddr_write(int addr, char mask, int data) {
    if (addr == 0) return;
    for (int i = 0; i < 4; i++) {
      if (mask & (1 << i)) {
        int byte_addr = addr + i;
        int byte_data = (data >> (i * 8)) & 0xFF;
        IFDEF(CONFIG_MTRACE, mtrace(true, byte_addr, 1, byte_data));
        if (likely(in_pmem(byte_addr))) pmem_write(byte_addr, 1, byte_data);
        else IFDEF(CONFIG_DEVICE, mmio_write(byte_addr, 1, byte_data));
      }
    }
  }
  void dpi_diffpc(int pc, int npc, int inst) {
    // Decode
    rtlDecode.pc = pc;
    rtlDecode.snpc = pc + 4;
    rtlDecode.dnpc = npc;
    rtlDecode.isa.inst = inst;
    // CPU_state
    cpu.pc = pc;
  }
  void dpi_diffgpr(int* gpr) {
    for (int i = 0; i < 32; i++)
      cpu.gpr[i] = gpr[i];
  }
  void dpi_diffcsr(int* csr) {
    cpu.csr.mstatus = csr[0];
    cpu.csr.mepc = csr[1];
    cpu.csr.mcause = csr[2];
    cpu.csr.mtvec = csr[3];
    cpu.csr.mcycle = csr[4];
    cpu.csr.mcycleh = csr[5];
    cpu.csr.mvendorid = csr[6];
    cpu.csr.marchid = csr[7];
  }
}

static vluint64_t sim_time = 0;
static void wave_tracer() {
  if (!wave_enable()) return;
#ifdef CONFIG_WAVE_VCD
  tfp->dump(sim_time++);
  tfp->flush();
#elif CONFIG_WAVE_FST
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
  tfp->close();
  delete tfp;
#endif
  delete top;
}

extern "C" {
  void rtl_init(int argc, char *argv[]) {
    // 初始化仿真对象
    Verilated::commandArgs(argc, argv);
    Verilated::mkdir("logs");
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
