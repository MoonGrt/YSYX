# make ARCH=riscv32-nemu mainargs=/home/moon/ysyx/ysyx/am-kernels/kernels/typing-game/build/typing-game-riscv32-nemu.bin
# make ARCH=riscv32e-memu mainargs=/home/moon/ysyx/ysyx/am-kernels/tests/cpu-tests/build/hello-riscv32e-memu.bin
ARCH_SPLIT = $(subst -, ,$(ARCH))
RAW_ISA    = $(word 1,$(ARCH_SPLIT))
PLATFORM   = $(word 2,$(ARCH_SPLIT))

ifneq ($(filter riscv32 riscv32e,$(RAW_ISA)),)
ISA = riscv32
endif

# support nemu and memu
ifneq ($(filter $(PLATFORM),nemu memu),$(PLATFORM))
$(error Only support with NEMU or MEMU)
endif

# choose emulator home
ifeq ($(PLATFORM),nemu)
EMU_HOME = $(NEMU_HOME)
else ifeq ($(PLATFORM),memu)
EMU_HOME = $(MEMU_HOME)
endif

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
