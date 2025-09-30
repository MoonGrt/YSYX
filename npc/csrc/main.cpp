#include "VDual_Control_Switch.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);

    // 启用波形
    Verilated::traceEverOn(true);
    VDual_Control_Switch *top = new VDual_Control_Switch;
    VerilatedVcdC *tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("wave.vcd");

    srand(time(NULL));
    vluint64_t main_time = 0;

    for (int i = 0; i < 20; i++) {
        int a = rand() & 1;
        int b = rand() & 1;

        top->a = a;
        top->b = b;

        top->eval();
        tfp->dump(main_time++);

        printf("a = %d, b = %d, f = %d\n", a, b, top->f);
        assert(top->f == (a ^ b));
    }

    tfp->close();
    delete tfp;
    delete top;
    return 0;
}
