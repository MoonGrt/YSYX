> 来源：[https://ysyx.oscc.cc/docs/ics-pa/FAQ.html](https://ysyx.oscc.cc/docs/ics-pa/FAQ.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# 常见问题(FAQ)

### PA是什么意思

PA是Programming Assignment的缩写, yzh也觉得这个名字起得有点随意.

### PA是不是组成原理/体系结构实验

都不是, PA不要求大家使用硬件描述语言进行编码, 而是通过C语言开发一款模拟器以及上层的软件(裸机运行时环境, 简易操作系统等). 与侧重于硬件层次的传统组成原理/体系结构实验相比, PA更注重计算机系统抽象层次的认识和理解.

### PA是不是很难

PA是一个超硬核的编程实验, 其中的硬核体现在, 只有同时满足以下条件, 你才有可能比较顺利地完成PA:

- 端正心态, 学会STFW/RTFM独立解决问题
- 掌握工具, 知道用什么样的工具快速解决什么样的问题
- 了解细节, 明白每一个文件每一行代码的行为
- 系统编程, 熟悉计算机系统中每个模块之间的联系

如果之前没有受到过类似的训练, 即使是高年级的研究生也会感到一定的困难. 所以对绝大部分同学来说, 做PA就是一个吃苦的过程.

### 为什么要用这么变态的PA来折磨我

因为大家普遍都很菜, 按照目前的状态, 你毕业之后很可能无法在社会的毒打下存活. 以下例子展示了将来你可能会面对什么样的毒打:

```
你的导师/老板: 你来做一个xxx, 目标是达到yyy的效果.
```

讲义? 框架代码? 不存在的. 如果我们不提供讲义和框架代码, 让你写一个能跑仙剑的NEMU, 这就和你毕业后面临的任务很类似了.

这就是社会毒打你的第一招必杀技: 充满不确定性的未知问题. 如果你现在连链表都调不好, 显然你几乎无法胜任这些不确定的任务. 作为算是扛得住社会毒打的人, 我们知道你缺什么, 知道应该给你挖什么样的坑, 设置什么样的技能训炼, 你就会得到什么程度的成长.

所以我们设计PA来把现在的你毒打一顿, 让你受尽折磨, 吃尽苦头, 归根到底是为了让将来的你在求职时候更具有竞争力, 经受得起社会的毒打.

### 我将来不从事系统相关的工作, 就不会那么痛苦了

太天真了. 就算是应用程序, 几千个模块之间通过几万个API交互的场景都是家常便饭, 复杂性是社会毒打你的第二招必杀技.

### 现在是开源的时代, 开源在《十四五规划和2035年远景目标纲要》中首次被列入国家发展规划, 那我为什么不能参考别人的代码/心得/攻略来学习

你来上课来做实验, 就应该接受我们设置的训练, 而独立完成实验是训练最基本的要求之一, 参考别人代码就是违反[学术诚信](http://integrity.mit.edu/)的行为, 针对这一点你没有任何理由讨价还价.

就算退一万步来讲, 你说参考别人是为了学习, 那你能写出比别人更好的代码作为学习的成果吗? 你要是真有这样的学习能力, 相信你也能够在遵守[学术诚信](http://integrity.mit.edu/)的前提下自己独立完成实验.

同理, 阅读网上流传的心得和攻略, 也是属于违反[学术诚信](http://integrity.mit.edu/)的行为, 因为你没有通过自己的努力和预期的训练来获得正确的答案.

### 为什么不能把代码/心得/攻略上传到公开的地方让大家学习

因为这违反了[学术诚信](http://integrity.mit.edu/). PA和其它项目不一样, 它本质上是一个课程作业, 你无法保证来看你代码的同学都是抱着纯洁的学习心态(我就看看我不抄). 如果有同学抱着抄袭的心态, 你的代码不仅会让他失去锻炼的机会, 而且还会破坏课程的公平性: 你一个bug调3天, 你同学1分钟就抄完了, 你甘心吗?

此外, 我们相信你的代码里面并没有太多值得大家学习的地方, 比如你的代码风格好看吗? 你设计的API合理吗? 和框架代码相比有什么新特色吗? 在你推荐自己的代码之前, 可以先看看一些优秀的开源项目. 如果你确实对自己的代码有信心, 不妨给yzh提建议, 如果你的建议很不错, 我们会把你加入到感谢名单中, 同时你的改进也可以一直在学弟学妹的作业中流传.

如果你上传代码只是为了托管, 那可以选择github的私人仓库.

同理, 将自己的心得和攻略上传到公开的地方, 也是属于违反[学术诚信](http://integrity.mit.edu/)的行为.

所以, 你公开的代码/心得/攻略很大概率并不能从真正的意义上帮助大家学习, 相反而是在很多层面上伤害大家.

### 能不能公布阶段性的参考答案, 这样即使bug调不出来, 也能往后做

不能. 把代码写对是对码农最基本的要求, 代码还没写对, 就不应该往后做. 以后你进入社会, 如果你交付的代码给客户造成经济损失, 是要赔钱的. 所以要学会对自己写的代码负责.

### 我总觉得讲义写得不清楚

你毕业后进入公司/课题组, 不会再有讲义具体地告诉你应该做什么, 总有一天你需要在脱离讲义的情况下完成任务. 我们希望你现在就放弃"讲义和框架代码会把我应该做的一切细节清楚地告诉我"的幻想, 为自己的成长负起责任:

- 不知道在说什么, 说明你对知识点的理解还不够清楚, 这时候你应该去看书/看手册
- 不知道要做什么/怎么做, 说明你的系统观还是零碎的, 理解不了系统中各个模块之间的联系, 这时候你应该RTFSC, 尽自己最大努力梳理并理解系统中的一切细节
- bug调不出来, 说明你不清楚程序正确的预期行为, 你需要RTFSC理解程序应该如何运行; 此外也说明你不重视工具和方法的使用, 你需要花时间去体验和总结它们

如果你发现自己有以上情况, 你还是少抱怨, 多吃苦吧.

当然, 如果你仍然觉得讲义写得不清楚, 可以联系yzh.

### 总是要求大家STFW/RTFM/RTFSC, 我有问题都不敢问了, 老师助教倒是轻松

老师助教不是你的保姆, 你需要先搞清楚哪些问题是你可以问的, 哪些问题是你应该自己解决的: 我们鼓励你提出关于方法层面的疑问以及对各种问题的探索性想法, 但不要直接让别人提供你想要的答案, 因为学会独立分析问题也是PA训练的一个重要环节.

一个我们不愿意回答的提问如下:

```
Q: 我的程序段错误了, 怎么办?
A: 机器永远是对的.
```

如果你确实需要一些调试相关的帮助, 那怎么办? 你需要展示你为了解决问题而付出过的努力, 当我们看到了你的努力, 也会认可你受到的训练. 例如:

```
Q: 我的程序在xxx的情况下段错误了, 我进行了以下尝试
* 首先我做了aaa, 现象是AAA, 我得到的结论是XXX
* 然后我做了bbb, 现象是BBB, 我得到的结论是YYY
* 我还做了ccc, 现象是CCC, 我得到的结论是ZZZ

综上, 我觉得问题可能出在yyy, 但我接下来没有思路了, 我的分析和理解是否正确? 或者我忽略了什么吗?
```

### 为什么用C语言写PA

首先C语言容易学, 可以给菜鸡们一个容易把编程能力补上的机会. 此外C语言的抽象少, 更接近机器, 更容易理解"程序如何在计算机上运行". 相对而言, 你很可能搞不清楚C++/python/java/scala/rust等各种语言特性背后的机制, 在调试代码的时候, 这会给你带来额外的挑战. 作为一个小型项目, 用C语言来写PA还是在可维护的范围的.

### 我发现自己做PA的用时明显大于讲义中预估的时间

讲义中的时间是按照"中等水平"同学的能力来预估的. 这里"中等水平"并不是指"程序设计课程总评80分以上", 而是指"心态端正, 编写过500行以上代码的单个程序, 并且懂得调试".

根据过去的情况, 绝大部分程序设计课程总评90分以上的同学都达不到我们所说的"中等水平"的标准. 所以忘了你的程序设计课程成绩吧, 对PA来说它并没有什么价值. (不过我们还是希望有一天这段话的描述不再符合实际.)

虽然程序设计课程成绩不能反映你们真实的编程水平, 但自己的编程水平是否扎实, 大部分同学还是心中有数的. 所以在这里我们也根据编程水平对讲义预估的时间进行调整, 得到一个更加可信的预估时间 (假设讲义上预估的时间是`x`小时):

- 神: `x / 5`
- 巨佬: `x / 3`
- 大佬: `x / 2`
- 编程基础扎实: `x`
- 不会调试: `x * 2`
- 不会写代码: `x * 3`
- 即不会写代码又不认真做PA: `x * 5`

我们知道大部分同学无法客观地判断自己完成PA的真实用时, 所以拖延你就输了.

### 我觉得PA对像我一样的菜鸡很不友好

程序设计实验对菜鸡友好, 但为什么你做完之后还是菜鸡? 做一个对菜鸡友好的实验, 能力并不会得到提升.

如果你是菜鸡, 说明你之前该吃苦的时候没吃够, 现在比别人多吃苦就是应该的.

### 我连完成PA1都觉得非常吃力

PA1和计算机系统的关联度偏低, 它主要是为了测试大家的编程能力而设计的. 如果你连完成PA1都觉得非常吃力, 那你就要给自己敲响警钟了: 快去学编程吧.

### 我感觉大部分同学都无法在一学期内做完PA的全部内容

很正常, PA从一开始设计的时候就没有想过会让所有同学完成所有内容. PA的设计理念是把目标定得很高, 强迫大家往上跳, 所以你会明显感觉到PA和你做过的其它实验都不太一样: 只要你愿意付出足够的努力, 即使你没有完成所有的内容, 你也会感到自己各个方面的技能都有了明显的提升.

每年确实会有同学直接躺倒放弃而挂科, 但也总有为数不少一批同学能坚持到最后, 锻炼出专业程序员该有的素质. 大家的编程水平有高有低, 如果你自己都觉得编程能力不行, 那你就应该去把编程能力补上来, 在那之前就不要抱有"完成PA所有内容"的幻想了. 一个比较合适的目标是"独立完成PA1和PA2", 最后你仍然有机会通过课程.

### 坚持了好久还是搞不定, 我想放弃了

也许是你坚持的姿势不对, 来跟yzh或者老师助教聊聊吧.

### 我觉得应该搜集大家踩过的坑, 这样后面做的同学就会顺利一些

这种想法是不对的, 掉坑里然后自己爬出来是训练重要的一环, 只有吃苦头才会让你成长. 如果你不想以后掉坑里, 正确的做法是现在花时间踩坑吃苦, 让自己变强大, 而不是通过投机取巧的方式绕过那些你本应该接受的训练.

### 为什么我本地测试都是对的, 但提交到OJ总是无法通过

因为你的代码有bug.

### PA的内容太丰富了, 我感觉没办法完全消化

所以PA值得二周目.

### 下学期的OSlab是不是比PA更难

在还没有PA的那个年代, jyy的OSlab是令人闻风丧胆的实验, 现在PA取代了这个位置. 你之所以觉得PA难, 一个主要原因就是前导课程没有给你足够的训练, 没有把你培养成一个素质合格的码农, 所以PA不得不额外承担这个角色.

从专业知识的角度来说, OSlab就应该比PA难. 但如果你已经在PA中训练出了码农应有的素质, 你也就已经准备好接受OSlab的挑战了.

### PA和OSlab有什么区别和联系

1. PA独有的内容: 上至运行时库函数和真实应用程序(仙剑, ONScripter等), 下至ISA模拟器的实现(寄存器, 指令, 分页机制等)
2. OSlab独有的内容: 并发(锁, 同步等), 持久化(可靠性, 崩溃一致性等)
3. PA和OSlab少量重合的部分: 上下文切换, 系统调用, 文件系统, 内存管理等. 但PA在涉及这些内容的时候是以广度优先为目标, 目的是通过设计一个最简单的模块, 把程序和计算机之前的关系串起来; 而OSlab会深入地展开这些内容, 比如ext文件系统, mmap等.

PA是OSlab的前导实验, 完成PA就会对操作系统有一个基本但不算深入的认识, 这时候再做OSlab, 上手就会更加顺利.

### 和大班的PA相比有什么区别, 哪个更难

大班PA是主线PA 2016版本的一个分支, 并且根据授课教师的想法进行调整. 随着主线PA的演进, 和大班PA的区别也逐渐增大. 鉴于"难"这个说法比较主观, 我们从另一个角度来展示两者的区别: 对于一个难点, 大班PA的设计理念是通过降低要求(提供提示甚至是代码)的方式来弱化它, 而主线PA的设计理念是呈现科学的方法来引导大家解决它.

所以从某种程度上来说, 大班PA降低要求的做法会对菜鸡来说会更友好, 但相对地, 全体学生在大班PA中受到的训练都会少很多. "计算机系统综合实验"课程对大班学生的少量抽样可以证明上述结论. 我们认为不应该为了照顾部分菜鸡而牺牲所有学生成长(吃苦)的机会, 所以主线PA没有选择降低要求, 而是让大家根据自身情况设置一个合适目标去努力.

### 我觉得PA有的设计不合理

欢迎联系yzh.


---

> 来源：[https://ysyx.oscc.cc/docs/ics-pa/changelog.html](https://ysyx.oscc.cc/docs/ics-pa/changelog.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# 更新日志

### ICS2024

#### NEMU

1. 特性
   - 提升在AM上运行时的随机性 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/fa6e67fcbbdddab62c738962072ea62b2c9e3938))
   - 使用capstone替换LLVM进行反汇编 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/1a493f9c0b433af2fbddabeb9c186bd55ccd4ad1))
   - DiffTest支持loongarch32r ([补丁](https://github.com/NJU-ProjectN/nemu/commit/8f74e3a5e6ef23cc0a0871f097e668f8992e25a2))
   - 重新添加x86 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/a738d2ea2d0194ab248c8b10c7e409e7a130b3ee))
2. 性能
   - 物理内存的初始化只采用1个随机字节, 大幅提升该步骤的性能 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/4fbe3ab3ba70a2cc6af0e2698a4041e89ac4dfc0))
   - 通过缩小局部变量的作用域提升译码过程的性能 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/a264eb16edc02c23c287ddd1aad11c38da8fe366))
3. 修复
   - 修复在AM上无法调用文件操作的问题 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/feea23db1987c80b3447c7966cc11a40b9f96a51))
   - 修复关闭窗口后仍无法退出的问题 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/da81fe5054d69c8d14d511bdcdca816fb1bcc5fd))
   - 修复将NEMU编译到`riscv64-nemu`时, NEMU中的ISA为`riscv32`的错误 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/7b57ba5d759fa6c18f7923ef985ae89d138b6196))
   - 修复在打开日志文件前调用`Log`导致段错误的问题 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/fc81a8f7b4e9da6c3dff68943082e8094f41bc3c))
   - 修复`utils.h`中`ANSI_BG_MAGENTA`的定义错误 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/bbbf9e3ac1cbf53ae754d19a5dcf406b630d4e1e))
4. 重构
   - 将`s->isa.inst.val`简化为`s->isa.inst` ([补丁](https://github.com/NJU-ProjectN/nemu/commit/a738d2ea2d0194ab248c8b10c7e409e7a130b3ee))
   - 添加`panic()`拦截不支持的译码类型 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/460dd550b604c15cba8c3d39631773116b919b0a))
   - 增大IO空间 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/98bc0822da1a3025c545b34b988006408a2e1edf))
