VERILATOR ?= verilator
VERILATOR_CFLAGS += --trace -cc -MMD -cc -O3 --x-assign fast \
                    --x-initial fast --noassert -Wno-WIDTH -Wno-UNOPTFLAT \
                    --timescale "1ns/1ns" --no-timing

VSRCS_DIR := $(NEMU2NPC_HOME)/vsrc
RTL_DIR   := $(NEMU2NPC_HOME)/rtl
VBUILD    := $(BUILD_DIR)/verilated

VTOP      := MiniRVSOC
VSRCS     := $(shell find $(RTL_DIR) -name "*.sv")
VSRCS     += $(shell find $(VSRCS_DIR) -name "*.v")

VERILATED_SRCS := \
  $(VBUILD)/V$(VTOP).cpp \
  $(VBUILD)/V$(VTOP)__Syms.cpp

verilate: $(OBJS)
	@echo + VERILATE RTL
	@mkdir -p $(VBUILD)
	$(VERILATOR) $(VERILATOR_CFLAGS) $(VSRCS) \
	  --top-module $(VTOP) \
	  -O3 --Mdir $(VBUILD)

.PHONY: verilate
