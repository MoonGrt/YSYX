// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VMiniRVSOC.h for the primary calling header

#include "VMiniRVSOC__pch.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VMiniRVSOC___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void VMiniRVSOC___024root___eval_triggers__ico(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_triggers__ico\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
    vlSelfRef.__VicoFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VMiniRVSOC___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
}

bool VMiniRVSOC___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void VMiniRVSOC___024unit____Vdpiimwrap_ebreak_TOP____024unit(CData/*7:0*/ code);
void VMiniRVSOC___024unit____Vdpiimwrap_pmem_read_TOP____024unit(IData/*31:0*/ raddr, IData/*31:0*/ &pmem_read__Vfuncrtn);
void VMiniRVSOC___024unit____Vdpiimwrap_pmem_write_TOP____024unit(IData/*31:0*/ waddr, CData/*7:0*/ wmask, IData/*31:0*/ wdata);

void VMiniRVSOC___024root___ico_sequent__TOP__0(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___ico_sequent__TOP__0\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & ((~ (IData)(vlSelfRef.reset)) & (~ ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_5) 
                                                  | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_4)))))) {
        VMiniRVSOC___024unit____Vdpiimwrap_ebreak_TOP____024unit(
                                                                 ((0x00100073U 
                                                                   == vlSelfRef.MiniRVSOC__DOT___rom_data)
                                                                   ? 0U
                                                                   : 
                                                                  ((0U 
                                                                    == vlSelfRef.MiniRVSOC__DOT___rom_data)
                                                                    ? 1U
                                                                    : 
                                                                   (((0x73U 
                                                                      == 
                                                                      (0x0000007fU 
                                                                       & vlSelfRef.MiniRVSOC__DOT___rom_data)) 
                                                                     & (0x00100073U 
                                                                        != vlSelfRef.MiniRVSOC__DOT___rom_data))
                                                                     ? 2U
                                                                     : 
                                                                    (1U 
                                                                     | (2U 
                                                                        & ((~ 
                                                                            ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_5) 
                                                                             | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_4))) 
                                                                           << 1U)))))));
    }
    if (vlSelfRef.valid) {
        VMiniRVSOC___024unit____Vdpiimwrap_pmem_read_TOP____024unit(vlSelfRef.raddr, vlSelfRef.__Vfunc_pmem_read__4__Vfuncout);
        vlSelfRef.rdata = vlSelfRef.__Vfunc_pmem_read__4__Vfuncout;
        if (vlSelfRef.wen) {
            VMiniRVSOC___024unit____Vdpiimwrap_pmem_write_TOP____024unit(vlSelfRef.waddr, 
                                                                         (0x000000ffU 
                                                                          & vlSelfRef.wdata), (IData)(vlSelfRef.wmask));
        }
    } else {
        vlSelfRef.rdata = 0U;
    }
}

void VMiniRVSOC___024root___eval_ico(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_ico\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        if ((1U & ((~ (IData)(vlSelfRef.reset)) & (~ 
                                                   ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_5) 
                                                    | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_4)))))) {
            VMiniRVSOC___024unit____Vdpiimwrap_ebreak_TOP____024unit(
                                                                     ((0x00100073U 
                                                                       == vlSelfRef.MiniRVSOC__DOT___rom_data)
                                                                       ? 0U
                                                                       : 
                                                                      ((0U 
                                                                        == vlSelfRef.MiniRVSOC__DOT___rom_data)
                                                                        ? 1U
                                                                        : 
                                                                       (((0x73U 
                                                                          == 
                                                                          (0x0000007fU 
                                                                           & vlSelfRef.MiniRVSOC__DOT___rom_data)) 
                                                                         & (0x00100073U 
                                                                            != vlSelfRef.MiniRVSOC__DOT___rom_data))
                                                                         ? 2U
                                                                         : 
                                                                        (1U 
                                                                         | (2U 
                                                                            & ((~ 
                                                                                ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_5) 
                                                                                | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_4))) 
                                                                               << 1U)))))));
        }
        if (vlSelfRef.valid) {
            VMiniRVSOC___024unit____Vdpiimwrap_pmem_read_TOP____024unit(vlSelfRef.raddr, vlSelfRef.__Vfunc_pmem_read__4__Vfuncout);
            vlSelfRef.rdata = vlSelfRef.__Vfunc_pmem_read__4__Vfuncout;
            if (vlSelfRef.wen) {
                VMiniRVSOC___024unit____Vdpiimwrap_pmem_write_TOP____024unit(vlSelfRef.waddr, 
                                                                             (0x000000ffU 
                                                                              & vlSelfRef.wdata), (IData)(vlSelfRef.wmask));
            }
        } else {
            vlSelfRef.rdata = 0U;
        }
    }
}