5. 构建
   - 源文件无变化时无需重新链接 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/f2e7323a2fa3a110f46780fd3b41365fefa39960))
   - 修复`CONFIG_CC`为空时导致编译失败的问题 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/7972a459ba5932cb291057167cb3242416fcde6c))
   - 修复在macOS上SDL2库路径错误的问题 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/2fd67c07edff1f60dc4cef57d1df41f353581485))
   - 去除无用的宏定义 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/0c64fb9e0961aaaea4780dcf10fa3219fe1fc0ba))
6. 文档
   - 修复`config.mk`中的文字错误 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/d0ca3cfda4cd96ded866a520b13a0829029a675f))
   - 更新license中的时间 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/ba499b77d4e8cdd763750810e6ca8484c204d073))

#### Abstract-Machine

1. 特性
   - 在native中添加UART ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/493a0650ce0960e52e56d6d7500dccb56142bd08))
   - 为npc添加`uart_config`函数 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/c383159000a2975dabde43f221deae3d54bc48b0))
   - 为`riscv??-nemu`的`_start`符号添加大小属性 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/90ae4830e39a69c8652061a1758551a63098afb8))
   - 添加`riscv32mini-nemu` ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/56d4ae7165293bdbb06aa386d904e6a3e4621b23)和 [补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/9d1cb1d5631ba745510cc01e15a1314532fb596e))
   - 为native新增其他架构
     - aarch64([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/fe84c58450fd50f38bc500220b24c1f3bfbb5e70))
     - riscv64([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/a7b830fedd86505e8accba8f4b928084542c841a))
2. 修复
   - 修复`riscv??-nemu`的`trap.S`中的寄存器数量错误 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/f198eb6073383c1e0a5201be42b43c609082264e))
   - 修复使用clang时libgcc中的编译错误 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/62ca04d426865cce1ab55483a8b1ae6a6cf71f62))
   - 修复编译预处理指示符 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/acd889e89c8f043f74af96a3f060db777f821ee3))
   - 修复链接时`jal`跳转距离不够的错误 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/031dd9d93104468c7681ce3c72b1a3d1d33f6dea))
   - 修复loongarch的`cte.c`中变量名错误导致的编译错误 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/6f2c34532022bbb0d0c02aac64ff174e9655fc24))
   - 修复`x86-qemu`中boot相关的strict aliasing bug ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/de78d6ca0a5d399c55f9bae489239f5542d20fe7))
3. 重构
   - 去除klib中的无用代码 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/bcdbc4e249627e7a65eb0de51ec7507c1f9bbaf1))
   - 简单重构native GPU中`W`和`H`相关的代码 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/e6f833c3b93f42080ee90bdf286c76fa364b4df5))
4. 构建
   - 去除`Makefile`的`image-dep`规则中的冗余依赖 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/3ba0c6afd76fffe249f5d076d9f631a6e6d4fe36))
   - 避免Linux上的其他动态库链接到ELF中的符号 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/fa82955135ef6b93b711ec8c3b4e30c3a75c6fc7))
   - 重构依赖规则
     - 修复源文件无变化时仍然重新链接的问题 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/c3ffbc97c39d5374c3e4f182eaaa8ae7bdc0e98e))
     - 将`mainargs`注入到bin文件, 避免重复编译`trm.c` ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/c52a41181f8ea5d0e970008e51f58867a3ce65bb))
     - 将链接脚本添加到依赖规则 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/84051a9071557010554b6535408a15293ffa5892))
     - 不显示native的链接命令 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/befa0459648bdf3821dc71e46673f443977ec337))
   - `native`的IOE通过`sdl2-config`找到`SDL.h` ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/61a35370c9ea634aeef69c5faacf2bb146a50230))
   - 修复`x86-qemu`中`array subscript 0 is outside array bounds`的警告 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/0e37b474981568f2790f75f5d1105bbb2509515c))

#### am-kernels

1. 特性
   - 新增若干测试
     - `yiels-os`([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/6f4a47afb9d6ca1872b52ec5ebaa0351d3549c71))
     - `bad-apple`([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/7bb7b1a94fb13729dcc8ce4b384fff47caeb04ec))
     - `blockchain` ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/3bdc2529639606a92d23e921542fc1ec95c68af6)和 [补丁](https://github.com/NJU-ProjectN/am-kernels/commit/a799b79f5f470986e1cdd2b594ef1300927da0e3))
   - 假设`uptime`不从0开始, 从而支持`typing-game`的重新运行 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/ade50b257ac81f21f82fdba6c2e9c80cc2b7a17b))
   - benchmark出错时向TRM返回非0值 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/2e7c5934eda067ca2b116d23fb567b7090ef0a44))
2. 性能
   - 加速`typing-game`清屏的过程 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/d41f447c17f387a10dee3ad750a7b5d8d0c2d264))
3. 修复
   - 修复`keyboard-test`中`char`符号问题 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/33c0dd0d8510c27678f230b9c2799a7fe91324a0))
   - 修复`game of life`的栈溢出问题 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/0c1f038ad0f50de57f806d24343ea93b102be732))
   - 修复`hanoi`中屏幕不刷新的问题 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/3c50c2eae3d9d001f33cae089c87cf9a51630669))
   - 修复`alu-tests`中的若干问题
     - 修复由`-Wall`和`-Werror`报告的错误 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/d918fc429f330325bd331e00aa8930d4a6593704))
     - 修复由clang报告的`-2147483648`格式错误问题 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/9486898b811b8e436733c2e1ca99419592c62fc5))
   - 修复`microbench`中的`uint32_t`溢出问题 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/1dc914a675aa41a09762ab4a83318a481f96e429))
   - 修复在性能较低的平台上`donut`显示时间过短的问题 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/bb725d6f8223dd7de831c3b692e8c4531e9d01af))
4. 重构
   - 为`intr-test`添加panic信息 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/86c5532674db3edf8793dc71cdc72dfb097523ec))
5. 构建
   - 改进`cpu-tests`的`Makefile`输出的信息 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/dbe346eb85628a44b18d00c666883b7506dc75ea))
6. 文档
   - 补充`alu-tests`和`snake`的license ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/773fa2b9972945ab1dbe1c5d675b7d2a0e6becbb))

#### Navy-apps

1. 修复
   - 修复`nplayer`中的结束判断条件 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/250084182bf17851ce2f48b7f4b7116a57163a56))
   - 拦截libbdf中字体文件打开错误的问题 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/a1ca3b9806a6addca02b5495ee99aa5071074315))
   - 用surface相关API实现`native`的SDL渲染, 修复render API只能在主线程调用的问题 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/b56b659255b8bd6f99e13cc484dc65d88f9f6a0f))
   - 修复`nslider`在Linux native上无法更新画面的问题 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/fb9d4528184fef345f1d4123116140e2336006bf))
   - 修复`libbdf`在gcc 13上编译错误的问题 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/b80605c997a22ae9f06ddf96b1aec5adc0b2b949))
2. 构建
   - 修复git未追踪`scripts/riscv/common.mk`的问题 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/d65f17be0929299822445b1f045ee074d0d56876))
   - 修复`ar`命令在macOS中出错的问题 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/6c8232a0519a82c8eabbf053af41053fce052599))
   - 重构依赖规则, 修复源文件无变化时仍然重新链接的问题 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/042a85a77d608195d3c23bbe90d0a599a130fbc1))
3. 文档
   - 添加关于`/proc/dispinfo`的注释 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/e8346911c80af39b63e47d8aba5878e43231ad63))

### ICS2023

#### NEMU

1. 特性
   - 重新添加mips32 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/76278e886803354b81d14522aa7eb71d7b810dee))
   - 新增loongarch32r ([补丁](https://github.com/NJU-ProjectN/nemu/commit/6fcaae09de32aafb3bf86d26d71def11db05bbfd))
   - 通过llvm反汇编时关闭伪指令 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/9bf4ff83597d37646098ed707f591f07d933e6bd))
2. 修复
   - 修复译码非法指令时的未定义行为 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/8417a259398089bb8b590b7785f768c075548d81))
   - 更新spike版本, 修复macOS上因llvm版本较新导致的spike编译错误 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/fe77a6b3a032f4ccd68da0570832518dd6475a1a))
     - 使用c++17编译spike ([补丁](https://github.com/NJU-ProjectN/nemu/commit/5f66cb8067674512bb606e20530d8d764188fbb4))
   - 修复`gen-expr`中`fscanf()`未检查返回值导致的编译报错 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/c3baa4a77de7525cef93e19c2353b90947e86e78))
   - 修复`nemu/src/device/keyboard.c`中宏可能与库的头文件中定义重名的问题
     - 宏展开后重名([补丁](https://github.com/NJU-ProjectN/nemu/commit/b5c841e21b2e87daedb64dd2710c0e8c38ee5aaf))
     - 宏展开过程中重名([补丁](https://github.com/NJU-ProjectN/nemu/commit/7cc6120266ba8163d4ae501017c1fcc195e556cd))
   - 修复SDL在Wayland环境下窗口不弹出的问题 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/03daf8795774fd9ba65454fb009daa65f66bc29a))
3. 重构
   - 合并riscv32和riscv64 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/4bfdb7e3a95752d2a901ac8ea726d80b3f1b58c6))
4. 构建
   - 修复C++报告的`invalid suffix on literal`警告 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/947dc940a9c9efcbdc798354eb71d85803bc4220))
   - 同步config文件 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/379f440c18499e9d80e02e3a72d263bafec187cf))
   - 修复在llvm15上库函数路径变化导致的编译错误 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/ed2066c1f6e7e6bfb4f8203146c5f3d1d856e348))
   - 修复在macOS上按键宏定义与系统库冲突的问题 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/48b4860cef80073dbac7b8d980c8d3b90f9bf152))
   - 将difftest动态库的符号默认设置为`visibility=hidden`, 提升动态库内部符号引用的性能 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/3d5b0b9160cd37fc5d462567123bd43e48f6fac6))
   - 修复Gentoo Linux中kconfig链接报错的问题 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/6498a76b2742a680ac2d6fd68358b878c64b05f5))
5. 文档
   - 更新启动debian的说明文档 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/f85b00d6a11bf537836e108f064603a0231ae094))
   - 修复`difftest-def.h`中注释的文字错误 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/cf50554d0294a033c6048a6cd29f4544f222971c))

#### Abstract-Machine

1. 特性
   - 新增`loongarch32r-nemu` ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/67699be876bd5afe4fc7ddf48b7363871120de0b))
   - 将`riscv64-npc`改为`riscv32e-npc` ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/d341fb23a0d3e032e93ca3d3486f7622450e2a72))
     - 为`riscv32e-npc`添加libgcc的若干支持, 用软件模拟乘除指令 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/a4d3661c31570eec6c87be650f6446bdd6099ea8))
   - 添加用于生成logisim镜像文件的python脚本 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/83ac97b4d90c2f4cdd0ecc043a93885d0d3c29a1))
2. 修复
   - 在mips32的`start.S`中为异常入口`0x80000180`预留若干位置, 用于设置异常入口处的执行 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/5051c13e02f657e87609c2bad17709155019c39c))
   - 修复sdl2-2.0.22-1后窗口有概率不显示的问题 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/ba5ba9838edcdef5cc8d7b436124af655ada36d1))
   - 修复native的`platform.c`链接到RT-Thread中`ftruncate()`的问题 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/21bfbcb293567804c9617e5ceb374f94f4bc32ed))
   - 修复`riscv.h`中通用寄存器数量在rve中不正确的问题 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/b1586e033693a3616b988200658342d6ff90569c))
   - 修复`riscv32-nemu`中错误采用rve ABI的问题 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/8878f1f6ce19c3fa0d9a9414e7a8c121116f31e1))
3. 重构
   - 将`scripts/isa/`目录下RISC-V相关的`.mk`文件合并成`riscv.mk` ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/ad8f8fb636925666d2fb9a2216da868b82ba0e5b))
   - 将`am/include/arch/`目录下RISC-V相关的`.h`文件合并成`riscv.h` ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/e0ae9b7651436f8dfcbe6383f73f67ebb04ce399))
4. 构建
   - 去除ld 2.39引入的关于可执行栈和可读可写可执行的可加载段的警告 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/024441cbed3e9889fe62503f34df5d6c3fa08170)和 [补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/31a5a10f4858096751329b5a9b8a671ba819b1ea))
   - 使用riscv64-linux-gnu-gcc 11将CSR指令独立成zicsr扩展, 修复相关编译错误 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/ad9504123fba7548ca41b1295664d1f9928b5052))
   - 支持将`LDFLAGS`传递给native的g++ ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/e8943b31fc30adaba4fded6b8e9eb4f73477e491))
   - 修复macOS上默认调用llvm-ar的问题 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/6d79d0efb082c5346c99fab1f1d67cb996f169f7))

#### am-kernels

1. 特性
   - 新增ALU test, bf等应用, 移植自[movfuscator项目](https://github.com/xoreaxeaxeax/movfuscator) ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/fbc27398751336619ed4242349fe4567b9bf82d5), [补丁](https://github.com/NJU-ProjectN/am-kernels/commit/d336e55bc38e8a4c2f263b562b02e8b95defdab2), [补丁](https://github.com/NJU-ProjectN/am-kernels/commit/6b5c2ad2d3cdfa24935e60ba5c4d166eb1ca94f4), [补丁](https://github.com/NJU-ProjectN/am-kernels/commit/b122a7fa12f13ccbde94c645f309f32325195149), [补丁](https://github.com/NJU-ProjectN/am-kernels/commit/1cf8c67eb673d2e344b1ae874c3d51f1e7c23d96), [补丁](https://github.com/NJU-ProjectN/am-kernels/commit/ec82e0f2cd389bfe0fa582244601af9ef70158b2), [补丁](https://github.com/NJU-ProjectN/am-kernels/commit/3388801aea9d288ed598fc3c66c6412f3460b0d2), [补丁](https://github.com/NJU-ProjectN/am-kernels/commit/c5bcf378e8de01ca1cf695ebcc36b8c7e0def2c9), [补丁](https://github.com/NJU-ProjectN/am-kernels/commit/4707aefcc525e7d25b4d3de941287acd0c7c14da))
2. 修复
   - 修复native在glibc 2.39上运行thread-os时发生栈溢出的问题 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/245c069c4efae82358a292a2d9dbdf9c1584fcbc))
3. 重构
   - 去除`cpu-tests`中冗余的klib依赖 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/53cc98e4c02fc44aab3d8595d451ff78aa15308f))

#### Navy-Apps

1. 特性
   - 新增loongarch32r ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/a0917289765288f1622e69d46666ab4540e7584c))
   - 新增riscv32e ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/0e782aa991e68b456c3cee4233b95c2ba4c7b820))
2. 修复
   - 修复native在glibc 2.39上段错误的问题 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/fd219c457db2b83a6e36f007079a6025b6fb3d1f))
   - 修复`LD_PRELOAD`影响gdb的问题 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/378380f4ecf51c4d65f4a475bdf66a91e95913db))
3. 重构
   - 将CRT中`_start`的定义集中在一个文件中, 方便使用`__riscv`宏进行判断 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/8fe76b4e50cc03c2d17e284f57f9e0d6e80e0c2f))
4. 构建
   - 添加缺失的文件`scripts/riscv/common.mk` ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/754fea853eaa91baf448b20464adb37f53798dff))
5. 文档
   - 修复`README.md`中的错误 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/f7209826eebd4011ac4a5d97f2a880e9c71d17c7))

### ICS2022

#### NEMU

