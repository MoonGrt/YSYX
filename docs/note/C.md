# C阶段
## C1 工具和基础设施

1. 什么才算是一个 Symbol？

    在 **ELF 符号表**中，一个 **symbol** 一般指:  **在链接阶段需要被识别或解析的名字**. 也就是说:  一个 symbol 必须满足: 
    - **有全局或静态存储位置**
    - **在链接时可能被引用**

    典型的 symbol 包括:  (1) 全局变量 (2) 函数 (3) static 全局变量 (4) 外部引用

2. 寻找"Hello World!"

    "Hello World!" 不在 ELF 的字符串表 .strtab 或 .dynstr 中，而是在 .rodata 段。
    ```c
    #include <stdio.h>
    int main() {
        printf("Hello World!\n");
        return 0;
    }
    ```
    ```bash
    gcc hello.c -o hello
    readelf -x .rodata hello
    ```

3. ELF 文件结构

    ELF - Executable and Linkable Format
    我们先写一段极简的 C 代码，来论证 ELF 是如何将不同数据分类存放的。
    ```c
    // main.c
    #include <stdio.h>
    int global_init = 42;  // 已初始化，应在 .data
    int global_uninit[10000];  // 未初始化数组（占据约 40KB），应在 .bss
    const char* msg = "Hello ELF";  // 字符串常量，应在 .rodata
    int main() {
      printf("%s\n", msg);  // 代码逻辑，应在 .text
      return 0;
    }
    ```
    编译它: gcc main.c -o app

    3.1. 链接视图: Section（给编译器和链接器看）
    使用 readelf -S app 查看 Section 头部表，你会清晰地看到刚才代码中的元素被安排得明明白白: 

    .text（代码段）: 存放 main 函数的机器指令。权限是只读且可执行。
    .data（数据段）: 存放 global_init（值为 42）。权限是可读可写。
    .rodata（只读数据段）: 存放 "Hello ELF"。权限是只读。
    .bss（BSS段）: 存放 global_uninit。
    重点实证: 如果你用 ls -l app 查看文件大小，可能只有 16KB。但 global_uninit 数组明明需要 40KB 的空间！这是因为 .bss 段在 ELF 文件中不占实际的磁盘空间，ELF 只记录了一句: “这里需要 40KB 的内存”。等程序运行加载到内存时，操作系统才会分配这 40KB 并清零。

    3.2. 执行视图: Segment（给操作系统加载器看）
    操作系统在运行程序时，嫌弃一个个细碎的 Section 效率太低，它只关心内存权限。使用 readelf -l app 查看 Segment（Program Headers）: 
    你会看到两个主要的 LOAD 段: 
    第一个 LOAD 段（只读/可执行 R E）: 操作系统将 .text 和 .rodata 打包进这个内存页。如果程序企图修改这片内存，会直接触发 Segmentation Fault（段错误）。
    第二个 LOAD 段（可读/可写 R W）: 操作系统将 .data 和 .bss 打包进这个内存页。

    3.3 ELF vs BIN
    ELF 文件和 BIN 文件是两种完全不同类型的文件，它们的用途和结构差异很大。下面做一个详细对比: 

    - 3.3.1. 文件定义
      * **ELF（Executable and Linkable Format）文件**
        * 是一种可执行文件格式，常用于 Linux、Unix 系统。
        * 可以包含 **程序代码、数据、符号表、调试信息** 等。
        * 可以直接被操作系统加载执行，或用于链接生成最终可执行程序。
        * 有不同类型: 可执行文件（`ET_EXEC`）、共享库（`ET_DYN`）、目标文件（`ET_REL`）等。
      * **BIN 文件**
        * 通常指 **纯二进制文件**，没有任何头信息或元数据。
        * 直接包含机器码或者原始数据，系统无法直接识别结构。
        * 常用于嵌入式系统的固件烧写、裸机程序等。

    - 3.3.2. 文件结构

      | 特性         | ELF 文件                           | BIN 文件             |
      | ---------- | -------------------------------- | ------------------ |
      | 头信息        | 有 ELF header，包括程序入口、段表、节表等       | 没有头信息              |
      | 段（Segment） | 包含多个段，如 `.text`, `.data`, `.bss` | 通常是一个连续的内存映像       |
      | 符号信息       | 可以包含符号表、调试信息                     | 通常没有符号信息           |
      | 可执行性       | 可以直接在操作系统中加载                     | 不能直接执行，需要特定地址/方式加载 |
      | 可移植性       | 依赖操作系统和 CPU 架构                   | 完全依赖硬件架构，纯码        |

    - 3.3.3. 使用场景
      * **ELF 文件**
        * Linux 可执行程序（如 `gcc` 编译出的 `a.out`）
        * 动态链接库 (`.so`)
        * 调试与分析工具（可以使用 `objdump`、`readelf` 查看内部信息）
      * **BIN 文件**
        * MCU/FPGA/嵌入式裸机程序烧写
        * Bootloader、固件更新
        * 需要直接加载到内存执行的场景

    - 3.3.4. 转换
      通常在嵌入式开发中会把 ELF 文件转成 BIN 文件: 
      ```bash
      # 使用 objcopy
      arm-none-eabi-objcopy -O binary input.elf output.bin
      ```
      * ELF → BIN: 丢掉符号表、节信息，只保留机器码和初始化数据。
      * BIN → ELF: 理论上不可逆，需要额外工具重建段和符号表。


