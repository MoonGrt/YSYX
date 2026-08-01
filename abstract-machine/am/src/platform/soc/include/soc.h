#ifndef SOC_H__
#define SOC_H__

#include <klib-macros.h>
#include ISA_H

#define MROM_BASE  0x20000000u
#define MROM_END   0x20001000u
#define FLASH_BASE 0x30000000u
#define FLASH_END  0x31000000u
#define SRAM_BASE  0x0f000000u
#define SRAM_END   0x0f002000u
#define PSRAM_BASE 0x80000000u
#define PSRAM_END  0x80400000u
#define SDRAM_BASE 0xa0000000u
#define SDRAM_END  0xa2000000u
#define UART_BASE  0x10000000u

#define SOC_PADDR_SPACE \
  RANGE(MROM_BASE, MROM_END), \
  RANGE(FLASH_BASE, FLASH_END), \
  RANGE(SRAM_BASE, SRAM_END), \
  RANGE(PSRAM_BASE, PSRAM_END), \
  RANGE(SDRAM_BASE, SDRAM_END), \
  RANGE(UART_BASE, UART_BASE + 0x1000)

#define soc_trap(code) \
  asm volatile("mv a0, %0; ebreak" : : "r"(code))

typedef uintptr_t PTE;
#define PGSIZE 4096

#endif
