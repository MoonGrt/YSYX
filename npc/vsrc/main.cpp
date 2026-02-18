#include <verilated.h>
#include "VMiniRVSOC.h"
#include <iostream>

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