## C2 支持RV32E的单周期NPC

1. NEMU 动态库
    nemu/src/cpu/difftest/ref.c -> `ref.c` 的核心逻辑:  把 NEMU 封装成一个“可被外部控制的参考模型”，供 NPC 做逐条对比。`ref.c` 只是把 NEMU 的内部状态暴露出来，变成一个可控的 golden model。

    > 提供的四个接口的本质:
    > **difftest_memcpy**: 同步内存（NPC ↔ NEMU）。
    > **difftest_regcpy**: 同步架构状态（整个 `CPU_state` 结构体）。
    > **difftest_exec(n)**: 让 NEMU 执行 n 条指令。
    > **difftest_init**: 初始化内存和 ISA 状态。

2. 硬件如何区分有符号数和无符号数?
    编写以下程序:
    ```c
    #include <stdint.h>
    int32_t fun1(int32_t a, int32_t b) { return a + b; }
    uint32_t fun2(uint32_t a, uint32_t b) { return a + b; }
    ```
    然后编译并查看反汇编代码:
    ```bash
    riscv64-linux-gnu-gcc -c -march=rv32g -mabi=ilp32 -O2 test.c
    riscv64-linux-gnu-objdump -d test.o
    ```
    结果:
    ```
    test.o:     file format elf32-littleriscv
    Disassembly of section .text:
    00000000 <fun1>:
      0:   00b50533                add     a0,a0,a1
      4:   00008067                ret
    00000008 <fun2>:
      8:   00b50533                add     a0,a0,a1
      c:   00008067                ret
    ```

    **结论: 硬件本身不区分有符号数和无符号数。**
    在 RISC-V 中，`add` 指令执行的是 **模 2³² 的加法**，只对比特做运算，不关心类型。 因此: 
    ```c
    int32_t  a + b
    uint32_t a + b
    ```
    生成的都是: 
    ```
    add a0, a0, a1
    ```
    区别只存在于:  软件如何解释结果
    硬件有区别情况在: 
    * 比较指令（`slt` vs `sltu`）
    * 右移指令（`sra` vs `srl`）
    类型是编译器概念，不是硬件概念。

3. 观察ALU的综合结果
- 3.1 简化版 ALU:
    ```verilog
    module alu #(parameter WIDTH = 4) (
      input  [WIDTH-1:0] a,
      input  [WIDTH-1:0] b,
      input  [2:0] op,
      output reg [WIDTH-1:0] y
    );
    wire [WIDTH-1:0] add_res = a + b;
    wire [WIDTH-1:0] sub_res = a - b;
    always @(*) begin
      case (op)
        3'b000: y = add_res;
        3'b001: y = sub_res;
        3'b010: y = a << b;
        3'b011: y = a >> b;
        3'b100: y = (a < b);
        default: y = 0;
      endcase
    end
    endmodule
    ```

- 3.2 使用 yosys 进行综合
    ```bash
    yosys alu.v
    yosys> hierarchy -check -top alu
    yosys> proc; opt; fsm; opt; memory; opt
    yosys> show
    ```

**问题 1**  “减法、比较是否会自动合并为同一个加法器？”
> 默认情况下，**不会自动合并为一个物理加法器**: 同时有 $add $sub
> Yosys 更偏向逻辑展开，而不是资源复用。

