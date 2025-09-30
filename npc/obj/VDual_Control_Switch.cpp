// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VDual_Control_Switch.h"
#include "VDual_Control_Switch__Syms.h"
#include "verilated_vcd_c.h"

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
    vlSymsp->__Vm_activity = true;
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
    vlSymsp->__Vm_activity = true;
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

//============================================================
// Trace configuration

void VDual_Control_Switch___024root__trace_init_top(VDual_Control_Switch___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    VDual_Control_Switch___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VDual_Control_Switch___024root*>(voidSelf);
    VDual_Control_Switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    VDual_Control_Switch___024root__trace_init_top(vlSelf, tracep);
    tracep->scopeEscape('.');
}

VL_ATTR_COLD void VDual_Control_Switch___024root__trace_register(VDual_Control_Switch___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void VDual_Control_Switch::trace(VerilatedVcdC* tfp, int levels, int options) {
    if (false && levels && options) {}  // Prevent unused
    tfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    VDual_Control_Switch___024root__trace_register(&(vlSymsp->TOP), tfp->spTrace());
}
