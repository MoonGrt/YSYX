ENTRY(_start)

MEMORY {
  flash (rx)  : ORIGIN = _soc_flash_base, LENGTH = _soc_flash_size
  sram (rwx)  : ORIGIN = _soc_sram_base, LENGTH = _soc_sram_size
  sdram (rwx) : ORIGIN = _soc_sdram_base, LENGTH = _soc_sdram_size
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

  .text ORIGIN(sdram) :
      AT(ALIGN(LOADADDR(.ssbl) + SIZEOF(.ssbl), 0x1000)) {
    _payload_start = .;
    *(.text*)
    etext = .;
    _etext = .;
  } > sdram
  _payload_load_start = LOADADDR(.text);

  .rodata ALIGN(8) :
      AT(ALIGN(LOADADDR(.text) + SIZEOF(.text), 8)) {
    *(.rodata*)
    *(.srodata*)
  } > sdram
  PROVIDE(_data_extra_load_end = LOADADDR(.rodata) + SIZEOF(.rodata));
  PROVIDE(_data_extra_vma_end = .);

  .data _data_extra_vma_end : AT(_data_extra_load_end) {
    _data_start = .;
    *(.data*)
    *(.sdata*)
    _data_end = .;
    _payload_end = .;
  } > sdram
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
  } > sdram

  _heap_start = ALIGN(8);
  _heap_end = ORIGIN(sdram) + LENGTH(sdram);
  _stack_top = ORIGIN(sram) + LENGTH(sram) / 2;
  _stack_pointer = ORIGIN(sram) + LENGTH(sram);
  end = _heap_start;
  _end = _heap_start;

  ASSERT(LOADADDR(.data) + SIZEOF(.data) <= ORIGIN(flash) + LENGTH(flash),
         "flash image overflow")
  ASSERT(SIZEOF(.ssbl) <= LENGTH(sram), "SSBL does not fit in SRAM")
  ASSERT(_heap_start <= ORIGIN(sdram) + LENGTH(sdram),
         "SDRAM data/BSS overflow")
}
