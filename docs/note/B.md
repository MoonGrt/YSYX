# B阶段
## B1 总线

1. 评估单周期NPC的主频和程序性能
microbench 的 train 规模测: am-kernels/benchmarks/microbench

> 跑分时关闭 NEMU 的监视点, trace, DiffTest, 同时取消 menuconfig 中的 `Enable debug information` 并重新编译NEMU, 以获得较为真实的跑分

```bash
cd $AM_TEST_HOME/benchmarks/microbench
make ARCH=riscv32e-memu run mainargs=train
```

```
[MEMU] Welcome to riscv32-MEMU-npc-riscv32e!
[MEMU] For help, type "help"
======= Running MicroBench [input *train*] =======
[qsort] Quick sort: * Passed.
  min time: 1056.504 ms [0]
[queen] Queen placement: * Passed.
  min time: 1422.238 ms [0]
[bf] Brainf**k interpreter: * Passed.
  min time: 1885.735 ms [0]
[fib] Fibonacci number: * Passed.
  min time: 25040.079 ms [0]
[sieve] Eratosthenes sieve: * Passed.
  min time: 1715.377 ms [0]
[15pz] A* 15-puzzle search: * Passed.
  min time: 1412.233 ms [0]
[dinic] Dinic's maxflow algorithm: * Passed.
  min time: 685.078 ms [0]
[lzip] Lzip compression: * Passed.
  min time: 778.658 ms [0]
[ssort] Suffix sort: * Passed.
  min time: 2082.401 ms [0]
[md5] MD5 digest: * Passed.
  min time: 1894.344 ms [0]
==================================================
MicroBench PASS
Scored time: 37972.647 ms
Total  time: 42478.522 ms
[MEMU] EBREAK exception
[csrc/cpu/cpu-exec.c:140 cpu_exec] memu: HIT GOOD TRAP at pc = 0x800055fc
[csrc/cpu/cpu-exec.c:109 statistic] host time spent = 42,481,315 us
[csrc/cpu/cpu-exec.c:110 statistic] total guest instructions = 195,143,195
[csrc/cpu/cpu-exec.c:111 statistic] simulation frequency = 4,593,624 inst/s
```

> nangate45 工艺下主频为 ~~51.491MHz~~ → microbench 需要运行 3.870s. (仿真花费了 42478.522 ms)

2. 评估多周期NPC的主频和程序性能
microbench 的 train 规模测: am-kernels/benchmarks/microbench

> 跑分时关闭 NEMU 的监视点, trace, DiffTest, 同时取消 menuconfig 中的 `Enable debug information` 并重新编译NEMU, 以获得较为真实的跑分

```bash
cd $AM_TEST_HOME/benchmarks/microbench
make ARCH=riscv32e-memu run mainargs=train
```

```
[MEMU] Welcome to riscv32-MEMU-npc-riscv32e!
[MEMU] For help, type "help"
======= Running MicroBench [input *train*] =======
[qsort] Quick sort: * Passed.
  min time: 3457.054 ms [0]
[queen] Queen placement: * Passed.
  min time: 4811.926 ms [0]
[bf] Brainf**k interpreter: * Passed.
  min time: 6105.016 ms [0]
[fib] Fibonacci number: * Passed.
  min time: 80542.522 ms [0]
[sieve] Eratosthenes sieve: * Passed.
  min time: 5518.897 ms [0]
[15pz] A* 15-puzzle search: * Passed.
  min time: 4824.460 ms [0]
[dinic] Dinic's maxflow algorithm: * Passed.
  min time: 2557.861 ms [0]
[lzip] Lzip compression: * Passed.
  min time: 2662.568 ms [0]
[ssort] Suffix sort: * Passed.
  min time: 6656.292 ms [0]
[md5] MD5 digest: * Passed.
  min time: 6362.659 ms [0]
==================================================
MicroBench PASS
Scored time: 123499.255 ms
Total  time: 137964.751 ms
[MEMU] EBREAK exception
[csrc/cpu/cpu-exec.c:147 cpu_exec] memu: HIT GOOD TRAP at pc = 0x800055fc
[csrc/cpu/cpu-exec.c:116 statistic] host time spent = 137,972,011 us
[csrc/cpu/cpu-exec.c:117 statistic] total guest instructions = 616,613,764
[csrc/cpu/cpu-exec.c:118 statistic] simulation frequency = 4,469,122 inst/s
```

> nangate45 工艺下主频为  → microbench 需要运行 . (仿真花费了 137964.751 ms)

### 避免握手的死锁和活锁

- 发送方不能等待 `ready` 才拉高 `valid`。
- `valid` 拉高后，在 `valid && ready` 握手前必须保持为高，负载也必须稳定。
- 接收方可以等待 `valid` 再拉高 `ready`，也可以提前拉高；为降低延迟通常提前拉高。
- 只有 `valid && ready` 同周期为高才算传输完成，双方才能更新状态。

因此，死锁由“双方互等”避免，活锁由“发送方不得在握手前撤销 `valid`”避免。

## B2 SoC计算机系统

### char-test：裸机与 AM

讲义中的裸机版本直接提供 `_start()`，写两次 UART 后死循环：

```c
void _start() {
  *(volatile char *)0x10000000 = 'A';
  *(volatile char *)0x10000000 = '\n';
  while (1);
}
```

