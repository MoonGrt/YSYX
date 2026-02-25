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
        bufp->chgBit(oldp+2,(((3U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4)) 
                              | (4U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4)))));
        bufp->chgIData(oldp+3,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__io_jump),32);
        bufp->chgCData(oldp+4,(((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_memBen)
                                 ? (0x0000000fU & ((IData)(1U) 
                                                   << 
                                                   (3U 
                                                    & vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__io_jump)))
                                 : 0x0000000fU)),8);
        bufp->chgIData(oldp+5,(((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_memBen)
                                 ? (vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs2 
                                    << (0x00000018U 
                                        & (vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__io_jump 
                                           << 3U)))
                                 : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs2)),32);
        bufp->chgIData(oldp+6,(vlSelfRef.MiniRVSOC__DOT___ram_rdata),32);
        bufp->chgIData(oldp+7,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs1),32);
        bufp->chgIData(oldp+8,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs2),32);
        bufp->chgIData(oldp+9,(((0U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_0))
                                 ? 0U : ((1U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_0))
                                          ? (((- (IData)(
                                                         (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                                          >> 0x0000001fU))) 
                                              << 0x0000000cU) 
                                             | (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                                >> 0x00000014U))
                                          : ((2U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_0))
                                              ? (((- (IData)(
                                                             (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                                              >> 0x0000001fU))) 
                                                  << 0x0000000cU) 
                                                 | ((0x00000fe0U 
                                                     & (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                                        >> 0x00000014U)) 
                                                    | (0x0000001fU 
                                                       & (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                                          >> 7U))))
                                              : (0xfffff000U 
                                                 & vlSelfRef.MiniRVSOC__DOT___rom_data))))),32);
        bufp->chgBit(oldp+10,(((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_2) 
                               | ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_1) 
                                  | ((~ (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___decoded_T_9)) 
                                     & ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_0) 
                                        | (0U != (3U 
                                                  & (- (IData)(
                                                               (0x37U 
                                                                == 
                                                                (0x0000007fU 
                                                                 & vlSelfRef.MiniRVSOC__DOT___rom_data))))))))))));
        bufp->chgBit(oldp+11,((1U & ((~ (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_1)) 
                                     | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_2)))));
        bufp->chgCData(oldp+12,((0x0000001fU & (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                                >> 7U))),5);
        bufp->chgIData(oldp+13,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data),32);
        bufp->chgBit(oldp+14,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__io_jumpen));
        bufp->chgBit(oldp+15,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_memBen));
        bufp->chgBit(oldp+16,(((1U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4)) 
                               | (2U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4)))));
        bufp->chgCData(oldp+17,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_0),2);
        bufp->chgCData(oldp+18,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4),3);
        bufp->chgIData(oldp+19,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_0),32);
        bufp->chgIData(oldp+20,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_1),32);
        bufp->chgIData(oldp+21,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_2),32);
        bufp->chgIData(oldp+22,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_3),32);
        bufp->chgIData(oldp+23,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_4),32);
        bufp->chgIData(oldp+24,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_5),32);
        bufp->chgIData(oldp+25,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_6),32);
        bufp->chgIData(oldp+26,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_7),32);
        bufp->chgIData(oldp+27,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_8),32);
        bufp->chgIData(oldp+28,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_9),32);
        bufp->chgIData(oldp+29,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_10),32);
        bufp->chgIData(oldp+30,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_11),32);
        bufp->chgIData(oldp+31,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_12),32);
        bufp->chgIData(oldp+32,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_13),32);
        bufp->chgIData(oldp+33,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_14),32);
        bufp->chgIData(oldp+34,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_15),32);
        bufp->chgIData(oldp+35,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_16),32);
        bufp->chgIData(oldp+36,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_17),32);
        bufp->chgIData(oldp+37,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_18),32);
        bufp->chgIData(oldp+38,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_19),32);
        bufp->chgIData(oldp+39,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_20),32);
        bufp->chgIData(oldp+40,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_21),32);
        bufp->chgIData(oldp+41,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_22),32);
        bufp->chgIData(oldp+42,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_23),32);
        bufp->chgIData(oldp+43,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_24),32);
        bufp->chgIData(oldp+44,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_25),32);
        bufp->chgIData(oldp+45,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_26),32);
        bufp->chgIData(oldp+46,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_27),32);
        bufp->chgIData(oldp+47,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_28),32);
        bufp->chgIData(oldp+48,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_29),32);
        bufp->chgIData(oldp+49,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_30),32);
        bufp->chgIData(oldp+50,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_31),32);
        bufp->chgIData(oldp+51,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__casez_tmp),32);
        bufp->chgCData(oldp+52,(((0x00100073U == vlSelfRef.MiniRVSOC__DOT___rom_data)
                                  ? 0U : ((0U == vlSelfRef.MiniRVSOC__DOT___rom_data)
                                           ? 1U : (
                                                   ((0x73U 
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
                                                          << 1U))))))),8);
        bufp->chgIData(oldp+53,(((IData)(4U) + vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc)),32);
    }
    bufp->chgBit(oldp+54,(vlSelfRef.clock));
    bufp->chgBit(oldp+55,(vlSelfRef.reset));
    bufp->chgIData(oldp+56,(vlSelfRef.io_pc),32);
    bufp->chgIData(oldp+57,(vlSelfRef.io_inst),32);
    bufp->chgBit(oldp+58,(vlSelfRef.valid));
    bufp->chgIData(oldp+59,(vlSelfRef.raddr),32);
    bufp->chgIData(oldp+60,(vlSelfRef.waddr),32);
    bufp->chgIData(oldp+61,(vlSelfRef.wdata),32);
    bufp->chgCData(oldp+62,(vlSelfRef.wmask),8);
    bufp->chgBit(oldp+63,(vlSelfRef.wen));
    bufp->chgIData(oldp+64,(vlSelfRef.rdata),32);
    bufp->chgBit(oldp+65,((1U & ((~ (IData)(vlSelfRef.reset)) 
                                 & (~ ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_5) 
                                       | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_4)))))));
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
