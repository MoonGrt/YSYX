#include <stdint.h>
#include <soc-device.h>

#define GPIO_LED    (*(volatile uint16_t *)(GPIO_BASE + 0x0))
#define GPIO_SWITCH (*(volatile uint16_t *)(GPIO_BASE + 0x4))
#define GPIO_SEG    (*(volatile uint32_t *)(GPIO_BASE + 0x8))
#define PASSWORD    0x000fu

static void delay(uint32_t cycles) {
  uint32_t start, now;
  asm volatile("csrr %0, mcycle" : "=r"(start));
  do {
    asm volatile("csrr %0, mcycle" : "=r"(now));
  } while ((uint32_t)(now - start) < cycles);
}

static uint32_t decimal_to_bcd(uint32_t value) {
  uint32_t bcd = 0;
  for (int digit = 0; digit < 8; digit++) {
    bcd |= (value % 10) << (digit * 4);
    value /= 10;
  }
  return bcd;
}

int main(void) {
  GPIO_LED = 0;
  GPIO_SEG = 0;
  while (GPIO_SWITCH != PASSWORD);

  uint32_t student_id;
  asm volatile("csrr %0, marchid" : "=r"(student_id));
  GPIO_SEG = decimal_to_bcd(student_id);

  uint16_t led = 1;
  while (1) {
    GPIO_LED = led;
    delay(100000);
    led = led == 0x8000 ? 1 : (uint16_t)(led << 1);
  }
}
