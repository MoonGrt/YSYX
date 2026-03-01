
GTKWAVE ?= gtkwave
VERILATOR ?= verilator
VERILATOR_ROOT = /usr/local/share/verilator
VERILATOR_CFLAGS += --trace -cc -MMD -cc -O3 --x-assign fast --x-initial fast \
                    --timescale "1ns/1ns" --no-timing \
                    -CFLAGS -ggdb -LDFLAGS -ggdb -j 8

WORK_DIR  = $(shell pwd)
VSRCS_DIR := $(MEMU_HOME)/vsrc
RTL_DIR   := $(MEMU_HOME)/rtl
VBUILD    := $(BUILD_DIR)/verilated

SCALA_DIR  := $(MEMU_HOME)/src
SCALA_SRCS := $(shell find $(SCALA_DIR) -name "*.scala")

PRJ       := chisel
TOP       := MiniRV
VTOP      := $(TOP)TOP
VSRCS     := $(shell find $(RTL_DIR) -name "*.sv")
VSRCS     += $(shell find $(VSRCS_DIR) -name "*.v")
RTL_OBJS  := $(VBUILD)/V$(VTOP)__ALL.a
VLIB      := $(VBUILD)/libV$(VTOP).a
WAVE_FILE := $(BUILD_DIR)/wave.vcd

CXXSRC += csrc/core/riscv32/exec.cc

ifeq ($(CONFIG_NPC),y)
INC_PATH += $(VBUILD)
INC_PATH += $(VERILATOR_ROOT)/include
INC_PATH += $(VERILATOR_ROOT)/include/vltstd
endif

$(RTL_DIR)/$(VTOP).sv: $(SCALA_SRCS)
	$(call git_commit, "generate verilog")
	@echo "+ CHISEL  (scala -> verilog)"
	mkdir -p $(RTL_DIR)
	mill -i $(PRJ).runMain $(VTOP) --target-dir $(RTL_DIR)

$(VBUILD)/V$(VTOP).mk: $(RTL_DIR)/$(VTOP).sv
	@echo + VERILATE RTL
	@mkdir -p $(VBUILD)
	$(VERILATOR) $(VERILATOR_CFLAGS) $(VSRCS) \
	  --top-module $(VTOP) -O3 --Mdir $(VBUILD)
	@echo "+ AR $@"
	$(MAKE) -C $(VBUILD) -f V$(VTOP).mk

$(VLIB): $(VBUILD)/V$(VTOP).mk
	@$(MAKE) -C $(VBUILD) -f V$(VTOP).mk
	@ar rcs $@ $(VBUILD)/*.o

rtl:
	$(call git_commit, "generate verilog")
	mkdir -p $(RTL_DIR)
	mill -i $(PRJ).runMain $(VTOP) --target-dir $(RTL_DIR)

verilate: $(RTL_DIR)/$(VTOP).sv
	@echo + VERILATE RTL
	@mkdir -p $(VBUILD)
	$(VERILATOR) $(VERILATOR_CFLAGS) $(VSRCS) \
	  --top-module $(VTOP) -O3 --Mdir $(VBUILD)
	@echo "+ AR $@"
	$(MAKE) -C $(VBUILD) -f V$(VTOP).mk

wave: $(WAVE_FILE)
	$(GTKWAVE) $(WAVE_FILE) > /dev/null 2>&1 &

.PHONY: rtl verilate wave
