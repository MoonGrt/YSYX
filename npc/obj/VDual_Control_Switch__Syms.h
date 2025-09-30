// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VDUAL_CONTROL_SWITCH__SYMS_H_
#define VERILATED_VDUAL_CONTROL_SWITCH__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VDual_Control_Switch.h"

// INCLUDE MODULE CLASSES
#include "VDual_Control_Switch___024root.h"

// SYMS CLASS (contains all model state)
class VDual_Control_Switch__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VDual_Control_Switch* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VDual_Control_Switch___024root TOP;

    // CONSTRUCTORS
    VDual_Control_Switch__Syms(VerilatedContext* contextp, const char* namep, VDual_Control_Switch* modelp);
    ~VDual_Control_Switch__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