**问题 2**  "移位运算符 << 和 >> 被综合成什么电路？"
> 被综合为 **多级多路选择器（barrel shifter）**
> ```verilog
> a << b (2 bits)
> ```
> 会变成: 
> ```
> if b[0] → shift 1 bit
> if b[1] → shift 2 bit
> ```
> 也就是:  log2(N) 级 MUX 级联

>  **特别说明**
> * 常数移位(a << 2) → 直接 rewiring
> * 可变移位(a << b) → barrel shifter（多级MUX）

**问题 3** "从运算符直接综合是否有改进空间？"
> Yosys 是逻辑综合工具，不是高级算术优化器。它: 
> * 不做 aggressive 资源共享
> * 不做高层算术结构合并
> * 不做算术单元调度

## C3 调试技巧
## C4 ELF文件和链接

1. ELF目标文件
ELF目标文件 = 节 + 元数据(节头) + …

ELF中一些常见的节
节	说明	|	节	说明
.text	代码	|	.bss	未初始化数据
.data	可写数据	|	.debug	调试信息
.rodata	只读数据	|	.line	行号信息
> .bss - Block Starting Symbol

2. 链接 = 符号解析 + 重定位
符号解析 = 将符号的引用和其定义建立关联
重定位 = 合并节 + 确定符号地址 + 在引用处填写地址

## C5 异常处理和RT-Thread

### NJU PA3.1

https://blog.stevepaul.cc/course-lab/nju-ics-pa/pa3

