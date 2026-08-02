GTKWAVE   ?= gtkwave
VERILATOR ?= verilator
MILL_JOBS ?= $(BUILD_JOBS)

ifeq ($(CONFIG_WAVE_VCD),y)
VERILATOR_CFLAGS += --trace
endif
ifeq ($(CONFIG_WAVE_FST),y)
VERILATOR_CFLAGS += --trace-fst
endif
VERILATOR_HOST_CFLAGS := -O3 \
  $(if $(CONFIG_CC_LTO),-flto,) \
  $(if $(CONFIG_CC_NATIVE),-march=native,) \
  $(if $(CONFIG_CC_DEBUG),-ggdb3,)
VERILATOR_CFLAGS += -cc -MMD -cc -O3 --x-assign fast --x-initial fast \
                    --timescale "1ns/1ns" --no-timing --autoflush \
                    -CFLAGS "$(VERILATOR_HOST_CFLAGS)" \
                    -LDFLAGS "$(VERILATOR_HOST_CFLAGS)" -j $(BUILD_JOBS)
ifeq ($(CONFIG_SOC_FAST_SDRAM),y)
VERILATOR_CFLAGS += -DFAST_SDRAM
endif
ifeq ($(CONFIG_SOC_FAST_PSRAM),y)
VERILATOR_CFLAGS += -DFAST_PSRAM
endif
ifeq ($(CONFIG_SOC_FAST_FLASH),y)
VERILATOR_CFLAGS += -DFAST_FLASH
endif
VERILATOR_CFLAGS += -I$(MEMU_HOME)/vsrc/perip/uart16550/rtl
VERILATOR_CFLAGS += -I$(MEMU_HOME)/vsrc/perip/spi/rtl

RTL_DIR   := $(BUILD_DIR)/rtl
VSRCS_DIR := $(MEMU_HOME)/vsrc
VBUILD    := $(BUILD_DIR)/verilated

PRJ        := chisel
SCALA_DIR  := $(PRJ)/src
SCALA_SRCS := $(shell find $(SCALA_DIR) -name "*.scala")

ifeq ($(CONFIG_SOC),y)
	ifeq ($(CONFIG_CORE_RV32E),y)
	TOP := SoC
	endif
else
	ifeq ($(CONFIG_CORE_MINIRV),y)
	TOP := MiniRV
	endif
	ifeq ($(CONFIG_CORE_RV32E),y)
	TOP := Riscv32E
	endif
endif

CONFIG    := .config
VTOP      := $(TOP)Top
RTL_OBJS  := $(RTL_DIR)/$(VTOP).sv
RTL_FINAL := $(RTL_DIR)/$(VTOP).v
VSRCS      = $(RTL_FINAL) \
             $(shell find $(VSRCS_DIR) -name "*.v")
VLIB      := $(VBUILD)/libV$(VTOP).a
WAVE_FILE := $(BUILD_DIR)/wave.vcd

ifeq ($(CONFIG_NVBOARD),y)
NVBOARD_HOME := $(MEMU_HOME)/../thirdpartys/nvboard
NVBOARD_NXDC := $(MEMU_HOME)/constr/SoCTop.nxdc
NVBOARD_BIND := $(BUILD_DIR)/nvboard-auto-bind.cc
CXXSRC += $(NVBOARD_BIND)
INC_PATH += $(NVBOARD_HOME)/usr/include
include $(NVBOARD_HOME)/scripts/nvboard.mk
# nvboard.mk targets a standalone example and puts SDL libraries in LDFLAGS.
# MEMU links static libraries later, so keep the dependent SDL libraries after
# nvboard.a to satisfy the linker's left-to-right symbol resolution.
LDFLAGS := $(filter-out $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf,$(LDFLAGS))
LIBS += $(NVBOARD_ARCHIVE) $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf

$(NVBOARD_BIND): $(NVBOARD_NXDC) $(NVBOARD_HOME)/scripts/auto_pin_bind.py
	@mkdir -p $(dir $@)
	NVBOARD_HOME=$(NVBOARD_HOME) python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $< $@

$(VLIB): $(NVBOARD_ARCHIVE)
# The generated binding includes VSoCTop.h, which is emitted while building
# VLIB. Keep its object behind that generation step during parallel builds.
$(OBJ_DIR)/$(NVBOARD_BIND:.cc=.o): $(VLIB)
endif

ifeq ($(CONFIG_SOC_BOOT_MROM),y)
SOC_BOOT := mrom
else
SOC_BOOT := flash
endif

