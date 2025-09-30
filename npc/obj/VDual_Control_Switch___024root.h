// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VDual_Control_Switch.h for the primary calling header

#ifndef VERILATED_VDUAL_CONTROL_SWITCH___024ROOT_H_
#define VERILATED_VDUAL_CONTROL_SWITCH___024ROOT_H_  // guard

#include "verilated.h"

class VDual_Control_Switch__Syms;
VL_MODULE(VDual_Control_Switch___024root) {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(a,0,0);
    VL_IN8(b,0,0);
    VL_OUT8(f,0,0);

    // INTERNAL VARIABLES
    VDual_Control_Switch__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
    VDual_Control_Switch___024root(const char* name);
    ~VDual_Control_Switch___024root();
    VL_UNCOPYABLE(VDual_Control_Switch___024root);

    // INTERNAL METHODS
    void __Vconfigure(VDual_Control_Switch__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
