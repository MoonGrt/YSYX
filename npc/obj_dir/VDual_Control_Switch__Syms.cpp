// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "VDual_Control_Switch__Syms.h"
#include "VDual_Control_Switch.h"
#include "VDual_Control_Switch___024root.h"

// FUNCTIONS
VDual_Control_Switch__Syms::~VDual_Control_Switch__Syms()
{
}

VDual_Control_Switch__Syms::VDual_Control_Switch__Syms(VerilatedContext* contextp, const char* namep,VDual_Control_Switch* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP(namep)
{
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-12);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(this, true);
}
