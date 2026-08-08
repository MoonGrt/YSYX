# B阶段
## B1 总线

1. 评估单周期 NPC 的主频和程序性能

在（`npc & OpenBus Joint Compilation`）节点测试。关闭 trace、difftest、watchpoint、device 和调试信息，以 `-O3` 运行 `microbench train`：

```bash
cd am-kernels/benchmarks/microbench
make ARCH=riscv32e-memu run mainargs=train
```

运行结果为 `HIT GOOD TRAP`，共执行 `195,122,746` 条指令，宿主机 RTL 仿真耗时 `37.581 s`。该 NPC 每周期完成一条指令，因此程序需要 `195,122,746` 个周期；宿主机仿真时间不是硬件性能。

按讲义要求，STA 时临时去掉 DPI-C 和 difftest 模块，为取指、访存各接入一个异步读的 `256×32 bit` 寄存器存储器。使用 `thirdpartys/yosys-sta`、Yosys 0.48 和 Nangate45 典型工艺库：

```bash
make -C thirdpartys/yosys-sta sta \
  DESIGN=Riscv32ETOP PDK=nangate45 \
  CLK_PORT_NAME=clock CLK_FREQ_MHZ=500 \
  RTL_FILES=/path/to/Riscv32ETOP.sv
```

为保证两个寄存器存储器仍属于 `core_clock`，本次临时跳过 clock-gating；使用 `share`、`DELAY-0`，并跳过与本题无关且耗时很长的功耗报告。最终网表包含 `63,107` 个标准单元，其中 `17,696` 个触发器，单元面积为 `149,132.634 µm²`。关键路径从 PC 出发，经过指令存储器、译码和执行后到达 GPR：

- 关键路径延迟：`2.507 ns`
- 估计最高主频：`392.510 MHz`
- 500 MHz 约束下 WNS：`-0.548 ns`，因此不能运行在 500 MHz
- 理想运行时间：`195,122,746 / 392,510,000 ≈ 0.497 s`

完整综合与时序报告见 [`docs/report/npc-single-cycle`](../report/npc-single-cycle/README.md)。

这是偏乐观的综合后、布局布线前估计：未计入布线、时钟树、片外存储器和实际 I/O；两个 1 KiB 存储器也装不下 `microbench train`，所以周期数与主频来自两次独立实验，不能视为真实 SoC 的端到端性能。

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
- 学号 CSR：`mvendorid=0x79737978`、`marchid=0x018ce1ae`（十进制
  `26010030`）已实现。
- SPI 中断等待是可选优化；当前 XIP 快速模型和软件驱动仍采用轮询。

实现中遇到的问题：

- SPI 返回字和 CPU 字节序相反，软件必须做 `bswap32`。
- 外设事务无法由 NEMU 参考模型重放，SPI 测试通过 `NO_DIFF=1` 关闭差分；
  普通 Flash 启动和 UART 测试仍可开启差分。
- 修改 SoC 基址后旧目标文件仍带有 `0x20000000`，需要清理 `memu/build`
  和 `tools/nemu-diff/build` 后重编译。
- 当前 `FAST_FLASH` XIP 使用 DPI 快速读模型，功能等价但不反映真实 SPI
  状态机延迟；软件 SPI 测试仍经过完整的 SPI master 和 Flash 引脚模型。

### 存储密度更大的随机存储器

