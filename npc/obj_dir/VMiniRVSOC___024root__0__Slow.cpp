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

VL_ATTR_COLD void VMiniRVSOC___024root___eval_initial__TOP(VMiniRVSOC___024root* vlSelf);

VL_ATTR_COLD void VMiniRVSOC___024root___eval_initial(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_initial\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VMiniRVSOC___024root___eval_initial__TOP(vlSelf);
}

VL_ATTR_COLD void VMiniRVSOC___024root___eval_initial__TOP(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_initial__TOP\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_wdata) {
        VL_COV_TOGGLE_CHG_ST_I(32, vlSymsp->__Vcoverage + 198, 0U, vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_wdata);
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_wdata = 0U;
    }
    if (vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__trap__DOT____Vtogcov__code) {
        VL_COV_TOGGLE_CHG_ST_I(8, vlSymsp->__Vcoverage + 344, 0U, vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__trap__DOT____Vtogcov__code);
        vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__trap__DOT____Vtogcov__code = 0U;
    }
    ++(vlSymsp->__Vcoverage[329]);
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
            VL_FATAL_MT("build/MiniRVSOC.sv", 179, "", "Settle region did not converge after 100 tries");
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

void VMiniRVSOC___024unit____Vdpiimwrap_ram_rdpi_TOP____024unit(IData/*31:0*/ raddr, IData/*31:0*/ &ram_rdpi__Vfuncrtn);
void VMiniRVSOC___024unit____Vdpiimwrap_ebreak_TOP____024unit(CData/*7:0*/ code);
void VMiniRVSOC___024unit____Vdpiimwrap_ram_wdpi_TOP____024unit(IData/*31:0*/ waddr, IData/*31:0*/ wdata, CData/*7:0*/ wmask);

VL_ATTR_COLD void VMiniRVSOC___024root___stl_sequent__TOP__0(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___stl_sequent__TOP__0\n"); );
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

VL_ATTR_COLD void VMiniRVSOC___024root____Vm_traceActivitySetAll(VMiniRVSOC___024root* vlSelf);

VL_ATTR_COLD void VMiniRVSOC___024root___eval_stl(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___eval_stl\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        VMiniRVSOC___024root___stl_sequent__TOP__0(vlSelf);
        VMiniRVSOC___024root____Vm_traceActivitySetAll(vlSelf);
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

VL_ATTR_COLD void VMiniRVSOC___024root____Vm_traceActivitySetAll(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root____Vm_traceActivitySetAll\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
}

VL_ATTR_COLD void VMiniRVSOC___024root___ctor_var_reset(VMiniRVSOC___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___ctor_var_reset\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clock = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5452235342940299466ull);
    vlSelf->reset = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9928399931838511862ull);
    vlSelf->MiniRVSOC__DOT___rom_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13150762794757657860ull);
    vlSelf->MiniRVSOC__DOT____Vtogcov__clock = 0;
    vlSelf->MiniRVSOC__DOT____Vtogcov__reset = 0;
    vlSelf->MiniRVSOC__DOT__cpu__DOT___exStage_io_pc_next = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 282242969083286415ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT___idStage_io_imm = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12414631923255557577ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_pc = 0;
    vlSelf->MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_instr = 0;
    vlSelf->MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_we = 0;
    vlSelf->MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_addr = 0;
    vlSelf->MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_wdata = 0;
    vlSelf->MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2344585391114112834ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__ifStage__DOT____Vtogcov__io_pc_next = 0;
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10241232708760665089ull);
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT____Vtogcov__io_jalr = 0;
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__trap__DOT____Vtogcov__trap = 0;
    vlSelf->MiniRVSOC__DOT__cpu__DOT__idStage__DOT__trap__DOT____Vtogcov__code = 0;
    vlSelf->MiniRVSOC__DOT__ram__DOT__rdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16149972540316315293ull);
    vlSelf->MiniRVSOC__DOT__ram__DOT____Vtogcov__rdata = 0;
    vlSelf->__Vfunc_ram_rdpi__1__Vfuncout = 0;
    vlSelf->__Vfunc_ram_rdpi__2__Vfuncout = 0;
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
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}

