#include <verilated.h>
#include "VMiniRVSOC.h"
#include <iostream>

typedef uint32_t word_t;
typedef uint32_t paddr_t;
#define CONFIG_MBASE 0x80000000L
#define CONFIG_MSIZE 0x8000000L
constexpr int MEM_SIZE=1024*1024*128;
uint8_t mem[MEM_SIZE];
static inline bool in_pmem(paddr_t addr) {
  return addr - CONFIG_MBASE <= CONFIG_MSIZE && addr >= CONFIG_MBASE;
}
uint8_t* guest_to_host(paddr_t paddr) {   
  if (in_pmem(paddr)) {
    return mem + paddr - CONFIG_MBASE;
  }
  else {
    return NULL;
  }
}
word_t paddr_read(paddr_t addr, int len)
{
    if (addr < CONFIG_MBASE || addr >= CONFIG_MBASE + MEM_SIZE) return 0;
    word_t result = 0;
    switch (len) {
        case 1: result= *guest_to_host(addr); break;
        case 2: result= *(uint16_t *)guest_to_host(addr); break;
        case 4: result= *(uint32_t *)guest_to_host(addr); break;
        default: return 0;
    }
  return result;
}
void paddr_write(paddr_t addr, int wmask, word_t data)
{
    if (addr < CONFIG_MBASE || addr >= CONFIG_MBASE + MEM_SIZE) return;
    for(int i = 0; i < 4; i++) {
        if(wmask & (1 << i)) {
            *guest_to_host(addr + i) = (data >> (i * 8)) & 0xff;
        }
    }
}

static uint64_t time_tmp=0;
extern "C" {
    bool is_ebreak;
    uint8_t ebreak_code;
    void ebreak(uint8_t code)
    {
        is_ebreak=true;
        ebreak_code=code;
    }
    int rom_rdpi(int addr) {
        word_t ret=0;
        bool mmio=false;
        if (mmio) {
            return ret;
        }
        addr = addr & ~0x3u;
        word_t data= paddr_read(addr, 4);
        return data;
    }
    int ram_rdpi(int raddr) {
        word_t ret=0;
        bool mmio=false;
        if (mmio) {
            return ret;
        }
        raddr = raddr & ~0x3u;
        word_t data= paddr_read(raddr, 4);
        return data;
    }
    void ram_wdpi(int waddr, int wdata, char wmask) {
        bool mmio=false;
        paddr_write(waddr,wmask, wdata);
    }
}


vluint64_t main_time = 0;

// Verilator 要求的时间函数
double sc_time_stamp() {
    return main_time;
}

int main(int argc, char **argv) {
    if (argc < 1) {
        puts("Format: <x.exe> +/-trace");
        return 1;
    }
    Verilated::commandArgs(argc, argv);
    Verilated::mkdir("logs");

    // 实例化顶层模块
    VMiniRVSOC *top = new VMiniRVSOC;

    // 可选：开启波形
    // Verilated::traceEverOn(true);

    std::cout << "[NPC] Simulation start" << std::endl;

    while (!Verilated::gotFinish()) {
        // ======== 上升沿 ========
        top->clock = 0;
        top->eval();
        main_time++;
        // ======== 下降沿 ========
        top->clock = 1;
        top->eval();
        main_time++;
    }

    std::cout << "[NPC] Simulation finished at time = "
              << main_time << std::endl;

    delete top;
    return 0;
}
