RTL_SOURCES = adder.v
SC_MAIN = sim_main.cpp
TOP_MODULE = adder
VERILATOR = verilator
CXX = g++

# 目标文件目录
OBJ_DIR_RTL = obj_dir_rtl
OBJ_DIR_SIM = obj_dir_sim

# 第一步：只编译RTL生成静态库
$(OBJ_DIR_RTL)/V$(TOP_MODULE).mk: $(RTL_SOURCES)
	$(VERILATOR) --cc --top-module $(TOP_MODULE) \
		-Mdir $(OBJ_DIR_RTL) $(RTL_SOURCES)
	cd $(OBJ_DIR_RTL) && make -f V$(TOP_MODULE).mk

# 第二步：链接RTL库和sc_main
sim: $(OBJ_DIR_RTL)/V$(TOP_MODULE).mk $(SC_MAIN)
	$(CXX) -I$(OBJ_DIR_RTL) -I/usr/local/share/verilator/include \
		$(SC_MAIN) $(OBJ_DIR_RTL)/*.o \
		-o sim
	@echo "只重新编译了sc_main，RTL部分已使用预编译"

# 第三步：运行
run: sim
	./sim

# 只重新编译RTL
rtl_only: $(RTL_SOURCES)
	$(VERILATOR) --cc --exe --top-module $(TOP_MODULE) \
		-Mdir $(OBJ_DIR_RTL) --build \
		-CFLAGS "-fPIC" $(RTL_SOURCES) dummy.cpp
	@echo "RTL已重新编译"

clean_rtl:
	rm -rf $(OBJ_DIR_RTL)

clean:
	rm -rf $(OBJ_DIR_RTL) sim
