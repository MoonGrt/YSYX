ENTRY(_start)

MEMORY {
  mrom (rx)  : ORIGIN = 0x20000000, LENGTH = 4K
  sram (rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
}

SECTIONS {
  . = ORIGIN(mrom);
  .text : {
    *(entry)
    *(.text*)
  } > mrom AT> mrom
  etext = .;
  _etext = .;
  .rodata : {
    *(.rodata*)
  } > mrom AT> mrom

  .data ORIGIN(sram) : {
    _data_start = .;
    *(.data*)
    *(.sdata*)
    _data_end = .;
  } > sram AT> mrom
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

  ASSERT(LOADADDR(.data) + SIZEOF(.data) <= ORIGIN(mrom) + LENGTH(mrom),
         "MROM image overflow")
  ASSERT(_heap_start <= _stack_top, "SRAM data/BSS overflow")
}
