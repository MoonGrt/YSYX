#include <verilated.h>
#include <verilated_vcd_c.h>
#include "VMiniRVSOC.h"

VMiniRVSOC *top = new VMiniRVSOC;
VerilatedVcdC *tfp = new VerilatedVcdC;

extern "C" {
  void rtl_init() {
    Verilated::commandArgs(argc, argv);
    Verilated::mkdir("logs");
  }
  void rtl_step() {
    top->clock = 0; top->eval();
    top->clock = 1; top->eval();
  }
}
