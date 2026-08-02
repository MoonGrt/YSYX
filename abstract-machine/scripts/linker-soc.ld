ENTRY(_start)

MEMORY {
  boot (rx) : ORIGIN = _pmem_start, LENGTH = _soc_boot_size
  sram (rwx) : ORIGIN = _soc_sram_base, LENGTH = _soc_sram_size
}

SECTIONS {
  . = ORIGIN(boot);
  .text : {
    *(entry)
    *(.text*)
    _ssbl_load_start = .;
    *(.ssbl)
    _ssbl_end = .;
  } > boot AT> boot
  etext = .;
  _etext = .;

  .rodata : {
    *(.rodata*)
    *(.srodata*)
  } > boot AT> boot

  PROVIDE(_data_extra_vma_end = ORIGIN(sram));
  PROVIDE(_data_extra_load_end = LOADADDR(.rodata) + SIZEOF(.rodata));
  .data _data_extra_vma_end : AT(_data_extra_load_end) {
    _data_start = .;
    *(.data*)
    *(.sdata*)
    _data_end = .;
  } > sram
  _data_load_start = LOADADDR(.data);
  edata = .;
  _data = .;

  PROVIDE(_bss_extra_start = .);
  PROVIDE(_bss_extra_vma_end = .);
  _bss_start = _bss_extra_start;
  .bss _bss_extra_vma_end (NOLOAD) : {
    *(.bss*)
    *(.sbss*)
    *(.scommon)
    _bss_end = .;
  } > sram

  _heap_start = ALIGN(8);
  _stack_top = ORIGIN(sram) + LENGTH(sram) / 2;
  _stack_pointer = ORIGIN(sram) + LENGTH(sram);
  _heap_end = _stack_top;

  end = _heap_start;
  _end = _heap_start;
  _soc_staged_load = 0;
  PROVIDE(_payload_load_start = 0);
  PROVIDE(_payload_start = 0);
  PROVIDE(_payload_end = 0);

  ASSERT(LOADADDR(.data) + SIZEOF(.data) <= ORIGIN(boot) + LENGTH(boot),
         "boot image overflow")
  ASSERT(_heap_start <= _stack_top, "SRAM data/BSS overflow")
}
