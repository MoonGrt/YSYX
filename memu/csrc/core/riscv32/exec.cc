#include <common.h>
#include <utils.h>
#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <cpu/difftest.h>
#include <memory/paddr.h>
#include <memory/host.h>
#include <device/mmio.h>

#ifdef CONFIG_CORE_minirv
#include "VMiniRVTOP.h"
VMiniRVTOP *top = new VMiniRVTOP;
#elif  CONFIG_CORE_riscv32e
#include "VRiscv32ETOP.h"
VRiscv32ETOP *top = new VRiscv32ETOP;
#endif

#if defined(CONFIG_WAVE_ABSOLUTE) || defined(CONFIG_WAVE_RELATIVE)

extern uint64_t g_nr_guest_inst;
#include <verilated.h>
#if defined(CONFIG_WAVE_VCD)
#include <verilated_vcd_c.h>
VerilatedVcdC *tfp;
#else
#include <verilated_fst_c.h>
VerilatedFstC *tfp;
#endif

#endif

bool wave_enable() {
#ifdef CONFIG_WAVE_ABSOLUTE
  return MUXDEF(CONFIG_WAVE_ABSOLUTE, (g_nr_guest_inst >= CONFIG_WAVE_ABS_START) &&
    (g_nr_guest_inst < CONFIG_WAVE_ABS_END), false);
#else
  return false;
#endif
}

#ifdef CONFIG_WAVE_RELATIVE
#include <utils.h>
#include <lightsss.h>
LightSSS *lightsss = new LightSSS;
bool have_initial_fork = false;
#endif

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
        printf("%s\n", ANSI_FMT("[MEMU] EBREAK exception", ANSI_FG_GREEN));
        MEMUTRAP(cpu.pc, code);
        break;
      case ECALL_CODE:
        IFDEF(CONFIG_ETRACE, etrace(decode.pc, 11));
        break;
      case ZERO_INST_CODE:
        printf("%s\n", ANSI_FMT("[MEMU] Zero instruction exception", ANSI_FG_RED));
        INV(cpu.pc);
        break;
      case UNIMPL_CODE:
        printf("%s\n", ANSI_FMT("[MEMU] Unimplemented instruction exception", ANSI_FG_RED));
        INV(cpu.pc);
        break;
      default:
        printf("%s %d\n", ANSI_FMT("[MEMU] Unknown exception code", ANSI_FG_RED), code);
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
  void dpi_diffen() {
    // difftest_step();
  }
  void dpi_diffpc(int pc, int npc, int inst) {
    // printf("pc: %x, npc: %x, inst: %08x\n", pc, npc, inst);
    // Decode
    decode.pc = pc;
    decode.snpc = pc + 4;
    decode.dnpc = npc;
    decode.isa.inst = inst;
    // CPU_state
    cpu.pc = pc;
    // reference step
    if (pc != 0) IFDEF(CONFIG_DIFFTEST, difftest_step());
  }
  void dpi_diffgpr(int* gpr) {
    // printf("dpi_diffgpr\n");
    for (int i = 0; i < 32; i++)
      cpu.gpr[i] = gpr[i];
  }
  void dpi_diffcsr(int* csr) {
    // printf("dpi_diffcsr\n");
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

void wave_init() {
#if defined(CONFIG_WAVE_ABSOLUTE) || defined(CONFIG_WAVE_RELATIVE)
  Verilated::traceEverOn(true);
#if defined(CONFIG_WAVE_VCD)
  tfp = new VerilatedVcdC;
#else
  tfp = new VerilatedFstC;
#endif
  top->trace(tfp, 99);  // 99 是 trace depth
  tfp->open("build/wave.vcd");
  // const char* path = getenv("WAVE_FILE");
  // tfp->open(path ? path : "build/wave.vcd");
#endif
}

bool force_dump_wave = false;
uint32_t inst_last = 0;

static vluint64_t sim_time = 0;
static void wave_tracer() {
#if defined(CONFIG_WAVE_ABSOLUTE) || defined(CONFIG_WAVE_RELATIVE)
  if (wave_enable() | force_dump_wave) {
    tfp->dump(sim_time++);
    tfp->flush();
  }
#endif
}

#ifdef CONFIG_WAVE_RELATIVE
void fork_child_init() {
  FORK_PRINTF("the oldest checkpoint start to dump wave...\n")
  wave_init();
  force_dump_wave = true;
}
#endif

static void tick(){
  top->clock = 0;
  top->eval();
  wave_tracer();
  top->clock = 1;
  top->eval();
  wave_tracer();

#ifdef CONFIG_WAVE_RELATIVE
  if (lightsss->is_child() && g_nr_guest_inst != 0)
    if (g_nr_guest_inst == lightsss->get_end_cycles())
      FORK_PRINTF("checkpoint has reached the main process abort point: %lu\n", g_nr_guest_inst)
  if ((g_nr_guest_inst - inst_last == CONFIG_WAVE_REL_INTERVAL || !have_initial_fork) && !lightsss->is_child()) {
    if (!have_initial_fork) printf("%s\n", ANSI_FMT("[Lightsss] do_fork", ANSI_FG_GREEN));
    have_initial_fork = true;
    switch (lightsss->do_fork()) {
      case FORK_ERROR:
        printf("%s\n", ANSI_FMT("[Lightsss] error", ANSI_FG_RED));
        return;
      case FORK_CHILD:
        // printf("%s\n", ANSI_FMT("[Lightsss] fork_child_init", ANSI_FG_GREEN));
        fork_child_init();
      default: break;
    }
    inst_last = g_nr_guest_inst;
  }
#endif
}

static void reset(){
  top->reset = 1;
  tick();
  top->reset = 0;
}

void exit(void) {
  delete top;
#if defined(CONFIG_WAVE_ABSOLUTE) || defined(CONFIG_WAVE_RELATIVE)
  if (tfp) {
    tfp->close();
    delete tfp;
  }
#ifdef CONFIG_WAVE_RELATIVE
  if (!lightsss->is_child()) {  // parent process
    bool need_wakeup = 
      (memu_state.state == MEMU_ABORT) ||
      (memu_state.state == MEMU_END && memu_state.halt_ret != 0);
    if (need_wakeup) {
      printf(ANSI_FMT("\n\n[Lightsss] wakeup_child\n", ANSI_FG_GREEN));
      lightsss->wakeup_child(g_nr_guest_inst);
    } else {
      printf(ANSI_FMT("[Lightsss] do_clear\n", ANSI_FG_GREEN));
      lightsss->do_clear();
    }
    delete lightsss;
  } else {  // child process
    printf(ANSI_FMT("[Lightsss] do_clear\n", ANSI_FG_RED));
    lightsss->do_clear();
  }
#endif
#endif
}

#ifdef CONFIG_WAVE_RELATIVE
void signal_handler(int signum) {
  if(getpid()) {
    kill(getpid(), SIGKILL);
    waitpid(getpid(), NULL, 0);
  }
}
#endif

extern "C" {
  void rtl_init(int argc, char *argv[]) {
    Verilated::commandArgs(argc, argv);
    IFDEF(CONFIG_WAVE_ABSOLUTE, wave_init());
    IFDEF(CONFIG_WAVE_RELATIVE, signal(SIGINT, signal_handler));
    reset();
  }
  void rtl_reset() {
    reset();
  }
  #define CYCLE_NUM 2
  void rtl_step() {
    // for (int i = 0; i < CYCLE_NUM; i++)
      tick();
  }
  void rtl_exit() {
    exit();
  }
}
