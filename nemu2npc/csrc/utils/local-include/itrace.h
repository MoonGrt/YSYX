
#ifndef __ITRACE_H__
#define __ITRACE_H__

#include <common.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include "../../../include/device/map.h"

void trace_inst(word_t pc, uint32_t inst);
void display_inst();
void trace_func_ret(paddr_t pc);
void trace_func_call(paddr_t pc, paddr_t target, bool is_tail);
void parse_elf(const char *exec_file);
void trace_dread(paddr_t addr, int len, IOMap *map);
void trace_dwrite(paddr_t addr, int len, word_t data, IOMap *map);
void display_pread(paddr_t addr, int len);
void display_pwrite(paddr_t addr, int len, word_t data);

#endif