ENTRY(_start)
PHDRS { text PT_LOAD; data PT_LOAD; }

SECTIONS {
  /* The boot image is read from the SoC MROM. */
  . = _pmem_start + _entry_offset;
  .text : {
    *(entry)
    *(.text*)
  } : text
  etext = .;
  _etext = .;
  .rodata : {
    *(.rodata*)
  }
  .data : {
    *(.data*)
  } : data
  edata = .;
  _data = .;
  .bss : {
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  }

  /*
   * ysyxSoC provides 8 KiB of writable SRAM at 0x0f000000.
   * Grow the stack down from its upper boundary.
   */
  _stack_top = 0x0f000000;
  _stack_pointer = 0x0f002000;

  end = .;
  _end = .;
  _heap_start = ALIGN(0x1000);
}
