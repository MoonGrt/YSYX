#ifndef SOC_H__
#define SOC_H__

#include <klib-macros.h>
#include ISA_H
#include <soc-device.h>

#define MROM_BASE  0x20000000u
#define MROM_END   0x20001000u
#ifndef FLASH_BASE
#define FLASH_BASE 0x30000000u
#endif
#ifndef FLASH_SIZE
#define FLASH_SIZE 0x1000000u
#endif
#ifndef SRAM_BASE
#define SRAM_BASE  0x0f000000u
#endif
#ifndef SRAM_SIZE
#define SRAM_SIZE  0x2000u
#endif
#ifndef PSRAM_BASE
#define PSRAM_BASE 0x80000000u
#endif
#ifndef PSRAM_SIZE
#define PSRAM_SIZE 0x400000u
#endif
#ifndef SDRAM_BASE
#define SDRAM_BASE 0xa0000000u
#endif
#ifndef SDRAM_SIZE
#define SDRAM_SIZE 0x2000000u
#endif
#define FLASH_END (FLASH_BASE + FLASH_SIZE)
#define SRAM_END  (SRAM_BASE + SRAM_SIZE)
#define PSRAM_END (PSRAM_BASE + PSRAM_SIZE)
#define SDRAM_END (SDRAM_BASE + SDRAM_SIZE)
#define VGA_END   (VGA_BASE + VGA_SIZE)

#define SOC_PADDR_SPACE \
  RANGE(MROM_BASE, MROM_END), \
  RANGE(FLASH_BASE, FLASH_END), \
  RANGE(SRAM_BASE, SRAM_END), \
  RANGE(PSRAM_BASE, PSRAM_END), \
  RANGE(SDRAM_BASE, SDRAM_END), \
  RANGE(UART_BASE, UART_BASE + UART_SIZE), \
  RANGE(SPI_BASE, SPI_BASE + SPI_SIZE), \
  RANGE(GPIO_BASE, GPIO_BASE + GPIO_SIZE), \
  RANGE(PS2_BASE, PS2_BASE + PS2_SIZE), \
  RANGE(VGA_BASE, VGA_END)

#define soc_trap(code) \
  asm volatile("mv a0, %0; ebreak" : : "r"(code))

typedef uintptr_t PTE;
#define PGSIZE 4096

#endif
