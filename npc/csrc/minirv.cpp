#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VMiniRVSOC.h"
#include <iostream>

// #define DEBUG

// 实例化顶层模块
VMiniRVSOC *top = new VMiniRVSOC;
VerilatedVcdC *tfp = new VerilatedVcdC;

typedef uint32_t word_t;
typedef uint32_t paddr_t;
uint8_t *mem = NULL;
#define MEM_BASE 0x80000000L
#define MEM_SIZE 0x01000000L
extern "C" void init_mem(){
  mem = (uint8_t *)malloc(MEM_SIZE);
  assert(mem);
  memset(mem, 0, MEM_SIZE);
};
static const uint32_t img [] = {
  0x00500513,  // 0x00 addi a0, zero, 5; a0 = 5
  0x00300593,  // 0x04 addi a1, zero, 3; a1 = 3
  0x00b50633,  // 0x08 add a2, a0, a1  ; a2 = a0 + a1
  0x00028823,  // 0x0c sb  zero, 16(t0); 存储 0 到 t0+16
  0x0102c503,  // 0x10 lbu a0, 16(t0)  ; 从 t0+16 读一个字节
  0x00100073,  // 0x04 ebreak
  0xdeadbeef,  // 0x08 deadbeef
};

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





static vluint64_t sim_time = 0;
static void tick(VMiniRVSOC* top, VerilatedVcdC* tfp){
  // ======== 上升沿 ========
  top->clock = 0;
  top->eval();
  tfp->dump(sim_time++);
  // ======== 下降沿 ========
  top->clock = 1;
  top->eval();
  tfp->dump(sim_time++);
}

int main(int argc, char **argv){
  if (argc < 1){
    puts("[NPC] Format: <exe> +/-trace <image>");
    return 1;
  }
  Verilated::commandArgs(argc, argv);
  Verilated::mkdir("logs");

  int img_size = 0;
  init_mem();
  if (argc >= 3) {
    // 使用用户提供的 image 文件
    FILE *img_file = fopen(argv[2], "rb");
    if (img_file == nullptr) {
      puts("[NPC] Open executable image failed");
      return 1;
    }
    img_size = fread(mem, 1, MEM_SIZE, img_file);
    fclose(img_file);
    printf("[NPC] Load image from file, size = %d bytes\n", img_size);
  } else {
    // 使用默认内置 image
    img_size = sizeof(img);
    memcpy(mem, img, img_size);
    printf("[NPC] Load default image, size = %d bytes\n", img_size);
  }


  // 创建 build 目录（如果不存在）
  Verilated::mkdir("build");
  // 创建 VCD 波形对象
  Verilated::traceEverOn(true);  // 必须先打开 trace
  top->trace(tfp, 99);  // 99 是 trace depth
  tfp->open("build/wave.vcd");

  // ===== 复位 =====
  printf("[NPC] Resetting...\n");
  top->reset = 1;
  tick(top, tfp);
  top->reset = 0;
  // 主仿真
  std::cout << "[NPC] Simulation start" << std::endl;
  // while (!Verilated::gotFinish()){
  for (int i = 0; i < 100000 && !Verilated::gotFinish(); i++) {
    tick(top, tfp);
    if (is_ebreak) {
      std::cout << "[NPC] EBREAK hit, exiting simulation.\n";
      break;
    }
  }
  // 结束
  tfp->close();
  delete tfp;
  delete top;
  if (is_ebreak) {
    std::cout << "[NPC] Simulation finished at time = " << sim_time 
              << ", \33[1;32mwith EBREAK hit\33[0m" << std::endl;
    return 0;
  } else {
    std::cout << "[NPC] Simulation finished at time = " << sim_time 
              << ", \33[1;31mwithout EBREAK hit\33[0m" << std::endl;
    return 1;
  }
}