bool VMiniRVSOC___024root___eval_phase__ico(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_phase__ico\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    VMiniRVSOC___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = VMiniRVSOC___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        VMiniRVSOC___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VMiniRVSOC___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

void VMiniRVSOC___024root___eval_triggers__act(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_triggers__act\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((IData)(vlSelfRef.clock) 
                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clock__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VMiniRVSOC___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
}

bool VMiniRVSOC___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void VMiniRVSOC___024root___nba_sequent__TOP__0(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___nba_sequent__TOP__0\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.reset) {
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_31 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_30 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_29 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_28 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_11 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_10 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_6 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_9 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_4 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_7 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_2 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_5 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_0 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_3 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_1 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_8 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_12 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_13 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_14 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_15 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_16 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_17 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_18 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_19 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_20 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_21 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_22 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_23 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_24 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_25 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_26 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_27 = 0U;
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc = 0x80000000U;
    } else {
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000f80U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_31 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000f00U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_30 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000e80U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_29 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000e00U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_28 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000580U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_11 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000500U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_10 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000300U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_6 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000480U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_9 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000200U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_4 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000380U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_7 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000100U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_2 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000280U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_5 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (~ (0U != (0x0000001fU & (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                         >> 7U)))))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_0 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000180U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_3 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000080U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_1 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000400U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_8 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000600U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_12 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000680U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_13 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000700U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_14 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000780U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_15 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000800U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_16 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000880U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_17 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000900U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_18 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000980U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_19 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000a00U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_20 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000a80U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_21 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000b00U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_22 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000b80U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_23 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000c00U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_24 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000c80U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_25 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000d00U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_26 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3) 
             & (0x00000d80U == (0x00000f80U & vlSelfRef.MiniRVSOC__DOT___rom_data)))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_27 
                = vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        }
        if ((1U & (~ ((~ (IData)(vlSelfRef.reset)) 
                      & (~ ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_5) 
                            | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_4))))))) {
            vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc 
                = ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT___idStage_io_jumpen)
                    ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT___exStage_io_exout
                    : vlSelfRef.MiniRVSOC__DOT__cpu__DOT___ifStage_io_pcn);
        }
    }
    vlSelfRef.io_pc = vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc;
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT___ifStage_io_pcn 
        = ((IData)(4U) + vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc);
    VMiniRVSOC___024unit____Vdpiimwrap_pmem_read_TOP____024unit(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc, vlSelfRef.__Vfunc_pmem_read__1__Vfuncout);
    vlSelfRef.MiniRVSOC__DOT___rom_data = vlSelfRef.__Vfunc_pmem_read__1__Vfuncout;
    vlSelfRef.io_inst = vlSelfRef.MiniRVSOC__DOT___rom_data;
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs1 
        = ((0x37U == (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data))
            ? 0U : ((0x00080000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                     ? ((0x00040000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                         ? ((0x00020000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                             ? ((0x00010000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                 ? ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_31
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_30)
                                 : ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_29
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_28))
                             : ((0x00010000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                 ? ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_27
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_26)
                                 : ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_25
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_24)))
                         : ((0x00020000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                             ? ((0x00010000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                 ? ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_23
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_22)
                                 : ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_21
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_20))
                             : ((0x00010000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                 ? ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_19
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_18)
                                 : ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_17
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_16))))
                     : ((0x00040000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                         ? ((0x00020000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                             ? ((0x00010000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                 ? ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_15
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_14)
                                 : ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_13
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_12))
                             : ((0x00010000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                 ? ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_11
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_10)
                                 : ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_9
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_8)))
                         : ((0x00020000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                             ? ((0x00010000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                 ? ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_7
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_6)
                                 : ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_5
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_4))
                             : ((0x00010000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                 ? ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_3
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_2)
                                 : ((0x00008000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                                     ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_1
                                     : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_0))))));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs2 
        = ((0x01000000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
            ? ((0x00800000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                ? ((0x00400000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                    ? ((0x00200000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                        ? ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_31
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_30)
                        : ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_29
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_28))
                    : ((0x00200000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                        ? ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_27
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_26)
                        : ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_25
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_24)))
                : ((0x00400000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                    ? ((0x00200000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                        ? ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_23
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_22)
                        : ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_21
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_20))
                    : ((0x00200000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                        ? ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_19
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_18)
                        : ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_17
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_16))))
            : ((0x00800000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                ? ((0x00400000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                    ? ((0x00200000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                        ? ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_15
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_14)
                        : ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_13
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_12))
                    : ((0x00200000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                        ? ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_11
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_10)
                        : ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_9
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_8)))
                : ((0x00400000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                    ? ((0x00200000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                        ? ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_7
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_6)
                        : ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_5
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_4))
                    : ((0x00200000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                        ? ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_3
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_2)
                        : ((0x00100000U & vlSelfRef.MiniRVSOC__DOT___rom_data)
                            ? vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_1
                            : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_0)))));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN 
        = ((0x00000380U & (vlSelfRef.MiniRVSOC__DOT___rom_data 
                           >> 5U)) | (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_4 
        = ((0x0067U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN)) 
           | (0x37U == (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data)));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_0 
        = ((0x0013U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN)) 
           | (0x0067U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN)));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_1 
        = ((0x0123U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN)) 
           | (0x0023U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN)));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_2 
        = ((0x0103U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN)) 
           | (0x0203U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN)));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___decoded_T_9 
        = (0x00000033U == ((0x0001fc00U & (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                           >> 0x0000000fU)) 
                           | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN)));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3 
        = (((~ (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_1)) 
            | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_2)) 
           & (0U != (0x0000001fU & (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                    >> 7U))));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_0 
        = ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_2)
            ? 1U : ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_1)
                     ? 2U : ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___decoded_T_9)
                              ? 0U : ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_0)
                                       ? 1U : (3U & 
                                               (- (IData)(
                                                          (0x37U 
                                                           == 
                                                           (0x0000007fU 
                                                            & vlSelfRef.MiniRVSOC__DOT___rom_data)))))))));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_2 
        = ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___decoded_T_9) 
           | (0x0013U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN)));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT___exStage_io_exout 
        = (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_2) 
            | ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_1) 
               | ((~ (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___decoded_T_9)) 
                  & ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_0) 
                     | (0U != (3U & (- (IData)((0x37U 
                                                == 
                                                (0x0000007fU 
                                                 & vlSelfRef.MiniRVSOC__DOT___rom_data))))))))))
            ? (((0U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_0))
                 ? 0U : ((1U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_0))
                          ? (((- (IData)((vlSelfRef.MiniRVSOC__DOT___rom_data 
                                          >> 0x0000001fU))) 
                              << 0x0000000cU) | (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                                 >> 0x00000014U))
                          : ((2U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_0))
                              ? (((- (IData)((vlSelfRef.MiniRVSOC__DOT___rom_data 
                                              >> 0x0000001fU))) 
                                  << 0x0000000cU) | 
                                 ((0x00000fe0U & (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                                  >> 0x00000014U)) 
                                  | (0x0000001fU & 
                                     (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                      >> 7U)))) : (0xfffff000U 
                                                   & vlSelfRef.MiniRVSOC__DOT___rom_data)))) 
               + vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs1)
            : (vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs1 
               + vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs2));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_5 
        = ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_2) 
           | ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_1) 
              | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_2)));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4 
        = ((0x0103U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN))
            ? 1U : ((0x0203U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN))
                     ? 2U : ((0x0123U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN))
                              ? 3U : ((0x0023U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN))
                                       ? 4U : (((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_2) 
                                                | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_4))
                                                ? 0U
                                                : 3U)))));
    if ((1U & ((~ (IData)(vlSelfRef.reset)) & (~ ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_5) 
                                                  | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_4)))))) {
        VMiniRVSOC___024unit____Vdpiimwrap_ebreak_TOP____024unit(
                                                                 ((0x00100073U 
                                                                   == vlSelfRef.MiniRVSOC__DOT___rom_data)
                                                                   ? 0U
                                                                   : 
                                                                  ((0U 
                                                                    == vlSelfRef.MiniRVSOC__DOT___rom_data)
                                                                    ? 1U
                                                                    : 
                                                                   (((0x73U 
                                                                      == 
                                                                      (0x0000007fU 
                                                                       & vlSelfRef.MiniRVSOC__DOT___rom_data)) 
                                                                     & (0x00100073U 
                                                                        != vlSelfRef.MiniRVSOC__DOT___rom_data))
                                                                     ? 2U
                                                                     : 
                                                                    (1U 
                                                                     | (2U 
                                                                        & ((~ 
                                                                            ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_5) 
                                                                             | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_4))) 
                                                                           << 1U)))))));
    }
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT___idStage_io_jumpen 
        = ((~ (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_5)) 
           & (0x0067U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN)));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_memBen 
        = ((2U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4)) 
           | (4U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4)));
    VMiniRVSOC___024unit____Vdpiimwrap_pmem_read_TOP____024unit(vlSelfRef.MiniRVSOC__DOT__cpu__DOT___exStage_io_exout, vlSelfRef.__Vfunc_pmem_read__2__Vfuncout);
    vlSelfRef.MiniRVSOC__DOT___ram_rdata = vlSelfRef.__Vfunc_pmem_read__2__Vfuncout;
    if (((3U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4)) 
         | (4U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4)))) {
        VMiniRVSOC___024unit____Vdpiimwrap_pmem_write_TOP____024unit(vlSelfRef.MiniRVSOC__DOT__cpu__DOT___exStage_io_exout, 
                                                                     ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_memBen)
                                                                       ? 
                                                                      (0x0000000fU 
                                                                       & ((IData)(1U) 
                                                                          << 
                                                                          (3U 
                                                                           & vlSelfRef.MiniRVSOC__DOT__cpu__DOT___exStage_io_exout)))
                                                                       : 0x0000000fU), 
                                                                     ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_memBen)
                                                                       ? 
                                                                      (vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs2 
                                                                       << 
                                                                       (0x00000018U 
                                                                        & (vlSelfRef.MiniRVSOC__DOT__cpu__DOT___exStage_io_exout 
                                                                           << 3U)))
                                                                       : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs2));
    }
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT___byte_data_T 
        = (vlSelfRef.MiniRVSOC__DOT___ram_rdata >> 
           (0x00000018U & (vlSelfRef.MiniRVSOC__DOT__cpu__DOT___exStage_io_exout 
                           << 3U)));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data 
        = (((1U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4)) 
            | (2U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4)))
            ? ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_memBen)
                ? (((- (IData)((1U & (vlSelfRef.MiniRVSOC__DOT__cpu__DOT___byte_data_T 
                                      >> 7U)))) << 8U) 
                   | (0x000000ffU & vlSelfRef.MiniRVSOC__DOT__cpu__DOT___byte_data_T))
                : vlSelfRef.MiniRVSOC__DOT___ram_rdata)
            : ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT___idStage_io_jumpen)
                ? ((IData)(4U) + vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc)
                : vlSelfRef.MiniRVSOC__DOT__cpu__DOT___exStage_io_exout));
}