1. 特性
   - 移除指令实现的IR层
   - 支持向spike注入中断
   - 使用LLVM库进行反汇编 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/58f009646bb6e2448f79486013f22d56d99c15a1))
   - 添加NEMU作为REF的API(一生一芯中使用) ([补丁](https://github.com/NJU-ProjectN/nemu/commit/55e43218041ddacd4487b4bdc4e15251b4ab9e03))
   - 添加MMIO区间重叠的检查 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/a1813e5e6f1ae0668da31d76b04517a189924068))
2. 修复
   - 修复spike段错误的问题 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/1b5a19b1975142d44797b7418aeebff458d52dbd))
   - 修复监视点初始化时的数组溢出问题 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/c02f89e0a88202ef497bbf048c105790c67626c8))
   - 修复`isa_logo`字符串缺少`\0`的错误 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/2e3773f9bb5581be6b4e7092955eb7215137bf9f))
   - 去掉RTL中间表示, 用"抄手册"宏重构译码部分 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/6892cee4d95ff628d878b4a0f6a9f887c9d5d626))
   - 修复`difftest_init()`中缺少的参数 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/af274458f2c0491cf3e5b4bd2520336057f531c0))
   - 修复因`optind`重定位错误导致spike触发段错误 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/8521f46acae2ada40ad067a4c0513f504cdd42d7))
   - 修复移位运算的未定义行为 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/ae8715807dc482db6f6e8f40efc38fcf9d4bc9f4))
   - 修复`ANSI`文字错误 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/a51185885fd23e411817014eaf820c8fe3eb589d))
   - 修复PMEM64的`printf`格式错误 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/32f212facc126f5a6d45cfb3a8276ef7b7d3d0c3))
   - 修复pmem右边界的计算 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/e9fd223f3d6c793c8ce5732ff183b9b98d3787d9)和 [补丁](https://github.com/NJU-ProjectN/nemu/commit/404746d04d0e1cfffe9d801bf9e3be05e03cd295))
   - 修复字符串中的文字错误 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/c0ecbb498aca635d9da3d179e1daaf5001b08775))
   - 修复`uint64_t`的格式说明符 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/c52dfec86a496a2399ef0aa1f8b54584ab3b7ce6)和 [补丁](https://github.com/NJU-ProjectN/nemu/commit/bf47a5911819fc1010f5d649f784113afa06b026))
3. 重构
   - 将`instr`重命名为`inst`
   - 去掉调用`dlopen()`时不使用的`RTLD_DEEPBIND` ([补丁](https://github.com/NJU-ProjectN/nemu/commit/d2de05d7d3f2ef8ae13403bc687be4a1a19c4aac))
   - 交换itrace中输出的字节序, 使其符合RISC-V的阅读习惯 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/161eb8dcc4ed1616f9e70db8d32bb31b80dd4697))
   - 重构物理内存左右边界的计算 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/4965f34aaac0cfa42030844c95110fd79dc61a7a))
   - 简化`INSTPAT`的写法 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/09bb925782871ed4eb98d17cfabab323d473df62)和 [补丁](https://github.com/NJU-ProjectN/nemu/commit/4aad1d6de344251c9c6c755fd000c30f199cbb24))
4. 构建
   - 修复`clean-tools`错误清除spike中子项目的问题 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/e9b9e4a9d7c792f5784f60c031ad0e0aa10819e5))
   - 修复git忽略追踪`disasm.cc`的问题 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/9fffdce8f8394b022ae3815f625408889dd6ec9b))
   - 支持多个LLVM版本 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/c24a93e6b21795fca269be4fe04d280e1e382960)和 [补丁](https://github.com/NJU-ProjectN/nemu/commit/d21e335ca8903670db422a8717956fa5c7fa92a3))
   - 使用`ics-pa`项目中的git函数 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/d7a7a000f36f9b5a309c509eebdea8f18e6f523c))
   - 默认关闭设备 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/030c87652479a84b9449d7f66ffafbae07a6551c))
   - 修复采用`-g`编译时的LLVM相关的警告 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/d114445d797c2782ee0ba597b6397f83c622f482))
   - 使用ssh从github上克隆spike ([补丁](https://github.com/NJU-ProjectN/nemu/commit/d65fa540caf35cf1a7e42b26de1fe09dbca7cc42))
   - 修复LLVM 14中头文件`TargetRegistry.h`移动导致的错误 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/a0a70ead187a928ad4e55cf3a5c72ef8a3734475))
   - LLVM版本小于11时报错 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/541d969d9280ffd60e6a94577c4bd3b9141e0bd5))
   - 去除`kconfig`中冗余的动态库`-ltinfo` ([补丁](https://github.com/NJU-ProjectN/nemu/commit/ea9758d0310d822a503761939b7f9f8dacb51470))
5. 文档
   - 添加license ([补丁](https://github.com/NJU-ProjectN/nemu/commit/29fd6af58df98ff102f09ff68a3e0972b13c1e99))

#### Abstract-Machine

1. 特性
   - `riscv64-npc`支持乘除法指令 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/89939ad7a2b2d7d92d4f72f4db33a48b9d0341eb))
   - 使用标准调试指令实现`nemu_trap` ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/d5fe878987b6f4b547c81b71897eabb7fb250940))
2. 修复
   - 修复定义`__NATIVE_USE_KLIB__`时的死递归 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/f9b9b390fb673cee2d733106db077efda65bb304))
3. 构建
   - 默认使用通常模式(而不是批处理模式)来运行NEMU ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/198ce9035281a5bc041c7b3213c2a3daacc091fa))
   - 修复ubuntu 21.10下因glibc中的`SIGSTKSZ`展开为函数调用而导致native编译出错的问题 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/112799e02a28d22f03cfe496fe36408112047a71))
     - 放宽`SIGSTKSZ`的检查条件 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/7c9b27be201ba70fa7793cab7efe822d8e951eee))

#### am-kernels

1. 构建
   - `cpu-tests`支持gdb目标 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/adc316af6e482e6444a9bd68bafc3a57e2cafdbc))

#### Nanos-lite

1. 修复
   - 修复`sizeof(struct timeval)`在glibc和newlib中不一致的问题 ([补丁](https://github.com/NJU-ProjectN/nanos-lite/commit/2a141760e31be246a7316942293a97873925bc2f))

#### Navy-apps

1. 构建
   - 使用ssh从github上克隆子仓库 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/13ba3997899ca9fe83e4c4c98a498ea06d41cfdd))

### ICS2021

#### NEMU

1. 特性
   - 为VGA添加sync寄存器 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/7e4bfdfc0c6058b6c488c4e05bfa06f8fb426795))
   - 添加riscv64 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/828ff8118f18de2079f08d1d658a80277a30a3bf))
   - 引入"抄手册宏", 简化操作码译码的实现 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/9edc3ac03d3a67c7fb368c1e6fb703b155293454))
   - 添加spike作为RISC-V DiffTest的REF
   - 暂时移除x86和mips
   - 移除`cpu-tests`的一键运行脚本, 将其合并到`cpu-tests`中
   - 添加各种对宏进行相关测试的宏定义
   - 添加一些将来可能会使用的资源, 包括启动Debian的说明, SD卡内核驱动等
   - 在`cpu_exec()`中调用`device_update()` ([补丁](https://github.com/NJU-ProjectN/nemu/commit/d9c2c749072e73b97e2b01d033d88c43ebc29d9b))
2. 修复
   - 修复`PMEM_SIZE`设置与讲义不一致的问题 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/c880b79490b33824995bfa4eb78b5f258ea735c5))
   - 修复文字错误`fecth` ([补丁](https://github.com/NJU-ProjectN/nemu/commit/0815e787a13dc6aa1dbafd7b7e6e7a4dadaf10d0))
   - 修复框架代码`audio_play()`未使用的编译警告 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/5536f2c5ae35e1d6683d7326908451069c43325e))
   - 修复`BITMASK`宏中的移位操作的未定义行为 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/b4cf42b47bf2b9ecb75e3ec5f9d850a1fef67057))
   - 修复`qemu-diff`中调用`calloc()`时的类型错误 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/91f932c6e1b921769e949b1f6844ed9a2da31399))
   - 修复`config.mk`中的文字错误 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/61e0cb43c31a46af6b2c75f57f718f027ae8e2f4))
   - 修复`MEM_RET_FAIL`与`MMU_TRANSLATE`的数值冲突的问题 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/7538d373a6e32088fff4000deace39d04ba329e0))
3. 重构
   - 去除`gen-expr`中的无用代码 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/dd5539c3f4e7306de7238ff47a83444ebc360f2d))
   - 将简易调试器命名为`sdb`
   - 添加`hostcall()`来封装计算指令以外的操作
   - 用`host_read()`/`host_write()`实现`pmem_read()`和`pmem_write()`
   - 添加`mmio_read()`/`mmio_write()`
   - 将部分功能实现放到`utils/`目录下
   - 重构`qemu-diff`中ISA相关的代码
   - 将`load_val`重命名为`is_write` ([补丁](https://github.com/NJU-ProjectN/nemu/commit/b9af1ea9abd93b169254ec6c4d3e6af55780a513))
   - 用`dnpc`更新`pc` ([补丁](https://github.com/NJU-ProjectN/nemu/commit/2bcb4d4cbfe4e1d2ba11b84126f2bd363216345d))
   - 将移位指令的命名修改成RISC-V风格 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/a1de894d42d83f31d54bff924a193e1b20ec86da))
   - 去除无用的`isa_mmu_state()` ([补丁](https://github.com/NJU-ProjectN/nemu/commit/b2371b1e16e9ab4af54f2ef66baf924aa10343bf))
   - 去除无用的`isa_hostcall()` ([补丁](https://github.com/NJU-ProjectN/nemu/commit/fe1f041fae05221b1db5ca768ba5b7eec9d968cc))
4. 构建
   - 添加`Kconfig`和`menuconfig`维护宏定义
   - 将`Makefile`拆成`build.mk`和`native.mk`, 前者用于在构建`tools/`目录下的工具时复用
   - 在`Makefile`中采用filelist维护需要编译的源文件
   - 支持将NEMU编译到AM
   - 去除`build.mk`中无用的`SO_CFLAGS` ([补丁](https://github.com/NJU-ProjectN/nemu/commit/2e014f5d6bc8d7211491a8547747211945e7fce4))
5. 文档
   - 在`Makefile`中添加注释 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/25ddea72b44035810a7c19bc4866c678a12b7dd2))
   - 修复`isa_raise_intr()`中的注释 ([补丁](https://github.com/NJU-ProjectN/nemu/commit/d80266ebcb5b38d89d88c061487eb436adcefdc0))

#### Abstract-Machine

1. 特性
   - NEMU的GPU通过向sync寄存器写入非零值实现屏幕的刷新 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/98ff649a54198edb6f4ee2720dc8bb8b9e2f878f))
   - `native`的堆区移动到`0x1000000`, 以支持用户程序可在VME关闭时访问 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/39b2c4350d46cd415860356239d6c4d8ba61cf92))
   - `native`的GPU支持800x600模式 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/e4e5d03fa6dc52795e66ac2693e0fe0e0d85c9af))
   - 添加`riscv64-nemu` ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/11059d5b6fbdb79ae2d22f4ce495ec04d20bf59e))
   - 强制`native`初始化时链接到glibc中的`memcpy()`, 在klib中的`memcpy()`实现不正确的情况下也能工作
   - 为NEMU添加单核的MPE实现
   - 支持`x86_64-qemu`的交叉编译
   - 添加`riscv64-mycpu`(一生一芯中使用) ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/1a4ad391764a7e160ad99e5fbf2b9d096ad25234), [补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/17037fabb0d877f2568490cdc035e3a28085848d), [补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/07eb9ba416c5207013d10c4b57667fce9ca4f809), [补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/01d76dd0d56b00400cdeb89636a95d8a7ee6f0bf))
   - 添加spike ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/3cf0ee6d428d1eb6348fa0ee6c2e3c7f8a746363))
2. 性能
   - 移除`native`在物理内存上的保护功能, 减少系统调用以提升性能 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/18995de2698b26140b660271054a1a37336e3f67))
   - 用哈希表实现`native`的`map()`中的虚地址查找
3. 修复
   - 修复Linux 4.19内核中因恢复FPU上下文时`fxrstor64`指令触发缺页而发送`SIGSEGV`的问题 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/66dcd98e39b6cd93c49dcc2b8ca38495d30db075))
   - 修复`native`在信号处理函数中调用非信号安全函数`printf()`的问题
   - 修复`amdev.h`被多次包含造成的问题
   - 修复在`native`上运行仙剑时遇到的`SIGFPE`问题, 需要在调用`SDL_BlitSurface`前清除等待中的FPU异常
   - 修复`riscv64-mycpu`模拟除法时的死递归问题 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/3364f57d0bf5f31f91d5b1214a7a7b17e975c049))
   - 修复静态库的循环依赖问题 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/3c2e025216938332206c6011951365fd5088ad3b))
4. 重构
   - 移除`x86-nemu`中无用的`usp` ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/55ef7b162d0466cacac0a7e96f1c7007f85752fc))
   - 在`native`中使用`SIGUSR2`实现`yield()`, 提升代码的可移植性
   - 在`native`中使用函数调用从`irq_handle()`返回, 提升代码的可移植性
   - 用surface相关API实现`native`的SDL渲染
   - 将`native`平台相关的代码移动到`platform.c`中
   - 用管道实现`native`声卡中的数据同步
   - 去除`boot`目录
   - 将`__amkcontext_start`重命名为`__am_kcontext_start`
   - klib中的函数默认调用`panic()`
   - 重构目录, 合并riscv32和riscv64 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/30e5cd0c7e50d19d7fde4f95c6d0ff8edbad5c1b))
5. 构建
   - 清理NEMU客户程序中未使用的代码和数据 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/a1c8ab14d1bc71bb80eea720ad00a4c87615f7f0))
   - 去除Ubuntu 20.04中在Comet Lake以上版本的CPU中编译出的`endbr32`指令 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/0f6f91dee305ad0b143bf13becc2882eda4d977a))
   - 待构建源文件列表为空时提示错误信息
   - 若交叉编译器不存在, 则使用本地编译器
   - 不同的架构复用相同的链接脚本
   - 在mk文件中指定AM相关的源文件 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/30e5cd0c7e50d19d7fde4f95c6d0ff8edbad5c1b))
   - 在Ubuntu中禁用栈保护 ([补丁](https://github.com/NJU-ProjectN/abstract-machine/commit/a873515bde26f4ee0826d5e0c7c4df700e6ebe77))
6. 文档
   - 完善`Makefile`中的注释

#### am-kernels

1. 特性
   - `microbench`的时间精度提升至`us` ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/f4f447c422d46f866bbd5ec5d871eef2407c03b5))
   - `microbench`添加`huge`规模输入, 用于真机测试 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/54f5c1f8faffc956cc195578563fc67be6f42c88)和) [补丁](https://github.com/NJU-ProjectN/am-kernels/commit/e611fa70d2e156c93adb4d002cce145defa17d05))
   - `microbench`的参考机器更换为`i9-9900k` ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/e45d2189d9ea0644e22c4e6b04ad3d40dc7393bf))
   - `cpu-tests`支持一键运行的结果统计 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/56c864d5eff587138e26149616bd129c35e230bc))
   - 支持将NEMU编译到AM ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/6052ab0244aa06b033eed47313c42093f9cc5e4b))
   - 当NEMU未成功编译到AM时, 恢复之前的config配置 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/c03fc2b97bbab2f5f37a41c991cd31d905a740b1))
