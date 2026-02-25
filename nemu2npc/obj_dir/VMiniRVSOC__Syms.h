// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VMINIRVSOC__SYMS_H_
#define VERILATED_VMINIRVSOC__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "VMiniRVSOC.h"

// INCLUDE MODULE CLASSES
#include "VMiniRVSOC___024root.h"
#include "VMiniRVSOC___024unit.h"

// DPI TYPES for DPI Export callbacks (Internal use)

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) VMiniRVSOC__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    VMiniRVSOC* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    VMiniRVSOC___024root           TOP;
    VMiniRVSOC___024unit           TOP____024unit;

    // CONSTRUCTORS
    VMiniRVSOC__Syms(VerilatedContext* contextp, const char* namep, VMiniRVSOC* modelp);
    ~VMiniRVSOC__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
