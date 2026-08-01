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

SOC_BOOT_ADDR := $(shell sed -n 's/^CONFIG_MBASE_SOC=//p' $(MEMU_HOME)/.config 2>/dev/null)
SOC_BOOT_ADDR := $(if $(SOC_BOOT_ADDR),$(SOC_BOOT_ADDR),0x30000000)
LDFLAGS += --defsym=_pmem_start=$(SOC_BOOT_ADDR) --defsym=_entry_offset=0x0
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
	@$(OBJCOPY) -S --set-section-flags .bss=alloc,contents -O binary $(IMAGE).elf $(IMAGE).bin

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
