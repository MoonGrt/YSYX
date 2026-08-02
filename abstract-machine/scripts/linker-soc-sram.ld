ENTRY(_start)

MEMORY {
  flash (rx) : ORIGIN = _soc_flash_base, LENGTH = _soc_flash_size
  sram (rwx) : ORIGIN = _soc_sram_base, LENGTH = _soc_sram_size
  psram (rwx): ORIGIN = _soc_psram_base, LENGTH = _soc_psram_size
}

SECTIONS {
  _soc_staged_load = 1;
  .boot ORIGIN(flash) : { *(entry) } > flash AT> flash

  .ssbl ORIGIN(sram) : {
    _ssbl_start = .;
    KEEP(*(.ssbl))
    _ssbl_end = .;
  } > sram AT> flash
  _ssbl_load_start = LOADADDR(.ssbl);

  .text ORIGIN(sram) + 0x100 :
      AT(ALIGN(LOADADDR(.ssbl) + SIZEOF(.ssbl), 0x1000)) {
    _payload_start = .;
    *(.text*)
    etext = .;
    _etext = .;
  } > sram
  _payload_load_start = LOADADDR(.text);

  .rodata ALIGN(8) :
      AT(ALIGN(LOADADDR(.text) + SIZEOF(.text), 8)) {
    *(.rodata*)
    *(.srodata*)
  } > sram

  PROVIDE(_data_extra_vma_end = .);
  PROVIDE(_data_extra_load_end = LOADADDR(.rodata) + SIZEOF(.rodata));
  .data _data_extra_vma_end : AT(_data_extra_load_end) {
    _data_start = .;
    *(.data*)
    *(.sdata*)
    _data_end = .;
    _payload_end = .;
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
  _heap_end = ORIGIN(psram) + LENGTH(psram);
  _stack_top = ORIGIN(sram) + LENGTH(sram) / 2;
  _stack_pointer = ORIGIN(sram) + LENGTH(sram);

  end = _heap_start;
  _end = _heap_start;

  ASSERT(SIZEOF(.ssbl) <= 0x100, "SSBL exceeds its SRAM slot")
  ASSERT(_bss_end <= _stack_top, "SRAM test image collides with stack")
  ASSERT(LOADADDR(.data) + SIZEOF(.data) <= ORIGIN(flash) + LENGTH(flash),
         "flash image overflow")
}
