// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VMiniRVSOC.h for the primary calling header

#include "VMiniRVSOC__pch.h"

extern "C" void rom_rdpi(int addr, int* data);

void VMiniRVSOC___024unit____Vdpiimwrap_rom_rdpi_TOP____024unit(IData/*31:0*/ addr, IData/*31:0*/ &data) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        VMiniRVSOC___024unit____Vdpiimwrap_rom_rdpi_TOP____024unit\n"); );
    // Body
    int addr__Vcvt;
    addr__Vcvt = addr;
    int data__Vcvt;
    rom_rdpi(addr__Vcvt, &data__Vcvt);
    data = (data__Vcvt);
}

extern "C" int ram_rdpi(int raddr);

void VMiniRVSOC___024unit____Vdpiimwrap_ram_rdpi_TOP____024unit(IData/*31:0*/ raddr, IData/*31:0*/ &ram_rdpi__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        VMiniRVSOC___024unit____Vdpiimwrap_ram_rdpi_TOP____024unit\n"); );
    // Body
    int raddr__Vcvt;
    raddr__Vcvt = raddr;
    int ram_rdpi__Vfuncrtn__Vcvt;
    ram_rdpi__Vfuncrtn__Vcvt = ram_rdpi(raddr__Vcvt);
    ram_rdpi__Vfuncrtn = (ram_rdpi__Vfuncrtn__Vcvt);
}

extern "C" void ram_wdpi(int waddr, int wdata, char wmask);

void VMiniRVSOC___024unit____Vdpiimwrap_ram_wdpi_TOP____024unit(IData/*31:0*/ waddr, IData/*31:0*/ wdata, CData/*7:0*/ wmask) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        VMiniRVSOC___024unit____Vdpiimwrap_ram_wdpi_TOP____024unit\n"); );
    // Body
    int waddr__Vcvt;
    waddr__Vcvt = waddr;
    int wdata__Vcvt;
    wdata__Vcvt = wdata;
    char wmask__Vcvt;
    wmask__Vcvt = wmask;
    ram_wdpi(waddr__Vcvt, wdata__Vcvt, wmask__Vcvt);
}

extern "C" void ebreak(char code);

void VMiniRVSOC___024unit____Vdpiimwrap_ebreak_TOP____024unit(CData/*7:0*/ code) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        VMiniRVSOC___024unit____Vdpiimwrap_ebreak_TOP____024unit\n"); );
    // Body
    char code__Vcvt;
    code__Vcvt = code;
    ebreak(code__Vcvt);
}
