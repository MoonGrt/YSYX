#ifndef SOC_DEVICE_H__
#define SOC_DEVICE_H__

#ifndef UART_BASE
#define UART_BASE  0x10000000u
#endif
#ifndef UART_SIZE
#define UART_SIZE  0x1000u
#endif
#ifndef SPI_BASE
#define SPI_BASE   0x10001000u
#endif
#ifndef SPI_SIZE
#define SPI_SIZE   0x1000u
#endif
#ifndef GPIO_BASE
#define GPIO_BASE  0x10002000u
#endif
#ifndef GPIO_SIZE
#define GPIO_SIZE  0x10u
#endif
#ifndef PS2_BASE
#define PS2_BASE   0x10011000u
#endif
#ifndef PS2_SIZE
#define PS2_SIZE   0x8u
#endif
#ifndef VGA_BASE
#define VGA_BASE   0x21000000u
#endif
#ifndef VGA_SIZE
#define VGA_SIZE   0x200000u
#endif

#endif
