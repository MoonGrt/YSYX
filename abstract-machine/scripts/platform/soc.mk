AM_SRCS := platform/soc/trm.c \
           platform/soc/ioe/ioe.c \
           platform/soc/mpe.c

CFLAGS += -fdata-sections -ffunction-sections
CFLAGS += -I$(AM_HOME)/am/src/platform/soc/include

ifeq ($(SOC_LOAD),sram)
LDSCRIPTS += $(AM_HOME)/scripts/linker-soc-sram.ld
else ifeq ($(SOC_LOAD),psram)
LDSCRIPTS += $(AM_HOME)/scripts/linker-soc-psram.ld
else ifeq ($(SOC_LOAD),sdram)
LDSCRIPTS += $(AM_HOME)/scripts/linker-soc-sdram.ld
else
LDSCRIPTS += $(AM_HOME)/scripts/linker-soc.ld
endif

soc_config = $(or $(shell sed -n 's/^CONFIG_$(1)=//p' $(MEMU_HOME)/.config 2>/dev/null),$(2))
SOC_BOOT_ADDR  := $(call soc_config,MBASE_SOC,0x30000000)
SOC_BOOT_SIZE  := $(call soc_config,MSIZE,0x1000000)
SOC_SRAM_BASE  := $(call soc_config,SOC_SRAM_BASE,0x0f000000)
SOC_SRAM_SIZE  := $(call soc_config,SOC_SRAM_SIZE,0x2000)
SOC_FLASH_BASE := $(call soc_config,SOC_FLASH_BASE,0x30000000)
SOC_FLASH_SIZE := $(call soc_config,SOC_FLASH_SIZE,0x1000000)
SOC_PSRAM_BASE := $(call soc_config,SOC_PSRAM_BASE,0x80000000)
SOC_PSRAM_SIZE := $(call soc_config,SOC_PSRAM_SIZE,0x400000)
SOC_SDRAM_BASE := $(call soc_config,SOC_SDRAM_BASE,0xa0000000)
SOC_SDRAM_SIZE := $(call soc_config,SOC_SDRAM_SIZE,0x2000000)
SOC_UART_BASE  := $(call soc_config,SOC_UART_MMIO,0x10000000)
SOC_UART_SIZE  := $(call soc_config,SOC_UART_SIZE,0x1000)
SOC_SPI_BASE   := $(call soc_config,SOC_SPI_MMIO,0x10001000)
SOC_SPI_SIZE   := $(call soc_config,SOC_SPI_SIZE,0x1000)
SOC_GPIO_BASE  := $(call soc_config,SOC_GPIO_MMIO,0x10002000)
SOC_GPIO_SIZE  := $(call soc_config,SOC_GPIO_SIZE,0x10)
SOC_PS2_BASE   := $(call soc_config,SOC_PS2_MMIO,0x10011000)
SOC_PS2_SIZE   := $(call soc_config,SOC_PS2_SIZE,0x8)
SOC_VGA_BASE   := $(call soc_config,SOC_VGA_ADDR,0x21000000)
SOC_VGA_SIZE   := $(call soc_config,SOC_VGA_SIZE,0x200000)
CFLAGS += -DUART_BASE=$(SOC_UART_BASE) -DUART_SIZE=$(SOC_UART_SIZE)
CFLAGS += -DSPI_BASE=$(SOC_SPI_BASE) -DSPI_SIZE=$(SOC_SPI_SIZE)
CFLAGS += -DGPIO_BASE=$(SOC_GPIO_BASE) -DGPIO_SIZE=$(SOC_GPIO_SIZE)
CFLAGS += -DPS2_BASE=$(SOC_PS2_BASE) -DPS2_SIZE=$(SOC_PS2_SIZE)
CFLAGS += -DVGA_BASE=$(SOC_VGA_BASE) -DVGA_SIZE=$(SOC_VGA_SIZE)
CFLAGS += -DSRAM_BASE=$(SOC_SRAM_BASE) -DSRAM_SIZE=$(SOC_SRAM_SIZE)
CFLAGS += -DFLASH_BASE=$(SOC_FLASH_BASE) -DFLASH_SIZE=$(SOC_FLASH_SIZE)
CFLAGS += -DPSRAM_BASE=$(SOC_PSRAM_BASE) -DPSRAM_SIZE=$(SOC_PSRAM_SIZE)
CFLAGS += -DSDRAM_BASE=$(SOC_SDRAM_BASE) -DSDRAM_SIZE=$(SOC_SDRAM_SIZE)
LDFLAGS += --defsym=_pmem_start=$(SOC_BOOT_ADDR) --defsym=_entry_offset=0x0
LDFLAGS += --defsym=_soc_boot_size=$(SOC_BOOT_SIZE)
LDFLAGS += --defsym=_soc_sram_base=$(SOC_SRAM_BASE) --defsym=_soc_sram_size=$(SOC_SRAM_SIZE)
LDFLAGS += --defsym=_soc_flash_base=$(SOC_FLASH_BASE) --defsym=_soc_flash_size=$(SOC_FLASH_SIZE)
LDFLAGS += --defsym=_soc_psram_base=$(SOC_PSRAM_BASE) --defsym=_soc_psram_size=$(SOC_PSRAM_SIZE)
LDFLAGS += --defsym=_soc_sdram_base=$(SOC_SDRAM_BASE) --defsym=_soc_sdram_size=$(SOC_SDRAM_SIZE)
LDFLAGS += --gc-sections -e _start
MEMUFLAGS += --log=$(shell dirname $(IMAGE).elf)/memu-log.txt
MEMUFLAGS += --ftrace=$(shell dirname $(IMAGE).elf)/memu-ftrace.txt
MEMUFLAGS += --elf=$(IMAGE).elf

