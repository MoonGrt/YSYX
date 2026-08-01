#ifndef SOC_H__
#define SOC_H__

#include <klib-macros.h>
#include ISA_H

#define MROM_BASE  0x20000000u
#define MROM_END   0x20001000u
#define SRAM_BASE  0x0f000000u
#define HEAP_END   0x0f001000u
#define SRAM_END   0x0f002000u
#define UART_BASE  0x10000000u

#define SOC_PADDR_SPACE \
  RANGE(MROM_BASE, MROM_END), \
  RANGE(SRAM_BASE, SRAM_END), \
  RANGE(UART_BASE, UART_BASE + 0x1000)

#define soc_trap(code) \
  asm volatile("mv a0, %0; ebreak" : : "r"(code))

typedef uintptr_t PTE;
#define PGSIZE 4096

#endif
