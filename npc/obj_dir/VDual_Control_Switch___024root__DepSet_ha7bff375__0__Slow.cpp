// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VDual_Control_Switch.h for the primary calling header

#include "verilated.h"

#include "VDual_Control_Switch___024root.h"

VL_ATTR_COLD void VDual_Control_Switch___024root___eval_initial(VDual_Control_Switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VDual_Control_Switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VDual_Control_Switch___024root___eval_initial\n"); );
}

void VDual_Control_Switch___024root___combo__TOP__1(VDual_Control_Switch___024root* vlSelf);

VL_ATTR_COLD void VDual_Control_Switch___024root___eval_settle(VDual_Control_Switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VDual_Control_Switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VDual_Control_Switch___024root___eval_settle\n"); );
    // Body
    VDual_Control_Switch___024root___combo__TOP__1(vlSelf);
}

VL_ATTR_COLD void VDual_Control_Switch___024root___final(VDual_Control_Switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VDual_Control_Switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VDual_Control_Switch___024root___final\n"); );
}

VL_ATTR_COLD void VDual_Control_Switch___024root___ctor_var_reset(VDual_Control_Switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VDual_Control_Switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VDual_Control_Switch___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->a = VL_RAND_RESET_I(1);
    vlSelf->b = VL_RAND_RESET_I(1);
    vlSelf->f = VL_RAND_RESET_I(1);
}