VL_ATTR_COLD void VMiniRVSOC___024root___configure_coverage(VMiniRVSOC___024root* vlSelf, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root___configure_coverage\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    (void)first;  // Prevent unused variable warning
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "build/MiniRVSOC.sv", 180, 9, ".MiniRVSOC", "v_toggle/MiniRVSOC", "clock");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[2]), first, "build/MiniRVSOC.sv", 181, 9, ".MiniRVSOC", "v_toggle/MiniRVSOC", "reset");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "build/MiniRVSOC.sv", 136, 17, ".MiniRVSOC.cpu", "v_toggle/MiniRV", "clock");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[2]), first, "build/MiniRVSOC.sv", 137, 17, ".MiniRVSOC.cpu", "v_toggle/MiniRV", "reset");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[4]), first, "build/MiniRVSOC.sv", 138, 17, ".MiniRVSOC.cpu", "v_toggle/MiniRV", "io_pc");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[68]), first, "build/MiniRVSOC.sv", 139, 17, ".MiniRVSOC.cpu", "v_toggle/MiniRV", "io_instr");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[132]), first, "build/MiniRVSOC.sv", 140, 17, ".MiniRVSOC.cpu", "v_toggle/MiniRV", "io_mem_we");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[134]), first, "build/MiniRVSOC.sv", 141, 17, ".MiniRVSOC.cpu", "v_toggle/MiniRV", "io_mem_addr");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[198]), first, "build/MiniRVSOC.sv", 142, 17, ".MiniRVSOC.cpu", "v_toggle/MiniRV", "io_mem_wdata");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[0]), first, "build/MiniRVSOC.sv", 54, 17, ".MiniRVSOC.cpu.ifStage", "v_toggle/IF", "clock");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[2]), first, "build/MiniRVSOC.sv", 55, 17, ".MiniRVSOC.cpu.ifStage", "v_toggle/IF", "reset");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[262]), first, "build/MiniRVSOC.sv", 56, 17, ".MiniRVSOC.cpu.ifStage", "v_toggle/IF", "io_pc_next");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[4]), first, "build/MiniRVSOC.sv", 57, 17, ".MiniRVSOC.cpu.ifStage", "v_toggle/IF", "io_pc_out");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[4]), first, "build/MiniRVSOC.sv", 60, 14, ".MiniRVSOC.cpu.ifStage", "v_toggle/IF", "pc");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[326]), first, "build/MiniRVSOC.sv", 62, 5, ".MiniRVSOC.cpu.ifStage", "v_branch/IF", "if", "62-63");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[327]), first, "build/MiniRVSOC.sv", 62, 6, ".MiniRVSOC.cpu.ifStage", "v_branch/IF", "else", "65");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[328]), first, "build/MiniRVSOC.sv", 61, 3, ".MiniRVSOC.cpu.ifStage", "v_line/IF", "block", "61");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[329]), first, "build/MiniRVSOC.sv", 72, 5, ".MiniRVSOC.cpu.ifStage", "v_line/IF", "block", "72");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[68]), first, "build/MiniRVSOC.sv", 91, 17, ".MiniRVSOC.cpu.idStage", "v_toggle/ID", "io_instr");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[198]), first, "build/MiniRVSOC.sv", 92, 17, ".MiniRVSOC.cpu.idStage", "v_toggle/ID", "io_rs1_data");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[198]), first, "build/MiniRVSOC.sv", 93, 17, ".MiniRVSOC.cpu.idStage", "v_toggle/ID", "io_rs2_data");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[134]), first, "build/MiniRVSOC.sv", 94, 17, ".MiniRVSOC.cpu.idStage", "v_toggle/ID", "io_imm");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[132]), first, "build/MiniRVSOC.sv", 95, 17, ".MiniRVSOC.cpu.idStage", "v_toggle/ID", "io_mem_write");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[330]), first, "build/MiniRVSOC.sv", 96, 17, ".MiniRVSOC.cpu.idStage", "v_toggle/ID", "io_jalr");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[332]), first, "build/MiniRVSOC.sv", 109, 9, ".MiniRVSOC.cpu.idStage", "v_branch/ID", "cond_then", "109");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[333]), first, "build/MiniRVSOC.sv", 111, 13, ".MiniRVSOC.cpu.idStage", "v_branch/ID", "cond_then", "111");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[334]), first, "build/MiniRVSOC.sv", 113, 17, ".MiniRVSOC.cpu.idStage", "v_branch/ID", "cond_then", "113");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[335]), first, "build/MiniRVSOC.sv", 115, 21, ".MiniRVSOC.cpu.idStage", "v_branch/ID", "cond_then", "115");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[336]), first, "build/MiniRVSOC.sv", 116, 46, ".MiniRVSOC.cpu.idStage", "v_branch/ID", "cond_then", "116");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[337]), first, "build/MiniRVSOC.sv", 116, 47, ".MiniRVSOC.cpu.idStage", "v_branch/ID", "cond_else", "116");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[338]), first, "build/MiniRVSOC.sv", 115, 22, ".MiniRVSOC.cpu.idStage", "v_branch/ID", "cond_else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[339]), first, "build/MiniRVSOC.sv", 113, 18, ".MiniRVSOC.cpu.idStage", "v_branch/ID", "cond_else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[340]), first, "build/MiniRVSOC.sv", 111, 14, ".MiniRVSOC.cpu.idStage", "v_branch/ID", "cond_else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[341]), first, "build/MiniRVSOC.sv", 109, 10, ".MiniRVSOC.cpu.idStage", "v_branch/ID", "cond_else", "");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[342]), first, "vsrc/ebreak.v", 4, 11, ".MiniRVSOC.cpu.idStage.trap", "v_toggle/EBreak", "trap");
    vlSelf->__vlCoverToggleInsert(0, 7, 1, &(vlSymsp->__Vcoverage[344]), first, "vsrc/ebreak.v", 5, 17, ".MiniRVSOC.cpu.idStage.trap", "v_toggle/EBreak", "code");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[360]), first, "vsrc/ebreak.v", 8, 9, ".MiniRVSOC.cpu.idStage.trap", "v_branch/EBreak", "if", "8-9");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[361]), first, "vsrc/ebreak.v", 8, 10, ".MiniRVSOC.cpu.idStage.trap", "v_branch/EBreak", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[362]), first, "vsrc/ebreak.v", 7, 5, ".MiniRVSOC.cpu.idStage.trap", "v_line/EBreak", "block", "7");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[198]), first, "build/MiniRVSOC.sv", 122, 17, ".MiniRVSOC.cpu.exStage", "v_toggle/EX", "io_rs1");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[134]), first, "build/MiniRVSOC.sv", 123, 17, ".MiniRVSOC.cpu.exStage", "v_toggle/EX", "io_imm");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[134]), first, "build/MiniRVSOC.sv", 124, 17, ".MiniRVSOC.cpu.exStage", "v_toggle/EX", "io_mem_addr");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[330]), first, "build/MiniRVSOC.sv", 125, 17, ".MiniRVSOC.cpu.exStage", "v_toggle/EX", "io_jalr");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[4]), first, "build/MiniRVSOC.sv", 126, 17, ".MiniRVSOC.cpu.exStage", "v_toggle/EX", "io_pc");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[262]), first, "build/MiniRVSOC.sv", 127, 17, ".MiniRVSOC.cpu.exStage", "v_toggle/EX", "io_pc_next");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[363]), first, "build/MiniRVSOC.sv", 132, 47, ".MiniRVSOC.cpu.exStage", "v_branch/EX", "cond_then", "132");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[364]), first, "build/MiniRVSOC.sv", 132, 48, ".MiniRVSOC.cpu.exStage", "v_branch/EX", "cond_else", "132");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[4]), first, "vsrc/minirv.v", 6, 22, ".MiniRVSOC.rom", "v_toggle/ROM_DPI", "addr");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[68]), first, "vsrc/minirv.v", 7, 22, ".MiniRVSOC.rom", "v_toggle/ROM_DPI", "data");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[365]), first, "vsrc/minirv.v", 9, 3, ".MiniRVSOC.rom", "v_line/ROM_DPI", "block", "9");
    vlSelf->__vlCoverToggleInsert(0, 0, 0, &(vlSymsp->__Vcoverage[132]), first, "vsrc/minirv.v", 13, 22, ".MiniRVSOC.ram", "v_toggle/RAM_DPI", "we");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[134]), first, "vsrc/minirv.v", 14, 22, ".MiniRVSOC.ram", "v_toggle/RAM_DPI", "addr");
    vlSelf->__vlCoverToggleInsert(0, 7, 1, &(vlSymsp->__Vcoverage[344]), first, "vsrc/minirv.v", 15, 22, ".MiniRVSOC.ram", "v_toggle/RAM_DPI", "mask");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[198]), first, "vsrc/minirv.v", 16, 22, ".MiniRVSOC.ram", "v_toggle/RAM_DPI", "wdata");
    vlSelf->__vlCoverToggleInsert(0, 31, 1, &(vlSymsp->__Vcoverage[366]), first, "vsrc/minirv.v", 17, 22, ".MiniRVSOC.ram", "v_toggle/RAM_DPI", "rdata");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[430]), first, "vsrc/minirv.v", 21, 5, ".MiniRVSOC.ram", "v_branch/RAM_DPI", "if", "21");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[431]), first, "vsrc/minirv.v", 21, 6, ".MiniRVSOC.ram", "v_branch/RAM_DPI", "else", "");
    vlSelf->__vlCoverInsert(&(vlSymsp->__Vcoverage[432]), first, "vsrc/minirv.v", 19, 3, ".MiniRVSOC.ram", "v_line/RAM_DPI", "block", "19-20");
}
