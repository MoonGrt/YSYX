// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VDual_Control_Switch.h for the primary calling header

#include "verilated.h"

#include "VDual_Control_Switch___024root.h"

VL_INLINE_OPT void VDual_Control_Switch___024root___combo__TOP__1(VDual_Control_Switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VDual_Control_Switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VDual_Control_Switch___024root___combo__TOP__1\n"); );
    // Body
    vlSelf->f = ((IData)(vlSelf->a) ^ (IData)(vlSelf->b));
}

void VDual_Control_Switch___024root___eval(VDual_Control_Switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VDual_Control_Switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VDual_Control_Switch___024root___eval\n"); );
    // Body
    VDual_Control_Switch___024root___combo__TOP__1(vlSelf);
}

#ifdef VL_DEBUG
void VDual_Control_Switch___024root___eval_debug_assertions(VDual_Control_Switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VDual_Control_Switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VDual_Control_Switch___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->a & 0xfeU))) {
        Verilated::overWidthError("a");}
    if (VL_UNLIKELY((vlSelf->b & 0xfeU))) {
        Verilated::overWidthError("b");}
}
#endif  // VL_DEBUG
