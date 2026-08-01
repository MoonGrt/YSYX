#include <stdint.h>

#define FLASH_BASE 0x30000000u

int main(void) {
  volatile const uint32_t *flash = (volatile const uint32_t *)FLASH_BASE;

  if (flash[0] != 0x00000413u)
    __asm__ volatile(".word 0");
  return 0;
}
