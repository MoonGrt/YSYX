// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VMiniRVSOC.h for the primary calling header

#include "VMiniRVSOC__pch.h"

void VMiniRVSOC___024unit___ctor_var_reset(VMiniRVSOC___024unit* vlSelf);

void VMiniRVSOC___024unit::ctor(VMiniRVSOC__Syms* symsp, const char* namep) {
    vlSymsp = symsp;
    vlNamep = strdup(Verilated::catName(vlSymsp->name(), namep));
    // Reset structure values
    VMiniRVSOC___024unit___ctor_var_reset(this);
}

void VMiniRVSOC___024unit::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

void VMiniRVSOC___024unit::dtor() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
