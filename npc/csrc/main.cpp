#include "VDual_Control_Switch.h"
#include "verilated.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    VDual_Control_Switch *top = new VDual_Control_Switch;

    srand(time(NULL));

    for (int i = 0; i < 20; i++) {
        int a = rand() & 1;
        int b = rand() & 1;
        top->a = a;
        top->b = b;
        top->eval();
        printf("a = %d, b = %d, f = %d\n", a, b, top->f);
        assert(top->f == (a ^ b));
    }

    delete top;
    return 0;
}
