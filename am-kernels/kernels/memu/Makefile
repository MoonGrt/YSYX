# make ARCH=riscv32e-memu mainargs=/home/moon/ysyx/ysyx/am-kernels/tests/cpu-tests/build/hello-riscv32e-memu.bin

ARCH_SPLIT = $(subst -, ,$(ARCH))
RAW_ISA    = $(word 1,$(ARCH_SPLIT))
PLATFORM   = $(word 2,$(ARCH_SPLIT))

ifneq ($(filter riscv32 riscv32e,$(RAW_ISA)),)
ISA = riscv32
endif

ifneq ($(PLATFORM), memu)
$(error Only support with MEMU)
endif

EMU_HOME = $(MEMU_HOME)
TMPDEFCONFIG = tmp_defconfig
TMPDEFCONFIG_FILE = $(EMU_HOME)/configs/$(TMPDEFCONFIG)

EMU = $(PLATFORM)
BIN = $(ISA)-$(EMU)-interpreter-$(ARCH).bin

all:
	$(MAKE) save_config
	$(MAKE) build_am
	$(MAKE) restore_config
	$(MAKE) -C $(EMU_HOME) run IMG=$(EMU_HOME)/build/$(BIN)

save_config:
	$(MAKE) -C $(EMU_HOME) savedefconfig
	mv $(EMU_HOME)/configs/defconfig $(TMPDEFCONFIG_FILE)

build_am:
	$(MAKE) -C $(EMU_HOME) $(ISA)-am_defconfig
	$(MAKE) -C $(EMU_HOME) ARCH=$(ARCH) mainargs=$(mainargs) || ($(MAKE) restore_config; false)

restore_config:
	$(MAKE) -C $(EMU_HOME) ARCH=$(ARCH) $(TMPDEFCONFIG)
	rm $(TMPDEFCONFIG_FILE)

.PHONY: all save_config build_am restore_config
