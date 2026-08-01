#include <stdint.h>

#define SPI_BASE 0x10001000u
#define SPI_REG(off) (*(volatile uint32_t *)(SPI_BASE + (off)))
#define SPI_TX0 0x00
#define SPI_TX1 0x04
#define SPI_CTRL 0x10
#define SPI_DIV 0x14
#define SPI_SS 0x18

#define SPI_GO (1u << 8)
#define SPI_RX_NEG (1u << 9)
#define SPI_TX_NEG (1u << 10)
#define SPI_ASS (1u << 13)

static uint32_t bswap32(uint32_t value) {
  return ((value & 0x000000ffu) << 24) |
         ((value & 0x0000ff00u) << 8) |
         ((value & 0x00ff0000u) >> 8) |
         ((value & 0xff000000u) >> 24);
}

static uint32_t flash_read(uint32_t addr) {
  SPI_REG(SPI_DIV) = 0;
  SPI_REG(SPI_SS) = 1u;
  SPI_REG(SPI_TX0) = 0;
  SPI_REG(SPI_TX1) = 0x03000000u | (addr & 0x00ffffffu);
  SPI_REG(SPI_CTRL) =
      SPI_ASS | SPI_TX_NEG | SPI_GO | 64u;
  while (SPI_REG(SPI_CTRL) & SPI_GO);
  return bswap32(SPI_REG(SPI_TX0));
}

int main(void) {
  volatile uint32_t *xip = (volatile uint32_t *)0x30000000u;
  for (uint32_t addr = 0; addr < 32; addr += 4) {
    uint32_t actual = flash_read(addr);
    if (actual != xip[addr / 4])
      __asm__ volatile(".word 0");
  }
  return 0;
}
