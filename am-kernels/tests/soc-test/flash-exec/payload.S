  .section .text.flash_payload, "ax"
  .align 2
  .global flash_payload_start
  .global flash_payload_end

flash_payload_start:
  li t0, 0x10000000
  li a0, 'A'
  sb a0, 0(t0)
  ret
flash_payload_end:
