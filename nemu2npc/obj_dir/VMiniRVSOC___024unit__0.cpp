// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VMiniRVSOC.h for the primary calling header

#include "VMiniRVSOC__pch.h"

extern "C" void ebreak(char code);

void VMiniRVSOC___024unit____Vdpiimwrap_ebreak_TOP____024unit(CData/*7:0*/ code) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        VMiniRVSOC___024unit____Vdpiimwrap_ebreak_TOP____024unit\n"); );
    // Body
    char code__Vcvt;
    code__Vcvt = code;
    ebreak(code__Vcvt);
}

extern "C" int pmem_read(int raddr);

void VMiniRVSOC___024unit____Vdpiimwrap_pmem_read_TOP____024unit(IData/*31:0*/ raddr, IData/*31:0*/ &pmem_read__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        VMiniRVSOC___024unit____Vdpiimwrap_pmem_read_TOP____024unit\n"); );
    // Body
    int raddr__Vcvt;
    raddr__Vcvt = raddr;
    int pmem_read__Vfuncrtn__Vcvt;
    pmem_read__Vfuncrtn__Vcvt = pmem_read(raddr__Vcvt);
    pmem_read__Vfuncrtn = (pmem_read__Vfuncrtn__Vcvt);
}

extern "C" void pmem_write(int waddr, char wmask, int wdata);

void VMiniRVSOC___024unit____Vdpiimwrap_pmem_write_TOP____024unit(IData/*31:0*/ waddr, CData/*7:0*/ wmask, IData/*31:0*/ wdata) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        VMiniRVSOC___024unit____Vdpiimwrap_pmem_write_TOP____024unit\n"); );
    // Body
    int waddr__Vcvt;
    waddr__Vcvt = waddr;
    char wmask__Vcvt;
    wmask__Vcvt = wmask;
    int wdata__Vcvt;
    wdata__Vcvt = wdata;
    pmem_write(waddr__Vcvt, wmask__Vcvt, wdata__Vcvt);
}
