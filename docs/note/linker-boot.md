# SoC 链接脚本、启动代码与 Bootloader

本文整理 ysyxSoC 当前链接布局、`start.S` 启动流程以及 FSBL/SSBL 两级加载机制，并分析实现约束与常见故障。

## 链接器解决什么问题

编译器把每个源文件分别编译成目标文件，其中包含代码、数据、符号和重定位信息，
但此时函数和全局变量还没有最终地址。链接器负责：

1. 合并同类输入段，例如把各目标文件的 `.text*` 合并为输出段 `.text`。
2. 解析跨文件符号，确定函数和全局变量的最终地址。
3. 根据最终地址完成重定位，把调用目标、全局变量地址等写入指令或数据。
4. 按链接脚本生成 ELF；之后 `objcopy` 再从 ELF 生成烧入 Flash 的二进制镜像。

常用段的含义如下：

| 段 | 内容 | 是否有初值 | 启动时处理 |
| --- | --- | --- | --- |
| `.boot`/`entry` | 复位入口和 FSBL | 有 | 直接在 Flash 执行 |
| `.ssbl` | 二级加载器 | 有 | FSBL 从 Flash 搬到 SRAM |
| `.text` | 程序指令 | 有 | XIP 或搬到目标内存 |
| `.rodata`/`.srodata` | 字符串、常量、跳转表 | 有 | 必须与代码一同可访问 |
| `.data`/`.sdata` | 有初值的可写全局变量 | 有 | 从 Flash 搬到运行地址 |
| `.bss`/`.sbss` | 零初始化全局变量 | 无 | 启动代码清零 |

链接脚本中的 VMA（virtual memory address）是 CPU 运行时使用的地址，LMA
（load memory address）是该段初值在镜像中的存放地址。例如：

```ld
.ssbl ORIGIN(sram) : {
  _ssbl_start = .;
  KEEP(*(.ssbl))
  _ssbl_end = .;
} > sram AT> flash
_ssbl_load_start = LOADADDR(.ssbl);
.data : {
  _data_start = .;
  *(.data*)
  _data_end = .;
} > psram AT> flash
_data_load_start = LOADADDR(.data);
```

这里 `.data` 的 VMA 位于 PSRAM，而 LMA 位于 Flash。程序中访问全局变量时使用
PSRAM 地址；bootloader 则从 `_data_load_start` 读取初值并写到 `_data_start`。
`NOLOAD` 表示 `.bss` 不需要占用镜像空间，`KEEP()` 防止 `--gc-sections` 删除入口
不可直接引用到的加载器段，`ASSERT()` 在链接时检查容量和布局，而不是等运行时才
发现越界。

## 当前脚本的选择

`abstract-machine/scripts/platform/soc.mk` 根据 `SOC_LOAD` 选择脚本：

| 配置 | 链接脚本 | 代码运行位置 | 加载方式 |
| --- | --- | --- | --- |
| 未设置 | `linker-soc.ld` | Flash/`_pmem_start` | `.text/.rodata` XIP，只搬 `.data` |
| `sram` | `linker-soc-sram.ld` | SRAM `0x0f000000` | FSBL 搬 SSBL，SSBL 搬 payload |
| `psram` | `linker-soc-psram.ld` | PSRAM `0x80000000` | FSBL 搬 SSBL，SSBL 搬 payload |
| `sdram` | `linker-soc-sdram.ld` | SDRAM `0xa0000000` | FSBL 搬 SSBL，SSBL 搬 payload |

未设置 `SOC_LOAD` 时，`.text` 和 `.rodata` 的 VMA、LMA 都在 Flash，因此 CPU
直接 XIP。`.data` 的 VMA 在 SRAM、LMA 在 Flash，`_start` 在进入 TRM 前复制
`.data` 并清零 `.bss`。`_soc_staged_load=0` 使启动代码跳过 FSBL/SSBL 路径。

设置 `SOC_LOAD` 后使用两级加载：

```text
复位到 Flash 中的 .boot/_start
  -> FSBL 将 .ssbl 从 Flash 复制到 SRAM
  -> 跳转到 SRAM 中的 SSBL
  -> SSBL 将 .text + .rodata + .data 复制到目标存储器
  -> 清零目标存储器中的 .bss
  -> 跳转到目标存储器中的 _trm_init，最后进入 main
```

