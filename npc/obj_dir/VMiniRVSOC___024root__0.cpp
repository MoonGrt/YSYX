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

void VMiniRVSOC___024root___ico_sequent__TOP__0(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___ico_sequent__TOP__0\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (((IData)(vlSelfRef.clock) ^ (IData)(vlSelfRef.MiniRVSOC__DOT____Vtogcov__clock))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 0, vlSelfRef.clock, vlSelfRef.MiniRVSOC__DOT____Vtogcov__clock);
        vlSelfRef.MiniRVSOC__DOT____Vtogcov__clock 
            = vlSelfRef.clock;
    }
    if (((IData)(vlSelfRef.reset) ^ (IData)(vlSelfRef.MiniRVSOC__DOT____Vtogcov__reset))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 2, vlSelfRef.reset, vlSelfRef.MiniRVSOC__DOT____Vtogcov__reset);
        vlSelfRef.MiniRVSOC__DOT____Vtogcov__reset 
            = vlSelfRef.reset;
    }
}

void VMiniRVSOC___024root___eval_ico(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_ico\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        VMiniRVSOC___024root___ico_sequent__TOP__0(vlSelf);
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

void VMiniRVSOC___024unit____Vdpiimwrap_ram_rdpi_TOP____024unit(IData/*31:0*/ raddr, IData/*31:0*/ &ram_rdpi__Vfuncrtn);
void VMiniRVSOC___024unit____Vdpiimwrap_ebreak_TOP____024unit(CData/*7:0*/ code);
void VMiniRVSOC___024unit____Vdpiimwrap_ram_wdpi_TOP____024unit(IData/*31:0*/ waddr, IData/*31:0*/ wdata, CData/*7:0*/ wmask);

void VMiniRVSOC___024root___nba_sequent__TOP__0(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___nba_sequent__TOP__0\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.reset) {
        ++(vlSymsp->__Vcoverage[326]);
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc = 0x80000000U;
    } else {
        ++(vlSymsp->__Vcoverage[327]);
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc 
            = vlSelfRef.MiniRVSOC__DOT__cpu__DOT___exStage_io_pc_next;
    }
    ++(vlSymsp->__Vcoverage[328]);
    if ((vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc 
         ^ vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_pc)) {
        VL_COV_TOGGLE_CHG_ST_I(32, vlSymsp->__Vcoverage + 4, vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc, vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_pc);
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_pc 
            = vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc;
    }
    VMiniRVSOC___024unit____Vdpiimwrap_ram_rdpi_TOP____024unit(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc, vlSelfRef.__Vfunc_ram_rdpi__1__Vfuncout);
    vlSelfRef.MiniRVSOC__DOT___rom_data = vlSelfRef.__Vfunc_ram_rdpi__1__Vfuncout;
    ++(vlSymsp->__Vcoverage[365]);
    if ((0x73U == (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data))) {
        VMiniRVSOC___024unit____Vdpiimwrap_ebreak_TOP____024unit(0U);
        ++(vlSymsp->__Vcoverage[360]);
    } else {
        ++(vlSymsp->__Vcoverage[361]);
    }
    ++(vlSymsp->__Vcoverage[362]);
    if ((vlSelfRef.MiniRVSOC__DOT___rom_data ^ vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_instr)) {
        VL_COV_TOGGLE_CHG_ST_I(32, vlSymsp->__Vcoverage + 68, vlSelfRef.MiniRVSOC__DOT___rom_data, vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_instr);
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_instr 
            = vlSelfRef.MiniRVSOC__DOT___rom_data;
    }
    if (((0x23U == (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data)) 
         ^ (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_we))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 132, 
                               (0x23U == (0x0000007fU 
                                          & vlSelfRef.MiniRVSOC__DOT___rom_data)), vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_we);
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_we 
            = (0x23U == (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data));
    }
    if (((0x67U == (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data)) 
         ^ (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____Vtogcov__io_jalr))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 330, 
                               (0x67U == (0x0000007fU 
                                          & vlSelfRef.MiniRVSOC__DOT___rom_data)), vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____Vtogcov__io_jalr);
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____Vtogcov__io_jalr 
            = (0x67U == (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data));
    }
    if (((0x73U == (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data)) 
         ^ (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__trap__DOT____Vtogcov__trap))) {
        VL_COV_TOGGLE_CHG_ST_I(1, vlSymsp->__Vcoverage + 342, 
                               (0x73U == (0x0000007fU 
                                          & vlSelfRef.MiniRVSOC__DOT___rom_data)), vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__trap__DOT____Vtogcov__trap);
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__trap__DOT____Vtogcov__trap 
            = (0x73U == (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data));
    }
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_0 
        = (((- (IData)((vlSelfRef.MiniRVSOC__DOT___rom_data 
                        >> 0x0000001fU))) << 0x0000000cU) 
           | (vlSelfRef.MiniRVSOC__DOT___rom_data >> 0x00000014U));
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT___idStage_io_imm 
        = ((0x67U == (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data))
            ? ([&]() {
                ++(vlSymsp->__Vcoverage[332]);
            }(), vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_0)
            : ([&]() {
                ++(vlSymsp->__Vcoverage[341]);
            }(), ((0x23U == (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data))
                   ? ([&]() {
                        ++(vlSymsp->__Vcoverage[333]);
                    }(), (((- (IData)((vlSelfRef.MiniRVSOC__DOT___rom_data 
                                       >> 0x0000001fU))) 
                           << 0x0000000cU) | ((0x00000fe0U 
                                               & (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                                  >> 0x00000014U)) 
                                              | (0x0000001fU 
                                                 & (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                                    >> 7U)))))
                   : ([&]() {
                        ++(vlSymsp->__Vcoverage[340]);
                    }(), ((3U == (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data))
                           ? ([&]() {
                                ++(vlSymsp->__Vcoverage[334]);
                            }(), vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_0)
                           : ([&]() {
                                ++(vlSymsp->__Vcoverage[339]);
                            }(), ((0x37U == (0x0000007fU 
                                             & vlSelfRef.MiniRVSOC__DOT___rom_data))
                                   ? ([&]() {
                                        ++(vlSymsp->__Vcoverage[335]);
                                    }(), (0xfffff000U 
                                          & vlSelfRef.MiniRVSOC__DOT___rom_data))
                                   : ([&]() {
                                        ++(vlSymsp->__Vcoverage[338]);
                                    }(), ((0x13U == 
                                           (0x0000007fU 
                                            & vlSelfRef.MiniRVSOC__DOT___rom_data))
                                           ? ([&]() {
                                                ++(vlSymsp->__Vcoverage[336]);
                                            }(), vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_0)
                                           : ([&]() {
                                                ++(vlSymsp->__Vcoverage[337]);
                                            }(), 0U))))))))));
    if ((vlSelfRef.MiniRVSOC__DOT__cpu__DOT___idStage_io_imm 
         ^ vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_addr)) {
        VL_COV_TOGGLE_CHG_ST_I(32, vlSymsp->__Vcoverage + 134, vlSelfRef.MiniRVSOC__DOT__cpu__DOT___idStage_io_imm, vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_addr);
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_addr 
            = vlSelfRef.MiniRVSOC__DOT__cpu__DOT___idStage_io_imm;
    }
    vlSelfRef.MiniRVSOC__DOT__cpu__DOT___exStage_io_pc_next 
        = ((0x67U == (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data))
            ? ([&]() {
                ++(vlSymsp->__Vcoverage[363]);
            }(), (0xfffffffeU & vlSelfRef.MiniRVSOC__DOT__cpu__DOT___idStage_io_imm))
            : ([&]() {
                ++(vlSymsp->__Vcoverage[364]);
            }(), ((IData)(4U) + vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc)));
    VMiniRVSOC___024unit____Vdpiimwrap_ram_rdpi_TOP____024unit(vlSelfRef.MiniRVSOC__DOT__cpu__DOT___idStage_io_imm, vlSelfRef.__Vfunc_ram_rdpi__2__Vfuncout);
    vlSelfRef.MiniRVSOC__DOT__ram__DOT__rdata = vlSelfRef.__Vfunc_ram_rdpi__2__Vfuncout;
    if ((0x23U == (0x0000007fU & vlSelfRef.MiniRVSOC__DOT___rom_data))) {
        VMiniRVSOC___024unit____Vdpiimwrap_ram_wdpi_TOP____024unit(vlSelfRef.MiniRVSOC__DOT__cpu__DOT___idStage_io_imm, 0U, 0U);
        ++(vlSymsp->__Vcoverage[430]);
    } else {
        ++(vlSymsp->__Vcoverage[431]);
    }
    ++(vlSymsp->__Vcoverage[432]);
    if ((vlSelfRef.MiniRVSOC__DOT__cpu__DOT___exStage_io_pc_next 
         ^ vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT____Vtogcov__io_pc_next)) {
        VL_COV_TOGGLE_CHG_ST_I(32, vlSymsp->__Vcoverage + 262, vlSelfRef.MiniRVSOC__DOT__cpu__DOT___exStage_io_pc_next, vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT____Vtogcov__io_pc_next);
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT____Vtogcov__io_pc_next 
            = vlSelfRef.MiniRVSOC__DOT__cpu__DOT___exStage_io_pc_next;
    }
    if ((vlSelfRef.MiniRVSOC__DOT__ram__DOT__rdata 
         ^ vlSelfRef.MiniRVSOC__DOT__ram__DOT____Vtogcov__rdata)) {
        VL_COV_TOGGLE_CHG_ST_I(32, vlSymsp->__Vcoverage + 366, vlSelfRef.MiniRVSOC__DOT__ram__DOT__rdata, vlSelfRef.MiniRVSOC__DOT__ram__DOT____Vtogcov__rdata);
        vlSelfRef.MiniRVSOC__DOT__ram__DOT____Vtogcov__rdata 
            = vlSelfRef.MiniRVSOC__DOT__ram__DOT__rdata;
    }
}

void VMiniRVSOC___024root___eval_nba(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_nba\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        VMiniRVSOC___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
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
            VL_FATAL_MT("build/MiniRVSOC.sv", 179, "", "Input combinational region did not converge after 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
    } while (VMiniRVSOC___024root___eval_phase__ico(vlSelf));
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            VMiniRVSOC___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("build/MiniRVSOC.sv", 179, "", "NBA region did not converge after 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                VMiniRVSOC___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("build/MiniRVSOC.sv", 179, "", "Active region did not converge after 100 tries");
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
}
#endif  // VL_DEBUG