- PSRAM 实现 `EBh` Quad IO Read 和 `38h` Quad IO Write，容量为 4 MiB；字节写地址需要结合 `PSTRB` 恢复。
- PSRAM 控制器复位后先以单线发送 `35h` 进入 QPI；后续命令、地址和数据均以四线传输。上层地址映射和软件接口不变。
- 可通过 `SOC_LOAD=psram` 将程序由 Flash 经 SRAM 中的二级加载器搬到 PSRAM。
- 从 PSRAM 执行时需关闭当前 NEMU difftest；参考模型未映射 `0x80000000`。PSRAM 自测也不能覆写正在执行的同一地址区间。
- RT-Thread 的 `.data.extra/.bss.extra` 已纳入 SoC 链接与 bootloader 范围，可从 PSRAM 启动并进入 `msh`。
- SDRAM 模型支持 ACTIVE、READ、WRITE、PRECHARGE、AUTO REFRESH 和 LOAD MODE，容量为 32 MiB；使用 `SOC_LOAD=sdram` 运行程序。
- 行为模型不模拟电容漏电，因此 PRECHARGE 和 AUTO REFRESH 可以简化；ACTIVE 仍用于记录各 bank 的当前行。
- SDRAM 已用两个 x16 颗粒并联扩展为 x32：命令和地址共用，`DQ[15:0]`/`DQM[1:0]` 连接低位颗粒，`DQ[31:16]`/`DQM[3:2]` 连接高位颗粒。
- 控制器使用 BL=1，一条 READ/WRITE 命令直接传输 32 位，不再用 BL=2 分两拍拼接半字；映射仍保留为 32 MiB，未实现后续的字扩展。
- `make -C memu/tests/perip/sdram32 test` 验证单命令读写、两个颗粒的数据分配和字节写掩码；SoC 的 SDRAM 测试也通过。

### 链接器、启动代码与 Bootloader

链接脚本、`start.S` 及 FSBL/SSBL 的完整分析已整理到
[SoC 链接脚本、启动代码与 Bootloader](linker-boot.md)。

### 接入更多外设

- GPIO 位于 `0x10002000`：`+0x0` 控制 16 个 LED，`+0x4` 读取 16 个拨码
  开关，`+0x8` 的 8 个十六进制半字节经硬件译码后驱动 8 个数码管。
- UART TX/RX 已绑定 NVBoard。UART16550 以 16 倍波特率工作且 DLL 为 1，
  因此 NVBoard 的串口除数使用默认值 16；`AM_UART_RX` 无数据时返回 `0xff`。
- PS/2 控制器在下降沿接收 11 位帧，检查起始位、停止位和奇校验，并用 FIFO
  保存扫描码。AM 负责解析 `e0` 扩展前缀和 `f0` 断码前缀，再转换为 AM 键码。
- VGA 帧缓冲位于 `0x21000000`，分辨率为 640×480、每像素 32 位，颜色格式为
  `00RRGGBB`。控制器用 100 MHz 时钟四分频产生约 25 MHz 像素节拍；NVBoard
  自动刷新，因此 `AM_GPU_FBDRAW` 忽略 `sync`。

在 `memu` 目录执行 `make menuconfig`，同时启用 `SOC` 和 `NVBOARD` 后，可运行：

```bash
make -C am-kernels/tests/soc-test/perip ARCH=riscv32e-soc run
make -C am-kernels/tests/soc-test/gpio ARCH=riscv32e-soc run
make -C am-kernels/tests/am-tests ARCH=riscv32e-soc SOC_LOAD=psram run mainargs=k
make -C am-kernels/tests/am-tests ARCH=riscv32e-soc SOC_LOAD=psram run mainargs=v
```

GPIO 示例等待拨码开关输入密码 `0x000f`，随后将 `marchid` 的十进制数值转换
成 packed BCD，在数码管显示学号并启动流水灯；否则 `26010030` 会被直接显示
成十六进制 `018CE1AE`。`am-tests` 的静态数据超过 8 KiB SRAM，因此通过二级加载器放入
PSRAM。前两项分别执行外设 RTL 单元测试和 SoC 软件读写回归；`mainargs=k`
测试 UART/PS2 输入，`mainargs=v` 测试 VGA。RT-Thread 的串口驱动在内置输入
耗尽后轮询 `AM_UART_RX`，可直接在 NVBoard 串口窗口输入 `help` 等命令。

#### NVBoard PS/2 键盘修复与测试

键盘无输入由两个问题共同造成：MEMU 的设备更新和 NVBoard 同时轮询 SDL 事件，
前者会提前取走键盘事件；此外，NVBoard 开始发送首帧前可能产生一次数据仍为高电平
的时钟下降沿，PS/2 接收器若直接计数，会使后续 11 位帧整体错位。

修复内容：

- SoC 不再调用主机功能设备的 `device_update()`；NVBoard 独占 SDL 事件队列，
  并在 RTL tick 中驱动外设引脚。
- PS/2 接收器只在检测到低电平起始位后开始计数。
- 扫描码 FIFO 从 8 项扩展为 32 项，以容纳按下码和断码的短时突发。

