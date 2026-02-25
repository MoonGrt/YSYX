VERILATOR ?= verilator
VERILATOR_CFLAGS += --trace -cc -MMD -cc -O3 --x-assign fast \
                    --x-initial fast --noassert -Wno-WIDTH -Wno-UNOPTFLAT \
                    --timescale "1ns/1ns" --no-timing

WORK_DIR  = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build
VSRCS_DIR := $(NEMU2NPC_HOME)/vsrc
RTL_DIR   := $(NEMU2NPC_HOME)/rtl
VBUILD    := $(BUILD_DIR)/verilated

VTOP      := MiniRVSOC
VSRCS     := $(shell find $(RTL_DIR) -name "*.sv")
VSRCS     += $(shell find $(VSRCS_DIR) -name "*.v")
RTL_OBJS  := $(VBUILD)/V$(VTOP)__ALL.a

$(VBUILD)/V$(VTOP).mk: $(RTL_DIR)/$(VTOP).sv
	@echo + VERILATE RTL
	@mkdir -p $(VBUILD)
	$(VERILATOR) $(VERILATOR_CFLAGS) $(VSRCS) \
	  --top-module $(VTOP) \
	  -O3 --Mdir $(VBUILD)
	@echo "+ AR $@"
	$(MAKE) -C $(VBUILD) -f V$(VTOP).mk

$(VBUILD)/libV$(VTOP).a: $(VBUILD)/V$(VTOP).mk
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
