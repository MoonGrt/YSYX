
## D阶段

### D1 支持RV32IM的NEMU

#### NJU PA2.1: 实现更多的指令, 在NEMU中运行大部分cpu-tests
> 类似 minirvEMU

1. Macro expansion
NEMU makefile add preprocess target to generate preprocessed source files, facilitating source code debugging and analysis (macro expansion).
```makefile
PREPS = $(SRCS:%.c=$(OBJ_DIR)/%.i) $(CXXSRC:%.cc=$(OBJ_DIR)/%.i)
$(OBJ_DIR)/%.i: %.c
	@echo + CPP $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -E -dD $< -o $@
$(OBJ_DIR)/%.i: %.cc
	@echo + CPP $<
	@mkdir -p $(dir $@)
	@$(CXX) $(CFLAGS) $(CXXFLAGS) -E -dD $< -o $@
.PHONY: preprocess
preprocess: $(PREPS)
```

2. mips32的分支延迟槽
为了提升处理器的性能, mips使用了一种叫分支延迟槽的技术. 采用这种技术之后, 程序的执行顺序会发生一些改变: 我们把紧跟在跳转指令(包括有条件和无条件)之后的静态指令称为延迟槽, 那么程序在执行完跳转指令后, 会先执行延迟槽中的指令, 再执行位于跳转目标的指令.

### D2 程序的机器级表示

1. 程序的内存布局
  +----------+
  |          |
  +----------+
  |   stack  |
  +----------+
  |    |     |  // 与变量相关的三个内存区域: 静态数据区(data), 堆区(heap), 栈区(stack)
  |    v     |  // 静态 = 不动态增长和变化, 编译时确定
  |          |  // 四种需要分配的C变量
  |    ^     |  // 全局变量 -> data区
  |    |     |  // 静态局部变量 -> data区
  +----------+  // 非静态局部变量 -> stack区
  |   heap   |  // 动态变量 -> heap区
  +----------+
  |   data   |
  +----------+
  |   text   |
  +----------+
  |          |
  +----------+

### D3 AM运行时环境

#### NJU PA2: 程序, 运行时环境与AM

1. AM(Abstract machine)项目就是这样诞生的. 作为一个向程序提供运行时环境的库, AM根据程序的需求把库划分成以下模块

AM = TRM + IOE + CTE + VME + MPE
TRM(Turing Machine) - 图灵机, 最简单的运行时环境, 为程序提供基本的计算能力
IOE(I/O Extension) - 输入输出扩展, 为程序提供输出输入的能力
CTE(Context Extension) - 上下文扩展, 为程序提供上下文管理的能力
VME(Virtual Memory Extension) - 虚存扩展, 为程序提供虚存管理的能力
MPE(Multi-Processor Extension) - 多处理器扩展, 为程序提供多处理器通信的能力 (MPE超出了ICS课程的范围, 在PA中不会涉及)

2. stdarg.h
<stdarg.h> 是 C 标准库中的一个头文件，提供了一组宏，用于访问可变数量的参数。
stdarg.h 头文件定义了一个变量类型 va_list 和三个宏，这三个宏可用于在参数个数未知（即参数个数可变）时获取函数中的参数。可变参数的函数通在参数列表的末尾是使用省略号 ... 定义的。

```c
#include <stdio.h>
#include <stdarg.h>
// 计算可变参数的和
int sum(int count, ...) {
  int total = 0;
  va_list args;
  // 初始化 args 以访问可变参数
  va_start(args, count);
  // 逐个访问可变参数
  for (int i = 0; i < count; i++)
    total += va_arg(args, int);
  // 清理 args
  va_end(args);
  return total;
}
int main() {
  printf("Sum of 1, 2, 3: %d\n", sum(3, 1, 2, 3));  // 输出 6
  printf("Sum of 4, 5, 6, 7: %d\n", sum(4, 4, 5, 6, 7));  // 输出 22
  return 0;
}
```

### D4 用RTL实现迷你RISC-V处理器

### D5 设备和输入输出

#### NJU PA2.3

1. 