MAINARGS_MAX_LEN = 64
MAINARGS_PLACEHOLDER = the_insert-arg_rule_in_Makefile_will_insert_mainargs_here
CFLAGS += -DMAINARGS_MAX_LEN=$(MAINARGS_MAX_LEN) -DMAINARGS_PLACEHOLDER=$(MAINARGS_PLACEHOLDER)

insert-arg: image
	@python $(AM_HOME)/tools/insert-arg.py $(IMAGE).bin $(MAINARGS_MAX_LEN) $(MAINARGS_PLACEHOLDER) "$(mainargs)"

image: image-dep
	@$(OBJDUMP) -d $(IMAGE).elf > $(IMAGE).asm
	@echo + OBJCOPY "->" $(IMAGE_REL).bin
	@$(OBJCOPY) -S -O binary $(IMAGE).elf $(IMAGE).bin

# Build only the application's _start entry, without AM or its linker script.
BARE_IMAGE  := $(WORK_DIR)/build/$(NAME)-bare
BARE_ELF    := $(BARE_IMAGE).elf
BARE_BIN    := $(BARE_IMAGE).bin
BARE_CFLAGS := -DBARE_METAL -Os -nostdlib -nostartfiles -ffreestanding \
               -march=rv32e_zicsr -mabi=ilp32e
BARE_LDFLAGS := -Wl,-Ttext=0x20000000 -Wl,-e,_start

bare:
	@mkdir -p $(WORK_DIR)/build
	$(CC) $(BARE_CFLAGS) $(BARE_LDFLAGS) $(realpath $(SRCS)) -o $(BARE_ELF)
	$(OBJCOPY) -j .text -O binary $(BARE_ELF) $(BARE_BIN)
	$(OBJCOPY) -O ihex $(BARE_ELF) $(BARE_IMAGE).hex
	$(OBJCOPY) -O verilog $(BARE_ELF) $(BARE_IMAGE).v
	$(OBJDUMP) -d -M no-aliases -S $(BARE_ELF) > $(BARE_IMAGE).s
	od -An -v -w4 -t x4 $(BARE_BIN) | tr -d ' ' > $(BARE_IMAGE).memhex

bare-run: bare
	$(MAKE) -C $(MEMU_HOME) ISA=$(ISA) run \
		IMG=$(BARE_BIN) \
		ARGS="--log=$(BARE_IMAGE)-memu-log.txt --ftrace=$(BARE_IMAGE)-memu-ftrace.txt --elf=$(BARE_ELF)"

run: insert-arg
	$(MAKE) -C $(MEMU_HOME) ISA=$(ISA) NO_DIFF=$(NO_DIFF) run ARGS="$(MEMUFLAGS)" IMG=$(IMAGE).bin

run-sdb: insert-arg
	$(MAKE) -C $(MEMU_HOME) ISA=$(ISA) run-sdb ARGS="$(MEMUFLAGS)" IMG=$(IMAGE).bin

wave: run
	$(MAKE) -C $(MEMU_HOME) wave

gdb: insert-arg
	$(MAKE) -C $(MEMU_HOME) ISA=$(ISA) gdb ARGS="$(MEMUFLAGS)" IMG=$(IMAGE).bin

.PHONY: insert-arg bare bare-run
