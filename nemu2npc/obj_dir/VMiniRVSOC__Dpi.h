// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#ifndef VERILATED_VMINIRVSOC__DPI_H_
#define VERILATED_VMINIRVSOC__DPI_H_  // guard

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI IMPORTS
    // DPI import at /home/moon/ysyx/ysyx/nemu2npc/vsrc/EBreak.v:1:30
    extern void ebreak(char code);
    // DPI import at /home/moon/ysyx/ysyx/nemu2npc/vsrc/PMem.v:1:30
    extern int pmem_read(int raddr);
    // DPI import at /home/moon/ysyx/ysyx/nemu2npc/vsrc/PMem.v:2:30
    extern void pmem_write(int waddr, char wmask, int wdata);

#ifdef __cplusplus
}
#endif

#endif  // guard