FSBL 必须留在 Flash，因为复位后 SRAM、PSRAM 和 SDRAM 都没有程序；SSBL 放在
SRAM，是为了避免在 Flash 上取指的同时继续访问 Flash，并让后续大量复制更快。
栈始终位于 8 KiB SRAM，初始 `sp=0x0f002000`，向低地址增长。PSRAM/SDRAM
脚本只把应用 payload 和堆放入大容量存储器，局部变量和函数调用仍使用快速 SRAM
栈。

## 启动代码与链接脚本如何配合

链接脚本只负责确定地址和导出边界符号，并不会自动搬运段或清零内存；真正执行
这些工作的代码是 `abstract-machine/am/src/riscv/soc/start.S`。反过来，启动代码
也不应写死镜像长度和目标地址，而应使用链接器计算出的符号。两者通过以下符号
形成约定：

| 链接符号 | 含义 | 启动代码用途 |
| --- | --- | --- |
| `_soc_staged_load` | 是否使用两级加载 | 在 XIP 与 FSBL/SSBL 路径间选择 |
| `_ssbl_load_start` | SSBL 在 Flash 中的 LMA | FSBL 复制源地址 |
| `_ssbl_start/_ssbl_end` | SSBL 在 SRAM 中的 VMA 范围 | FSBL 复制目标和长度 |
| `_payload_load_start` | payload 在 Flash 中的 LMA | SSBL 复制源地址 |
| `_payload_start/_payload_end` | payload 的运行时 VMA 范围 | SSBL 复制目标和长度 |
| `_data_load_start` | `.data` 在 Flash 中的 LMA | XIP 路径复制 `.data` |
| `_data_start/_data_end` | `.data` 的 SRAM VMA 范围 | XIP 路径复制目标和长度 |
| `_bss_start/_bss_end` | `.bss` 的 VMA 范围 | 启动代码逐字节清零 |
| `_stack_pointer` | SRAM 栈顶 | 初始化 `sp` |

入口代码首先建立最小运行环境：

```asm
_start:
  mv s0, zero
  la sp, _stack_pointer
  la a3, _soc_staged_load
  beqz a3, xip_start
```

栈必须在任何 C 函数调用前有效。当前栈位于 SRAM，复位后无需预先加载内容，直接
设置 `sp` 即可。`_soc_staged_load` 是链接期常量：默认脚本定义为 `0`，直接走
XIP 初始化；SRAM/PSRAM/SDRAM 脚本定义为 `1`，先执行 bootloader。

## FSBL：从 Flash 启动并搬运 SSBL

FSBL 就是 `.boot` 中从 `_start` 开始执行的第一阶段代码。CPU 复位 PC 为
`0x30000000`，因此 `.boot` 的 VMA 和 LMA 都位于 Flash。FSBL 使用：

```asm
la t0, _ssbl_load_start  # Flash 源地址
la t1, _ssbl_start       # SRAM 目标地址
la t2, _ssbl_end         # SRAM 结束地址
```

随后用 `lbu/sb` 逐字节复制 `[ _ssbl_start, _ssbl_end )`，最后通过
`jalr zero, 0(_ssbl_start)` 跳转到 SRAM。这里使用 `jalr zero` 而不是普通函数
调用，因为 SSBL 不需要返回 FSBL。逐字节复制对段长度和对齐没有要求；SSBL 很小，这部分性能损失可以忽略。

不能直接在 Flash 中执行 SSBL 的主要原因是：SSBL 要持续读取 Flash 中的应用
镜像。若取指和数据读取共用同一个 SPI/Flash 通路，边执行边读可能产生控制器重入
或严重串行化。先把 SSBL 搬到 SRAM 后，取指来自 SRAM，Flash 通路只负责读取
payload。

## SSBL：将完整应用搬到目标内存

`.ssbl` 通过 `KEEP(*(.ssbl))` 独立保留。SSBL 在 SRAM 中执行，并加载三个边界：

```asm
la t0, _payload_load_start  # Flash 中的镜像
la t1, _payload_start       # SRAM/PSRAM/SDRAM 运行地址
la t2, _payload_end
```

