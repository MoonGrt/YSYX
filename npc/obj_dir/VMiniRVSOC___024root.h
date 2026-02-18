// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VMiniRVSOC.h for the primary calling header

#ifndef VERILATED_VMINIRVSOC___024ROOT_H_
#define VERILATED_VMINIRVSOC___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_cov.h"
class VMiniRVSOC___024unit;


class VMiniRVSOC__Syms;

class alignas(VL_CACHE_LINE_BYTES) VMiniRVSOC___024root final {
  public:
    // CELLS
    VMiniRVSOC___024unit* __PVT____024unit;

    // DESIGN SPECIFIC STATE
    VL_IN8(clock,0,0);
    VL_IN8(reset,0,0);
    CData/*0:0*/ MiniRVSOC__DOT____Vtogcov__clock;
    CData/*0:0*/ MiniRVSOC__DOT____Vtogcov__reset;
    CData/*0:0*/ MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_we;
    CData/*0:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT____Vtogcov__io_jalr;
    CData/*0:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__trap__DOT____Vtogcov__trap;
    CData/*7:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT__trap__DOT____Vtogcov__code;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
    IData/*31:0*/ MiniRVSOC__DOT___rom_data;
    IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT___exStage_io_pc_next;
    IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT___idStage_io_imm;
    IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_pc;
    IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_instr;
    IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_addr;
    IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT____Vtogcov__io_mem_wdata;
    IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__ifStage__DOT__pc;
    IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__ifStage__DOT____Vtogcov__io_pc_next;
    IData/*31:0*/ MiniRVSOC__DOT__cpu__DOT__idStage__DOT___GEN_0;
    IData/*31:0*/ MiniRVSOC__DOT__ram__DOT__rdata;
    IData/*31:0*/ MiniRVSOC__DOT__ram__DOT____Vtogcov__rdata;
    IData/*31:0*/ __Vfunc_ram_rdpi__1__Vfuncout;
    IData/*31:0*/ __Vfunc_ram_rdpi__2__Vfuncout;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;

    // INTERNAL VARIABLES
    VMiniRVSOC__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    VMiniRVSOC___024root(VMiniRVSOC__Syms* symsp, const char* namep);
    ~VMiniRVSOC___024root();
    VL_UNCOPYABLE(VMiniRVSOC___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
    void __vlCoverToggleInsert(int begin, int end, bool ranged, uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp);
};


#endif  // guard
