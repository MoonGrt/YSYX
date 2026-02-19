#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VMiniRVSOC.h"
#include <iostream>

#define DEBUG

typedef uint32_t word_t;
typedef uint32_t paddr_t;
#define CONFIG_MBASE 0x80000000L
#define CONFIG_MSIZE 0x8000000L
constexpr int MEM_SIZE=1024*1024*128;

uint8_t mem[MEM_SIZE];
static inline bool in_pmem(paddr_t addr){
  return addr - CONFIG_MBASE <= CONFIG_MSIZE && addr >= CONFIG_MBASE;
}
uint8_t* guest_to_host(paddr_t paddr){   
  if (in_pmem(paddr)) return mem + paddr - CONFIG_MBASE;
  else return NULL;
}
word_t paddr_read(paddr_t addr, int len){
  if (addr < CONFIG_MBASE || addr >= CONFIG_MBASE + MEM_SIZE) return 0;
  word_t result = 0;
  switch (len){
    case 1: result= *guest_to_host(addr); break;
    case 2: result= *(uint16_t *)guest_to_host(addr); break;
    case 4: result= *(uint32_t *)guest_to_host(addr); break;
    default: return 0;
  }
#ifdef DEBUG
  printf("paddr_read: addr=0x%08x, len=%d, data=0x%08x\n", addr, len, result);
#endif
  return result;
}
void paddr_write(paddr_t addr, int wmask, word_t data){
#ifdef DEBUG
  printf("paddr_write: addr=0x%08x, wmask=0x%02x, data=0x%08x\n", addr, wmask, data);
#endif
  if (addr < CONFIG_MBASE || addr >= CONFIG_MBASE + MEM_SIZE) return;
  for(int i = 0; i < 4; i++)
    if(wmask & (1 << i)) *guest_to_host(addr + i) = (data >> (i * 8)) & 0xff;
}

extern "C" {
  bool is_ebreak;
  uint8_t ebreak_code;
  void ebreak(uint8_t code){
    is_ebreak=true;
    ebreak_code=code;
  }
  int pmem_read(int raddr){
    raddr = raddr & ~0x3u;
    word_t data= paddr_read(raddr, 4);
    return data;
  }
  void pmem_write(int waddr, int wdata, char wmask){
    paddr_write(waddr, wmask, wdata);
  }
}



uint8_t *rom = NULL;
uint8_t *ram = NULL;
#define ROM_BASE 0x30000000L
#define ROM_SIZE 0x1000000L
#define RAM_BASE 0x80000000L
#define RAM_SIZE 0x20000000L
extern "C" void init_rom(){
  rom = (uint8_t *)malloc(ROM_SIZE);
  assert(rom);
  memset(rom, 0, ROM_SIZE);
};
extern "C" void init_ram() {
  ram = (uint8_t *)malloc(RAM_SIZE);
  assert(ram);
  memset(ram, 0, RAM_SIZE);
};
static const uint32_t img [] = {
  0x00000297,  // auipc t0,0
  0x00500513,  // li a0, 5
  0x00300593,  // li a1, 3
  0x00b50633,  // add a2, a0, a1
  0x40b506b3,  // sub a3, a0, a1
  0x00b51733,  // and a4, a0, a1
  0x00b567b3,  // or  a5, a0, a1
  0x00b54733,  // xor a6, a0, a1
  0x00028823,  // sb  zero, 16(t0)
  0x0102c503,  // lbu a0, 16(t0)
  0x00100073,  // ebreak
  0xdeadbeef,  // some data
};

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
    puts("Format: <exe> +/-trace <image>");
    return 1;
  }
  Verilated::commandArgs(argc, argv);
  Verilated::mkdir("logs");

  int img_size = 0;
  init_ram();
  init_rom();
  if (argc >= 3) {
    // 使用用户提供的 image 文件
    FILE *img_file = fopen(argv[2], "rb");
    if (img_file == nullptr) {
      puts("Open executable image failed");
      return 1;
    }
    img_size = fread(rom, 1, ROM_SIZE, img_file);
    fclose(img_file);
    printf("[NPC] Load image from file, size = %d bytes\n", img_size);
  } else {
    // 使用默认内置 image
    img_size = sizeof(img);
    memcpy(rom, img, img_size);
    printf("[NPC] Load default image, size = %d bytes\n", img_size);
  }


  // 实例化顶层模块
  VMiniRVSOC *top = new VMiniRVSOC;
  // 创建 build 目录（如果不存在）
  Verilated::mkdir("build");
  // 创建 VCD 波形对象
  Verilated::traceEverOn(true);  // 必须先打开 trace
  VerilatedVcdC *tfp = new VerilatedVcdC;
  top->trace(tfp, 99);  // 99 是 trace depth
  tfp->open("build/wave.vcd");

  // ===== 复位 =====
  printf("Resetting...\n");
  top->reset = 1;
  tick(top, tfp);
  top->reset = 0;
  // 主仿真
  std::cout << "[NPC] Simulation start" << std::endl;
  // while (!Verilated::gotFinish()) tick(top, tfp);
  for (int i = 0; i < 50; i++) tick(top, tfp);
  // 结束
  std::cout << "[NPC] Simulation finished at time = " << sim_time << std::endl;
  tfp->close();
  delete tfp;
  delete top;
  return 0;
}
