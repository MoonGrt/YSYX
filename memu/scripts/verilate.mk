
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

PRJ       := chisel
VTOP      := MiniRVSOC
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

rtl: $(RTL_DIR)/$(VTOP).sv
	@echo + VERILATE RTL
	@mkdir -p $(VBUILD)
	$(VERILATOR) $(VERILATOR_CFLAGS) $(VSRCS) \
	  --top-module $(VTOP) -O3 --Mdir $(VBUILD)
	@echo "+ AR $@"
	$(MAKE) -C $(VBUILD) -f V$(VTOP).mk

TEST := csrc/minirv.cpp
ARGS ?= --log=$(BUILD_DIR)/memu-test-log.txt
test: $(VLIB) $(TEST)
	@mkdir -p $(dir $@)
	$(CXX) -I$(VBUILD) -I/usr/local/share/verilator/include \
		-I/usr/local/share/verilator/include/vltstd \
		$(TEST) $(VLIB) -o $(BUILD_DIR)/test
	$(BUILD_DIR)/test $(ARGS)

verilog:
	 $(call git_commit, "generate verilog")
	mkdir -p $(RTL_DIR)
	mill -i $(PRJ).runMain $(VTOP) --target-dir $(RTL_DIR)

wave: $(WAVE_FILE)
	$(GTKWAVE) $(WAVE_FILE) > /dev/null 2>&1 &

.PHONY: test verilog wave
