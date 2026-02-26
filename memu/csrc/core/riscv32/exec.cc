#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VMiniRVSOC.h"

#include <common.h>
#include <cpu/decode.h>
#include <memory/paddr.h>
#include <memory/host.h>
#include "../../utils/local-include/itrace.h"

// #define DEBUG

extern "C" void set_nemu_state(int state, vaddr_t pc, int halt_ret);
extern "C" void invalid_inst(vaddr_t thispc);

Decode RTL_Decode;

VMiniRVSOC *top = new VMiniRVSOC;
VerilatedVcdC *tfp = new VerilatedVcdC;

typedef uint32_t word_t;
typedef uint32_t paddr_t;

extern "C" {
  #define EBREAK_CODE    0
  #define ZERO_INST_CODE 1
  #define OTHER_E_CODE   2
  #define UNIMPL_CODE    3
  void ebreak(uint8_t code) {
    if (code == EBREAK_CODE)
      set_nemu_state(MEMU_END, top->io_pc, code);
    else
      invalid_inst(top->io_pc);
    // 停止仿真
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
    if (in_pmem(waddr))
      for(int i = 0; i < 4; i++)
        if(wmask & (1 << i)) {
          IFDEF(CONFIG_MTRACE, display_pwrite(waddr + i, 4, (waddr >> (i * 8)) & 0xff));
          host_write(guest_to_host(waddr + i), 4, (waddr >> (i * 8)) & 0xff);
        }
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
  RTL_Decode.pc = top->io_pc;
  RTL_Decode.snpc = top->io_snpc;
  RTL_Decode.dnpc = top->io_dnpc;
  RTL_Decode.isa.inst = top->io_inst;
}

static void reset(){
  printf("[MEMU] Resetting ...\n");
  top->reset = 1;
  tick();
  top->reset = 0;
  // printf("[MEMU] Resetting ...\n");
}

void exit(void) {
  tfp->close();
  delete tfp;
  delete top;
}

// #define PRINTARG
extern "C" {
  void rtl_init(int argc, char *argv[]) {
#ifdef PRINTARG
    printf("[MEMU] ARGC = %d\n", argc);
    for (int i = 0; i < argc; i++)
      printf("[MEMU] ARGV[%d] = '%s'\n", i, argv[i]);
#endif
    // 初始化仿真对象
    Verilated::commandArgs(argc, argv);
    Verilated::mkdir("logs");
    // 创建 build 目录（如果不存在）
    Verilated::mkdir("build");
    // 创建 VCD 波形对象
    Verilated::traceEverOn(true);  // 必须先打开 trace
    top->trace(tfp, 99);  // 99 是 trace depth
    tfp->open("build/wave.vcd");

    // /* Initialize memory. */
    // init_mem();
    // /* Load the image to memory.*/
    // load_img();

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