主循环在剩余长度不少于 4 字节时用 `lw/sw` 搬运，以降低 Flash 和目标存储器的
事务数；最后不足 4 字节的尾部使用 `lbu/sb`。复制内容是连续的
`.text + .rodata + .data`，因此指令、字符串、跳转表和有初值全局变量会同时到达
正确的 VMA。

`.bss` 没有 LMA 内容，不能从 Flash 复制。SSBL 单独将
`[_bss_start, _bss_end)` 清零，然后执行：

```asm
la t0, _trm_init
jalr ra, 0(t0)
```

此时 `_trm_init` 的地址已经是目标存储器中的 VMA，跳转后开始使用搬运完成的
代码和数据，最终调用 `main()`。虽然这里写入 `ra`，正常情况下 `_trm_init`
不会返回；程序结束时由 AM 的 `halt()` 处理。

## 默认 XIP 路径

未设置 `SOC_LOAD` 时不需要搬运 `.text/.rodata`，因为它们本来就在 Flash 中执行。
入口代码只执行：

```text
复制 Flash LMA 的 .data -> SRAM VMA
清零 SRAM 中的 .bss
call _trm_init -> main
```

默认脚本仍提供值为 `0` 的 `_payload_*` 占位符，使同一份 `start.S` 可以与所有
SoC 链接脚本链接；由于 `_soc_staged_load=0`，这些占位符不会在运行时被使用。

## 启动镜像的形成

ELF 同时保存各段的 VMA 和 LMA，而烧入 Flash 的 `.bin` 是按 LMA 排列的加载
镜像。因此在分阶段模式下，二进制内容依次包含 Flash 中的 `.boot`、`.ssbl`、
`.text`、`.rodata` 和 `.data` 初值；PSRAM/SDRAM 的高 VMA 不会让二进制产生几
GB 的空洞。`.bss` 理论上不需要进入镜像，因为 bootloader 会清零。

完整启动时序为：

```text
reset deassert
  -> PC = 0x30000000
  -> Flash XIP 取出 _start
  -> 设置 SRAM 栈
  -> FSBL: Flash[LMA(.ssbl)] -> SRAM[VMA(.ssbl)]
  -> PC 跳到 SRAM 中的 _ssbl_start
  -> SSBL: Flash[LMA(.text)] -> target[VMA(.text..data)]
  -> 清零 target[.bss]
  -> PC 跳到 target[_trm_init]
  -> 初始化 UART/TRM
  -> main()
```

## 不匹配时的典型故障

- VMA 正确但未搬运：CPU 跳到 SRAM/PSRAM 后读到随机指令，立即触发非法指令。
- LMA 或复制长度错误：前几条指令可能正常，访问 `.rodata/.data` 或较后函数时
  才出错，表现为字符串损坏、跳转表跳飞或全局变量初值错误。
- `.bss` 未清零：C 语言要求的零初始化不成立，程序行为依赖上电随机值。
- `_stack_pointer` 位于未映射区域：首次函数压栈就会产生总线错误，看起来像程序
  卡在调用 `main()` 之前。
- SSBL 超过预留 SRAM 区域：会覆盖 payload 或栈；SRAM 脚本目前通过
  `ASSERT(SIZEOF(.ssbl) <= 0x100)` 在链接期阻止这一情况。
- 修改链接脚本但未重新链接：旧 ELF 中的地址已经完成重定位，仅重新运行仿真
  不会更新地址，必须清理并重新生成镜像。

## `start.S` 逐段分析

`start.S` 中的 `entry` 段包含复位入口 `_start`：

```asm
.section entry, "ax"
.globl _start
.type _start, @function
```

`"ax"` 表示该段需要分配内存且允许执行；`.globl` 让链接器可以把 `_start` 作为
全局入口，链接脚本中的 `ENTRY(_start)` 则把它写入 ELF 入口地址。

入口首先初始化帧指针和栈：

```asm
_start:
  mv s0, zero
  la sp, _stack_pointer
```

`mv s0, zero` 清空初始帧指针，`la` 把链接符号 `_stack_pointer` 表示的地址装入
`sp`。`la` 取的是符号值，不会读取该地址中的内存。

接着选择启动方式：

```asm
  la a3, _soc_staged_load
  beqz a3, 8f
```

