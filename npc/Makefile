# 顶层 Makefile

TOP     = Dual_Control_Switch
VSRC    = vsrc/$(TOP).v
CSRC    = csrc/main.cpp

OBJ_DIR = obj
VTOP    = $(OBJ_DIR)/V$(TOP)

VERILATOR_FLAGS = -Wall --cc --exe --trace

all: $(VTOP)

$(VTOP): $(VSRC) $(CSRC)
	verilator $(VERILATOR_FLAGS) $(VSRC) $(CSRC) -o V$(TOP) --Mdir $(OBJ_DIR)
	make -C $(OBJ_DIR) -f V$(TOP).mk

sim: $(VTOP)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	./$(VTOP)

clean:
	rm -rf $(OBJ_DIR) wave.vcd

include ../Makefile