1. 文件后缀名是.S，代表的是这个汇编代码是会被预处理的。通过下面的命令输出预处理后的结果:

    ```
    gcc -E trap.S -o trap.s
    ```

    ```s
    __am_asm_trap:
      # ===============================
      # 1. 为 Context 在栈上分配空间
      #    32 个 GPR
      #  + 3 个 CSR (mcause/mstatus/mepc)
      #  + 1 个填充槽（对齐）
      #    每个 8 字节 (RV64)
      # ===============================
      addi sp, sp, -((32 + 4) * 8)
      # ===============================
      # 2. 保存通用寄存器
      #    x0 不需要保存（恒为 0）
      #    按寄存器编号 * 8 的方式存放
      #    这样 C 层可以用 gpr[i] 直接索引
      # ===============================
      sd x1, (1 * 8)(sp); sd x3, (3 * 8)(sp); sd x4, (4 * 8)(sp); sd x5, (5 * 8)(sp); sd x6, (6 * 8)(sp); sd x7, (7 * 8)(sp); sd x8, (8 * 8)(sp); sd x9, (9 * 8)(sp); sd x10, (10 * 8)(sp); sd x11, (11 * 8)(sp); sd x12, (12 * 8)(sp); sd x13, (13 * 8)(sp); sd x14, (14 * 8)(sp); sd x15, (15 * 8)(sp); sd x16, (16 * 8)(sp); sd x17, (17 * 8)(sp); sd x18, (18 * 8)(sp); sd x19, (19 * 8)(sp); sd x20, (20 * 8)(sp); sd x21, (21 * 8)(sp); sd x22, (22 * 8)(sp); sd x23, (23 * 8)(sp); sd x24, (24 * 8)(sp); sd x25, (25 * 8)(sp); sd x26, (26 * 8)(sp); sd x27, (27 * 8)(sp); sd x28, (28 * 8)(sp); sd x29, (29 * 8)(sp); sd x30, (30 * 8)(sp); sd x31, (31 * 8)(sp);
      # ===============================
      # 3. 读取关键 CSR
      #    mcause : trap 原因
      #    mstatus: 状态寄存器
      #    mepc   : 异常返回地址
      # ===============================
      csrr t0, mcause
      csrr t1, mstatus
      csrr t2, mepc
      # ===============================
      # 4. 将 CSR 保存到 Context
      # ===============================
      sd t0, ((32 + 0) * 8)(sp)
      sd t1, ((32 + 1) * 8)(sp)
      sd t2, ((32 + 2) * 8)(sp)
      # ===============================
      # 5. 设置 mstatus.MPRV 位
      #    MPRV = 1 时: 
      #    load/store 使用 MPP 指示的特权级
      #    这里用于通过 difftest
      # ===============================
      li a0, (1 << 17)
      or t1, t1, a0
      csrw mstatus, t1
      # ===============================
      # 6. 调用 C 层中断处理函数
      #    a0 = 当前 Context 指针
      # ===============================
      mv a0, sp
      call __am_irq_handle
      # 返回后: 
      #  - Context 可能被修改
      #  - 甚至可能被替换（调度）
      # ===============================
      # 7. 恢复 CSR（使用可能被修改后的值）
      # ===============================
      ld t1, ((32 + 1) * 8)(sp)
      ld t2, ((32 + 2) * 8)(sp)
      csrw mstatus, t1
      csrw mepc, t2
      # ===============================
      # 8. 恢复全部通用寄存器
      # ===============================
      ld x1, (1 * 8)(sp); ld x3, (3 * 8)(sp); ld x4, (4 * 8)(sp); ld x5, (5 * 8)(sp); ld x6, (6 * 8)(sp); ld x7, (7 * 8)(sp); ld x8, (8 * 8)(sp); ld x9, (9 * 8)(sp); ld x10, (10 * 8)(sp); ld x11, (11 * 8)(sp); ld x12, (12 * 8)(sp); ld x13, (13 * 8)(sp); ld x14, (14 * 8)(sp); ld x15, (15 * 8)(sp); ld x16, (16 * 8)(sp); ld x17, (17 * 8)(sp); ld x18, (18 * 8)(sp); ld x19, (19 * 8)(sp); ld x20, (20 * 8)(sp); ld x21, (21 * 8)(sp); ld x22, (22 * 8)(sp); ld x23, (23 * 8)(sp); ld x24, (24 * 8)(sp); ld x25, (25 * 8)(sp); ld x26, (26 * 8)(sp); ld x27, (27 * 8)(sp); ld x28, (28 * 8)(sp); ld x29, (29 * 8)(sp); ld x30, (30 * 8)(sp); ld x31, (31 * 8)(sp);
      # ===============================
      # 9. 释放栈空间
      # ===============================
      addi sp, sp, ((32 + 4) * 8)
      # ===============================
      # 10. 从异常返回
      #     PC ← mepc
      #     恢复特权级和中断状态
      # ===============================
      mret
    ```

    ```mermaid
    sequenceDiagram
        participant U as User Code
        participant CPU as RISC-V CPU
        participant Trap as __am_asm_trap
        participant C as __am_irq_handle
        participant S as Scheduler

        U->>CPU: ecall / exception / interrupt
        CPU->>CPU: 保存 mepc\n写入 mcause\n更新 mstatus
        CPU->>Trap: 跳转到 mtvec

        Trap->>Trap: 分配栈空间\n构造 Context
        Trap->>Trap: 保存 x1~x31
        Trap->>Trap: 读取 mcause/mstatus/mepc\n保存到栈
        Trap->>Trap: 设置 mstatus.MPRV = 1

        Trap->>C: 传入 a0 = Context*

        C->>C: 根据 mcause 分发事件

        alt 是 yield / syscall
            C->>S: 调用 schedule()
            S-->>C: 返回新的 Context\n(可能不同线程)
        end

        C-->>Trap: 返回 Context*

        Trap->>Trap: 恢复 mstatus
        Trap->>Trap: 恢复 mepc
        Trap->>Trap: 恢复 x1~x31
        Trap->>Trap: 释放栈空间

        Trap->>CPU: mret
        CPU->>U: 跳转到 mepc 指向地址\n(可能已被修改)
    ```


2. 理解上下文结构体的前世今生
    查看RISC-V手册就会知道这个a0通用寄存器就是用来放函数的第一个参数的。看看上面的汇编就会发现是mv a0, sp把参数给传给__am_irq_hendle这个函数了:由于我们把上下文从低地址到高地址相对于sp存的，所以sp实际上就是上下文结构体的首地址了。这里面成员的赋值的位置，看看刚才的预处理后的结果就知道了，都是相对于sp的分别的一个偏移处。

    这四部分的联系: 
    riscv.h指定了上下文结构体的定义，方便CTE去使用上下文。
    trap.S负责异常发生后对之前的程序状态进行保存，然后调用__am_irq_handle进一步处理异常，然后再恢复之前的程序状态。
    上面的讲义文字把这一切的大纲给阐明了。
    实现的新指令让这些东西能在NEMU上作为一个个指令能执行得动。具体而言ecall让程序具有了跳到异常处理程序的能力，csrrw和csrrs使得可以读取、写入CSR，让保存、恢复CSR的状态成为可能。

3. 标准 RISC-V（RV32I / RV64I）
  在标准 RISC-V ABI（如 RV32I）中: 
    - a0–a7 是参数寄存器
    - a7 约定用于存放 syscall number
    - ecall 时: 
      - a7 = syscall 号
      - a0–a6 = 参数
      - 返回值放在 a0

