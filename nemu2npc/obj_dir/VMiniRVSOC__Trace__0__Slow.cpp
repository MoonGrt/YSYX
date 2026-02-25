// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "VMiniRVSOC__Syms.h"


VL_ATTR_COLD void VMiniRVSOC___024root__trace_init_sub__TOP__0(VMiniRVSOC___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root__trace_init_sub__TOP__0\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->pushPrefix("$rootio", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+55,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+56,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+57,0,"io_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+58,0,"io_inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+59,0,"valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+60,0,"raddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+61,0,"waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+62,0,"wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+63,0,"wmask",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+64,0,"wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+65,0,"rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("MiniRVSOC", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+55,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+56,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+57,0,"io_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+58,0,"io_inst",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("cpu", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+55,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+56,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+1,0,"io_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+2,0,"io_inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+3,0,"io_mem_we",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"io_mem_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"io_mem_mask",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+6,0,"io_mem_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+7,0,"io_mem_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("exStage", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+8,0,"io_rs1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+9,0,"io_rs2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"io_imm",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+11,0,"io_immen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"io_exout",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("idStage", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+55,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+56,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+2,0,"io_inst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+12,0,"io_wb_en",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+13,0,"io_wb_rd",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+14,0,"io_wb_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+8,0,"io_rs1",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+9,0,"io_rs2",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"io_imm",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+11,0,"io_immen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+13,0,"io_rd_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBit(c+66,0,"io_halt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+15,0,"io_jumpen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+16,0,"io_memBen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+17,0,"io_memRen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+3,0,"io_memWen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"io_regWen",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+18,0,"decoded_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+19,0,"decoded_4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+20,0,"regfile_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+21,0,"regfile_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+22,0,"regfile_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+23,0,"regfile_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+24,0,"regfile_4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+25,0,"regfile_5",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+26,0,"regfile_6",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+27,0,"regfile_7",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+28,0,"regfile_8",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+29,0,"regfile_9",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+30,0,"regfile_10",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+31,0,"regfile_11",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+32,0,"regfile_12",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+33,0,"regfile_13",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+34,0,"regfile_14",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+35,0,"regfile_15",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+36,0,"regfile_16",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+37,0,"regfile_17",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+38,0,"regfile_18",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+39,0,"regfile_19",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+40,0,"regfile_20",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+41,0,"regfile_21",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+42,0,"regfile_22",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+43,0,"regfile_23",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+44,0,"regfile_24",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+45,0,"regfile_25",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+46,0,"regfile_26",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+47,0,"regfile_27",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+48,0,"regfile_28",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+49,0,"regfile_29",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+50,0,"regfile_30",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+51,0,"regfile_31",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+52,0,"casez_tmp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+9,0,"casez_tmp_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"casez_tmp_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("trap", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+66,0,"trap",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+53,0,"code",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("ifStage", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+55,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+56,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+66,0,"io_halt",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+15,0,"io_jumpen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"io_jump",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+54,0,"io_pcn",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+1,0,"io_pc",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+1,0,"pc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("ram", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+3,0,"we",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+4,0,"addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+5,0,"mask",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+6,0,"wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+7,0,"rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("rom", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+1,0,"addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+2,0,"data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("PMem", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+59,0,"valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+60,0,"raddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+61,0,"waddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+62,0,"wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+63,0,"wmask",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+64,0,"wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+65,0,"rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->popPrefix();
}

VL_ATTR_COLD void VMiniRVSOC___024root__trace_init_top(VMiniRVSOC___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root__trace_init_top\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    VMiniRVSOC___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void VMiniRVSOC___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void VMiniRVSOC___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void VMiniRVSOC___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void VMiniRVSOC___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void VMiniRVSOC___024root__trace_register(VMiniRVSOC___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root__trace_register\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&VMiniRVSOC___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&VMiniRVSOC___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&VMiniRVSOC___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&VMiniRVSOC___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void VMiniRVSOC___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root__trace_const_0\n"); );
    // Body
    VMiniRVSOC___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VMiniRVSOC___024root*>(voidSelf);
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
}

VL_ATTR_COLD void VMiniRVSOC___024root__trace_full_0_sub_0(VMiniRVSOC___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void VMiniRVSOC___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root__trace_full_0\n"); );
    // Body
    VMiniRVSOC___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VMiniRVSOC___024root*>(voidSelf);
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VMiniRVSOC___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void VMiniRVSOC___024root__trace_full_0_sub_0(VMiniRVSOC___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VMiniRVSOC___024root__trace_full_0_sub_0\n"); );
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullIData(oldp+1,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc),32);
    bufp->fullIData(oldp+2,(vlSelfRef.MiniRVSOC__DOT___rom_data),32);
    bufp->fullBit(oldp+3,(((3U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4)) 
                           | (4U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4)))));
    bufp->fullIData(oldp+4,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__io_jump),32);
    bufp->fullCData(oldp+5,(((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_memBen)
                              ? (0x0000000fU & ((IData)(1U) 
                                                << 
                                                (3U 
                                                 & vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__io_jump)))
                              : 0x0000000fU)),8);
    bufp->fullIData(oldp+6,(((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_memBen)
                              ? (vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs2 
                                 << (0x00000018U & 
                                     (vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__io_jump 
                                      << 3U))) : vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs2)),32);
    bufp->fullIData(oldp+7,(vlSelfRef.MiniRVSOC__DOT___ram_rdata),32);
    bufp->fullIData(oldp+8,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs1),32);
    bufp->fullIData(oldp+9,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs2),32);
    bufp->fullIData(oldp+10,(((0U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_0))
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
    bufp->fullBit(oldp+11,(((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_2) 
                            | ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_1) 
                               | ((~ (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___decoded_T_9)) 
                                  & ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_0) 
                                     | (0U != (3U & 
                                               (- (IData)(
                                                          (0x37U 
                                                           == 
                                                           (0x0000007fU 
                                                            & vlSelfRef.MiniRVSOC__DOT___rom_data))))))))))));
    bufp->fullBit(oldp+12,((1U & ((~ (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_1)) 
                                  | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_2)))));
    bufp->fullCData(oldp+13,((0x0000001fU & (vlSelfRef.MiniRVSOC__DOT___rom_data 
                                             >> 7U))),5);
    bufp->fullIData(oldp+14,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data),32);
    bufp->fullBit(oldp+15,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__io_jumpen));
    bufp->fullBit(oldp+16,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_memBen));
    bufp->fullBit(oldp+17,(((1U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4)) 
                            | (2U == (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4)))));
    bufp->fullCData(oldp+18,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_0),2);
    bufp->fullCData(oldp+19,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4),3);
    bufp->fullIData(oldp+20,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_0),32);
    bufp->fullIData(oldp+21,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_1),32);
    bufp->fullIData(oldp+22,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_2),32);
    bufp->fullIData(oldp+23,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_3),32);
    bufp->fullIData(oldp+24,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_4),32);
    bufp->fullIData(oldp+25,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_5),32);
    bufp->fullIData(oldp+26,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_6),32);
    bufp->fullIData(oldp+27,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_7),32);
    bufp->fullIData(oldp+28,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_8),32);
    bufp->fullIData(oldp+29,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_9),32);
    bufp->fullIData(oldp+30,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_10),32);
    bufp->fullIData(oldp+31,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_11),32);
    bufp->fullIData(oldp+32,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_12),32);
    bufp->fullIData(oldp+33,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_13),32);
    bufp->fullIData(oldp+34,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_14),32);
    bufp->fullIData(oldp+35,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_15),32);
    bufp->fullIData(oldp+36,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_16),32);
    bufp->fullIData(oldp+37,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_17),32);
    bufp->fullIData(oldp+38,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_18),32);
    bufp->fullIData(oldp+39,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_19),32);
    bufp->fullIData(oldp+40,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_20),32);
    bufp->fullIData(oldp+41,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_21),32);
    bufp->fullIData(oldp+42,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_22),32);
    bufp->fullIData(oldp+43,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_23),32);
    bufp->fullIData(oldp+44,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_24),32);
    bufp->fullIData(oldp+45,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_25),32);
    bufp->fullIData(oldp+46,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_26),32);
    bufp->fullIData(oldp+47,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_27),32);
    bufp->fullIData(oldp+48,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_28),32);
    bufp->fullIData(oldp+49,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_29),32);
    bufp->fullIData(oldp+50,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_30),32);
    bufp->fullIData(oldp+51,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_31),32);
    bufp->fullIData(oldp+52,(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT__casez_tmp),32);
    bufp->fullCData(oldp+53,(((0x00100073U == vlSelfRef.MiniRVSOC__DOT___rom_data)
                               ? 0U : ((0U == vlSelfRef.MiniRVSOC__DOT___rom_data)
                                        ? 1U : (((0x73U 
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
    bufp->fullIData(oldp+54,(((IData)(4U) + vlSelfRef.MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc)),32);
    bufp->fullBit(oldp+55,(vlSelfRef.clock));
    bufp->fullBit(oldp+56,(vlSelfRef.reset));
    bufp->fullIData(oldp+57,(vlSelfRef.io_pc),32);
    bufp->fullIData(oldp+58,(vlSelfRef.io_inst),32);
    bufp->fullBit(oldp+59,(vlSelfRef.valid));
    bufp->fullIData(oldp+60,(vlSelfRef.raddr),32);
    bufp->fullIData(oldp+61,(vlSelfRef.waddr),32);
    bufp->fullIData(oldp+62,(vlSelfRef.wdata),32);
    bufp->fullCData(oldp+63,(vlSelfRef.wmask),8);
    bufp->fullBit(oldp+64,(vlSelfRef.wen));
    bufp->fullIData(oldp+65,(vlSelfRef.rdata),32);
    bufp->fullBit(oldp+66,((1U & ((~ (IData)(vlSelfRef.reset)) 
                                  & (~ ((IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_5) 
                                        | (IData)(vlSelfRef.MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_4)))))));
}
