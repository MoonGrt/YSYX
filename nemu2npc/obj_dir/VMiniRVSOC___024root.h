// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VMiniRVSOC.h for the primary calling header

#ifndef VERILATED_VMINIRVSOC___024ROOT_H_
#define VERILATED_VMINIRVSOC___024ROOT_H_  // guard

#include "verilated.h"
class VMiniRVSOC___024unit;


class VMiniRVSOC__Syms;

class alignas(VL_CACHE_LINE_BYTES) VMiniRVSOC___024root final {
  public:
    // CELLS
    VMiniRVSOC___024unit* __PVT____024unit;

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clock,0,0);
        VL_IN8(reset,0,0);
        VL_IN8(valid,0,0);
        VL_IN8(wmask,7,0);
        VL_IN8(wen,0,0);
        CData/*0:0*/ MiniRVSOC__DOT__cpu__DOT___idStage_io_jumpen;
        CData/*0:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_memBen;
        CData/*0:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT___decoded_T_9;
        CData/*0:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_1;
        CData/*0:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_2;
        CData/*1:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_0;
        CData/*2:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__decoded_4;
        CData/*0:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_3;
        CData/*0:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_0;
        CData/*0:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_2;
        CData/*0:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_4;
        CData/*0:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT____VdfgRegularize_h208ff40b_0_5;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
        SData/*9:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN;
        VL_OUT(io_pc,31,0);
        VL_OUT(io_inst,31,0);
        VL_IN(raddr,31,0);
        VL_IN(waddr,31,0);
        VL_IN(wdata,31,0);
        VL_OUT(rdata,31,0);
        IData/*31:0*/ MiniRVSOC__DOT___ram_rdata;
        IData/*31:0*/ MiniRVSOC__DOT___rom_data;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT___exStage_io_exout;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT___ifStage_io_pcn;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT___byte_data_T;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT____Vcellinp__idStage__io_wb_data;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs1;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__io_rs2;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_0;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_1;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_2;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_3;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_4;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_5;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_6;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_7;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_8;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_9;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_10;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_11;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_12;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_13;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_14;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_15;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_16;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_17;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_18;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_19;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_20;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_21;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_22;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_23;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_24;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_25;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_26;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_27;
    };
    struct {
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_28;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_29;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_30;
        IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__regfile_31;
        IData/*31:0*/ __Vfunc_pmem_read__1__Vfuncout;
        IData/*31:0*/ __Vfunc_pmem_read__2__Vfuncout;
        IData/*31:0*/ __Vfunc_pmem_read__4__Vfuncout;
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
        VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    };

    // INTERNAL VARIABLES
    VMiniRVSOC__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    VMiniRVSOC___024root(VMiniRVSOC__Syms* symsp, const char* namep);
    ~VMiniRVSOC___024root();
    VL_UNCOPYABLE(VMiniRVSOC___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
