GTKWAVE   ?= gtkwave
VERILATOR ?= verilator

ifeq ($(CONFIG_WAVE_VCD),y)
VERILATOR_CFLAGS += --trace
endif
ifeq ($(CONFIG_WAVE_FST),y)
VERILATOR_CFLAGS += --trace-fst
endif
VERILATOR_CFLAGS += -cc -MMD -cc -O3 --x-assign fast --x-initial fast \
                    --timescale "1ns/1ns" --no-timing \
                    -CFLAGS -ggdb -LDFLAGS -ggdb -j 8
VERILATOR_CFLAGS += -I$(MEMU_HOME)/vsrc/perip/uart16550/rtl
VERILATOR_CFLAGS += -I$(MEMU_HOME)/vsrc/perip/spi/rtl

RTL_DIR   := $(BUILD_DIR)/rtl
VSRCS_DIR := $(MEMU_HOME)/vsrc
VBUILD    := $(BUILD_DIR)/verilated

PRJ        := chisel
SCALA_DIR  := $(PRJ)/src
SCALA_SRCS := $(shell find $(SCALA_DIR) -name "*.scala")

ifeq ($(CONFIG_CORE_MINIRV),y)
TOP := MiniRV
endif
ifeq ($(CONFIG_CORE_RV32E),y)
TOP := Riscv32E
endif

CONFIG    := .config
VTOP      := $(TOP)TOP
RTL_OBJS  := $(RTL_DIR)/$(VTOP).sv
RTL_FINAL := $(RTL_DIR)/$(VTOP).v
VSRCS      = $(RTL_FINAL) \
             $(shell find $(VSRCS_DIR) -name "*.v")
VLIB      := $(VBUILD)/libV$(VTOP).a
WAVE_FILE := $(BUILD_DIR)/wave.vcd

VROOT    := /usr/local/share/verilator
INC_PATH += $(VROOT)/include
INC_PATH += $(VROOT)/include/vltstd
INC_PATH += $(VBUILD)

# Firtool version
# ENABLE_FIRTOOL_PATCH ?= y
FIRTOOL_VERSION = 1.105.0
FIRTOOL_PATCH_DIR = $(MEMU_HOME)/scripts/firtool

$(RTL_FINAL): $(SCALA_SRCS)
	$(call git_commit, "generate verilog")
	@echo "+ CHISEL  (scala -> verilog)"
	@mkdir -p $(RTL_DIR)
ifeq ($(ENABLE_FIRTOOL_PATCH),y)
# Replace firtool with a newer version
# TODO: This can be removed after chisel publishes a new version
	@$(MEMU_HOME)/scripts/firtool-patch.sh \
		$(FIRTOOL_VERSION) $(FIRTOOL_PATCH_DIR)
	CHISEL_FIRTOOL_PATH=$(FIRTOOL_PATCH_DIR)/firtool-$(FIRTOOL_VERSION)/bin \
	mill -i $(PRJ).runMain $(VTOP) --target-dir $(RTL_DIR)
else
	mill -i $(PRJ).runMain $(VTOP) --target-dir $(RTL_DIR)
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
