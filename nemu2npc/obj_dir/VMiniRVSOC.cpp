// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VMiniRVSOC__pch.h"

//============================================================
// Constructors

VMiniRVSOC::VMiniRVSOC(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VMiniRVSOC__Syms(contextp(), _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , reset{vlSymsp->TOP.reset}
    , valid{vlSymsp->TOP.valid}
    , wmask{vlSymsp->TOP.wmask}
    , wen{vlSymsp->TOP.wen}
    , io_pc{vlSymsp->TOP.io_pc}
    , io_inst{vlSymsp->TOP.io_inst}
    , raddr{vlSymsp->TOP.raddr}
    , waddr{vlSymsp->TOP.waddr}
    , wdata{vlSymsp->TOP.wdata}
    , rdata{vlSymsp->TOP.rdata}
    , __PVT____024unit{vlSymsp->TOP.__PVT____024unit}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VMiniRVSOC::VMiniRVSOC(const char* _vcname__)
    : VMiniRVSOC(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VMiniRVSOC::~VMiniRVSOC() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VMiniRVSOC___024root___eval_debug_assertions(VMiniRVSOC___024root* vlSelf);
#endif  // VL_DEBUG
void VMiniRVSOC___024root___eval_static(VMiniRVSOC___024root* vlSelf);
void VMiniRVSOC___024root___eval_initial(VMiniRVSOC___024root* vlSelf);
void VMiniRVSOC___024root___eval_settle(VMiniRVSOC___024root* vlSelf);
void VMiniRVSOC___024root___eval(VMiniRVSOC___024root* vlSelf);

void VMiniRVSOC::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VMiniRVSOC::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VMiniRVSOC___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VMiniRVSOC___024root___eval_static(&(vlSymsp->TOP));
        VMiniRVSOC___024root___eval_initial(&(vlSymsp->TOP));
        VMiniRVSOC___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VMiniRVSOC___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VMiniRVSOC::eventsPending() { return false; }

uint64_t VMiniRVSOC::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VMiniRVSOC::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VMiniRVSOC___024root___eval_final(VMiniRVSOC___024root* vlSelf);

VL_ATTR_COLD void VMiniRVSOC::final() {
    VMiniRVSOC___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VMiniRVSOC::hierName() const { return vlSymsp->name(); }
const char* VMiniRVSOC::modelName() const { return "VMiniRVSOC"; }
unsigned VMiniRVSOC::threads() const { return 1; }
void VMiniRVSOC::prepareClone() const { contextp()->prepareClone(); }
void VMiniRVSOC::atClone() const {
    contextp()->threadPoolpOnClone();
}
