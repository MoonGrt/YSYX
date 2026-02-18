TOPNAME = MiniRVSOC

VERILATOR = verilator
VERILATOR_CFLAGS += --trace -cc -exe -MMD --build -cc -O3 --x-assign fast \
                    --x-initial fast --noassert -Wno-WIDTH -Wno-UNOPTFLAT

RTL_DIR = rtl
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)
WAVE_FILE = $(BUILD_DIR)/wave.vcd

PRJ = playground

verilog:
	$(call git_commit, "generate verilog")
	mkdir -p $(RTL_DIR)
	mill -i $(PRJ).runMain Elaborate --target-dir $(RTL_DIR)

test:
	mill -i $(PRJ).test

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

VSRCS := $(shell [ -d $(RTL_DIR) ] && find $(RTL_DIR) -name "MiniRVSOC.sv" || echo "")
VSRCS += $(shell find ./vsrc -name "*.v")
CSRCS := $(shell find ./csrc -name "minirv.cpp")
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

$(BIN): $(VSRCS)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	mkdir -p $(BUILD_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) -o $(abspath $(BIN)) \
		--top-module $(TOPNAME) $^ $(CSRCS)

run: $(BIN)
	@$^

gdb: $(BIN)
	@echo "Write this Makefile by yourself."

wave: sim
	gtkwave $(WAVE_FILE)

clean-all:
	-rm -rf $(RTL_DIR)
	-rm -rf $(BUILD_DIR)

.PHONY: sim run gdb wave

-include ../Makefile
