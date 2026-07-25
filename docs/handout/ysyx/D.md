> 来源：[https://ysyx.oscc.cc/docs/2407/d/1.html](https://ysyx.oscc.cc/docs/2407/d/1.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# D1 支持RV32IM的NEMU

#### 课件和视频

讲义内容未就绪, 编程内容见下文提到的PA部分, 大家可以先参考[课件](https://ysyx.oscc.cc/slides/2306/08.html#/)和[视频](https://www.bilibili.com/video/BV15h4y1A7Up)进行学习.

通过PA1复习完C语言之后, 你就可以用C语言来实现一个RISC-V处理器(的模拟器)了! 实现这个模拟器可以让你对RISC-V指令集和处理器的行为有一个初步的了解, 为接下来用RTL实现一个真正的处理器做好准备.

#### 实现支持RV32IM的NEMU

根据PA讲义完成, PA2阶段1, 直到你看到如下提示框:

#### 温馨提示

PA2阶段1到此结束.


---

> 来源：[https://ysyx.oscc.cc/docs/2407/d/2.html](https://ysyx.oscc.cc/docs/2407/d/2.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# D2 程序的机器级表示

#### 课件和视频

讲义内容未就绪, 但本小节暂无编程内容, 大家可以先参考课件([上](https://ysyx.oscc.cc/slides/2306/09.html#/), [下](https://ysyx.oscc.cc/slides/2306/10.html#/))和视频([上](https://www.bilibili.com/video/BV1ow411275B), [下](https://www.bilibili.com/video/BV19H4y1d7Yi))进行学习.


---

> 来源：[https://ysyx.oscc.cc/docs/2407/d/3.html](https://ysyx.oscc.cc/docs/2407/d/3.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# D3 运行时环境

#### 课件和视频

讲义内容未就绪, 编程内容见下文提到的PA部分, 讲义内容未就绪, 可以先参考[课件](https://ysyx.oscc.cc/slides/2306/11.html#/)和[视频](https://www.bilibili.com/video/BV1Vu4y1s73Y)进行学习.

在这一小节中, 我们将会先带大家了解程序和计算机硬件之间的一层重要的抽象: 运行时环境. 同时我们也会引导大家搭建更强大的基础设施, 它们将会在后续设计NPC的时候发挥强大的作用.

#### 理解运行时环境

根据PA讲义, 完成PA2中的"程序, 运行时环境与AM".


---

> 来源：[https://ysyx.oscc.cc/docs/2407/d/4.html](https://ysyx.oscc.cc/docs/2407/d/4.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# D4 用RTL实现迷你RISC-V处理器

有了AM, 我们就可以考虑用RTL实现一个更强大的处理器, 并在处理器上运行更多程序. 不过如F阶段所分析, sISA由于过于简单, 很难支撑更多程序的运行, 因此, 我们先考虑将E阶段用RTL实现的NPC"升级"为一个minirv处理器. 借助minirv的完备性, 我们就可以在NPC上运行更多程序了.

## 模块化的RTL设计

和sCPU不同, 将来我们还会不断改进NPC, 在其中添加更多的功能. 因此, 我们有必要维护好NPC项目, 为将来的改进做好准备. 维护代码的一个方式就是模块化.

回顾minirv的ISA规范:

- PC初值为`0`
- GPR数量与RV32E中定义的GPR数量一致
- 支持如下8条指令: `add`, `addi`, `lui`, `lw`, `lbu`, `sw`, `sb`, `jalr`
- 其他的ISA细节与RV32I相同

从指令类型来看, minirv的指令涵盖的功能包括加法, 位拼接, 访存和跳转. 我们可以根据这些功能, 结合处理器的工作流程给NPC划分模块:

- IFU(Instruction Fetch Unit): 负责根据当前PC从存储器中取出一条指令
- IDU(Instruction Decode Unit): 负责对当前指令进行译码, 准备执行阶段需要使用的数据和控制信号
- EXU(EXecution Unit): 负责根据控制信号控制ALU, 对数据进行计算
- LSU(Load-Store Unit): 负责根据控制信号控制存储器, 从存储器中读出数据, 或将数据写入存储器
- WBU(WriteBack Unit): 将数据写入寄存器, 并更新PC

你需要自行梳理出模块之间的接口. 当然, 你也可以自行决定将哪些部件放置在哪一个模块中. 一个例外是存储器, 为了方便测试, 我们不打算通过RTL来实现这个存储器, 而是用C++来实现它. 当前, 我们先考虑一种最简单的实现方式: 将存储器访问接口的信号拉到顶层, 通过C++代码来访问存储器.

```
while (???) {
  ...
  top->inst = pmem_read(top->pc);
  top->eval();
  ...
}
```

你可以很容易地通过C++代码来实现一个简单的存储器.

## 只有两条指令的minirv处理器

接下来, 我们来实现一条最简单的指令: `addi`. 你已经在F阶段中用Logisim实现了minirv处理器, 因此你应该已经有一个相对完整的处理器架构图, 或者能够在心中想象指令如何在上述模块中执行. 有了架构图或者指令执行流程, 要用RTL描述相关的模块, 就很容易了.

#### 在NPC中实现addi指令

具体地, 你需要注意以下事项:

- 存储器中可以放置若干条`addi`指令的二进制编码(可以利用0号寄存器的特性来编写行为确定的指令)
- 由于目前未实现跳转指令, 因此NPC只能顺序执行, 你可以在NPC执行若干指令之后停止仿真
- 可以通过查看波形, 或者在RTL代码中打印通用寄存器的状态, 来检查`addi`指令是否被正确执行
- 关于通用寄存器, 其电路本质是一个存储器. 为了避免选择Verilog的同学编写出不太合理的行为建模代码, 我们给出如下不完整的代码供大家补充(大家无需改动`always`代码块中的内容):

```
module RegisterFile #(ADDR_WIDTH = 1, DATA_WIDTH = 1) (
  input clk,
  input [DATA_WIDTH-1:0] wdata,
  input [ADDR_WIDTH-1:0] waddr,
  input wen
);
  reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];
  always @(posedge clk) begin
    if (wen) rf[waddr] <= wdata;
  end
endmodule
```

- 你还需要思考如何实现0号寄存器的特性
- 使用NVBoard需要RTL代码比较好地支持设备, 我们会在B阶段再讨论这个问题, 目前不必接入NVBoard

#### 不知道如何下手?

你很可能会遇到以下问题:

- 如何通过PC值正确地访问存储器?
- 如何在存储器中放置`addi`指令?
- 如何仅执行若干指令后结束仿真?
- 通用寄存器模块的端口应该如何设计?

在预学习阶段搭建verilator框架的时候, 我们就已经提醒过大家: 项目里面的所有细节都是和大家有关系的. 每当你觉得没有思路的时候, 这很大概率是在提醒你, 你很可能在之前的学习中有什么没做好. 相比于询问同学, 你其实更应该回顾之前的实验内容, 并尽自己最大努力理解每一处细节, 从而找到上述问题的答案.

#### 在NPC中实现jalr指令

实现后`addi`和`jalr`指令后, 让NPC运行之前在Logisim上运行过的那个两条指令的测试程序, 并检查NPC的运行结果是否符合预期.

## 让程序决定仿真何时结束

我们刚才是让仿真环境(C++代码)来决定执行多少条指令后结束仿真, 或者让NPC一直执行, 直到陷入一个预期的死循环, 来表示程序运行结束. 但这些做法并不具有很好的通用性: 你需要提前知道一个程序执行多少条指令才能结束. 有没有方法可以在程序执行结束的时候自动结束仿真呢?

事实上, NEMU已经给了一个很好的解决方案了: trap指令. NEMU实现了一条特殊的`nemutrap`指令, 用于指示客户程序的结束, 具体地, 在RISC-V中, NEMU选择了`ebreak`指令来作为`nemutrap`指令. 事实上在NPC中, 我们也可以实现类似的功能: 如果程序执行了`ebreak`指令, 就通知仿真环境结束仿真.

要实现这一功能并不困难, 你首先需要在NPC中添加`ebreak`指令的支持. 不过, 为了让NPC在执行`ebreak`指令的时候可以通知仿真环境, 你还需要实现一种RTL代码和C++代码之间的交互机制. 我们借用system verilog中的DPI-C机制来实现这一交互.

#### 尝试DPI-C机制

阅读verilator手册, 找到DPI-C机制的相关内容, 并尝试运行手册中的例子.

#### 通过DPI-C实现ebreak

在RTL代码中利用DPI-C机制, 使得在NPC执行`ebreak`指令的时候通知仿真环境结束仿真. 实现后, 在上述程序中`halt()`函数的位置放置一条`ebreak`指令来进行测试. 如果你的实现正确, 仿真环境就无需关心程序何时结束仿真了, 它只需要不停地进行仿真, 直到程序执行`ebreak`指令为止.

如果你使用Chisel, 你可以借助Chisel中的BlackBox机制调用Verilog代码, 然后让Verilog代码通过DPI-C机制与仿真环境交互. 关于BlackBox的使用方式, 请查阅相关资料.

## 实现完整的minirv处理器

你需要实现剩下的6条minirv指令, 包括`add`, `lui`, `lw`, `lbu`, `sw`, `sb`. 其中, 前两条都是整数计算指令, 它们和sISA中的`add`和`li`指令非常类似. 你已经在E阶段中实现过sISA的这两条指令了, 因此这对你来说并不困难.

为了实现剩下的4条访存指令, 我们需要进行一些额外的考量. 访存指令需要访问存储器, 与取指不同, 访存指令还可能需要将数据写入存储器. 我们之前把取指的接口拉到顶层的简单实现方式, 并不能正确实现访存指令, 这是因为访存接口的信号会依赖于当前取到的指令, 而仿真环境无法正确地处理这个依赖关系. 为了解决这个问题, 我们可以通过DPI-C机制来实现访存:

```
import "DPI-C" function int pmem_read(input int raddr);
import "DPI-C" function void pmem_write(
  input int waddr, input int wdata, input byte wmask);
reg [31:0] rdata;
always @(*) begin
  if (valid) begin // 有读写请求时
    rdata = pmem_read(raddr);
    if (wen) begin // 有写请求时
      pmem_write(waddr, wdata, wmask);
    end
  end
  else begin
    rdata = 0;
  end
end
```

```
extern "C" int pmem_read(int raddr) {
  // 总是读取地址为`raddr & ~0x3u`的4字节返回
}
extern "C" void pmem_write(int waddr, int wdata, char wmask) {
  // 总是往地址为`waddr & ~0x3u`的4字节按写掩码`wmask`写入`wdata`
  // `wmask`中每比特表示`wdata`中1个字节的掩码,
  // 如`wmask = 0x3`代表只写入最低2个字节, 内存中的其它字节保持不变
}
```

我们在这两个内存读写函数中模拟了32位总线的行为: 它们只支持地址按4字节对齐的读写, 其中读操作总是返回按4字节对齐读出的数据, 需要由RTL代码根据读地址选择出需要的部分. 这样是为了将来在实现总线的时候不必改动太多的代码. 你需要在Verilog代码中为这两个函数的调用传入正确的参数, 并在C++代码中实现这两个函数的功能. 对于取指, 你需要删除之前把信号拉到顶层的实现, 然后额外调用一次`pmem_read()`来实现它.

和实现minirvEMU的时候一样, 为了运行更大的程序, 手动对存储器进行初始化是很低效的. 为了提高效率, 我们可以让仿真环境从命令行中读入程序的路径, 然后把程序内容放置到存储器中.

#### 实现完整的minirv处理器

为NPC添加剩余的6条minirv指令, 并通过更新加载程序的方式, 然后在NPC上运行之前在Logisim上运行过的`sum`和`mem`两个程序. 为了判断程序是否成功结束运行, 你可以在NPC开始仿真之前, 在存储器中`halt()`函数对应的位置放置一条`ebreak`指令.

## 搭建面向minirv的AM运行时环境

你已经可以通过AM项目将方便地将程序编译到`riscv32-nemu`上. 类似地, 我们也可以通过类似的方式, 快速地将程序编译到`minirv-npc`上, 从而通过更多的程序来测试NPC的实现是否正确.

#### 更新AM

我们在2025/05/03 12:30:00将在AM中添加了`minirv-npc`的支持. 如果你在上述时间之前获得AM的代码, 你可以通过以下命令获取新版本:

```
cd ysyx-workbench
cp -r abstract-machine/klib .  # 备份klib的实现, 如果你之前还改动了AM中的其他代码, 请手动备份它们
rm -rf abstract-machine
bash init.sh abstract-machine
rm -rf abstract-machine/klib
mv klib abstract-machine       # 恢复klib, 如果你之前还备份了AM中的其他代码, 请手动恢复它们
```

AM项目已经提供了`minirv-npc`的基本框架, 你只需要在`am-kernels/tests/cpu-tests/`目录下执行

```
make ARCH=minirv-npc ALL=xxx
```

即可将名为`xxx`的测试编译到`minirv-npc`的运行时环境中. 不过, 为了兼容加接下来的设备功能, `minirv-npc`约定程序从`0x80000000`开始, 你需要修改PC的初值, 从而满足`minirv-npc`这个运行时环境的约定.

为了熟悉流程, 我们先尝试在NPC中运行dummy程序.

#### 一键编译并在NPC上运行AM程序

在AM项目中, Makefile并没有为`minirv-npc`提供`run`目标. 尝试为`minirv-npc`提供`run`目标, 使得键入`make ARCH=minirv-npc ALL=dummy run`即可把AM程序编译并在NPC上运行. 不过目前`minirv-npc`的`halt()`函数是一个死循环, 你可以通过查看波形来检查NPC是否成功进入了`halt()`函数.

#### 实现minirv-npc中的halt()函数

为了可以自动地结束程序, 你需要在`minirv-npc`中实现TRM的halt()函数, 在其中添加一条`ebreak`指令. 这样以后, 在NPC上运行的AM程序在结束的时候就会执行`ebreak`指令, 从而通知NPC的仿真环境结束仿真.

实现之后, 你就可以通过一条命令自动在NPC上运行AM程序并自动结束仿真了.

#### 为NPC实现HIT GOOD/BAD TRAP

NEMU可以输出"程序是否成功结束执行"的信息, 尝试在NPC中实现相似的功能, 这样以后, 你就可以快速了解程序在NPC上是否成功结束了.

得益于minirv指令集的完备性, 之前你在`riscv32-nemu`上能运行的程序, 都能通过重新编译到`minirv-npc`, 从而运行在NPC上. 你无需为了运行它们而在NPC上实现更多的指令.

#### 在NPC上运行更多程序

在`minirv-npc`上运行`cpu-tests`和`riscv-tests`, 来测试NPC的实现是否正确.

由于minirv将其他指令转换成上述8条指令时, 需要满足程序不会使用`sp`, `gp`和`tp`寄存器的假设. 但`riscv-arch-test`中的测试过程确实使用了这些寄存器, 不符合这个假设, 因此`riscv-arch-test`无法在`minirv-npc`中正确运行.


---

> 来源：[https://ysyx.oscc.cc/docs/2407/d/5.html](https://ysyx.oscc.cc/docs/2407/d/5.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# D5 设备和输入输出

你已经在NEMU和NPC上都实现TRM了, 下一步当然是让它们支持输入输出了.

#### 在NEMU中实现输入输出

根据PA讲义完成PA2阶段3, 直到你看到如下提示框:

#### 温馨提示

PA2到此结束...

## NPC中的输入输出

对于RISC-V架构, 输入输出是通过MMIO来实现的. 有了基于DPI-C的内存读写函数, 目前我们不必修改RTL代码就可以为NPC实现输入输出了! 我们只需要在这两个函数中对地址的范围进行简单的判断, 就可以将来自NPC的访存请求重定向到正确的设备了. 硬件上的MMIO是基于总线来实现的, 我们将来再实现真正的MMIO.

关于设备, 我们在这里不直接采用NEMU的设备模型, 而是为NPC在仿真环境中实现一套与将来流片SoC相近的设备模型. 实现总线后, 我们再来基于总线实现RTL版本的设备. 这时候, AM中IOE抽象的作用就体现出来了: NEMU和NPC的设备地址和设备模型都有所不同, 但经过抽象之后, 它们都可以运行同一份红白机模拟器的源代码, 更多地, AM上的所有程序都不必为不同的运行环境编写不同的代码.

## 在NPC中运行红白机游戏

大家已经完成了支持RV32IM和外设的NEMU, 并在NEMU上成功运行了红白机游戏. 同样, 我们也可以在RV32E的NPC上运行红白机游戏, 不过这首先需要实现串口和时钟.

我们知道RISC-V处理器通过MMIO访问外设, 例如在NEMU中串口会映射到`0xa00003f8`. 类似地, 我们也可以在NPC的仿真环境中实现简单的串口和时钟. 在上一节中提到, 我们通过DPI-C方式让NPC调用读写函数`pmem_read()`和`pmem_write()`来访问内存. 和NEMU一样, 我们可以在这两个函数中添加若干判断来实现MMIO的功能, 伪代码如下所示:

```
extern "C" int pmem_read(int raddr) {
  // 总是读取地址为`raddr & ~0x3u`的4字节并返回
  if (raddr == 时钟地址) { 返回当前时间 }
  ...
}
extern "C" void pmem_write(int waddr, int wdata, char wmask) {
  // 总是往地址为`waddr & ~0x3u`的4字节按写掩码`wmask`写入`wdata`
  // `wmask`中每比特表示`wdata`中1个字节的掩码,
  // 如`wmask = 0x3`代表只写入最低2个字节, 内存中的其它字节保持不变
  if (waddr == 串口地址) { putchar(...) }
  ...
}
```

#### 为NPC添加串口和时钟

在NPC仿真环境中实现串口的输出功能, 并运行hello程序. 为了和后面的SoC串口地址保持一致, 此处可将NPC的串口地址设置为`0x10000000`.

#### 为NPC添加时钟

在NPC仿真环境中实现时钟, 并运行`am-tests`的`real-time clock test`测试. 可以基于系统时间来实现时钟的功能, 在C语言中与系统时间相关的库是什么, 以及如何获取系统时间, 就交给你来STFW了.

#### 运行字符版本的红白机游戏

尝试在NPC中运行字符版本的红白机游戏. 但此时NPC仿真环境还不支持键盘输入.


---

> 来源：[https://ysyx.oscc.cc/docs/2407/d/6.html](https://ysyx.oscc.cc/docs/2407/d/6.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# D6 D阶段流片准备

#### 流程处于内测阶段

目前本页面处于内测阶段, 流程可能会有所更新, 请保持关注.

#### 建议创建新分支

如果你不打算参加D阶段流片, 你可以直接跳过本页面的内容.

由于D阶段流片的准备工作需要对NPC进行调整, 这些调整可能会在某种程度上提升C阶段的实现难度, 因此我们建议你在`ysyx-workbench`中创建一个新分支, 并在新分支中进行代码的调整. 如果你想继续进行C阶段的开发工作, 可以切换回旧分支.

此外, 为了达到流片的基本功能要求, 我们需要引用C阶段和B阶段中的少数学习内容.

#### 在NPC中添加CSR

阅读[C阶段`异常处理和RT-Thread`中`在NPC中添加CSR`这一小节的内容](C.md#%E5%9C%A8npc%E4%B8%AD%E6%B7%BB%E5%8A%A0csr), 并完成其中的必做题, 添加`mcycle`和学号CSR.

#### 实现总线

1. 阅读[B阶段`总线`中`总线 - 硬件模块间的通信协议`这一小节的内容](B.md#%E6%80%BB%E7%BA%BF-%E7%A1%AC%E4%BB%B6%E6%A8%A1%E5%9D%97%E9%97%B4%E7%9A%84%E9%80%9A%E4%BF%A1%E5%8D%8F%E8%AE%AE), 学习总线的基本概念.
2. 阅读[B阶段`总线`中`系统总线`这一小节的内容](B.md#%E7%B3%BB%E7%BB%9F%E6%80%BB%E7%BA%BF), 并完成其中的必做题, 在NPC中实现支持有效信号的SimpleBus总线. 直到你看到如下提示框:

#### 温馨提示

如果你是为了D阶段流片而学习总线, 学习到此处即可.

## 接入ysyxSoC

我们提供一个可以在verilator上运行的SoC环境, 称为ysyxSoC. 你可以SoC环境中测试你的NPC, 从而更早地暴露NPC的问题, 帮助你进行调试.

#### 获取ysyxSoC的代码

你需要克隆[ysyxSoC](https://github.com/OSCPU/ysyxSoC)项目:

```
cd ysyx-workbench
git clone git@github.com:OSCPU/ysyxSoC.git
```

需要注意的是, ysyxSoC与最终流片使用的SoC仍有一定差异. 因此, 通过ysyxSoC的测试并不代表最终也能通过流片SoC仿真环境的测试. 但即使这样, 也可以借助ysyxSoC项目提前暴露一部分问题.

ysyxSoC项目中包含较多细节, 我们会在B阶段再深入学习SoC的相关内容. 我们为D阶段的流片专门准备了一份经过简化的SoC代码, 包含如下设备:

| 设备 | 地址空间 |
| --- | --- |
| UART16550 | `0x1000_0000~0x1000_0fff` |
| SPI master | `0x1000_1000~0x1000_1fff` |
| Flash | `0x3000_0000~0x3fff_ffff` |
| SDRAM | `0x8000_0000~0x81ff_ffff` |
| Reverse | 其他 |

这份简化后的SoC代码中还包含一个转接桥模块, 来将SimpleBus转换成AXI. 有了这个转接桥, 就可以将NPC接入到AXI接口的SoC中, 并与各种设备进行通信.

#### 接入ysyxSoC

依次按照以下步骤将NPC接入ysyxSoC:

1. 调整NPC顶层接口, 使其与`ysyxSoC/ready-to-run/D-stage/cpu-interface.md`中的接口命名规范**完全一致**, 包括信号方向, 命名和数据位宽
   - 其中`io_lsu_size`用于与外设进行通信, 由LSU根据访存指令的数据位宽来设置: 位宽为1字节时设置为`2'b00`, 为2字节时设置为`2'b01`, 为4字节时设置为`2'b10`
2. 将NPC中的PC复位值修改为`0x3000_0000`, 即复位后从Flash取指令
3. 将`ysyxSoC/perip`目录及其子目录下的所有`.v`文件加入verilator的Verilog文件列表
4. 将`ysyxSoC/perip/uart16550/rtl`和`ysyxSoC/perip/spi/rtl`两个目录加入verilator的include搜索路径中
   - 具体如何加入, 请RTFM(`man verilator`或verilator的官方手册)
     - 如果你从来没有查阅过verilator有哪些选项, 我们建议你趁这次机会认真阅读一下手册中的`argument summary`, 你很可能会发现一些新的宝藏
5. 在verilator编译选项中添加`--timescale "1ns/1ns"`和`--no-timing`
6. 将`ysyxSoC/ready-to-run/D-stage/ysyxSoCFull.v`加入verilator的Verilog文件列表
7. 将`ysyxSoCFull`模块(在`ysyxSoC/ready-to-run/D-stage/ysyxSoCFull.v`中定义)设置为verilator仿真的顶层模块
8. 将`ysyxSoC/ready-to-run/D-stage/ysyxSoCFull.v`中的`ysyx_00000000`模块名修改为你的学号, 例如`ysyx_26000001`
9. 在仿真的cpp文件中加入如下内容, 用于解决链接时找不到`flash_read`的问题

   ```
   extern "C" void flash_read(int32_t addr, int32_t *data) { assert(0); }
   ```
10. 仿真顶层的复位信号需要维持至少10个周期
11. 通过verilator编译出仿真可执行文件
    - 如果你遇到了组合回环的错误, 请自行修改你的RTL代码
12. 尝试开始仿真, 你将观察到代码触发了`flash_read()`中的`assert(0)`错误, 我们接下来再解决这个问题
    - 如果没有触发这个错误, 请检查总线的实现

#### 在ysyxSoC上运行程序

在仿真的cpp文件中定义一个16MB的数组作为Flash存储器, 然后实现`flash_read()`函数, 根据地址`addr`返回Flash存储器中的相应数据. 然后, 将NPC需要运行的`.bin`文件读入到Flash存储器中, 从而让NPC从Flash中取出程序的第一条指令.

我们准备了一个hello程序, 位于`ysyxSoC/ready-to-run/D-stage/hello-minirv-ysyxsoc.bin`, 你可以按照上述方式让NPC运行这个程序. 如果你的实现正确, 你将看到程序输出`Hello World!`后陷入死循环.

## 运行更多程序

针对ysyxSoC, 我们只提供了一个hello程序. 接下来, 你需要自己将程序编译到ysyxSoC上并运行.

在真实的计算机中, 一般的存储器是易失存储器(volatile memory), 例如SRAM和DRAM, 它们在上电时并没有存放有效数据. 如果上电后CPU直接从内存中读取指令执行, 存储器读出什么数据是未定义的, 因此整个系统的行为也是未定义的, 从而无法让CPU执行预期的程序. 因此, 需要使用一种非易失存储器(non-volatile memory)来存放最初的程序, 使其内容能在断电时保持, 并在上电时能让CPU马上从中取出指令.

在ysyxSoC中, 非易失存储器由Flash充当, 易失存储器由SDRAM充当. 接入ysyxSoC后, NPC复位后将从位于`0x30000000`的Flash中取出第一条指令. 但由于对处理器来说, Flash无法直接通过访存指令写入, 因此通常需要将程序从Flash中加载到可写入的非易失存储器(如SDRAM)后再执行.

上述的hello程序已经包含了这个过程. 事实上, 上述的`.bin`文件中还包含一个加载器(loader)程序, 它位于地址`0x30000000`的位置. NPC执行这个`.bin`文件时, 首先执行的是加载器. 加载器的工作是将真正的hello程序从Flash中加载到位于`0x80000000`的SDRAM中, 因此你会看到程序通过串口输出`loading to memory region [0x80000000, 0x80048650)`的信息. 加载完成后, NPC将会跳转到hello程序的入口, 即`0x80000000`, 然后取出hello程序的指令并执行.

由于加载器在Flash中运行, 而Flash对NPC来说无法通过访存指令写入, 因此在加载器进行链接的时候需要进行一些额外的处理. 为了减轻大家的负担, 目前我们不要求大家实现加载器, 而是复用上述`.bin`文件中的加载器. 我们提供了一个脚本, 位于`ysyxSoC/ready-to-run/D-stage/gen.sh`, 用于将其他程序和这个加载器拼接成一个新的`.bin`文件. 通过这种方式, 你就可以在ysyxSoC中加载并运行其他程序了.

#### 更新minirv的构建过程

我们在2025/08/30 22:30:00更新了minirv的构建过程. 如果你在上述时间之前获取`abstract-machine`的代码, 请按照以下说明更新文件:

```
--- a/tools/minirv/minirv-common.sh
+++ b/tools/minirv/minirv-common.sh
@@ -29,3 +29,5 @@

 src_dir=`dirname $src
 riscv64-linux-gnu-gcc -I$src_dir $flags -D_LUT_BIN_PATH=\"$lut_bin_path\" -Wno-trigraphs -c -o $dst $dst_S
+
+/bin/echo -ne '\x80' | dd of=$dst bs=1 seek=39 count=1 conv=notrunc 2> /dev/null
```

脚本的用法示例如下:

```
cd am-kernels/tests/cpu-tests
make ARCH=minirv-npc ALL=dummy
cd ysyxSoC/ready-to-run/D-stage
bash gen.sh am-kernels/tests/cpu-tests/build/dummy-minirv-npc.elf
ls new.bin
```

#### 运行其他程序

根据上文的介绍, 尝试在ysyxSoC中运行dummy程序. 由于dummy程序没有输出, 加载器跳转到dummy程序后将会输出`HIT GOOD TRAP`的信息.

#### 运行hello程序

用类似的方式在ysyxSoC中运行hello程序, 你将看到NPC输出若干字符. 不过你发现NPC并没有输出全部字符, 尽管这并不是我们所期望的, 但目前来说这是预期行为, 我们接下来将会修复这个问题.

在真实的芯片中, 程序在通过串口输出之前, 还需要对串口进行初始化. 具体地, 初始化过程需要设置串口收发参数, 包括波特率, 字符长度, 是否带校验位, 停止位的位宽等.

- 波特率指每秒传送的字符数. 不过通常并非直接在寄存器中设置波特率, 而是设置一个与波特率成反比的除数: 除数越小, 波特率越大, 传输速率越快, 但受电气特性的影响, 误码率也越高, 字符传送成功的概率越低; 相反, 除数越大, 波特率越小, 传输速率越慢, 软件等待的时间也越长. 除数的值还与串口控制器的工作频率有关, 后者即串口每秒传送的比特数, 可RTFM了解两者的具体关系. 串口的手册位于`ysyxSoC/perip/uart16550/doc/UART_spec.pdf`.
- 串口收发端的参数配置要完全一致, 才能正确发送和接收字符. 通常用形如`115200 8N1`等方式来描述一组参数配置, 它表示波特率是115200, 字符长度是8位, 不带校验位, 1位停止位.

#### 正确实现串口的初始化

你需要在TRM中添加代码, 设置串口的除数寄存器. 由于ysyxSoC本质上还是一个仿真环境, 没有串口接收端, 也没有电气特性的概念, 因此目前可随意设置上述除数, 不必担心误码率的问题. 当然, 在真实的芯片中, 除数寄存器的设置是需要仔细考量的.

具体如何设置除数, 你可以RTFM了解UART IP的功能, 也可以RTFSC, 结合UART16550寄存器的RTL实现, 帮助你理解设置的除数如何工作.

如果除数寄存器设置得足够小, 你会观察到`hello`程序多输出了一些字符, 但仍然会出现字符丢失的情况. 为了解决这个问题, 我们需要在向串口写入字符之前, 保证其发送队列一定有空闲位置可以写入. 这可以通过查询串口的状态寄存器实现: 软件可以轮询相关寄存器, 直到确保写入的字符不会丢失为止.

#### 输出前轮询串口的状态寄存器

你需要修改`putch()`的代码, 在输出前先查询串口发送队列的情况. 具体如何查询, 同样地, 你可以RTFM了解UART IP的功能, 也可以RTFSC, 结合UART16550寄存器的RTL实现, 帮助你理解相关的功能.

实现后, 重新将hello程序编译到ysyxSoC上并运行, 你会发现hello程序可以正确输出所有字符.

最后, 你还需要修改AM时钟的实现. 具体地, 你需要访问`mcycle`, 并通过某个系数将计数器的值换算成时间. 将来在真实的处理器芯片上运行程序时, 这个系数和处理器的工作频率相关. 不过, 在仿真环境中并没有频率的概念, 而且仿真环境中时间流逝的速率和真实时间并不一致, 因此你可以选择一个合适的系数, 让程序读出的时钟流逝速率接近真实时间. 由于这个换算过程是在软件中完成的, 将来在真实的处理器芯片上运行时, 可以调整系数并重新编译程序.

#### 运行时钟测试

修改AM时钟的实现, 并运行`am-tests`的`real-time clock test`测试, 使得测试程序输出信息的间隔接近1秒.

#### 运行字符版本的红白机游戏

尝试在ysyxSoC中运行字符版本的红白机游戏.

#### 待续未完

## 综合

## 将代码上传到ECOS Studio云平台
