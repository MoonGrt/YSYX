TARGET = sim_main
OBJ_DIR = obj_dir
VERILATED_SRCS = $(OBJ_DIR)/Vadder.cpp
CXX = g++
VERILATOR_INCLUDE = /usr/local/share/verilator/include
VERILATOR_LIB = /usr/local/share/verilator/include/vltstd/libverilated.a
CXXFLAGS = -I$(OBJ_DIR) -I/usr/local/share/verilator/include -I/usr/local/share/verilator/include/vltstd -std=c++17

all: $(TARGET)

$(TARGET): $(VERILATED_SRCS) sim_main.cpp
	$(CXX) $(CXXFLAGS) -o $@ sim_main.cpp $(VERILATED_SRCS) $(VERILATOR_LIB)

clean:
	rm -rf $(TARGET)
