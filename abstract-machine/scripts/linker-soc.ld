ENTRY(_start)

MEMORY {
  boot (rx) : ORIGIN = _pmem_start, LENGTH = 16M
  sram (rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
}

SECTIONS {
  . = ORIGIN(boot);
  .text : {
    *(entry)
    *(.text*)
  } > boot AT> boot
  etext = .;
  _etext = .;
  .rodata : {
    *(.rodata*)
  } > boot AT> boot

  .data ORIGIN(sram) : {
    _data_start = .;
    *(.data*)
    *(.sdata*)
    _data_end = .;
  } > sram AT> boot
  _data_load_start = LOADADDR(.data);
  edata = .;
  _data = .;

  .bss (NOLOAD) : {
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
    _bss_end = .;
  } > sram

  _heap_start = ALIGN(8);
  _stack_top = 0x0f001000;
  _stack_pointer = 0x0f002000;

  end = _heap_start;
  _end = _heap_start;

  ASSERT(LOADADDR(.data) + SIZEOF(.data) <= ORIGIN(boot) + LENGTH(boot),
         "boot image overflow")
  ASSERT(_heap_start <= _stack_top, "SRAM data/BSS overflow")
}