void VMiniRVSOC___024root___eval_nba(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_nba\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        VMiniRVSOC___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void VMiniRVSOC___024root___trigger_orInto__act(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___trigger_orInto__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool VMiniRVSOC___024root___eval_phase__act(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_phase__act\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VMiniRVSOC___024root___eval_triggers__act(vlSelf);
    VMiniRVSOC___024root___trigger_orInto__act(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void VMiniRVSOC___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool VMiniRVSOC___024root___eval_phase__nba(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_phase__nba\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = VMiniRVSOC___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        VMiniRVSOC___024root___eval_nba(vlSelf);
        VMiniRVSOC___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void VMiniRVSOC___024root___eval(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            VMiniRVSOC___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("/home/moon/ysyx/ysyx/nemu2npc/rtl/MiniRVSOC.sv", 606, "", "Input combinational region did not converge after 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
    } while (VMiniRVSOC___024root___eval_phase__ico(vlSelf));
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            VMiniRVSOC___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/home/moon/ysyx/ysyx/nemu2npc/rtl/MiniRVSOC.sv", 606, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                VMiniRVSOC___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/home/moon/ysyx/ysyx/nemu2npc/rtl/MiniRVSOC.sv", 606, "", "Active region did not converge after 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
        } while (VMiniRVSOC___024root___eval_phase__act(vlSelf));
    } while (VMiniRVSOC___024root___eval_phase__nba(vlSelf));
}

#ifdef VL_DEBUG
void VMiniRVSOC___024root___eval_debug_assertions(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_debug_assertions\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clock & 0xfeU)))) {
        Verilated::overWidthError("clock");
    }
    if (VL_UNLIKELY(((vlSelfRef.reset & 0xfeU)))) {
        Verilated::overWidthError("reset");
    }
    if (VL_UNLIKELY(((vlSelfRef.valid & 0xfeU)))) {
        Verilated::overWidthError("valid");
    }
    if (VL_UNLIKELY(((vlSelfRef.wen & 0xfeU)))) {
        Verilated::overWidthError("wen");
    }
}
#endif  // VL_DEBUG