`_soc_staged_load` 是链接脚本定义的绝对符号。值为 `0` 时，`beqz` 跳到后方最近
的 `8:`，进入 XIP 初始化路径；值为 `1` 时继续执行 FSBL。`8f` 中的 `f` 表示
forward，即向后寻找编号为 `8:` 的局部标签。

FSBL 的字节复制循环为：

```asm
  la t0, _ssbl_load_start
  la t1, _ssbl_start
  la t2, _ssbl_end
1:
  bgeu t1, t2, 2f
  lbu a0, 0(t0)
  sb a0, 0(t1)
  addi t0, t0, 1
  addi t1, t1, 1
  j 1b
2:
  la t0, _ssbl_start
  jalr zero, 0(t0)
```

`t0` 是 Flash 源指针，`t1` 是 SRAM 目标指针，`t2` 是目标结束地址。
`bgeu` 使用无符号地址比较，在 `t1 >= t2` 时跳到后方 `2:`；否则用 `lbu/sb`
复制一个字节并递增指针。`j 1b` 中的 `b` 表示 backward，即回到前方最近的
`1:`。完成后 `jalr zero` 跳到 SRAM 中的 SSBL，同时丢弃返回地址。

数字标签只在汇编文件局部使用，并且可以重复：`1b` 表示前方最近的 `1:`，
`1f` 表示后方最近的 `1:`。因此后面的 XIP 和 SSBL 循环也可以再次使用
`1:`、`2:`，不会发生符号冲突。

默认 XIP 路径从 `8:` 开始：

```asm
8:
  la t0, _data_load_start
  la t1, _data_start
  la t2, _data_end
1:
  bgeu t1, t2, 2f
  lbu a0, 0(t0)
  sb a0, 0(t1)
  addi t0, t0, 1
  addi t1, t1, 1
  j 1b
```

这段只把 `.data` 初值从 Flash 搬到 SRAM，因为 `.text/.rodata` 仍在 Flash
中 XIP，不需要复制。随后清零 `.bss`：

```asm
2:
  la t1, _bss_start
  la t2, _bss_end
3:
  bgeu t1, t2, 4f
  sb zero, 0(t1)
  addi t1, t1, 1
  j 3b
4:
  call _trm_init
```

`sb zero` 逐字节建立 C 语言要求的零初始化状态，之后 `call` 跳转到 TRM；
`call` 是会把返回地址写入 `ra` 的伪指令。

SSBL 被放入独立的 `.ssbl` 段：

```asm
.section .ssbl, "ax"
_ssbl_start:
  la t0, _payload_load_start
  la t1, _payload_start
  la t2, _payload_end
```

其复制循环优先一次搬运 4 字节：

```asm
3:
  bgeu t1, t2, 4f
  sub a1, t2, t1
  li a2, 4
  bltu a1, a2, 7f
  lw a0, 0(t0)
  sw a0, 0(t1)
  addi t0, t0, 4
  addi t1, t1, 4
  j 3b
```

`sub` 计算剩余字节数；不少于 4 字节时使用 `lw/sw`，减少总线事务。剩余不足
4 字节时跳到尾部循环：

```asm
7:
  lbu a0, 0(t0)
  sb a0, 0(t1)
  addi t0, t0, 1
  addi t1, t1, 1
  j 3b
```

尾部复制后重新回到 `3:` 检查是否到达 `_payload_end`。payload 完成后，SSBL
用同样的逐字节循环清零目标内存中的 `.bss`，最后跳转到已经搬运完成的 TRM：

```asm
6:
  la t0, _trm_init
  jalr ra, 0(t0)
```

这里必须用 `_trm_init` 的 VMA；若错误地跳到它的 Flash LMA，就会继续在镜像
副本而不是目标内存中执行。当前 `start.S` 同时适用于 SRAM、PSRAM 和 SDRAM，
具体目标地址完全由所选链接脚本给出的 `_payload_*` 与 `_bss_*` 符号决定。

## 为什么 `.rodata` 也会被搬运

三个分阶段脚本都按以下顺序连续布置 payload：

```text
_payload_start -> .text -> .rodata -> .data -> _payload_end
```

