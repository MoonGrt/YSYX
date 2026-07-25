> 来源：[https://ysyx.oscc.cc/docs/2407/e/1.html](https://ysyx.oscc.cc/docs/2407/e/1.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# E1 C语言程序设计

C语言几乎是开发系统软件的不二选择, 而且考虑到参加"一生一芯"的不少同学就读的是非计算机专业, C语言对大家来说学习的门槛也比较低. 大家需要掌握如下内容: 递归, 指针, 链表, 并且能够独立写出正确的程序(而不是在百度上搜一个所谓的示例代码).

#### 通过线上网站学习C语言

你之前应该已经使用过[Compiler Explorer](https://godbolt.org/)这个在线网站来运行C程序了, 现在你将要系统地学习C语言程序设计, 并通过这个在线网站来完成一些编程作业.

具体地, 你需要学习[Linux C编程一站式学习](http://akaedu.github.io/book/)中的 第1~9章, 第11~16章, 第21章, 第23~25章, 以及第26章第1节(即"链表"). 你需要完成所有习题, 并在Compiler Explorer中测试你的程序是否正确.

此外, 你需要在正确运行程序之后, 把相应的程序代码保存到本地, 一方面可以把这些程序作为你的作业保留下来, 另一方面, 后面在安装Linux后, 我们会要求你再次运行其中的一些代码.

如果你对自己的C语言水平很有自信, 能够在不参考其他代码的情况下, 能独立编写一个链表程序并调试正确, 你可以跳过这部分学习. 如果你没有完整学习过C语言程序设计, 或者已经遗忘得差不多, 我们非常不建议你跳过这部分学习.

#### 另外推荐一些C语言学习资料

- [The C programming language (2nd Edition)](https://www.emgywomenscollege.ac.in/templateEditor/kcfinder/upload/files/C_Programming.pdf): 真正的C语言之父是这本书的作者[Dennis M. Ritchie](http://en.wikipedia.org/wiki/Dennis_Ritchie), 而不是谭浩强
- [C Coding Standard](https://users.ece.cmu.edu/~eno/coding/CCodingStandard.html)
- [SEI CERT C Coding Standard](https://wiki.sei.cmu.edu/confluence/display/c/SEI+CERT+C+Coding+Standard)
- [Learn C the hard way 中文版](https://wizardforcel.gitbooks.io/lcthw/content/preface.html)


---

> 来源：[https://ysyx.oscc.cc/docs/2407/e/2.html](https://ysyx.oscc.cc/docs/2407/e/2.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# E2 硬件描述语言

你已经学习了数字电路的基础知识, 并已经在Logisim中设计了简单的处理器. 但你应该也多少能体会到, Logisim并不适合设计更复杂的电路. 事实上, 现代处理器都是通过硬件描述语言(HDL)来设计的. 接下来, 你将来学习如何通过HDL来设计数字电路.

需要说明的是, 虽然我们后面不再使用Logisim进行处理器设计, 但Logisim的使用经验应该已经帮助你建立了"电路思维": 数字电路设计只做两件事, “实例化”和"连线". 你接下来使用HDL来设计数字电路时, 头脑中也需要将HDL代码和Logisim的使用经验建立关联: 你只不过是换了一种方式来设计电路, 但本质上还是在进行"实例化"和"连线"的工作, 因此你应该能根据你编写的代码想象到电路的逻辑结构. 如果你发现自己无法想象, 那你很大概率会设计出质量较低的电路(频率低, 面积大, 功耗高), 甚至是功能不符合预期的电路.

#### 推荐一些数字电路学习资料

- [数字电路与计算机体系结构](https://pages.hmc.edu/harris/ddca/ddcarv.html): 如果你在学习过程中需要了解一些数字电路的理论知识, 可以参考书中的1~5章
- [Verilog入门视频](https://www.bilibili.com/video/BV1PS4y1s7XW)
- [Verilog语法简介](https://vlab.ustc.edu.cn/guide/doc_verilog.html)
- Verilog高级数字系统设计技术与案例分析
- [中科大的Verilog OJ平台](https://verilogoj.ustc.edu.cn/oj/)(需要注册并登录)

#### 通过线上网站学习Verilog语言

我们给大家推荐Verilog在线学习网站[HDLBits](https://hdlbits.01xz.net/wiki/Main_Page), 它提供了丰富的习题, 并通过在线仿真判断你的代码是否正确.

如果你对自己的Verilog水平很有自信, 可以尝试完成以下习题:

- Sequential Logic
  - Finite State Machines
    - Lemmings 1
    - Lemmings 2
    - Lemmings 3
    - Lemmings 4
    - PS/2 packet parser
    - PS/2 packet parser and datapath
    - Serial receiver
    - Serial receiver and datapath
    - Serial receiver with parity checking

如果你发现上述习题非常困难, 我们建议你从基础习题开始做起. 具体地, 你需要完成以下章节对应的习题:

- Getting Started - 建议完成, 以熟悉完成习题的流程
- Verilog Language - 建议不熟悉Verilog的同学完成
- Combinational Logic
  - Basic Gates
    - More logic gates
    - Truth tables
    - Simple circuit A
    - Simple circuit B
    - Thermostat
    - 3-bit population count
    - Even longer vectors
  - Multiplexers
    - 2-to-1 multiplexer
    - 9-to-1 multiplexer
    - 256-to-1 4-bits multiplexer
  - Arithmetic Circuits
    - Signed addition overflow
    - 100-bits binary adder
- Sequential Logic
  - Latches and Flip-Flops
    - D flip-flip
    - DFF with reset value
    - DFF with asynchronous reset
    - DFF with byte enable
    - Mux and DFF
    - Create circuit from truth table
    - Detect an edge
    - Detect both edges
    - Edge capture register
    - Dual-edge triggered flip-flop
  - Counters
    - Decade counter again
    - Slow decade counter
    - Counter 1000
    - 12-hour clock
  - Shift Registers
    - Left/right rotator
    - Left/right arithmetic shift by 1 or 8
    - 5-bits LFSR
    - Shift register
    - 3-input LUT
  - More Circuits - 全部完成
  - Finite State Machines - 全部完成

#### 学习敏捷开发语言Chisel

对于一些复杂的数字电路, 采用Chisel进行设计将会更方便, 你在学习B阶段的过程中将会逐渐体会到这一点. 不过"一生一芯"并不限制你使用何种语言来设计处理器.

如果你打算学习Chisel语言, 我们还是建议你先掌握一些Verilog语言的基础, 然后建议你按照如下顺序学习:

1. [Chisel Users Guide](https://www.chisel-lang.org/docs)比较系统地整理了chisel的特性, 也是不错的入门教程.
2. [Chisel小抄](https://github.com/freechipsproject/chisel-cheatsheet/releases/latest/download/chisel_cheatsheet.pdf)简明地列出了chisel语言的大部分用法.
3. [Digital Design with Chisel](http://www.imm.dtu.dk/~masca/chisel-book.html)是一本结合数字逻辑设计和Chisel的参考书.
4. [Chisel API](https://www.chisel-lang.org/api/latest/)详细地列出了chisel库的所有API供参考.

如果你希望加入Chisel交流群, 可以微信扫描下方二维码联系助教申请进群:

![](https://ysyx.oscc.cc/docs/assets/wangrui.218ec3e0.jpg)


---

> 来源：[https://ysyx.oscc.cc/docs/2407/e/3.html](https://ysyx.oscc.cc/docs/2407/e/3.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# E3 Linux系统安装和基本使用

#### 安装一个Linux操作系统

我们复用PA讲义的内容, 请大家根据[PA0](../pa/PA0.md)安装Linux操作系统.

#### 获取"一生一芯"框架代码

当你阅读PA0讲义, 并进行到获取PA框架代码的部分, 将会有提示框请你返回到此处的讲义内容.

首先请你在github上添加一个ssh key, 具体操作请STFW. 然后通过以下命令获取"一生一芯"的框架代码:

```
git clone -b master git@github.com:OSCPU/ysyx-workbench.git
```

获取后, 你就可以回到PA讲义的相应位置, 继续阅读了. 不过你还需要注意:

- 请把`ysyx-workbench`作为PA讲义中的项目目录, 即将PA讲义中的`ics2022`看成是`ysyx-workbench`
- 修改`ysyx-workbench/Makefile`中的学号和姓名时, 学号可先不修改, 等到大家完成预学习之后再修改

这种来回跳转的做法可能会给你带来一些麻烦, 但我们之所以这样做, 是希望把文档看作代码来管理: 我们希望做到类似`"一生一芯"讲义调用PA讲义`的效果, 因此我们在PA讲义中尽可能少地提到"一生一芯", 而把"一生一芯"的相关内容都放到"一生一芯"本身的讲义中. 如果不遵守这条原则, 不仅会使我们维护讲义时感到困难, 而且大家阅读讲义时也不知道应该到哪里寻找相关的内容.

#### 安装系统是独立解决问题的最简单的训练

如果你是第一次安装并使用Linux, 你可能会遇到非常多的问题. 不用担心, 因为全世界都在使用Linux, 因此你遇到的问题, 很大概率别人也遇到过, 在互联网上搜索关键字, 很大概率就能找到解决方案.

#### 树立正确的价值观, 接受最大程度的训练

事实上, 你总能耍些小聪明来绕过这些训练, 例如

- 直接使用别人提供的虚拟机镜像或者一键安装配置的脚本, 瞬间完成本小节的任务
- 在网上搜到了所谓的PA攻略, 心里暗暗窃喜
- 找大佬要到了关键代码或者往期代码, 美言曰学习

有同学会觉得, "凭什么不能参考别人的攻略和代码? 我都看懂了啊!" 但从训练的角度来说, "看懂"和"自己独立完成"的效果是天差地别的: 你知道大佬为什么要这样做, 而不是那样做吗? 大佬踩过了多少坑, 这些坑背后是什么道理, 你能看出来吗? 相比于这些几乎躺倒就可以得到的"好处", 你更应该去想一下, 这会让你失去什么. "能抄对也是本事"这种主动降低自己要求的观点, 并不符合我们所提倡的价值观.

事实上, 如果你是初学者, 这些小聪明会给你的训练带来毁灭性的伤害:

- 你参考了这些在这个阶段不应该参考的内容, 它们就会成为你学习的上界, 因为你几乎不清楚它们哪里不好, 从而使得你几乎不会做得比它们更好
- 而且这会让你产生"我学得很好, 我善于学习"的错觉, 你就不会去尝试, 也不知道如何才能做得更好
- 更严重地, 你现在得不到应有的训练, 但将来总要面对那些没有攻略或者参考代码的新问题, 你自然也就无法解决它们

但说实话, 助教团队几乎不存在有效的方法来禁止大家耍这些小聪明. 其实, 这更多是需要大家发自内心去认可和执行的: 当你搜到了一些所谓攻略的时候, 你心里应该想到"阅读它们会降低训练的效果", 然后你主动拒绝它们的诱惑, 坚持自己独立完成实验内容. 这和大家自觉遵守学术诚信是很类似的: 你心里清楚考试作弊是不对的, 然后自发地独立完成考试题目.

事实上, 学术诚信远远不止考试不作弊, 我们推荐大家阅读一下[MIT对学术诚信的诠释](http://integrity.mit.edu/), 尤其是[关于写代码的学术诚信](http://integrity.mit.edu/handbook/writing-code). 在这里, 我们引用其中的一些示例说法(当然我们还是建议大家阅读原版的英文描述):

- 当讲义要求"实现X"的时候, 你必须在不复用任何外部资源的情况下独立实现X
- 分享代码和交换测试用例都是不合适的

你也许会觉得这些奇葩的要求颠覆了你的三观, 但这些准则归根到底是为了让你可以获得预期的训练效果: 不要忘记你是在通过学习提升自己的能力, 而不是交付项目. 如果你能够坚持下来, 你就能成为真正的专业人士.

#### 我能否使用其它Linux发行版?

我们不会强制规定必须使用什么样的Linux发行版, 因此经常有同学提出类似"使用xxx发行版是否会对实验造成影响"的问题. 首先请阅读PA0中关于发行版的提示, 除此之外, 我们大概率无法给出确切的答复, 因为我们大概率没用过.

事实上, 如果你决定使用其它发行版, 你就应该做好解决新问题的准备.

#### 学习Linux基本使用

我们给大家墙裂推荐MIT的Linux工具使用系列课程: [The Missing Semester of Your CS Education](https://missing-semester-cn.github.io/)中文版. 通过学习这些课程, 你将会了解到如何使用Linux中的工具来方便地完成各种任务, 这将大大提升你的工作效率.

**必做题**:

- 课程概览与shell
- Shell工具和脚本
- 编辑器 (Vim)
- 数据整理
- 命令行环境
- 版本控制(Git)

包括阅读讲义并完成课后习题. 此外, [B站上](https://www.bilibili.com/video/BV1x7411H7wa)有这门公开课的视频供大家参考.

#### 另外推荐一些Linux学习资料

- [The Art of Command Line](https://github.com/jlevy/the-art-of-command-line)这篇文章总结了很多常用的命令行工具, 值得大家去阅读
- [Linux101](https://101.ustclug.org/)由中国科学技术大学 Linux 用户协会编写, 大家可以挑选自己感兴趣的部分阅读


---

> 来源：[https://ysyx.oscc.cc/docs/2407/e/4.html](https://ysyx.oscc.cc/docs/2407/e/4.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# E4 从C代码到二进制程序

在线网站Compiler Explorer很适合开发单个源文件的程序, 但如果要开发多个源文件的程序, 或者让开发的多个程序之间相互协助以完成更复杂的任务, 在线网站就不方便了. 安装Linux系统后, 我们将把开发环境迁移到Linux系统中, 同时借助Linux中一些有用的工具辅助C语言的进阶学习, 为搭建后续任务的开发环境打下基础.

#### Linux中的C语言进阶学习

在Linux中完成[Learn C the hard way](https://wizardforcel.gitbooks.io/lcthw/content/preface.html)练习0~22, 练习24~25, 练习27~33, 你需要将示例代码拷贝到Linux中编译并运行, 结合文字RTFSC理解示例代码, 并完成相应的附加题.

注意, 上述习题将是入学答辩的一部分. 如果你被某些题目卡住, 可以通过STFW或在预学习群中询问.

虽然这份教程的C语言知识点和之前的《Linux C编程一站式学习》差不多, 但它还包含了Makefile, Valgrind等各种工具的使用介绍, 以及一些值得学习的编程理念, 这些对大家将来进行开发都是很有帮助的, 非常值得大家在Linux上进行实践. 事实上, 如果你之前的C语言基础足够牢固, 你不应该在阅读代码上花费过多的时间; 相反, 如果你在阅读代码时遇到不少困难, 你应该感谢这次机会帮助你查缺补漏.

熟悉了Linux系统中的C语言开发后, 你已经知道, 程序从C代码生成二进制的可执行文件后才能运行. 那么, 编译器是如何将C代码转变成可执行文件的呢? 为了回答这个问题, 我们借助Linux上的一些工具, 来进一步了解这个过程中都有哪些步骤.

## 预处理

预处理属于正式编译之前的步骤, 其本质是文本处理. 预处理主要包含以下工作:

- 头文件包含
- 宏替换
- 去掉注释
- 连接因断行符(行尾的`\`)而拆分的字符串
- 处理条件编译`#ifdef`/`#else`/`#endif`
- 处理字符串化操作符`#`
- 处理标识符连接操作符`##`

例如, 有如下C代码

```
// a.c
#include <stdio.h>
#define MSG "Hello \
World!\n"
#define _str(x) #x
#define _concat(a, b) a##b
int main() {
  printf(MSG /* "hi!\n" */);
#ifdef __riscv
  printf("Hello RISC-V!\n");
#endif
  _concat(pr, intf)(_str(RISC-V));
  return 0;
}
```

可通过

```
gcc -E a.c
```

对上述C代码进行预处理.

#### 观察预处理结果

尝试运行上述`gcc`命令, 然后对比预处理结果和源文件的区别.

一个值得讨论的问题是, `gcc`是如何找到头文件的? 要回答这个问题, 我们可以通过阅读工具的日志和相关手册.

#### 如何寻找头文件

1. 尝试执行`gcc -E a.c --verbose > /dev/null`, 并在输出的结果中寻找和头文件相关的内容.
2. 在`man gcc`中搜索`-I`选项相关的说明并阅读.

了解后, 尝试创建一些`stdio.h`文件, 然后通过`-I`选项让`gcc`包含你创建的`stdio.h`, 而不是标准库中的`stdio.h`. 通过`-E`选项来检查预处理结果是否符合你的预期.

#### 观察预处理结果(2)

尝试安装面向RISC-V架构的`gcc`, 并用其进行预处理:

```
apt-get install g++-riscv64-linux-gnu
riscv64-linux-gnu-gcc -E a.c
```

查看此时的预处理结果, 你发现有什么新的变化?

上述C代码中的宏`__riscv`很特殊, 它是由`riscv64-linux-gnu-gcc`预先定义的. 因此即使在C代码中没有直接定义它, `riscv64-linux-gnu-gcc`仍然按已定义的方式处理它. 可以通过以下命令查看所有预定义宏:

```
echo | gcc -dM -E - | sort
```

上述命令让`gcc`对一个空文件进行预处理, 然后打印出这个过程中的所有定义的宏, 并将其排序.

#### 对比gcc和riscv64-linux-gnu-gcc的预定义宏

尝试对比`gcc`和`riscv64-linux-gnu-gcc`的预定义宏, 从而了解两者在预处理时的差异. 你只需要简单了解这些差异即可, 无需深入了解每一个宏的具体含义.

Hint:

- 使用`diff`或者相关的命令能帮助你快速找到两个文件的不同之处
- 如果你想了解一些宏的含义, 可以查阅[`gcc`的相关手册](https://gcc.gnu.org/onlinedocs/cpp/Macros.html)

## 编译

从广义上理解, 编译是将一种语言转换成另一种语言的过程. 而对于C语言编译器来说, 编译是将C语言转换成目标语言的过程, 这里的目标语言和ISA相关, 通常是指目标ISA的汇编语言. 例如, 对x86架构的计算机来说, `gcc`会将C语言转换成x86汇编语言; 而`riscv64-linux-gnu-gcc`会将C语言转换成`riscv64`汇编语言.

这个过程涉及较多细节, 在此我们不深究过程中的每个步骤是如何实现的. 不过我们将借助合适的工具来了解每个步骤都在做什么, 从而对编译的过程建立简单的认识. 为此, 你需要安装`clang`, 它在功能上和`gcc`等价, 都是C语言的编译器.

```
apt-get install clang
```

同时, 我们通过以下程序来观察编译过程中的步骤:

```
// a.c
#include <stdio.h>
int main() { // compute 10 + 20
  int x = 10, y = 20;
  int z = x + y;
  printf("z = %d\n", z);
  return 0;
}
```

#### 了解编译的过程

尝试查阅`man clang`, 阅读其中关于编译阶段的介绍, 从而大致了解编译过程.

### 词法分析

词法分析的工作是识别并记录源文件中的每一个token, 包括标识符, 关键字, 常数, 字符串, 运算符, 大括号, 分号等. 若遇到非法的token(如`@`), 则报告错误. 可以通过如下命令来查看词法分析的结果:

```
clang -fsyntax-only -Xclang -dump-tokens a.c
```

可以看到, 词法分析的结果还通过`文件名:行号:列号`的格式记录了每一个token的位置.

事实上, C语言的源文件本质上是一个文本文件, 因此也可以将其看成一个字符串, 而词法分析工具则是可以看作一个字符串匹配程序.

#### 词法分析和语法高亮

你应该使用过编辑器中的语法高亮功能. 事实上, 这一功能并不难实现: 根据C语言标准规范中的定义, 你可以编写一个简单的词法分析工具, 来识别C代码中的一些关键字, 并用不同的颜色重新输出它们即可. 如果要输出到终端, 可以使用[ANSI转义码的颜色功能](http://en.wikipedia.org/wiki/ANSI_escape_code#Colors).

### 语法分析

语法分析的工作是按照C语言的语法将识别出的token组织成树状结构, 从而梳理出源程序的层次结构, 从文件, 函数, 到语句, 表达式, 变量等. 若遇到语法错误(如漏了分号), 则报告错误. 语法分析的结果通常通过抽象语法树(Abstrace Syntax Tree, AST)的方式呈现. 可以通过如下命令来查看语法分析的结果:

```
clang -fsyntax-only -Xclang -ast-dump a.c
```

### 语义分析

语法分析的工作是按照C语言的语义确定AST中每个表达式的类型. 在这个过程中, 相容的类型将根据C语言标准进行类型转换(如算术类型提升). 而对于不符合语义的情况, 则报告错误. 一些符合语法但不符合语义的情况包括未定义的引用, 运算符的操作数类型不匹配(如`struct mytype a; int b = a + 1;`), 函数调用参数的类型和数量不匹配等.

对于`clang`来说, 在输出AST的时候就已经给出表达式的类型了. 事实上, 大多数编译器并没有将语法分析和语义分析严格分开.

语义分析的一个重要应用是静态程序分析, 它是指在不运行程序的情况下对源代码进行分析, 本质是分析AST中的语义信息. 分析的角度包括代码风格和规范, 潜在的软件缺陷, 安全漏洞, 性能问题等. 例如有如下程序:

```
// a.c
#include <stdlib.h>
int main() {
  int *p = malloc(sizeof(*p) * 10);
  free(p);
  *p = 0;
  return 0;
}
```

这个程序符合C语言的语法, 单独看每条语句也符合C语言的语义, 直接通过`gcc a.c`编译并没有任何报错, 甚至编译后的程序也能成功运行. 但如果添加编译选项`-Wall`, `gcc`就会进行更多的代码检查工作, 并通过警告的方式指出代码中存在`use-after-free`的问题, 即空间释放后仍然继续访问的问题. 这种通过静态程序分析报告代码中潜在问题的工具称为lint工具.

类似地, 也可以调用`clang`的lint工具来分析上述程序:

```
clang a.c --analyze -Xanalyzer -analyzer-output=text
```

#### 重视lint工具的作用

一些编程初学者会觉得, 让编译器报告更多的警告会给编程带来额外的工作量. 事实上, 使用lint工具对开发者来说几乎是零成本的, 却可以帮助开发者发现很多潜在问题. 这些问题一旦进入程序运行阶段, 开发者将要付出更大的代价来调试它们. 尤其是在大型项目的运行过程中, 类似上文的代码造成的问题非常隐蔽, 软件很可能在运行很长一段时间后突然崩溃, 要调试是非常困难的. 因此, 大型项目通常都会充分利用lint工具, 来尽可能提升项目的质量.

### 中间代码生成

中间代码是一种由编译器定义的, 面向编译场景的ISA, 也称中间表示(Intermediate Representation, IR)或中间语言(Intermediate Language). 可以通过如下命令来查看`clang`生成的中间代码:

```
clang -S -emit-llvm a.c
cat a.ll
```

回顾状态机模型, 编译的工作主要是将C程序的状态机翻译成ISA的状态机, 也即, 将C程序的变量翻译成寄存器或内存, 将C程序的语句翻译成指令序列. 既然中间代码也可以看成一种ISA, 我们也可以通过状态机视角来理解中间代码生成的工作: 将C程序的变量翻译成中间代码的变量, 包括`%1`, `%2`, `%3`等; 将C程序的语句翻译成中间代码的指令, 包括`alloca`, `store`, `load`, `add`, `call`, `ret`等. 当然, 翻译的过程需要依据AST分析出的语义, 使得翻译之后得到的中间代码的行为与输入的C程序等价.

那为什么不直接翻译到目标语言, 即处理器相关的ISA呢? 一方面, 处理器相关的ISA有很多, 如果直接翻译到处理器相关的ISA, 并且要要对程序进行优化, 就要将一个优化技术分别实现到不同的ISA上, 增加了编译器的维护成本; 如果先翻译到中间代码, 再翻译到处理器相关的ISA, 就只需要将优化技术实现到中间代码上. 另一方面, 中间代码还能作为多种源语言(如C语言, Fortran, Haskell等) 和多种目标语言(如x86, ARM, RISC-V等)之间的桥梁: 假设有种源语言和种目标语言, 如果直接翻译到目标语言, 就需要实现个翻译模块; 如果引入中间代码, 以中间代码为边界, 将编译器的流程分为前端(frontend)和后端(backend), 就只实现个翻译模块, 其中个前端模块分别负责将种源语言翻译到中间代码, 个后端模块分别负责将中间代码翻译到种目标语言.

```
             frontend                              backend
           +----------+                        +------------+
      C -> |  Clang   | -+                 +-> |  llvm-x86  | -> x86
           +----------+  |                 |   +------------+
           +----------+  +-> +----------+ -+   +------------+
Fortran -> | llvm-gcc | ---> | llvm-opt | ---> |  llvm-arm  | -> ARM
           +----------+  +-> +----------+ -+   +------------+
           +----------+  |                 |   +------------+
Haskell -> |    GHC   | -+                 +-> | llvm-riscv | -> RISC-V
           +----------+  LLVM IR      LLRM IR  +------------+
```

不同的编译器可能会采用不同的中间代码, 例如`clang`使用的中间代码叫`LLVM IR`, `gcc`使用的中间代码叫`GIMPLE`. 不过, 我们并不需要理解中间代码的具体细节, 只需要从状态机模型的视角大致了解中间代码生成的工作过程即可.

### 编译优化

编译优化是现代软件构建过程中的重要步骤, 通过编译优化, 开发者可以将精力集中在程序业务逻辑的开发中, 而不必在开发阶段过多考虑程序的性能, 编译器通常能提供一个还不错的性能下限. 真实项目普遍都使用编译优化技术, 将来你也会在自己设计的处理器上运行各种经过编译优化的程序. 因此, 了解一些常见的优化技术, 知道编译器为什么会生成相应的指令序列, 将有助于将来开展调试和体系结构优化等工作.

#### 编译优化正确性的定义

我们可以从程序行为的角度来理解编译优化: 如果两个程序在某种意义上"一致", 就可以用"简单"的替代"复杂"的. 其中, 遵循C语言标准逐条语句执行的行为称为"严格执行". 以"严格执行"为基准, C语言标准对上文的"一致"作了严谨的定义, 即优化后的程序应满足"程序可观测行为"([C99标准手册](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)5.1.2.3节第6点)的一致性, 具体包括:

1. 对`volatile`关键字修饰变量的访问需要严格执行
2. 程序结束时, 写入文件的数据需要与严格执行时一致
3. 交互式设备的输入输出(stdio.h)需要与严格执行时一致

"可观测行为"刻画的是从外部视角看C程序对外界的影响, 例如, 第2点要求那些没有实时性的外部操作在最后"看起来一致", 第3点要求那些有实时性的外部操作在执行过程中"看起来一致". 第1点约束的是C程序内部的行为, 它其实和F阶段中提到的"内存映射I/O"有关, 不过我们不打算在此进一步说明, 我们会在D阶段中继续讨论相关内容.

因此, 只要优化后仍然满足程序可观测行为的一致性, 这种优化都是"正确"的. 在这个条件下, 如果优化后的程序变量更少, 或者语句更少, 可以预期程序的性能表现就会更优.

#### 编译优化技术举例

下面列举一些常见的编译优化技术. 注意在编译流程中, 优化技术并不是在C代码上直接开展的, 但为了方便理解, 我们用C代码来呈现优化前后的语义.

- 常量传播 - 如果一个变量的取值是常数, 可以将该取值代入到引用处, 若代入后形成常量表达式, 可直接计算出该表达式的值. 以下示例中, `a`的取值是常数, 因此表达式`a + 2`也是常数, 从而使得`b`的取值也是常数; 进一步地, 表达式`b * 3`也是常数. 编译器可以直接计算这些常量表达式, 用计算结果代替它们, 从而无需生成相应的指令(如加法指令和乘法指令)来在程序运行时刻计算这些表达式.

```
//          优化前              |            优化后
  int a = 1;                   |    int a = 1;
  int b = a + 2;               |    int b = 3;
  printf("%d\n", b * 3);       |    printf("%d\n", 9);
```

- 死代码消除 - 对于不可达(unreachable)的代码或不再使用的变量, 可将其移除. 以下示例中, `DEBUG`宏的定义为`0`, 因此`if`代码块中的代码永远不会执行, 可将其移除; 移除`if`块的代码后, 变量`a`未被使用, 可进一步将其移除.

```
//          优化前              |            优化后
  #define DEBUG 0              |    #define DEBUG 0
  int fun(int x) {             |    int fun(int x) {
    int a = x + 3;             |      return x / 2;
    if (DEBUG) {               |    }
      printf("a = %d\n", a);   |
    }                          |
    return x / 2;              |
  }                            |
```

- 消除冗余操作 - 对于那些没有被读出就被覆盖的赋值操作, 可将其移除. 以下示例中, `a = 3`的赋值操作将会被`a = f()`覆盖, 因此可移除前者; 同理, 可移除`a = f()`的赋值操作和`a = 7`的赋值操作.

```
//          优化前              |            优化后
  int a;                       |    int a;
  a = 3;                       |    f();
  a = f();                     |    a = 10;
  a = 7;                       |
  a = 10;                      |
```

#### 可以进一步优化吗?

上例优化结果保留了函数调用`f()`, 能否进一步移除`f()`? 为什么?

- 代码强度削减 - 用简单的运算操作替代复杂的运算操作. 以下示例中, `i * 4`和`i << 2`的行为在有定义时, 其语义一致. 但在大多数计算机中, 乘法指令的执行开销高于移位指令, 通过用后者替代前者, 可以提升程序的性能.

```
//          优化前              |            优化后
  int x = a[i * 4];            |    int x = a[i << 2];
```

- 提取公共子表达式 - 对于多次计算的子表达式, 可用中间变量保存其结果, 并在后续代码中直接引用该结果, 无需重复计算. 以下示例中, `a * b`出现了2次, 通过引入中间变量`temp`来存放`a * b`的结果, 可减少一次乘法运算, 从而提升程序的性能.

```
//          优化前              |            优化后
  int x = a * b - 1;           |    int temp = a * b;
  int y = a * b * 2;           |    int x = temp - 1;
                               |    int y = temp * 2;
```

- 循环不变代码外提 - 对于每次循环结果都一样的代码, 可以将其提到循环之前进行一次计算. 以下示例中, 表达式`a + 2`在每次循环中的结果都相同, 因此可以将其提到循环之前进行一次计算, 从而无需在每次循环中都重复计算.

```
//          优化前              |            优化后
  int a = f1();                |    int x = f1() + 2;
  for (i = 0; i < 10; i ++) {  |    for (i = 0; i < 10; i ++) {
    int x = a + 2;             |      int y = f2(x);
    int y = f2(x);             |      sum += y + i;
    sum += y + i;              |    }
  }                            |
```

#### 可以进一步优化吗? (2)

上例优化结果的`f2(x)`仍然在循环中, 能否进一步将`f2(x)`提到循环之前进行计算? 为什么?

- 函数内联 - 对于较小的函数, 可以在调用处将其展开, 节省函数调用的开销. 以下示例中, `f2()`中的`f1(x, 3)`可以直接展开, 直接计算`x + 3`, 无需经过函数调用和函数返回的过程, 从而提升程序的性能.

```
//          优化前              |            优化后
  int f1(int x, int y) {       |    int f1(int x, int y) {
    return x + y;              |      return x + y;
  }                            |    }
  int f2(int x) {              |    int f2(int x) {
    return f1(x, 3);           |      return x + 3;
  }                            |    }
```

#### 可以进一步优化吗? (3)

上例中, 假设`f1(x, 3)`是在该源文件中对`f1()`的唯一调用, 能否对优化结果中的`f1()`应用死代码消除技术将其移除? 为什么?

除了上文介绍的技术, 编译优化技术还有很多, 例如归纳变量分析, 循环展开, 软流水, 自动并行化, 别名和指针分析等, 此处我们不展开讨论, 感兴趣的同学可以查阅相关资料.

#### 启用编译优化技术

可以在`clang`的命令行中给出`-O1`选项来开启更多的编译优化工作:

```
clang -S -emit-llvm -O1 a.c
cat a.ll
```

#### 对比编译优化的结果

尝试对比添加`-O1`前后所生成的中间代码, 你发现添加`-O1`后, 生成的中间代码有何不同?

#### 对比编译优化的结果(2)

尝试在`int x = 10, y = 20;`之前添加`volatile`关键字, 并重新生成`-O1`的中间代码. 和之前生成的中间代码对比, 你发现此时的中间代码有何不同?

编译器通常会提供不同的优化等级, 让开发者在程序性能, 代码大小和编译时间等指标中选择. 例如, 在`gcc`中, 针对程序性能, 有以下不同的优化等级: `-Ofast` > `-O3` > `-O2` > `-O1` > `-Og` > `-O0`(默认). 优化等级越高, 生成程序的性能也越高, 但编译时间也越长. 大部分采用`gcc`或`clang`编译的软件项目通常使用`-O2`的优化等级, 这能使软件在较好的性能下运行; 对于`-O3`, `gcc`还会尝试通过生成更多的代码来换取更高的程序性能; `-Ofast`则更激进, 它甚至会采取一些违反语言标准的优化策略, 来换取更高的程序性能. `-Og`则会仅采取那些对调试较友好的优化策略, 和`-O0`相比, 能在提升程序性能的同时, 让优化后的程序仍然能保持程序原本的层次结构(如循环, 函数调用等), 使得生成的指令序列能较好地对应到C代码中, 方便开发者进行调试.

除了程序性能, `gcc`还提供了一些面向代码大小的优化等级: `-Oz` > `-Os` > `-O1` > `-O0`(默认). 对`clang`来说, 上述优化等级的编译选项也同样适用.

一个优化等级通常包含很多优化技术. 对于`gcc`, 可以通过`-Q --help=optimizers`查看相应优化等级开启的优化技术, 例如

```
gcc -Q --help=optimizers -O1
```

可以了解`-O1`启用了哪些优化技术. 而对于`clang`, 可以通过`-ftime-report`查看编译过程中都有哪些子步骤(pass):

```
clang -S -emit-llvm -O1 a.c -ftime-report
```

当然, 我们不要求你理解每一个优化技术的具体细节. 如果你感兴趣, 可以查阅相关手册.

### 目标代码生成

目标代码生成的工作是将优化后的中间代码翻译成目标代码, 也即处理器相关的ISA. 同样地, 我们可以通过状态机视角来理解目标代码生成的工作: 将中间代码的变量翻译成处理器ISA的变量, 也即将`%1`, `%2`, `%3`等翻译成寄存器或内存地址; 将中间代码的指令翻译成处理器ISA的指令, 也即将`alloca`, `store`, `load`, `add`, `call`, `ret`等指令翻译成处理器ISA的指令. 可以通过如下命令来查看`clang`生成的目标代码:

```
clang -S a.c
cat a.s
```

上述`clang`命令会默认生成与本地环境相同ISA的汇编代码, 如x86. 也可以向`clang`提供编译选项`--target=xxx`来生成对应的汇编代码, 例如, 可以通过`--target=riscv64-linux-gnu`来让`clang`生成riscv64的汇编代码:

```
clang -S a.c --target=riscv64-linux-gnu
```

这种生成与本地环境不同的ISA汇编代码的编译过程, 称为"交叉编译"(cross-compilation).

#### 使用riscv64作为示例

由于系统中缺少riscv32的运行时环境, 因此无法通过系统的默认配置生成riscv32的代码, 后续步骤也无法生成riscv32的可执行文件.

为了方便举例, 此处以riscv64为例来展示RISC-V相关的编译流程. 和riscv32相比, riscv64只是增加了若干条指令. 不过为了了解C代码和汇编代码的大致对应关系, 此时你不必深入了解每一条指令的具体语义.

#### 理解C代码与riscv指令序列的关联

阅读`clang`交叉编译得到的riscv64汇编代码, 并尝试指出哪一段汇编代码是由哪一段C代码编译得到的.

#### 理解C代码与riscv指令序列的关联(2)

添加`-O1`并重新编译得到riscv64汇编代码, 你发现生成的汇编代码有何不同? 它如何与C代码建立关联?

目标代码生成作为编译过程的最后一个步骤, 使用`gcc`也可以得到相应的结果:

```
gcc -S a.c  # 编译到本地ISA
riscv64-linux-gnu-gcc -S a.c  # 交叉编译到riscv64
```

在生成目标代码的过程中, 编译器还会进行与目标ISA相关的优化. 例如, 将中间代码的变量翻译成ISA的寄存器或内存时, 编译器会尝试把经常使用的变量放到寄存器, 不太常用的变量放到内存. 在现代计算机中, 处理器访问寄存器的效率要远高于访问内存, 因此将常用的变量放到寄存器中, 可以从整体上提升程序的性能. 对于指令的翻译, 编译器也会尝试生成指令数量较少的指令序列, 这同样可以提升程序的性能. 这些策略的背后有一定的理论支撑, 在这里我们就不详细展开了, 感兴趣的同学可以考虑查阅编译原理的相关资料.

## 二进制文件的生成和执行

### 汇编

编译的结果是汇编代码. 我们已经知道汇编语言是指令的符号化表示, 因此汇编代码本质上是可读的文本. 但处理器的电路无法理解文本, 因此还需要将汇编代码转变成指令的二进制编码. 这就是汇编(assemble)这一步骤的工作, 完成这一工作的工具称为汇编器.

汇编器的工作方式很直接, 总体上来说就是查阅ISA手册, 将汇编代码中的文本指令逐条翻译成相应的二进制编码, 从而得到目标文件(object file). 可以通过如下命令来让`clang`生成汇编后的目标文件:

```
clang -c a.c
ls a.o
```

不过, 目标文件中包含的内容已经不是文本了, 因此用文本编辑器打开目标文件将得到不可读的内容. 为了查看目标文件中的内容, 我们需要一些面向二进制文件的解析工具, 来帮我们将这些文件中的二进制内容解析成可读的文本内容. 例如, 我们可以利用`binutils(Binary Utilities)`工具包中的`objdump`工具来解析目标文件:

```
objdump -d a.o
```

从目标文件中重新解析出汇编代码的过程称为"反汇编"(disassemble). 上述命令将得到x86的反汇编代码, 它和编译器生成的汇编文件是类似的. 事实上, 你在F阶段中对sISA的二进制指令进行人工译码, 开展的就是类似反汇编的工作!

为了得到riscv64的目标文件, 我们需要进行交叉编译:

```
clang -c a.c --target=riscv64-linux-gnu
riscv64-linux-gnu-objdump -d a.o
```

类似地, 我们也可以用`gcc`来生成目标文件:

```
gcc -c a.c
riscv64-linux-gnu-gcc -c a.c
```

或者用LLVM的工具链来进行反汇编, 它可以自动识别目标文件对应的ISA架构, 用起来更方便:

```
llvm-objdump -d a.o  # x86和RISC-V的目标文件均支持
```

#### 查看riscv64目标文件的反汇编结果

根据上述命令, 查看`riscv64`目标文件的反汇编结果, 并将其与编译器生成的汇编文件进行对比.

### 链接

链接的工作是将多个目标文件合并成最终的可执行文件. 可以通过如下命令来让`clang`生成链接后的可执行文件:

```
clang a.c
ls a.out
```

可执行文件同样可以通过`objdump`进行反汇编.

不过你会发现, 和链接前的目标文件(`a.o`)相比, 链接后的可执行文件中多出了不少内容. 为了进一步了解这些内容来自哪里, 我们可以查看`clang`命令执行时的日志:

```
clang a.c --verbose
```

在日志末尾可以看到链接相关的命令, 在该命令中还包含了若干命名形如`crt*.o`的目标文件. 此处的`crt`是`C runtime`的缩写, 表示C程序的运行时环境. 也即, 链接过程会将`a.c`编译和汇编后得到的目标文件, 和已有的C程序运行时环境相关的目标文件进行合并, 最终生成可执行文件. 可以预见, 可执行文件之所以要包含这些和运行时环境相关的目标文件, 是为了向可执行文件的执行提供必要的支持.

类似地, 我们也可以用`gcc`来生成可执行文件:

```
gcc a.c
```

也可以通过交叉编译来生成`riscv64`的可执行文件:

```
clang a.c --target=riscv64-linux-gnu
riscv64-linux-gnu-gcc a.c
```

#### 查看riscv64可执行文件的反汇编结果

尝试生成`riscv64`的可执行文件, 查看其反汇编结果, 并将其与链接前的目标文件进行对比.

链接的过程还涉及较多细节, 此时不必深究, 我们会在C阶段中再展开介绍.

### 执行

对于x86, 编译出可执行文件后, 通过以下命令来执行:

```
./a.out
```

你已经熟悉处理器执行指令的过程了: 取指, 译码, 执行, 更新PC. 只要将程序的指令序列放置在内存, 并让PC指向第一条指令, 处理器就会自动执行这个程序.

#### 对比编译优化前后的性能差异

我们之前介绍了各种编译优化的选项, 现在你可以来体会一下这些选项的威力了. 以之前介绍的数列求和程序为例, 你可以测量不同编译优化等级下程序的运行时间, 从而体会不同优化等级对程序性能的影响.

不过之前的数列求和程序的末项为`10`, 为了方便测量出性能的区别, 你需要调整程序的末项, 以增加其执行时间. 如果程序的末项较大, 你还可以将`sum`变量的类型修改为`long long`. 你可以通过`time`命令来测量一条命令的执行时间, 如`time ls`将报告`ls`命令的执行时间.

调整数列的末项后, 分别在`-O0`, `-O1`, `-O2`下编译并测量程序的运行时间.

如果你感兴趣, 你还可以通过反汇编来查看相应的汇编代码, 并尝试根据汇编代码理解: 为什么会得到相应的性能提升? 编译器可能应用了哪些编译优化技术? 不过为了回答这些问题, 你可能需要通过RTFM或STFW来了解一些汇编指令的功能.

不过, 编译出生成的可执行文件在外存(磁盘或SSD)中, 怎么把它放置在内存呢? 回顾之前用Logisim实现的处理器, 我们是直接将指令序列以常数的形式连接到电路中, 或者通过GUI的`Load Image`操作将程序的指令序列读入到`ROM`组件中. 这两种方式的本质都是我们手动来完成"将程序的指令序列放置在内存"的工作, 但在上述`./a.out`的命令中, 我们并没有手动完成这项工作.

在我们执行`./a.out`的时候, 究竟是谁完成了"将程序的指令序列放置在内存"的工作, 使得处理器可以从内存中取出程序的指令序列来执行呢? 事实上, 现代操作系统中有一个称为"加载器"的特殊程序, 它的工作是将其他可执行文件从外存读入(加载)到内存, 并跳转到相应的程序入口处执行指令.

但处理器只能执行符合其ISA规范的指令, 例如, 大多数同学使用的是配备x86处理器的计算机, 因此只能执行x86的可执行文件, 而无法执行RISC-V的可执行文件; 如果强行让x86处理器执行RISC-V的指令序列, 在译码过程中可能会将RISC-V指令识别成其他行为的x86指令, 甚至识别成非法指令, 使得处理器无法按照RISC-V指令原本的语义去执行, 程序执行的结果将不符合预期. 因此, 加载器在加载程序的过程中会检查程序的指令序列属于哪种ISA, 如果与当前处理器的ISA不一致, 加载器将停止加载并报错.

加载程序是程序运行之前的必要步骤, 因此加载器属于运行时环境的一部分. 上文提到的`crtxxx.o`这些目标文件, 其中就包含加载器的部分功能. 运行时环境还包含其他功能, 例如, 在上述`./a.out`的执行过程中, 运行时环境的作用还体现在:

- 在程序执行开始前, 准备各种初始化事项. 在之前学习C语言时, 你可能会认为程序就是从`main()`开始执行的. 但如果真的是这样, 我们在命令行中输入的程序参数, 是如何传递给`main()`的`argc`和`argv`的呢? 事实上, 这项工作也是运行时环境来完成的: 运行时环境在完成加载程序, 参数准备等一系列准备工作后, 才会调用`main()`.

#### 程序真的从main()开始执行吗?

尝试用strace或gdb验证你的想法.

Hint: gdb可使用`starti`命令, 让程序在第一条指令处暂停.

- 在程序执行过程中, 提供`printf()`等库函数的支持. 上文的示例代码中直接调用了`printf()`, 并没有编写`printf()`的代码, 但执行`./a.out`的时候确实成功通过`printf()`输出了信息. 因此我们有理由猜测, `crtxxx.o`这些目标文件以直接或者间接的方式提供了执行`printf()`的方法. 事实上, 库函数确实是运行时环境的一部分.
- 在程序执行结束后, 提供程序退出的功能. 在之前学习C语言时, 你可能会认为程序从`main()`返回后就直接退出了. 但如果你能理解运行时环境在`main()`执行之前还做了很多准备工作, 你也很容易猜到, 从`main()`返回之后应该回到运行时环境, 再由它来开展一些程序退出前的清理工作.

#### 程序真的从main()返回后结束吗?

尝试用strace或gdb验证你的想法.

一般来说, 光有程序本身还不能运行, 从广义的角度来讲, 所有支撑程序运行的功能, 都属于运行时环境的范畴.

## 手册行为和编码规范

和ISA手册定义了指令的语义一样, C语言的语义也是通过相应的手册定义的. C语言在上世纪70年代问世后, 由于其高效, 灵活和移植性高等特点被广泛使用, 但是各种C语言在不同编译器中的变体和扩展带来了兼容性问题. 为了解决这一挑战, ANSI组织在1983年成立了一个委员会, 来开展C语言的标准化工作. C语言的标准经过多年的发展, 演进出各种版本, 包括C90, C99, C11, C17, C23. 这些版本通常以标准发布的年份来命名, 例如, C11标准是在2011年左右发布的. 在"一生一芯"中, 我们以[C99](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)为例, 来了解C语言标准中的一些定义和概念, 从而对C程序的行为建立更全面的认识.

### 标准规范的实现

标准规范的本质是一些定义和约定, 通常以手册作为载体呈现. 为了让标准规范得到落实, 需要将标准规范以某种形式实现出来, 这样的形式称为标准规范的实现(implementation). 例如, ISA的本质是标准规范, 而通过数字电路将这一规范实现出来的处理器, 就是ISA的一种实现. 显然, 处理器的行为需要符合ISA标准规范.

类似地, C语言标准也有相应的实现. C99手册的第3.12节对"什么是实现"进行了定义:

```
particular set of software, running in a particular translation environment
under particular control options, that performs translation of programs for,
and supports execution of functions in a particular execution environment
```

也即, C语言标准的实现是一系列特定软件, 这些软件在特定的翻译环境中运行, 用于将程序翻译到一个特定的执行环境中, 并支持该执行环境中相关功能的执行. 如果用我们熟悉的概念去理解, C语言标准的实现就是编译器(用于进行程序的翻译)和运行时环境(用于支持程序的执行). 这里的编译器是广义的, 包括汇编器和链接器. 同样地, 编译器和运行时环境需要符合C语言标准.

标准规范定义了很多细节, 包括各种"应该"或者"不应该", 这些属于明确定义的行为, 具体实现的相应行为需要遵循标准规范. 但并非所有情况下的行为, 标准规范都能明确定义. 我们会在下文继续讨论.

### 程序执行的语义

回顾计算机系统的状态机模型, C程序执行的过程就是通过C程序的语句改变程序状态的过程. 这个理解是基于状态机模型的, 现在我们可以来看看C语言标准是如何定义"程序执行"的, 这将有助于我们进一步认识"程序执行"的细节.

C99手册的第5.1.2.3节定义了"程序执行", 我们对这些定义逐条进行说明:

```
1 The semantic descriptions in this International Standard describe the behavior of
an abstract machine in which issues of optimization are irrelevant.
```

在手册中, 程序执行的语义描述是针对抽象机(abstract machine)而言的, 其中不涉及优化的话题. 在这里, 抽象机的概念和我们之前介绍ISA时讨论的模型机很类似, 都是只讨论其具备的功能和行为, 而不讨论其具体实现.

```
2 Accessing a volatile object, modifying an object, modifying a file, or calling a
function that does any of those operations are all side effects, which are changes
in the state of the execution environment. Evaluation of an expression in general
includes both value computations and initiation of side effects. Value computation
for an lvalue expression includes determining the identity of the designated object.
```

访问`volatile`对象, 修改对象, 修改文件, 或者调用一个包含上述操作的函数, 都称为"副作用", 也即执行环境状态的改变. 对表达式的求值通常包括值的计算和副作用的引入. 对左值表达式的计算还包括决定目标对象的实体.

针对"访问"(access)和"修改"(modify), 它们的概念均在手册第3章`Terms, definitions, and symbols`中定义. 具体地, "访问"是指"读出"或"修改"对象的值, 其中, "修改"包含"需要存储的新值与旧值相同"的情况.

```
3 Sequenced before is an asymmetric, transitive, pair-wise relation between
evaluations executed by a single thread, which induces a partial order among those
evaluations. Given any two evaluations A and B, if A is sequenced before B, then the
execution of A shall precede the execution of B. (Conversely, if A is sequenced
before B, then B is sequenced after A.) If A is not sequenced before or after B,
then A and B are unsequenced. Evaluations A and B are indeterminately sequenced when
A is sequenced either before or after B, but it is unspecified which. The presence
of a sequence point between the evaluation of expressions A and B implies that every
value computation and side effect associated with A is sequenced before every value
computation and side effect associated with B. (A summary of the sequence points is
given in annex C.)
```

- "前序于"是针对在一个线程中执行的求值所定义的一个反对称和传递性的二元关系, 通过它可以得到这些求值之间的一个偏序.
- 给定两个任意的求值`A`和`B`, 如果`A`前序于`B`, 那么`A`的执行发生在`B`的执行之前.
- 相反地, 如果`A`前序于`B`, 那么`B`后序于`A`.
- 如果`A`既不前序于`B`, 也不后序于`B`, 那么`A`和`B`是未定序的.
- 如果`A`前序于`B`, 或者`A`后序于`B`, 但并未指定是何者, 则称`A`和`B`是不确定序的.
- 如果`A`和`B`之间存在一个序列点, 那么, 和`A`相关的所有值的计算和副作用, 都前序于和`B`相关的所有值的计算和副作用.
- 附录C给出了序列点的总结.

第3条内容借助序列点的概念, 严格定义了不同求值操作之间合法的顺序关系. 结合第2条内容定义的副作用, 从而严格定义了整个程序执行的语义. 例如, 有以下程序:

```
a = 1;
b = a + 2;
```

根据附录C中对序列点的总结, 表达式语句之间的表达式求值存在序列点. 根据序列点的定义, 这意味着, `a = 1`这个表达式相关的所有值的计算和副作用, 都需要在对`b = a + 2`进行求值之前发生并生效, 因此, 对`b = a + 2`进行求值时, `a`的值已经被修改为`1`, 从而让程序此刻在变量`a`中读出`1`.

你可能会觉得这好像没什么用, 让我们来看下面的例子, 这个程序的输出是什么?

```
#include <stdio.h>
int f() { printf("in f()\n"); return 1; }
int g() { printf("in g()\n"); return 2; }
int h() { printf("in h()\n"); return 3; }
int main () {
  int result = f() + g() * h();
  return 0;
}
```

事实上, 这个程序可能输出任意的函数调用顺序, 这是因为, 在同一个表达式语句中, 多个函数调用之间是不确定序的, 因此它们可以按任意顺序调用. 如果程序的行为依赖于某种调用顺序, 程序的执行结果将可能不符合预期.

```
4 In the abstract machine, all expressions are evaluated as specified by the
semantics. An actual implementation need not evaluate part of an expression if it
can deduce that its value is not used and that no needed side effects are produced
(including any caused by calling a function or accessing a volatile object).
```

在抽象机中, 所有表达式都按照相应的语义进行求值. 而在一个具体实现中, 如果一个表达式中的其中一部分的值没有被使用, 也没有产生副作用(包括由调用函数和访问`volatile`对象引起的副作用), 那么, 这部分表达式可以不进行求值.

第4条内容其实指示了表达式求值过程中的优化空间.

```
5 When the processing of the abstract machine is interrupted by receipt of a signal,
the values of objects that are neither lock-free atomic objects nor of type volatile
sig_atomic_t are unspecified, as is the state of the floating-point environment. The
value of any object modified by the handler that is neither a lock-free atomic
object nor of type volatile sig_atomic_t becomes indeterminate when the handler
exits, as does the state of the floating-point environment if it is modified by the
handler and not restored to its original state.
```

第5条内容和信号机制相关, 已经超出了当前的学习范围, 因此这里不展开说明.

```
6 The least requirements on a conforming implementation are:
— Accesses to volatile objects are evaluated strictly according to the rules of the
  abstract machine.
— At program termination, all data written into files shall be identical to the
  result that execution of the program according to the abstract semantics would
  have produced.
— The input and output dynamics of interactive devices shall take place as specified
  in 7.21.3. The intent of these requirements is that unbuffered or line-buffered
  output appear as soon as possible, to ensure that prompting messages actually
  appear prior to a program waiting for input.
This is the observable behavior of the program.
```

一个符合规范的实现至少需要满足3点要求, 这就是上文讨论编译优化时的"程序可观测行为的一致性".

```
7 What constitutes an interactive device is implementation-defined.
```

交互式设备具体包含哪些, 是由实现来定义的.

```
8 More stringent correspondences between abstract and actual semantics may be
defined by each implementation.
```

每个实现可以进一步定义抽象语义和实际语义之间的严格对应关系.

上文提到, "并非所有情况下的行为, 标准规范都能明确定义". 理解具体实现会如何处理这些行为, 将有助于我们理解计算机系统如何工作, 并指导我们如何编写更规范的代码来规避这些行为.

以C99标准为例, 无法明确定义的行为有以下几类, 它们的概念均在手册第3章`Terms, definitions, and symbols`中定义.

### 未指定行为(Unspecified Behavior)

C99手册对Unspecified Behavior的定义如下:

```
use of an unspecified value, or other behavior where this International
Standard provides two or more possibilities and imposes no further requirements
on which is chosen in any instance
```

也即, 对于这类行为的结果, C语言标准提供了多种选择, 但没有规定选择哪一种, 具体实现可以从中选择一种.

C99手册中举了如下示例:

```
An example of unspecified behavior is the order in which the arguments to a
function are evaluated
```

也即, 函数调用时参数求值顺序是未指定的. 我们可以通过以下程序来验证:

```
// a.c
#include <stdio.h>
void f(int x, int y) {
  printf("x = %d, y = %d\n", x, y);
}
int main() {
  int i = 1;
  f(i ++, i ++);
  return 0;
}
```

在yzh的系统中分别通过`gcc`和`clang`编译并运行程序, 结果如下:

```
$ gcc a.c && ./a.out
x = 2, y = 1
$ clang a.c && ./a.out
x = 1, y = 2
```

可以看到, 即使是同一份程序代码, 使用不同的编译器进行编译, 程序的运行结果会有所不同.

#### 体验未指定行为

尝试在你的系统中编译运行上述程序, 观察程序的结果.

如果你尝试在自己的系统上编译并运行上述程序, 得到的结果可能和yzh不同. 如果是这样, 说明即使是同一个编译器, 使用不同的版本编译这个程序, 也可能会得到不同的运行结果, 但这仍然符合C语言标准. 更极端地, 某编译器通过随机方式决定函数调用时的参数求值顺序, 这仍然符合C语言标准!

```
if (rand() & 1) { 从左向右求值; }
else            { 从右向左求值; }
```

既然C语言标准和C语言标准的实现都没有错, 那出问题的只能是程序. 事实上, 上述程序的行为依赖于C语言标准中的未指定行为, 使得程序在不同的编译器中有不同的表现. 如果不希望出现这种结果, 我们应该编写出不受未指定行为影响的代码. 例如, 将上述代码按如下方式改写:

```
  int i = 1;
  int x = i ++;
  int y = i ++;
  f(x, y);
```

这样, 无论`f(x, y)`采用何种求值顺序, 程序的行为总是输出`x = 1, y = 2`, 从而不受未指定行为的影响.

#### 尝试从序列点的角度理解参数求值的顺序

在C99手册中查阅参数求值的相关内容, 手册是如何通过序列点的角度说明参数求值的顺序的?

### 实现定义行为(Implementation-defined Behavior)

C99手册对Implementation-defined Behavior的定义如下:

```
unspecified behavior where each implementation documents how the choice is made
```

也即, 这类行为是一类特殊的未指定行为, 但具体实现需要将行为的选择写进相关文档中. 和一般的未指定行为不同, 具体实现将实现定义行为将选择写进相关文档后, 就不能再修改了, 具体实现不仅需要遵循C语言标准, 还需要遵循自己的文档. 因此, 包含这类行为的程序, 在特定的环境下(包括编译器和运行时环境)多次编译运行, 仍然可以得到相同的结果.

一个常见的例子是整数类型的长度. 事实上, C语言标准从来没有定义过每个整数类型有多长. C99手册的5.2.4.2小节对整数类型长度的相关规定如下:

```
An implementation is required to document all the limits specified in this
subclause, which are specified in the headers <limits.h> and <float.h>.
Additional limits are specified in <stdint.h>.
```

关于整数类型的长度, C99手册的5.2.4.2.1小节的规定如下:

```
The values given below shall be replaced by constant expressions suitable for
use in #if preprocessing directives. Moreover, except for CHAR_BIT and
MB_LEN_MAX, the following shall be replaced by expressions that have the same
type as would an expression that is an object of the corresponding type
converted according to the integer promotions. Their implementation-defined
values shall be equal or greater in magnitude (absolute value) to those shown,
with the same sign.
```

在这里我们列出上文中提到的`the values given below`的其中一些取值:

|  | 取值 | 说明 |
| --- | --- | --- |
| `SCHAR_MIN` |  | `signed char`的最小值 |
| `SCHAR_MAX` |  | `signed char`的最大值 |
| `UCHAR_MAX` |  | `unsigned char`的最大值 |
| `SHRT_MIN` |  | `short int`的最小值 |
| `SHRT_MAX` |  | `short int`的最大值 |
| `USHRT_MAX` |  | `unsigned short int`的最大值 |
| `INT_MIN` |  | `int`的最小值 |
| `INT_MAX` |  | `int`的最大值 |
| `UINT_MAX` |  | `unsigned int`的最大值 |
| `LONG_MIN` |  | `long int`的最小值 |
| `LONG_MAX` |  | `long int`的最大值 |
| `ULONG_MAX` |  | `unsigned long int`的最大值 |
| `LLONG_MIN` |  | `long long int`的最小值 |
| `LLONG_MAX` |  | `long long int`的最大值 |
| `ULLONG_MAX` |  | `unsigned long long int`的最大值 |

可以看到, C语言标准只定义了每个整数类型的取值的最小范围, 具体实现可以为每个整数类型的取值定义更大的范围, 但不能比C语言标准所定义的最小范围更小.

为什么C语言标准要这样规定呢? 我们可以从C99手册的摘要部分了解到C语言标准的目标:

```
This International Standard specifies the form and establishes the
interpretation of programs expressed in the programming language C. Its purpose
is to promote portability, reliability, maintainability, and efficient
execution of C language programs on a variety of computing systems.
```

为了最大程度地兼容各种计算机系统, C语言标准的制定需要考虑:

- 要支持过去的计算机系统, 于是很多规定不能说太死. 细心的你可能已经注意到, 在C语言标准中, `signed char最小值`的最大值是, 但8位二进制补码可以表示的最小数是. 这是因为C语言标准考虑到, 过去有些计算机采用原码或反码表示, 在这些计算机中, 8位有符号数可以表示的最小数是. 如果C语言标准将`signed char最小值`的最大值定义为, 就无法兼容这些计算机.

#### 1个字节有多长?

你可能会不假思索地回答"8比特". 但事实上, C语言标准第3.6节规定, 1字节所包含的比特数量是implementation-defined的:

```
A byte is composed of a contiguous sequence of bits, the number of which
is implementation-defined
```

这显然是为了兼容过去的计算机系统: 在历史上, 1字节的长度曾经在不同的计算机中被定义成不同数量的比特, [从1比特到48比特都有](https://en.wikipedia.org/wiki/Byte). 于是, C语言标准不能直接将`1字节`定义成`8比特`, 而是交给具体实现来定义.

细心的你也许已经发现, 上文引用的C语言标准中的内容, 是用取值范围来间接描述整数类型的长度, 而不是用类似`4字节`的直接描述, 其实也是为了避免使用`字节`这个在不同的实现上存在歧义的概念.

- 要支持将来的计算机系统, 于是很多规定也要能被将来兼容. C语言标准只定义了每个整数类型的取值的最小范围, 就是在给将来留空间. 以`int`类型为例, 在一些上世纪90年代的环境中 (如[Turbo C](https://en.wikipedia.org/wiki/Borland_Turbo_C), 一些老教材使用的开发环境), `int`是16位的; 在32位系统中(如windows的VC 6.0, 或Linux的GCC), `int`是32位的; 在现代64位系统中, `int`还是32位的.

#### 查看Linux系统中整数类型的取值范围

Linux的运行时环境也是C语言标准的具体实现的一部分, 你可以通过查看`/usr/include/limits.h`, 来了解在这个具体实现中整数类型的取值范围.

总之, 对于包含实现定义行为的程序, 在特定环境中多次编译运行, 可以得到相同的结果. 但如果要将程序移植到另一个环境, 就需要考虑实现定义行为在新环境中的表现与旧环境的差异. 例如, 如果要将一个32位的程序移植到16位的环境(虽然现在这种需求极少出现), 一个需要考虑的问题是`int`类型的数据可能会发生溢出, 一种解决方案是将其改为`long`类型, 因为C语言标准规定, `long`类型的取值范围至少是, 能包含32位环境中`int`类型的取值范围.

### 区域特定行为(Locale-specific Behavior)

C99手册对Locale-specific Behavior的定义如下:

```
behavior that depends on local conventions of nationality, culture, and
language that each implementation documents
```

也即, 这类行为的结果依赖于国家地区, 文化和语言的本土习惯, 具体实现需要将行为的结果写入文档中, 是一类特殊的实现定义行为.

一个例子是扩展字符集. 扩展字符集中包含哪些字符, 属于区域特定行为. 考虑如下程序:

```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define 主函数 main
#define 返回 return

char* 字符串拼接(char *串1, char *串2) {
  char *新串 = malloc(strlen(串1) + strlen(串2) + 1);
  assert(新串);
  strcpy(新串, 串1);
  strcat(新串, 串2);
  返回 新串;
}

int 主函数() {
  char *信息 = 字符串拼接("一生一芯", "很简单");
  printf("%s\n", 信息);
  free(信息);
  返回 0;
}
```

上述程序使用了包含中文字符的字符串和标识符. 在支持中文字符的具体实现中, 该程序可以成功编译并运行; 但在只支持基本字符集(即ASCII字符集)的具体实现中, 上述程序将无法通过编译.

通常, 开发国际化软件(即i18n)时需要考虑区域特定行为. 除了字符集外, 区域特定行为还包括小数点字符, 货币符号, 时间和日期的格式等. 不过"一生一芯"中不涉及这类软件, 因此你无需深入了解.

### 未定义行为(Undefined Behavior)

C99手册对Undefined Behavior的定义如下:

```
behavior, upon use of a nonportable or erroneous program construct or of
erroneous data, for which this International Standard imposes no requirements
```

这是一类程序或数据不符合标准的错误行为, 但C语言标准对这种行为的结果不作任何约束, 也即, 无论结果如何, 都符合C语言标准. 通俗来说, 就是"一切皆有可能". C99手册列举了一些可能的结果:

```
Possible undefined behavior ranges from ignoring the situation completely with
unpredictable results, to behaving during translation or program execution in a
documented manner characteristic of the environment (with or without the
issuance of a diagnostic message), to terminating a translation or execution
(with the issuance of a diagnostic message).
```

这些结果包括:

- 编译时或执行时报错并退出
- 按照具体实现的文档要求来处理, 可能不报警告
- 完全无法预料的结果

一个未定义行为的例子是缓冲区溢出. 考虑如下程序:

```
// a.c
#include <stdio.h>
int main() {
  int a[10] = {0};
  printf("a[10] = %d\n", a[10]);
  return 0;
}
```

#### 体验未定义行为

尝试在你的系统中编译并多次运行上述程序, 观察程序的结果.

上述程序在调用`printf()`时引用了`a[10]`, 访问的元素已经越过了数组的边界. 按照C语言标准, `a[10]`的值是未定义的. 因此, 无论是编译器报错, 还是程序运行过程中报错, 还是程序输出`0`或垃圾值, 这些行为都符合C语言标准.

包含未定义行为的程序, 即使是在编译之后多次运行, 大概率也无法得到正确的结果. 如果你的程序在多次运行的过程中得到不同的结果, 在排除外部带来的随机因素之后, 你就可以怀疑你的程序存在未定义行为了.

#### 为什么要RTFM

我们之所以在上文中引用C语言标准中的原文, 就是希望让大家看到C语言标准对一些概念的精确定义. 你大概率很难从其他材料中看到类似的概念及其定义. 例如, 即使你上过C语言课, 或者通过其他材料学习过C语言, 你也可能是第一次听说"未定义行为"和"序列点"这些概念.

这说明了, 你接触的C语言教材和学习资料, 并不是C语言的全部. 事实上, C语言标准精确定义了C语言的每一处细节, 我们也有理由相信, 在对C语言的认知方面, C语言标准的制定者比书籍和博客的作者要深刻.

当然, 不同的人学习C语言的目标也并不相同. 如果是为了用C语言来编写一些简单的程序, 或者是为了通过考试, 大部分教材和学习资料已经能满足这些需求. 在此基础上, 如果你想进一步深入学习C语言, 或者是想理解计算机系统工作的基本原理, 甚至是想构建一台属于自己的计算机系统, 阅读C语言标准手册将是你的不二选择.

"一生一芯"的目标是后者, 因为处理器芯片和其他芯片不同, 其设计目标就是为了运行软件程序. 因此, 我们是从计算机系统的视角来看待处理器芯片设计: 你不仅需要学会设计出一颗处理器芯片, 还需要学会在这颗处理器芯片上把程序运行起来, 从而检查程序运行得对不对, 运行得好不好.

随着学习的深入, 你会逐渐遇到一些书籍和博客都无法解释清楚的问题. 这时候你需要意识到, 你已经开始踏入专业人士的领域了. 学会阅读手册, 是成为专业人士的通行证.

不过手册中内容繁多, 我们建议你阅读手册, 并不是希望你在短时间内掌握其中的所有内容, 更重要的是培养阅读手册的意识: 当你想彻底弄清楚一个问题, 你应该想到阅读手册的相关内容; 即使能在互联网上搜到相关回答, 你也应该想着看看手册是怎么说的, 除非这些回答显式地引用了手册中的内容(这样的回答是优秀的!). 如果你能建立这样的意识并付诸实践, 你对C语言的理解就已经进入行业水平的前1%了.

#### 上述不确定行为的参考列表

C99手册的附录J(Annex J)列出了C语言标准中上述4类行为的所有内容, 必要时可查阅.

### 应用程序二进制接口(Application Binary Interface)

我们已经知道, C语言标准的具体实现是一系列软件, 主要是编译器和运行时环境, 其中编译器负责生成程序的二进制可执行文件, 运行时环境负责支撑程序的运行. 一方面, 程序的二进制可执行文件和ISA相关, 程序也是在相应ISA的处理器上执行; 另一方面, 运行时环境包含库函数和操作系统的部分功能, 程序在运行的前, 中, 后都需要和它们交互.

因此, 程序, 编译器, 操作系统, 库函数, ISA这些概念, 它们作为一个计算机系统的整体, 彼此之间存在一定的关联. 这种关联一般通过约定和规范来呈现, 这就是[应用程序二进制接口](https://en.wikipedia.org/wiki/Application_binary_interface), 简称ABI, 也即, ABI是程序在二进制层面与上述概念之间的接口规范.

C语言标准由于要兼容各种计算机系统, 因此无法精确定义很多行为的结果. 而对于一个特定的计算机系统, 很多条件是确定的. ABI作为这个计算机系统在二进制层次的约定, 它可以看成是C语言标准的一种具体实现的文档, 因此对于C语言标准层次中的很多实现定义行为, 其选择都会写入ABI中.

例如, 对于特定的ISA, 字节和通用寄存器的位宽都是确定的. 基于这一点, ABI就可以确定C语言标准中整数类型的取值范围, 整个计算机系统对整数类型取值范围的理解都会遵循ABI, 从而基于一致的认识共同支撑程序的运行.

ABI作为一种规范, 其内容包括:

- 处理器的指令集, 寄存器结构, 栈的组织, 访存类型等
- 处理器可直接访问的基本数据类型的大小, 布局, 对齐方式
- 调用约定, 用于规定函数的参数如何传递, 返回值如何获取
- 应用程序如何向操作系统发起系统调用
- 目标文件的格式, 支持的运行库等

我们再次看到: 程序在特定计算机系统上的运行结果, 与源代码, 编译器, 运行时环境, ISA, 硬件等都有关联; 而ABI也是计算机系统软件和硬件相互协助, 共同支撑程序运行的重要体现. 目前你只需要简单认识ABI即可, 我们将会在D阶段以RISC-V为例, 再展开介绍ABI的具体内容.

#### RTFM

当然, 不仅是[C语言标准](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)的手册, 我们也推荐大家在茶余饭后阅读其他手册, 包括[RISC-V手册](https://github.com/riscv/riscv-isa-manual/releases/download/20240411/unpriv-isa-asciidoc.pdf), [Verilog手册](http://staff.ustc.edu.cn/~songch/download/IEEE.1364-2005.pdf), [RISC-V的ABI手册](https://github.com/riscv-non-isa/riscv-elf-psabi-doc/blob/master/riscv-cc.adoc)等, 它们能为你理解相关细节带来最全面, 最权威的帮助. 如果你发现阅读它们非常吃力, 不必担心, 当你随着学习的深入积累越来越多的基础知识后, 再回过头来阅读它们, 就会越来越顺利.

## 指令集模拟器 - 可以执行程序的程序

我们已经介绍了从C代码到二进制程序的步骤, 为了进一步理解程序执行的本质, 我们尝试用C语言来实现程序执行的过程. 这样一个用来执行程序的程序, 称为模拟器. 在工业界的处理器设计流程中, 模拟器起着非常重要的作用. 往后, 你也会使用模拟器帮助你完成处理器设计流程中的一些重要工作, 不过目前我们还是先关注如何实现一个简单的模拟器.

你已经尝试在Logisim中设计过CPU了, 其过程就是用数字电路的状态机实现ISA的状态机. 要用C语言来实现模拟器, 其实需要考虑的是如何用C程序的状态机实现ISA的状态机. 为此, 我们先回顾状态机视角下的C程序和ISA:

|  | C程序 | ISA |
| --- | --- | --- |
| 状态 |  |  |
| 激励事件 | 执行语句 | 执行指令 |
| 状态转移规则 | 语句的语义 | 指令的语义 |

要用C程序的状态机实现ISA的状态机, 我们需要开发一个包含如下功能的C程序:

- 用C程序的状态实现ISA的状态, 也即, 用C程序的变量实现ISA的PC, GPR和内存
- 用C程序的状态转移规则实现ISA的状态转移规则, 也即, 用C语言语句实现指令的语义

这种仅仅从ISA层面实现指令行为的模拟器, 称为指令集模拟器. 类似地, 还有架构模拟器和电路模拟器, 不过我们暂时不会接触它们.

### sEMU的基本实现

下面以sISA为例说明如何实现指令集模拟器, 我们称相应的指令集模拟器为sEMU(simple EMUlator). 关于sISA的细节, 请查阅之前的讲义.

sEMU要用C程序的变量实现ISA的PC, GPR和内存, 这并不难:

```
#include <stdint.h>
uint8_t PC = 0;
uint8_t R[4];
uint8_t M[16];
```

其中, 虽然在ISA层面中PC位宽为4位, 但C语言中不存在4位的基础数据类型, 故此处使用`uint8_t`; 此外, PC的位宽只有4位, 说明sISA的程序最多只能包含16条指令, 因此用于实现内存的数组`M`的大小只需设置为`16`即可.

sEMU要用C语言语句实现指令的语义, 这也不难. 从指令周期的角度考虑, 需要编写一个函数`inst_cycle()`实现如下功能:

- 取指 - 直接根据`PC`索引内存`M`, 即可取出一条指令
- 译码 - 通过C语言的位运算抽取出指令的`opcode`字段, 并检查属于哪一条指令; 然后根据指令格式抽取出操作数字段, 并获得相应的操作数
- 执行 - 若执行的指令不是`bner0`, 则将结果写回目的寄存器; 否则, 根据判断情况决定是否进行跳转
- 更新PC - 若不跳转, 则让`PC`加1

实现`inst_cycle()`后, 只需要让sEMU不断调用它即可:

```
while (1) { inst_cycle(); }
```

上文已经考虑了sISA的所有细节, 但要让程序在sEMU中运行起来, 不仅需要实现ISA层次的功能, 还需要考虑如何给程序提供相应的运行时环境. 但毕竟sISA的功能有限, 它只能支持少数程序的运行, 因此我们以"只运行数列求和程序"为前提, 来讨论运行时环境应该需要提供哪些支持. 我们从三个方面来考虑:

- 在程序执行开始前: 一个需要考虑的问题是如何加载程序. 但因为sEMU只打算运行数列求和这一个程序, 我们可以直接对`M`进行初始化:

  ```
  uint8_t M[16] = { ... };
  ```

  由于目前数列求和程序的运行过程中并没有涉及参数, 故运行时环境可暂时不考虑程序参数的传递.
- 在程序执行过程中: 由于目前数列求和程序的运行过程中并没有涉及库函数的调用, 故运行时环境可暂时不考虑库函数的支持.
- 在程序执行结束后: 由于目前数列求和程序通过死循环来指示程序结束, 而这已经通过指令层面的`bner0`指令来实现, 故无需额外提供程序退出的功能.

#### 实现sEMU

根据上述思路, 用C代码实现sEMU, 并运行之前的数列求和程序. 由于数列求和程序本身不会结束, 你可以修改`while`语句的循环条件, 在循环一定的次数后退出循环, 然后检查数列求和的结果是否符合预期.

### 强化运行时环境

可以看到, 这个运行时环境比上文讨论的`./a.out`涉及的运行时环境简单很多. 事实上, C语言标准定义了两种运行时环境, 一种称为"独立环境"(freestanding environment), 这个运行时环境通常没有操作系统的支持, 程序通常直接运行在裸机(bare-metal)上, 刚才讨论的sEMU的运行时环境就属于独立环境; 另一种称为"宿主环境"(hosted environment), 它指代有操作系统运行的情况, 程序通常运行在操作系统上, 由操作系统的相关组件提供运行时环境的支持, 上文讨论的`./a.out`的运行时环境就属于宿主环境.

你已经能理解, 如果程序的ISA和处理器的ISA不一致, 程序就无法运行. 但即使ISA一致, 程序也不一定能成功运行, 还需要考虑运行时环境. 假设你实现了一个类似sEMU的x86指令集模拟器, 但你还是无法将上文的`./a.out`放到这个指令集模拟器上运行, 这是因为`./a.out`假设自己运行在Linux这个宿主环境上, 需要运行时环境提供一系列的功能支持; 但你实现的指令集模拟器提供的运行时环境属于独立环境, 它提供的支持无法满足`./a.out`的需求. 另一个例子是, 如果你将一个Windows的程序拷贝到Linux下, 它也无法成功运行, 虽然Windows和Linux均属于宿主环境, 但它们提供的具体支持并不相同.

从另一个侧面看, 为了让程序的功能更丰富, 除了添加更多的指令, 我们还可以向程序提供功能更强大的运行时环境. 下面我们尝试向sEMU添加更多功能.

首先, 我们来向sEMU添加输出功能, 使得在其上运行的程序可以输出一个整数. 具体地, 你需要为sISA添加一条新指令`out rs`, 执行该指令后, 会将`R[rs]`输出到终端. 你可以自行决定这条指令的编码, 然后在sEMU中实现它.

一个需要考虑的问题是如何实现"输出到终端"的功能, 毕竟"终端"这个概念已经不属于sISA的范畴了, 确切来说, 它属于Linux这个宿主环境的范畴. 注意到, 虽然sISA的程序运行在sEMU提供的运行时环境中, 但同时sEMU也运行在Linux提供的运行时环境中, 因此我们可以借助Linux运行时环境的功能来实现"输出到终端"的效果. 而这样的功能, 自然是`printf()`了, 也即, sEMU通过调用`printf()`, 向其上运行的程序提供"输出到终端"的运行时环境支持, 从而实现`out`指令的约定功能. 从运行时环境的角度来看, 这一功能属于程序执行过程中的支持.

#### 实现输出功能

根据上文, 在sEMU中实现`out`指令, 并修改数列求和程序, 使得在计算出结果后通过`out`指令输出计算结果. 如果你的实现正确, 你应该能看到终端上显示`55`.

然后我们来考虑实现程序的传参. 之前的数列求和程序只能计算`1+2+...+10`, 我们希望把数列的末项作为参数, 也即, 我们希望用户从命令行输入参数`n`, 让数列求和程序计算`1+2+...+n`. 为了将`n`传递给程序, 我们需要让运行时环境在程序开始执行之前将`n`放在一个约定的位置, 这样程序就可以从约定的位置读到`n`, 从而进行计算. 一种简单的方式是将这个参数放在寄存器中, 例如`r0`.

#### 实现参数化的数列求和

修改数列求和程序, 使其从`r0`中获取数列的末项. 然后修改sEMU, 来将用户输入的参数放置在`r0`中. 实现后, 简单测试你的实现, 例如, 键入`./semu 10`, 程序应输出`55`; 键入`./semu 15`, 程序应输出`120`. 我们假设用户的输入不会导致计算过程溢出, 因此你不必考虑如何处理结果溢出的情况.

经过上述增强后, 我们简单总结sEMU向程序提供的运行时环境: 我们从三个方面来考虑:

- 在程序执行开始前, 程序的指令序列将存放在内存中. 此外, 在`r0`寄存器中存放程序的参数.
- 在程序执行过程中, 可通过`out`指令以整数方式输出指定寄存器的值.
- 在程序执行结束后, 程序将陷入死循环.

### minirvEMU的实现

你已经知道如何实现sEMU了, 类似地, 你也可以为之前的minirv实现一个指令集模拟器, 我们称它为minirvEMU. 关于minirv的细节, 请参考之前的讲义.

#### 实现两条指令的minirvEMU

设计支持`addi`和`jalr`指令的minirvEMU, 并让其运行之前在Logisim上运行过的那个两条指令的测试程序.

要为minirvEMU添加剩余的6条指令并不难, 但要运行`sum`和`mem`两个程序, 则需要一些额外的考量. 这两个程序有很多指令, 不方便手动对`M`进行初始化. 为了自动对`M`进行初始化, 我们可以让minirvEMU通过文件方式将需要运行的程序读入到`M`中. 以`sum`程序为例, 我们可以通过以下命令将之前的`.hex`文件转换成二进制表示的`.bin`文件:

```
tail -n +2 sum.hex | sed -e 's/.*: //' -e 's/ /\n/g' | sed -e 's/\(..\)\(..\)\(..\)\(..\)/\4 \3 \2 \1/' | xxd -r -p > sum.bin
```

得到`.bin`文件后, 你就可以通过C语言中的文件操作将其读入`M`并执行它了.

#### 实现完整的minirvEMU

为minirvEMU添加剩余的6条指令, 并更新加载程序的方式, 然后运行之前在Logisim上运行过的`sum`和`mem`两个程序. 为了判断程序是否成功结束运行, 你可以参考之前在Logisim上的判断方式.

之前我们是人工判断Logisim上运行的程序是否成功结束, 一个原因是, Logisim作为GUI程序, 不太方便添加个性化的功能. 而minirvEMU作为一个C程序, 我们可以尝试让minirvEMU自动判断程序是否成功结束.

具体地, 我们可以添加一条`ebreak`指令, 并将其功能定义为程序结束. 为了实现程序结束的自动判断, 我们让minirvEMU执行`ebreak`后停止仿真. 为了实现程序结束状态正确性的自动判断, 我们对运行时环境的功能进行扩充, 约定在程序结束前, 先将一个表示结束状态的整数写入`a0`寄存器, 然后执行`ebreak`指令. 这个整数如果为`0`, 表示程序正确结束; 若不为`0`, 表示程序发生错误. 根据这个约定, 一方面, 我们需要修改程序结束时的指令序列来实现这个约定; 另一方面, 在minirvEMU执行`ebreak`后, 可以通过检查`a0`寄存器的值, 来查看程序是否成功结束. 例如, 若`a0`为`0`, 则输出`HIT GOOD TRAP`的信息, 表示程序成功结束; 若`a0`不为`0`, 则输出`HIT BAD TRAP`的信息, 表示程序发生错误.

为了修改程序来遵守上述运行时环境的约定, 我们可以让minirvEMU在将程序读入`M`后, 手动将`ebreak`指令的编码写入一个正确的位置: 关于`ebreak`指令的具体编码, 请RTFM; 而对于"正确的位置", 就是指程序中`halt`函数的附近. 例如, 你可以通过如下方式写入`ebreak`指令:

```
M[? + 0] = ?;
M[? + 1] = ?;
// ......
```

你需要找到正确的内存位置和`ebreak`指令的编码, 然后替换上述`?`.

#### 实现程序结束的自动判断

根据上述运行时环境的约定, 在minirvEMU中添加并实现`ebreak`指令, 然后修改程序的指令序列, 使其在结束时执行`ebreak`指令. 如果你的实现正确, 你会看到程序自动结束并通过minirvEMU输出结束信息.

当然, 这个过程仍然涉及不少手动操作, 不过目前我们需要运行的程序并不多, 这些手动操作的开销尚可接受. 当需要运行的程序数量越来越多, 我们还是需要想办法实现全自动的判断方式. 我们将会在C阶段中继续讨论这个问题.

## 支持GUI输入输出的程序

你之前已经在Logisim中让minirv处理器运行一个显示图片的程序, 那么, 能否也在minirvEMU中运行这个程序呢? 但是, 你之前开发的C程序都只能通过终端进行输入输出, 那么, 我们平时常用的GUI程序是如何开发的呢? 为了给大家建立简单的认识, 我们先来让你体验红白机游戏的运行.

#### 运行红白机游戏

阅读PA1的`在开始愉快的PA之旅之前->NEMU是什么?`开头部分的讲义内容, 按照讲义指示尝试运行红白机游戏, 并完成画面, 按键和声音的检查.

你一定会对红白机游戏具体如何运行感到好奇. 事实上, 游戏本身也是一个指令序列, 不过其中的指令属于一种叫6502的指令集. 这种指令集是上世纪80年代的时候问世的, 现在已经很少使用, 相应的处理器也不那么常见了. 但你刚才并没有在真正的6502处理器上运行游戏, 那游戏究竟是如何运行起来的呢? 刚才其实是先运行了一个6502指令集的模拟器程序`fceux`, 这个程序的行为十分特殊, 它可以通过软件的行为模拟6502指令执行的过程, 从而模拟出整个游戏执行的过程!

### 体验GUI输入输出

不过我们还是先来考虑GUI程序相关的内容, 后面再回过头来讨论模拟器. 我们引入一个叫`abstract machine`(简称AM)的运行时环境, 它以库函数的方式提供了一些API(Application Programming Interface), 用于实现一些在GUI中常用的输入输出功能. 刚才的`fceux`正是通过调用这些API, 来实现游戏的操作和显示. 但`fceux`的行为对大家来说还是太复杂, 我们还是先通过一些简单的示例程序来体会`fceux`用到的输入输出功能.

#### 体验时钟功能

通过如下命令运行时钟测试程序:

```
cd am-kernels/tests/am-tests
make ARCH=native mainargs=t run
```

你会发现程序在终端上每隔1s输出一句话. 此外, 程序还会弹出一个画面全黑的新窗口, 但在当前程序中无任何功能, 目前你不必关心它.

体验上述功能后, 尝试阅读`am-kernels/tests/am-tests/src/tests/rtc.c`, 理解上述功能是如何实现的. 其中, 代码`io_read(AM_TIMER_UPTIME).us`将获得程序运行以来经过的时间, 单位是us.

#### 体验按键功能

通过如下命令运行按键测试程序:

```
cd am-kernels/tests/am-tests
make ARCH=native mainargs=k run
```

你会发现程序弹出一个画面全黑的新窗口, 在新窗口中按下按键, 你将会看到程序在终端输出相应的按键信息, 包括按键名, 键盘码, 以及按键状态.

体验上述功能后, 尝试阅读`am-kernels/tests/am-tests/src/tests/keyboard.c`, 理解上述功能是如何实现的(目前你可以忽略代码中`uart`相关的功能). 其中, 代码`io_read(AM_INPUT_KEYBRD)`将获得一个按键事件`ev`, `ev.keycode`表示按键的编码, `ev.keydown`表示按键为按下还是释放. 按键的编码值可查阅`abstract-machine/am/include/amdev.h`, 它们均以`AM_KEY_`为前缀, 如`A`键的编码为`AM_KEY_A`. 特别地, `AM_KEY_NONE`表示无按键事件.

#### 体验显示功能

通过如下命令运行显示测试程序:

```
cd am-kernels/tests/am-tests
make ARCH=native mainargs=v run
```

你会发现程序弹出一个新窗口并播放动画.

体验上述功能后, 尝试阅读`am-kernels/tests/am-tests/src/tests/video.c`, 理解上述功能是如何实现的. 其中, 代码`io_write(AM_GPU_FBDRAW, x * w, y * h, color_buf, w, h, false)` 表示向屏幕`(x * w, y * h)`坐标处绘制`w*h`的矩形图像. 图像像素按行优先方式存储在`color_buf`中, 每个像素用32位整数以`00RRGGBB`的方式描述颜色.

### 设计简单的屏幕保护程序

了解如何在代码中使用GUI输入输出后, 我们接下来将实现一个简单的屏幕保护程序, 来了解如何在AM上开发一个简单的GUI程序.

首先, 我们先尝试让弹出的窗口显示某种颜色. 我们给出如下的框架代码:

```
#include <am.h>
#include <klib-macros.h>

void draw(uint32_t color) {
  // add code here
}

int main() {
  ioe_init(); // initialization for GUI
  while (1) {
    draw(0x000000ff);
  }
  return 0;
}
```

为了使用AM提供的功能, 我们需要编写一个符合AM规范的`Makefile`文件, 例如:

```
NAME = screensaver
SRCS = screensaver.c
include $(AM_HOME)/Makefile
```

如果你保存的C代码的文件名不是`screensaver.c`, 你需要按照实际的文件名修改上述`Makefile`文件. 然后通过以下命令编译运行:

```
make ARCH=native run
```

你应该能看到程序弹出一个画面全黑的新窗口, 这是因为你还没有正确实现`void draw(uint32_t color)`函数. 关于上述`Makefile`和AM的详细信息, 我们将在D阶段进行介绍, 目前你只需要知道如何使用AM提供的功能来开发, 编译, 运行程序即可.

#### 实现单种颜色的显示

实现上述的`draw()`函数, 它将弹出的窗口填充为参数`color`所指示的颜色, 窗口的分辨率为`400x300`.

实现后, 重新编译运行. 如果你的实现正确, 你应该看到弹出的窗口填充了蓝色.

我们需要实现的屏幕保护程序的效果是让屏幕在多种颜色之间发生渐变. 渐变算法需要在当前颜色和目标颜色之间线性插入种颜色, 并依次显示它们, 从而实现渐变效果. 假设当前颜色是, 渐变过程经过步后变化为目标颜色, 每个颜色分量的取值都是, 则第步(应该显示的颜色为

当一轮渐变结束后, 就选择下一种目标颜色进行下一轮的渐变. 目标颜色可以在以下颜色中随机选择:

```
0x000000, 0xff0000, 0x00ff00, 0x0000ff, 0xffff00, 0xff00ff, 0x00ffff, 0xffffff
```

我们只需要通过时钟相关的代码控制屏幕显示颜色的间隔, 即可实现渐变效果.

#### 实现颜色渐变效果

按照上述介绍, 实现颜色渐变效果. 你可以自行决定每轮渐变持续多长时间, 以及一轮渐变中的步数.

最后, 让我们把按键的功能用起来. 具体地, 我们希望实现如下的按键功能:

- 如果按下`ESC`键(按键编码为`AM_KEY_ESCAPE`), 则退出程序
- 如果按下其他任意键, 则加快一轮渐变的时间; 释放按键后, 渐变时间恢复

#### 添加按键效果

按照上述介绍, 为屏幕保护程序添加按键效果.

#### 屏幕保护程序如何保护屏幕

过去, 人们通常采用CRT显示器, 其工作原理是通过电子枪发射的高速电子束轰击屏幕的荧光层, 从而使其发光来显示图像. 但如果屏幕显示的画面不变, 电子束将长时间轰击荧光层的相同位置, 会使得该位置的显像管加速老化, 甚至击穿显像管, 损坏屏幕. 屏幕保护程序通过不断变化屏幕上显示的图像, 从而不断改变电子束轰击屏幕的位置和强度, 避免损坏屏幕.

不过, 如今人们用的更多是LCD显示器(即液晶显示器), 其工作原理与CRT显示器不同, 过去的屏幕保护程序如今已经不能起到保护作用了. 上面的必做题也仅仅是作为一个简单的练习, 并不考虑其保护功能. 事实上, 屏幕显示的画面不变通常意味着用户长时间未对计算机进行操作, 此时最好的做法是关闭显示器.

实现屏幕保护程序之后, 你应该对GUI程序的开发过程有了基本的了解. 但是, 我们并没有进一步解释`io_read()`和`io_write()`究竟是如何实现输入输出的: 为什么调用`io_read(AM_INPUT_KEYBRD)`就可以获得按键的信息? 为什么调用`io_write(AM_GPU_FBDRAW, x, y, pixels, w, h, true)`就可以往屏幕绘制像素? 在真实的计算机系统中, 这是需要多个抽象层次的模块之间相互协助才能实现的, 包括运行时环境, 指令集, 处理器, 总线, 设备控制器, I/O设备. 随着学习进度的深入, 你将会在B阶段了解到这个过程中的每一处细节.

### 开发自己的小游戏

如果你感兴趣, 你还可以利用上述API来开发一款属于自己的小游戏! 所谓小游戏, 其本质不过是一个死循环:

```
while (1) {
  等待新的一帧();
  处理用户按键();
  更新游戏逻辑();
  绘制新的屏幕();
}
```

你刚才开发的屏幕保护程序, 本质上也是这样一个死循环, 只不过其游戏逻辑非常简单, 只包含一个渐变算法的处理. 更多地, `am-kernels`还提供了一些小游戏的示例:

- `am-kernels/kernels/typing-game` - 打字游戏
- `am-kernels/kernels/snake` - 贪吃蛇

#### 开发自己的小游戏

尝试构思并设计一个小游戏. 一方面, 将来这个小游戏可以运行在你自己设计的处理器上; 另一方面, 我们也长期征集好玩有趣的小游戏, 如果你设计的游戏足够优秀, 将有机会收录到我们维护的游戏集合中, 供其他同学进行娱乐, 甚至在真实的芯片上展示.

一些有用的资源:

- 显示字符: `am-kernels/kernels/typing-game/font.c`提供了字符的位图, 请查阅相关代码了解如何使用
- 显示图片: 可以通过命令`convert abc.jpg abc.txt`将一张图片转化成一个枚举像素的文本文件, 文件中按顺序列举了每一个像素的颜色编码, 你可以通过脚本进一步处理这个文本文件, 将其转化成一个C语言的数组

如果你计划向我们提交你设计的游戏, 可联系助教. 但为了保证你的游戏可以在其他同学的环境中运行, 请额外保证如下内容:

- 可移植性:
  - 代码中不使用浮点数
    - 需要进行小数相关的计算时, 可放大到整数后进行操作, 例如, 要处理一个3位小数, 可将其放大1000倍后再处理
    - 需要计算`sin`等初等函数时, 可通过幂级数展开来近似计算
  - 需要64位整数类型时, 使用`uint64_t`或`int64_t`
  - 需要使用整数类型存放指针时, 使用`uintptr_t`或`intptr_t`
- 可玩性: 进入游戏主体后, 如果玩家不操作, 一段时间后游戏将失败
- 可退出: 按下`ESC`键后, 代码调用`halt(0)`退出

### 为minirvEMU添加图形显示功能

你已经设计过屏幕保护程序了, 因此要为minirvEMU添加图形显示功能并不困难. 具体地, 你需要额外定义一个数组用于存放程序将要写入的像素信息, 并在`sw`指令的实现中判断其地址是否落在`[0x20000000, 0x20040000)`, 若是, 则将这次写入操作写入到上述数组中. 等到程序运行结束后, 再通过AM提供的API将这些像素显示到屏幕上.

#### 添加图形显示功能

根据上述思路, 为minirvEMU添加图形显示功能, 然后运行之前在Logisim上运行过的`vga`程序.

一些提示:

- 为了使用AM提供的功能, 你可以参考上文屏幕保护程序的相关代码
- 为了防止minirvEMU在显示图像后马上退出, 可以让它进入死循环

虽然目前的minirvEMU只运行了一个显示图片的程序, 但不难想象, 如果它支持更多的指令, 并且提供时钟和按键等更完善的输入输出功能, 你就得到了一个更强大的, 类似`fceux`的模拟器, 有可能运行红白机游戏, 甚至是你自己开发的游戏! 到了D阶段, 你就能实现这个目标了!

此外, AM作为一个运行时环境, 我们可以借助它编译出通过`ebreak`指令来结束的程序, 而不需要手动通过minirvEMU在正确的位置写入`ebreak`指令. 我们将会在D阶段再来展开介绍AM中的细节.

最后, 你应该能感受到, 同样是执行minirv指令集的程序, 用C语言开发一个模拟器, 比用Logisim电路开发一个处理器简单得多: 我们只要考虑如何用C语言实现指令的行为即可, 不必考虑其电路实现, 也不必考虑连线等细节. 事实上, 实现一个真正的处理器还要考虑更多的因素, 包括时序, 面积, 功耗等, 你会在B阶段对此有更深刻的认识. 但从学习的角度来考虑, 也正是因为模拟器的实现无需考虑这些因素, 它成为了了解指令集和程序行为的一种很好的方式. 在工业界的处理器设计流程中, 模拟器还充当着功能验证, 程序分析和调试的重要作用, 一些更细致的体系结构模拟器还是处理器设计空间探索的重要组成部分. 随着学习的深入, 你也会逐渐体会到模拟器的这些意义.


---

> 来源：[https://ysyx.oscc.cc/docs/2407/e/5.html](https://ysyx.oscc.cc/docs/2407/e/5.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# E5 从RTL代码到可流片版图

你已经通过在线学习网站HDLbits学习了Verilog的使用, 同样地, 为了设计自己的处理器, 我们需要使用Linux作为开发环境.

有了Linux开发环境后, 我们就可以开展更多芯片设计流程中的工作了. 具体地, 使用Verilog等语言进行RTL开发只是属于整个流程中逻辑设计的步骤, 后续还涉及验证和评估的工作, 具体包括:

- 功能验证 - 通过RTL仿真检查RTL代码所描述的电路功能是否符合预期
- 电路评估 - 通过综合器将RTL代码逻辑元件转换为物理标准单元的网表
- 物理设计 - 将标准单元的网表转换为可流片的版图

## RTL仿真(Simulation) - 功能验证

在Linux中进行RTL代码的开发并不困难, 只需要一款编辑器即可. 但在完成RTL代码的开发工作后, 我们还需要一款仿真器来验证RTL代码所描述的电路是否符合预期.

### RTL仿真的基本原理

RTL仿真的本质是通过软件程序来模拟硬件电路的行为. 因此, 要实现RTL仿真, 就是要考虑如何用C程序的状态机实现数字电路的状态机. 为此, 我们先回顾状态机视角下的C程序和:

|  | C程序 | 数字电路 |
| --- | --- | --- |
| 状态 |  | 时序逻辑电路 |
| 激励事件 | 执行语句 | 处理组合逻辑 |
| 状态转移规则 | 语句的语义 | 组合逻辑电路的逻辑 |

要用C程序的状态机实现数字电路的状态机, 我们需要开发一个包含如下功能的C程序:

- 用C程序的状态实现数字电路的状态, 也即, 用C程序的变量实现时序逻辑电路
- 用C程序的状态转移规则实现数字电路的状态转移规则, 也即, 用C语言语句实现组合逻辑电路的逻辑

我们来看一个流水灯的例子. 流水灯是按照顺序依次亮起和熄灭的一组灯, 以下是一个流水灯模块的Verilog代码:

```
module light(
  input clk,
  input rst,
  output reg [15:0] led
);
  reg [31:0] count;
  always @(posedge clk) begin
    if (rst) begin led <= 1; count <= 0; end
    else begin
      if (count == 0) led <= {led[14:0], led[15]};
      count <= (count >= 5000000 ? 32'b0 : count + 1);
    end
  end
endmodule
```

根据上述Verilog代码所描述的电路, 我们可以设计一个C程序, 来对这个电路进行RTL层次的仿真:

```
#include <stdio.h>
#include <stdint.h>

#define _CONCAT(x, y) x ## y
#define CONCAT(x, y)  _CONCAT(x, y)
#define BITMASK(bits) ((1ull << (bits)) - 1)
// similar to x[hi:lo] in verilog
#define BITS(x, hi, lo) (((x) >> (lo)) & BITMASK((hi) - (lo) + 1))
#define DEF_WIRE(name, w) uint64_t name : w
#define DEF_REG(name, w)  uint64_t name : w; \
                          uint64_t CONCAT(name, _next) : w; \
                          uint64_t CONCAT(name, _update) : 1
#define EVAL(c, name, val) do { \
                             c->CONCAT(name, _next) = (val); \
                             c->CONCAT(name, _update) = 1; \
                           } while (0)
#define UPDATE(c, name)    do { \
                             if (c->CONCAT(name, _update)) { \
                               c->name = c->CONCAT(name, _next); \
                             } \
                           } while (0)

typedef struct {
  DEF_WIRE(clk, 1);
  DEF_WIRE(rst, 1);
  DEF_REG (led, 16);
  DEF_REG (count, 32);
} Circuit;
static Circuit circuit;

static void cycle(Circuit *c) {
  c->led_update = 0;
  c->count_update = 0;
  if (c->rst) {
    EVAL(c, led, 1);
    EVAL(c, count, 0);
  } else {
    if (c->count == 0) {
      EVAL(c, led, (BITS(c->led, 14, 0) << 1) | BITS(c->led, 15, 15));
    }
    EVAL(c, count, c->count >= 5000000 ? 0 : c->count + 1);
  }
  UPDATE(c, led);
  UPDATE(c, count);
}

static void reset(Circuit *c) {
  c->rst = 1;
  cycle(c);
  c->rst = 0;
}

static void display(Circuit *c) {
  static uint16_t last_led = 0;
  if (last_led != c->led) { // only update display when c->led changes
    for (int i = 0; i < 16; i ++) {
      putchar(BITS(c->led, i, i) ? 'o' : '.');
    }
    putchar('\r');
    fflush(stdout);
    last_led = c->led;
  }
}

int main() {
  reset(&circuit);
  while (1) {
    cycle(&circuit);
    display(&circuit);
  }
  return 0;
}
```

程序通过`circuit`这个结构体变量来实现时序逻辑电路, 包括`led`和`count`. 虽然`clk`和`rst`不属于时序逻辑电路, 但它们作为电路的输入, 也是电路状态的一部分, 因此也出现在结构体中. 此外, 程序通过C语言的语句来实现组合逻辑电路的逻辑. 可以看到, 上述`cycle()`函数的内容基本上是相应Verilog代码的直接翻译, 除了引入一些后缀为`next`的中间变量和后缀为`update`的更新标志. 这些中间变量的引入是为了实现Verilog非阻塞赋值的语义, 也即, 相应信号的更新需要等到周期结束时才发生. 因此, 仿真过程需要先把组合逻辑的计算结果暂存到这些中间变量中, 并设置更新标志, 在一个周期结束时, 才依据更新标志, 把计算结果真正写入到时序逻辑元件相关的变量中.

`main()`函数的`while`循环揭示了RTL仿真的主要过程: 通过不断执行`cycle()`函数, 从而实现"根据输入和当前状态计算出新状态并更新"的功能. 这一功能其实也是数字电路工作的本质. 不过在进入`while`循环之前, 还需要通过`reset()`函数对电路进行复位. 此外, 虽然`display()`函数并不属于电路本身的功能, 但为了呈现电路的功能, `display()`函数将根据`led`信号每一位的状态来输出相应的字符, 从而在终端展示出流水灯的效果.

上面的仿真程序是手工编写的, 但如果针对每个电路设计都要手工编写对应的仿真程序才能开展功能验证工作, 这会给开发者带来很多麻烦. 为此, 开发者一般通过一个RTL仿真器的软件, 将RTL代码自动转换为用于模拟电路行为的C程序, 这个C程序就是RTL代码对应的电路仿真程序.

### STFW + RTFM搭建Verilator仿真环境

Verilator是一款开源的Verilog仿真器, 你将会使用它来进行RTL功能仿真.

框架代码默认提供了一个`npc`目录, 这里的`npc`是`New Processor Core`的含义, 你将来会在这个目录下设计自己的处理器. 我们将大家设计的处理器统称为NPC, 当然大家可以给自己的处理器起一个更个性化的名字. 不过为了设置一个环境变量`NPC_HOME`, 你需要运行如下命令:

```
cd ysyx-workbench
bash init.sh npc
```

这个环境变量会在将来使用. `npc`目录下有一些简单的文件:

```
ysyx-workbench/npc
├── csrc
│   └── main.cpp
├── Makefile
└── vsrc
    └── example.v
```

目前这三个文件几乎都是空文件, 我们将会引导大家搭建Verilator仿真环境, 并编写两个简单的数字电路模块来进行仿真.

#### 竟然连仿真框架都没有, 真寒酸

我们之所以设置这部分的实验内容, 是为了让大家知道, 项目里面的所有细节都是和大家有关系的.

在以前的课程实验当中, 大家不多不少都会觉得, 框架理所应当是由助教来提供的, 做实验就是在指定的地方写上相应的代码, 其它都是无关的代码/文件, 大家不需要关心. 事实上, 这样的实验方案是很危险的, 这不仅不能将你训练成真正的专业人士, 反而会使得你无法在真正的项目中存活下来:

1. 遇到系统性的bug, 肯定调不出来, 因为连调用你代码的模块你都觉得跟你没关系, 更别说可以清晰地认识到整个项目的架构和其中的每一处细节了
2. 离开了讲义, 就什么都做不了, 因为你总是在等别人像这些讲义一样清楚地告诉你接下来应该做什么怎么做, 而不是站在项目的角度去切实分析现在应该做什么

一个很现实的场景是, 以后你到了企业或者进入课题组, 不会再有讲义和框架代码照顾你, 你的老板说一句"来试试Verilator", 你就要自己把Verilator跑起来, 写一份使用报告, 在下周的组会上给老板汇报工作.

因此, 我们希望给大家提供更真实的训练: 给出一个目标, 让大家学会对目标进行分解, 并通过自身的技能一步步达成这个目标. 搭建Verilator仿真框架其实是一个很容易实现的目标, 因此作为一项小试牛刀的训练, 也是非常合适的.

#### 如果你想使用Chisel

Chisel可以生成功能等价的Verilog代码, 并通过Verilator进行仿真. 目前我们先关注Verilator的使用方法, 如果你想使用Chisel, 我们也建议你先按照讲义内容搭建好Verilog的工作流程, 完后再切换到Chisel.

事不宜迟, 我们马上开始.

#### 认识Verilator

你很可能是第一次听说过Verilator这个工具, 这是很正常的. 然后你就会想进一步了解Verilator的各种信息, 这也是很正常的. 但如果你的第一反应是去问人, 这就不恰当了. 事实上, Verilator这个工具在仿真领域已经非常有名, 以至于你可以很容易在互联网上搜索到它的相关信息. 你需要通过STFW找到它的官方网站, 然后阅读一下相关的介绍.

找到官网并且阅读过相关介绍之后, 接下来就是通过运行来体会一下了. 不过在这之前, 我们还需要安装它.

#### 安装Verilator

在官网中找到安装Verilator的步骤, 然后按照从git安装的相应步骤进行操作. 我们之所以不采用`apt-get`安装, 是因为其版本较老. 我们推荐安装`stable`版本. 为此, 你还需要进行一些简单的git操作, 如果你对此感到生疏, 你可能需要寻找一些git教程来学习. 另外, 你最好在`ysyx-workbench/`之外的目录进行这一操作, 否则git将会追踪到Verilator的源代码, 从而占用不必要的磁盘空间.

安装成功后, 运行以下命令来检查安装是否成功, 以及版本是否正确.

```
verilator --version
```

Verilator会编译出C++文件, 然后将C++文件编译成可执行文件, 通过执行这个可执行文件来进行仿真.

#### 运行示例

Verilator手册中包含一个C++的示例, 你需要在手册中找到这个示例, 然后按照示例的步骤进行操作.

你已经学习过C语言, 为了使用Verilator, 你并不需要了解复杂的C++语法, 你只需要了解一些类(class)的基本使用方法就可以了. 单从这一点来看, 网上的很多资料都可以满足你的需求.

### 示例: 双控开关(组合逻辑电路)

手册中的示例非常简单, 甚至算不上是一个真正的电路模块. 接下来我们编写一个真正的电路模块, 双控开关, 来进行测试. 编写如下的Verilog代码:

```
module top(
  input a,
  input b,
  output f
);
  assign f = a ^ b;
endmodule
```

双控开关的一个应用是通过两个开关(`a`和`b`)联合控制同一盏灯的亮灭(`f`). 和手册中的示例不同, 这个模块有输入输出端口. 为了驱动输入端口, 并从输出端口获得结果, 我们需要对C++文件中的`while`循环进行修改:

```
// 以下为伪代码

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

while (???) {
  int a = rand() & 1;
  int b = rand() & 1;
  top->a = a;
  top->b = b;
  top->eval();
  printf("a = %d, b = %d, f = %d\n", a, b, top->f);
  assert(top->f == (a ^ b));
}
```

在一次循环中, 代码将会随机生成两个1比特信号, 用来驱动两个输入端口, 然后通过`eval()`函数更新电路的状态, 这样我们就可以读取输出端口的值并打印. 为了自动检查结果是否正确, 我们通过`assert()`语句对输出结果进行检查.

#### 对双控开关模块进行仿真

尝试在Verilator中对双控开关模块进行仿真. 由于顶层模块名与手册中的示例有所不同, 你还需要对C++文件进行一些相应的修改. 此外, 这个项目没有指示仿真结束的语句, 为了退出仿真, 你需要键入`Ctrl+C`.

#### 上述代码是什么意思?

如果你不知道应该如何修改, 说明你还不太熟悉C程序的编写, 你应该先回到上一小节复习C语言.

### 打印并查看波形

查看波形文件是RTL调试的常用手段之一. Verilator支持波形的生成, 你可以通过开源的波形查看工具GTKWave来查看波形.

#### 生成波形并查看

Verilator手册中已经介绍了波形生成的方法, 你需要阅读手册找到相关内容, 然后按照手册中的步骤生成波形文件, 并通过

```
apt-get install gtkwave
```

安装GTKWave来查看波形.

#### 手册这么多内容, 怎么找?

尝试一下键入`Ctrl+F`.

#### 不要长时间生成波形

波形文件一般会占用较多的磁盘空间, 长时间生成波形可能会导致磁盘空间耗尽, 从而导致系统崩溃.

#### 生成FST格式的波形

FST格式的波形文件的大小大致是VCD格式的1/50, 但它仅能被GTKWave支持. 尽管如此, 我们还是推荐你使用它. 具体地, 你可以查阅Verilator手册, 了解如何生成FST格式的波形.

### 编写Makefile

#### 一键仿真

反复键入编译运行的命令是很不方便的, 尝试为`npc/Makefile`编写规则`sim`, 实现一键仿真, 如键入`make sim`即可进行上述仿真.

#### 注意保留git追踪的命令

框架代码已经在`npc/Makefile`中提供了一条默认的`sim`规则, 它已经包含用于git追踪的命令`$(call git_commit, "sim RTL")`, 在编写Makefile的时候注意不要修改这一命令, 否则会影响开发跟踪的功能, 而这是记录"一生一芯"成果原创性的重要依据. 因此在编写Makefile并运行之后, 你也需要确认git是否已经正确追踪了仿真的记录.

### 接入NVBoard

[NVBoard](https://github.com/NJU-ProjectN/nvboard.git)(NJU Virtual Board)是南京大学开发的, 用于教学的虚拟FPGA板卡项目, 可以在RTL仿真环境中提供一个虚拟板卡的界面, 支持拨码开关, LED灯, VGA显示等功能, 在速度要求不高的场景下可完全替代真实的FPGA板卡(毕竟不是每人身边都有一块FPGA). 通过以下命令获取NVBoard的代码:

```
cd ysyx-workbench
bash init.sh nvboard
```

#### 运行NVBoard示例

阅读NVBoard项目的介绍, 尝试运行NVBoard项目中提供的示例.

#### 不知道NVBoard如何工作?

试试从`make`命令开始, 看看一切是如何发生的. 通过前面的学习, 你已经掌握了足够的知识背景去理解NVBoard如何工作了: 包括Makefile的使用, C语言和C++中类的基本用法. 现在就试试阅读代码(Makefile也是代码), 看看示例中的Verilog顶层端口, 约束文件, 以及NVBoard是如何建立联系的.

#### 在NVBoard上实现双控开关

阅读NVBoard项目的说明, 然后仿照该示例下的C++文件和Makefile, 修改你的C++文件, 为双控开关的输入输出分配引脚, 并修改`npc/Makefile`, 使其连接到NVBoard上的开关和LED灯.

#### NVBoard的故事

NVBoard虽然是南京大学的教学项目, 但它却与参加"一生一芯"的各位有着一种特殊的联系: 在第三期"一生一芯"的流片名单当中有两位特殊的同学, 他们报名的时候还只是大一, 而其中一位同学sjr就是NVBoard的第一作者.

事实上, 也正是sjr同学在参加"一生一芯"时锻炼出的独立解决问题的能力和自信, 帮助他成功开发NVBoard项目. 如今NVBoard项目又反过来帮助"一生一芯"改进学习效果, NVBoard承载的除了虚拟FPGA板卡的功能之外, 还有"一生一芯"秉承的独立解决问题的理念.

这些离你其实并不遥远, 当你愿意自主学习而不再等着别人给你答案的时候, 你的将来来也会充满无限可能.

### 示例: 流水灯(时序逻辑电路)

回顾上文的流水灯模块, 其输出信号`led`的每一位对应虚拟板卡的一个LED灯. 由于代码中包含需要进行复位的时序逻辑部件, 我们需要对Verilator的仿真代码进行修改:

```
// 以下为伪代码

void single_cycle() {
  top->clk = 0; top->eval();
  top->clk = 1; top->eval();
}

void reset(int n) {
  top->rst = 1;
  while (n -- > 0) single_cycle();
  top->rst = 0;
}

...
reset(10);  // 复位10个周期
while(???) {
  ...
  single_cycle();
  ...
}
```

#### 将流水灯接入NVBoard

编写流水灯模块, 然后接入NVBoard并分配引脚. 如果你的实现正确, 你将看到灯从右端往左端依次亮起并熄灭.

### 静态代码检查

Verilator还可以作为一个lint工具来对代码进行静态检查. 在命令行中给`verilator`传递`--lint-only`参数, Verilator将仅开展代码检查工作, 并以警告信息的方式指出可能存在问题的代码, 而不生成C++文件. 特别地, 你还可以添加`-Wall`选项, 来让Verilator开启所有类型的检查, 让它帮助你找到更多的潜在问题.

Verilator手册中的`Errors and Warnings`章节列出了所有警告的说明, 通过阅读它们, 你将了解这些警告是如何产生的, 从而得知应该如何修复它们. 对于代码逻辑相关的警告, 你应该通过修改代码来移除它们; 但对于一些代码风格类型的警告, 如果确定不影响代码逻辑, 可以通过额外的`-Wno-xxx`选项来关闭`xxx`警告, 例如`-Wno-DECLFILENAME`.

#### 通过Verilator进行静态代码检查

尝试使用Verilator检查你的代码, 并尽最大可能修复所有警告.

我们建议你将来总是开启Verilator的静态代码检查功能. 一方面, 这有助于你养成良好的编码习惯, 从而编写出更高质量的代码. 另一方面, 尽早发现代码中潜在问题, 也有利于节省不必要的调试工作: 随着代码规模的增加, 将来你很可能因为某个信号的位宽错误而调试好几天, 而Verilator的警告可以让你马上注意到这个问题, 从而轻松地排除相应的错误.

#### Verilator进阶学习

[请点击这里](https://www.itsembedded.com/)

## Verilog的仿真行为和编码风格

和C语言标准类似, Verilog语言在仿真过程中的语义是由[Verilog标准手册](http://staff.ustc.edu.cn/~songch/download/IEEE.1364-2005.pdf)定义的. 手册的第11章揭示了Verilog语言的本质. 这一章并不长, 只有5页, 但其中包含着巨大的信息量(yzh觉得这部分非常重要, 以至于应该提前放到手册的第3章). 不过, 这些本质在传统的教材和大部分Verilog资料中都没被提及, 以至于绝大多数Verilog的开发者, 甚至是有些Verilog经验丰富的从业者, 都不知道这部分语义的存在, 从而无法精确理解Verilog在仿真和综合这两种使用场景下的差异.

Verilog标准手册的引言(Introduction)部分有如下内容:

```
It was designed ... for a variety of design tools, including verification
simulation, timing analysis, test analysis, and synthesis.
```

这说明, Verilog是为一系列电路设计工具而提出的. 因此, 这一系列工具都可以认为是Verilog标准的具体实现, 包括仿真工具, 时序分析工具, 测试分析工具, 综合工具等. 不过, Verilog标准手册中出现`simulation`的频次(356次), 远高于`synthesis`出现的频次(4次), 因此Verilog标准手册更多还是面向仿真工具.

#### 我会写Verilog不就行了吗? 为什么要知道这些?

事实上, 很多Verilog开发者也确实不知道Verilog的本质, 但他们也能通过遵循一定的Verilog编码建议, 来设计出行为大概率符合预期的电路. 不过, 他们并不知道这些编码建议背后的本质, 也无法判断一条编码建议是否正确, 在仿真时遇到不符合预期的情况, 也没有能力去分析问题的原因, 只能抓瞎随便改改, 万一改不对, 心里可能还抱怨是仿真器有bug...

作为一个小小的测试, 下面有若干条Verilog的编码建议或描述, 但其中有一些是不正确的, 请尝试找出它们:

1. 使用`#0`可以将赋值操作强制延迟到当前仿真时刻的末尾.
2. 在同一个`begin`-`end`语句块中对同一个变量进行多次非阻塞赋值, 结果是未定义的.
3. 用`always`块描述组合逻辑元件时, 不能使用非阻塞赋值.
4. 不能在多个`always`块中对同一个变量进行赋值.
5. 不建议使用`$display`系统任务, 因为有时候它无法正确输出变量的值.
6. `$display`无法输出非阻塞赋值语句的结果.

如果你打算在后续开发中使用Verilog语言, 而又无法判断上述描述是否正确, 我们强烈建议你认真理解这一部分的内容.

### Verilog代码的执行

我们知道, C语言的执行是指通过符合标准规范的某种求值顺序来修改对象的状态. 那么在Verilog中, "执行"的含义又是什么呢? 为了得到一个清晰的回答, 我们需要查阅Verilog标准手册. 手册的第11.1节定义了什么叫"执行Verilog代码":

```
The elements that make up the Verilog HDL can be used to describe the behavior, at
varying levels of abstraction, of electronic hardware. An HDL has to be a parallel
programming language. The execution of certain language constructs is defined by
parallel execution of blocks or processes. It is important to understand what
execution order is guaranteed to the user and what execution order is indeterminate.

Although the Verilog HDL is used for more than simulation, the semantics of the
language are defined for simulation, and everything else is abstracted from this
base definition.
```

也即, Verilog语言用来从各个抽象层次来描述硬件的行为(包括系统级, 行为级, RTL级, 门级, 晶体管级). HDL是一门并行编程语言, 部分语言成分的执行被定义为代码块或过程的并行执行. 理解什么样的执行顺序是由标准手册保证的, 什么样的执行顺序是不确定的, 对Verilog的用户来说至关重要. 尽管Verilog的使用场景并不仅限于仿真, Verilog的语义是为了仿真而定义的, 其他场景的语义都是基于这一基础定义抽象得到的.

#### 有没有感到对Verilog的认知被颠覆了?

Verilog的本质竟然是一门并行编程语言! 而且Verilog的语言标准是为了仿真而定义的, 而不是RTL设计! 更进一步地, Verilog的语义在一些场景下是存在不确定性的! 这和C语言的未指定行为或未定义行为有一些相似之处: 理解什么样的编码风格会引入不确定性, 然后在使用Verilog的过程中避免这些编码风格, 从而保证所描述对象的行为是确定的.

这意味着, 有一些Verilog代码的语义可能不符合你的直觉, 或者是仿真行为和综合行为存在差异. 如果你以前使用过Verilog, 并且有类似"仿真行为通过但FPGA上运行不正确"的经历, 在排除FPGA相关的细节问题后, 如果你仍然不理解其中的原因, 很大概率是因为你没有理解Verilog语言的上述本质. 现在是时候进一步深入理解它了!

### 基于事件的仿真

Verilog标准手册的第11.2节介绍了仿真的过程:

```
The Verilog HDL is defined in terms of a discrete event execution model.
```

Verilog语言是基于离散事件的执行模型来定义的. 我们挑选一些关键的内容继续说明:

```
Processes are objects that can be evaluated, that may have state, and that can
respond to changes on their inputs to produce outputs. Processes include primitives,
modules, initial and always procedural blocks, continuous assignments, asynchronous
tasks, and procedural assignment statements.
```

在Verilog中, "过程"是一些可以被求值的对象. 这些对象拥有自己的状态, 当输入产生变化时, 它们可以响应这些变化, 并产生输出. 过程包括原语, 模块, `initial`和`always`过程块, 连续赋值, 异步任务和过程赋值语句.

```
Every change in value of a net or variable in the circuit being simulated, as well
as the named event, is considered an update event.

Processes are sensitive to update events. When an update event is executed, all the
processes that are sensitive to that event are evaluated in an arbitrary order. The
evaluation of a process is also an event, known as an evaluation event.
```

在被仿真电路中, 线网或变量的值的变化, 以及命名事件, 都被视为一个"更新事件". 过程是对更新事件敏感的. 执行一个更新事件后, 对该事件敏感的所有过程将会被求值, 求值顺序是任意的. 一个过程的求值也是一个事件, 称为"求值事件".

```
Events can occur at different times. In order to keep track of the events and to
make sure they are processed in the correct order, the events are kept on an event
queue, ordered by simulation time. Putting an event on the queue is called
scheduling an event.
```

不同的仿真时刻都会发生事件. 为了保证按正确顺序处理事件, 需要将它们按仿真时刻的顺序存储在一个事件队列中. 将一个事件放入队列中称为"事件的调度".

可以看到, Verilog语言成分的语义都和事件有关联. 仿真的过程就是按某种正确的顺序处理这些事件的过程. 在处理事件的过程中, 电路中对象的状态会发生改变. 我们期望这种改变符合电路的预期行为, 从而实现对电路行为的仿真.

### 层次化事件队列

根据Verilog标准手册, 事件队列在逻辑上包含以下5个区域, 分别用于处理对应种类的事件:

1. 激活事件(active event)区域, 记为, 存放发生在当前仿真时刻, 且能被处理的事件.
2. 未激活事件(inactive event)区域, 记为, 存放发生在当前仿真时刻, 但不能立即处理的事件, 需要在为空时, 才能处理这类事件.
3. 非阻塞赋值更新事件(nonblocking assign update event)区域, 记为, 存放在之前的仿真时刻已经完成求值, 但需要在当前仿真时刻结束时才能进行赋值的事件, 需要在和均为空时, 才能处理这类事件.
4. 监控事件(monitor event)区域, 记为, 存放监控操作相关的事件, 需要在, 和均为空时, 才能处理这类事件.
5. 未来事件(future event)区域, 记为, 存放在未来仿真时刻才处理的事件.

一个事件会按其类别添加到不同区域, 并按照一定的规则转移到, 被处理后从事件队列中移除. 一些事件生成的规则如下:

- 显式零延迟(`#0`)可以使对应的过程挂起, 将产生一个事件.
- 非阻塞赋值将产生一个事件.
- 系统任务`$monitor`和`$strobe`会在每个仿真时刻都将产生一个事件.
- PLI过程的求值将产生一个事件.

根据上述不同事件处理顺序, Verilog标准手册提供了事件处理引擎的一个参考实现, 它是Verilog仿真器的核心循环:

```
while (there are events) {
  if (no active events) {
    if (there are inactive events) {
      activate all inactive events;
    } else if (there are nonblocking assign update events) {
      activate all nonblocking assign update events;
    } else if (there are monitor events) {
      activate all monitor events;
    } else {
      advance T to the next event time;
      activate all inactive events for time T;
    }
  }
  E = any active event;
  if (E is an update event) {
    update the modified object;
    add evaluation events for sensitive processes to event queue;
  } else { /* shall be an evaluation event */
    evaluate the process;
    add update events to the event queue;
  }
}
```

事件处理引擎将不断重复如下操作:

- 如果中存在事件, 则取出一个事件`E`
  - 如果`E`是一个更新事件, 则
    - 更新相应的对象
    - 并将对该事件敏感的过程的求值作为求值事件添加到事件队列中
  - 否则, `E`是一个求值事件, 则
    - 对过程进行求值
    - 并将赋值行为作为更新事件添加到事件队列中
- 否则(即为空)
  - 如果不为空, 则将中的所有事件转移到
  - 否则, 如果不为空, 则将中的所有事件转移到
  - 否则, 如果不为空, 则将中的所有事件转移到
  - 否则
    - 将仿真时刻前进一个单位
    - 并将中所有当前仿真时刻的事件按类型转移到或

#### Verilog代码 != C代码

对数字电路课程的老师来说, 最头疼的事情, 莫过于学生学习Verilog的时候, 很容易按照C语言的程序设计思维来编写Verilog代码. 尽管老师已经多次强调"不能把Verilog当作C语言来写", 大部分同学仍然无法深刻认识这句话的含义: 如果不能当作C语言来写, 那Verilog究竟是什么?

我们之所以在这里介绍Verilog标准手册中的内容, 就是希望给大家呈现这个问题的答案. 上述的事件处理循环已经很直接地呈现出了Verilog代码和C代码的区别: 以`i = i + 1`为例, 在C程序中, 在编译器的作用下, 这行代码最终被编译成一条类似`addi a0, a0, 1`的指令, 最后在处理器上直接执行; 而在Verilog中, 这行代码会被转化成一个求值事件和一个更新事件, 在事件处理引擎的处理下完成加法操作和赋值操作, 并产生对其敏感的新事件.

事实上, 你写的Verilog代码, 最终都会按照标准手册的约定转换成一个个事件. 仿真器按照符合标准手册约定的某种顺序来处理这些事件, 通过处理过程的结果反映出硬件电路的整体行为, 从而实现硬件电路的建模.

### 赋值操作的事件调度

根据Verilog标准手册的第11.6节, 赋值操作会转换成行为等价的过程, 从而产生相应的事件, 来被仿真器处理. 我们选取一些常见的赋值操作进行说明, 为了简单起见, 我们先考虑没有指定延迟信息(`#`)的情况.

- 连续赋值(即`assign`语句) - 对应一个对表达式的源操作数都敏感的过程. 当表达式的值变化时, 将产生一个更新事件添加到. 特别地, 连续赋值过程会产生一个`0`时刻的求值事件, 用来实现常量的传播.
- 过程中的阻塞赋值 - 先使用对象的当前值计算赋值表达式右侧的值, 然后马上计算赋值表达式左侧的赋值目标对象, 对其进行更新, 并产生由此更新导致的事件. 执行过程可以继续按顺序执行下一条语句, 也可以处理其他激活事件.
- 过程中的非阻塞赋值 - 先使用对象的当前值计算赋值表达式右侧的值和左侧的赋值目标对象, 产生一个当前仿真时刻的事件.

#### 重新认识阻塞赋值和非阻塞赋值

对数字电路课程的老师来说, 第二头疼的事情, 就是学生很难理解阻塞赋值和非阻塞赋值的区别. C语言的赋值只有一种, 但Verilog中的赋值却有好几种, 而要深入理解不同赋值方式的区别, 还是要回到Verilog的本质, 也就是事件模型.

和大家的直觉不同, 在Verilog的事件模型中, 赋值表达式的具体操作需要从两个子操作来考虑: 首先是求值操作, 用于完成赋值表达式右侧的求值过程; 然后才是更新操作, 用于将求值结果写入到赋值表达式左侧所指示的对象中.

根据上文提到的事件调度行为, 阻塞赋值和非阻塞赋值最大的不同, 就是两者对更新操作的处理不同. 具体地, 阻塞赋值的更新操作是紧跟在求值操作后一同进行的, 没有产生新的更新事件; 而对非阻塞赋值来说, 求值操作和更新操作是分开的, 完成求值操作后, 会生成一个属于的更新事件, 这个更新事件需要等到和均为空时才能处理. 正是这一不同之处, 使得两者开展具体赋值操作的时机有所不同, 进一步使得能看到赋值结果的事件集合并不相同, 从而影响这些事件的行为, 最终影响电路的整体行为.

#### 用事件模型分析Verilog代码的行为

考虑以下代码, 假设在`t`时刻有`a = 1`, `b = 2`, `c = 3`, `d = 4`, `e = 5`. 尝试利用事件模型分析在`t+1`时刻, 变量的值各为多少.

```
always @(posedge clk) begin
  b  = a;
  c <= b;
  d  = c;
  e <= d;
  a  = e;
end
```

- 端口连接 - 对于输入端口的连接`.a(expr)`, 将视为连续赋值语句`assign a = expr;`来处理; 对于输出端口的连接`.b(net)`, 将视为连续赋值语句`assign net = b;`来处理.
- 函数和任务 - 调用时参数按值传递. 返回时, "用返回值替换调用处"的行为按阻塞赋值来处理.

Verilog手册中还定义了如何将更多情况转换成事件来处理, 包括指定延迟信息, 使用过程连续赋值语句, 处理晶体管层次行为等, 需要了解时可以查阅手册中的相关内容.

### 事件处理顺序

事实上, 事件处理的顺序并非100%确定的. 根据Verilog标准手册的定义, 不确定性主要有两个来源:

- 事件队列中有多个激活事件时, 处理顺序是任意的.
- 在行为模块中, 不带时间控制(即`#`表达式和`@`表达式)的语句不必作为一整个事件来处理. 在对行为模块中的一条语句进行求值时, 仿真器可以随时挂起这条语句的执行, 并将剩下的执行操作作为事件队列中的一个激活事件. 这样可以允许不同的过程交织执行, 但交织的顺序是不确定的, 而且不受用户的控制.

为什么Verilog需要引入这些不确定性呢? 要回答这个问题, 我们需要回顾硬件电路的工作方式. 事实上, 硬件电路的行为本身就具有并行性, 多个组件之间天然就是并行工作的.

- 从电路行为模型和真实电路的一致性来看, 并不存在规定这些组件之间工作先后顺序的理由. 如果强行规定这些先后顺序, 就会导致建模结果无法全面地反映真实电路的工作情况. 特别地, 如果真实电路存在问题, 但无法通过建模反映出来并及时修复, 建模就失去意义.
- 从仿真器的软件本质来看, 仿真器只能以串行方式处理不同的事件. 而Verilog标准定义的上述不确定性, 其实是对事件处理顺序的一种"放松": 如果两个事件之间不存在依赖关系, 也不必要求它们按一定的先后顺序来处理. 进一步地, 仿真器甚至可以使用一些并行优化技术来处理这些没有依赖关系的事件, 从而更好地模拟电路组件之间的并行性.

为了全面地理解Verilog代码的行为, 我们还要考虑事件处理顺序的确定性. 为了方便表示, 我们引入一种顺序关系, 标记为, 表示事件先于事件被处理. 上文的事件处理引擎其实隐含了一些顺序要求:

- `顺序规则1` - 如果在处理的过程中生成了, 则. 这是因为, 要处理, 必须先完成的处理.
- `顺序规则2` - 如果在仿真过程中的某一时刻, 有, , 且, 则. 这是因为, 事件处理引擎会在中的事件都处理完后, 才会处理中的事件.

除了这些隐含的顺序, Verilog标准手册还显式定义了如下两条顺序规则:

- `顺序规则3` - `begin`-`end`语句块中的语句需要按语句顺序执行. 也即, 对于同一个`begin`-`end`语句块中的两个语句和, 若, 则.
- `顺序规则4` - 非阻塞赋值操作需要按语句的执行顺序来进行. 也即, 若, 相应的赋值表达式求值操作分别为和, 且有, 则.

例如, 在Verilog标准手册中有如下例子:

```
initial begin
  a <= 0; // (1)
  a <= 1; // (2)
end
```

我们用表示"表达式的求值事件", 用表示"对象的更新事件". 因此, 上例中标注`(1)`的语句可分解为和两个事件. 同理, 标注`(2)`的语句可分解为和两个事件. 应用上文的顺序规则, 可以得到如下结论:

- 考虑`顺序规则1`, 应有,
- 考虑`顺序规则2`, 应有,
- 考虑`顺序规则3`, 应有
- 考虑`顺序规则4`, 应有

综合这些结论, 有且仅有. 也即, 在这个例子中, 仿真器只能按这种顺序来处理事件. 因此, 在仿真过程中, 对象`a`将先被赋`0`, 然后被赋`1`.

### 仿真器和仿真程序

回顾流水灯的例子, 我们来分析其中的事件处理顺序.

```
module light(
  input clk,
  input rst,
  output reg [15:0] led
);
  reg [31:0] count;
  always @(posedge clk) begin
    if (rst) begin led <= 1; count <= 0; end
    else begin
      if (count == 0) led <= {led[14:0], led[15]};
      count <= (count >= 5000000 ? 32'b0 : count + 1);
    end
  end
endmodule
```

假设`clk`上升沿到来, 在这个仿真时刻中, 可能会发生以下事件:



应用上文的顺序规则, 可以得到如下结论:

- 当`rst = 1`时, 应有
- 当`rst = 0`, `count = 0`时, 应有
- 当`rst = 0`, `count != 0`时, 应有

得到上述的事件处理顺序后, 我们可以用C代码直接实现这个顺序, 其中定义的两个宏`EVAL()`和`UPDATE()`, 分别实现了求值事件和更新事件的语义:

```
#define EVAL(c, name, val) do { \
                             c->CONCAT(name, _next) = (val); \
                             c->CONCAT(name, _update) = 1; \
                           } while (0)
#define UPDATE(c, name)    do { \
                             if (c->CONCAT(name, _update)) { \
                               c->name = c->CONCAT(name, _next); \
                             } \
                           } while (0)

static void cycle(Circuit *c) {
  c->led_update = 0;
  c->count_update = 0;
  if (c->rst) {
    EVAL(c, led, 1);
    EVAL(c, count, 0);
  } else {
    if (c->count == 0) {
      EVAL(c, led, (BITS(c->led, 14, 0) << 1) | BITS(c->led, 15, 15));
    }
    EVAL(c, count, c->count >= 5000000 ? 0 : c->count + 1);
  }
  UPDATE(c, led);
  UPDATE(c, count);
}
```

这份C代码虽然实现了流水灯电路仿真的功能, 但其中并没有"事件队列"的概念: Verilog标准手册中定义的事件, 在这份C代码中并非从一个队列中取出的, 而是按照一定的顺序直接"平铺"在C代码中, 但这种顺序又符合Verilog标准手册的约定. 事实上, Verilog标准手册对事件队列的定义是逻辑上的:

```
The Verilog event queue is logically segmented into five different regions.
```

因此, 仿真程序并非必须显式地通过队列的数据结构来维护事件之间的顺序, 只要事件处理顺序符合Verilog标准手册的约定, 仿真程序的行为就是符合手册规范的.

上面这种将事件按照一定的顺序"平铺"的仿真方式, 称为"周期仿真"(cycle simulation). 这种仿真方式以周期为粒度进行, 在每个仿真周期中对电路中的所有组件进行求值. 求值顺序是在仿真开始之前决定好的, 属于事件的静态调度(static scheduling). 由于事件已经按照一定的顺序"平铺"开来, 因此在仿真过程中不需要对事件进行调度, 一方面节省了调度开销, 另一方面事件"平铺"后, 仿真程序也有更多优化的机会, 因此仿真效率较高. 不过周期仿真方式不支持时序信息, 因此只能用于进行同步电路的功能验证. 开源仿真器Verilator采用这种仿真方式.

#### 理解Verilator生成的仿真程序的行为

用Verilator编译流水灯电路, 尝试理解生成的C++代码的行为.

相对地, 上文提到的Verilog标准手册提供的事件处理引擎参考实现, 则称为"事件仿真"(event simulation). 电路的求值顺序是在仿真过程中决定的, 属于事件的动态调度(dynamic scheduling), 因此仿真时需要花费额外的开销来维护事件队列并进行事件的调度, 相比周期仿真方式来说, 仿真效率较低. 不过由于事件队列的存在, 事件仿真方式支持时序信息, 可用于同步电路, 异步电路以及混合电路的功能验证和时序验证. 开源仿真器iVerilog以及大多数商业仿真器(如VCS)都采用这种仿真方式.

### 数据竞争

一个有效的真实电路在各个组件并行工作的情况下, 都应该得到一致的输出. 因此, 这也要求电路模型在上述不确定性的情况下, 不管这些事件按何种顺序处理, 都应该得到一致的结果. 相反, 如果存在两种不同的事件处理顺序, 使得仿真结果不一致, 则称为存在数据竞争(data race). Verilog标准手册将其称为"竞争条件"(race condition), 其含义与数据竞争相同. 通常, 如果仿真过程中存在数据竞争, 这个电路模型所描述的就不是一个有效的真实电路.

考虑如下例子:

```
always @(posedge clk or negedge rstn) begin
  if (!rstn) a = 1'b0;
  else a = b; // (1)
end

always @(posedge clk or negedge rstn) begin
  if (!rstn) b = 1'b1;
  else b = a; // (2)
end
```

代码中存在两个`always`块, 也即存在两个过程. 假设在某时刻有`a = 0`, `b = 1`, `rstn = 1`, 且`clk`的上升沿到来. 考虑到阻塞赋值的求值操作和更新操作是一同完成的, 我们用一个新操作来表示它. 因此, 标注`(1)`和`(2)`的语句可分解为如下事件:



根据Verilog标准手册的定义, 多个激活事件的处理顺序是任意的, 因此其他顺序规则无法适用. 我们可以列出所有可能的事件处理顺序:

- , 结果为`a = 1`, `b = 1`
- , 结果为`a = 0`, `b = 0`

可以看到, 上述代码中存在数据竞争, 当仿真器选择不同的事件处理顺序时, 会导致不同的仿真结果. 这有点类似C语言中的未指定行为, 不同仿真结果可能出现在不同的仿真器中, 也可能会出现在同一款仿真器的不同版本中, 还可能会出现在同一款仿真器, 同一个版本的多次运行中, 甚至可能会出现在同一款仿真器, 同一个版本, 单次运行的不同仿真时刻中. 这些情况都符合Verilog标准手册的约定. 可以看到, 如果Verilog代码中存在数据竞争, 仿真结果可能是难以预测的.

#### 用事件模型分析Verilog代码的行为(2)

将上述代码中的阻塞赋值改成非阻塞赋值, 尝试重新分析可能的事件处理顺序及其结果. 修改后的代码还存在数据竞争吗? 为什么?

```
always @(posedge clk or negedge rstn) begin
  if (!rstn) a <= 1'b0;
  else a <= b;
end

always @(posedge clk or negedge rstn) begin
  if (!rstn) b <= 1'b1;
  else b <= a;
end
```

考虑如下例子:

```
always @(posedge clk or negedge rstn) begin
  if (!rstn) a = 1'b0;
  else a = 1;
end

always @(posedge clk) begin
  $display("a = %d", a);
end
```

假设在某时刻有`a = 0`, `rstn = 1`, 且`clk`的上升沿到来. 根据类似的分析过程, 我们可以得到2个事件:



注意到`$display`系统任务的处理事件. 我们可以列出所有可能的事件处理顺序:

- , 输出`a = 1`
- , 输出`a = 0`

可以看到, 上述代码中存在数据竞争, 虽然和电路本身的行为无关, 但当仿真器选择不同的事件处理顺序时, 仍然会导致不同的仿真结果. 这可能会给开发者的调试带来混乱.

#### 用事件模型分析Verilog代码的行为(3)

将上述代码中的`$display`改成`$strobe`, 尝试重新分析可能的事件处理顺序及其结果. 修改后的代码还存在数据竞争吗? 为什么?

```
always @(posedge clk or negedge rstn) begin
  if (!rstn) a = 1'b0;
  else a = 1;
end

always @(posedge clk) begin
  $strobe("a = %d", a);
end
```

事实上, 我们可以从上面的例子中总结出存在数据竞争的充分必要条件. Verilog代码中存在数据竞争, 当且仅当存在和同一个对象相关的两个事件和, 同时满足:

- 和之间的处理顺序不确定
- 在和中, 至少一个事件会更新

### 良好的Verilog编码风格

要消除数据竞争, 就需要消除满足上述条件的事件. 不过当项目规模变得复杂, 要人工判断代码中是否存在数据竞争, 是很困难的. 为了应对这个挑战, 很多Verilog书籍和相关资料都会推荐一些良好的编码规范, 如果开发者遵循这些编码规范, 就可以消除代码中的绝大部分数据竞争, 从而更有可能设计出行为符合预期的电路.

例如, ["Nonblocking Assignments in Verilog Synthesis, Coding Styles That Kill!"](http://www.sunburst-design.com/papers/CummingsSNUG2000SJ_NBA.pdf) 这篇文章中提出了如下的Verilog编码建议, 并提到, 采用这些建议可以消除90%以上的数据竞争:

1. 时序电路建模时, 用非阻塞赋值.
2. 锁存器电路建模时, 用非阻塞赋值.
3. 用`always`块建立组合逻辑模型时, 用阻塞赋值.
4. 在同一个`always`块中建立时序和组合逻辑电路时, 用非阻塞赋值.
5. 在同一个`always`块中不要既用非阻塞赋值又用阻塞赋值.
6. 不要在一个以上的`always`块中为同一个变量赋值.
7. 用`$strobe`系统任务来显示用非阻塞赋值的变量值.
8. 在赋值时不要使用`#0`延迟.

理解事件模型之后, 我们可以来分析这些建议背后的原理:

1. 之所以采用非阻塞赋值来描述时序逻辑元件, 是因为非阻塞赋值的更新事件在和中的事件处理结束后才处理, 这一特点与"时序逻辑元件在下一个时钟到来时才进行写入"的属性匹配.
2. 在同步电路中锁存器使用并不多, 此处不展开讨论.
3. 之所以采用阻塞赋值来描述组合元件, 是因为阻塞赋值的更新事件在中马上被处理, 其他事件可以马上看到阻塞赋值的更新结果, 从而可以使用更新后的结果进行后续的求值, 这一特点与"组合逻辑元件的输出在输入改变时马上改变"的属性匹配.
4. 和Verilog的可综合语义相关, 下文会进一步讨论.
5. 和上一条建议一样, 这条建议也和Verilog的可综合语义相关, 下文会进一步讨论.
6. 不同的`always`块属于不同的过程, 而不同过程之间的求值顺序是不确定的, 加上对变量赋值会产生更新事件, 正好满足数据竞争的充分必要条件, 因此必定会造成数据竞争.
7. 非阻塞赋值的更新事件属于, 而`$strobe`系统任务的事件属于, 因此`$strobe`系统任务可以输出非阻塞赋值更新后的变量值.
8. `#0`产生的事件属于, 其处理时机位于和之间, 若不理解事件处理顺序, 可能会写出行为与预期不符的代码.

#### 我会写Verilog不就行了吗? 为什么要知道这些?

在这一小节的最开始提到了若干条Verilog的编码建议或描述, 但其中有一些是不正确的. 请尝试找出它们, 并分析它们为什么不正确:

1. 使用`#0`可以将赋值操作强制延迟到当前仿真时刻的末尾.
2. 在同一个`begin`-`end`语句块中对同一个变量进行多次非阻塞赋值, 结果是未定义的.
3. 用`always`块描述组合逻辑元件时, 不能使用非阻塞赋值.
4. 不能在多个`always`块中对同一个变量进行赋值.
5. 不建议使用`$display`系统任务, 因为有时候它无法正确输出变量的值.
6. `$display`无法输出非阻塞赋值语句的结果.

#### 更多的例子和分析

["Nonblocking Assignments in Verilog Synthesis, Coding Styles That Kill!"](http://www.sunburst-design.com/papers/CummingsSNUG2000SJ_NBA.pdf) 这篇文章中还列举了很多例子和分析. 如果你打算使用Verilog, 我们强烈建议你阅读它.

#### 我会写Verilog不就行了吗? 为什么要知道这些?(2)

当然, 就算遵循再多的建议, 也总会有那10%的概率不小心编写出了存在数据竞争的代码. 当你理解了事件模型的细节, 你也就具备了独立分析和解决代码中数据竞争的能力.

况且, 要理解这些内容, 你只需要投入大约1小时. 和你将来花在调试中的时间相比, 这1小时是微不足道的. 光从"可能帮助你避免好几天不知所以然的调试"这一点来说, 这1小时的付出绝对是值得的.

## 逻辑综合(Logic Synthesis) - 从RTL代码到网表

RTL代码只是电路的描述, 而仿真也只是用程序来模拟电路的行为. 如果需要把这个电路制造出来, 晶圆厂还需要更多详细的信息. 具体地, 晶圆厂需要的是一个GDSII(Graphic Design System II)格式的版图文件, 它描述了电路中每个元素的物理位置, 例如, 在坐标`(3, 4)`的位置有一个与门, 在坐标`(4, 2)`和`(0, 2)`之间有一根走线. 要将RTL代码转换成类似的GDS版图, 则需要一系列EDA工具进行多个阶段的处理. 例如, 需要通过"布局"阶段确定每一个门电路的坐标, 需要通过"布线"阶段确定如何通过线网将门电路之间连接起来.

通常, 晶圆厂会提供一个[工艺设计套件](https://en.wikipedia.org/wiki/Process_design_kit)(Process Design Kit, 简称PDK), 其中包含了特定工艺节点下的器件模型, 设计规则, 工艺约束, 验证文件和标准单元库等一系列资源, 物理设计工程师通常使用PDK来设计出符合晶圆厂制造规范的电路. PDK中的标准单元库(standard cell library)包含了该工艺所支持的逻辑单元, 称为标准单元(standard cell). 标准单元是上文提到的GDS版图文件中描述的一部分对象, 它也是EDA工具进行处理的最小单元.

逻辑综合(也简称"综合")是指将RTL描述转换成标准单元的过程. 此外, GDS版图文件中还通过走线记录了标准单元之间的连接关系(也即拓扑结构), 这种连接关系最早是在RTL代码中描述的(也即电路和模块之间的连接关系), 因此综合器也需要在综合结果中包含它们, 以供后续阶段使用, 最终传递到GDS版图文件中. 综上所述, 综合器的输出是标准单元的网表(netlist), 它不仅记录了转换之后的标准单元, 还记录了它们之间的连接关系.

为了让大家进一步了解这个过程, 我们提供了一个基于开源EDA的综合和评估项目. 你可以通过以下命令克隆该项目:

```
git clone git@github.com:OSCPU/yosys-sta.git
```

这个项目通过[开源RTL综合器yosys](https://yosyshq.net/yosys)对RTL代码进行综合, 并将综合结果映射到一个55nm的[开源PDK ICsprout55](https://github.com/openecos-projects/icsprout55-pdk/).

#### 国内的首个开源PDK, 也是发布时全球工艺最先进的开源PDK

ICsprout55是由浙江创芯集成电路有限公司自主研发, 并于2025年10月在中国科学院计算技术研究所ECOS团队协助下一起发布的一款开源PDK. ICsprout55基于成熟的55nm CMOS工艺技术构建, 是中国国内发布的首个开源PDK, 也是截至发布时业界最先进的开源PDK, 对全球的开源芯片生态来说是一项重要的突破.

"一生一芯"的学习讲义曾经采用另一款开源PDK nangate45, 但这款PDK仅面向学术研究, 其中标准单元的数量和质量也与商业PDK有一定差距, 而且不能用于流片, 没有工厂将其用于产线中. 如今ICsprout55的发布填补了我国在这一领域的空白, 让我们向`基于开源IP+开源SoC+开源EDA+开源PDK完成一颗全开源处理器芯片的流片`这个目标迈进了一大步.

感谢浙江创芯集成电路有限公司对开源芯片领域作出的贡献!

#### 尝试使用综合器

克隆上述项目后, 尝试对上文的流水灯项目作为示例进行综合. 你可以在上述项目中通过`make syn`命令进行综合, 但你需要修改一些配置或参数, 具体操作方式请阅读项目中的README.

通过一个示例体验综合过程后, 我们可以来看看综合的网表文件. 在`result`目录下找到综合结果, 打开其中的`.netlist.v`文件. 可以看到, 网表文件中以bit为单位定义了很多信号, 同时还实例化了很多名称类似`NOR2X0P5H7L`, `OAI22X6H7L`的子模块, 这些子模块就是ICsprout55这个PDK提供的标准单元.

那么, 综合器是如何将RTL代码转换成网表的呢? 我们以下面的计数器为例, 向大家介绍综合器yosys的综合过程. 此处提供[yosys的官方手册](https://yosyshq.readthedocs.io/projects/yosys/en/latest/), 供大家需要时查阅.

```
// counter.v
module counter(
  input clk,
  input rst,
  input en,
  output reg [1:0] count
);
  always @(posedge clk) begin
    if (rst) count <= 2'd0;
    else if (en) count <= count + 2'd1;
  end
endmodule
```

### 解析文件(Parsing)

可以通过如下命令让yosys读入源文件并解析:

```
$ yosys counter.v

-- Parsing `counter.v' using frontend ` -vlog2k' --

1. Executing Verilog-2005 frontend: counter.v
Parsing Verilog input from `counter.v' to AST representation.
Storing AST representation for module `$abstract\counter'.
Successfully finished Verilog frontend.

yosys>
```

可以看到, yosys对`counter.v`进行了解析, 并将其转换为抽象语法树(AST), 然后输出命令提示符`yosys>`. 如果希望退出yosys, 可以在命令提示符后键入`exit`.

解析源文件的过程和C语言的编译非常类似, 包含词法分析和语法分析. 如果去掉源文件中的其中一个分号`;`, 重新运行命令, 你会发现yosys报告如下错误:

```
counter.v:10: ERROR: syntax error, unexpected TOK_ELSE
```

### 细化(Elaboration)

细化阶段的工作包括解析模块间的实例化关系, 计算模块实例的参数, 完成模块实例化的实例名和端口绑定等.

可以通过如下命令让yosys开展细化工作:

```
yosys> hierarchy -check -top counter

2. Executing HIERARCHY pass (managing design hierarchy).

3. Executing AST frontend in derive mode using pre-parsed AST for module `\counter'.
Generating RTLIL representation for module `\counter'.

3.1. Analyzing design hierarchy..
Top module:  \counter

3.2. Analyzing design hierarchy..
Top module:  \counter
Removing unused module `$abstract\counter'.
Removed 1 unused modules.
```

可以看到, `hierarchy`命令还需要指定一个顶层模块, yosys将以这个顶层模块为起点, 依次展开所有实例化的子模块, 从而确定整个设计的边界, 未被实例化的模块将被删除. 同时, 细化阶段还将整个设计的AST转换成yosys的一种中间语言RTLIL, 这和C语言编译中的中间代码生成阶段非常相似.

#### 语义分析

我们可以猜想, 在yosys的细化阶段中还进行了类似C语言编译中语义分析的工作. 例如, 如果将`counter.v`中的`posedge clk`改为`posedge counter`, yosys将在执行上述`hierarchy`命令时报告如下错误:

```
counter.v:8: ERROR: Found posedge/negedge event on a signal that is not 1 bit wide!
```

如果在`counter.v`中添加一条模块实例化语句`mymodule abc(clk, rst);`, yosys将在执行上述`hierarchy`命令时报告如下错误:

```
ERROR: Module `\mymodule' referenced in module `\counter' in cell `\abc' is not part of the design.
```

可以看到, 这两种错误都符合Verilog的语法, 因此无法在解析文件阶段发现.

#### 中间代码生成

`hierarchy`命令成功执行后, 我们就可以来查看整个设计的RTLIL了. 通过执行`dump`命令, yosys会将当前设计的RTLIL以文本形式输出到终端:

```
yosys> dump
```

或者通过`write_rtlil`命令将RTLIL输出到文件:

```
yosys> write_rtlil counter.rtlil
```

以`counter.rtlil`文件为例, 其内容如下:

```
autoidx 3
attribute \hdlname "counter"
attribute \top 1
attribute \src "counter.v:2.1-12.10"
module \counter
  attribute \src "counter.v:8.3-11.6"
  wire width 2 $0\count[1:0]
  attribute \src "counter.v:10.27-10.39"
  wire width 2 $add$counter.v:10$2_Y
  attribute \src "counter.v:3.9-3.12"
  wire input 1 \clk
  attribute \src "counter.v:6.20-6.25"
  wire width 2 output 4 \count
  attribute \src "counter.v:5.9-5.11"
  wire input 3 \en
  attribute \src "counter.v:4.9-4.12"
  wire input 2 \rst
  attribute \src "counter.v:10.27-10.39"
  cell $add $add$counter.v:10$2
    parameter \A_SIGNED 0
    parameter \A_WIDTH 2
    parameter \B_SIGNED 0
    parameter \B_WIDTH 2
    parameter \Y_WIDTH 2
    connect \A \count
    connect \B 2'01
    connect \Y $add$counter.v:10$2_Y
  end
  attribute \src "counter.v:8.3-11.6"
  process $proc$counter.v:8$1
    assign $0\count[1:0] \count
    attribute \src "counter.v:9.5-10.40"
    switch \rst
      attribute \src "counter.v:9.9-9.12"
      case 1'1
        assign $0\count[1:0] 2'00
      attribute \src "counter.v:10.5-10.9"
      case
        attribute \src "counter.v:10.10-10.40"
        switch \en
          attribute \src "counter.v:10.14-10.16"
          case 1'1
            assign $0\count[1:0] $add$counter.v:10$2_Y
          case
        end
    end
    sync posedge \clk
      update \count $0\count[1:0]
  end
end
```

我们对输出的RTLIL进行一些说明, 关于RTLIL的更多内容, 可以查阅[yosys的相关手册](https://yosyshq.readthedocs.io/projects/yosys/en/latest/yosys_internals/formats/rtlil_rep.html):

- `attribute`用于标识一些属性, 例如, `attribute \src "counter.v:10.27-10.39"`用于标识相应的元素在源文件中的位置, 即`counter.v`中的第10行第27列至第10行第39列.
- `wire width 2 $0\count[1:0]`表示定义一个位宽为`2`的信号, 其名称为`$0\count[1:0]`(注意, `$`, `\`, `[`, `:`和`]`这些字符都是名称的一部分).
- `cell $add $add$counter.v:10$2`表示实例化一个类型为`$add`的单元, 其名称为`$add$counter.v:10$2`. 单元的具体参数用`parameter`表示, 例如, `parameter \A_WIDTH 2`表示单元的端口`A`的位宽为`2`, `parameter \A_SIGNED 0`表示单元的端口`A`是无符号的. 端口的连接关系用`connect`表示, 例如, `connect \Y $add$counter.v:10$2_Y`表示单元的端口`Y`与信号`$add$counter.v:10$2_Y`相连.
- `process`表示一个行为描述过程, 其中`assign`表示信号的赋值, `switch`-`case`表示根据信号的值进行条件性赋值, `sync`表示当条件满足时对信号进行更新.

可以看到, RTLIL的语法虽然和Verilog不同, 但我们仍然能感觉到, RTLIL也是在描述硬件, 甚至能感觉到`process`和Verilog代码中的`always`存在对应关系. 不过, 一些运算符被单元(cell)取代了, 例如`+`被`$add`取代, 因此和输入的Verilog代码相比, 当前的RTLIL更接近网表. 类似`$add`这些单元, 属于[yosys的内部单元库(internal cell library)](https://yosyshq.readthedocs.io/projects/yosys/en/latest/cell_index.html).

我们还可以将RTLIL中的拓扑关系通过结构图的方式进行可视化. 不过在这之前, 你可能需要安装一个`Graphviz dot`类型文件的查看工具:

```
apt-get install xdot
```

然后, 你可以在yosys中执行`show`命令, 它会自动调用`xdot`等工具打开结构图:

```
yosys> show
```

`show`命令生成的结构图文件默认保存在`~/.yosys_show.dot`, 多次执行`show`命令会将其覆盖, 你可以将其手动拷贝到其他目录下, 并通过`xdot`工具打开它.

#### 查看结构图

通过`show`命令查看当前的结构图, 从而认识RTLIL.

### 粗粒度综合(Coarse-grain synthesis)

粗粒度综合阶段负责基于设计的"粗粒度表示"进行处理. 在这里, 粗粒度表示是指采用[字级单元](https://yosyshq.readthedocs.io/projects/yosys/en/latest/cell/index_word.html)(word-level cells)来描述设计. 字级单元是yosys内部单元库的其中一部分, 这些单元位于相对较高的抽象层次, 支持多位宽和参数功能. 在命名风格上, 字级单元通常以`$`为前缀来命名. 上文提到的`$add`单元就属于字级单元, 其他的字级单元还包括`$shift`(移位运算), `$mux`(选择运算)等.

#### 将过程描述转换为粗粒度表示

不过, 目前的RTLIL还存在`process`这样的过程描述(在结构图中通过`PROC`节点表示), 它们还不属于粗粒度表示, 无法对其开展粗粒度表示相关的处理工作. 因此, yosys还需要先将所有过程描述转换为粗粒度表示, 这可以通过`proc`命令来实现:

```
yosys> proc
```

`proc`命令其实是一条宏命令(macro command), 它会依次调用一系列子命令来完成过程描述的转换:

| 步骤 | 子命令 | 说明 |
| --- | --- | --- |
| 1 | `proc_clean` | 移除空分支和空的过程描述 |
| 2 | `proc_rmdead` | 移除不可达的`case`分支 |
| 3 | `proc_prune` | 移除冗余的赋值操作(被后续赋值操作所覆盖) |
| 4 | `proc_init` | 将过程描述中的`init`操作转换为相应信号上的`init`属性 |
| 5 | `proc_arst` | 识别异步复位 |
| 6 | `proc_rom` | 将过程描述中的`switch`操作在适合时转换为ROM |
| 7 | `proc_mux` | 将过程描述中的`switch`操作转换为`$mux`单元(多路选择器) |
| 8 | `proc_dlatch` | 将过程描述中的锁存器转换为D锁存器类型的单元 |
| 9 | `proc_dff` | 将过程描述中的触发器转换为D触发器类型的单元 |
| 10 | `proc_memwr` | 将过程描述中的存储器写操作转换为`$memwr`单元 |
| 11 | `proc_clean` | 移除空分支和空的过程描述 |
| 12 | `opt_expr -keepdc` | 进行表达式相关的优化 |

有一些子命令和C语言的编译优化技术很类似, 它们对你来说应该不难理解. 从整体上看, `proc`命令主要将RTLIL中过程描述的`switch`-`case`部分转换为`$mux`单元, 将`sync`描述转换为D锁存器类型或D触发器类型的单元, 从而得到完整的粗粒度表示.

#### 查看结构图(2)

通过`show`命令查看当前的结构图, 对比执行`proc`命令前后的不同.

#### 优化

和编译优化类似, 综合器一般也提供优化的功能, 使得开发者可以将精力集中在架构设计和逻辑设计当中, 而不必在设计阶段过多考虑电路的性能表现, 综合器通常能提供一个还不错的性能下限.

得到完整的粗粒度表示后, 就可以应用一系列优化来生成更优的设计了. 这可以通过`opt`命令来实现:

```
yosys> opt
```

和上文介绍的`proc`类似, `opt`也是一条宏命令, 它会依次调用一系列子命令来开展各种优化:

| 步骤 | 子命令 | 说明 |
| --- | --- | --- |
| 1 | `opt_expr` | 常量合并和简单表达式改写 |
| 2 | `opt_merge -nomux` | 合并相同的单元, 但不合并选择器类型的单元 |
|  | `do` | 开始循环 |
| 3 | `opt_muxtree` | 移除嵌套选择器中的不可达分支 |
| 4 | `opt_reduce` | 简化多输入的选择器, 与门和或门 |
| 5 | `opt_merge` | 合并相同的单元 |
| 6 | `opt_share` | 合并输入相同, 类型相同, 且不会同时激活的单元 |
| 7 | `opt_dff` | D触发器的常量优化和时钟复位信号合并 |
| 8 | `opt_clean` | 移除无用的单元和线网 |
| 9 | `opt_expr` | 常量合并和简单表达式改写 |
|  | `while (changed)` | 若设计发生变化, 则跳转到第3步继续循环 |

下面列举一些常见的优化技术. 为了方便理解, 我们用Verilog代码来呈现优化前后的语义.

- 常量合并和简单表达式改写(`opt_expr`) - 在一些表达式中, 若某输入为特定的常量, 或表达式符合某种特殊样式, 可对其进行简化. 以下示例中, 表达式`a != a`的结果必定为`0`, 故可优化为`assign x = 1'b0`; 进一步地, 应用常量传播优化技术后, 表达式`b | x`的结果必定为`b`, 故可优化为`assign y = b;`; 此外, 由于`c`的位宽为1, 表达式`c == 0`与`~c`等价, 故可优化为`assign z = ~c;`. 综合器可以用计算结果替代这些单元, 从而简化相应的电路.

```
//          优化前              |            优化后
  wire a, b, c, x, y, z;       |    wire a, b, c, x, y, z;
  // ......                    |    // ......
  assign x = a != a;           |    assign x = 1'0;
  assign y = b | x;            |    assign y = b;
  assign z = c == x;           |    assign z = ~c;
```

- 合并相同单元(`opt_merge`) - 对于多个功能和输入都相同的单元, 可将其合并成一个单元, 让其输出驱动原来的各输出信号, 从而减少单元的数量. 以下示例中, `a + b`和`b + a`这两个单元的功能和输入都相同, 可直接让`x`驱动`y`, 从而减少一个加法单元.

```
//          优化前              |            优化后
  wire a, b, x, y;             |    wire a, b, x, y;
  // ......                    |    // ......
  assign x = a + b;            |    assign x = a + b;
  assign y = b + a;            |    assign y = x;
```

#### 面积和性能的权衡

需要注意的是, 这种优化虽然减少了单元的数量, 但却增加了单元的扇出(即与该单元输出相连的下游单元的数量). 在其他条件保持不变的情况下, 扇出增大会使得电路延迟上升.

用生活中的例子来比喻, 单元的输出就像是水龙头, 用于向下游的水池提供水流, 当水池充满水时, 才能推开闸门, 类似让下游的晶体管发生翻转. 优化前, 两个水龙头各自向下游的水池提供水流; 优化后, 水龙头数量节省了, 但它需要同时向下游的两个水池提供水流. 在水流速度不变的情况下, 要让两个水池达到充满状态, 则需要花费更长的时间, 这个时间就类似于电路的延迟.

在需要优化延迟的场合, 反而会采用"复制单元"的方法添加水龙头的数量. 因此, 是采用合并单元还是采用复制单元, 其实是面积和性能之间的权衡.

- 移除嵌套选择器中的不可达分支(`opt_muxtree`) - 在嵌套的选择器中, 某些分支因条件冲突而不可达, 可将其移除. 以下示例中, 内层选择器`a ? b : c`的结果不可能为`c`, 因为这要求外层的选择信号`a = 1`, 同时要求内层的选择信号`a = 0`, 矛盾. 因此可将内层的选择器单元替换为`b`, 从而简化相应的电路.

```
//          优化前              |            优化后
  wire a, b, c, d, x;             |    wire a, b, c, d, x;
  // ......                       |    // ......
  assign x = a ? (a ? b : c) : d; |    assign x = a ? b : d;
```

- 简化多输入的选择器, 与门和或门(`opt_reduce`) - 对于多输入的选择器, 与门和或门, 它们中有一些输入可能相同, 可以对这些输入进行消除或合并. 以下示例中, 优化前需要在两个32位的信号中进行选择, 得出`imm`, 但对于这两个信号来说, 它们的第12到第31位都分别和第11位相同(一个是`0`, 另一个是`inst[31]`), 因此可以对选择器的输入进行优化, 先选择第0到第11位的部分作为`imm[11:0]`, 再将选出的第11位作为`imm[31:20]`. 优化后, 选择器的数据端位宽从32降低到12. 类似地, 通过`&imm`进行归约与运算(reduce and)时, 由于输入`imm`的第12到第31位都和第11位相同, 故可直接移除输入的第12到第31位, 其结果与`&imm[11:0]`相同. 优化后, 与门的输入端位宽从32降低到12.

```
//          优化前              |            优化后
  wire [31:0] inst, imm;          |    wire [31:0] inst, imm;
  wire sel, x;                    |    wire sel, x;
  // ......                       |    // ......
  assign imm = !sel ? 32'b0 :     |    assign imm[11:0] = !sel ? 12'b0 : inst[31:20];
    {{20{inst[31]}}, inst[31:20]};|    assign imm[31:12] = {20{imm[11]}};
  assign x = &imm;                |    assign x = &imm[11:0];
```

- D触发器的常量优化(`opt_dff`) - 若D触发器的数据输入端为常量, 则可将其替换为常量, 从而移除相应的D触发器单元. 以下示例中, D触发器`r`的数据输入端为常量, 可直接将其优化成一个常量信号.

```
//          优化前              |            优化后
  reg [31:0] r;                   |    wire [31:0] r;
  // ......                       |    // ......
  always @ (posedge clk)          |    assign r = 32'hdeadbeef;
    r <= 32'hdeadbeef;            |
```

- 移除无用的单元和线网(`opt_clean`) - 如果某些单元和线网不影响模块的输出, 可将其移除. 以下示例中, 线网`t`不影响模块的输出端口`x`, 故可将其与单元`a & b`一同移除.

```
//          优化前              |            优化后
  module m(                       |    module m(
    input a, b;                   |      input a, b;
    output x;                     |      output x;
  );                              |    );
    wire t;                       |      assign x = a + b;
    assign x = a + b;             |    endmodule
    assign t = a & b;             |
  endmodule                       |
```

除了上文介绍的技术, 综合过程中使用的优化技术还有很多, 例如位宽削减, 窥孔优化等, 此处我们不展开讨论, 感兴趣的同学可以查阅[yosys的文档](https://yosyshq.readthedocs.io/projects/yosys/en/latest/using_yosys/synthesis/opt.html)或相关资料.

#### 查看结构图(3)

通过`show`命令查看当前的结构图, 对比执行`opt`命令前后的不同.

#### 有限状态机的识别和处理

我们之前介绍过计算机系统的状态机模型, 其中说明过数字电路也可以看成一个状态机. 这里的有限状态机(Finite State Machine, FSM)更多是指设计中用数字逻辑实现的, 具有状态机特征的部分.

例如, 你应该在HDLBits上完成过类似"识别连续的3个`1`"的题目. 针对这个问题, 我们可以列出如下状态转移表(表项含义为"次态/输出"):

|  | 含义 | 输入`0` | 输入`1` |
| --- | --- | --- | --- |
| `S0` | 初始状态 | `S0`/`0` | `S1`/`0` |
| `S1` | 识别了1个`1` | `S0`/`0` | `S2`/`0` |
| `S2` | 识别了2个`1` | `S0`/`0` | `S2`/`1` |

对于一些更复杂的FSM, 其中可能包含一些冗余状态, 或者可合并的状态, 输入和输出, 但这些情况在运算符类别的字级单元上很难发现. 因此综合器一般先在字级单元上识别出FSM, 然后在FSM的语义上对其进行分析和优化, 最后再将其映射回字级单元.

在yosys中, 这可以通过`fsm`命令来实现:

```
yosys> fsm
```

`fsm`也是一条宏命令, 它会依次调用一系列子命令来开展FSM的处理, 主要的处理步骤包括:

1. `fsm_detect` - FSM检测, 根据一定的规则在RTLIL中识别出FSM, 并用特殊属性标记相关单元
2. `fsm_extract` - FSM抽取, 将标记的相关单元用`$fsm`单元替代, 并解析出状态转移表
3. `fsm_opt` - FSM优化, 根据状态转移表对FSM进行优化, 包括移除无用的输出信号, 合并上游相同的输入信号, 合并相同状态下输出相同的不同输入, 根据常量输入简化状态等
4. `fsm_recode` - FSM重编码, 使用独热码对状态信号进行重新编码
5. `fsm_map` - 单元映射, 将处理后的`$fsm`单元映射回字级单元

不过, 上述`counter.v`并不包含FSM, 因此执行上述`fsm`命令并没有效果. 理论上讲, 根据数字电路的状态机模型, 我们可以尝试将任意数字电路设计整体看作一个FSM来开展上述处理, 但这样解析出的状态转移表非常庞大(对于一个32位的寄存器, 就已经有种状态), 这会带来两方面的问题: 一方面, 处理这样的状态空间需要的计算量, 已经远高于当前计算机的计算能力; 另一方面, 这样的状态在输入, 输出, 次态这些方面的相似性非常低, 几乎不可能找到可以优化的状态和信号. 因此, 数字电路的状态机模型只用于帮助我们理解基本原理, 实际中并不会将其用于FSM优化.

#### 存储器的识别和处理

另一种需要特殊处理的单元是存储器. 在yosys中, 可以通过`memory`命令来对RTLIL进行存储器相关的处理:

```
yosys> memory
```

`memory`也是一条宏命令, 它会依次调用一系列子命令, 相关处理包括将上下游的触发器合并到存储器的读写单元, 将存储器的多个读写单元合并成一个多端口的存储器单元等.

在FPGA流程中, 由于FPGA提供的存储器器件类型不多(如LUT RAM, Block RAM和FF), FPGA综合器可以通过上文的方式自动在RTL代码中识别出存储器, 并根据识别出的存储器属性将其映射到物理上的存储器器件. 利用FPGA的可编程性, 综合器可以实现存储器器件的按需分配, 也即, 综合器可以根据RTL代码动态计算出需要多大的存储器, 并映射到它们.

但对于ASIC流程来说则并非如此. 为了提升存储器的性能, ASIC流程的存储器单元中并不包含可编程的功能, 而是由标准单元库提供若干种规格确定的存储器供RTL开发者选择. 这些存储器单元还有不同的性能, 面积和功耗属性, 例如, 要在RTL层次实现`64x64`的存储器功能, RTL开发者可以选择1个`64x64`的存储器单元, 也可以选择2个`32x64`的存储器单元进行拼接. 前者具有较小的总面积, 但读延迟可能较高; 而后者的总面积较大, 但读延迟较优. 此外, 不同的存储器规格具有不同的形状, 也会对后续的布局布线产生影响. 这些互相制约的因素使得综合器难以自动进行存储器的识别和映射, 因此需要RTL开发者需要根据设计目标自行选择存储器规格, 并在RTL代码中手动以子模块的方式实例化存储器单元.

可以说, ASIC流程和FPGA流程在存储器使用方式的差异上, 体现的是性能和灵活性的权衡: ASIC追求更高的性能, 但灵活性较弱, 难以实现按需分配, 需要开发者自行选择具体规格; FPGA的灵活性较好, 但存储器器件的可编程功能使其性能表现不如ASIC.

不过, 上述`counter.v`并不包含存储器, 因此执行上述`memory`命令并没有效果. 在将来一段时间内, 我们都不会接触包含这种存储器的电路设计. 我们会在A阶段再讨论存储器的问题.

### 细粒度综合(Fine-grain synthesis)

细粒度综合阶段负责基于设计的"细粒度表示"进行处理. 如上文所述, 所谓细粒度表示, 是指采用门级的单元来描述设计. yosys的内部单元库中有一类[门级单元](https://yosyshq.readthedocs.io/projects/yosys/en/latest/cell/index_gate.html)(gate-level cells), 和粗粒度表示中采用的单元相比, 这些门级单元的数据位宽都是1, 而且不提供参数功能. 在命名风格上, 门级单元通常以`$_XXX_`的形式命名, 其中`XXX`一般采用大写, 从而与字级单元区分开来.

细粒度综合首先需要将设计的粗粒度表示转换为细粒度表示, 这可以通过`techmap`命令来实现:

```
yosys> techmap
```

`techmap`命令用于将当前设计的单元替换成指定单元库中的单元实现, 若不指定单元库, 命令将采用yosys内部的门级单元库.

替换为门级单元后, 还需要对一些多位的线网和端口进行拆分, 否则RTLIL中将会包含不必要的位抽取和位拼接操作. 这可以通过`splitnets`命令来实现:

```
yosys> splitnets -ports
```

然后, 可以执行`opt -full`命令让yosys开展一些优化工作, 以清除无用的单元和线网, 然后再查看结构图.

可以看到, 粗粒度表示中位宽为2的D触发器单元被拆分为2个位宽为1的D触发器单元, 加法器单元`$add`也被拆分为一些门级单元. 因此, 和粗粒度表示相比, 当前的细粒度表示更接近网表.

#### 查看结构图(4)

通过`show`命令查看当前的结构图, 对比执行`techmap`命令前后的不同.

### 工艺映射(Technology mapping)

工艺映射是指从工艺无关的电路表示映射到具体工艺的实现. 在这里, 工艺映射阶段负责将设计的细粒度表示映射到目标工艺的标准单元. 为了展示工艺映射的效果, 我们采用一个简单的示例标准单元库, 它源于yosys手册:

```
library(demo) {
  cell(BUF) {
    area: 6;
    pin(A) { direction: input; }
    pin(Y) { direction: output;
              function: "A"; }
  }
  cell(NOT) {
    area: 3;
    pin(A) { direction: input; }
    pin(Y) { direction: output;
              function: "A'"; }
  }
  cell(NAND) {
    area: 4;
    pin(A) { direction: input; }
    pin(B) { direction: input; }
    pin(Y) { direction: output;
             function: "(A*B)'"; }
  }
  cell(NOR) {
    area: 4;
    pin(A) { direction: input; }
    pin(B) { direction: input; }
    pin(Y) { direction: output;
             function: "(A+B)'"; }
  }
  cell(DFF) {
    area: 18;
    ff(IQ, IQN) { clocked_on: C;
                  next_state: D; }
    pin(C) { direction: input;
                 clock: true; }
    pin(D) { direction: input; }
    pin(Q) { direction: output;
              function: "IQ"; }
  }
}
```

将上述内容保存到文件`cell.lib`, 它以文本方式描述了标准单元的属性. 上述文件包含如下属性:

- 单元的面积(area), 一般以为单位
- 端口(pin), 其中又标识了方向(direction); 特别地, 输出端口还包含功能(function)属性, 通过逻辑表达式给出; 对于触发器的时钟输入端口, 还包含时钟(clock)属性, 用于标识该端口为时钟信号

在yosys中, 工艺映射的过程分两步. 首先通过如下命令对时序逻辑单元进行工艺映射:

```
yosys> dfflibmap -liberty cell.lib
```

执行上述命令后查看结构图, 你会发现在细粒度表示中, 门级单元`$_SDFFE_PP0P_`被替换成`DFF`和一些`$_MUX_`, 其中`DFF`就是标准单元库`cell.lib`中的标准单元. 之所以这一步骤会产生额外的`$_MUX_`, 是因为`cell.lib`中没有与`$_SDFFE_PP0P_`功能完全相同的标准单元: 查阅yosys手册发现, `$_SDFFE_PP0P_`的功能是"带高有效同步复位信号和高有效使能信号的正边沿D触发器", 但`cell.lib`中仅有的时序逻辑单元`DFF`只是一个简单的D触发器, 因此需要引入一些额外的组合逻辑单元来实现"高有效同步复位信号"和"高有效使能信号"的功能.

不过你会发现, `DFF`单元的输出端`Q`在结构图中出现在代表输入端的左侧, 这是因为`cell.lib`对yosys来说属于外部单元库, `show`命名默认没有关于`DFF`这个标准单元的信息. 为了修复这个问题, 我们可以让yosys先读入`cell.lib`这个标准单元库:

```
yosys> read_liberty -lib cell.lib
```

成功读入后, 再执行`show`命令, 即可修复该问题.

#### 查看结构图(5)

通过`show`命令查看当前的结构图, 对比执行`dfflibmap`命令前后的不同.

接下来通过如下命令对组合逻辑单元进行工艺映射:

```
yosys> abc -liberty cell.lib
```

`abc`命名将会调用一个外部工具`ABC`来进行组合逻辑单元的工艺映射工作. 所有门级单元都被替换成标准单元库`cell.lib`中的标准单元. 最后通过`clean`命令清除无用的单元和连线, 就得到了最终的网表, 从而完成从RTL代码到网表的转换.

#### 查看结构图(6)

通过`show`命令查看当前的结构图, 对比执行`abc`命令前后的不同.

#### 工艺映射和yosys的techmap命令

在之前的细粒度综合阶段, 我们介绍了yosys的`techmap`命令, 它其实也是Technology Mapping的缩写. yosys官方手册对Technology Mapping的说明分两步: 第一步是将字级单元映射到门级单元, 第二步是将门级单元映射到目标工艺的标准单元.

这其实和讲义中介绍的工艺映射概念有所不同: 讲义对工艺映射的理解更多是强调"从抽象到具体". 为了与行业概念保持一致, 我们没有采用yosys官方手册中对工艺映射的理解. 因此, yosys官方手册中描述的"工艺映射的第一步", 其实对应讲义中的"细粒度综合"; 而yosys官方手册中描述的"工艺映射的第二步", 其实对应讲义中的"工艺映射".

### 网表和报告生成

最后, 通过`write_verilog`命令将网表写入到文件, 并通过`stat`命令输出所用标准单元的信息:

```
yosys> write_verilog netlist.v
yosys> stat -liberty cell.lib
```

#### 通过yosys的日志文件了解综合过程

你已经对流水灯项目进行综合了. 尝试查看`yosys-sta/result`目录下的yosys日志文件, 结合上述文字了解综合过程.

为了避免反复键入yosys的命令, `make syn`通过脚本驱动yosys进行综合, 具体可查阅`yosys-sta/scripts/yosys.tcl`. 如果你想进一步了解yosys的命令, 可以查阅yosys的官方手册, 或者在yosys的命令行中输入`help xxx`来查看`xxx`命令的相关信息.

### Verilog的RTL综合语义

将什么样的RTL代码转换成什么样的标准单元, 需要考虑RTL综合的语义. 但Verilog标准手册定义的是Verilog的仿真语义, 因此不适用于RTL综合这一场景. 为此, [Verilog RTL综合标准手册](https://0x04.net/~mwk/vstd/ieee-1364.1-2002.pdf)专门描述了Verilog语言在综合场景下的语义. 综合器读入Verilog代码, 然后根据这一标准手册所描述的语义, 将Verilog代码转换成语义等价的标准单元.

Verilog RTL综合标准手册的第1.1节介绍了RTL综合的背景:

```
This standard defines a set of modeling rules for writing Verilog® HDL descriptions
for synthesis. Adherence to these rules guarantees the interoperability of Verilog
HDL descriptions between register-transfer level synthesis tools that comply to this
standard. The standard defines how the semantics of Verilog HDL are used, for
example, to describe level- and edge-sensitive logic. It also describes the syntax
of the language with reference to what shall be supported and what shall not be
supported for interoperability.

Use of this standard will enhance the portability of Verilog-HDL-based designs
across synthesis tools conforming to this standard. In addition, it will minimize
the potential for functional mismatch that may occur between the RTL model and the
synthesized netlist.
```

一些关键的信息包括:

- 这份标准描述了Verilog语法中, 哪些是综合器需要支持的, 哪些是综合器不支持的. 这说明, 综合器支持的Verilog语法, 只是Verilog整体语法中的一个子集.
- 采用这份标准可以提升Verilog设计在不同综合器之间的可移植性, 从而让符合标准的综合器能按一致的语义来解析符合标准的Verilog代码.
- 采用这份标准也可以尽可能避免RTL模型和综合网表之间功能不一致的潜在风险.

#### RTFM

阅读Verilog RTL综合标准手册的第5章`Modeling hardware elements`, 了解什么样的Verilog代码被综合成什么样的电路.

这部分内容只有10页左右, 但比其他所有Verilog学习资料都要权威, 而且提供了大量的代码示例和说明, 甚至连`x`和`z`在哪些使用场景下是可综合, 都有详细的说明.

事实上, 上文引用的若干Verilog编码建议, 其中有一些建议就是依据Verilog RTL综合标准手册的规范提出的.

由于仿真和综合的语义不完全一致, 因此可能会出现同一份Verilog代码在仿真和综合这两个场景下行为不一致的问题. 在芯片设计的流程中, 仿真和综合都是必须的步骤, 而且考虑到物理设计和制造, 我们设计的Verilog代码的行为需要以综合为准. 这要求我们需要避免编写出在仿真和综合这两个场景下行为不一致的代码.

Verilog RTL综合标准手册的附录B`Functional mismatches`描述了一些发生这种问题的场景. 其中`B.1`小节提到的就是不确定性的行为, 举例如下:

```
always @(posedge clock) begin
  a = 0;
  a = 1;
end

always @(posedge clock)
  b = a;
```

#### 用事件模型分析Verilog代码的行为(4)

尝试用事件模型分析上述代码为什么存在数据竞争.

在这个例子中, 综合器可以自由选择将`0`或`1`作为触发器`b`的输入. 但不管如何选择, 由于数据竞争的存在, 综合网表的行为都可能与仿真结果不一致.

#### RTFM(2)

阅读Verilog RTL综合标准手册的附录B, 了解还有哪些情况会造成综合网表和仿真行为的功能不匹配.

#### Chisel福利

如果你打算选择Chisel语言来设计电路, 你不必考虑上文提到的数据竞争和功能不匹配的问题, 因为Chisel语言的语义保证了生成的Verilog代码不存在这些问题.

## 用开源EDA工具评估电路

由于网表中的标准单元是可制造的, 它具备各种物理属性, 因此在得到网表后, 我们就可以对电路的好坏进行初步评估了. 衡量一个电路的好坏有多个维度, 常用的三个维度分别是性能, 功耗, 面积, 它们统称为PPA(Performance, Power, Area).

### 面积评估

最简单的是面积评估. `.lib`文件已经给出了标准单元的面积属性, 综合器只需要统计出每个标准单元在网表中实例化的次数, 即可计算出当前设计的总面积.

### 性能评估

一个电路的性能主要通过频率来衡量, 也即"电路每秒最多能工作多少次". 这又是由"完成一次工作最少需要花多少时间"来决定的. 我们将"一次工作"定义为"时序逻辑元件在时钟信号的驱动下更新状态". 因为这些指标和时间相关, 因此分析它们的过程也称为时序分析(timing analysis).

回顾数字电路的状态机模型, 时序逻辑元件会在时钟信号到来时更新其状态. 这里的"状态"本质上也是数据, 需要通过组合逻辑计算得到. 但组合逻辑的计算需要经过一定的延迟, 因此我们需要控制好时钟的频率, 使得两次时钟之间的间隔(也即周期)能足够容纳组合逻辑的延迟; 否则, 用于更新状态的数据信号并不是由组合逻辑计算出的稳定结果, 这样电路工作时的行为就与我们设计的预期不符.

```
    +------------------+
+-->| Sequential Logic |----+
|   +------------------+    |
| next state                | current state
|                           |
|  +---------------------+  |
+--| Combinational Logic |<-+
   +---------------------+
```

因此, 评估电路的性能, 就是通过评估电路中组合逻辑的延迟, 来推算出电路可以工作的最高频率. 如果电路的实际工作频率高于这个最高频率, 电路中的某些时序逻辑元件的新状态将与我们设计的预期不符, 从而无法让电路按照预期开展工作.

#### 更快的代价

有一些电子发烧友会尝试对处理器进行超频, 让处理器运行在比厂商所宣称的最高频率更高的频率, 从而尝试获得更好的计算机使用体验. 不过, 如果超频失败, 计算机将会进入不稳定状态, 运行一段时间后可能会卡死.

卡死的本质原因其实和上文的介绍一样: 由于处理器工作得太快, 其中某些时序逻辑单元没有按照预期的数据进行更新, 最终造成处理器进入错误的状态.

电路中的组合逻辑有很多, 而电路的工作频率受限于电路中延迟最长的一条组合逻辑路径, 这条路径称为电路的"关键路径"(critical path). 为了找到电路中的关键路径, EDA工具需要从标准单元库中读出标准单元的延迟信息, 然后对综合出的网表进行分析, 计算出组合逻辑路径上所有标准单元的总延迟, 总延迟最长的路径即为电路的关键路径. 这个评估过程可以基于网表和标准单元库的延迟信息来开展, 不涉及电路工作的过程, 因此称为静态时序分析(STA, Static Timing Analysis). 需要说明的是, 上文的`cell.lib`只是一个简单的实例, 其中未包含延迟信息, 因此无法用于静态时序分析.

不过, ICsprout55中的标准单元库已经提供了完整的标准单元延迟信息. 在`yosys-sta`项目中执行`make sta`命令, 就可以在ICsprout55上评估RTL设计的性能. 具体地, 该命令首先调用综合器yosys对RTL设计进行综合, 得到ICsprout55标准单元的网表; 然后将网表文件和PDK中的标准单元信息文件输入到[开源静态时序分析工具iSTA](https://github.com/OSCC-Project/iEDA/tree/master/src/operation/iSTA)中, iSTA将快速评估RTL设计中的路径延迟, 并报告距离目标频率差距最大的若干条路径供用户参考.

#### 评估电路的性能

尝试通过`yosys-sta`项目评估电路的性能, 并阅读静态时序分析的报告, 了解目标电路能运行的最大频率.

目前我们不要求你了解报告中的所有细节, 我们会在B阶段介绍更多STA的内容. 如果你现在对报告的细节感兴趣, 可以参考[这个教程](https://ieda.oscc.cc/tools/ieda-tools/ista.html), 或者在上网查询时序报告的阅读教程. 其他工具也可以生成时序报告, 虽然格式可能有所不同, 但其中的大部分概念是相通的.

#### 评估过程中遇到问题

如果在运行时遇到bug，可到`yosys-sta`仓库的Issue中报告问题，并提供如下信息：

- 相应的RTL设计
- sdc文件
- yosys生成的网表文件
- iEDA的版本号, 可通过命令`echo exit | ./bin/iEDA -v`获取

事实上, 上述方式得到的时序报告并不能完全反映芯片流片时的频率. 这是因为, 网表中只包含标准单元及其拓扑信息, 并未包含标准单元的物理位置信息. 可以想象, 如果两个标准单元在物理位置上距离较远, 在它们之间传输的信号也需要经过一定的延迟才能到达, 这种延迟称为线延迟(net delay). 而标准单元库中标准单元的延迟属性, 只能反映出信号经过标准单元本身的延迟, 这种延迟称为逻辑延迟(logic delay). 完整的延迟信息应该由逻辑延迟和线延迟共同构成. 也就是说, 上述评估方式得到的频率, 只是基于逻辑延迟得到的. 只有等到EDA工具完成布局布线工作后, 才能获取准确的线延迟信息, 从而评估出更接近流片场景的频率信息.

那么, 当前得到的频率信息, 是否毫无意义呢? 并不是. 一方面, 开展物理设计工作也需要一定的时间, 对于复杂的高性能处理器, 甚至需要数天时间才能完成一轮物理设计工作. 显然, 为了获得更准确的延迟和频率信息, 设计团队需要付出更多时间, 这会影响项目迭代的效率. 另一方面, 逻辑延迟虽然不能代表最终的延迟信息, 但它已经给出了频率的上限, 同时也已经能反映出RTL逻辑设计阶段的某些问题, 如电路逻辑过于复杂. 这些信息已经足够帮助RTL设计者对RTL设计进行初步评估, 从而进行快速迭代优化. 我们将在B阶段进一步介绍优化的方法.

特别地, 对于处理器来说, 频率并不是衡量其性能的唯一因素. 频率的另一种理解是每秒工作了多少个周期, 但不一定每个周期都有"实质性的工作". 处理器的本分工作是执行程序, 因此对于处理器来说, 性能应该解读为"执行程序的效率". 更具体地, 处理器执行的是程序中的指令, 如果处理器的频率很高, 但要过很久才执行一条指令, 那么整体上来看也算不上一个优秀的处理器. 因此, 还需要通过另一个指标来衡量处理器执行指令的效率, 这个常用的指标称为IPC(Instruction Per Cycle), 它用来衡量处理器每周期执行的平均指令数. 我们将在B阶段进一步讨论IPC的测量和优化方法.

### 功耗评估

要评估电路的功耗, 就是要评估电路中所有标准单元的功耗之和. EDA工具需要从标准单元库中读出标准单元的功耗信息, 计算出每个标准单元的功耗, 从而计算出电路的总功耗. 和延迟的评估类似, 上文的`cell.lib`只是一个简单的实例, 其中未包含功耗信息, 因此无法用于功耗分析.

同样地, ICsprout55中的标准单元库已经提供了完整的标准单元功耗信息. 在`yosys-sta`项目中执行`make sta`命令, 除了可以评估RTL设计的性能, 也能评估其功耗: iSTA将快速评估并报告RTL设计中每个标准单元的功耗和总功耗.

#### 评估电路的功耗

尝试通过`yosys-sta`项目评估电路的性能, 并阅读功耗分析的报告, 了解目标电路的功耗信息.

功耗报告中报告了三类功耗, 其中:

- `Internal Power`是内部功耗. 在晶体管翻转时, 由于nMOS和pMOS并非瞬间就完成状态切换, 因此在一段很短的时间内, nMOS和pMOS会同时处于导通状态, 导致形成了从电源端到地端的短路电流, 这部分电流所产生的功耗就是内部功耗, 也称短路功耗. 内部功耗属于动态功耗(dynamic power)的一部分.
- `Switch Power`是翻转功耗. CMOS电路翻转时, 为了完成从`0`到`1`或从`1`到`0`的变化, 需要对相应的等效电容进行充电或放电, 这个过程产生的功耗就是翻转功耗, 也称开关功耗. 翻转功耗也属于动态功耗的一部分, 也即, 动态功耗由内部功耗和翻转功耗两部分组成.
- `Leakage Power`是漏电功耗. 在理想情况下, 晶体管处于截止状态时, 源极和漏极之间没有任何电流通过. 但实际上并非如此, 真正的晶体管会因为多种原因, 导致在源极和漏极之间存在一定的微小电流, 称为漏电电流(leakage current). 由漏电电流形成的功耗就是漏电功耗. 由于漏电功耗在晶体管不翻转时也会存在, 因此也称为静态功耗.

特别地, 在目前的报告中, 翻转功耗都是`0`. 这是因为评估翻转功耗需要先计算出相应的等效电容, 而等效电容不仅和标准单元本身有关, 也和走线的拓扑和长度相关. 进一步地, 要得到走线的拓扑和长度, 需要先完成后端物理设计的一系列步骤. `yosys-sta`没有开展这些步骤, 因此无法计算出等效电容, 从而无法评估翻转功耗. 我们会在B阶段介绍更多功耗相关的内容.

#### 开源EDA工具的局限性

当然, `yosys-sta`这一评估项目也不是完美的, 因为yosys的综合质量不高, 和商业综合器相比还存在一定的差距. 不过, 在综合后时序评估这一场景中, 上述缺陷不会造成明显的影响. 即使yosys的综合质量不高, 我们也可以通过综合结果的相对提升, 来指导RTL优化的方向.

#### 所以学习"一生一芯"还需要FPGA吗?

基本上不需要了:

- 从准确度来说, yosys的综合流程是面向ASIC设计的, 其原理和报告的准确度都更适合"一生一芯"; 而FPGA流程的原理与ASIC不同, 无法替代ASIC流程, 即使FPGA流程正确, 规范的ASIC流程仍然需要进行网表的功能仿真和时序仿真.
- 从时间来说, FPGA的主要作用是仿真加速, 也就是说, 如果仿真任务并不需要花费很长时间来完成, 使用FPGA的优势并不明显. 事实上, 从两者的完整流程来看, 当以下不等式成立时, FPGA的优势才能体现出来:其中, 通常达到小时量级, 而通常能在数分钟内完成, 因此, 只有当达到小时量级, 上述不等式才有可能成立. 不过在"一生一芯"的学习中, 你很难遇到需要小时量级的时间才能完成的仿真任务. 而当你遇到这样的任务时, 我们也会对FPGA的评估过程提出更高的要求. 我们会在B阶段中继续讨论这个问题.
- 从调试难度来说, FPGA的调试手段很有限, 只能在时间和空间均受限的条件下抓取底层的波形信息; 相反, 软件仿真则灵活很多, 我们可以借助很多软件方法来从多方面提升调试的效率.

## PDK和标准单元库

我们刚才提到的`cell.lib`只是一个标准单元库的简单示例. 现在我们来介绍ICsprout55这个PDK. 你对流水灯项目进行综合的时候, 已经接触过ICsprout55了. 具体地, 你可以在`yosys-sta/result`目录下找到综合后的网表文件, 网表文件中实例化的都是ICsprout55的标准单元.

### PDK的内容

如上文所述, PDK包含了特定工艺节点下的器件模型, 设计规则, 工艺约束, 验证文件和标准单元库等一系列资源. 而标准单元库是标准单元及其属性的集合, 这些属性包括逻辑功能, 晶体管结构, 时序, 功耗, 物理尺寸等信息. 通常, 这些信息分布在PDK的多种文件格式中, 上文提到的`.lib`文件只是其中一种. 以ICsprout55为例, 其中的文件包括(部分文件未列出):

```
.
├── IP
│   ├── IO        # IO库
│   └── STD_cell  # 标准单元库
│       └── ics55_LLSC_H7C_V1p10C100   # 版本号
│           ├── ics55_LLSC_H7CL        # LVT标准单元
│           │   ├── cdl
│           │   │   └── ics55_LLSC_H7CL.cdl        # 标准单元的晶体管级信息
│           │   ├── cell_list
│           │   │   └── ics55_LLSC_H7CL.txt        # 标准单元的名称列表
│           │   ├── doc                            # 标准单元的文档
│           │   ├── lef
│           │   │   └── ics55_LLSC_H7CL.lef        # 标准单元的物理几何信息
│           │   ├── liberty
│           │   │   └── ics55_LLSC_H7CL_typ_tt_1p2_25_nldm.lib   # 标准单元的逻辑功能
│           │   │                                                # 和PPA等信息
│           │   └── verilog
│           │       └── ics55_LLSC_H7CL.v          # 标准单元的verilog行为仿真模型
│           └── ics55_LLSC_H7CR
└── prtech
    └── techLEF
        └── N551P6M.lef    # 工艺相关的设计规范
```

上述文件都是文本文件, 可以直接使用文本编辑器打开并阅读.

可以看到, ICsprout55当前开放的标准单元库名称为`ics55_LLSC_H7C_V1p10C100`. 其中, `ics55`是ICsprout55的简写, `LLSC`含义为`Low Leakage Standard Cell`, `H7`表示标准单元的高度为7个轨道, `C`表示大版本号(之前还有大版本`A`和`B`), `V1p10C100`表示具体的小版本.

在处理器设计的全流程中, 不同的设计阶段会使用不同的文件. 例如, 综合的工艺映射阶段会读入`.lib`文件, 根据标准单元的逻辑功能, 将逻辑上功能等价的子电路映射到相应的标准单元; 进行网表仿真时会读入`.v`文件, 让RTL仿真器进行标准单元级别的仿真, 从而验证综合后的网表功能符合预期; 布局时需要读入`.lef`文件, 根据标准单元的尺寸等信息决定每个标准单元的位置.

### 工艺视角的芯片结构

为了方便大家理解PDK中的信息以及后续的物理设计阶段, 我们需要先从工艺视角了解芯片的结构. 在半导体制造中, 芯片的物理结构是分层次的. 例如, 某工艺的芯片侧视图如下图所示:

```
---------------------   M7    ------ 电源
  | | | | | | | | |
---------------------   M6    ------ 时钟
  | | | | | | | | |
---------------------   M5    --+
  | | | | | | | | |             |
---------------------   M4      |
  | | | | | | | | |             +--- 标准单元间的连接
---------------------   M3      |
  | | | | | | | | |             |
---------------------   M2    --+
  | | | | | | | | |
---------------------   M1    ------ 晶体管间的连接
  | | | | | | | | | <------- 通孔
=====================  多晶硅  --+
+++++++++++++++++++++  绝缘层    +--- 晶体管
ooooooooooooooooooooo  硅衬底  --+
```

其中, 最底层是硅衬底(silicon substrate), 包含晶体管的源极和漏极; 其上是绝缘层(dielectric), 也称栅氧层, 通常使用二氧化硅作为材料; 再上方是多晶硅层(poly-silicon), 作为晶体管的栅极. 这三层用于实现晶体管的物理结构.

在多晶硅层上方还有多个金属层(metal), 利用其导电性质实现信号的传输, 从而连接不同的晶体管, 实现不同门电路或标准单元的功能. 连接方式有层内连接和跨层连接两种, 前者在同一个金属层内进行走线, 后者通过不同金属层之间的通孔(via)进行连接. 在RTL逻辑设计中各个元件之间的连接关系, 在物理上最终是通过金属层提供的连接功能实现的.

为了区分不同的金属层, 通常对它们进行编号, 编号越大, 层数越高. 不同金属层对其中的走线宽度和距离有不同的要求, 从而充当不同的作用, 如下表所示. 需要补充的是, 根据中学的物理知识, 走线的电阻与横截面积成反比.

| 金属层 | 线宽 | 走线间距 | 走线特性 | 作用 |
| --- | --- | --- | --- | --- |
| 低层 | 小 | 小 | 电阻大, 传输距离短, 布线密度高 | 连接不同的晶体管, 从而构成门电路和标准单元 |
| 中层 | 中 | 中 | 电阻中, 传输距离中等, 布线密度中 | 连接不同的标准单元, 实现芯片的主要逻辑 |
| 高层 | 大 | 大 | 电阻小, 传输距离长, 布线密度低 | 电源 |

对于不同的制造工艺, 其金属层数量可能不同. 例如, 上图的工艺结构简称为`1P7M`, 其中`P`表示`Poly`, 即多晶硅层; `M`表示`Metal`, 即金属层; 因此`1P7M`表示1层多晶硅层和7层金属层. 在`1P7M`中, `M1`为低层金属层, `M2`-`M6`为中层金属层, `M7`为高层金属层. 可见, 在`1P7M`中, 有5层中层金属层专门用于实现标准单元之间的连接.

在连接不同标准单元的信号中, 时钟信号和数据信号有所不同. 由于时钟信号需要连接大量的触发器, 其传输距离比一般的数据信号要长, 因此通常采用更大的线宽(例如数据信号线宽的2倍), 后端工程师会在EDA工具中指定线宽的参数. 同时, 后端工程师也会指定采用哪一层金属层来实现时钟信号. 理论上来说, 任何一层中层金属层都可以, 但习惯上会选择高层金属层的下面一层来实现时钟信号(如上例中的`M6`).

通常, 先进工艺会提供更多的金属层, 如`1P9M`, `1P11M`等, 它们能提供更丰富的空间用于进行标准单元之间的连接, 但在制造过程中需要用到更多的金属层掩膜(mask), 因此制造成本也更高.

金属层的属性记录在PDK的工艺LEF文件中. LEF文件以`.lef`为后缀, 采用`Library Exchange Format`格式, 它以文本方式描述了相应工艺的金属层, 通孔, 布局规则等物理层信息.

```
vim yosys-sta/pdk/icsprout55/prtech/techLEF/N551P6M.lef
```

例如, 你可以看到`LAYER MET1`的定义, 相关字段描述了第1层金属层的属性.

```
LAYER MET1
  TYPE ROUTING ;
  DIRECTION HORIZONTAL ;
  PITCH 0.2 0.2 ;
  WIDTH 0.09 ;
  OFFSET 0.1 0.1 ;
  AREA 0.042 ;
  SPACING 0.09 ;
  MAXWIDTH 10 ;
  MINENCLOSEDAREA 0.18 ;
  CAPACITANCE CPERSQDIST 0.0007630 ;
  EDGECAPACITANCE 0.0000339 ;
  RESISTANCE RPERSQ 0.1122 ;
  DCCURRENTDENSITY AVERAGE 1.5 ;
END MET1
```

其中, `TYPE`字段为`ROUTING`, 表示该层用于布线; `WIDTH`字段和`PITCH`字段分别以为单位给出了该层的最小线宽和最小走线间距, 具体如下图所示. 如果你想了解LEF文件的更多信息, 可以查阅[相关手册](https://www.ispd.cc/contests/18/lefdefref.pdf).

```
 WIDTH
   |
 <-+->
|     |                          |     |
|     |                          |     |
|     |                          |     |
|     |                          |     |
|wire |                          |     |
|     |                          |     |
|     |                          |     |
|     |                          |     |
|     |                          |     |
|     |                          |     |
|     |           PITCH          |     |
|     |             |            |     |
|     |             |            |     |
|     |             |            |     |
   |<---------------+-------------->|
```

在金属层的定义之前, 你应该还能看到多晶硅层`LAYER POLY`的定义, 但其中只有一个`TYPE`字段, 没有其他字段. 这是因为多晶硅层连同绝缘层和硅衬底共同用于实现晶体管, 而晶体管的参数由工艺决定, 这对后端物理设计过程来说是相对固定的, 并不像金属层那样可以让EDA工具根据设计需求进行动态布线. 因此, 在LEF文件中只需要声明其存在即可, 更多工艺细节记录在其他文件(如GDS)中. 类似地, 绝缘层和硅衬底从功能上与多晶硅层紧密绑定, 甚至不需要在LEF文件中出现.

#### 了解ICsprout55的金属层

阅读ICsprout55的工艺LEF文件, 其中包含多少层金属层? 并尝试根据线宽和走线间距, 推测每层金属层的作用.

如果处理器的规模复杂(如乱序超标量的高性能处理器), 标准单元之间则会存在较多连线, 使得布线阶段的压力较大, 走线就需要迂回. 这不仅增加了芯片的面积, 还增加了线延迟, 降低了芯片的频率. 还可能会因为过分拥堵而使得布线失败, 从而无法制造出功能正确的芯片. 因此, 高性能处理器的设计通常选择金属层多的工艺, 通过更丰富的布线空间来缓解布线阶段的压力. 例如, 香山处理器团队在设计过程中尝试将工艺从`1P9M`切换到`1P11M`, 无需改动RTL代码, 即可降低线延迟, 提升处理器的主频.

#### 多个多晶硅层的工艺

并非所有工艺都只有1层多晶硅层, 根据不同的应用场景, 可能会采用更多多晶硅层的工艺. 例如, 闪存(flash存储器)的存储单元采用浮栅晶体管, 是一种包含两个栅极的特殊晶体管. 其中一个称为浮栅(floating gate), 分"存储电荷"(充电)和"未存储电荷"(放电)两种状态, 分别表示`0`和`1`; 另一个称为控制栅(control gate), 用于控制存储单元的读写. 闪存采用`2P8M`的制造工艺来实现这种特殊的晶体管, 其中包含的两个多晶硅层分别用于实现浮栅和控制栅.

### 标准单元的属性

PDK提供的标准单元库通常包含很多标准单元. 为了方便得知标准单元的属性, 标准单元的命名通常会遵循一定的规范. 在ICsprout55中, 标准单元的命名遵循`功能+驱动能力+H+轨道数+阈值电压`的命名方式. 例如, `NAND2X1H7L`表示该标准单元的功能为二输入的与非门, 驱动能力为`X1`, 即1倍标准驱动能力, 其高度为7个轨道, 阈值电压为LVT; `OR3X0P5H7R`表示该标准单元的功能为三输入的或门, 驱动能力为`X0P5`, 即0.5倍标准驱动能力(`P`表示小数点), 其高度为7个轨道, 阈值电压为RVT. 接下来, 我们以`NAND2X1H7L`为例, 查阅标准单元库中的相关文件, 来进一步了解标准单元的各种属性.

#### LIB文件 - 功能, 时序和功耗

LIB文件以`.lib`为后缀, 采用`Liberty Timing File`格式, 它以文本方式描述了标准单元的功能, 以及在某种条件下的时序和功耗等属性.

```
cd yosys-sta/pdk/icsprout55/IP/STD_cell/ics55_LLSC_H7C_V1p10C100/
vim ics55_LLSC_H7CL/liberty/ics55_LLSC_H7CL_typ_tt_1p2_25_nldm.lib
```

简单查阅后发现, LIB文件由一些头部字段和若干个标准单元(cell)的描述组成. 例如, 我们可以直接搜索`NAND2X1H7L`来查阅这个标准单元的相关属性.

```
  cell (NAND2X1H7L) {
    area : 1.12;
    cell_footprint : "NAND2X1H7L";
    cell_leakage_power : 0.434974;
    pg_pin (VDD) {
      pg_type : primary_power;
      voltage_name : "VDD";
    }
    pg_pin (VSS) {
      pg_type : primary_ground;
      voltage_name : "VSS";
    }
    leakage_power () {
      value : 0.312371;
      when : "(A * B * !Y)";
      related_pg_pin : VDD;
    }
    leakage_power () {
      value : 0;
      when : "(A * B * !Y)";
      related_pg_pin : VSS;
    }
    leakage_power () {
      value : 0.82883;
      when : "(A * !B * Y)";
      related_pg_pin : VDD;
    }
    leakage_power () {
      value : 0;
      when : "(A * !B * Y)";
      related_pg_pin : VSS;
    }
    leakage_power () {
      value : 0.565379;
      when : "(!A * B * Y)";
      related_pg_pin : VDD;
    }
    leakage_power () {
      value : 0;
      when : "(!A * B * Y)";
      related_pg_pin : VSS;
    }
    leakage_power () {
      value : 0.0333159;
      when : "(!A * !B * Y)";
      related_pg_pin : VDD;
    }
    leakage_power () {
      value : 0;
      when : "(!A * !B * Y)";
      related_pg_pin : VSS;
    }
    leakage_power () {
      value : 0.434974;
      related_pg_pin : VDD;
    }
    leakage_power () {
      value : 0;
      related_pg_pin : VSS;
    }
    pin (Y) {
      direction : output;
      function : "(!A) + (!B)";
      output_voltage : default_VDD_VSS_output;
      power_down_function : "(!VDD) + (VSS)";
      related_ground_pin : VSS;
      related_power_pin : VDD;
      max_capacitance : 0.055;
      timing () { ......  }
      timing () { ......  }
      internal_power () { ...... }
      internal_power () { ...... }
      internal_power () { ...... }
      internal_power () { ...... }
    }
    pin (A) {
      direction : input;
      driver_waveform_fall : "PreDriver20.5:fall";
      driver_waveform_rise : "PreDriver20.5:rise";
      input_voltage : default_VDD_VSS_input;
      related_ground_pin : VSS;
      related_power_pin : VDD;
      max_transition : 0.795659;
      capacitance : 0.000898206;
      rise_capacitance : 0.000898206;
      rise_capacitance_range (0.000705173, 0.000898206);
      fall_capacitance : 0.000888785;
      fall_capacitance_range (0.000696354, 0.000888785);
      internal_power () { ...... }
      internal_power () { ...... }
    }
    pin (B) {
      direction : input;
      driver_waveform_fall : "PreDriver20.5:fall";
      driver_waveform_rise : "PreDriver20.5:rise";
      input_voltage : default_VDD_VSS_input;
      related_ground_pin : VSS;
      related_power_pin : VDD;
      max_transition : 0.795659;
      capacitance : 0.000953054;
      rise_capacitance : 0.000953054;
      rise_capacitance_range (0.000589512, 0.000953054);
      fall_capacitance : 0.000952783;
      fall_capacitance_range (0.000588209, 0.000952783);
      internal_power () { ...... }
      internal_power () { ...... }
    }
  }
```

目前为止, 我们能看懂的属性包括(一些属性的单位在头部字段处定义):

- 面积(area), 一般以为单位
- 漏电功耗(leakage power), 该属性包含标准单元在各种情况下的漏电功耗
- 内部功耗(internal power), 该属性包含标准单元在各种情况下的内部功耗
- 端口(pin), 包括方向(direction), 电容(capacitance)等; 特别地, 对于输出端口, 还包含以下信息
  - 功能(function), 通过逻辑表达式给出, 可从该属性了解该标准单元的功能
  - 时序(timing), 包含标准单元在各种情况下的延迟

我们对面积属性的含义稍加说明. 芯片是一个三维物体, 芯片中的标准单元也存在于三维空间中. 为了方便描述, 我们假设将芯片水平放置, 并建立一个三维坐标系. 标准单元的面积是指标准单元在平面中投影的面积, 也即俯视图中的面积. 考虑芯片的工艺结构, 标准单元的面积也是其在多晶硅层和低层金属层中所占的面积.

从上述属性可以看到, LIB文件主要用于综合, 时序分析和功耗分析. 例如, yosys在进行工艺映射时会读入LIB文件, 并根据标准单元`function`字段, 决定将哪些子电路映射为何种标准单元, 从而保证网表所描述的电路逻辑与输入RTL代码等价; iSTA工具会根据标准单元的`timing`字段, 计算出各种情况下的每个标准单元的逻辑延迟, 最后报告网表的若干条最长路径.

#### RTFM

上述LIB文件有上百万行, 不方便直接查阅. 我们推荐你查阅相关的标准单元数据手册, 手册位于`yosys-sta/pdk/icsprout55/IP/STD_cell/ics55_LLSC_H7C_V1p10C100/ics55_LLSC_H7CL/doc/ics55_LLSC_H7CL_TYPICAL_V1P2_T25.pdf`.

如果想了解LIB文件中各个字段的具体含义, 可以查阅[`Liberty Timing File`的文件格式手册](https://media.c3d2.de/mgoblin_media/media_entries/659/Liberty_User_Guides_and_Reference_Manual_Suite_Version_2017.06.pdf).

#### Verilog文件 - 行为模型

为了验证综合后的网表与综合前的RTL设计等价, 一种方式是进行网表仿真, 即结合标准单元的行为, 对网表进行仿真. 虽然LIB文件中标准单元的`function`字段也描述了标准单元的行为, 但RTL仿真器通常无法识别LIB文件. 因此, 标准单元库通常还提供标准单元的Verilog行为模型.

在ICsprout55中, 标准单元的Verilog行为模型位于如下文件:

```
cd yosys-sta/pdk/icsprout55/IP/STD_cell/ics55_LLSC_H7C_V1p10C100/
vim ics55_LLSC_H7CL/verilog/ics55_LLSC_H7CL.v
```

例如, `NAND2X1H7L`的行为模型如下:

```
module NAND2X1H7L (Y, A, B);
output Y;
input A, B;

  nand (Y, A, B);

endmodule //NAND2X1H7L
```

可以看到, 这只不过是用Verilog语言将标准单元的功能实现了一遍, 这里用Verilog语言的内建原语`nand`来实现二输入与非门的功能. 将网表文件连同这个行为模型文件一同输入到RTL仿真器中, RTL仿真器将会按照模型文件中的模块定义对网表文件中的标准单元进行实例化, 从而开展网表层次的仿真工作.

ICsprout55提供的行为模型不仅可以用于进行功能仿真, 还包含丰富的时序信息(由`specify`语句给出), 可以支持用户开展网表层次的时序仿真工作.

#### LEF文件 - 物理几何信息

上文已经介绍了和工艺相关的LEF文件, 事实上还有一种和标准单元相关的LEF文件, 用于描述标准单元的物理几何信息.

```
cd yosys-sta/pdk/icsprout55/IP/STD_cell/ics55_LLSC_H7C_V1p10C100/
vim ics55_LLSC_H7CL/lef/ics55_LLSC_H7CL.lef
```

以`NAND2X1H7L`为例, LEF文件对其描述如下:

```
MACRO NAND2X1H7L
  CLASS CORE ;
  ORIGIN 0 0 ;
  FOREIGN NAND2X1H7L 0 0 ;
  SIZE 0.8 BY 1.4 ;
  SYMMETRY X Y ;
  SITE core7 ;
  PIN A
    DIRECTION INPUT ;
    USE SIGNAL ;
    PORT
      LAYER MET1 ;
        RECT 0.055 0.425 0.23 0.59 ;
    END
  END A
  ......
END NAND2X1H7L
```

其中, `SYMMETRY X Y`表示标准单元可以沿轴或沿轴对称放置, 从而优化布局的效果(如到某端口的线延迟等); `PIN`字段用于描述指定引脚的一些属性, 包括方向(`DIRECTION`)和端口的几何形状(`PORT`)等. 其中的`PORT`又描述了端口需要在`MET1`层占用一个矩形, 形状通过`RECT`字段给出.

`SITE`给出了标准单元在放置时需要对齐的规则, 此处字段的值`core7`表示引用了另一处的对齐规则, 具体位于工艺LEF文件中:

```
SITE core7
    SIZE 0.200 BY 1.400 ;
    CLASS CORE ;
    SYMMETRY Y  ;
END core7
```

这里的`SYMMETRY Y`含义表示标准单元可以沿轴对称放置; `SIZE 0.200 BY 1.400`给出了对齐规则为`0.2 X 1.4`, 也即摆放标准单元时, 轴坐标必须为`0.2`的整数倍, 轴坐标必须为`1.4`的整数倍. 回过头来看`NAND2X1H7L`的`SIZE`字段, 它给出了标准单元的尺寸. 可以看到, `SIZE`字段在轴上的长度`0.8`和在轴上的长度`1.4`, 都分别是对齐规则中`0.2`和`1.4`的整数倍. 更一般地, 可以认为`SITE`定义了一个网格单元, 所有标准单元从尺寸上来看, 都是由一个或多个网格单元组成的矩形.

可以看到, LEF文件详细地描述了标准单元的几何外形信息. 这些信息将会帮助EDA工具将标准单元正确地摆放在芯片中.

#### CDL文件 - 晶体管结构描述

CDL文件以`.cdl`为后缀, 它其实是一种电路描述语言(Circuit Description Language), 以文本方式描述了标准单元的晶体管结构.

```
cd yosys-sta/pdk/icsprout55/IP/STD_cell/ics55_LLSC_H7C_V1p10C100/
vim ics55_LLSC_H7CL/cdl/ics55_LLSC_H7CL.cdl
```

CDL文件中对晶体管结构的描述格式如下:

```
.SUBCKT 子电路名称 端口1 端口2 ...
晶体管实例名称 漏极 栅极 源极 衬底 晶体管类型 沟道宽度 沟道长度
...
.ENDS
```

以`NAND2X1H7L`为例, CDL文件对其描述如下:

```
.SUBCKT NAND2X1H7L A B VDD VSS Y
*.PININFO A:I B:I Y:O VDD:B VSS:B
MMN0 Y B net6 VSS nm1p2_lvt_lp W=210n L=60n m=1
MMN1 net6 A VSS VSS nm1p2_lvt_lp W=210n L=60n m=1
MMP1 Y B VDD VDD pm1p2_lvt_lp W=270n L=60n m=1
MMP0 Y A VDD VDD pm1p2_lvt_lp W=270n L=60n m=1
.ENDS
```

其中, 以`*`开头的行是注释. 上述描述通过`.SUBCKT`定义了一个名为`NAND2X1H7L`的子电路(即标准单元), 有5个端口, 依次为`A`, `B`, `VDD`, `VSS`和`Y`. 以`MMN0`开头的行实例化了一个名为`MMN0`的nMOS晶体管, 其漏极和端口`Y`相连, 栅极和端口`B`相连, 源极和线网`net6`相连, 衬底和端口`VSS`相连, 采用的晶体管类型为`nm1p2_lvt_lp`, 沟道的宽度和长度分别为和. 上述例子的剩余内容通过类似方式描述剩余的晶体管及其连接关系.

#### 根据CDL文件画出晶体管结构

尝试根据上述CDL描述, 画出标准单元`NAND2X1H7L`的晶体管结构, 并检查其功能与与非门是否一致.

CDL中描述的晶体管结构信息主要用于进行晶体管层次的SPICE仿真, 以及用于检查GDS版图与网表逻辑的一致性, 后者的工作称为LVS(Layout Versus Schematic).

#### GDS文件 - 物理版图

GDS文件以`.gds`为后缀, 它包含了制造某标准单元的所需的所有物理和工艺信息. GDS文件并非文本文件, 需要专门的工具来解析读取. ICsprout55的GDS文件暂未开放, 不过"一生一芯"对GDS文件中的具体内容不作要求, 故此处不展开介绍.

### 标准单元的分类

标准单元库中的标准单元种类繁多, 可以根据功能对其进行分类, 包括但不限于如下类别. 通常来说, 前5类单元和时钟缓存器是必须的, 从而保证能正确实现各种设计的基本功能. 通过提供其他类型的单元, 用户可以针对指定的场景设计出更优的电路, 或实现更方便的芯片调试功能.

#### 逻辑门单元

逻辑门单元包括基本逻辑门(与门, 或门, 非门等)和复杂逻辑门.

#### 理解复杂逻辑门单元的功能

ICsprout55的LIB文件中还存在命名类似`OAI22X1H7L`的标准单元, 其功能并不直观. 尝试查阅标准单元`OAI22X1H7L`相关的属性, 了解其功能.

查阅ICsprout55的LIB文件后可发现, `OAI22X1H7L`这个标准单元的功能比单一的逻辑门更复杂. 根据德摩根定律, 可以对`OAI22X1H7L`输出端口的逻辑表达式进行转换:

```
(!A0 * !A1) + (!B0 * !B1) = !(A0 + A1) + !(B0 + B1) = !((A0 + A1) * (B0 + B1))
```

此处`+`表示或运算, `*`表示与运算, `!`表示非运算. 可以看到, 这个标准单元的功能包含两个二输入或门, 一个二输入与门和一个非门. 这种逻辑门称为复杂门(complex gate). 如果查阅相关标准单元的面积, 可以得到如下数据:

```
area(OAI22X1H7L) = 1.96
area(OR2X1H7L)*2 + area(AND2X1H7L) + area(INVX1H7L) = 1.68*2 + 1.68 + 0.84 = 5.88
```

可以看到, `OAI22X1H7L`这个标准单元的面积, 比采用功能等价的多个逻辑门单元所花费的面积要小得多, 这是因为, 通过晶体管之间的串联和并联来实现"与"和"或"的逻辑功能, 比通过"与门"和"或门"来实现相应的逻辑功能, 代价要低很多. 这里的代价不仅仅体现在面积上, 还体现在延迟和功耗上. 因此, 标准单元库并非只包含简单逻辑门单元, 对于类似`OAI22X1H7L`这种在晶体管层次实现的复杂逻辑门, 也作为标准单元提供, 从而让芯片具备更好的PPA.

#### 理解OAI22的晶体管结构

在CDL文件中查阅`OAI22X1H7L`的晶体管结构, 它有多少根晶体管? 尝试理解如何通过其晶体管结构实现`OAI22X1H7L`的逻辑表达式.

#### OAI22的命名

事实上, `OAI22`的命名是有其含义的, 其中`OAI`表示`Or-And-Invert`, `22`表示两组输入信号, 每组各两个. 不妨假设输入信号分别为`A0, A1, B0, B1`, 那么, `OAI`表示首先对每组信号内部进行`Or`运算, 得到`A0 | A1`和`B0 | B1`; 再对结果进行`And`运算, 得到`(A0 | A1) & (B0 | B1)`; 最后对结果进行`Invert`运算, 得到`!((A0 | A1) & (B0 | B1))`.

#### 理解复杂逻辑门单元的功能(2)

类似地, 有一个标准单元的命名为`AOI221`, 尝试根据命名列出其逻辑表达式, 并查阅标准单元库中的功能, 对比你的理解是否正确.

标准单元中包含的类似`X1`, `X4`等后缀, 表示这个标准单元的驱动能力(drive strength). 驱动能力是指标准单元在维持指定电压范围时能驱动或吸收的电流, 它会影响下游标准单元翻转所需的时间. 因此, `NAND2X1H7L`, `NAND2X2H7L`和`NAND2X4H7L`在逻辑功能上是完全等价的, 但`NAND2X4H7L`能提供更大的驱动能力, 能使其下游逻辑翻转得更快, 不过这需要更大或更多的晶体管来实现, 因此`NAND2X4H7L`具有更大的面积, 其功耗也更高.

#### 理解驱动能力

尝试查阅`NAND2X1H7L`, `NAND2X2H7L`和`NAND2X4H7L`的相关属性, 对比其面积和功耗.

#### 理解驱动能力(2)

尝试查阅`NAND2X2H7L`的晶体管结构, 和`NAND2X1H7L`相比, 有何不同?

考虑到不同驱动能力在性能, 面积, 功耗等指标上的权衡, 通常在影响频率的关键路径上使用驱动能力较高的标准单元, 从而降低关键路径的延迟, 提升芯片的频率; 在不影响频率的非关键路径上使用驱动能力较低的标准单元, 从而在不降低芯片频率的情况下, 降低芯片整体的面积和功耗.

#### 时序单元

时序单元包括触发器, 锁存器等, 其中又包含有/无清零端/置位端等各种类型, 如触发器`DFFX1H7L`等.

#### 根据CDL文件画出晶体管结构(2)

在CDL文件中查阅`DFFX1H7L`的晶体管结构. 其中`TSINV`为三态反相器, 其晶体管结构可参考`.SUBCKT TSINV`子电路的结构. 根据CDL文件的描述画出`DFFX1H7L`的晶体管结构. 这个标准单元由多少个晶体管组成? 并尝试理解如何通过该晶体管结构实现触发器的功能.

#### I/O单元

芯片需要通过I/O单元(输入输出单元)来与外界进行通信. I/O单元用于将芯片内部的I/O信号和金属压焊块(pad)连接起来, 在芯片生产后, 封装工序会从I/O单元的金属压焊块中引出金属引脚, 从而允许芯片外部的信号通过引脚与芯片内部的I/O信号进行交互.

ICsprout55的I/O单元可以参考相关LIB文件:

```
cd yosys-sta/pdk/icsprout55/IP/IO/ICsprout_55LLULP1233_IO_251013/
vim liberty/ICSIOA_N55_3P3_tt_1p2_3p3_25c.lib
```

其中, I/O单元可继续分类如下:

1. 数据I/O单元(也称GPIO), 用于提供数据信号的输入输出, 如`P65_1233_PBMUX`.
2. 核心电源单元, 用于为芯片内部的晶体管提供电源, 包括源极的电源(VSS)和漏极的电源(VDD), 如`P65_1233_VSS1`和`P65_1233_VDD1`.
3. I/O电源单元, 用于为数据I/O单元(即第1类I/O单元)提供电源, 如`P65_1233_VSSIO3`和`P65_1233_VDDIO3`. 数据I/O单元通常比一般的标准单元要复杂, 因此其供电需求也不同于一般的标准单元, 故不能使用核心电源单元(即第2类I/O单元)为数据I/O单元供电.

虽然I/O单元也是标准单元库中的一部分, 但它们的面积比一般的标准单元要大几个数量级. 这是因为, 与芯片外界通信对I/O单元的功能提出了更多需求, 例如需要具备很强的驱动能力来向芯片外部输送信号, 需要集成保护电路来防止外部的静电对芯片内部造成损害, 需要符合芯片引脚的物理尺寸和焊接要求(如间距, 金属层厚度, 保留空白区域避免短路)等. 因此, I/O单元的电路层实现要比一般的标准单元复杂得多.

#### 了解I/O单元的尺寸

尝试查阅ICsprout55中的相关文件, 了解一个二输入与非门的尺寸以及一个I/O单元的尺寸, 并对比它们.

#### 驱动单元

驱动单元用于增强信号的驱动能力, 保证信号完整性, 优化时序和负载. 当信号传输距离过长或下游电路过多(高扇出)时, 信号可能会因为驱动能力不足而导致传输延迟过高, 甚至使得信号失真从而导致错误. 插入驱动单元有助于缓解上述问题. 具体分为:

- 逻辑正向驱动单元, 又称缓冲器(buffer), 其输出在逻辑上和输入完全相同. 在ICsprout55中, 这种驱动单元包括`BUFX1H7L`, `BUFX2H7L`, `BUFX4H7L`等, `X`后的数字最大, 单元的驱动能力越强.
- 逻辑反向驱动单元, 又称反相器(inverter), 其功能和非门相同, 同样也存在多种驱动能力.

#### 物理单元

物理单元本身没有逻辑功能, 主要用于解决后端物理设计中与电路逻辑功能无关的特定问题. 一些常见的物理单元包括:

- 上拉/下拉单元. 这类单元没有输入, 只有输出, 分别提供`逻辑0`(低电平)和`逻辑1`(高电平)的功能. 在ICsprout55中, 上拉单元和下拉单元分别是`TIELOH7L`和`TIEHIH7L`.
- 填充单元(filler). 用于填充芯片中的空白区域, 保证某些层(如电源层)的连续性, 避免制造过程导致的缺陷. 在ICsprout55中, 填充单元包括`FILLER1H7L`, `FILLER2H7L`等.
- 去耦单元(decap). 用于避免电路中大量单元同时翻转引起的动态电压降对电路的影响. 在ICsprout55中, 去耦单元包括`FILLCAP4H7L`, `FILLCAP8H7L`等.
- 天线效应修复单元. 在芯片制造过程的离子刻蚀步骤中, 在一定条件下会引发电路上的天线效应, 这种效应会击穿晶体管, 使其失效. 在合适的位置添加这种标准单元可以消除天线效应, 从而保证芯片的正确性. 在ICsprout55中, 天线效应修复单元包括`ANT2H7L`和`ANT4H7L`.

#### 宏单元

宏单元是一种具有特定功能的, 被厂商(晶圆厂或IP厂商)预先设计好其物理实现的, 面积较大的标准单元, 例如SRAM存储器, DDR phy模块等. SRAM存储器是一类常见的宏单元, 在处理器设计中经常使用. ICsprout55目前暂未开放相关的宏单元.

#### 复杂功能单元

复杂功能单元包括多路选择器, 半加器, 全加器, 比较器等. 相比于用逻辑门搭建出功能等价的电路, 以标准单元提供这些功能可以实现更优的PPA. 在ICsprout55中, 复杂功能单元包括`MUX2X1H7L`, `MUXI2X1H7L`, `ADDHX1H7L`, `ADDFX1H7L`等.

#### 复杂单元的全定制电路

以`ADDHX1H7L`为例, 尝试从标准单元库的相关文件中找到这个标准单元的面积和晶体管结构. 假设某标准单元库不提供半加器的标准单元, 需要通过若干基本逻辑门的标准单元来搭建半加器, 请计算此时所需的面积和晶体管数量.

#### 时钟专用单元

时钟专用单元专门用于处理时钟信号的单元, 包括时钟缓冲器, 时钟门控(clock gating)单元, 用于处理时钟信号的逻辑门单元等. 之所以不能用一般的标准单元(如与门, 缓冲器等)来处理时钟信号, 是因为时钟信号的特殊性:

- 时钟信号的细微变化可能会导致触发器无法正确工作, 例如, 时钟信号因抖动产生的毛刺可能会被触发器误认为时钟边沿的到来.
- 时钟信号的延迟会影响触发器的时序, 进而影响整个电路的工作频率.
- 电路中的触发器都需要接入时钟, 因此时钟信号的扇出非常大, 传输距离也很远, 需要很强的驱动能力. 根据上文对芯片内部结构的介绍, 时钟信号通常会采用更大的线宽.

因此, 和一般的标准单元相比, 标准单元库的设计者需要对时钟专用单元进行针对性设计, 使其具备低抖动, 低延迟, 高驱动能力等特性.

在ICsprout55中, 时钟专用单元包括`ICGX1H7L`, `ICGNX1H7L`等.

#### 电源管理单元

电源管理单元用于实现低功耗设计, 包括电源门控(power gating)单元, 隔离单元等. ICsprout55目前暂未开放此类单元.

#### 测试调试单元

测试调试单元用于支持芯片制造后的测试和调试, 包括扫描链(scan chain)单元, 内建自测试(Built-In Self Test, BIST)控制单元等.

扫描链单元通常用于可测试性设计(Design for Testability, DFT), 它们在一般触发器的基础上, 添加了扫描使能端`SE`(scan enable)和扫描输入端`SI`(scan input). 当`SE`有效时, 用`SI`来更新触发器. 因此, 开发者可以通过外部的控制将特定状态注入到这种触发器中, 从而帮助开发者对制造后的芯片进行调试. 不过, 和一般的触发器相比, 扫描链单元的面积更大, 功耗也更高.

在ICsprout55中, 测试调试单元包括`SDFFX1H7L`, `SDFFSX1H7L`, `SDFFRX1H7L`等.

#### 了解的所有标准单元

尝试结合PDK的相关文件, 进一步了解ICsprout55提供的标准单元. 你可以查看相应的注释和功能属性了解相关标准单元的作用. 了解后, 你将会对你的RTL代码如何被综合器处理有一个简单的认识.

### PVT角

电路的延迟主要受三个因素的影响: 工艺(Process), 电压(Voltage)和温度(Temperature). 三者统称PVT参数. 后端工程师一般会选取多个PVT参数的组合作为一系列环境, 并在设计阶段尽可能保证芯片将来能在这些环境下工作. 这些环境称为PVT角(PVT corner).

在标准单元库中, 不同的PVT角体现为不同的LIB文件. 在这些LIB文件中, 标准单元的名称和面积都相同, 但延迟和功耗不同. 通过采用不同的LIB文件进行评估, 后端工程师可以了解芯片能否在对应PVT角下按预期工作.

工艺波动是指芯片制造过程中不可控的扰动因素. 例如, 晶圆中心的芯片所处的环境与晶圆边界的芯片有所不同, 晶体管金属层的厚度并非完全均匀, 晶体管衬底的掺杂浓度不均匀, 等等. 这些因素都会影响晶体管的电阻和电容, 最终影响晶体管的延迟表现: 可能会变快, 也可能会变慢.

为了测试电路在各种晶体管延迟下都能正确工作, 一般会根据晶体管的工作速度定义若干情况, 这些情况称为工艺角(process corner). 工艺角通常用两个字母来命名, 第一个字母表示nMOS的工作速度, 第二个字母表示pMOS的工作速度. 工作速度分成三种情况: 典型(typical, 用字母`t`表示), 快速(fast, 用字母`f`表示)和慢速(slow, 用字母`s`表示). 其中, 快速和慢速都是相对与典型情况而言的. 因此, 根据晶体管的极性和工作速度, 可以组合出五种工艺角: `ss`, `tt`, `ff`, `sf`和`fs`. 例如, `fs`表示nMOS工作得比典型情况快, 但pMOS工作得比典型情况慢的延迟情况.

```
     pMOS
      ^
      |     sf            ff
 fast +    o-------------o
      |    |             |
      |    |       tt    |
      |    |      o      |
      |    |             |
      |    |ss           |fs
 slow +    o-------------o
      |
      +----+-------------+---> nMOS
          slow          fast
```

#### tt算一个"角"吗?

在一个坐标轴中, 如果用X轴代表nMOS的工作速度, 用Y轴代表pMOS的工作速度, 那么`ss`, `ff`, `sf`和`fs`将分别落在一个矩形的四个角, 这也是"工艺角"的由来. 而`tt`其实落在矩形的中心, 严格来说它并不是一个"角". 但作为典型情况, 后端工程师还是会把它归到"工艺角"的概念中.

在上述五种工艺角中, 对于`ss`, `tt`和`ff`来说, nMOS和pMOS的工作速度基本保持一致, 因此对晶体管整体的功能没有太大影响, 只不过会影响其延迟. 但对于`sf`和`fs`来说, 由于nMOS和pMOS的工作速度一个变快而另一个变慢, 从而使得CMOS整体从`0`变成`1`与从`1`变成`0`时的延迟有所不同, 为了保证各种电路元件能正确工作, 元件延迟参数的确定需要更加谨慎. 不过在实际的制造过程中, 由于工艺波动也有一定的随机性, 要使得芯片中nMOS和pMOS的工作速度恰好往相反方向变化, 概率是非常低的. 因此, 后端工程师通常不会考虑`sf`和`fs`这两个工艺角, ICsprout55中也不提供`sf`和`fs`对应的LIB文件.

#### 工艺角和Intel处理器型号

由于工艺波动的存在, 同一批次的芯片可能会有不同的性能表现. Intel正好利用了这一点, 将同一批次中属于不同工艺角的芯片划分到不同层次的型号中进行销售. 例如, 在Intel Core系列中, 大部分性能表现属于`tt`工艺角的芯片以i5的型号进行销售; 少部分属于`ff`工艺角的芯片能运行在更高的频率, 以价格更高的i7型号进行销售, 以赚取更多利润; 而剩下属于`ss`工艺角的芯片只能运行在比`tt`更低的频率, 则以价格更低的i3型号进行销售, 避免将其作为废片丢弃.

在芯片的工作环境中, 电压也并非恒定不变. 例如, 电流通过电源网络会根据其电阻形成电压降, 使得不同位置上的标准单元的输入电压并不完全相同: 靠近电源I/O单元的标准单元能获得较强的输入电压, 晶体管的工作速度较快; 而远离电源I/O单元的标准单元由于电压降的存在, 相对而言它们获得的输入电压较低, 晶体管的工作速度也相对较慢. 此外, 电源也可能会存在白噪声, 即使是对同一个位置的标准单元而言, 晶体管的工作速度也会随时间而波动. 为了应对电压的波动, 后端工程师一般需要保证电路在标准工作电压 的区间(即)内能正确工作.

温度也会影响晶体管的工作速度. 一方面是外部环境温度的影响, 有的芯片在工厂车间的高温环境中工作, 有的芯片在南北极的低温环境中工作. 另一方面, 即使外部环境相同, 芯片中不同位置的晶体管也会受到不同温度的影响: 在晶体管密度高或者晶体管翻转频率高的区域, 产生的热量也高. 相对于常温而言, 温度升高会使晶体管的工作速度变慢. 这是因为, 根据热力学效应, 粒子在高温状态下具有更高的能量, 因此半导体材料中的原子会在晶格中加剧振动. 受这种振动的影响, 晶体管沟道中电子移动的方向会被改变, 从而使得电流降低, 进一步使得晶体管的工作速度下降. 因此, 为了提升芯片的健壮性, 不同温度下的工作情况都需要考虑.

LIB文件的命名中通常会包含PVT角的信息, 例如, `ss_1p08_125`表示工艺角为`ss`, 电压为`1.08V`, 温度为`125`摄氏度; `ff_1p32_m40`表示工艺角为`ff`, 电压为`1.32V`, 温度为`-40`摄氏度. 在集成电路领域, 类似`1p08`这种用`p`(表示`point`)替代小数点`.`的命名方式很常见. 一方面, 一些早期的文件系统或EDA工具不支持文件名中包含小数点; 另一方面, 在书写密集的技术文档或字体很小的板卡上, `1p60`的视觉区分效果比`1.60`更好, 尤其是小数点很容易看漏. 用字母`m`(表示`minus`)替代负号`-`也是出于相似的考虑. 此外, 不同厂商采用的命名规范可能有所不同, 包括用单位(如字母`v`)替代小数点(如用`1v08`表示`1.08V`), 用字母`n`(表示`negative`)替代负号(如用`n40`表示`-40`摄氏度)等.

#### 尝试不同PVT角的评估结果

ICsprout55提供了不同PVT角的LIB文件(位于`yosys-sta/pdk/ICsprout55IP/STD_cell/ics55_LLSC_H7C_V1p10C100/ics55_LLSC_H7CL/liberty`目录下). 尝试为`yosys-sta`项目更换不同PVT角的LIB文件(在`yosys-sta/scripts/pdk/icsprout55.tcl`中指定), 然后重新评估电路的性能, 对比不同PVT角下的评估结果.

由于PVT角描述的是标准单元在不同环境下的工作情况, 因此, 同一个标准单元在不同的PVT角下, 其内部结构和几何形状是完全一样的, 因此只需要在不同的LIB文件中不同PVT角的时序信息和功耗信息. 用EDA工具在某个PVT角下评估一款芯片, 其实是回答"如果芯片将来在这个PVT角所描述的环境中工作, 其表现如何"的问题. 而芯片的实测表现与其真实的工作环境相关, 如果实际工作环境和设计芯片时采用的PVT角不一致, 则EDA工具报告的信息并不能完全代表芯片实测的表现.

#### PVT角和超频

某发烧友群体采用水冷甚至液氮等技术对处理器进行超频, 成功让计算机稳定地运行在更高的工作频率. 尝试从PVT角的角度分析为什么采用这些技术后可以成功超频.

#### 厂商的营销策略

一些厂商可能会利用PVT角与实际工作环境的差异来进行营销. 例如, 某厂商在芯片设计阶段采用`ff_1p32_m40`这个PVT角, EDA工具报告芯片最高可运行在2GHz的频率, 厂商便宣称其芯片频率达到2GHz. 但用户购买该厂商的芯片或搭载该芯片的相关产品后, 发现芯片最高只能运行在1.5GHz.

一方面, 用户是在常温(约`25`摄氏度)环境下使用芯片产品, 并不是`-40`摄氏度; 另一方面, 在一批芯片中, 工艺波动处于典型情况的芯片占大多数, 大部分用户购买到的都是这部分芯片, 而工艺波动落在`ff`范围内的芯片则是占少数. 如果厂商在设计阶段采用`tt_1p2_25`这个PVT角, EDA工具报告的数据将更接近用户实际使用的情况.

因此, 如果厂商广告中的频率不是实测数据, 还需要关注相关数据是在哪个PTV角下评估得到的, 从而对将来芯片的工作情况进行更加客观的估计.

### 阈值电压

回顾晶体管的工作原理, 栅极电压与源极电压之间的差值必须达到某个阈值, 晶体管才能导通, 否则晶体管截止. 对于不同阈值的晶体管, 其电气属性有所不同, 因此用不同阈值的晶体管搭建的标准单元, 其特性也有所不同.

不同阈值电压的标准单元主要用于在延迟和静态功耗之间取得权衡. 具体地, 对于阈值电压较高的标准单元, 需要花费更多时间才能让晶体管从截止状态变成导通状态, 因此延迟较高. 而对于静态功耗, 如上文所述, 它主要由漏电电流产生. 在目前的CMOS技术中, 漏电电流中占比最多的部分是亚阈值电流(sub-threshold current). 之所以存在亚阈值电流, 是因为晶体管从导通状态转换为截止状态时, 并非瞬间就进入完美的截止状态, 而是进入了"亚阈值"状态. 在这种状态下, 栅极附近仍然存在微弱的电场, 在其作用下仍然会吸引少量电子. 这些电子虽然不足以形成沟道连通源极和漏极, 但它们仍然会产生从漏极到源极的微小电流, 这就是亚阈值电流. 如果其他因子不变, 亚阈值电流和阈值电压之间存在如下关系:

其中和是两个与无关的因子. 由于亚阈值电流在漏电电流中占比较大, 因此静态功耗可近似看成:

其中, 为电源电压. 可以看到, 阈值电压越高, 漏电电流越低, 静态功耗也越低. 相反, 当阈值电压降低时, 静态功耗却呈指数增长.

不过, 对于逻辑功能相同但阈值电压不同的标准单元, 其面积通常相同. 这是因为不同阈值电压是通过调整晶体管本身的参数来实现的, 如衬底的参杂浓度, 栅极绝缘层的厚度等, 这些参数的调整并不影响标准单元中晶体管的尺寸和排布, 因此不会影响标准单元的面积.

通常将标准单元按阈值电压分如下几类: HVT(High Voltage Threshold), RVT(Regular Voltage Threshold), LVT(Low Voltage Threshold)和ULVT(Ultra-Low Voltage Threshold). 其中, HVT的阈值电压最高, 其静态功耗最低, 但延迟最高; ULVT则相反, 其阈值电压最低, 延迟也最低, 但静态功耗最高. 有一些厂商将RVT称为SVT(Standard Voltage Threshold). 有一些工艺节点还提供UHVT(Ultra-High Voltage Threshold)的标准单元供用户选择. ICsprout55提供了HVT, RVT和LVT三种不同阈值电压的标准单元.

#### 尝试不同的阈值电压

todo

后端工程师需要根据芯片的应用场景, 选择合适阈值电压的标准单元来设计芯片. 例如, 在低功耗应用场景中, 偏向选择HVT; 在高性能应用场景中, 偏向选择LVT甚至ULVT. 在两个目标都追求的场合, 可以选择混合设计方式, 即在影响频率的关键路径上使用LVT或ULVT, 从而降低关键路径的延迟, 提升芯片的频率; 在不影响频率的非关键路径上使用RVT或HVT, 从而在不降低芯片频率的情况下, 降低芯片整体的静态功耗. 例如, 根据[体系结构领域国际顶级会议MICRO上发表的"香山"论文](https://ieeexplore.ieee.org/abstract/document/9923860), 第一代"香山"处理器芯片中不同电压阈值的标准单元的比例为: ULVT 1.04%, LVT 19.32%, SVT 25.19%, HVT 53.67%.

### 轨道数

轨道(track)数是标准单元的其中一个属性, 它是标准单元高度的另一种衡量. 这里的"高度"(height)并不是指标准单元在三维空间中轴方向投影的度量, 而是在轴方向投影的度量; 相应地, 标准单元在轴方向投影的度量称为"宽度"(width). 因此, 后端设计在尺寸描述上的术语, 和几何度量概念的使用习惯有所不同, 后端设计中的"宽度", "高度"和"厚度", 分别对应三维几何空间中的"长度", "宽度"和"高度".

我们已经知道, 金属层的`PITCH`属性描述了该层的最小走线间距. 为了方便EDA工具开展布局布线工作, 通常会让标准单元的高度取`PITCH`属性的整数倍, 这个倍数就是标准单元的轨道数. 金属层有很多, 但标准单元一定会使用M1金属层, 因此通常用M1金属层的`PITCH`属性作为轨道数计算的参考.

在一种标准单元库中, 标准单元的高度通常是相同的, 从而进一步方便EDA工具开展布局工作. 因此, 也可以从轨道数的角度来描述不同标准单元库的标准单元. 例如, 某标准单元库的标准单元轨道数为6, 则称为"6T标准单元".

#### 理解ICsprout55的轨道数

上文在介绍ICsprout55时已经提到过其轨道数. 尝试在相关文件中找到需要的参数, 计算ICsprout55标准单元的轨道数, 检查计算所得的轨道数是否与上文所介绍的轨道数一致.

轨道数较少的标准单元(如6T, 7T), 其面积较小, 功耗较低, 但驱动能力较弱, 使得晶体管翻转时间较长, 故性能不高; 相反, 轨道数较多的标准单元(如12T, 13T), 则具备较高的性能, 但面积较大, 功耗也较高; 也有轨道数处于两者之间的标准单元(如9T, 10T), 它们在性能，面积和功耗等指标上相对平衡.

有的PDK会提供不同轨道数的多种标准单元库. 后端工程师需要根据芯片的应用场景, 选择合适轨道数的标准单元来设计芯片. 不过在选定标准单元库后, 电路中无法混合使用不同轨道数的标准单元. 这和阈值电压不同, 因为一个标准单元库中也可以包含多种阈值电压的标准单元, 它们可以混合使用. 事实上, ICsprout55还提供了9T的标准单元库, 但目前暂未开放.

## 物理设计(Physical Design) - 从网表到可流片版图

物理设计是指将网表中记录的标准单元及其连接关系映射到真实芯片三维空间的过程. 具体地, 负责物理设计的EDA工具需要确定好每个标准单元在芯片中的坐标, 还需要确定走线的走向, 使得走线可以按照网表中的连接关系, 将位于不同坐标的标准单元连接起来, 从而实现和网表逻辑一致的功能. 记录标准单元的坐标以及走线走向的文件, 就是上文提到的GDS版图文件. 最后, EDA工具还需要评估得到的芯片是否能被正确地制造, 芯片的指标是否满足预期等.

理解芯片的工艺结构之后, 你就可以理解物理设计的本质了. 物理设计的过程就是确定每一层中的内容: 每一层应该选取多大的面积(布图规划), 在低层的什么位置摆放什么标准单元(布图规划, 布局), 如何在中层连接这些标准单元(布线), 如何规划时钟(时钟树综合), 以及如何在高层规划电源(电源规划). 下面我们逐一介绍这些阶段需要开展哪些工作.

```
---------------------   M7    <----- 电源规划
  | | | | | | | | |
---------------------   M6    <----- 时钟树综合
  | | | | | | | | |
---------------------   M5    <-+
  | | | | | | | | |             |
---------------------   M4      |
  | | | | | | | | |             +--- 布线
---------------------   M3      |
  | | | | | | | | |             |
---------------------   M2    <-+
  | | | | | | | | |
---------------------   M1    <-+
  | | | | | | | | |             +--- 布图规划, 布局
=====================  多晶硅 <-+
+++++++++++++++++++++  绝缘层
ooooooooooooooooooooo  硅衬底
```

由于物理设计涉及真正的电路, 因此物理设计工程师需要理解电子领域的相关知识才能很好地胜任相关工作. 不过在"一生一芯"中, 你只需要大致了解从网表转换为可流片版图都经历了哪些步骤, 从而帮助你在将来理解逻辑设计(即RTL设计)和物理设计之间有哪些相互影响之处, 你不必深入了解甚至记忆物理设计过程中的所有细节.

### 布图规划(Floorplan)

布图规划的主要任务是确定芯片的大小, 并且摆放一些在后续流程中不会调整位置的单元. 布图规划的工作主要包括以下内容.

#### 确定芯片大小

与标准单元的面积类似, 芯片大小(die size)是指芯片在平面中投影的面积, 也即芯片俯视图所得矩形的面积, 同时也是芯片中每一层金属层的面积, 故也称芯片面积. 芯片的厚度(即轴方向的度量)和选取的工艺相关, 如上文提到的`1P7M`. 一般来说, 选定一种工艺后, 芯片的厚度并非一个可以调整的参数, 因此物理设计阶段通常不关心芯片的厚度.

根据芯片的工艺结构, 芯片面积主要由晶体管的面积和走线的面积构成. 晶体管的面积主要包括硅衬底的源极和漏极所占的面积, 加上多晶硅层的栅极所占的面积. 不过, 标准单元库会给出每个标准单元所占用的面积, 因此用户或EDA工具无需考虑晶体管层次的尺寸. 而走线分垂直方向(即轴方向)和水平方向两种, 前者会经过金属层之间的通孔, 在平面的投影为一个点; 后者在金属层内部延伸, 在平面的投影为一条线. 表面上看这两种情况都不占用面积, 但根据工艺制造的要求, 通孔之间以及走线之间都存在最小间距, 否则将会发生信号干扰甚至短路, 因此实际上走线也会占用一定的面积.

由于此时还没有开展布线工作, 因此无法得到走线所占的具体面积. 在布图规划阶段, 一般是通过综合所得的面积报告(即标准单元所占总面积)来估算芯片大小. 估算时, 工程师需要考虑标准单元总面积占芯片总面积的预期比例, 这个比例称为利用率(utilization). 根据经验, 利用率一般在60%~80%左右. 例如, 假设某芯片综合后, 其标准单元总面积约, 某工程师预期能做到70%的利用率, 那么在布图规划阶段, 可以估算芯片大小为.

利用率的选取需要在成本和设计难度之间进行权衡. 如果利用率较高, 说明留给布线阶段的空间较小, 布线阶段就容易发生拥堵而进行长距离走线, 从而增加了线延迟, 使得芯片频率下降, 甚至可能因为过分拥堵而失败, 无法完成物理设计; 如果利用率较低, 则芯片中空余的面积较大, 造成浪费, 而芯片的制造费用一般和面积成正比, 从而引入不必要的成本开销.

工程师需要根据芯片属性和自身经验来选择目标利用率: 对于小芯片, 其拓扑较简单, 布局布线相对容易成功, 因此可以设置较高的利用率; 而复杂的大芯片则不宜设置过高的利用率, 需要为布线阶段预留足够的空间. 有经验的工程师可以设置更高的利用率, 而新手在前期可以从低利用率开始积累经验. 在大型项目中, 工程师一般会开展多轮的物理设计, 根据前一轮的设计结果(过度拥挤或剩余面积过多)来调整后一轮的参数, 从而不断优化物理设计的结果, 在不引入过多成本的情况下实现预期的性能目标.

#### 确定芯片尺寸

确定大致面积后, 还需要考虑芯片的尺寸, 即芯片在轴和轴两个方向上的度量. 影响尺寸的因素除了标准单元的综合面积, 还需要考虑芯片引脚的数量. 引脚数量的影响又与封装方案有关. 一种常见的封装方案是QFP(Quad Flat Package，四侧引脚扁平封装), 这种方案的引脚会分布在芯片的四周, 因此芯片尺寸会与引脚数量成正比.

```
         |    |    |
    +----+----+----+----+
    |                   |
 ---+                   +---
    |                   |
 ---+                   +---
    |                   |
 ---+                   +---
    |                   |
    +----+----+----+----+
         |    |    |
```

一个芯片引脚需要对应一个I/O单元, 因此芯片引脚数量对芯片尺寸的影响, 其实是通过I/O单元的尺寸反映出来的. 一方面, 如上文所述, I/O单元的尺寸比一般的标准单元要大好几个数量级. 另一方面, 由于部分I/O单元需要承担供电的任务, 无法用于通信, 因此实际需要规划的引脚总数要多于用于通信的引脚. 供电引脚的比例和分布密度与芯片的尺寸, 工艺, 功耗等属性有关, 工艺相关的手册会给出推荐的供电引脚排布方案. 但通常来说, 尺寸越大, 功耗越高, 需要的供电量也越大, 供电引脚的数量也更多.

例如, 某芯片需要90个引脚进行通信, 假设需要1/3的引脚用于供电, 则实际需要个引脚, 故应选择144脚这种常见的封装方案. 如果让引脚在四周均匀分布, 则每条边大约需要放置个引脚. 假设该芯片采用ICsprout55工艺进行设计, 一个I/O单元的尺寸为. 假设该工艺允许I/O单元之间可以紧挨着排布, 那么芯片的一条边长为, 芯片的最小面积为. 也即, 即使按照利用率估算出芯片大小为, 考虑引脚和封装方案后, 仍然需要规划的芯片面积. 有的工艺要求I/O单元之间预留一定的间隙, 这时芯片的边长将会更长, 最小面积也会更大.

#### 芯片的形状必须是正方形吗?

正方形的对称性可以减轻后续某些工作的负担, 如电源规划, 时钟树综合等, 这些工作要求从源点到所有目标点的距离不能相差过大. 但实际上, 芯片的边长可以不相同. 只要能放置所需要的I/O单元, 成功进行物理设计(如布线成功), 并且芯片满足厂商指定的制造约束, 并且封装方案可实施, 芯片都是可以投片生产的.

因此, 芯片引脚数量作为一种资源, 需要在项目前期的规格定义阶段就明确其需求. 同时, 我们也可以通过引脚数量快速估计芯片的最小面积. 例如, 某芯片只需要28个引脚进行通信, 按照同样的供电引脚比例进行计算, 可采用44脚的封装方案. 在ICsprout55工艺下, 芯片的最小面积为.

另一个可能会影响芯片尺寸的因素是特殊的宏单元. 由于宏单元已经被预先设计好, 其形状是固定的. 为了摆放某些特殊的宏单元, 需要芯片的尺寸满足一定的要求. 例如, 有一些DDR phy模块需要摆放在芯片的I/O边界上, 并且形状是L型的, 这就要求芯片长边必须长于L型形状的长边, 否则这个DDR phy模块将无法摆放.

综合上述条件可以初步确定芯片的尺寸, 其俯视图如下图所示.

```
+-----------------------------------------+
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
|                                         |
+-----------------------------------------+
```

#### 摆放I/O单元

确定好芯片的尺寸后, 接下来就可以在芯片四周摆放I/O单元了. 一般I/O单元的摆放会遵循以下做法:

- 将功能相近的顶层端口对应的数据I/O单元摆放在物理上相邻的位置. 数据I/O单元在逻辑上对应整个设计的顶层端口, 它会通过走线连接到芯片内部的标准单元. 因此, 这种摆放方式有利于降低布线阶段中的线延迟(如下图的`A`和`B`两个端口). 否则, 若将功能相近的端口摆放在芯片的两侧甚至对角, 必定有其中一端需要经过较长的走线才能到达目标标准单元.

```
         |    |    |                         |    |    |
    +----+----+----+----+               +----+----+----+----+
    |                   |               |                   |
A---+--+                +---        A---+--+                +---
    |  o                |               |  o                |
B---+--+                +---         ---+  +                +---
    |                   |               |  |                |
 ---+                   +---         ---+  +----------------+---B
    |                   |               |                   |
    +----+----+----+----+               +----+----+----+----+
         |    |    |                         |    |    |
```

- 根据工艺手册中对供电引脚密度的要求, 摆放相应的核心电源单元和I/O电源单元. 例如, 某工艺可能会要求每隔两个数据I/O单元就要放置一个电源单元.

```
+-----------------------------------------+
|  I  I  P  p  I  I  P  p  I  I  P  p  I  |
|                                         |
|p                                       I|
|                                         |
|P                                       P|
|                                         |          I 数据I/O单元
|I                                       p|          p 核心电源单元
|                                         |          P I/O电源单元
|I                                       I|
|                                         |
|I                                       I|
|                                         |
|p                                       p|
|                                         |
|P                                       P|
|                                         |
|  I  p  P  I  I  p  P  I  I  p  P  I  I  |
+-----------------------------------------+
```

#### 摆放宏单元

还有一项工作是摆放宏单元. 宏单元占用的面积比一般的标准单元大得多. 例如, 一个`64x64`的SRAM, 仅考虑存储单元, 就需要根晶体管, 而一个二输入与非门的标准单元只需要4根晶体管. 因此, 宏单元需要提前摆放, 否则在摆放标准单元后, 将很难空出连续的大面积来摆放宏单元.

```
+-----------------------------------------+
|  I  I  P  p  I  I  P  p  I  I  P  p  I  |
|                                         |
|p                                       I|
|    +-------+                            |
|P   | MMMMM |                           P|
|    | MMMMM |                            |          I 数据I/O单元
|I   | MMMMM |                           p|          p 核心电源单元
|    +-------+                            |          P I/O电源单元
|I                                       I|          M 宏单元
|                            +-------+    |
|I                           | MMMMM |   I|
|                            +-------+    |
|p                                       p|
|                                         |
|P                                       P|
|                                         |
|  I  p  P  I  I  p  P  I  I  p  P  I  I  |
+-----------------------------------------+
```

和I/O单元的摆放类似, 宏单元的摆放也需要参考它们的功能, 来将功能相近的宏单元摆放在物理上相邻的位置, 从而避免在布线阶段产生较长的走线, 进而影响芯片的频率.

### 电源规划(Powerplan)

电源规划的目标是在芯片层面规划电源走线的分布, 从而保证芯片供电的可靠性. 电源规划的工作主要包括:

1. 规划I/O单元的电源环(Power Ring). 从物理分布上来看, I/O单元的电源环围绕芯片四周的I/O单元, 并与I/O单元的电源端口相连, 由I/O单元中的I/O电源单元进行供电. 上文提到, 为了驱动芯片外部的电路, I/O单元需要很强的驱动能力, 因此I/O单元的供电与一般标准单元的供电也不同, 需要单独规划和设计.
2. 规划核心电源环. 物理分布上和I/O单元的电源环类似, 但位于I/O单元的内侧并围绕芯片四周, 形成电源网络的主干, 由I/O单元中的核心电源单元供电, 向芯片内部的标准单元提供均匀的供电输入.
3. 规划芯片内部的电源条线(power stripe). 从物理分布上来看, 电源条线以纵横交错的方式分布在芯片内部, 用于将电源均匀地输送到芯片内部的各种宏单元和标准单元. 在布局阶段, 这些电源条线将会连接标准单元中门电路的源极和漏极.

考虑到简洁性, 下图只展示了一条电源条线作为示意, 实际上应规划纵横交错的多条电源条线.

```
+-----------------------------------------+
|  I  I  P  p  I  I  P  p  I  I  P  p  I  |
| ####################################### |
|p#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#I|
| #% +-------+                         %# |
|P#% | MMMMM |                         %#P|
| #% | MMMMM |                         %# |          I 数据I/O单元
|I#% | MMMMM |                         %#p|          p 核心电源单元
| #% +-------+                         %# |          P I/O电源单元
|I#%                                   %#I|          M 宏单元
| #%                         +-------+ %# |          # I/O电源环
|I#%                         | MMMMM | %#I|          % 核心电源环
| #%                         +-------+ %# |          = 电源条线
|p#%===================================%#p|
| #%                                   %# |
|P#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#P|
| ####################################### |
|  I  p  P  I  I  p  P  I  I  p  P  I  I  |
+-----------------------------------------+
```

将来芯片工作时, 电源通过供电引脚输入芯片, 通过电源环传播到芯片的四周, 并通过电源条线传播到芯片各区域的标准单元, 对晶体管的源极和漏极施加相应电压, 从而使其按照晶体管的电气特性进行工作.

一些复杂的芯片还需要支持电源管理相关的功能, 如多电压域, 电源门控等. 这些功能也需要在此阶段开展相关的规划工作.

### 布局(Placement)

布局的目标是将标准单元摆放在芯片中, 确定每个标准单元在芯片中的物理位置. 但标准单元的摆放并非任意均可, 需要遵循一定的规则:

1. 标准单元之间不能互相重叠. 虽然芯片是一个三维物体, 但根据芯片的工艺结构, 标准单元是通过底层的晶体管和低层金属层的连接实现的, 不同标准单元的晶体管应该占用这些层次的不同位置. 也即, 所有标准单元的轴坐标分量都是相同的. 因此从平面的投影(即芯片的俯视图)来看, 标准单元之间不能相互重叠.
2. 标准单元的摆放需要满足一定的对齐条件. 上文提到了标准单元的SITE和轨道数等属性, 它们本质上都是用于约束标准单元在布局时的位置. 按SITE对齐可以让电源规划阶段所设置的电源条线轻松地接入到标准单元中(如下图所示), 而轨道数的概念可以让后续的布线阶段较轻松地满足金属层走线的最小间距要求(即`PITCH`属性). 如果不对标准单元的摆放满足对齐要求, EDA工具将需要花费很大的代价来生成一个满足工艺要求的设计方案.

```
        --- +------+  +------------+----------+    +---+
         ^  |======|==|============|==========|====|===| <- VSS power stripe
         |  |      |  |            |          |    |   |
height --+  |      |  |            |          |    |   |
         |  |      |  |            |          |    |   |
         v  |======|==|============|==========|====|===| <- VDD power stripe
        --- +------+  +------------+----------+    +---+
               OR2        AOI221       AND4        NAND2
```

```
+-----------------------------------------+
|  I  I  P  p  I  I  P  p  I  I  P  p  I  |
| ####################################### |
|p#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#I|
| #% +-------+  @@  @@  @           @ @%# |
|P#% | MMMMM |   @      @@@      @@  @@%#P|
| #% | MMMMM |  @    @                @%# |          I 数据I/O单元
|I#% | MMMMM |                @        %#p|          p 核心电源单元
| #% +-------+   @   @@           @    %# |          P I/O电源单元
|I#%                                   %#I|          M 宏单元
| #% @   @   @   @@  @       +-------+ %# |          # I/O电源环
|I#% @    @  @   @   @   @   | MMMMM | %#I|          % 核心电源环
| #% @   @   @   @   @    @  +-------+@%# |          = 电源条线
|p#%===================================%#p|          @ 标准单元
| #% @   @       @   @    @     @     @%# |
|P#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#P|
| ####################################### |
|  I  p  P  I  I  p  P  I  I  p  P  I  I  |
+-----------------------------------------+
```

除了让标准单元的布局满足工艺制造要求之外, EDA工具还会考虑如何提升电路的质量. 一些措施包括但不限于:

- 将逻辑上相近的标准单元靠近摆放. 和上文提到的数据I/O单元的摆放类似, 如果逻辑上相近的两个标准单元距离很远, 在布线阶段将会引入较高的线延迟, 从而降低芯片的频率.
- 对标准单元进行镜像对称. 上文提到, LEF文件中的`SYMMETRY`属性表示标准单元可以沿轴或沿轴对称放置, 从而优化布局的效果(如到某端口的线延迟等). 例如, 某标准单元`A`左侧的端口`p`需要与位于`A`右侧的另一个标准单元`B`相连, 此时可以将`A`沿轴进行镜像对称, 使得端口`p`位于`A`的右侧, 从而让`p`与`B`的距离更近, 降低线延迟.
- 拥塞缓解. 标准单元过分集中在某区域, 可能会使得后续的布线工作变得困难, 不仅会造成走线迂回而引入较高的线延迟, 甚至有可能会因为过分拥塞而造成布线失败. 为了缓解拥塞, EDA工具可能会将过分集中的标准单元进行分散处理, 从而给布线阶段预留更多的空间.

#### 填充单元的尺寸

标准单元库通常提供不同尺寸的填充单元, 用于填充芯片中没有摆放标准单元的空白位置. 以ICsprout55为例, 尝试在相关文件中找到最小填充单元的尺寸, 这个尺寸和标准单元的`SITE`属性有什么关联? 为什么?

### 时钟树综合(CTS, Clock Tree Synthesis)

时钟树综合的目标是构建时钟网络, 将时钟信号输送到所有时序单元的时钟端. 这个时钟网络通常只有一个或少数几个源头(时钟引脚或锁相环的输出), 我们可以将这些源头看作根节点, 时序单元看作叶子节点, 这个时钟网络就像是从根节点向叶子节点生长的一棵或几颗树, 因此称为"时钟树".

在RTL设计阶段, 我们会认为时钟信号是理想的. 但实际上并非如此, 在物理设计阶段, 我们需要考虑实际时钟信号需要处理的问题. 上文介绍"时钟专用单元"时已经简单讨论了时钟信号的特殊性质, 因此, 构建的时钟树也应满足这些性质, 具体包括:

- 低延迟(low latency). 给时钟信号的传播引入延迟的因素有很多, 有一些是EDA工具可以优化的, 如时钟信号的走线, EDA工具应尽可能减少时钟源到触发器时钟端口的距离; 另一些是EDA工具无法优化的, 如时钟源本身的延迟, EDA工具应在建模时钟信号延迟时考虑这些因素.
- 低偏斜(low skew). 在RTL设计时, 我们会认为理想时钟的信号同时到达所有的触发器. 但实际上, 不同的触发器在布局阶段被放置在不同的位置, 同一个时钟信号到达不同触发器的所需时间并不完全相同, 这就产生了时钟偏斜的概念. 为了尽可能降低时钟偏斜, EDA工具需要仔细规划时钟信号的走线, 使得时钟源到各触发器的线延迟尽可能均匀.
- 低抖动(low jitter). 抖动是电信号在物理世界中天然存在的特性, 和具体的工艺参数有关, 无法通过EDA工具优化或消除. 因此EDA工具应在建模时钟信号延迟时考虑抖动的影响, 否则EDA工具对时钟信号延迟的估计可能会过于乐观, 将来芯片在真实场景下工作时, 真实的抖动可能会使得电路违反过于乐观的时序条件, 最终令芯片无法正确工作.
- 高驱动能力(high drive). 为了实现时钟信号的高驱动能力, 一般会在时钟树中插入专用的时钟缓冲器.

不过, 这些性质之间还存在一定的相互制约关系. 例如, 一些走线拓扑具有低偏斜的性质, 但其线延迟较高; 插入时钟缓冲器可以提高时钟信号的驱动能力, 但也会改变相应路径上的延迟, 从而可能让偏斜变得严重. 因此, EDA工具需要综合考虑这些技术对时钟树的影响, 从整体上构建出满足需求的时钟树.

考虑到简洁性, 下图只展示了时钟树的一部分作为示意, 实际上时钟树应连接到所有时序单元.

```
+-----------------------------------------+
|  I  I  P  p  I  I  P  p  I  I  P  p  I  |
| ####################################### |
|p#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#I|
| #% +-------+  @@o @@  @           @ @%# |
|P#% | MMMMM |   @o     @@@      @@ o@@%#P|
| #% | MMMMM |  @ o  @    o         o @%# |          I 数据I/O单元
|I#% | MMMMM |    o       o   @     o  %#p|          p 核心电源单元
| #% +-------+   @o  @@   o       @ o  %# |          P I/O电源单元
|I#% oooooooooooooooooooooooooooooooooo%#I|<-- clk   M 宏单元
| #% @   @   @   @@o @    o  +-------+ %# |          # I/O电源环
|I#% @    @  @   @ o @   @o  | MMMMM | %#I|          % 核心电源环
| #% @   @   @   @ o @    @  +-------+@%# |          = 电源条线
|p#%===================================%#p|          @ 标准单元
| #% @   @       @ o @    @     @   oo@%# |          o 时钟树
|P#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#P|
| ####################################### |
|  I  p  P  I  I  p  P  I  I  p  P  I  I  |
+-----------------------------------------+
```

### 布线(Routing)

布线的目标是根据网表的拓扑关系, 将布局阶段的标准单元通过走线连接起来. 作为大规模和超大规模集成电路, 标准单元的数量非常多, 标准单元之间的走线也很多, 只要有一条走线无法连通, 布线就会失败. 为了提升布线成功的概率, 一般将布线任务分成两个阶段进行: 全局布线(Global Routing)和详细布线(Detailed Routing).

以城市的道路规划为例, 全局布线就好比规划城市的主干道, 一方面要保证城市中不同地点之间的连通性, 另一方面不能让主干道过分迂回, 尽量以较短的距离实现连通, 最后还需要避免某些区域过分拥堵. 而详细布线就相当于在主干道上进一步划分真正的车道, 让车辆可以在车道上行驶, 从而到达由主干道连通的地点.

回到布线的场景, 全局布线的目标是规划粗粒度的走线方案, 并为这些粗粒度的走线方案分配布线资源, 包括轨道数量, 走线方向, 以及金属层之间的通孔等. 具体地, 布线工具在全局布线阶段会将多个轨道看成一个网格, 然后尝试通过网格把标准单元连接起来, 得到一些"网格路径"(类似道路规划中的主干道). 在全局布线的过程中, 布线工具会在保证连通性的同时, 寻找一套距离较短, 同时避免过分拥塞的"网格路径连通方案". 详细布线的目标是在全局布线的基础上, 在"网格路径"内部确定走线的轨道, 通过这些走线的轨道将标准单元真正地连接起来.

```
+-----------------------------------------+
|  I  I  P  p  I  I  P  p  I  I  P  p  I  |
| ####################################### |
|p#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#I|
| #% +-------+..@@o @@..@...   .....@.@%# |
|P#% | MMMMM |  .@o.....@@@..... @@ o@@%#P|
| #% | MMMMM |..@ o  @    o   .   . o @%# |          I 数据I/O单元
|I#% | MMMMM |  . o       o   @   . o .%#p|          p 核心电源单元
| #% +-------+  .@o  @@...o   ....@ o .%# |          P I/O电源单元
|I#% oooooooooooooooooooooooooooooooooo%#I|<-- clk   M 宏单元
| #% @ ..@...@ ..@@o @... o  +-------+.%# |          # I/O电源环
|I#% @....@ .@.. @ o @. .@o .| MMMMM |.%#I|          % 核心电源环
| #% @...@...@  .@ o @  ..@..+-------+@%# |          = 电源条线
|p#%===================================%#p|          @ 标准单元
| #% @...@      .@ o @... @.....@.. oo@%# |          o 时钟树
|P#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#P|          . 走线
| ####################################### |
|  I  p  P  I  I  p  P  I  I  p  P  I  I  |
+-----------------------------------------+
```

至此, 物理设计的工作已全部完成, 芯片中每一层的内容都已确定, 可以生成GDS版图文件, 来描述芯片中每一层的所有标准单元和走线

### 签核分析(Sign-off)

签核分析的目标是保证物理设计过程得到的版图是可生产的. 一方面, 需要保证版图满足前端设计的指标, 包括PPA等; 另一方面, 还需要保证版图满足晶圆厂的生产制造要求. 严格来说, 签核分析并不属于物理设计的范畴, 但为了保证版图是可流片的, 签核分析是不可或缺的, 否则生产得到的芯片将可能无法工作.

签核分析的具体工作包括但不限于:

- 静态时序分析. 物理设计工作完成后, 所有标准单元的在三维空间中的位置都已确定, 所有走线的方向, 长度和拐角等细节都已明了. 因此可以准确建模出电路中每一条路径的逻辑延迟和线延迟, 包括时钟信号的传播延迟, 抖动和偏斜. 综合这些因素, 得到更准确的时序评估结果, 从而确定是否满足用户指定的频率指标.
- 功耗分析. 和静态时序分析类似, 物理设计工作完成后, 可以得到更准确的功耗评估结果, 从而确定是否满足用户指定的功耗指标.
- 信号完整性分析. 分析相邻走线之间的串扰(crosstalk)现象, 确保信号在噪声环境和串扰条件下仍然能正确传输, 不失真.
- 物理验证(Physical Verification, 简称PV). 对芯片进行物理结构上的检查, 若发现违例, 则需要修改布局布线的结果, 重新进行检查. 物理验证的检查工作具体包括:
  - 设计规则检查(Design Rule Check, DRC). 保证GDS版图满足晶圆厂的设计规则, 包括了多晶硅层和各种金属层的检查规则, 如最小线宽要求, 最小间距要求等. 有的PDK会将这些规则以文本形式记录到文件中, EDA工具可以从文件中读取这些规则并逐条检查. 例如, 某PDK中的一些规则如下:

    ```
    # metal1层的最小线宽是65nm
    metal1.width(65.nm, euclidian).output("METAL1.1", "METAL1.1 : Minimum width of metal1 : 65nm")

    # via6层的最小间距是160nm
    via6.space(160.nm, euclidian).output("VIA6.2", "VIA6.2 : Minimum spacing of via6 : 160nm")
    ```
  - 电学规则检查(Electrical Rule Check, ERC). 检查电路中是否存在走线悬空, 短路等电气问题.
  - 版图和原理图比较(Layout Versus Schematic, LVS). 确认GDS版图(物理电路)与网表(逻辑电路)的一致性.

#### 从可流片的版图到可运行的芯片

从可流片的版图到可运行的芯片还需要经过以下步骤:

1. 后端设计团队将芯片的GDS版图提交给晶圆厂后, 晶圆厂将会按照版图制作出掩膜(mask),
2. 晶圆厂用掩膜批量生产出晶圆(wafer). 一个晶圆上有多个裸片(die), 晶圆厂对晶圆进行切割, 得到一批裸片.
3. 晶圆厂将裸片交给封装厂, 由封装厂按照计划的封装方案对裸片进行封装, 得到芯片成品.
4. 封装厂将芯片成品交给开发板团队, 由开发板团队设计开发板, 并将芯片成品焊接到开发板上.
5. 将开发板交给用户, 用户在芯片上部署软件并运行.

## 若干代码风格和规范

在往期的"一生一芯"计划中, 我们发现部分不规范的代码风格会给后期的SoC集成带来额外的问题. 为了避免将来影响SoC集成的进度, 我们建议大家遵守以下若干代码规范.

#### 1. 如果你还没有深入理解Verilog的事件模型, 不要使用行为建模

事实上, 南京大学数字电路实验讲义中也提到"行为建模不利于初学者建立电路思维", 我们在这里引用相关的描述:

#### 强烈建议初学者不要使用行为建模方式设计电路

Verilog一开始并不是为了设计可综合电路而提出的, 它的本质是一门基于事件队列模型的电路建模语言. 因此, 行为建模很容易会让初学者偏离描述电路的初衷: 开发者需要看着电路图, 心里想象电路的行为, 然后转化成事件队列模型的思考方式, 最后再用行为建模方式来描述电路的行为, 综合器再来根据这样的描述推导出相应的电路. 从这个过程来看, 这不仅是没有必要的, 而且还很容易引入错误:

- 如果开发者心里本身就已经有电路图, 直接描述它是最方便的
- 如果开发者心里本身就已经有电路图, 而开发者对行为建模方式的理解所有偏差, 可能会采用了错误的描述方式, 从而设计出非预期的电路
- 如果开发者心里没有电路图, 而是期望通过行为建模方式让综合器生成某种行为的电路, 这就已经偏离“描述电路”的本质了. 大部分同学非常容易犯这样的错误, 把行为建模当作过程式的C语言来写, 尝试把任意复杂的行为描述映射到电路, 最终综合器只会生成出延迟大, 面积大, 功耗高的低质量电路, 甚至因为代码包含数据竞争而被综合器综合成行为不符合预期的电路

所以, 直到大家掌握"描述电路"的思维而不被行为建模误导之前 我们强烈建议初学者远离行为建模方式, 仅通过数据流建模和结构化建模方式直接描述电路. 下面的问题可以帮助大家测试自己是否已经掌握Verilog的本质:

- 在硬件描述语言中, "执行"的精确含义是什么?
- 是谁在执行Verilog的语句? 是电路，综合器，还是其它的?
- if的条件满足, 就不执行else后的语句, 这里的"不执行"又是什么意思? 和描述电路有什么联系?
- 有"并发执行", 又有"顺序执行", 还有"任何一个变量发生变化就立即执行", 以及"在任何情况下都执行", 它们都是如何在设计出来的电路中体现的?

如果你无法对这些问题作出明确的回答, 我们强烈建议你不要使用行为建模方式. 如果你真的想弄懂它们, 你需要阅读[Verilog标准手册](http://staff.ustc.edu.cn/~songch/download/IEEE.1364-2005.pdf).

#### 真正的描述电路 = 实例化 + 连线

忘记行为建模方式, 就可以很容易回归到描述电路的简单本质. 想象一下, 你手中有一张电路图纸, 如果你需要向其它人描述图纸上的内容, 你将会如何描述? 你一定会说出类似"有一个A元件/模块, 它的x引脚和另一个B元件/模块的y引脚相连"的描述, 因为这才是描述电路的最自然的方式. 用HDL设计电路, 就是在用HDL来描述电路图纸, 图纸上有什么, 就直接描述什么. 所以, 用HDL描述电路, 无非是做两件事情:

- 实例化: 在电路板上放一个元件/模块, 可以是一个门电路, 或者是由门电路组成的模块
- 连线: 用导线将元件/模块的引脚正确地连起来

大家可以体会一下, 数据流建模和结构化建模是如何体现这两件事的, 而行为建模又是如何把这两件简单的事情复杂化的.

所以, 我们不建议初学者在Verilog代码中编写任何always语句. 为了方便大家使用触发器和选择器, 我们提供了如下Verilog模板给大家进行调用:

```
// 触发器模板
module Reg #(WIDTH = 1, RESET_VAL = 0) (
  input clk,
  input rst,
  input [WIDTH-1:0] din,
  output reg [WIDTH-1:0] dout,
  input wen
);
  always @(posedge clk) begin
    if (rst) dout <= RESET_VAL;
    else if (wen) dout <= din;
  end
endmodule

// 使用触发器模板的示例
module example(
  input clk,
  input rst,
  input [3:0] in,
  output [3:0] out
);
  // 位宽为1比特, 复位值为1'b1, 写使能一直有效
  Reg #(1, 1'b1) i0 (clk, rst, in[0], out[0], 1'b1);
  // 位宽为3比特, 复位值为3'b0, 写使能为out[0]
  Reg #(3, 3'b0) i1 (clk, rst, in[3:1], out[3:1], out[0]);
endmodule
```

```
// 选择器模板内部实现
module MuxKeyInternal #(NR_KEY = 2, KEY_LEN = 1, DATA_LEN = 1, HAS_DEFAULT = 0) (
  output reg [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [DATA_LEN-1:0] default_out,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);

  localparam PAIR_LEN = KEY_LEN + DATA_LEN;
  wire [PAIR_LEN-1:0] pair_list [NR_KEY-1:0];
  wire [KEY_LEN-1:0] key_list [NR_KEY-1:0];
  wire [DATA_LEN-1:0] data_list [NR_KEY-1:0];

  genvar n;
  generate
    for (n = 0; n < NR_KEY; n = n + 1) begin
      assign pair_list[n] = lut[PAIR_LEN*(n+1)-1 : PAIR_LEN*n];
      assign data_list[n] = pair_list[n][DATA_LEN-1:0];
      assign key_list[n]  = pair_list[n][PAIR_LEN-1:DATA_LEN];
    end
  endgenerate

  reg [DATA_LEN-1 : 0] lut_out;
  reg hit;
  integer i;
  always @(*) begin
    lut_out = 0;
    hit = 0;
    for (i = 0; i < NR_KEY; i = i + 1) begin
      lut_out = lut_out | ({DATA_LEN{key == key_list[i]}} & data_list[i]);
      hit = hit | (key == key_list[i]);
    end
    if (!HAS_DEFAULT) out = lut_out;
    else out = (hit ? lut_out : default_out);
  end
endmodule

// 不带默认值的选择器模板
module MuxKey #(NR_KEY = 2, KEY_LEN = 1, DATA_LEN = 1) (
  output [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);
  MuxKeyInternal #(NR_KEY, KEY_LEN, DATA_LEN, 0) i0 (out, key, {DATA_LEN{1'b0}}, lut);
endmodule

// 带默认值的选择器模板
module MuxKeyWithDefault #(NR_KEY = 2, KEY_LEN = 1, DATA_LEN = 1) (
  output [DATA_LEN-1:0] out,
  input [KEY_LEN-1:0] key,
  input [DATA_LEN-1:0] default_out,
  input [NR_KEY*(KEY_LEN + DATA_LEN)-1:0] lut
);
  MuxKeyInternal #(NR_KEY, KEY_LEN, DATA_LEN, 1) i0 (out, key, default_out, lut);
endmodule
```

其中, `MuxKey`模块实现了"键值选择"功能, 即在一个`(键值, 数据)`的列表`lut`中, 根据给定的键值`key`, 将`out`设置为与其匹配的数据. 若列表中不存在键值为`key`的数据, 则`out`为`0`. 特别地, `MuxKeyWithDefault`模块可以提供一个默认值`default_out`, 当列表中不存在键值为`key`的数据, 则`out`为`default_out`. 实例化这两个模块时需要注意如下两点:

- 需要使用者提供键值对的数量`NR_KEY`, 键值的位宽`KEY_LEN`以及数据的位宽`DATA_LEN`这三个参数, 并保证端口的信号宽度与提供的参数一致, 否则将会输出错误的结果
- 若列表中存在多个键值为`key`的数据, 则`out`的值是未定义的, 需要使用者来保证列表中的键值互不相同

`MuxKeyInternal`模块的实现中用到了很多高级的功能, 如`generate`和`for`循环等, 为了方便编写还使用了行为建模方式, 在这里我们不展开介绍, 通过结构化建模的抽象, 使用者可以无需关心这些细节.

以下代码通过使用选择器模板来分别实现2选1多路选择器和4选1多路选择器:

```
module mux21(a,b,s,y);
  input   a,b,s;
  output  y;

  // 通过MuxKey实现如下always代码
  // always @(*) begin
  //  case (s)
  //    1'b0: y = a;
  //    1'b1: y = b;
  //  endcase
  // end
  MuxKey #(2, 1, 1) i0 (y, s, {
    1'b0, a,
    1'b1, b
  });
endmodule

module mux41(a,s,y);
  input  [3:0] a;
  input  [1:0] s;
  output y;

  // 通过MuxKeyWithDefault实现如下always代码
  // always @(*) begin
  //  case (s)
  //    2'b00: y = a[0];
  //    2'b01: y = a[1];
  //    2'b10: y = a[2];
  //    2'b11: y = a[3];
  //    default: y = 1'b0;
  //  endcase
  // end
  MuxKeyWithDefault #(4, 2, 1) i0 (y, s, 1'b0, {
    2'b00, a[0],
    2'b01, a[1],
    2'b10, a[2],
    2'b11, a[3]
  });
endmodule
```

#### 如果你使用Chisel, 也建议你不要使用when和switch

在Chisel中, `when`和`switch`的语义和Verilog的行为建模非常相似, 因此也不建议初学者使用. 相反, 你可以使用`Mux1H`等库函数来实现选择器的功能, 具体可以查阅Chisel的相关资料.

#### 2. 如果你坚持使用Verilog的行为建模, 不要用negedge

`posedge`和`negedge`混用, 会导致时序收敛更加困难, 增加后端物理实现的难度. 如果你不清楚如何在两者混用的情况下仍然保持很好的时序, 我们建议你只使用`posedge`. 否则, 如果你的处理器严重影响SoC整体的时序, 在流片时间节点紧张的情况下, "一生一芯"项目组将会把你的处理器移出该批次的流片名单.

如果你使用我们提供的上述Verilog模板, 或者使用Chisel, 你不必担心这一问题.

#### 尝试用negedge综合

以上述模块为例, 尝试评估以下模块的时序:

```
module test(input clk, input rst, input in, output out);
  wire t0, t1;
  Reg r1(clk, rst, in, t0, 1'b1);
  Reg r2(clk, rst, t0, t1, 1'b1);
  Reg r3(clk, rst, t1, out, 1'b1);
endmodule
```

然后单独将`r2`修改为时钟下降沿触发, 并重新评估时序. 对比修改前后的时序报告, 你发现有什么不同之处? 如果你发现自己无法理解其中的细节, 不必担心, 我们会在B阶段进一步介绍时序分析的细节, 到时候将会重新讨论这个问题.

#### 3. 如果你坚持使用Verilog的行为建模, 不要使用锁存器(Latch)

锁存器的变化不受时钟驱动, 因此时序分析工具难以对其进行分析. 如果你不清楚如何避免锁存器, 我们建议你不要使用行为建模.

如果你使用我们提供的上述Verilog模板, 或者使用Chisel, 你不必担心这一问题.

#### 4. 需要在模块名前添加学号前缀

如`module IFU`需要修改为`module ysyx_22040000_IFU`. 这是因为大家将自己的处理器集成到SoC后, 名字相同的模块会导致工具报告重复定义的错误.

如果你使用Chisel, 我们将来会提供一个自动添加前缀的方法, 目前你编写代码时模块名不必添加学号前缀.

#### 5. 如果你使用Verilog, 需要在宏定义的标识符前添加学号前缀

如`` `define SIZE 5 ``需要修改为`` `define ysyx_22040000_SIZE 5 ``. 这是因为大家将自己的处理器集成到SoC后, 名字相同的宏会导致工具报告重复定义的错误.

如果你使用Chisel, 你不必担心这一问题.

## 完成数字电路实验

你之前已经通过在线学习网站HDLBits完成了不少数字电路的设计. 在搭建仿真环境并介绍EDA工具后, 我们已经可以支撑一个相对完整的数字电路设计流程:

```
新需求 -> 架构设计 -> 逻辑设计 -> 功能验证 -> 电路评估
```

其中, `架构设计`是指"思考如何通过电路功能实现新需求的方案", `逻辑设计`是指"用RTL代码实现设计方案", `功能验证`目前通过Verilator仿真来实现, 以检查RTL代码实现的功能是否符合预期, `电路评估`则是用开源EDA工具评估电路的性能, 面积, 功耗等指标.

接下来, 你将尝试按照上述流程来完成一些数字电路实验, 从而对其建立更深刻的认识.

#### 如果你想使用Chisel

请运行以下命令:

```
cd ysyx-workbench
bash init.sh npc-chisel
```

上述命令会将`npc`目录中的文件换成一个Chisel开发环境, 具体介绍可以阅读其中的`README.md`.

对于Chisel生成的Verilog代码, Verilator的静态代码检查功能产生的警告可能难以修复, 你可以在确定这些警告不影响代码正确性的情况下忽略它们. 但我们仍然建议你总是开启Verilator的静态代码检查功能, 因为在查阅这些警告的过程中, 你很有可能会发现一些代码逻辑相关的问题.

#### 借助NVBoard完成数字电路实验

我们首先推荐南京大学的[数字电路与计算机组成实验](https://nju-projectn.github.io/dlco-lecture-note/index.html).

南京大学开展教学改革, 将"数字电路"与"计算机组成原理"两门课程进行融合, 其实验内容贯穿从数字电路基础到简单的处理器设计. 有了NVBoard之后, 你就可以把它当作FPGA来使用, 用它来实现需要FPGA支持的实验内容.

你需要完成以下**必做内容**:

- 实验二 译码器和编码器
- 实验三 加法器与ALU
- 实验六 移位寄存器及桶形移位器
- 实验七 状态机及键盘输入
- 实验八 VGA接口控制器实现

如果你打算使用Chisel来完成上述数字电路实验, 你只需要把编译出的Verilog代码接入Verilator和NVBoard就可以了.

## 用RTL实现简单处理器

终于到了用RTL来设计自己的第一个处理器的时刻了! 你已经用Logisim实现了sCPU, 要用RTL来实现sCPU, 就是根据Logisim中的电路结构图, 用RTL代码描述出每个模块的电路结构. 有了完成数字电路的经验, 这对你来说并不困难.

#### 用RTL实现sCPU

尝试把sCPU作为NPC的设计目标, 根据之前你用Logisim设计的sCPU, 用RTL重新设计它, 用于计算`1+2+...+10`. 为了看到输出效果, 你可以在sCPU中添加`out rs`指令, 用于通过NVBoard的七段数码管显示数列求和的计算结果.

和sEMU不同, 我们暂时不要求你实现更强大的运行时环境, 目前只需要让这个处理器支持`1+2+...+10`的计算即可. 我们会在D阶段介绍运行时环境的更多相关内容.

#### 对比sEMU和sCPU

针对sISA, 你已经分别实现了sEMU和sCPU. 尝试对比一下, 它们之间有什么不同?

#### 评估sCPU的性能

尝试通过`yosys-sta`对你设计的sCPU进行评估.

恭喜你, 你已经基本完成了一个简单CPU的全流程设计了!

```
新需求 -> 架构设计 -> 逻辑设计 -> 功能验证 -> 电路评估
```

- sCPU设计的需求就是用RTL实现一个sISA的处理器
- F阶段的讲义内容已经帮助大家梳理了如何通过数字电路的功能来实现sCPU, 这其实已经完成了架构设计, 其产出就是Logisim中的电路结构图
- 大家用RTL设计sCPU的过程, 就是逻辑设计的过程
- 用Verilator和NVBoard验证你的RTL代码能否成功运行`1+2+...+10`, 就是在进行功能验证
- 你已经用`yosys-sta`对sCPU进行了电路评估

#### 使用开源EDA工具进行物理设计

目前"一生一芯"讲义只介绍了物理设计的过程, 暂未包含物理设计相关的动手实践内容. 如果你感兴趣, 你可以阅读[iEDA的入门教程](https://ieda.oscc.cc/tools/ieda-platform/guide.html), 并尝试用iEDA对sCPU进行物理设计, 生成相应的版图.

当然, sCPU的功能距离我们想要实现的CPU还差很远, 因此目前我们暂不要求大家去分析评估结果的好坏. 从项目流程上来看, 我们需要先设计出一个功能相对完整的CPU, 再考虑如何优化它, 这也是为了践行"先完成, 后完美"的法则. 后续的讲义内容将会按照上述流程, 指导大家如何设计功能更强大的处理器, 从而运行更复杂的程序.


---

> 来源：[https://ysyx.oscc.cc/docs/2407/e/6.html](https://ysyx.oscc.cc/docs/2407/e/6.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# E6 完成PA1

南京大学"计算机系统基础"课程实验PA是国内首个也是目前唯一一个模拟器教学实验, 它将会指导大家开发一个功能完备但又经过简化的模拟器NEMU, 并基于NEMU来搭建一个完整的计算机系统, 这个目标和"一生一芯"非常类似. 你已经实现了minirvEMU, 并在上面运行了一些简单的程序; 而NEMU的核心工作原理和minirvEMU是一样的, 只不过NEMU支持的功能更丰富.

我们将PA引入到"一生一芯"中, 主要有以下考虑:

- PA承担了系统能力培养的绝大部分任务: 从硬件模拟器, ISA, 运行时环境, 到自制OS, 库函数, 应用程序, 可以让你深刻认识到程序如何在计算机上运行的每一处细节
  - 如果你选择直接在RTL实现的处理器上构建系统软件, 你首先需要保证你的处理器是对的: 如果你的流水线在某个极端场景下和总线交互有问题, 你的自制OS和复杂应用程序(例如仙剑)都跑不起来. 相对地, 正确实现一个模拟器, 比正确实现RTL要容易得多
- 在企业流程中, 模拟器是处理器测试验证的一个重要组件. 通过引入PA, 我们希望让大家在"一生一芯"中也能体会到企业中的处理器开发流程. 同时, 我们还希望大家可以理解模拟器中的每一处细节, 需要的时候可以自行对它进行定制, 而不是把它当作一个和自己没有关系的外部工具

#### "计算机系统基础"理论课课程资源

在完成PA的过程中, 如果你需要补充一些理论课的知识, 可以参考袁春风老师在中国大学MOOC上开设的课程: [上](https://www.icourse163.org/course/NJU-1001625001), [中](https://www.icourse163.org/course/NJU-1001964032), [下](https://www.icourse163.org/course/NJU-1002532004)

#### 阅读PA讲义中的FAQ(常见问题)

在做PA之前, 我们强烈建议大家阅读[PA讲义中的FAQ](../pa/misc.md), 从而对PA有更多的了解.

#### 完成PA1

根据PA讲义完成相关内容(ISA选择默认的`riscv32`), 包括如下内容:

- [基础设施:简易调试器](../pa/PA1.md)
- [表达式求值](../pa/PA1.md)
- [监视点](../pa/PA1.md)
- 完成PA1的必答题 直到你看到如下提示框:

#### 温馨提示

PA1到此结束...


---

> 来源：[https://ysyx.oscc.cc/docs/2407/e/7.html](https://ysyx.oscc.cc/docs/2407/e/7.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# E7 提交入学答辩申请

#### 如果你感受到了独立解决问题的快乐

恭喜你!

因为这不仅意味着你的能力得到了肉眼可见的提升, 更重要的是你的内心也在变强, 和之前相比没那么害怕解决未知问题了. 这种心态的转变是至关重要的, 因为接下来还有无数的未知困难等着你去解决 😃

#### 阅读"提问的智慧"和"别像弱智一样提问", 编写读后感

很快你就要进入正式学习了. 随着知识难度的增加, 学习过程对你独立解决问题的要求也会越来越高. 为了帮助你尽快适应正式阶段的学习, 你需要仔细阅读[提问的智慧](https://github.com/ryanhanwu/How-To-Ask-Questions-The-Smart-Way/blob/master/README-zh_CN.md)和[别像弱智一样提问](https://github.com/tangx/Stop-Ask-Questions-The-Stupid-Ways/blob/master/README.md)这两篇文章, 结合自己在预学习阶段提问和被提问的经历, 写一篇不少于800字的读后感, 谈谈你对"好的提问"以及"通过STFW, RTFM和RTFSC独立解决问题"的看法.

#### 完成必做题并提交入学答辩申请

请根据["一生一芯"入学答辩申请指引](https://fa45epzd9c7.feishu.cn/docx/JyoFdo2lHoeUblxWgAscqkjSnt5), 完成相应内容并提交申请.