测试时启用 `SOC`、`NVBOARD` 和键盘设备，运行：

```bash
make -C thirdpartys/rt-thread-am/bsp/abstract-machine \
  ARCH=riscv32e-soc SOC_LOAD=sdram run
```

在 NVBoard 窗口中手动输入 `version`、`help`，字符能正常回显并执行对应的
RT-Thread shell 命令。自动化 X11 按键注入需要保留按下时间和字符间隔；发送过快
可能丢字符，不能据此判断人工键盘链路失败。

问题：若把帧缓冲放到普通内存，CPU 写像素和 VGA 连续读像素会竞争同一内存
端口和总线带宽；仲裁不及时会使 VGA 读数据欠载并出现花屏。实际实现通常使用
双端口缓存、突发预取、DMA 和行缓冲，而不是占用 1.17 MiB 片上寄存器型 SRAM。

### 仿真加速

软件功能调试可在 `menuconfig` 中分别启用快速 Flash、PSRAM、SDRAM，并为 PSRAM、
SDRAM 独立启用 ELF 预加载。
快速 Flash 跳过逐次 SPI XIP 传输；快速内存保留 APB/AXI 握手和字节写掩码，
但绕过 PSRAM QPI、SDRAM 命令及颗粒时序；ELF 预加载直接初始化目标存储器，
并用短跳板跳过 FSBL/SSBL 的逐字搬运。
开启 difftest 时会自动禁用快速启动。

只使用 NVBoard 键盘、UART、GPIO 时，可关闭 `Capture VGA output in NVBoard`，
避免每周期采样像素；需要验证 VGA 时应重新开启。构建使用 `O3` 和
`-march=native`。LTO 实测仅将启动时间从 `0.865 s` 降到 `0.863 s`，但明显增加
链接时间，因此未启用。

同一 RT-Thread SDRAM 镜像从启动到 `Hello RISC-V!` 由 `54.373 s` 降至
`0.852 s`，约加速 `63.8` 倍。RT-Thread 的 SDRAM/PSRAM 启动以及 char、mem、
SDRAM、PSRAM 测试均通过。验证 FSBL/SSBL、QPI 或 SDRAM 颗粒时，必须关闭对应
快速启动和快速内存选项，恢复精确模型。

## B3 时序分析和优化
## B4 性能优化和简易缓存

### 统计 IPC

在 NPC 仿真环境中分别统计动态指令数和有效周期数。动态指令数复用 IFU 已有的
`dpi_diffpc()`回调：当前处理器是顺序、非推测执行，因此每次 `ifu.io.out.fire`
都对应一条最终会提交的指令。原实现为了 Difftest 跳过第一次回调；现在 RTL 对
每条指令都调用 `dpi_diffpc()`，C++ 先增加动态指令数，再仅对第一次回调跳过
Difftest，从而不漏掉第一条指令。

周期数在统一的性能事件回调中累加，该回调受处理器内部的 `!reset`门控。因此，
复位同步和传播期间不计入 benchmark 周期。结束时输出
`IPC = instructions / cycles`和`CPI = cycles / instructions`，并处理分母为 0 的
情况。

最初曾在每次 `rtl_step()`后增加周期数，内置 8 指令程序得到 58 周期；逐周期事件
trace 只有 48 个有效周期。检查后发现多出的 10 周期位于 SoC 复位已经撤销、但
CPU 内部同步复位尚未撤销的区间。将周期统计移动到 `!reset`门控的采样回调后，
内置程序得到 8 条指令、48 周期、IPC 0.166667、CPI 6.0，统计窗口与 RTL 的实际
运行窗口一致。

### 添加性能计数器

性能事件在 `Riscv32E`顶层汇总为一个 32 位位图，并通过单个
`dpi_perf_event(events)`每周期送入仿真环境。计数器本体全部位于 C++，不会参与
综合，也不会增加流片面积或影响关键路径。目前统计以下事件：

- IFU 请求握手、响应握手和向后端交付指令；
- IFU 请求被总线阻塞、等待响应、被后端反压；
- EXU 完成计算；
- LSU 请求、响应、等待响应，以及 load/store 请求；
- compute、load、store、branch、jump、CSR/system 六类动态指令；
- 每类指令的累计执行周期和 LSU 请求到响应的累计延迟。

