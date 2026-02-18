// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VMiniRVSOC.h for the primary calling header

#ifndef VERILATED_VMINIRVSOC___024UNIT_H_
#define VERILATED_VMINIRVSOC___024UNIT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"


class VMiniRVSOC__Syms;

class alignas(VL_CACHE_LINE_BYTES) VMiniRVSOC___024unit final {
  public:

    // INTERNAL VARIABLES
    VMiniRVSOC__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    VMiniRVSOC___024unit() = default;
    ~VMiniRVSOC___024unit() = default;
    void ctor(VMiniRVSOC__Syms* symsp, const char* namep);
    void dtor();
    VL_UNCOPYABLE(VMiniRVSOC___024unit);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
};


#endif  // guard