SSBL 从 `_payload_load_start` 连续复制到 `_payload_end`，所以复制范围不仅包含
指令，也包含字符串常量、常量数组以及编译器生成的跳转表。若只复制 `.text`，
普通直线代码可能暂时正常，但 `printf` 字符串或使用跳转表的 `switch` 会读取错误
内容，甚至跳到非法地址。`.bss` 不在 payload 中，因为它没有初值，单独清零即可。

## 当前实现的约束和风险

- `linker-soc-sram.ld` 为 SSBL 预留 `0x100` 字节，并用 `ASSERT` 检查；应用从
  `0x0f000100` 开始，`.bss` 结束地址不得越过 `0x0f001000`，上方空间留给栈。
- PSRAM 和 SDRAM 脚本分别检查 4 MiB、32 MiB payload/BSS 上界，且检查 Flash
  中的加载镜像不超过 16 MiB；PSRAM 自测不能从 PSRAM 执行后再覆盖自身代码。
- 分阶段复制假定 `.text/.rodata/.data` 的 VMA 布局与 Flash 中 LMA 布局具有相同
  的连续偏移。后续若插入带特殊对齐的新段，应把它纳入 payload 并检查 VMA/LMA
  间隙，否则一次连续复制可能错位。
- `linker-soc-sram.ld` 当前令 `_heap_start` 位于 SRAM，而 `_heap_end` 指向 PSRAM
  末端。两者之间并非连续物理内存，通用 bump allocator 可能越过 SRAM 后进入
  未映射地址；更合理的做法是让 SRAM 模式的堆止于栈下界，或显式建立独立的
  PSRAM heap。
- `linker-soc.ld` 的启动地址来自 `CONFIG_MBASE_SOC`，另外三个分阶段脚本则固定
  Flash 为 `0x30000000`。修改 SoC 地址图时必须同步链接脚本并彻底清理旧 ELF/RTL
  构建产物。
- `--gc-sections` 会删除不可达段，入口和二级加载器必须分别通过 `ENTRY(_start)`、
  `KEEP(*(.ssbl))` 保留。检查最终布局应以 ELF 为准，而不能只看源链接脚本。

常用检查命令：

```bash
riscv64-linux-gnu-readelf -lW build/program.elf
riscv64-linux-gnu-readelf -SW build/program.elf
riscv64-linux-gnu-nm -n build/program.elf | grep -E '_start|_ssbl|_payload|_data|_bss|_stack|_heap'
riscv64-linux-gnu-objdump -h build/program.elf
```

`readelf -lW` 用于对照段的 VMA（`VirtAddr`）、LMA（`PhysAddr`）和镜像大小；
`readelf -SW`/`objdump -h` 用于确认各输出段的位置；`nm` 用于确认 bootloader
使用的边界符号是否与预期一致。

## RT-Thread 的额外段

RT-Thread 的 `extra.ld` 会生成 `.data.extra` 和 `.bss.extra`，用于保存 FinSH
符号表、组件初始化表以及集成 AM 应用的数据。它们是独立输出段，
`INSERT BEFORE .data` 并不等于并入 `.data`。

SoC 使用单独的 `extra-soc.ld`：

- `.data.extra` 的 VMA 紧跟 `.rodata`，LMA 也紧跟 Flash 中的 `.rodata`。
- `.data` 从 `_data_extra_vma_end/_data_extra_load_end` 继续，避免两个段重叠。
- `.bss.extra` 紧跟 `.data`，普通 `.bss` 从 `_bss_extra_vma_end` 继续。
- `_bss_start` 指向 `.bss.extra` 起点，使 bootloader 将两个 BSS 段一起清零。

此外，分阶段脚本将 payload 的 Flash LMA 对齐到 `0x1000`，并保持
`.text/.rodata/.data.extra/.data` 的 LMA 相对偏移与 VMA 相对偏移一致。否则 SSBL
虽然连续复制整个 payload，段间对齐差异仍会让 `.rodata` 和后续数据错位。

验证最终 ELF 时，不能只确认段位于 PSRAM，还应比较每个段的相对偏移：

```text
VMA(section) - VMA(.text) == LMA(section) - LMA(.text)
```

修复后 RT-Thread 可从 PSRAM 启动，正确识别 AM 应用数据/BSS，进入 `msh`，并
正常执行 `help`、`free`、`ps` 和 `memtrace`。