`microbench test`的运行方法为：

```sh
make -C am-kernels/benchmarks/microbench \
  ARCH=riscv32e-soc SOC_LOAD=psram NO_DIFF=1 mainargs=test
NVBOARD_HOME=$PWD/thirdpartys/nvboard \
  memu/build/riscv32-memu-interpreter -b \
  am-kernels/benchmarks/microbench/build/microbench-riscv32e-soc.bin
```

这里必须直接运行注入参数后的 `.bin`，原因见下文的问题记录。10 个测试项目全部
PASS，统计结果为：

| 指标 | 结果 |
| --- | ---: |
| 动态指令数 | 612690 |
| 有效周期数 | 1830075 |
| IPC / CPI | 0.334790 / 2.986951 |
| IFU 请求 / 响应 / 交付 | 612690 / 612690 / 612690 |
| EXU 完成 | 612690 |
| LSU 请求 / 响应 | 135358 / 135358 |
| load / store 请求 | 76007 / 59351 |
| LSU 总响应延迟 / 平均延迟 | 460825 / 3.404 cycles |

一致性检查成立：六类指令数之和、IFU 请求数、IFU 响应数、IFU 交付数、EXU 完成
数和动态指令数均为 612690；LSU 请求数和响应数均为 135358，并且
`76007 + 59351 = 135358`。这些等式同时检查了事件定义、握手去重和程序退出时的
末条指令统计。

### 添加性能计数器(2)

各类指令占比和按相邻交付事件归属的平均周期如下。当前核是顺序、非推测设计，
因此可将相邻指令交付之间的周期归给前一条指令；这种定义适用于当前核，但将来
加入流水线重叠和冲刷后应改为真正的提交级统计。

| 指令类别 | 数量 | 占比 | 累计周期 | 平均周期 |
| --- | ---: | ---: | ---: | ---: |
| compute | 322529 | 52.64% | 870390 | 2.699 |
| load | 76007 | 12.41% | 242445 | 3.190 |
| store | 59351 | 9.69% | 214780 | 3.619 |
| branch | 124047 | 20.25% | 407275 | 3.283 |
| jump | 30689 | 5.01% | 95047 | 3.097 |
| CSR/system | 67 | 0.01% | 133 | 1.985 |

IFU 未交付指令的周期总数为
`1830075 - 612690 = 1217385`，原因被划分为互斥类别：

| 未供给原因 | 周期数 | 占总周期 | 占未供给周期 |
| --- | ---: | ---: | ---: |
| 等待指令响应 | 143870 | 7.86% | 11.82% |
| 后端反压（主要是 LSU） | 460825 | 25.18% | 37.85% |
| IFU 请求通道阻塞 | 0 | 0% | 0% |
| IFU 状态切换/发起下一请求 | 612690 | 33.48% | 50.33% |

四项之和恰好为 1217385。最后一项恰好等于动态指令数：查看 IFU 状态机可知，
指令交付后状态回到 `sIdle`，下一周期才发起新请求，因此当前实现每条指令固定产生
一个不能交付指令的周期。这不是存储器响应慢，而是 IFU 状态机本身带来的结构性
气泡。

LSU 共完成 135358 次事务，请求到响应的总间隔为 460825 周期，平均访存延迟为
3.404 周期。它与 IFU 的后端反压周期完全相等，说明当前顺序核在 LSU 等待响应时，
反压会一路传播到 IFU，数据供给延迟不能被其他指令隐藏。store 平均周期比 load
更高，当前 LSU 对 store 同样等待写响应，没有 store buffer。

### 性能计数器的 trace

设置环境变量 `MEMU_PERF_TRACE`即可逐周期输出累计计数器 CSV；默认不打开，避免
长 benchmark 的逐周期文件 I/O 降低仿真速度。例如：

```sh
cd memu
MEMU_PERF_TRACE=/tmp/perf.csv make run
python3 scripts/plot-perf-trace.py /tmp/perf.csv -o /tmp/perf.svg
```

