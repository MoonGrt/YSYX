TOPNAME = MiniRVSOC

VERILATOR = verilator
VERILATOR_CFLAGS += --trace -MMD --build -cc -O3 --x-assign fast --x-initial fast --noassert -Wno-WIDTH -Wno-UNOPTFLAT

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)
WAVE_FILE = $(BUILD_DIR)/wave.vcd

PRJ = playground

test:
	mill -i $(PRJ).test

verilog:
	$(call git_commit, "generate verilog")
	mkdir -p $(BUILD_DIR)
	mill -i $(PRJ).runMain Elaborate --target-dir $(BUILD_DIR)

help:
	mill -i $(PRJ).runMain Elaborate --help

reformat:
	mill -i __.reformat

checkformat:
	mill -i __.checkFormat

bsp:
	mill -i mill.bsp.BSP/install

idea:
	mill -i mill.idea.GenIdea/idea

clean:
	-rm -rf $(BUILD_DIR)

.PHONY: test verilog help reformat checkformat clean

VSRCS := $(shell find ./build -name "MiniRVSOC.sv")
VSRCS += $(shell find ./vsrc -name "*.v")
CSRCS := $(shell find ./csrc -name "minirv.cpp")
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

sim: $(VSRCS)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ $(CSRCS) \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

run: sim
	@echo "Write this Makefile by yourself."

gdb: sim
	@echo "Write this Makefile by yourself."

wave: sim
	gtkwave $(WAVE_FILE)

.PHONY: sim run gdb wave

-include ../Makefile
