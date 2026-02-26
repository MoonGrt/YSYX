#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VMiniRVSOC.h"

#include <cpu/decode.h>
#include <memory/paddr.h>
#include <common.h>

extern "C" void set_nemu_state(int state, vaddr_t pc, int halt_ret);

Decode RTL_Decode;

// #define DEBUG

VMiniRVSOC *top = new VMiniRVSOC;
VerilatedVcdC *tfp = new VerilatedVcdC;

typedef uint32_t word_t;
typedef uint32_t paddr_t;

// #define MEM_BASE 0x80000000L
// #define MEM_SIZE 0x01000000L
// uint8_t *mem = NULL;
// void init_mem(){
//   mem = (uint8_t *)malloc(MEM_SIZE);
//   assert(mem);
//   memset(mem, 0, MEM_SIZE);
// };
// static const uint32_t img [] = {
//   0x00500513,  // 0x00 addi a0, zero, 5; a0 = 5
//   0x00300593,  // 0x04 addi a1, zero, 3; a1 = 3
//   0x00b50633,  // 0x08 add a2, a0, a1  ; a2 = a0 + a1
//   0x00028823,  // 0x0c sb  zero, 16(t0); 存储 0 到 t0+16
//   0x0102c503,  // 0x10 lbu a0, 16(t0)  ; 从 t0+16 读一个字节
//   0x00100073,  // 0x04 ebreak
//   0xdeadbeef,  // 0x08 deadbeef
// };
// static char *img_file = NULL;
// static void load_img(void) {
//   long img_size = 0;
//   if (img_file == NULL) {
//     // 使用默认内置 image
//     img_size = sizeof(img);
//     memcpy(mem, img, img_size);
//   } else {
//     // 使用用户提供的 image 文件
//     FILE *fp = fopen(img_file, "rb");
//     assert(fp);
//     img_size = fread(mem, 1, MEM_SIZE, fp);
//     fclose(fp);
//   }
// }

// static inline bool in_mem(paddr_t addr){
//   return addr - MEM_BASE <= MEM_SIZE && addr >= MEM_BASE;
// }
// uint8_t* guest_to_host(paddr_t paddr){
//   if (in_mem(paddr)) return mem + paddr - MEM_BASE;
//   else return NULL;
// }
// word_t paddr_read(paddr_t addr, int len){
//   uint8_t *host = guest_to_host(addr);
//   if (!host) return 0;
//   word_t result = 0;
//   switch (len) {
//     case 1: result = *host; break;
//     case 2: result = *(uint16_t *)host; break;
//     case 4: result = *(uint32_t *)host; break;
//     default: return 0;
//   }
// #ifdef DEBUG
//   printf("paddr_read:  addr=0x%08x,  len=%d,   data=0x%08x\n", addr, len, result);
// #endif
//   return result;
// }
// void paddr_write(paddr_t addr, int mask, word_t data){
// #ifdef DEBUG
//   printf("paddr_write: addr=0x%08x, mask=0x%x, data=0x%08x\n", addr, mask, data);
// #endif
//   if (addr < MEM_BASE || addr >= MEM_BASE + MEM_SIZE) return;
//   for(int i = 0; i < 4; i++)
//     if(mask & (1 << i)) *guest_to_host(addr + i) = (data >> (i * 8)) & 0xff;
// }

extern "C" {
  #define EBREAK_CODE    0
  #define ZERO_INST_CODE 1
  #define OTHER_E_CODE   2
  #define UNIMPL_CODE    3
  // bool is_ebreak;
  // void ebreak(uint8_t code) {
  //   // 异常信息映射：颜色 + 消息
  //   is_ebreak = (code == EBREAK_CODE);
  //   struct {
  //     const char* color;
  //     const char* msg;
  //   } exc_info[] = {
  //     [EBREAK_CODE]  = {"\33[1;32m", "EBREAK: HIT GOOD TRAP"},
  //     [ZERO_INST_CODE]= {"\33[1;34m", "ALL ZERO INSTRUCTION"},
  //     [OTHER_E_CODE] = {"\33[1;33m", "E-INSTRUCTION EXCEPTION"},
  //     [UNIMPL_CODE]  = {"\33[1;31m", "UNIMPLEMENTED INSTRUCTION"},
  //   };
  //   // 默认异常（安全）
  //   const char* color = "\33[1;31m";
  //   const char* msg   = "UNKNOWN EXCEPTION";
  //   if (code <= ZERO_INST_CODE) {
  //     color = exc_info[code].color;
  //     msg   = exc_info[code].msg;
  //   }
  //   // 统一打印
  //   printf("[MEMU] %s%s\33[0m at pc = 0x%08x -> ", color, msg, top->io_pc);
  //   printf("\33[1;35mInstruction\33[0m = 0x%08x\n", top->io_inst);
  //   // 停止仿真
  //   Verilated::gotFinish(true);
  //   // 停止MEMU
  //   set_nemu_state(MEMU_END, top->io_pc, 0);
  // }
  void ebreak(uint8_t code) {
    // 停止仿真
    Verilated::gotFinish(true);
    // 停止MEMU
    set_nemu_state(MEMU_END, top->io_pc, 0);
  }
  int pmem_read(int raddr){
    raddr = raddr & ~0x3u;
    word_t data= paddr_read(raddr, 4);
#ifdef DEBUG
    printf("paddr_read:  addr=0x%08x,   data=0x%08x\n", raddr, data);
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
  void rtl_step() {
    tick();
  }
  void rtl_exit() {
    exit();
  }
}