```bash
make bare
```

它没有函数调用、栈和全局数据，只需把代码放入 MROM `0x20000000`，因此不需要
SRAM 链接脚本。

AM 版本提供 `main()`，执行路径为：

```text
_start -> 初始化 sp -> _trm_init -> main -> halt
```

```bash
make ARCH=riscv32e-soc run
```

AM 暴露了裸机版本没有覆盖的问题：

- 旧 `linker.ld` 把栈放到 `0x20009000`，首次压栈访问未映射的
  `0x20008ffc`，AXI 无响应；专用链接脚本应把栈放入
  `0x0f000000–0x0f001fff` 的 SRAM。
- 日志虽然最后显示 UART 的 `sb`，真正阻塞的可能是更早的栈写；日志出现指令
  不代表指令已经退休。
- AM 会产生更多 store，要求 LSU 只在 `valid && ready` 握手后退休，否则栈写
  或 UART 写会丢失。
- AM 平台的入口、栈和设备地址都必须符合 SoC 地址图。

裸机 char-test 只能验证 MROM 取指和 UART 通路；AM char-test 才会继续验证链接
脚本、SRAM 栈、运行时和总线背压。

### 支持全局变量的写入操作

- `.text/.rodata` 的 VMA、LMA 都在 MROM。
- `.data` 的 VMA 在 SRAM，LMA 在 MROM；启动代码通过 `LOADADDR(.data)` 得到
  MROM 初值地址，并在调用 `main()` 前复制到 SRAM。
- `.bss` 是 `NOLOAD`，镜像中没有初值，因此启动代码必须主动清零。
- 数据的 SRAM 地址必须在链接阶段确定，因为指令中的全局变量地址会在重定位时
  固化，运行时再决定地址已经太晚。
- 链接时还要检查 MROM 镜像以及 SRAM 中 `.data + .bss + heap` 是否越界；
  仅设置 `AT>` 并不能替代这些容量检查。

`mem-test` 使用带初值和无初值的可写全局变量，验证了 `.data` 搬运、`.bss`
清零和运行时写回。

### 通过串口输出

未初始化 UART 时最多只能看到 16 个字符，因为 UART16550 的发送 FIFO 深度为
16，除数为 0 时发送器不工作，FIFO 填满后后续字符被丢弃。

TRM 的处理流程：

1. 置 `LCR.DLAB`，写 DLL/DLM 配置非零除数。
2. 清除 `DLAB`，配置 `8N1` 并复位 FIFO。
3. `putch()` 写 THR 前轮询 `LSR.THRE`，等待发送 FIFO 为空。

此外，UART 寄存器由地址低位选择。LSU 若把 `0x10000003`、`0x10000005`
统一对齐成 `0x10000000`，LCR/LSR 就会被误访问为 THR；UART 事务必须保留低
地址位。修复后 `hello` 能完整输出超过 16 字符的两行文本。

### 可重复编程的非易失存储器

- Flash 镜像为 16 MiB，烧录到偏移 0；DPI `flash_read()` 按 24 位地址读出
  32 位数据。`0x30000000–0x3fffffff` 为只读 XIP 区，写入会直接报错。
- SPI master 的寄存器仍映射在 `0x10001000–0x10001fff`。bitrev 用 16 位
  传输验证串并转换；软件 `flash_read()` 发送 `03h + 24 位地址 + 32 位数据`，
  收到的数据还需按字节翻转。
- `flash-exec` 先通过软件 SPI 将字符程序搬到 SRAM 执行，再直接从 Flash
  XIP 执行，终端输出 `AA`。
- SoC 已移除 MROM，从 `0x30000000` 复位；链接脚本也将 `.text/.rodata`
  和 `.data` 的加载地址迁到 Flash，`.data/.bss/栈` 仍位于 SRAM。

问题：

- CoreMark 太慢：调小 `coremark/include/core_portme.h` 中的 `ITERATIONS`
  可缩短功能验证时间；正式跑分仍应使用规定迭代次数。
- 为什么不能在 Flash 上执行软件 `flash_read()`：取指和函数内部的 SPI
  寄存器访问会同时占用同一个 SPI master，形成重入竞争，可能死锁或破坏事务。
  应让启动代码位于 SRAM，或用独立硬件 XIP 控制器。
- 学号 CSR：`mvendorid=0x79737978`、`marchid=0x018ce26e` 已实现。
- SPI 中断等待是可选优化；当前 XIP 快速模型和软件驱动仍采用轮询。

实现中遇到的问题：

- SPI 返回字和 CPU 字节序相反，软件必须做 `bswap32`。
- 外设事务无法由 NEMU 参考模型重放，SPI 测试通过 `NO_DIFF=1` 关闭差分；
  普通 Flash 启动和 UART 测试仍可开启差分。
- 修改 SoC 基址后旧目标文件仍带有 `0x20000000`，需要清理 `memu/build`
  和 `tools/nemu-diff/build` 后重编译。
- 当前 `FAST_FLASH` XIP 使用 DPI 快速读模型，功能等价但不反映真实 SPI
  状态机延迟；软件 SPI 测试仍经过完整的 SPI master 和 Flash 引脚模型。

## B3 时序分析和优化
## B4 性能优化和简易缓存
## B5 流水线处理器