CSV 包含周期、IFU 请求/响应/交付、EXU 完成、LSU 请求/响应以及各种累计等待周期。
`plot-perf-trace.py`使用 Python 标准库直接生成双面板 SVG：上图显示累计完成事件，
下图显示累计 stall 周期。累计曲线的斜率表示一段时间内事件发生的速率；水平段
表示对应事件暂时没有发生。小程序的 trace 中，IFU 响应、指令交付和 EXU 完成三条
曲线最终都到达 8，验证了 trace 与结束时汇总计数一致。

最初绘图脚本使用 matplotlib，但当前环境未安装该模块，运行时报
`ModuleNotFoundError: No module named 'matplotlib'`。为使实验可直接复现，最后改为
只依赖标准库并输出 SVG，而不是要求额外安装 Python 包。

### 根据性能计数器寻找合适的性能瓶颈

以 `microbench test`的 1830075 周期为基准，候选优化对象及 Amdahl 定律估算如下。
`p`是该部分占总周期的比例；“优化 2 倍”使用
`S = 1 / (1 - p + p / 2)`，“理论上完全消除”使用`Smax = 1 / (1 - p)`。

| 候选优化对象 | p | 优化 2 倍 | 完全消除上限 |
| --- | ---: | ---: | ---: |
| 每条指令一个 IFU 固定气泡 | 33.48% | 1.2010x | 1.5033x |
| LSU/后端等待 | 25.18% | 1.1440x | 1.3366x |
| 单独的取指响应等待 | 7.86% | 1.0409x | 1.0853x |
| 所有未供给周期合计 | 66.52% | 1.4984x | 2.9870x |

因此当前最合适的首要优化对象是 IFU 固定气泡：它占比最大，成因明确，并且不需要
先设计复杂 cache。可尝试让 IFU 在交付当前指令的同周期准备或发出下一次请求，或
加入一个小型取指缓冲。若能完全删除这一个周期，理论上周期数可从 1830075 降到
1217385，IPC 从 0.3348 提升到约 0.5032，最高加速约 1.503 倍。

第二个瓶颈是数据供给。将 LSU 等待部分加速 2 倍，整机理论加速约 1.144 倍；即使
完全消除，上限也只有 1.337 倍。后续可考虑降低数据存储响应延迟，或用 store
buffer使 store 不等待写响应。不过 load 仍有真实数据依赖，简单 store buffer 只
覆盖 9.69%的 store 指令，收益必须再次测量。

当前 EXU 完成数等于动态指令数，且 EXU 自身没有单独的等待事件，因此没有证据表明
算术单元吞吐是主要 IPC 瓶颈。branch 虽占 20.25%，但当前非流水设计没有预测失败
冲刷代价；仅凭指令占比就添加分支预测器缺乏收益依据。优先改 EXU 或分支预测都不如
先消除已量化的前端固定气泡。

上述数据来自当前启用快速 Flash/PSRAM/SDRAM的仿真配置，尚未进行讲义后续要求的
访存延迟校准。因此结论只适用于当前仿真模型；校准后必须重新运行计数器和 Amdahl
分析，不能把这里的绝对 IPC 当作流片环境结果。

实现过程中还遇到两个工程问题：

1. 在 C++ 的 `exec.cc`中新使用现有 `Log()`宏时，宏内部的局部
   `extern bool log_enable()`被赋予 C++ linkage，而实现位于 C 文件，最终出现
   `undefined reference to log_enable()`。直接补 `extern "C"`又与头文件中已经出现
   的 C++ 声明冲突。性能报告最终使用带 `[PERF]`前缀的 `printf()`，避免修改公共
   日志接口而影响其他模块。
2. AM 的 `insert-arg.py`把`mainargs=test`写入生成的 `.bin`，但 MEMU 的 ELF 快速
   启动直接预加载未被修改的 `.elf`。通过原来的 `make ... run`会看到占位字符串
   `the_insert-arg_rule_in_Makefile_will_insert_mainargs_here`，实际没有运行 test。
   本次改为直接运行注入参数后的 `.bin`，关闭 ELF 快速启动后得到有效 benchmark
   数据。若以后希望保留 ELF 快速预加载，需要让参数注入同时更新 ELF 对应 section，
   或让快速启动额外从 `.bin`复制参数区域。

## B5 流水线处理器
