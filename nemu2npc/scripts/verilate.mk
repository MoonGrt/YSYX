GTKWAVE ?= gtkwave
VERILATOR ?= verilator
VERILATOR_ROOT = /usr/local/share/verilator
VERILATOR_CFLAGS += --trace -cc -MMD -cc -O3 --x-assign fast --x-initial fast \
                    --timescale "1ns/1ns" --no-timing \
                    -CFLAGS -ggdb -LDFLAGS -ggdb -j 8

WORK_DIR  = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build
VSRCS_DIR := $(NEMU2NPC_HOME)/vsrc
RTL_DIR   := $(NEMU2NPC_HOME)/rtl
VBUILD    := $(BUILD_DIR)/verilated

VTOP      := MiniRVSOC
VSRCS     := $(shell find $(RTL_DIR) -name "*.sv")
VSRCS     += $(shell find $(VSRCS_DIR) -name "*.v")
RTL_OBJS  := $(VBUILD)/V$(VTOP)__ALL.a
VLIB      := $(VBUILD)/libV$(VTOP).a

CXXSRC += csrc/core/riscv32/exec.cc

ifeq ($(CONFIG_NPC),y)
INC_PATH += build/verilated
INC_PATH += $(VERILATOR_ROOT)/include
INC_PATH += $(VERILATOR_ROOT)/include/vltstd
endif

$(VBUILD)/V$(VTOP).mk: $(RTL_DIR)/$(VTOP).sv
	@echo + VERILATE RTL
	@mkdir -p $(VBUILD)
	$(VERILATOR) $(VERILATOR_CFLAGS) $(VSRCS) \
	  --top-module $(VTOP) \
	  -O3 --Mdir $(VBUILD)
	@echo "+ AR $@"
	$(MAKE) -C $(VBUILD) -f V$(VTOP).mk

$(VLIB): $(VBUILD)/V$(VTOP).mk
	@$(MAKE) -C $(VBUILD) -f V$(VTOP).mk
	@ar rcs $@ $(VBUILD)/*.o

rtl: $(RTL_DIR)/$(VTOP).sv
	@echo + VERILATE RTL
	@mkdir -p $(VBUILD)
	$(VERILATOR) $(VERILATOR_CFLAGS) $(VSRCS) \
	  --top-module $(VTOP) \
	  -O3 --Mdir $(VBUILD)
	@echo "+ AR $@"
	$(MAKE) -C $(VBUILD) -f V$(VTOP).mk

.PHONY: verilate