4. 理解穿越时空的旅程
yield() → 在 a7 寄存器放入自陷的标志，并要求执行 ecall 指令
  → NEMU 根据之前设定的异常处理入口，让 pc 指到异常处理入口 __am_asm_trap
  → 保存通用寄存器和 CSR 到栈上
  → 以刚才保存的上下文为参数，调用 __am_irq_handle
  → 根据上下文的信息识别事件类型，修改 mepc ，并调用注册好了的 simple_trap → 输出 y
  → 从栈上恢复 CSR 和通用寄存器
  → 调用 mret → NEMU 根据 mepc 的实现，恢复 pc 到 mepc
  → 继续跑之前的程序。

### NJU PA4.1





## C阶段答辩

1. Typing-Game 程序流程图
    %% 按键视角: 从按键到命中
    按下键盘 → 键盘硬件产生事件
    → NEMU/NPC/AM接口捕获按键
    → 游戏程序读取键码
    → check_hit判断是否命中
    → 命中?
    → 更新 wrong 计数 / 更新 hit 计数
    → render更新帧缓冲

    %% 程序视角: 事件处理到渲染
    init(ioe,gpu) → while(1) 主循环
      → 计时 (AM_TIMER_UPTIME)
      → game_logic_update() 更新字符状态
      → 读取键盘 (AM_INPUT_KEYBRD)
      → check_hit() 判断是否击中
      → render() 绘制屏幕
      → 循环执行，形成 30 FPS 的打字下落游戏。

2. Makefile 调用时序图

    `cpu-tests/Makefile`
    ```mermaid
    sequenceDiagram
      autonumber
      participant User as User
      participant CPU as cpu-tests/Makefile
      participant Tmp as Makefile.<test>
      participant AM as $(AM_HOME)/Makefile
      participant Arch as Arch/Platform MK (riscv32.mk / nemu.mk)
      participant NEMU as NEMU Simulator
      User->>CPU: make run / make all
      CPU->>Tmp: 生成临时 Makefile.<test>
      Tmp->>AM: include $(AM_HOME)/Makefile
      AM->>Arch: 引入 rv32.mk / nemu.mk
      Arch->>NEMU: 构建 ELF → 镜像 → 执行模拟器
      NEMU-->>Arch: 返回执行状态
      Arch-->>AM: 返回状态
      AM-->>Tmp: 返回状态
      Tmp-->>CPU: PASS / FAIL 写入 $(RESULT)
      CPU->>User: 输出测试结果
    ```

    - 2.1. **cpu-tests/Makefile** 是入口，生成每个测试的临时 Makefile
    - 2.2. **临时 Makefile** 引入 **AM Makefile**
    - 2.3. **AM Makefile** 根据 `ARCH` 分析并引入对应的 **ISA/Platform makefiles**
    - 2.4. 平台 makefile（nemu.mk）负责生成 ELF、镜像并调用 NEMU 执行
    - 2.5. 执行结果逐层返回，最终记录到 `$(RESULT)` 并输出

