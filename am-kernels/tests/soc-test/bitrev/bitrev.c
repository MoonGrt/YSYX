#include <stdint.h>

#define SPI_BASE 0x10001000u
#define SPI_REG(off) (*(volatile uint32_t *)(SPI_BASE + (off)))
#define SPI_TX0 0x00
#define SPI_CTRL 0x10
#define SPI_DIV 0x14
#define SPI_SS 0x18

#define SPI_GO (1u << 8)
#define SPI_RX_NEG (1u << 9)
#define SPI_TX_NEG (1u << 10)
#define SPI_ASS (1u << 13)

int main(void) {
  SPI_REG(SPI_DIV) = 0;
  SPI_REG(SPI_SS) = 1u << 7;
  SPI_REG(SPI_TX0) = 0x00009600u;
  SPI_REG(SPI_CTRL) = SPI_ASS | SPI_TX_NEG | SPI_RX_NEG | SPI_GO | 16u;
  while (SPI_REG(SPI_CTRL) & SPI_GO);

  if ((SPI_REG(SPI_TX0) & 0xffu) != 0x69u)
    __asm__ volatile(".word 0");
  return 0;
}
