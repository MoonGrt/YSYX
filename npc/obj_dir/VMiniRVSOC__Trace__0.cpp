// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "VMiniRVSOC__Syms.h"


void VMiniRVSOC___024root__trace_chg_0_sub_0(VMiniRVSOC___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void VMiniRVSOC___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root__trace_chg_0\n"); );
    // Body
    VMiniRVSOC___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VMiniRVSOC___024root*>(voidSelf);
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    VMiniRVSOC___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void VMiniRVSOC___024root__trace_chg_0_sub_0(VMiniRVSOC___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root__trace_chg_0_sub_0\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgIData(oldp+0,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc),32);
        bufp->chgIData(oldp+1,(vlSelfRef.MiniRVSOC__DOT___rom_data),32);
        bufp->chgBit(oldp+2,((0x23U == (0x0000007fU 
                                        & vlSelfRef.MiniRVSOC__DOT___rom_data))));
        bufp->chgIData(oldp+3,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT___idStage_io_imm),32);
        bufp->chgBit(oldp+4,((0x67U == (0x0000007fU 
                                        & vlSelfRef.MiniRVSOC__DOT___rom_data))));
        bufp->chgIData(oldp+5,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT___exStage_io_pc_next),32);
        bufp->chgBit(oldp+6,((0x73U == (0x0000007fU 
                                        & vlSelfRef.MiniRVSOC__DOT___rom_data))));
        bufp->chgIData(oldp+7,(vlSelfRef.MiniRVSOC__DOT__ram__DOT__rdata),32);
    }
    bufp->chgBit(oldp+8,(vlSelfRef.clock));
    bufp->chgBit(oldp+9,(vlSelfRef.reset));
}

void VMiniRVSOC___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root__trace_cleanup\n"); );
    // Body
    VMiniRVSOC___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VMiniRVSOC___024root*>(voidSelf);
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