3. Abstract Machine Makefile 调用时序图

    ```mermaid
    sequenceDiagram
      autonumber
      participant User as User
      participant AM as AM Makefile
      participant Arch as Arch/Platform MK
      participant Build as build/$(ARCH)
      participant Lib as Libraries (am, klib, ...)
      participant Insert as insert-arg
      %% 1. 入口
      User->>AM: make run / make image / make archive
      %% 2. 环境检查 & 架构/平台配置
      AM->>AM: 检查 AM_HOME 是否有效 <br> 检查 ARCH 是否支持
      %% 3. 架构/平台配置
      AM->>Arch: include 架构/平台 Makefile <br> 设置编译 flag、库路径、汇编/链接脚本
      %% 4. 编译
      Arch->>Build: 自动创建 `build/$(ARCH)` <br> 编译 .c/.cc/.cpp/.S -> .o
      %% 5. 依赖库编译
      Build->>Lib: 递归 make archive am, klib, ... <br>
      Lib-->>Build: 返回 .a 文件
      %% 6. 链接 ELF
      Build->>Build: 链接 .o + .a -> IMAGE.elf
      %% 7. insert-arg
      Build->>Insert: 嵌入 mainarg 到 ELF 镜像
      %% 8. 完成
      Insert-->>User: 返回最终 ELF 或 archive <br> Platform 运行相关Makfile
    ```

    - 3.1. **入口**: 用户执行 `make run`、`make image` 或 `make archive`。
    - 3.2. **环境检查**: 
      * 确认 `AM_HOME` 指向 Abstract-Machine 仓库。
      * 检查 `ARCH` 是否在支持列表。
      * 拆分 `ARCH` 得到 `ISA` 和 `PLATFORM`。
    - 3.3. **架构/平台配置**: 
      * 引入架构/平台特定 makefile（`x86_64-qemu.mk`、`riscv64-nemu.mk` 等）。
      * 配置架构相关 flag、编译器、库路径、汇编/链接脚本。
    - 3.4. **编译**: 
      * 自动创建 `build/$(ARCH)`。
      * `.c/.cc/.cpp/.S -> .o`。
    - 3.4.1. **依赖库编译**: 
      * 对 `am`、`klib` 等库执行递归 make archive。
      * 返回 `.a` 文件。
    - 3.5. **链接 ELF**: 
      * `.o` + `.a` → 最终 `IMAGE.elf`。
    - 3.6. **insert-arg**:(前进到8)
      * 嵌入 `mainarg` 到 ELF 镜像。
    - 3.7. **完成**: 
      * 返回给用户最终 ELF 或 archive 文件。
      * Platform 运行相关Makfile

4. MEMU Makefile 调用时序图

    ```mermaid
    sequenceDiagram
      autonumber
      participant User as User
      participant Config as menuconfig / auto.conf
      participant MEMU as MEMU Makefile
      participant Compiler as Compiler (CC/CXX)
      participant RTL as RTL/Chisel
      participant Diff as DIFF Reference
      participant Exec as MEMU_EXEC
      %% 4.0 menuconfig
      User->>MEMU:
      MEMU->>Config: 检查 .config 存在
      Config-->>MEMU: 生成 .config, auto.conf, auto.conf.cmd
      %% 4.1 环境检查
      MEMU->>MEMU: 检查 MEMU_HOME 是否有效
      %% 4.2 编译设置
      MEMU->>Compiler: include filelist.mk <br> 收集 csrc/**/*.c, 过滤黑名单
      MEMU->>Compiler: 设置 CC, CFLAGS, LDFLAGS <br> 支持 LTO, ASAN, 调试选项
      %% 4.3 项目编译
      %% 4.3.1 RTL/Chisel 支持
      alt CONFIG_NPC=y
          Compiler->>RTL: chisel scala -> verilog
          RTL->>RTL: verilate -> VLIB
          RTL-->>Compiler:
      end
      %% 4.3.2 差分测试 DIFFTEST
      alt CONFIG_DIFFTEST=y
          Compiler->>Diff: 构建 DIFF_REF_SO
          Diff-->>Compiler: run 时添加 --diff=DIFF_REF_SO
      end
      Compiler->>Exec: Build: 编译 OBJ, 链接 BINARY
      %% 4.4 最终执行
      User->>Exec: run / run-sdb / gdb
      Exec-->>User: MEMU_EXEC 执行完成
    ```

    - 4.0. **menuconfig**
      * menuconfig 生成配置文件 .config auto.conf auto.conf.cmd
    - 4.1. **环境检查**: 
      * 确保 `MEMU_HOME` 指向 MEMU 仓库
      * `.config` 文件必须存在，否则提示 `make menuconfig`
    - 4.2. **源文件收集**: 
      * `filelist.mk`: 包含 `csrc/**/*.c` ...
      * 过滤黑名单目录/文件
    - 4.3. **编译器配置**: 
      * 根据 menuconfig 设置 CC、CFLAGS、LDFLAGS
      * 支持 LTO、ASAN、调试选项
    - 4.4. **项目编译**: 
      * 遍历 am/klib 等库构建 `.a`
      * 与 OBJ 一起链接最终可执行文件
    - 4.4.1. **RTL/Chisel 支持**: 
      * 如果配置 NPC（用 RTL CPU），生成 Verilog
      * 使用 Verilator 生成 VLIB
    - 4.4.2. **差分测试（DIFFTEST）**: 
      * 构建参考实现 SO 文件
      * run 时加 `--diff=DIFF_REF_SO` 参数
    - 4.5. **最终执行**: 
      * MEMU_EXEC 可以运行 batch 模式、SDB 调试模式或 gdb

---

