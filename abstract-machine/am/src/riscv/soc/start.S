.section entry, "ax"
.globl _start
.type _start, @function

_start:
  mv s0, zero
  la sp, _stack_pointer

  la a3, _soc_staged_load
  beqz a3, 8f

  /* FSBL: copy the small second-stage loader from flash to SRAM. */
  la t0, _ssbl_load_start
  la t1, _ssbl_start
  la t2, _ssbl_end
1:
  bgeu t1, t2, 2f
  lbu a0, 0(t0)
  sb a0, 0(t1)
  addi t0, t0, 1
  addi t1, t1, 1
  j 1b

2:
  la t0, _ssbl_start
  jalr zero, 0(t0)

8:
  la t0, _data_load_start
  la t1, _data_start
  la t2, _data_end
1:
  bgeu t1, t2, 2f
  lbu a0, 0(t0)
  sb a0, 0(t1)
  addi t0, t0, 1
  addi t1, t1, 1
  j 1b

2:
  la t1, _bss_start
  la t2, _bss_end
3:
  bgeu t1, t2, 4f
  sb zero, 0(t1)
  addi t1, t1, 1
  j 3b

4:
  call _trm_init

.size _start, . - _start

.section .ssbl, "ax"
.globl _ssbl_start
.type _ssbl_start, @function

_ssbl_start:
  /* SSBL: copy all initialized program sections to PSRAM. */
  la t0, _payload_load_start
  la t1, _payload_start
  la t2, _payload_end
3:
  bgeu t1, t2, 4f
  sub a1, t2, t1
  li a2, 4
  bltu a1, a2, 7f
  lw a0, 0(t0)
  sw a0, 0(t1)
  addi t0, t0, 4
  addi t1, t1, 4
  j 3b

7:
  lbu a0, 0(t0)
  sb a0, 0(t1)
  addi t0, t0, 1
  addi t1, t1, 1
  j 3b

4:
  la t1, _bss_start
  la t2, _bss_end
5:
  bgeu t1, t2, 6f
  sb zero, 0(t1)
  addi t1, t1, 1
  j 5b

6:
  la t0, _trm_init
  jalr ra, 0(t0)

.size _ssbl_start, . - _ssbl_start
