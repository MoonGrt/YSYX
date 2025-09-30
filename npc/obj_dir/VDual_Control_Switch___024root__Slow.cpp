// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VDual_Control_Switch.h for the primary calling header

#include "verilated.h"

#include "VDual_Control_Switch__Syms.h"
#include "VDual_Control_Switch___024root.h"

void VDual_Control_Switch___024root___ctor_var_reset(VDual_Control_Switch___024root* vlSelf);

VDual_Control_Switch___024root::VDual_Control_Switch___024root(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    VDual_Control_Switch___024root___ctor_var_reset(this);
}

void VDual_Control_Switch___024root::__Vconfigure(VDual_Control_Switch__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

VDual_Control_Switch___024root::~VDual_Control_Switch___024root() {
}
