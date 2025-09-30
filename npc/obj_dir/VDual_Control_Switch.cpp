// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VDual_Control_Switch.h"
#include "VDual_Control_Switch__Syms.h"

//============================================================
// Constructors

VDual_Control_Switch::VDual_Control_Switch(VerilatedContext* _vcontextp__, const char* _vcname__)
    : vlSymsp{new VDual_Control_Switch__Syms(_vcontextp__, _vcname__, this)}
    , a{vlSymsp->TOP.a}
    , b{vlSymsp->TOP.b}
    , f{vlSymsp->TOP.f}
    , rootp{&(vlSymsp->TOP)}
{
}

VDual_Control_Switch::VDual_Control_Switch(const char* _vcname__)
    : VDual_Control_Switch(nullptr, _vcname__)
{
}

//============================================================
// Destructor

VDual_Control_Switch::~VDual_Control_Switch() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void VDual_Control_Switch___024root___eval_initial(VDual_Control_Switch___024root* vlSelf);
void VDual_Control_Switch___024root___eval_settle(VDual_Control_Switch___024root* vlSelf);
void VDual_Control_Switch___024root___eval(VDual_Control_Switch___024root* vlSelf);
#ifdef VL_DEBUG
void VDual_Control_Switch___024root___eval_debug_assertions(VDual_Control_Switch___024root* vlSelf);
#endif  // VL_DEBUG
void VDual_Control_Switch___024root___final(VDual_Control_Switch___024root* vlSelf);

static void _eval_initial_loop(VDual_Control_Switch__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    VDual_Control_Switch___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        VDual_Control_Switch___024root___eval_settle(&(vlSymsp->TOP));
        VDual_Control_Switch___024root___eval(&(vlSymsp->TOP));
    } while (0);
}

void VDual_Control_Switch::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VDual_Control_Switch::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VDual_Control_Switch___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        VDual_Control_Switch___024root___eval(&(vlSymsp->TOP));
    } while (0);
    // Evaluate cleanup
}

//============================================================
// Utilities

VerilatedContext* VDual_Control_Switch::contextp() const {
    return vlSymsp->_vm_contextp__;
}

const char* VDual_Control_Switch::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

VL_ATTR_COLD void VDual_Control_Switch::final() {
    VDual_Control_Switch___024root___final(&(vlSymsp->TOP));
}
