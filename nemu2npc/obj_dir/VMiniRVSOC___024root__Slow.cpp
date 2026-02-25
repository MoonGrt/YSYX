// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VMiniRVSOC.h for the primary calling header

#include "VMiniRVSOC__pch.h"

void VMiniRVSOC___024root___ctor_var_reset(VMiniRVSOC___024root* vlSelf);

VMiniRVSOC___024root::VMiniRVSOC___024root(VMiniRVSOC__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    VMiniRVSOC___024root___ctor_var_reset(this);
}

void VMiniRVSOC___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

VMiniRVSOC___024root::~VMiniRVSOC___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
