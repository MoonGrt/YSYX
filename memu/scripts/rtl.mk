GTKWAVE ?= gtkwave
VERILATOR ?= verilator
VERILATOR_ROOT = /usr/local/share/verilator
VERILATOR_CFLAGS += --trace -cc -MMD -cc -O3 --x-assign fast --x-initial fast \
                    --timescale "1ns/1ns" --no-timing \
                    -CFLAGS -ggdb -LDFLAGS -ggdb -j 8

WORK_DIR  = $(shell pwd)
RTL_DIR   := $(BUILD_DIR)/rtl
VSRCS_DIR := $(MEMU_HOME)/vsrc
VBUILD    := $(BUILD_DIR)/verilated

PRJ        := chisel
SCALA_DIR  := $(PRJ)/src
SCALA_SRCS := $(shell find $(SCALA_DIR) -name "*.scala")

ifeq ($(CONFIG_CORE_minirv),y)
TOP := MiniRV
endif
ifeq ($(CONFIG_CORE_riscv32e),y)
TOP := Riscv32E
endif
ifeq ($(CONFIG_CORE_riscv32),y)
TOP := Riscv32
endif

VTOP      := $(TOP)TOP
RTL_OBJS  := $(RTL_DIR)/$(VTOP).sv
VSRCS      = $(RTL_OBJS) \
             $(shell find $(VSRCS_DIR) -name "*.v")
VLIB      := $(VBUILD)/libV$(VTOP).a
WAVE_FILE := $(BUILD_DIR)/wave.vcd

CXXSRC += csrc/core/riscv32/exec.cc

ifeq ($(CONFIG_NPC),y)
INC_PATH += $(VBUILD)
INC_PATH += $(VERILATOR_ROOT)/include
INC_PATH += $(VERILATOR_ROOT)/include/vltstd
endif

$(RTL_OBJS): $(SCALA_SRCS)
	$(call git_commit, "generate verilog")
	@echo "+ CHISEL  (scala -> verilog)"
	@mkdir -p $(RTL_DIR)
	mill -i $(PRJ).runMain $(VTOP) --target-dir $(RTL_DIR)

$(VLIB): $(RTL_OBJS)
	@echo "+ VERILATE RTL"
	@mkdir -p $(VBUILD)
	$(VERILATOR) $(VERILATOR_CFLAGS) $(VSRCS) \
	  --top-module $(VTOP) -O3 --Mdir $(VBUILD)
	@echo "+ AR $@"
	$(MAKE) -C $(VBUILD) -f V$(VTOP).mk
	ar rcs $@ $(VBUILD)/*.o

rtl: $(RTL_OBJS)

verilate: $(VLIB)

wave: $(WAVE_FILE)
	$(GTKWAVE) $(WAVE_FILE) > /dev/null 2>&1 &

.PHONY: rtl verilate wave
