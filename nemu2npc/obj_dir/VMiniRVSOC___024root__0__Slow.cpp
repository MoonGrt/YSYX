// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VMiniRVSOC.h for the primary calling header

#include "VMiniRVSOC__pch.h"

VL_ATTR_COLD void VMiniRVSOC___024root___eval_static(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_static\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clock__0 = vlSelfRef.clock;
}

VL_ATTR_COLD void VMiniRVSOC___024root___eval_initial(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_initial\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void VMiniRVSOC___024root___eval_final(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_final\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VMiniRVSOC___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool VMiniRVSOC___024root___eval_phase__stl(VMiniRVSOC___024root* vlSelf);

VL_ATTR_COLD void VMiniRVSOC___024root___eval_settle(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_settle\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            VMiniRVSOC___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("/home/moon/ysyx/ysyx/nemu2npc/rtl/MiniRVSOC.sv", 606, "", "Settle region did not converge after 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
    } while (VMiniRVSOC___024root___eval_phase__stl(vlSelf));
}

VL_ATTR_COLD void VMiniRVSOC___024root___eval_triggers__stl(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_triggers__stl\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered
                                      [0U]) | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
    vlSelfRef.__VstlFirstIteration = 0U;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VMiniRVSOC___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
}

VL_ATTR_COLD bool VMiniRVSOC___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VMiniRVSOC___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(VMiniRVSOC___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool VMiniRVSOC___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___trigger_anySet__stl\n"); );
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

void VMiniRVSOC___024unit____Vdpiimwrap_pmem_read_TOP____024unit(IData/*31:0*/ raddr, IData/*31:0*/ &pmem_read__Vfuncrtn);
void VMiniRVSOC___024unit____Vdpiimwrap_pmem_write_TOP____024unit(IData/*31:0*/ waddr, CData/*7:0*/ wmask, IData/*31:0*/ wdata);
void VMiniRVSOC___024unit____Vdpiimwrap_ebreak_TOP____024unit(CData/*7:0*/ code);

VL_ATTR_COLD void VMiniRVSOC___024root___stl_sequent__TOP__0(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___stl_sequent__TOP__0\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.io_pc = vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc;
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT___ifStage_io_pcn 
        = ((IData)(4U) + vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc);
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

VL_ATTR_COLD void VMiniRVSOC___024root___eval_stl(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_stl\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        VMiniRVSOC___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool VMiniRVSOC___024root___eval_phase__stl(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_phase__stl\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    VMiniRVSOC___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = VMiniRVSOC___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        VMiniRVSOC___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool VMiniRVSOC___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VMiniRVSOC___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(VMiniRVSOC___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool VMiniRVSOC___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void VMiniRVSOC___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(VMiniRVSOC___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VMiniRVSOC___024root___ctor_var_reset(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___ctor_var_reset\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clock = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5452235342940299466ull);
    vlSelf->reset = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9928399931838511862ull);
    vlSelf->io_pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13491569557311850474ull);
    vlSelf->io_inst = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16668489171332404422ull);
    vlSelf->valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4944192500720994163ull);
    vlSelf->raddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12822808926477430924ull);
    vlSelf->waddr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15530376126285439671ull);
    vlSelf->wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12890271867161903902ull);
    vlSelf->wmask = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 7533683342978896906ull);
    vlSelf->wen = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12409248811792671830ull);
    vlSelf->rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10065165116613087284ull);
    vlSelf->MiniRVSOC__DOT___ram_rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12884220036477923586ull);
    vlSelf->MiniRVSOC__DOT___rom_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13150762794757657860ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT___exStage_io_exout = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8773924608711916739ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT___idStage_io_jumpen = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10536331267163305245ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT___ifStage_io_pcn = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 497790198580320680ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT___byte_data_T = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5483698904469808632ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data = 0;
    vlSelf->MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2344585391114112834ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7281240590019379453ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4777521431277892440ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_memBen = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2042319048419075072ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 10820810695675891948ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT___decoded_T_9 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12935521132327518107ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1112764669491030971ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_2 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13436032119595841085ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_0 = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8414291545248467340ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4 = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 16150734709348912186ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17414702859906983042ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17828197590490260078ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7048582591286835775ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_3 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7462077321869980003ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_4 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1290667251168691794ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_5 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6686188832165767702ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_6 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3114072460879227626ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_7 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4706706214590623717ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_8 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13877886024652117880ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_9 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3726413839038636103ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_10 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9010911628901626996ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_11 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13796007259472626162ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_12 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12336941282787715591ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_13 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14132448122739795745ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_14 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13378283493607670919ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_15 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1945423150766150646ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_16 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5772020555490391743ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_17 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17323766826321160431ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_18 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7083986892556381123ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_19 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 408038415895731655ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_20 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16999369326273328625ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_21 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9876241012518349329ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_22 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17634101852097117427ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_23 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 923177973913973015ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_24 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14254351172503135997ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_25 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16742167266410281632ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_26 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11005276682138359344ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_27 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10738152471003667905ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_28 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17266576461163807504ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_29 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12831523885758730897ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_30 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9090673711619840048ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_31 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4372264209679811719ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4886884984827013761ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_0 = 0;
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_2 = 0;
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_4 = 0;
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_5 = 0;
    vlSelf->__Vfunc_pmem_read__1__Vfuncout = 0;
    vlSelf->__Vfunc_pmem_read__2__Vfuncout = 0;
    vlSelf->__Vfunc_pmem_read__4__Vfuncout = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