SOC_DEVICE_ENV := \
  MEMU_SOC_SRAM_BASE=$(CONFIG_SOC_SRAM_BASE) MEMU_SOC_SRAM_SIZE=$(CONFIG_SOC_SRAM_SIZE) \
  MEMU_SOC_MROM_BASE=$(CONFIG_SOC_MROM_BASE) MEMU_SOC_MROM_SIZE=$(CONFIG_SOC_MROM_SIZE) \
  MEMU_SOC_UART_BASE=$(CONFIG_SOC_UART_MMIO) MEMU_SOC_UART_SIZE=$(CONFIG_SOC_UART_SIZE) \
  MEMU_SOC_SPI_BASE=$(CONFIG_SOC_SPI_MMIO) MEMU_SOC_SPI_SIZE=$(CONFIG_SOC_SPI_SIZE) \
  MEMU_SOC_GPIO_BASE=$(CONFIG_SOC_GPIO_MMIO) MEMU_SOC_GPIO_SIZE=$(CONFIG_SOC_GPIO_SIZE) \
  MEMU_SOC_PS2_BASE=$(CONFIG_SOC_PS2_MMIO) MEMU_SOC_PS2_SIZE=$(CONFIG_SOC_PS2_SIZE) \
  MEMU_SOC_VGA_BASE=$(CONFIG_SOC_VGA_ADDR) MEMU_SOC_VGA_SIZE=$(CONFIG_SOC_VGA_SIZE) \
  MEMU_SOC_FLASH_BASE=$(CONFIG_SOC_FLASH_BASE) MEMU_SOC_FLASH_SIZE=$(CONFIG_SOC_FLASH_SIZE) \
  MEMU_SOC_PSRAM_BASE=$(CONFIG_SOC_PSRAM_BASE) MEMU_SOC_PSRAM_SIZE=$(CONFIG_SOC_PSRAM_SIZE) \
  MEMU_SOC_SDRAM_BASE=$(CONFIG_SOC_SDRAM_BASE) MEMU_SOC_SDRAM_SIZE=$(CONFIG_SOC_SDRAM_SIZE)

# exec.cc includes the Verilator-generated top header.  This dependency is
# required once the C/C++ objects and RTL library are allowed to build in
# parallel.
$(OBJ_DIR)/csrc/core/riscv32/exec.o: $(VLIB)

VROOT    := /usr/local/share/verilator
INC_PATH += $(VROOT)/include
INC_PATH += $(VROOT)/include/vltstd
INC_PATH += $(VBUILD)

# Firtool version
# ENABLE_FIRTOOL_PATCH ?= y
FIRTOOL_VERSION = 1.105.0
FIRTOOL_PATCH_DIR = $(MEMU_HOME)/scripts/firtool

$(RTL_FINAL): $(SCALA_SRCS) $(CONFIG)
	$(call git_commit, "generate verilog")
	@echo "+ CHISEL  (scala -> verilog)"
	@mkdir -p $(RTL_DIR)
ifeq ($(ENABLE_FIRTOOL_PATCH),y)
# Replace firtool with a newer version
# TODO: This can be removed after chisel publishes a new version
	@$(MEMU_HOME)/scripts/firtool-patch.sh \
		$(FIRTOOL_VERSION) $(FIRTOOL_PATCH_DIR)
	$(SOC_DEVICE_ENV) \
	CHISEL_FIRTOOL_PATH=$(FIRTOOL_PATCH_DIR)/firtool-$(FIRTOOL_VERSION)/bin \
	MEMU_SOC_BOOT=$(SOC_BOOT) mill -i --jobs $(MILL_JOBS) $(PRJ).runMain $(VTOP) --target-dir $(RTL_DIR)
else
	$(SOC_DEVICE_ENV) MEMU_SOC_BOOT=$(SOC_BOOT) mill -i --jobs $(MILL_JOBS) $(PRJ).runMain $(VTOP) --target-dir $(RTL_DIR)
endif
	@echo "+ SV2V"
	@mv $(RTL_OBJS) $@
	sed -i -E \
		-e 's/_(aw|ar|w|r|b)_(bits_)?/_\1/g' \
		-e 's/_(in|out)_bits_/_\1_/g' \
		$@
	sed -i '/firrtl_black_box_resource_files.f/, $$d' $@

rtl: $(RTL_FINAL)
.PHONY: rtl

$(VLIB): $(RTL_FINAL) $(CONFIG) $(VSRCS)
	@echo "+ VERILATE RTL"
	@mkdir -p $(VBUILD)
	$(VERILATOR) $(VERILATOR_CFLAGS) $(VSRCS) \
	  --top-module $(VTOP) -O3 --Mdir $(VBUILD)
	@echo "+ AR $@"
	$(MAKE) -C $(VBUILD) -f V$(VTOP).mk
	ar rcs $@ $(VBUILD)/*.o
verilate: $(VLIB)
.PHONY: verilate

wave: $(WAVE_FILE)
	$(GTKWAVE) $(WAVE_FILE) > /dev/null 2>&1 &
.PHONY: wave