2. 修复
   - 修复`cpu-tests`的`string`测试中`strcmp()`的返回值检查 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/242c1f1f53a5c38268c68b0827e655296431358d))
   - 修复`litenes`中多重定义的链接错误 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/87c35f8f19aa0545a1e78a81020b9c105e76e87d))
3. 重构
   - 在`microbench`中显式使用`uint32_t`和`uint64_t` ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/1a008865df39382cf9bc6f5afa5a0eae34686513))
   - 由`microbench`自行对`us`部分进行输出格式化, 避免对`%03d`的依赖 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/a3d742d2592ef7b6135f0f93c460320cc3304c07))
   - 将`am-tests`中`intr-test`的`pirntf()`换成`putch()`, 降低对klib的依赖 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/5e7cd0c7f237e1b276674245c733bbcfe055bd55))
4. 构建
   - 移除`cpu-tests`中不再使用的构建规则 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/f3af11ebbfeab009a2213f9ca534e9a802a64235))
   - 取消部分文件的可执行权限 ([补丁](https://github.com/NJU-ProjectN/am-kernels/commit/8a1caa1db35077367ec83757b90b6be160021200))

#### Nanos-lite

1. 修复
   - 修复`HAS_NAVY=0`时依赖错误的问题 ([补丁](https://github.com/NJU-ProjectN/nanos-lite/commit/a5a1a3dbfa7f4f5d1b25fb834572544bf04fbbbb))
   - 修复框架代码`pg_alloc()`未使用的编译警告 ([补丁](https://github.com/NJU-ProjectN/nanos-lite/commit/04ae868da1e100fb3199e8f1baf1ebbed3368501))

#### Navy-apps

1. 特性
   - 添加`riscv64`的支持 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/0de5de8d21e68ff3f4d732cb17fd100f13461cc9))
2. 修复
   - 修复NWM在退出时子进程仍然运行的问题 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/1b68cecfd71e3964a446a982ae36136c651fe543))
   - 修复`libbdf`和`libbmp`调用`SDL_CreateRGBSurfaceFrom`后的内存泄漏问题 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/8a2f3d910b5228a4c5415b888e7da0b8390aacd5))
3. 重构
   - `libminiSDL`将`fp`从`SDL_RWops`的`union`成员中取出, 从而允许通过`fmemopen`实现内存文件 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/603b7b776860b82e6b69cd28e14fec1ad3957259))
   - `libSDL_image`中要求`IMG_Load_RW()`的`freesrc`参数为`0` ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/603b7b776860b82e6b69cd28e14fec1ad3957259))
4. 构建
   - 令`ramdisk.img`大小为512字节的整数倍, 从而易于实现磁盘的特性 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/88a384c7f5b65380c5797b7589342442d6f44279))
   - 去除`make clean-all`时的警告信息 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/e853ea70d08a17a3f7b7dbeeed8bf06fe20fd4d4))
   - `make init`时不检查`ISA`是否合法 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/fb4f7184883917de77e85e6568637464ef6b7860))
   - `make install`时自动创建`fsimg/bin/`目录 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/da22c2f16559c461d1f420bc22ff2481900ad95e))
