TOPNAME = MiniRVSOC
RTL_DIR = rtl
PRJ = chisel

verilog:
	$(call git_commit, "generate verilog")
	mkdir -p $(RTL_DIR)
	mill -i $(PRJ).runMain $(TOPNAME) --target-dir $(RTL_DIR)

test:
	mill -i $(PRJ).test

help:
	mill -i $(PRJ).runMain $(TOPNAME) --help

reformat:
	mill -i __.reformat

checkformat:
	mill -i __.checkFormat

bsp:
	mill -i mill.bsp.BSP/install

idea:
	mill -i mill.idea.GenIdea/idea

.PHONY: test verilog help reformat checkformat clean




GTKWAVE =gtkwave
VERILATOR = verilator
VERILATOR_CFLAGS += --trace -cc -exe -MMD --build -cc -O3 --x-assign fast \
                    --x-initial fast --noassert -Wno-WIDTH -Wno-UNOPTFLAT \
                    --timescale "1ns/1ns" --no-timing \
                    -CFLAGS -ggdb -LDFLAGS -ggdb -j 8

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)
WAVE_FILE = $(BUILD_DIR)/wave.vcd

VSRCS := $(shell [ -d $(RTL_DIR) ] && find $(RTL_DIR) -name "MiniRVSOC.sv" || echo "")
VSRCS += $(shell find ./vsrc -name "*.v")
CSRCS := $(shell find ./csrc -name "minirv.cpp")
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

override ARGS ?= --log=$(BUILD_DIR)/npc-log.txt
IMG ?=
NPC_EXEC := $(BIN) $(ARGS) $(IMG)

$(BIN): $(VSRCS) $(CSRCS)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	mkdir -p $(BUILD_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) -o $(abspath $(BIN)) \
		--top-module $(TOPNAME) $^

run: $(BIN)
	$(NPC_EXEC)

gdb: $(BIN)
	gdb --args $(NPC_EXEC)

wave: $(WAVE_FILE)
	$(GTKWAVE) $(WAVE_FILE)

clean:
	-rm -rf $(BUILD_DIR)

clean-all:
	-rm -rf $(RTL_DIR)
	-rm -rf $(BUILD_DIR)

.PHONY: sim run gdb wave

-include ../Makefile
