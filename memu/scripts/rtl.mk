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

CONFIG    := .config
VTOP      := $(TOP)TOP
RTL_OBJS  := $(RTL_DIR)/$(VTOP).sv
VSRCS      = $(RTL_OBJS) \
             $(shell find $(VSRCS_DIR) -name "*.v")
VLIB      := $(VBUILD)/libV$(VTOP).a
WAVE_FILE := $(BUILD_DIR)/wave.vcd

VROOT    := /usr/local/share/verilator
INC_PATH += $(VROOT)/include
INC_PATH += $(VROOT)/include/vltstd
INC_PATH += $(VBUILD)

$(RTL_OBJS): $(SCALA_SRCS)
	$(call git_commit, "generate verilog")
	@echo "+ CHISEL  (scala -> verilog)"
	@mkdir -p $(RTL_DIR)
	mill -i $(PRJ).runMain $(VTOP) --target-dir $(RTL_DIR)
rtl: $(RTL_OBJS)
.PHONY: rtl

$(VLIB): $(RTL_OBJS) $(CONFIG)
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