5. 文档
   - `libSDL_mixer`支持不同频率不同声道的多通道混声 ([补丁](https://github.com/NJU-ProjectN/navy-apps/commit/603b7b776860b82e6b69cd28e14fec1ad3957259))


---

> 来源：[https://ysyx.oscc.cc/docs/ics-pa/exec.html](https://ysyx.oscc.cc/docs/ics-pa/exec.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# x86的mov指令执行例子剖析

我们举两个`mov`指令的例子, 它们是NEMU自带的客户程序`mov`中的两条指令:

```
100000:	b8 34 12 00 00        mov    $0x1234,%eax
......
100017:	66 c7 84 99 00 e0 ff	movw   $0x1,-0x2000(%ecx,%ebx,4)
10001e:	ff 01 00
```

## 简单mov指令的执行

我们先来剖析第一条`mov $0x1234, %eax`指令的执行过程.

### 取指(instruction fetch, IF)

首先通过`inst_fetch()`取得这条指令的第一个字节`0xb8`.

### 译码(instruction decode, ID)

在`isa_exec_once()`函数中用这条指令的第一个字节`0xb8`来进行模式匹配, 发现这一指令的操作数宽度是`4`字节的`mov`指令, 形式是将立即数移入寄存器(move immediate to register).

事实上, 一个字节最多只能区分256种不同的指令形式. 当指令形式的数目大于256时, 我们需要使用另外的方法来识别它们. x86中有主要有两种方法来解决这个问题(在PA2中你都会遇到这两种情况):

- 一种方法是使用转义码(escape code), x86中有一个2字节转义码 `0x0f`, 当指令`opcode`的第一个字节是`0x0f`时, 表示需要再读入一个字节才能决定具体的指令形式(部分条件跳转指令就属于这种情况). 后来随着各种SSE指令集的加入, 使用2字节转义码也不足以表示所有的指令形式了, x86在2字节转义码的基础上又引入了3字节转义码, 当指令`opcode`的前两个字节是`0x0f`和`0x38`时, 表示需要再读入一个字节才能决定具体的指令形式.
- 另一种方法是使用`ModR/M`字节中的扩展opcode域来对`opcode`的长度进行扩充. 有些时候, 读入一个字节也还不能完全确定具体的指令形式, 这时候需要读入紧跟在`opcode`后面的`ModR/M`字节, 把其中的`reg/opcode`域当做`opcode`的一部分来解释, 才能决定具体的指令形式. x86把这些指令划分成不同的指令组(instruction group), 在同一个指令组中的指令需要通过`ModR/M`字节中的扩展opcode域来区分.

接下来还需要识别指令的操作数. 对于`mov $0x1234, %eax`指令来说, 识别操作数其实就是识别寄存器`%eax`和立即数`$0x1234`. 在x86中, 通用寄存器都有自己的编号,`I2r`形式的指令把寄存器编号也放在指令的第一个字节里面, 我们可以通过位运算将寄存器编号抽取出来; 立即数存放在指令的第二个字节, 可以很容易得到它. 需要说明的是, 由于立即数是指令的一部分, 我们还需要通过`inst_fetch()`函数来获得它.

此外, x86的译码类型主要以i386手册附录A中的操作数表示记号来命名, 直接反映了操作数的类型和数据流向. 例如`I2r`表示将立即数移入寄存器, 其中`I`表示立即数, `2`表示英文`to`, `r`表示通用寄存器, 更多的记号请参考i386手册.

### 执行(execute, EX)

对于`mov $0x1234, %eax`指令来说, 执行阶段的工作就是把立即数`$0x1234`送到寄存器`%eax`中. 直接通过`Rw()`宏实现这一功能即可.

### 更新PC

把`s->dnpc`赋值给`cpu.pc`即可.

## 复杂mov指令的执行

对于第二个例子`movw $0x1, -0x2000(%ecx,%ebx,4)`, 执行这条执行还是分取指, 译码, 执行三个阶段.

首先是取指. 这条mov指令比较特殊, 它的第一个字节是`0x66`, 如果你查阅i386手册, 你会发现`0x66`是一个`operand-size prefix`. 因为这个前缀的存在, 本例中的`mov`指令才能被CPU识别成`movw`. NEMU通过一个局部变量标志`is_operand_size_16`来记录操作数宽度前缀是否出现, 模式匹配中的`0x66`将设置该标志, 然后通过`goto`语句回到函数的开头重新取出操作码, 此时取得了真正的操作码`0xc7`. 由于`is_operand_size_16`标志已设置, 在后续译码过程中将会确定操作数长度为`2`字节.

#### x86的操作数宽度处理

大部分x86指令都有不同操作数宽度的版本, 因此x86的操作数宽度信息记录会更复杂: 首先模式匹配规则中给出的宽度信息确定操作数宽度; 若该操作数宽度结果为`0`, 表示仅仅根据操作码来判断, 操作数宽度还不能确定, 可能是16位或者32位, 需要通过`is_operand_size_16`来决定.

接下来是识别操作数. 根据操作码`0xc7`查找相应的模式匹配规则, 发现译码类型为`I2E`, 于是分别调用`decode_rm()`和`imm()`来取出操作数. 由于本例中的`mov`指令需要访问内存, 因此除了要识别出立即数之外, 还需要确定好要访问的内存地址. x86通过`ModR/M`字节来指示内存操作数, 支持各种灵活的寻址方式. 其中最一般的寻址格式是

> displacement(R[base\_reg], R[index\_reg], scale\_factor)

相应内存地址的计算方式为

> addr = R[base\_reg] + R[index\_reg] \* scale\_factor + displacement

其它寻址格式都可以看作这种一般格式的特例, 例如

> displacement(R[base\_reg])

可以认为是在一般格式中取`R[index_reg] = 0, scale_factor = 1`的情况. 这样, 确定内存地址就是要确定`base_reg`, `index_reg`, `scale_factor`和`displacement`这4个值, 而它们的信息已经全部编码在`ModR/M`字节里面了.

我们以本例中的`movw $0x1, -0x2000(%ecx,%ebx,4)`说明如何识别出内存地址:

```
100017:	66 c7 84 99 00 e0 ff	movw   $0x1,-0x2000(%ecx,%ebx,4)
10001e:	ff 01 00
```

根据`I2E`的指令形式, `0xc7`是`opcode`, `0x84`是`ModR/M`字节. 在i386手册中查阅表格17-3得知, `0x84`的编码表示在`ModR/M`字节后面还跟着一个`SIB`字节, 然后跟着一个32位的`displacement`. 于是读出`SIB`字节, 发现是`0x99`. 在i386手册中查阅表格17-4得知, `0x99`的编码表示`base_reg = ECX, index_reg = EBX, scale_factor = 4`. 在`SIB`字节后面读出一个32位的`displacement`, 发现是`00 e0 ff ff`, 在小端存储方式下, 它被解释成`-0x2000`. 于是内存地址的计算方式为

> addr = R[ECX] + R[EBX] \* 4 - 0x2000

框架代码已经实现了`decode_rm()`函数和`load_addr()`函数, 其函数原型为

```
void decode_rm(Decode *s, int *rm_reg, word_t *rm_addr, int *reg, int width);
void load_addr(Decode *s, ModR_M *m, word_t *rm_addr);
```

它们将`s->snpc`所指向的内存位置解释成`ModR/M`字节, 根据上述方法对`ModR/M`字节和`SIB`字节进行译码, 把译码结果存放到参数`rm_reg`和`rm_addr`指向的变量中. 虽然i386手册中的表格17-3和表格17-4内容比较多, 仔细看会发现, `ModR/M`字节和`SIB`字节的编码都是有规律可循的, 所以`load_addr()`函数可以很简单地识别出计算内存地址所需要的4个要素(当然也处理了一些特殊情况). 不过你现在可以不必关心其中的细节, 框架代码已经为你封装好这些细节, 并且提供了各种用于译码的接口函数.

本例中的执行阶段就是要把立即数写入到相应的内存位置. 译码阶段已经把操作数准备好了, 通过`RMw()`宏完成数据移动的操作, 最终更新PC.


---

> 来源：[https://ysyx.oscc.cc/docs/ics-pa/git.html](https://ysyx.oscc.cc/docs/ics-pa/git.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# git快速入门

## 光玉

想象一下你正在玩Flappy Bird, 你今晚的目标是拿到100分, 不然就不睡觉. 经过千辛万苦, 你拿到了99分, 就要看到成功的曙光的时候, 你竟然失手了! 你悲痛欲绝, 滴血的心在呼喊着, "为什么上天要这样折磨我? 为什么不让我存档?"

想象一下你正在写代码, 你今晚的目标是实现某一个新功能, 不然就不睡觉. 经过千辛万苦, 你终于把代码写好了, 保存并编译运行, 你看到调试信息一行一行地在终端上输出. 就要看到成功的曙光的时候, 竟然发生了段错误! 你仔细思考, 发现你之前的构思有着致命的错误, 但之前正确运行的代码已经永远离你而去了. 你悲痛欲绝, 滴血的心在呼喊着, "为什么上天要这样折磨我?" 你绝望地倒在屏幕前... 这时, 你发现身边渐渐出现无数的光玉, 把你包围起来, 耀眼的光芒令你无法睁开眼睛... 等到你回过神来, 你发现屏幕上正是那份之前正确运行的代码! 但在你的记忆中, 你确实经历过那悲痛欲绝的时刻... 这一切真是不可思议啊...

## 人生如戏, 戏如人生

人生就像不能重玩的Flappy Bird, 但软件工程领域却并非如此, 而那不可思议的光玉就是"版本控制系统". 版本控制系统给你的开发流程提供了比朋也收集的更强大的光玉, 能够让你在过去和未来中随意穿梭, 避免上文中的悲剧降临你的身上.

没听说过版本控制系统就完成实验, 艰辛地排除万难, 就像游戏通关之后才知道原来游戏可以存档一样, 其实玩游戏的时候进行存档并不是什么丢人的事情.

在实验中, 我们使用 `git` 进行版本控制. 下面简单介绍如何使用 `git` .

### 游戏设置

首先你得安装 `git` :

```
apt-get install git
```

安装好之后, 你需要先进行一些配置工作. 在终端里输入以下命令

```
git config --global user.name "Zhang San"		# your name
git config --global user.email "zhangsan@foo.com"	# your email
git config --global core.editor vim			# your favourite editor
git config --global color.ui true
```

经过这些配置, 你就可以开始使用 `git` 了.

在实验中, 你会通过 `git clone` 命令下载我们提供的框架代码, 里面已经包含一些 `git` 记录, 因此不需要额外进行初始化. 如果你想在别的实验/项目中使用 `git` , 你首先需要切换到实验/项目的目录中, 然后输入

```
git init
```

进行初始化.

### 查看存档信息

使用

```
git log
```

查看目前为止所有的存档.

使用

```
git status
```

可以得知, 与当前存档相比, 哪些文件发生了变化.

### 存档

你可以像以前一样编写代码. 等到你的开发取得了一些阶段性成果, 你应该马上进行"存档".

首先你需要使用 `git status` 查看是否有新的文件或已修改的文件未被跟踪, 若有, 则使用 `git add` 将文件加入跟踪列表, 例如

```
git add file.c
```

会将 `file.c` 加入跟踪列表. 如果需要一次添加所有未被跟踪的文件, 你可以使用

```
git add -A
```

但这样可能会跟踪了一些不必要的文件, 例如编译产生的 `.o` 文件, 和最后产生的可执行文件. 事实上, 我们只需要跟踪代码源文件即可. 为了让 `git` 在添加跟踪文件之前作筛选, 你可以编辑 `.gitignore` 文件(你可以使用 `ls -a` 命令看到它), 在里面给出需要被 `git` 忽略的文件和文件类型.

把新文件加入跟踪列表后, 使用 `git status` 再次确认. 确认无误后就可以存档了, 使用

```
git commit
```

提交工程当前的状态. 执行这条命令后, 将会弹出文本编辑器, 你需要在第一行中添加本次存档的注释, 例如"fix bug for xxx". 你应该尽可能添加详细的注释, 将来你需要根据这些注释来区别不同的存档. 编写好注释之后, 保存并退出文本编辑器, 存档成功. 你可以使用 `git log` 查看存档记录, 你应该能看到刚才编辑的注释.

### 读档

如果你遇到了上文提到的让你悲痛欲绝的情况, 现在你可以使用光玉来救你一命了. 首先使用 `git log` 来查看已有的存档, 并决定你需要回到哪个过去. 每一份存档都有一个hash code, 例如 `b87c512d10348fd8f1e32ddea8ec95f87215aaa5` , 你需要通过hash code来告诉 `git` 你希望读哪一个档. 使用以下命令进行读档:

```
git reset --hard b87c
```

其中 `b87c` 是上文hash code的前缀: 你不需要输入整个hash code. 这时你再看看你的代码, 你已经成功地回到了过去!

但事实上, 在使用 `git reset` 的hard模式之前, 你需要再三确认选择的存档是不是你的真正目标. 如果你读入了一个较早的存档, 那么比这个存档新的所有记录都将被删除! 这意为着你不能随便回到"将来"了.

### 第三视点

当然还是有办法来避免上文提到的副作用的, 这就是 `git` 的分支功能. 使用命令

```
git branch
```

查看所有分支. 其中 `master` 是主分支, 使用 `git init` 初始化之后会自动建立主分支.

读档的时候使用以下命令

```
git checkout b87c
```

而不是 `git reset` . 这时你将处于一个虚构的分支中, 你可以

- 查看 `b87c` 存档的内容
- 使用以下命令切换到其它分支

```
git checkout 分支名
```

- 对代码的内容进行修改, 但你不能使用 `git commit` 进行存档, 你需要使用

```
git checkout -B 分支名
```

把修改结果保存到一个新的分支中, 如果分支已存在, 其内容将会被覆盖

不同的分支之间不会相互干扰, 这也给项目的分布式开发带来了便利. 有了分支功能, 你就可以像第三视点那样在一个世界的不同时间(一个分支的多个存档), 或者是多个平行世界(多个分支)之间来回穿梭了.

### 更多功能

以上介绍的是 `git` 的一些基本功能, `git` 还提供很多强大的功能, 例如使用 `git diff` 比较同一个文件在不同版本中的区别, 使用 `git bisect` 进行二分搜索来寻找一个bug在哪次提交中被引入...

其它功能的使用请参考 `git help` , `man git` , 或者在网上搜索相关资料.


---

> 来源：[https://ysyx.oscc.cc/docs/ics-pa/i386-intro.html](https://ysyx.oscc.cc/docs/ics-pa/i386-intro.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# x86指令系统简介

i386手册有一章专门列出了所有指令的细节, 附录中的opcode map也很有用. 在这里, 我们先对x86指令系统作一些简单的梳理. 当你对x86指令系统有任何疑惑时, 请查阅i386手册, 关于指令系统的一切细节都在里面.

#### i386手册勘误

由于PDF版本的i386手册的印刷错误较多, 一定程度上影响理解, 我们在github上开放了一个[repo](https://github.com/NJU-ProjectN/i386-manual), 用于提供修复印刷错误的版本. 同时我们也为修复错误后的版本提供在线的[HTML版本](https://nju-projectn.github.io/i386-manual/toc.htm).

如果你在做实验的过程中也发现了新的错误, 欢迎帮助我们修复这些错误.

## 指令格式

x86指令的一般格式如下:

```
+-----------+-----------+-----------+--------+------+------+------+------------+-----------+
|instruction| address-  |  operand- |segment |opcode|ModR/M| SIB  |displacement| immediate |
|  prefix   |size prefix|size prefix|override|      |      |      |            |           |
|-----------+-----------+-----------+--------+------+------+------+------------+-----------|
|   0 OR 1  |  0 OR 1   |   0 OR 1  | 0 OR 1 |1 OR 2|0 OR 1|0 OR 1| 0,1,2 OR 4 |0,1,2 OR 4 |
| - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -|
|                                     number of bytes                                      |
+------------------------------------------------------------------------------------------+
```

除了opcode(操作码)必定出现之外, 其余组成部分可能不出现, 而对于某些组成部分, 其长度并不是固定的. 但给定一条具体指令的二进制形式, 其组成部分的划分是有办法确定的, 不会产生歧义(即把一串比特串看成指令的时候, 不会出现两种不同的解释). 例如对于以下指令:

```
100017:	66 c7 84 99 00 e0 ff ff 01 00  	movw   $0x1,-0x2000(%ecx,%ebx,4)
```

其组成部分的划分如下:

```
+-----------+-----------+-----------+--------+------+------+------+------------+-----------+
|instruction| address-  |  operand- |segment |opcode|ModR/M| SIB  |displacement| immediate |
|  prefix   |size prefix|size prefix|override|      |      |      |            |           |
|-----------+-----------+-----------+--------+------+------+------+------------+-----------|
|                            66                 c7     84     99    00 e0 ff ff    01 00   |
+------------------------------------------------------------------------------------------+
```

凭什么`0x84`要被解释成`ModR/M`字节呢? 这是由`opcode`决定的, `opcode`决定了这是什么指令的什么形式, 同时也决定了`opcode`之后的比特串如何解释. 如果你要问是谁来决定`opcode`, 那你就得去问Intel了.

PA中的x86经过简化, `address-size prefix`和`segment override prefix`都不会用到, 因此NEMU也不需要实现这两者的功能.

#### 编码的艺术

对于以下5个集合:

1. 所有`instruction prefix`
2. 所有`address-size prefix`
3. 所有`operand-size prefix`
4. 所有`segment override prefix`
5. 所有`opcode`的第一个字节

它们是两两不相交的. 这是必须的吗? 这背后反映了怎样的隐情?

另外我们在这里先给出`ModR/M`字节和`SIB`字节的格式, 它们是用来确定指令的操作数的, 详细的功能会在将来进行描述:

```
ModR/M byte
7    6    5    4    3    2    1    0
+--------+-------------+-------------+
|  mod   | reg/opcode  |     r/m     |
+--------+-------------+-------------+


SIB (scale index base) byte
7    6    5    4    3    2    1    0
+--------+-------------+-------------+
|   ss   |    index    |    base     |
+--------+-------------+-------------+
```

事实上, 一个字节最多只能区分256种不同的指令形式. 当指令形式的数目大于256时, 我们需要使用另外的方法来识别它们. x86中有主要有两种方法来解决这个问题:

- 一种方法是使用转义码(escape code). x86中有一个2字节转义码`0x0f`, 当指令`opcode`的第一个字节是`0x0f`时, 表示需要再读入一个字节才能决定具体的指令形式(部分条件跳转指令就属于这种情况). 后来随着各种SSE指令集的加入, 使用2字节转义码也不足以表示所有的指令形式了, x86在2字节转义码的基础上又引入了3字节转义码, 当指令`opcode`的前两个字节是`0x0f`和`0x38`时,表示需要再读入一个字节才能决定具体的指令形式.
- 另一种方法是使用`ModR/M`字节中的扩展opcode域来对`opcode`的长度进行扩充. 有些时候, 读入一个字节也还不能完全确定具体的指令形式, 这时候需要读入紧跟在`opcode`后面的`ModR/M`字节, 把其中的`reg/opcode`域当做`opcode`的一部分来解释, 才能决定具体的指令形式. x86把这些指令划分成不同的指令组(instruction group), 在同一个指令组中的指令需要通过`ModR/M`字节中的扩展opcode域来区分.

## 指令集细节

要实现一条指令, 首先你需要知道这条指令的格式和功能, 格式决定如何解释, 功能决定如何执行. 而这些信息都在instruction set page中, 因此你务必知道如何阅读它们. 我们以`mov`指令的opcode表为例来说明如何阅读:

```
     Opcode       Instruction       Clocks        Description
                  
< 1> 88 /r        MOV r/m8,r8       2/2           Move byte register to r/m byte
< 2> 89 /r        MOV r/m16,r16     2/2           Move word register to r/m word
< 3> 89 /r        MOV r/m32,r32     2/2           Move dword register to r/m dword
< 4> 8A /r        MOV r8,r/m8       2/4           Move r/m byte to byte register
< 5> 8B /r        MOV r16,r/m16     2/4           Move r/m word to word register
< 6> 8B /r        MOV r32,r/m32     2/4           Move r/m dword to dword register
< 7> 8C /r        MOV r/m16,Sreg    2/2           Move segment register to r/m word
< 8> 8D /r        MOV Sreg,r/m16    2/5,pm=18/19  Move r/m word to segment register
< 9> A0           MOV AL,moffs8     4             Move byte at (seg:offset) to AL
<10> A1           MOV AX,moffs16    4             Move word at (seg:offset) to AX
<11> A1           MOV EAX,moffs32   4             Move dword at (seg:offset) to EAX
<12> A2           MOV moffs8,AL     2             Move AL to (seg:offset)
<13> A3           MOV moffs16,AX    2             Move AX to (seg:offset)
<14> A3           MOV moffs32,EAX   2             Move EAX to (seg:offset)
<15> B0 + rb ib   MOV r8,imm8       2             Move immediate byte to register
<16> B8 + rw iw   MOV r16,imm16     2             Move immediate word to register
<17> B8 + rd id   MOV r32,imm32     2             Move immediate dword to register
<18> C6 /0 ib (*) MOV r/m8,imm8     2/2           Move immediate byte to r/m byte
<19> C7 /0 iw (*) MOV r/m16,imm16   2/2           Move immediate word to r/m word
<20> C7 /0 id (*) MOV r/m32,imm32   2/2           Move immediate dword to r/m dword

---------------------------------------------------------------------------
NOTES:
moffs8, moffs16, and moffs32 all consist of a simple offset relative
to the segment base. The 8, 16, and 32 refer to the size of the data. The
address-size attribute of the instruction determines the size of the
offset, either 16 or 32 bits.
---------------------------------------------------------------------------

注:
标记了(*)的指令形式的Opcode相对于i386手册有改动, 具体情况见下文的描述.
```

上表中的每一行给出了`mov`指令的不同形式, 每一列分别表示这种形式的opcode, 汇编语言格式, 执行所需周期, 以及功能描述. 由于NEMU关注的是功能的模拟, 因此`Clocks`一列不必关心. 另外需要注意的是, i386手册中的汇编语言格式都是Intel格式, 而objdump的默认格式是AT&T格式, 两者的源操作数和目的操作数位置不一样, 千万不要把它们混淆了! 否则你将会陷入难以理解的bug中.

首先我们来看`mov`指令的第一种形式:

```
     Opcode       Instruction       Clocks        Description
< 1> 88 /r        MOV r/m8,r8       2/2           Move byte register to r/m byte
```

- 从功能描述可以看出, 它的作用是"将一个8位寄存器中的数据传送到8位的寄存器或者内存中", 其中`r/m`表示"寄存器或内存".
- Opcode一列中的编码都是用十六进制表示, `88`表示这条指令的opcode的首字节是`0x88`, `/r`表示后面跟一个`ModR/M`字节, 并且`ModR/M`字节中的`reg/opcode`域解释成通用寄存器的编码, 用来表示其中一个操作数.
- 通用寄存器的编码如下:

| 二进制编码 | 000 | 001 | 010 | 011 | 100 | 101 | 110 | 111 |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 8位寄存器 | AL | CL | DL | BL | AH | CH | DH | BH |
| 16位寄存器 | AX | CX | DX | BX | SP | BP | SI | DI |
| 32位寄存器 | EAX | ECX | EDX | EBX | ESP | EBP | ESI | EDI |

- Instruction一列中, `r/m8`表示操作数是8位的寄存器或内存, `r8`表示操作数是8位寄存器, 按照Intel格式的汇编语法来解释, 表示将8位寄存器(`r8`)中的数据传送到8位寄存器或内存(`r/m8`)中, 这和功能描述是一致的. 至于`r/m`表示的究竟是寄存器还是内存, 这是由`ModR/M`字节的`mod`域决定的: 当`mod`域取值为`3`的时候, `r/m`表示的是寄存器; 否则`r/m`表示的是内存. 表示内存的时候又有多种寻址方式, 具体信息参考i386手册中的表格17-3.

看明白了上面的第一种形式之后, 接下来的两种形式也就不难看懂了:

```
< 2> 89 /r        MOV r/m16,r16     2/2           Move word register to r/m word
< 3> 89 /r        MOV r/m32,r32     2/2           Move dword register to r/m dword
```

但你会发现, 这两种形式的`Opcode`都是一样的, 难道不会出现歧义吗? 不用着急, 还记得指令一般格式中的`operand-size prefix`吗? x86正是通过它来区分上面这两种形式的. `operand-size prefix`的编码是`0x66`, 作用是指示当前指令需要改变操作数的宽度. 在i386中, 通常来说, 如果这个前缀没有出现, 操作数宽度默认是32位; 当这个前缀出现的时候, 操作数宽度就要改变成16位 (也有相反的情况, 这个前缀的出现使得操作数宽度从16位变成32位, 但这种情况在i386中极少出现). 换句话说, 如果把一个开头为`89 ...`的比特串解释成指令, 它就应该被解释成`MOV r/m32,r32`的形式; 如果比特串的开头是`66 89...`, 它就应该被解释成`MOV r/m16,r16`.

#### 操作数宽度前缀的由来

i386是从[8086](http://en.wikipedia.org/wiki/Intel_8086)发展过来的. 8086是一个16位的时代, 很多指令的16位版本在当时就已经实现好了. 要踏进32位的新时代, 兼容就成了需要仔细考量的一个重要因素.

一种最直接的方法是让32位的指令使用新的操作码, 但这样1字节的操作码很快就会用光. 假设8086已经实现了200条16位版本的指令形式, 为了加入这些指令形式的32位版本, 这种做法需要使用另外200个新的操作码, 使得大部分指令形式的操作码需要使用两个字节来表示, 这样直接导致了32位的程序代码会变长. 现在你可能会觉得每条指令的长度增加一个字节也没什么大不了, 但在i386诞生的那个遥远的时代(你可以在i386手册的封面看到那个时代), 内存是一种十分珍贵的资源, 因此这种使用新操作码的方法并不是一种明智的选择.

Intel想到的解决办法就是引入操作数宽度前缀, 来达到操作码复用的效果. 当处理器工作在16位模式([实模式](http://en.wikipedia.org/wiki/Real_mode))下的时候, 默认执行16位版本的指令; 当处理器工作在32位模式([保护模式](http://en.wikipedia.org/wiki/Protected_mode))下的时候, 默认执行32位版本的指令. 当某些需要的时候, 才通过操作数宽度前缀来指示操作数的宽度. 这种方法最大的好处就是不需要引入额外的操作码, 从而也不会明显地使得程序代码变长. 虽然在NEMU里面可以使用很简单的方法来模拟这个功能, 但在真实的芯片设计过程中, CPU的译码部件需要增加很多逻辑才能实现.

到现在为止, <4>-<6>三种形式你也明白了:

```
< 4> 8A /r        MOV r8,r/m8       2/4           Move r/m byte to byte register
< 5> 8B /r        MOV r16,r/m16     2/4           Move r/m word to word register
< 6> 8B /r        MOV r32,r/m32     2/4           Move r/m dword to dword register
```

`<7>` 和 `<8>` 两种形式的mov指令涉及到段寄存器:

```
< 7> 8C /r        MOV r/m16,Sreg    2/2           Move segment register to r/m word
< 8> 8D /r        MOV Sreg,r/m16    2/5,pm=18/19  Move r/m word to segment register
```

PA中的x86去掉了段寄存器的实现, 我们可以忽略这两种形式的`mov`指令.

`<9>` - `<14>` 这6种形式涉及到一种新的操作数记号`moffs`:

```
< 9> A0           MOV AL,moffs8     4             Move byte at (seg:offset) to AL
<10> A1           MOV AX,moffs16    4             Move word at (seg:offset) to AX
<11> A1           MOV EAX,moffs32   4             Move dword at (seg:offset) to EAX
<12> A2           MOV moffs8,AL     2             Move AL to (seg:offset)
<13> A3           MOV moffs16,AX    2             Move AX to (seg:offset)
<14> A3           MOV moffs32,EAX   2             Move EAX to (seg:offset)
---------------------------------------------------------------------------
NOTES:
moffs8, moffs16, and moffs32 all consist of a simple offset relative
to the segment base. The 8, 16, and 32 refer to the size of the data. The
address-size attribute of the instruction determines the size of the
offset, either 16 or 32 bits.
---------------------------------------------------------------------------
```

NOTES中给出了`moffs`的含义, 它用来表示段内偏移量, 但PA中的x86没有"段"的概念, 目前可以理解成"相对于物理地址0处的偏移量". 这6种形式是`mov`指令的特殊形式, 它们可以不通过`ModR/M`字节, 让`displacement`直接跟在`opcode`后面, 同时让`displacement`来指示一个内存地址.

`<15>` - `<17>` 三种形式涉及到两种新的操作数记号:

```
<15> B0 + rb ib   MOV r8,imm8       2             Move immediate byte to register
<16> B8 + rw iw   MOV r16,imm16     2             Move immediate word to register
<17> B8 + rd id   MOV r32,imm32     2             Move immediate dword to register
```

其中:

- `+rb`, `+rw`, `+rd`分别表示8位, 16位, 32位通用寄存器的编码. 和`ModR/M`中的`reg`域不一样的是, 这三种记号表示直接将通用寄存器的编号按数值加到`opcode`中 (也可以看成通用寄存器的编码嵌在`opcode`的低三位), 因此识别指令的时候可以通过`opcode`的低三位确定一个寄存器操作数.
- `ib`, `iw`, `id`分别表示8位, 16位, 32位立即数

最后3种形式涉及到一种新的操作码记号`/digit`, 其中`digit`为`0`~`7`中的一个数字:

```
<18> C6 /0 ib (*) MOV r/m8,imm8     2/2           Move immediate byte to r/m byte
<19> C7 /0 iw (*) MOV r/m16,imm16   2/2           Move immediate word to r/m word
<20> C7 /0 id (*) MOV r/m32,imm32   2/2           Move immediate dword to r/m dword

注:
标记了(*)的指令形式的Opcode相对于i386手册有改动, 具体情况见下文的描述.
```

上述形式中的`/0`表示一个`ModR/M`字节, 并且`ModR/M`字节中的`reg/opcode`域解释成扩展opcode, 其值取`0`. 对于含有`/digit`记号的指令形式, 需要通过指令本身的`opcode`和`ModR/M`中的扩展opcode共同决定指令的形式, 例如`80 /0`表示`add`指令的一种形式, 而`80 /5`则表示`sub`指令的一种形式, 只看`opcode`的首字节`80`不能区分它们.

注: 在i386手册中, 这3种形式的`mov`指令并没有`/0`的记号, 在这里加入`/0`纯粹是为了说明`/digit`记号的意思. 但同时这条指令在i386中也比较特殊, 它需要使用`ModR/M`字节来表示一个寄存器或内存的操作数, 但`ModR/M`字节中的`reg/opcode`域却没有用到 (一般情况下, `ModR/M`字节中的`reg/opcode`域要么表示一个寄存器操作数, 要么作为扩展opcode), i386手册也没有对此进行特别的说明, 直觉上的解释就是"无论`ModR/M`字节中的`reg/opcode`域是什么值, 都可以被CPU识别成这种形式的`mov`指令". x86是商业CPU, 我们无法从电路级实现来考证这一解释, 但对编译器生成代码来说, 这条指令中的`reg/opcode`域总得有个确定的值, 因此编译器一般会把这个值设成`0`. 在NEMU的框架代码中, 对这3种形式的`mov`指令的实现和i386手册中给出`Opcode`保持一致, 忽略`ModR/M`字节中的`reg/opcode`域, 没有判断其值是否为`0`. 如果你不能理解这段话在说什么, 你可以忽略它, 因为这并不会影响实验的进行.

到此为止, 你已经学会了如何阅读大部分的指令集细节了. 需要说明的是, 这里举的`mov`指令的例子并没有完全覆盖i386手册中指令集细节的所有记号, 若有疑问, 请参考i386手册.

除了opcode表之外, `Operation`, `Description`和`Flags Affected`这三个条目都要仔细阅读, 这样你才能完整地掌握一条指令的功能. `Exceptions`条目涉及到执行这条指令可能产生的异常, 由于PA中的x86不打算加入异常处理的机制, 你可以不用关心这一条目.


---

> 来源：[https://ysyx.oscc.cc/docs/ics-pa/linux.html](https://ysyx.oscc.cc/docs/ics-pa/linux.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# Linux入门教程

以下内容引用自jyy的操作系统实验课程网站, 并有少量修改和补充. 如果你是第一次使用Linux, 请你一边仔细阅读教程, 一边尝试运行教程中提到的命令.

## 探索命令行

Linux命令行中的命令使用格式都是相同的:

```
命令名称 参数1 参数2 参数3 ...
```

参数之间用任意数量的空白字符分开. 关于命令行, 可以先阅读[一些基本常识](https://linux.cn/article-6160-1.html). 然后我们介绍最常用的一些命令:

- `ls`用于列出当前目录(即"文件夹")下的所有文件(或目录). 目录会用蓝色显示. `ls -l`可以显示详细信息.
- `pwd`能够列出当前所在的目录.
- `cd DIR`可以切换到`DIR`目录. 在Linux中, 每个目录中都至少包含两个目录: `.`指向该目录自身, `..`指向它的上级目录. 文件系统的根是`/`.
- `touch NEWFILE`可以创建一个内容为空的新文件`NEWFILE`, 若`NEWFILE`已存在, 其内容不会丢失.
- `cp SOURCE DEST`可以将`SOURCE`文件复制为`DEST`文件; 如果`DEST`是一个目录, 则将`SOURCE`文件复制到该目录下.
- `mv SOURCE DEST`可以将`SOURCE`文件重命名为`DEST`文件; 如果`DEST`是一个目录, 则将`SOURCE`文件移动到该目录下.
- `mkdir DIR`能够创建一个`DIR`目录.
- `rm FILE`能够删除`FILE`文件; 如果使用`-r`选项则可以递归删除一个目录. 删除后的文件无法恢复, 使用时请谨慎!
- `man`可以查看命令的帮助. 例如`man ls`可以查看`ls`命令的使用方法. 灵活应用`man`和互联网搜索, 可以快速学习新的命令.

`man`的功能不仅限于此. `man`后可以跟两个参数, 可以查看不同类型的帮助(请在互联网上搜索). 例如当你不知道C标准库函数`freopen`如何使用时, 可以键入命令

```
man 3 freopen
```

#### 学会使用man

如果你是第一次使用`man`, 请阅读[这里](#). 这个教程除了说明如何使用`man`之外, 还会教你在使用一款新的命令行工具时如何获得帮助.

#### 消失的cd

上述各个命令除了`cd`之外都能找到它们的manpage, 这是为什么? 如果你思考后仍然感到困惑, 试着到互联网上寻找答案.

下面给出一些常用命令使用的例子, 你可以键入每条命令之后使用`ls`查看命令执行的结果:

```
$ mkdir temp      # 创建一个目录temp
$ cd temp         # 切换到目录temp
$ touch newfile   # 创建一个空文件newfile
$ mkdir newdir    # 创建一个目录newdir
$ cd newdir       # 切换到目录newdir
$ cp ../newfile . # 将上级目录中的文件newfile复制到当前目录下
$ cp newfile aaa  # 将文件newfile复制为新文件aaa
$ mv aaa bbb      # 将文件aaa重命名为bbb
$ mv bbb ..       # 将文件bbb移动到上级目录
$ cd ..           # 切换到上级目录
$ rm bbb          # 删除文件bbb
$ cd ..           # 切换到上级目录
$ rm -r temp      # 递归删除目录temp
```

#### 更多的命令行知识

仅仅了解这些最基础的命令行知识是不够的. 通常, 我们可以抱着如下的信条: 只要我们能想到的, 就一定有方便的办法能够办到. 因此当你想要完成某件事却又不知道应该做什么的时候, 请向Google求助. 如果你想以Linux作为未来的事业, 那就可以去图书馆或互联网上找一些相关的书籍来阅读.

## 统计代码行数

第一个例子是统计一个目录中(包含子目录)中的代码行数. 如果想知道当前目录下究竟有多少行的代码, 就可以在命令行中键入如下命令:

```
find . | grep '\.c$\|\.h$' | xargs wc -l
```

如果用`man find`查看`find`操作的功能, 可以看到`find`是搜索目录中的文件. Linux中一个点`.`始终表示Shell当前所在的目录, 因此`find .`实际能够列出当前目录下的所有文件. 如果在文件很多的地方键入`find .`, 将会看到过多的文件, 此时可以按`CTRL + c`退出.

同样, 用`man`查看`grep`的功能——"print lines matching a pattern". `grep`实现了输入的过滤, 我们的`grep`有一个参数, 它能够匹配以`.c`或`.h`结束的文件. 正则表达式是处理字符串非常强大的工具之一, 每一个程序员都应该掌握其相关的知识. 有兴趣的同学可以首先阅读一个[基础的教程](https://linux.vbird.org/linux_basic/centos7/0330regularex.php), 然后看一个有趣的小例子: [如何用正则表达式判定素数](http://coolshell.cn/articles/2704.html). 正则表达式还可以用来编写一个30行的java表达式求值程序(传统方法几乎不可能), 聪明的你能想到是怎么完成的吗? 上述的`grep`命令能够提取所有`.c`和`.h`结尾的文件.

刚才的`find`和`grep`命令, 都从标准输入中读取数据, 并输出到标准输出. 关于什么是标准输入输出, 请参考[这里](http://en.wikipedia.org/wiki/Standard_streams). 连接起这两个命令的关键就是管道符号`|`. 这一符号的左右都是Shell命令, `A | B`的含义是创建两个进程`A`和`B`, 并将`A`进程的标准输出连接到`B`进程的标准输入. 这样, 将`find`和`grep`连接起来就能够筛选出当前目录(`.`)下所有以`.c`或`.h`结尾的文件.

我们最后的任务是统计这些文件所占用的总行数, 此时可以用`man`查看`wc`命令. `wc`命令的`-l`选项能够计算代码的行数. `xargs`命令十分特殊, 它能够将标准输入转换为参数, 传送给第一个参数所指定的程序. 所以, 代码中的`xargs wc -l`就等价于执行`wc -l aaa.c bbb.c include/ccc.h ...`, 最终完成代码行数统计.

## 统计磁盘使用情况

以下命令统计`/usr/share`目录下各个目录所占用的磁盘空间:

```
du -sc /usr/share/* | sort -nr
```

`du`是磁盘空间分析工具, `du -sc`将目录的大小顺次输出到标准输出, 继而通过管道传送给`sort`. `sort`是数据排序工具, 其中的选项`-n`表示按照数值进行排序, 而`-r`则表示从大到小输出. `sort`可以将这些参数连写在一起.

然而我们发现, `/usr/share`中的目录过多, 无法在一个屏幕内显示. 此时, 我们可以再使用一个命令: `more`或`less`.

```
du -sc /usr/share/* | sort -nr | more
```

此时将会看到输出的前几行结果. `more`工具使用空格翻页, 并可以用`q`键在中途退出. `less`工具则更为强大, 不仅可以向下翻页, 还可以向上翻页, 同样使用`q`键退出. 这里还有一个[关于less的小故事](http://en.wikipedia.org/wiki/Less_(Unix)).

## 在Linux下编写Hello World程序

Linux中用户的主目录是`/home/用户名称`, 如果你的用户名是`user`, 你的主目录就是`/home/user`. 用户的`home`目录可以用波浪符号`~`替代, 例如临时文件目录`/home/user/Templates`可以简写为`~/Templates`. 现在我们就可以进入主目录并编辑文件了. 如果`Templates`目录不存在, 可以通过`mkdir`命令创建它:

```
cd ~
mkdir Templates
```

创建成功后, 键入

```
cd Templates
```

可以完成目录的切换. 注意在输入目录名时, `tab`键可以提供联想.

#### 你感到键入困难吗?

你可能会经常要在终端里输入类似于

```
cd AVeryVeryLongFileName
```

的命令, 你一定觉得非常烦躁. 回顾上面所说的原则之一: 如果你感到有什么地方不对, 就一定有什么好办法来解决. 试试`tab`键吧.

Shell中有很多这样的小技巧, 你也可以使用其他的Shell例如zsh, 提供更丰富好用的功能. 总之, 尝试和改变是最重要的.

进入正确的目录后就可以编辑文件了, 开源世界中主流的两大编辑器是`vi(m)`和`emacs`, 你可以使用其中的任何一种. 如果你打算使用`emacs`, 你还需要安装它

```
apt-get install emacs
```

`vi`和`emacs`这两款编辑器都需要一定的时间才能上手, 它们共同的特点是需要花较多的时间才能适应基本操作方式(命令或快捷键), 但一旦熟练运用, 编辑效率就比传统的编辑器快很多.

进入了正确的目录后, 输入相应的命令就能够开始编辑文件. 例如输入

```
vi hello.c
或emacs hello.c
```

就能开启一个文件编辑. 例如可以键入如下代码(对于首次使用`vi`或`emacs`的同学, 键入代码可能会花去一些时间, 在编辑的同时要大量查看网络上的资料):

```
#include <stdio.h>
int main(void) {
  printf("Hello, Linux World!\n");
  return 0;
}
```

保存后就能够看到`hello.c`的内容了. 终端中可以用`cat hello.c`查看代码的内容. 如果要将它编译, 可以使用`gcc`命令:

```
gcc hello.c -o hello
```

`gcc`的`-o`选项指定了输出文件的名称, 如果将`-o hello`改为`-o hi`, 将会生成名为`hi`的可执行文件. 如果不使用`-o`选项, 则会默认生成名为`a.out`的文件, 它的含义是[assembler output](http://en.wikipedia.org/wiki/A.out). 在命令行输入

```
./hello
```

就能够运行该程序. 命令中的`./`是不能少的, 点代表了当前目录, 而`./hello`则表示当前目录下的`hello`文件. 与Windows不同, Linux系统默认情况下并不查找当前目录, 这是因为Linux下有大量的标准工具(如`test`等), 很容易与用户自己编写的程序重名, 不搜索当前目录消除了命令访问的歧义.

## 使用重定向

有时我们希望将程序的输出信息保存到文件中, 方便以后查看. 例如你编译了一个程序`myprog`, 你可以使用以下命令对`myprog`进行反汇编, 并将反汇编的结果保存到`output`文件中:

```
objdump -d myprog > output
```

`>`是标准输出重定向符号, 可以将前一命令的输出重定向到文件`output`中. 这样, 你就可以使用文本编辑工具查看`output`了.

但你会发现, 使用了输出重定向之后, 屏幕上就不会显示`myprog`输出的任何信息. 如果你希望输出到文件的同时也输出到屏幕上, 你可以使用`tee`命令:

```
objdump -d myprog | tee output
```

使用输出重定向还能很方便地实现一些常用的功能, 例如

```
> empty                  # 创建一个名为empty的空文件
cat old_file > new_file  # 将文件old_file复制一份, 新文件名为new_file
```

如果`myprog`需要从键盘上读入大量数据(例如一个图的拓扑结构), 当你需要反复对`myprog`进行测试的时候, 你需要多次键入大量相同的数据. 为了避免这种无意义的重复键入, 你可以使用以下命令:

```
./myprog < data
```

`<`是标准输入重定向符号, 可以将前一命令的输入重定向到文件`data`中. 这样, 你只需要将`myprog`读入的数据一次性输入到文件`data`中, `myprog`就会从文件`data`中读入数据, 节省了大量的时间.

下面给出了一个综合使用重定向的例子:

```
time ./myprog < data | tee output
```

这个命令在运行`myprog`的同时, 指定其从文件`data`中读入数据, 并将其输出信息打印到屏幕和文件`output`中. `time`工具记录了这一过程所消耗的时间, 最后你会在屏幕上看到`myprog`运行所需要的时间. 如果你只关心`myprog`的运行时间, 你可以使用以下命令将`myprog`的输出过滤掉:

```
time ./myprog < data > /dev/null
```

`/dev/null`是一个特殊的文件, 任何试图输出到它的信息都会被丢弃, 你能想到这是怎么实现的吗? 总之, 上面的命令将`myprog`的输出过滤掉, 保留了`time`的计时结果, 方便又整洁.

## 使用Makefile管理工程

大规模的工程中通常含有几十甚至成百上千个源文件(Linux内核源码有25000+的源文件), 分别键入命令对它们进行编译是十分低效的. Linux提供了一个高效管理工程文件的工具: GNU Make. 我们首先从一个简单的例子开始, 考虑上文提到的Hello World的例子, 在`hello.c`所在目录下新建一个文件`Makefile`, 输入以下内容并保存:

```
hello:hello.c
	gcc hello.c -o hello	# 注意开头的tab, 而不是空格

.PHONY: clean

clean:
	rm hello	# 注意开头的tab, 而不是空格
```

返回命令行, 键入`make`, 你会发现`make`程序调用了`gcc`进行编译. `Makefile`文件由若干规则组成, 规则的格式一般如下:

```
目标文件名:依赖文件列表
	用于生成目标文件的命令序列   # 注意开头的tab, 而不是空格
```

我们来解释一下上文中的`hello`规则. 这条规则告诉`make`程序, 需要生成的目标文件是`hello`, 它依赖于文件`hello.c`, 通过执行命令`gcc hello.c -o hello`来生成`hello`文件.

如果你连续多次执行`make`, 你会得到"文件已经是最新版本"的提示信息, 这是`make`程序智能管理的功能. 如果目标文件已经存在, 并且它比所有依赖文件都要"新", 用于生成目标的命令就不会被执行. 你能想到`make`程序是如何进行"新"和"旧"的判断的吗?

上面例子中的`clean`规则比较特殊, 它并不是用来生成一个名为`clean`的文件, 而是用于清除编译结果, 并且它不依赖于其它任何文件. `make`程序总是希望通过执行命令来生成目标, 但我们给出的命令`rm hello`并不是用来生成`clean`文件, 因此这样的命令总是会被执行. 你需要键入`make clean`命令来告诉`make`程序执行`clean`规则, 这是因为`make`默认执行在`Makefile`中文本序排在最前面的规则. 但如果很不幸地, 目录下已经存在了一个名为`clean`的文件, 执行`make clean`会得到"文件已经是最新版本"的提示. 解决这个问题的方法是在`Makefile`中加入一行`PHONY: clean`, 用于指示"`clean`是一个伪目标". 这样以后, `make`程序就不会判断目标文件的新旧, 伪目标相应的命令序列总是会被执行.

对于一个规模稍大一点的工程, `Makefile`文件还会使用变量, 函数, 调用Shell命令, 隐含规则等功能. 如果你希望学习如何更好地编写一个`Makefile`, 请到互联网上搜索相关资料.

## 综合示例: 教务刷分脚本

使用编辑器编辑文件`jw.sh`为如下内容(另外由于教务网站的升级改版, 目前此脚本可能不能实现正确的功能):

```
#!/bin/bash
save_file="score" # 临时文件
semester=20102 # 刷分的学期, 20102代表2010年第二学期
jw_home="http://jwas3.nju.edu.cn:8080/jiaowu" # 教务网站首页地址
jw_login="http://jwas3.nju.edu.cn:8080/jiaowu/login.do" # 登录页面地址
jw_query="http://jwas3.nju.edu.cn:8080/jiaowu/student/studentinfo/achievementinfo.do?method=searchTermList&termCode=$semester" # 分数查询页面地址

name="09xxxxxxx" # 你的学号
passwd="xxxxxxxx" # 你的密码

# 请求jw_home地址, 并从中找到返回的cookie. cookie信息在http头中的JSESSIONID字段中
cookie=`wget -q -O - $jw_home --save-headers | \
    sed -n 's/Set-Cookie: JSESSIONID=\([0-9A-Z]\+\);.*$/\1/p'`
# 用户登录, 使用POST方法请求jw_login地址, 并在POST请求中加入userName和password
wget -q -O - --header="Cookie:JSESSIONID=$cookie" --post-data \
    "userName=${name}&password=${passwd}" "$jw_login" &> /dev/null
# 登录完毕后, 请求分数查询页面. 此时会返回html页面并输出到标准输出. 我们将输出重定向到文件"tmp"中.
wget -q -O - --header="Cookie:JSESSIONID=$cookie" "$jw_query" > tmp
# 获取分数列表. 因为教务网站的代码实在是实现得不太规整, 我们又想保留shell的风味, 所以用了比较繁琐的sed和awk处理. list变量中会包含课程名称的列表.
list=`cat tmp | sed -n '/<table.*TABLE_BODY.*>/,/<\/table>/p' \
        | sed '/<--/,/-->/d' | grep td \
        | awk 'NR%11==3' | sed 's/^.*>\(.*\)<.*$/\1/g'`
# 对list中的每一门课程, 都得到它的分数
for item in $list; do
    score=`cat tmp | grep -A 20 $item | awk "NR==18" | sed -n '/^.*\..*$/p'`
    score=`echo $score`
    if [[ ${#score} != 0 ]]; then # 如果存在成绩
        grep $item $save_file &>/dev/null # 查找分数是否显示过
        if [[ $? != 0 ]]; then # 如果没有显示过
        # 考虑到尝试的同学可能没有安装notify-send工具, 这里改成echo  -- yzh
            # notify-send "新成绩：$item $score" # 弹出窗口显示新成绩
            echo "新成绩：$item $score" # 在终端里输出新成绩
            echo $item >> $save_file # 将课程标记为已显示
        fi
    fi
done
```

运行这个例子需要在命令行中输入`bash jw.sh`, 用bash解释器执行这一脚本. 如果希望定期运行这一脚本, 可以使用Linux的标准工具之一: `cron`. 将命令添加到crontab就能实现定期自动刷新.

为了理解这个例子, 首先需要一些HTTP协议的基础知识. HTTP请求实际就是来回传送的文本流——浏览器(或我们例子中的爬虫)生成一个文本格式的HTTP请求, 包括header和content, 以文本的形式通过网络传送给服务器. 服务器根据请求内容(header中包含请求的URL以及浏览器等其他信息), 生成页面并返回.

用户登录的实现, 就是通过HTTP头中header中的cookie实现的. 当浏览器第一次请求页面时, 服务器会返回一串字符, 用来标识浏览器的这次访问. 从此以后, 所有与该网站交互时, 浏览器都会在HTTP请求的header中加入这个字符串, 这样服务器就"记住"了浏览器的访问. 当完成登录操作(将用户名和密码发送到服务器)后, 服务器就知道这个cookie隐含了一个合法登录的帐号, 从而能够根据帐号信息发送成绩.

得到包含了成绩信息的html文档之后, 剩下的事情就是解析它了. 我们用了大量的`sed`和`awk`完成这件事情, 同学们不用去深究其中的细节, 只需知道我们从文本中提取出了课程名和成绩, 并且将没有显示过的成绩显示出来.

我们讲解这个例子主要是为了说明新环境下的工作方式, 以及实践Unix哲学:

- 每个程序只做一件事, 但做到极致
- 用程序之间的相互协作来解决复杂问题
- 每个程序都采用文本作为输入和输出, 这会使程序更易于使用

一个Linux老手可以用脚本完成各式各样的任务: 在日志中筛选想要的内容, 搭建一个临时HTTP服务器(核心是使用`nc`工具)等等. 功能齐全的标准工具使Linux成为工程师, 研究员和科学家的最佳搭档.


---

> 来源：[https://ysyx.oscc.cc/docs/ics-pa/man.html](https://ysyx.oscc.cc/docs/ics-pa/man.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# man快速入门

这是一个man的使用教程, 同时给出了一个如何寻找帮助的例子.

## 初识man

你是一只Linux菜鸟. 因为课程实验所迫, 你不得不使用Linux, 不得不使用十分落后的命令行. 实验内容大多数都要在命令行里进行, 面对着一大堆陌生的命令和参数, [这个链接](http://tieba.baidu.com/p/1410532522)中的饼图完美地表达了你的心情.

不行! 还是得认真做实验, 不然以后连码农都当不上了! 这样的想法鞭策着你, 因为你知道, 就算是码农, 也要有适应新环境和掌握新工具的能力. "还是先去找man吧." 于是你在终端里输入`man`, 敲了回车. 只见屏幕上输出了一行信息:

> What manual page do you want?

噢, 原来命令行也会说人话! 你明白这句话的意思, `man`在询问你要查询什么内容. 你能查询什么内容呢? 既然`man`会说人话, 还是先多了解`man`吧. 为了告诉`man`你想更了解ta, 你输入

```
man man
```

敲了回车之后, `man`把你带到了一个全新的世界. 这时候, 你又看到了一句人话了, 那是`man`的独白, ta告诉你, ta的真实身份其实是

> an interface to the on-line reference manuals

接下来, ta忽然说了一大堆你听不懂的话, 似乎是想告诉你ta的使用方法. 可是你还没做好心理准备啊, 于是你无视了这些话.

## 寻找帮助

很快, 你已经看到"最后一行"了. 难道man的世界就这么狭小? 你仔细一看, "最后一行"里面含有一些信息:

> Manual page man(1) line 1 (press h for help or q to quit)

原来可以通过按`q`来离开这个世界啊, 不过你现在并不想这么做, 因为你想多了解`man`, 以后可能会经常需要`man`的帮助. 为了更了解ta, 你按了`h`.

这时你又被带到了新的世界, 世界的起点是"SUMMARY OF LESS COMMANDS", 你马上知道, 这个世界要告诉你如何使用`man`, 你十分激动. 于是你往下看, 这句话说"带有'\*'标记的命令可以在前面跟一个数, 这时命令的行为在括号里给出". 这是什么意思? 你没看懂, 还是找个带'\*'的命令试试吧. 你继续往下看, 看到了两个功能和相应的命令:

- 第一个是展示帮助, 原来除了`h`之外, `H`也可以看到帮助, 而且这里把帮助的命令放在第一个, 也许`man`想暗示你, 找到帮助是十分重要的.
- 第二个命令是退出. "哈哈, 知道怎么退出之后, 就不用通过重启来退出一个命令行程序啦", 你心想. 但你现在还是不想退出, 还是再看看其它的吧.

继续往下看, 你看到了用于移动的命令. 果然, 你还是可以在这个世界里面移动的. 第一个用于移动的功能是往下移动一行, 你看到有5种方法可以实现:

```
e  ^E  j  ^N  CR
```

`e`和`j`你看懂了, 就是按`e`或者`j`. 但`^E`是什么意思呢? 你尝试找到`^`的含义, 但是你没找到, 还是让我告诉你吧. 在上下文和按键有关的时候, `^`是Linux中的一个传统记号, 它表示`ctrl+`. 还记得Windows下`ctrl+c`代表复制的例子吗? 这里的`^E`表示`ctrl+E`. `CR`代表回车键, 其实`CR`是控制字符(ASCII码小于32的字符)的一个, [这里](http://stackoverflow.com/questions/3091524/what-are-carriage-return-linefeed-and-form-feed)有一段关于控制字符的问答.

你决定使用`j`, 因为它像一个向下的箭头, 而且它是右手食指所按下的键. 其实这点和`vim`的使用是类似的, 如果你不能理解为什么`vim`中使用`h`, `j`, `k`, `l`作为方向键, 这里有一个[初学者的提问](http://stackoverflow.com/questions/7665246/do-i-save-time-using-the-h-j-k-l-keys). 事实上, 这是一种[touch typing](http://en.wikipedia.org/wiki/Touch_typing).

你按下了`j`, 发现画面上的信息向下滚动了一行. 你看到了`*`, 想起了`*`标记的命令可以在前面跟一个数. 于是你试着输入`10j`, 发现画面向下滚动了10行, 你第一次感觉到在这个"丑陋"的世界中也有比GUI方便的地方. 你继续阅读帮助, 并且尝试每一个命令. 于是你掌握了如何通过移动来探索`man`所在的世界.

继续往下翻, 你看到了用于搜索的命令. 你十分感动, 因为使用关键字可以快速定位到你关心的内容. 帮助的内容告诉你, 通过按`/`激活前向搜索模式, 然后输入关键字(可以使用正则表达式), 按下回车就可以看到匹配的内容了. 帮助中还列出了后向搜索, 跳到下一匹配处等功能. 于是你掌握了如何使用搜索.

## 探索man

你一边阅读帮助, 一边尝试新的命令, 就这样探索着这个陌生的世界. 你虽然记不住这么多命令, 但你知道你可以随时来查看帮助. 掌握了一些基本的命令之后, 你按`q`离开了帮助, 回到了`man`的世界. 现在你可以自由探索`man`的世界了. 你向下翻, 跳过了看不懂的`SYNOPSIS`小节, 在`DESCRIPTION`小节看到了人话, 于是你阅读这些人话. 在这里, 你看到整个manual分成9大类, 每个manual page都属于其中的某一类; 你看到了一个manual page主要包含以下的小节:

- NAME - 命令名
- SYNOPSIS - 使用方法大纲
- CONFIGURATION - 配置
- DESCRIPTION - 功能说明
- OPTIONS - 可选参数说明
- EXIT STATUS - 退出状态, 这是一个返回给父进程的值
- RETURN VALUE - 返回值
- ERRORS - 可能出现的错误类型
- ENVIRONMENT - 环境变量
- FILES - 相关配置文件
- VERSIONS - 版本
- CONFORMING TO - 符合的规范
- NOTES - 使用注意事项
- BUGS - 已经发现的bug
- EXAMPLE - 一些例子
- AUTHORS - 作者
- SEE ALSO - 功能或操作对象相近的其它命令

你还看到了对`SYNOPSIS`小节中记号的解释, 现在你可以回过头来看`SYNOPSIS`的内容了. 但为了弄明白每个参数的含义, 你需要查看`OPTIONS`小节中的内容.

你想起了搜索的功能, 为了弄清楚参数`-k`的含义, 你输入`/-k`, 按下回车, 并通过`n`跳过了那些`OPTIONS`小节之外的`-k`, 最后大约在第254行找到了`-k`的解释: 通过关键字来搜索相关功能的manual page. 在`EXAMPLES`小节中有一个使用`-k`的例子:

```
man -k printf
```

你阅读这个例子的解释: 搜索和`printf`相关的manual page. 你还是不太明白这是什么意思, 于是你退出`man`, 在命令行中输入

```
man -k printf
```

并运行, 发现输出了很多和`printf`相关的命令或库函数, 括号里面的数字代表相应的条目属于manual的哪一个大类. 例如`printf (1)`是一个shell命令, 而`printf (3)`是一个库函数. 要访问库函数`printf`的manual page, 你需要在命令行中输入

```
man 3 printf
```

当你想做一件事的而不知道用什么命令的时候, `man`的`-k`参数可以用来列出候选的命令, 然后再通过查看这些命令的manual page来学习怎么使用它们.

接下来, 你又开始学习`man`的其它功能...

## 开始旅程

到这里, 你应该掌握`man`的用法了. 你应该经常来拜访ta, 因为在很多时候, ta总能给你提供可靠的帮助.

在这个励志的故事中, 你学会了:

- 阅读程序输出的提示和错误信息
- 通过搜索来定位你关心的内容
- 动手实践是认识新事物的最好方法
- 独立寻找帮助, 而不是一有问题就问班上的大神

于是, 你就这样带着 `man` 踏上了Linux之旅...


---

> 来源：[https://ysyx.oscc.cc/docs/ics-pa/nemu-isa-api.html](https://ysyx.oscc.cc/docs/ics-pa/nemu-isa-api.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# NEMU ISA相关的API说明文档

为了提高性能, 这些API也可以通过宏定义实现, 但本文档还是以C变量或函数的方式列出, 以给出变量或函数的类型.

### 全局类型

```
word_t;
```

表示与ISA字长等长的无符号类型, 在32位的ISA中为`uint32_t`, 在64位的ISA中为`uint64_t`.

---

```
sword_t;
```

表示与ISA字长等长的有符号类型, 在32位的ISA中为`int32_t`, 在64位的ISA中为`int64_t`.

---

```
char *FMT_WORD;
```

`word_t`类型对应的十六进制格式化说明符, 在32位的ISA中为`"0x%08x"`, 在64位的ISA中为`"0x%016lx"`.

### Monitor相关

```
unsigned char isa_logo[];
```

用于在未实现指令的报错信息中提示开发者阅读相关的手册.

---

```
word_t RESET_VECTOR;
```

表示PC的初始值.

---

```
void init_isa();
```

在monitor初始化时调用, 进行至少如下ISA相关的初始化工作:

- 设置必要的寄存器初值, 如`PC`等
- 加载内置客户程序

### 寄存器相关

```
struct {
  // ...
  word_t pc;
} CPU_state;
```

寄存器结构的类型定义, 其中必须包含一个名为`pc`, 类型为`word_t`的成员.

---

```
CPU_state cpu;
```

寄存器结构的全局定义.

---

```
void isa_reg_display();
```

用于打印寄存器当前的值.

---

```
word_t isa_reg_str2val(const char *name, bool *success);
```

若存在名称为`name`的寄存器, 则返回其当前值, 并设置`success`为`true`; 否则设置`success`为`false`.

### 指令执行相关

```
struct {
  // ...
} ISADecodeInfo;
```

用于存放ISA相关的译码信息, 会嵌入在译码信息结构体`Decode`的定义中.

---

```
int isa_exec_once(Decode *s);
```

取出`s->pc`指向的指令并译码执行, 同时更新`s->snpc`.

### 虚拟内存相关

```
int isa_mmu_check(vaddr_t vaddr, int len, int type);
```

检查当前系统状态下对内存区间为`[vaddr, vaddr + len)`, 类型为`type`的访问是否需要经过地址转换. 其中`type`可能为:

- `MEM_TYPE_IFETCH`: 取指令
- `MEM_TYPE_READ`: 读数据
- `MEM_TYPE_WRITE`: 写数据

函数返回值可能为:

- `MMU_DIRECT`: 该内存访问可以在物理内存上直接进行
- `MMU_TRANSLATE`: 该内存访问需要经过地址转换
- `MMU_FAIL`: 该内存访问失败, 需要抛出异常(如RISC架构不支持非对齐的内存访问)

---

```
paddr_t isa_mmu_translate(vaddr_t vaddr, int len, int type);
```

对内存区间为`[vaddr, vaddr + len)`, 类型为`type`的内存访问进行地址转换. 函数返回值可能为:

- `pg_paddr` | `MEM_RET_OK`: 地址转换成功, 其中`pg_paddr`为物理页面的地址(而不是`vaddr`翻译后的物理地址)
- `MEM_RET_FAIL`: 地址转换失败, 原因包括权限检查失败等不可恢复的原因, 一般需要抛出异常
- `MEM_RET_CROSS_PAGE`: 地址转换失败, 原因为访存请求跨越了页面的边界

### 中断异常相关

```
vaddr_t isa_raise_intr(word_t NO, vaddr_t epc);
```

抛出一个号码为`NO`的异常, 其中`epc`为触发异常的指令PC, 返回异常处理的出口地址.

---

```
word_t isa_query_intr();
```

查询当前是否有未处理的中断, 若有则返回中断号码, 否则返回`INTR_EMPTY`.

### DiffTest相关

```
bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc);
```

检查当前的寄存器状态是否与`ref_r`相同, 其中`pc`为`cpu.pc`的上一条动态指令的PC, 即`cpu.pc`的旧值. 如果状态相同, 则返回`true`, 否则返回`false`.

---

```
void isa_difftest_attach();
```

将当前的所有状态同步到REF, 并在之后的执行中开启DiffTest.


---

> 来源：[https://ysyx.oscc.cc/docs/ics-pa/why.html](https://ysyx.oscc.cc/docs/ics-pa/why.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# 为什么要学习计算机系统基础

### 一知半解

你已经学过`程序设计基础`课程了, 对于C和C++程序设计已有一定的基础. 但你会发现, 你可能还是不能理解以下程序的运行结果:

#### 数组求和

```
int sum(int a[ ], unsigned len) {
	int i, sum = 0;
	for (i = 0; i <= len-1; i++)
		sum += a[i];
	return sum;
}
```

当`len = 0`时, 执行`sum`函数的for循环时会发生`Access Violation`, 即"访问违例"异常. 但是, 当参数`len`说明为`int`型时, `sum`函数能正确执行, 为什么?

#### 整数的平方

若`x`和`y`为`int`型, 当`x = 65535`时, 则`y = x*x = -131071`. 为什么?

#### 多重定义符号

```
/*---main.c---*/
#include <stdio.h>
int d=100;
int x=200;
void p1(void);
int main() {
	p1();
	printf("d=%d,x=%d\n",d,x);
	return 0;
}

/*---p1.c---*/
double d;
void p1() {
	d=1.0;
}
```

在上述两个模块链接生成的可执行文件被执行时, `main`函数的`printf`语句打印出来的值是: `d=0,x=1072693248`. 为什么不是`d=100,x=200`?

#### 奇怪的函数返回值

```
double fun(int i) {
	volatile double d[1] = {3.14};
	volatile long int a[2];
	a[i] = 1073741824; /* Possibly out of bounds */
	return d[0];
}
```

从`fun`函数的源码来看, 每次返回的值应该都是`3.14`, 可是执行`fun`函数后发现其结果是:

- `fun(0)`和`fun(1)`为`3.14`
- `fun(2)`为`3.1399998664856`
- `fun(3)`为`2.00000061035156`
- `fun(4)`为`3.14`并会发生`访问违例` 这是为什么?

#### 时间复杂度和功能都相同的程序

```
void copyij(int src[2048][2048], int dst[2048][2048]) {
	int i,j;
	for (i = 0; i < 2048; i++)
		for (j = 0; j < 2048; j++)
			dst[i][j] = src[i][j];
}
void copyji(int src[2048][2048], int dst[2048][2048]) {
	  int i,j;
	  for (j = 0; j < 2048; j++)
		  for (i = 0; i < 2048; i++)
			  dst[i][j] = src[i][j];
}
```

上述两个功能完全相同的函数, 时间复杂度也完全一样, 但在Pentium 4处理器上执行时, 所测时间相差大约21倍. 这是为什么? 猜猜看是`copyij`更快还是`copyji`更快?

#### 网友贴出的一道百度招聘题

请给出以下C语言程序的执行结果, 并解释为什么.

```
#include <stdio.h>
int main() {
	double a = 10;
	printf("a = %d\n", a);
	return 0;
}
```

该程序在IA-32上运行时, 打印结果为`a=0`; 在x86-64上运行时, 打印出来的`a`是一个不确定值. 为什么?

#### 整数除法

以下两个代码段的运行结果是否一样呢?

- 代码段一:

```
int a = 0x80000000;
int b = a / -1;
printf("%d\n", b);
```

- 代码段二:

```
int a = 0x80000000;
int b = -1;
int c = a / b;
printf("%d\n", c);
```

代码段一的运行结果为`-2147483648`; 而代码段二的运行结果为`Floating point exception`. 显然, 代码段二运行时被检测到了"溢出"异常. 看似同样功能的程序为什么结果完全不同?

类似上面这些例子还可以举出很多. 从这些例子可以看出, 仅仅明白高级语言的语法和语义, 很多情况下是无法理解程序执行结果的.

### 站得高, 看得远

国内很多学校老师反映, 学完高级语言程序设计后会有一些学生不喜欢计算机专业了, 这是为什么? 从上述给出的例子应该可以找到部分答案, 如果一个学生经常对程序的执行结果百思不得其解, 那么他对应用程序开发必然产生恐惧心理, 也就对计算机专业逐渐失去兴趣. 其实, 程序的执行结果除了受编程语言的语法和语义影响外, 还与程序的执行机制息息相关. `计算机系统基础`课程主要描述程序的底层执行机制, 因此, 学完本课程后同学们就能很容易地理解各种程序的执行结果, 也就不会对程序设计失去信心了.

我们还经常听到学生问以下问题: 像地质系这些非计算机专业的学生自学JAVA语言等课程后也能找到软件开发的工作, 而我们计算机专业学生多学那么多课程不也只能干同样的事情吗? 我们计算机专业学生比其他专业自学计算机课程的学生强在哪里啊? 现在计算机学科发展这么快, 什么领域都和计算机相关, 为什么我们计算机学科毕业的学生真正能干的事也不多呢? ...

确实, 对于大部分计算机本科专业学生来说, 硬件设计能力不如电子工程专业学生, 行业软件开发和应用能力不如其他相关专业学生, 算法设计和分析基础又不如数学系学生. 那么, 计算机专业学生的特长在哪里? 我们认为计算机专业学生的优势之一在于计算机系统能力, 即具备计算机系统层面的认知与设计能力, 能从计算机系统的高度考虑和解决问题.

随着大规模数据中心(WSC)的建立和个人移动设备(PMD)的大量普及使用, 计算机发展进入了后PC时代, 呈现出"人与信息世界及物理世界融合"的趋势和网络化, 服务化, 普适化和智能化的鲜明特征. 后PC时代WSC, PMD和PC等共存, 使得原先基于PC而建立起来的专业教学内容, 已经远远不能反映现代社会对计算机专业人才的培养要求, 原先计算机专业人才培养强调"程序"设计也变为更强调"系统"设计.

后PC时代, 并行成为重要主题, 培养具有系统观的, 能够进行软, 硬件协同设计的软硬件贯通人才是关键. 而且, 后PC时代对于大量从事应用开发的应用程序员的要求也变得更高. 首先, 后PC时代的应用问题更复杂, 应用领域更广泛. 其次, 要能够编写出各类不同平台所适合的高效程序, 应用开发人员必需对计算机系统具有全面的认识, 必需了解不同系统平台的底层结构, 并掌握并行程序设计技术和工具.

下图描述了计算机系统抽象层的转换.

![cs-hierarchy](https://ysyx.oscc.cc/docs/assets/cs-hierarchy.d1e0f547.jpg)

从图中可以看出, 计算机系统由不同的抽象层构成, "计算"的过程就是不同抽象层转换的过程, 上层是下层的抽象, 而下层则是上层的具体实现. 计算机学科主要研究的是计算机系统各个不同抽象层的实现及其相互转换的机制, 计算机学科培养的应该主要是在计算机系统或在系统某些层次上从事相关工作的人才.

相比于其他专业, 计算机专业学生的优势在于对系统深刻的理解, 能够站在系统的高度考虑和解决应用问题, 具有系统层面的认知和设计能力, 包括:

- 能够对软, 硬件功能进行合理划分
- 能够对系统不同层次进行抽象和封装
- 能够对系统的整体性能进行分析和调优
- 能够对系统各层面的错误进行调试和修正
- 能够根据系统实现机理对用户程序进行准确的性能评估和优化
- 能够根据不同的应用要求合理构建系统框架等

要达到上述这些在系统层面上的分析, 设计, 检错和调优等系统能力, 显然需要提高学生对整个计算机系统实现机理的认识, 包括:

- 对计算机系统整机概念的认识
- 对计算机系统层次结构的深刻理解
- 对高级语言程序, ISA, OS, 编译器, 链接器等之间关系的深入掌握
- 对指令在硬件上执行过程的理解和认识
- 对构成计算机硬件的基本电路特性和设计方法等的基本了解等 从而能够更深刻地理解时空开销和权衡, 抽象和建模, 分而治之, 缓存和局部性, 吞吐率和时延, 并发和并行, 远程过程调用(RPC), 权限和保护等重要的核心概念, 掌握现代计算机系统中最核心的技术和实现方法.

`计算机系统基础`课程的主要教学目标是培养学生的系统能力, 使其成为一个"高效"程序员, 在程序调试, 性能提升, 程序移植和健壮性等方面成为高手; 建立扎实的计算机系统概念, 为后续的OS, 编译, 体系结构等课程打下坚实基础.

### 实践是检验真理的唯一标准

旷日持久的计算机教学只为解答三个问题：

- (theory, 理论计算机科学) 什么是计算?
- (system, 计算机系统) 什么是计算机?
- (application, 计算机应用) 我们能用计算机做什么?

除了纯理论工作之外, 计算机相关的工作无不强调动手实践的能力. 很多时候, 你会觉得理解某一个知识点是一件简单是事情, 但当你真正动手实践的时候, 你才发现你的之前的理解只是停留在表面. 例如你知道链表的基本结构, 但你能写出一个正确的链表程序吗? 你知道程序加载的基本原理, 但你能写一个加载器来加载程序吗? 你知道编译器, 操作系统, CPU的基本功能, 但你能写一个编译器, 操作系统, CPU吗? 你甚至会发现, 虽然你在程序设计课上写过很多程序, 但你可能连下面这个看似很简单的问题都无法回答:

#### 终极拷问

当你运行一个Hello World程序的时候, 计算机究竟做了些什么?

很多东西说起来简单, 但做起来却不容易, 动手实践会让你意识到你对某些知识点的一知半解, 同时也给了你深入挖掘其中的机会, 你会在实践过程中发现很多之前根本没有想到过的问题(其实科研也是如此), 解决这些问题反过来又会加深你对这些知识点的理解. 理论知识和动手实践相互促进, 最终达到对知识点透彻的理解.

目前也有以下观点:

> 目前像VS, Eclipse这样的IDE功能都十分强大, 点个按钮就能编译, 拖动几个控件就能设计一个GUI程序, 为什么还需要学习程序运行的机理?
>
> PhotoShop里面的滤镜功能繁多, 随便点点就能美化图片, 为什么还需要学习图像处理的基本原理?

像"GUI程序开发", "PhotoShop图片美化"这样的工作也确实需要动手实践, 但它们并不属于上文提到的计算机应用的范畴, 也不是计算机本科教育的根本目的, 因为它们强调的更多是技能的培训, 而不是对"计算机能做什么"这个问题的探索, 这也是培训班教学和计算机本科教学的根本区别. 但如果你对GUI程序运行的机理了如指掌, 对图像处理基本原理的理解犹如探囊取物, 上述工作对你来说根本就不在话下, 甚至你还有能力参与Eclipse和PhotoShop的开发.

而对这些原理的透彻理解, 离不开动手实践.

#### 宋公语录

学汽车制造专业是要学发动机怎么设计, 学开车怎么开得过司机呢?
