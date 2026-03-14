
#ifndef __ITRACE_H__
#define __ITRACE_H__





void trace_func_ret(paddr_t pc);
void trace_func_call(paddr_t pc, paddr_t target, bool is_tail);

void etrace_exec(uint32_t pc);

#endif