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
    // DPI import at vsrc/ebreak.v:1:30
    extern void ebreak(char code);
    // DPI import at vsrc/minirv.v:2:30
    extern int ram_rdpi(int raddr);
    // DPI import at vsrc/minirv.v:3:30
    extern void ram_wdpi(int waddr, int wdata, char wmask);
    // DPI import at vsrc/minirv.v:1:30
    extern void rom_rdpi(int addr, int* data);

#ifdef __cplusplus
}
#endif

#endif  // guard
