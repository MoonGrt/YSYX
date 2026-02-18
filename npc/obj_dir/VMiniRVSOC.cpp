// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VMiniRVSOC__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

VMiniRVSOC::VMiniRVSOC(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VMiniRVSOC__Syms(contextp(), _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , reset{vlSymsp->TOP.reset}
    , __PVT____024unit{vlSymsp->TOP.__PVT____024unit}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

VMiniRVSOC::VMiniRVSOC(const char* _vcname__)
    : VMiniRVSOC(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VMiniRVSOC::~VMiniRVSOC() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VMiniRVSOC___024root___eval_debug_assertions(VMiniRVSOC___024root* vlSelf);
#endif  // VL_DEBUG
void VMiniRVSOC___024root___eval_static(VMiniRVSOC___024root* vlSelf);
void VMiniRVSOC___024root___eval_initial(VMiniRVSOC___024root* vlSelf);
void VMiniRVSOC___024root___eval_settle(VMiniRVSOC___024root* vlSelf);
void VMiniRVSOC___024root___eval(VMiniRVSOC___024root* vlSelf);

void VMiniRVSOC::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VMiniRVSOC::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VMiniRVSOC___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VMiniRVSOC___024root___eval_static(&(vlSymsp->TOP));
        VMiniRVSOC___024root___eval_initial(&(vlSymsp->TOP));
        VMiniRVSOC___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VMiniRVSOC___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VMiniRVSOC::eventsPending() { return false; }

uint64_t VMiniRVSOC::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VMiniRVSOC::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VMiniRVSOC___024root___eval_final(VMiniRVSOC___024root* vlSelf);

VL_ATTR_COLD void VMiniRVSOC::final() {
    VMiniRVSOC___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VMiniRVSOC::hierName() const { return vlSymsp->name(); }
const char* VMiniRVSOC::modelName() const { return "VMiniRVSOC"; }
unsigned VMiniRVSOC::threads() const { return 1; }
void VMiniRVSOC::prepareClone() const { contextp()->prepareClone(); }
void VMiniRVSOC::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> VMiniRVSOC::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void VMiniRVSOC___024root__trace_decl_types(VerilatedVcd* tracep);

void VMiniRVSOC___024root__trace_init_top(VMiniRVSOC___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    VMiniRVSOC___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VMiniRVSOC___024root*>(voidSelf);
    VMiniRVSOC__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    VMiniRVSOC___024root__trace_decl_types(tracep);
    VMiniRVSOC___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void VMiniRVSOC___024root__trace_register(VMiniRVSOC___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void VMiniRVSOC::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'VMiniRVSOC::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    VMiniRVSOC___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
