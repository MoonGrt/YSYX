> 来源：[https://ysyx.oscc.cc/docs/ics-pa/PA0.html](https://ysyx.oscc.cc/docs/ics-pa/PA0.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# PA0 - 世界诞生的前夜: 开发环境配置

#### 世界诞生的故事 - 序章

PA讲述的是一个"先驱创造计算机"的故事.

先驱打算创造一个计算机世界. 但巧妇难为无米之炊, 为了更方便地创造这个世界, 就算是先驱也是花了一番功夫来准备的. 让我们来看看他都准备了些什么工具.

#### 提交要求(请认真阅读以下内容, 若有违反, 后果自负)

**预计平均耗时**: 10小时


---

> 来源：[https://ysyx.oscc.cc/docs/ics-pa/0.1.html](https://ysyx.oscc.cc/docs/ics-pa/0.1.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# Preparation

PA0 is a guide to GNU/Linux development environment configuration. You are guided to install a GNU/Linux development environment. All PAs and Labs are done in this environment. If you are new to GNU/Linux, and you encounter some troubles during the configuration, which are not mentioned in this lecture note (such as "No such file or directory"), that is your fault. Go back to read this lecture note carefully. Remember, the machine is always right!

#### 信息框说明

讲义中会出现一些信息框, 根据其颜色和左上角的图标可以得知信息的类别. 例如本信息框就是一些提示相关的内容. 其它类别主要还有

#### 实验进度相关的提示

#### 扩展阅读

#### 选做思考题

#### 选做编程题

#### 实验必做内容

#### 实验进度相关的必读信息

#### 重要性超越实验的原则与方法

#### 对, 你没有看错, 除了一些重要的信息之外, PA0的实验讲义都是英文!

随着科学技术的发展, 在国际学术交流中使用英语已经成为常态: 顶尖的论文无一不使用英文来书写, 在国际上公认的计算机领域经典书籍也是使用英文编著. 顶尖的论文没有中文翻译版; 如果需要获取信息, 也应该主动去阅读英文材料, 而不是等翻译版出版. "我是中国人, 我只看中文"这类观点已经不符合时代发展的潮流, 要站在时代的最前沿, 阅读英文材料的能力是不可或缺的.

阅读英文材料, 无非就是"不会的单词查字典, 不懂的句子反复读". 如今网上有各种词霸可解燃眉之急, 但英文阅读能力的提高贵在坚持. "刚开始觉得阅读英文效率低", 是所有中国人都无法避免的经历. 如果你发现身边的大神可以很轻松地阅读英文材料, 那是因为他们早就克服了这些困难. 引用陈道蓄老师的话: 坚持一年, 你就会发现有不同; 坚持两年, 你就会发现大有不同.

撇开这些高大上的话题不说, 阅读英文材料和你有什么关系呢? 有! 因为在PA中陪伴你的, 就是没有中文版的各种手册(例如[riscv手册](https://github.com/riscv/riscv-isa-manual/releases/download/riscv-isa-release-382fd8b-2024-04-11/unpriv-isa-asciidoc.pdf)), 当然还有`man`: 如果你不愿意阅读英文材料, 你是注定无法独立完成PA的.

作为过渡, 我们为大家准备了全英文的PA0. PA0的目的是配置实验环境, 同时熟悉GNU/Linux下的工作方式. 其中涉及的都是一些操作性的步骤, 你不必为了完成PA0而思考深奥的问题. 你需要独立完成PA0, 请你认真阅读讲义中的每一个字符, 并按照讲义中的内容进行操作: 当讲义提到要在互联网上搜索某个内容时, 你就去互联网上搜索这个内容. 如果遇到了错误, 请认真反复阅读讲义内容, 机器永远是对的. 如果你是第一次使用GNU/Linux, 你还需要查阅大量资料或教程来学习一些新工具的使用方法, 这需要花费大量的时间(例如你可能需要花费一个下午的时间, 仅仅是为了使用`vim`在文件中键入两行内容). 这就像阅读英文材料一样, 一开始你会觉得效率很低, 但随着时间的推移, 你对这些工具的使用会越来越熟练. 相反, 如果你通过"投机取巧"的方式来完成PA0, 你将会马上在PA1中遇到麻烦. 正如etone所说, 你在专业上的技不如人, 迟早有一天会找上来.

另外, PA0的讲义只负责给出操作过程, 并不负责解释这些操作相关的细节和原理. 如果你希望了解它们, 请在互联网上搜索相关内容.

We are going to install the [Ubuntu 22.04](https://ubuntu.com) distribution directly over your physical machine. If you already have one copy of GNU/Linux distribution, and you want to use your copy as the development environment, just use it! But if you encounter some troubles because of platform disparity, please search the Internet for trouble-shooting.

It is also OK to use virtual machines, such as VMWare or VirtualBox. If you decide to do this and you do not have a copy of GNU/Linux, please install [Ubuntu](https://ubuntu.com) distribution in the virtual machine. Also, please search the Internet for trouble-shooting if you have any problems about virtual machines.

#### 必须使用带GUI的64位GNU/Linux

如果你打算使用已有的GNU/Linux平台, 请确保它是64位版本. PA的某些特性会依赖于64位平台和图形显示.

#### 使用GNU/Linux真机的一些原因

- 真机的稳定性会比虚拟机相对高一些(比如[crash consistency](https://en.wikipedia.org/wiki/Data_consistency)之类的).
- 真机的性能会比虚拟机相对高一些(但不影响实验分数), 如果你希望在实验后期获得比较流畅的游戏体验, 真机是一个不错的选择

#### 建议体验真机的安装

虽然学习计算机专业不是为了修电脑装系统, 但如果你连系统都没装过, 也确实不太好意思跟亲戚说你是学计算机的. 现在机会来了, 如果你以前真的从来没有安装过操作系统, 我们强烈建议你装一下真机, 来了解一下安装操作系统都需要经历些什么.

#### Mac用户的不幸

与ICS同时开设的数字电路实验课程需要安装`Vivado/Quartus`工具来进行实验, 然而非常不幸的是, 这两款工具皆不提供Mac版本. 为了使用它们, 你必须安装Windows或者GNU/Linux操作系统. 那么, 还不如一石二鸟, 现在装个GNU/Linux真机, 就可以解决上述所有问题了.

如果你不必修读南京大学的课程, 可以忽略这个问题.

#### 首先当然是备份重要数据!

如果你是第一次安装操作系统, 你可能会因为误操作而删除了磁盘上的重要文件. 备份数据无疑是一个非常重要的操作, 这样以后你就可以在安装过程中进行各种尝试, 随心所欲地折腾你的机器了.

当然, 就算你安装系统的操作看上去是正确的, 也有可能因为硬件兼容问题导致操作系统无法启动等后果. 如果确实发生了这种情况, 就到互联网上搜索解决方案吧. 因此, PA0还是要尽早开始体验.

Please reserve at least one partitions (20GB ~ 50GB) on the disk for Ubuntu to install. If you want to install `Vivado/Quartus` in Ubuntu, please reserve about 100GB of disk space. For how to do this, please search the Internet. For example, if you use Windows, you can search for `压缩卷 Windows`.

## Installing Ubuntu

Please search the Internet for "Ubuntu 22.04 安装教程" and follow the tutorial.

#### 不要使用Ubuntu的Software Updater

经同学发现, 在安装过程中默认选中的`Download updates while installing Ubuntu`选项可能会改变Ubuntu中包管理器的状态, 使其与讲义后续指示的操作产生冲突, 最终将导致系统崩溃而无法再次进入Ubuntu. 可考虑取消相关选项, 具体可参考[这里](https://github.com/NJU-ProjectN/ics-pa-gitbook/issues/23).

此外, 在完成安装并初次登陆Ubuntu时, Software Updater也会弹出提示框提醒用户更新软件(如下图所示), 请务必忽略该提示框, 不要点击"安装". 否则安装操作可能同样导致系统崩溃而无法再次进入Ubuntu.

![Ubuntu Software Updater](https://ysyx.oscc.cc/docs/assets/ubuntu-software-updater.a0dc5d34.png)

建议关闭Software Updater功能使其不再提示, 具体操作请在互联网中搜索解决方案. 感谢2020级彭浩伦同学发现此问题.

#### 我可以选择其它Ubuntu的版本吗?

可以. 不过不同版本的Ubuntu中的工具版本会稍有差异, 尤其是编译器GCC. 如果你选择了其它版本, 可能会遇到因此带来的少量问题, 不过这不会对实验内容产生大幅的影响.

#### 选择语言时选择English, 不要选择中文

使用中文的系统环境会给一些命令行操作带来不便, 甚至会增加排查错误的难度. 每年都有部分同学因为选择了中文环境, 在工具报错时无法在互联网上搜索到有效的解决方案, 从而影响了实验进度.

事实上, 即使在英文的系统环境中, 也可以通过安装中文输入法来键入中文.


---

> 来源：[https://ysyx.oscc.cc/docs/ics-pa/0.2.html](https://ysyx.oscc.cc/docs/ics-pa/0.2.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# First Exploration with GNU/Linux

Open `terminal`, you will see the following prompt:

```
username@hostname:~$
```

#### 找不到终端?

如果你不知道如何打开`terminal`(终端), 你需要在互联网上搜索一些Ubuntu的使用教程来学习.

This prompt shows your username, host name, and the current working directory. The username should be the same as you set during the installation. The current working directory is `~` now. As you switch to another directory, the prompt will change as well. You are going to code under this environment, so try to make friends with terminal!

#### Where is GUI?

Many of you always use operating system with GUI, such as Windows. But the terminal is completely with CLI (Command Line Interface). Have you wondered if there is something that you can do it in CLI, but can not in GUI? Have no idea? If you are asked to count how many lines of code you have coded during the 程序设计基础 course, what will you do?

If you stick to Visual Studio, you will never understand why `vim` is called 编辑器之神. If you stick to Windows, you will never know what is [Unix Philosophy](http://en.wikipedia.org/wiki/Unix_philosophy). If you stick to GUI, you can only do what it can; but in CLI, it can do what you want. One of the most important spirits of young people like you is to try new things to bade farewell to the past.

GUI wins when you do something requires high definition displaying, such as watching movies. [Here](http://www.computerhope.com/issues/ch000619.htm) is an article discussing the comparison between GUI and CLI.

Now you can see how much disk space Ubuntu occupies. Type the following command:

```
df -h
```

To shut down the system, issue the following command:

```
poweroff
```

#### "command not found" in some Linux distributions

In some Linux distributions, executing the command above may give an error message:

```
-bash: poweroff: command not found
```

This error is due to the property of the `poweroff` command - it is a system administration command. In such Linux distribution, executing this command requires superuser privilege.

Therefore, to shut down the system, you should first switch to the root account:

```
su -
```

Enter the root password you set during the installation. Note that the password is not shown in the terminal to avoid password leaks. If the password is correct, you will see the prompt changes:

```
root@hostname:/home/username#
```

The last character is `#`, instead of `$` before you executing `su -`. `#` is the indicator of root account. Now execute `poweroff` command again, you will find that the command is executed successfully.

#### Why executing the "poweroff" command requires superuser privilege in some Linux distributions?

Can you provide a scene where bad thing will happen if the `poweroff` command does not require superuser privilege?

#### 不要强制关闭虚拟机!!!

如果你使用虚拟机, 你务必通过`poweroff`命令或菜单关闭虚拟机. 如果你通过点击窗口右上角的`X`按钮强制关闭虚拟机, 可能会造成虚拟机中文件损坏. 往届有若干学长因此而影响了实验进度, 甚至由于损坏了实验相关的文件而影响了分数. 请大家引以为鉴, 不要贪图方便, 否则后果自负!


---

> 来源：[https://ysyx.oscc.cc/docs/ics-pa/0.3.html](https://ysyx.oscc.cc/docs/ics-pa/0.3.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# Installing Tools

In GNU/Linux, you can download and install a software by one command (which may be difficult to do in Windows). This is achieved by the package manager. Different GNU/Linux distribution has different package manager. In Ubuntu, the package manager is called `apt`.

You will download and install some tools needed for the PAs from the network mirrors. Before using the network mirrors, you should check whether the system can access the Internet.

### Checking network state

Inside NJU, you should easily obtain an IPv6 address. To test this, try to ping a mirror host with IPv6 support:

```
ping mirrors.tuna.tsinghua.edu.cn -c 4
```

You should receive reply packets successfully:

```
PING mirrors.tuna.tsinghua.edu.cn(2402:f000:1:408:8100::1 (2402:f000:1:408:8100::1)) 56 bytes of data.
64 bytes from 2402:f000:1:408:8100::1 (2402:f000:1:408:8100::1): icmp_seq=1 ttl=54 time=1.56 ms
64 bytes from 2402:f000:1:408:8100::1 (2402:f000:1:408:8100::1): icmp_seq=2 ttl=54 time=1.07 ms
64 bytes from 2402:f000:1:408:8100::1 (2402:f000:1:408:8100::1): icmp_seq=3 ttl=54 time=1.07 ms
64 bytes from 2402:f000:1:408:8100::1 (2402:f000:1:408:8100::1): icmp_seq=4 ttl=54 time=1.24 ms

--- mirrors.tuna.tsinghua.edu.cn ping statistics ---
4 packets transmitted, 4 received, 0% packet loss, time 7ms
rtt min/avg/max/mdev = 1.071/1.237/1.563/0.203 ms
```

If you do not have an IPv6 address, you may access the Internet by IPv4 address. You can try to ping a host outside the university LAN:

```
ping www.baidu.com -c 4
```

If you can ping Baidu successfully, you should successfully ping the mirror host above, too.

### Setting APT source file

#### 如果你的系统不是Ubuntu 22.04, 请更换合适的源

使用与系统不相符的源会导致工具包版本冲突, 强行安装将会损坏系统. 如果你使用的系统不是Ubuntu 22.04, 请勿使用以下的源, 你可以在[这里](https://mirrors.bfsu.edu.cn/help/ubuntu/)选择相应的Ubuntu版本, 并将源更换成选择的结果.

Run the following commands to update the APT source file:

```
sed -i "s/archive.ubuntu.com/mirrors.tuna.tsinghua.edu.cn/g" /etc/apt/sources.list
```

However, you will receive an error message:

```
sed: /etc/apt/sources.list: Permission denied
```

This is because the APT source file is owned by root, and you do not have the permission to modify it.

One solution is first switching to the root account. But to avoid switching, an alternative way is to use `sudo`. If you find an operation requires superuser permission, append `sudo` before that operation. Before using `sudo`, you should add your account to the `sudo` group. But first, you still need to switch to the root account.

```
su -
Password:
```

Enter the root password you set during the installation. Note that the password is not shown in the terminal to avoid password leaks. If the password is correct, you will see the prompt changes:

```
root@hostname:/home/username#
```

The last character is `#`, instead of `$` before you executing `su -`. `#` is the indicator of root account. Now you can add your account to the `sudo` group.

```
adduser username sudo  # Change `username` to your user name
exit
```

To let the changes to take effect, you should log out or reboot. After that, try

```
whoami
sudo whoami
```

If it is the first time you run `sudo`, enter the password of your account. You should find that `sudo whoami` will output `root`.

Now you can use `sudo` to modify the APT source file. This time you should modify it successfully. To check this, you can output the file:

```
cat /etc/apt/sources.list
```

You should see it really outputs the line you just updated.

### Updating APT package information

Now you can tell `apt` to retrieve software information from the sources:

```
apt-get update
```

However, you will receive an error message:

```
E: Could not open lock file /var/lib/apt/lists/lock - open (13: Permission denied)
E: Unable to lock directory /var/lib/apt/lists/
```

This is because `apt-get` requires superuser privilege to run. Run the command with superuser privilege. Since it requires Internet accessing, it may cost some time to finish.

#### 遇到could not resolve 'cn.mirrors.tuna.tsinghua.edu.cn'的错误

这可能是因为你在安装Ubuntu时默认源选择了国内镜像, 导致默认的`sources.list`被修改造成的. 为了修复这个问题, 你需要额外运行以下命令:

```
sed -i "s/cn.mirrors.tuna/mirrors.tuna/g" /etc/apt/sources.list
```

然后尝试重新运行`apt-get update`.

### Installing tools for PAs

The following tools are necessary for PAs:

```
apt-get install build-essential    # build-essential packages, include binary utilities, gcc, make, and so on
apt-get install man                # on-line reference manual
apt-get install gcc-doc            # on-line reference manual for gcc
apt-get install gdb                # GNU debugger
apt-get install git                # revision control system
apt-get install libreadline-dev    # a library used later
apt-get install libsdl2-dev        # a library used later
```

The usage of these tools is explained later.

### Installing Chinese input method

Search the Internet for how to install a Chinese input method in Ubuntu.


---

> 来源：[https://ysyx.oscc.cc/docs/ics-pa/0.4.html](https://ysyx.oscc.cc/docs/ics-pa/0.4.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# Configuring vim

```
apt-get install vim
```

`vim` is called [编辑器之神](https://code2048.com/post/war_3_editor/). You will use `vim` for coding in all PAs and Labs, as well as editing other files. If you prefer to `emacs`, you can download and install `emacs` from network mirrors.

### Learning vim

You are going to be asked to modify a file using `vim`. For most of you, this is the first time to use `vim`. The operations in `vim` are quite different from other editors you have ever used. To learn `vim`, you need a tutorial. There are two ways to get tutorials:

- Issue the `vimtutor` command in terminal. This will launch a tutorial for `vim`. This way is recommended, since you can read the tutorial and practice at the same time.
- Search the Internet with keyword "vim 教程", and you will find a lot of tutorials about `vim`. Choose some of them to read, meanwhile you can practice with the a temporary file by

```
vim test
```

PRACTICE IS VERY IMPORTANT. You can not learn anything by only reading the tutorials.

#### 为什么上课不讲GNU/Linux的使用?

你可能会想: 这是我第一次接触GNU/Linux, 为什么上课不讲讲怎么用?

因为说明书不是用来讲的, 是用来一边看一边操作的; 你也不能光靠道听途说来掌握这些工具, 而是要自己去动手尝试. 你在大学课堂上应该学习到的是那些一脉相承的知识, 然后去思考这些知识背后的原则和思想, 将来有能力将这些原则和思想应用到新的领域.

我们设计这些实验内容, 是为了让你明白, 你有能力自己去看教程学习新的工具; 以及, 以后接触新事物的时候, 你不应该等着别人来给你讲, 而应该自己主动去找教程来学习如何使用.

#### Some games operated with vim

Here are some games to help you master some basic operations in `vim`. Have fun!

- [Vim Adventures](http://vim-adventures.com)
- [Vim Snake](http://www.vimsnake.com)
- [Open Vim Tutorials](http://www.openvim.com/tutorial.html)
- [Vim Genius](http://www.vimgenius.com)

#### The power of vim

You may never consider what can be done in such a "BAD" editor. Let's see two examples.

The first example is to generate the following file:

```
1
2
3
.....
98
99
100
```

This file contains 100 lines, and each line contains a number. What will you do? In `vim`, this is a piece of cake. First change `vim` into normal state (when `vim` is just opened, it is in normal state), then press the following keys sequentially:

```
i1<ESC>q1yyp<C-a>q98@1
```

where `<ESC>` means the ESC key, and `<C-a>` means "Ctrl + a" here. You only press no more than 15 keys to generate this file. Is it amazing? What about a file with 1000 lines? What you do is just to press one more key:

```
i1<ESC>q1yyp<C-a>q998@1
```

The magic behind this example is recording and replaying. You initial the file with the first line. Then record the generation of the second. After that, you replay the generation for 998 times to obtain the file.

The second example is to modify a file. Suppose you have such a file:

```
aaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbb
cccccccccccccccccccccccccddddddddddddddddddddddddd
eeeeeeeeeeeeeeeeeeeeeeeeefffffffffffffffffffffffff
ggggggggggggggggggggggggghhhhhhhhhhhhhhhhhhhhhhhhh
iiiiiiiiiiiiiiiiiiiiiiiiijjjjjjjjjjjjjjjjjjjjjjjjj
```

You want to modify it into:

```
bbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaaaaaaaaa
dddddddddddddddddddddddddccccccccccccccccccccccccc
fffffffffffffffffffffffffeeeeeeeeeeeeeeeeeeeeeeeee
hhhhhhhhhhhhhhhhhhhhhhhhhggggggggggggggggggggggggg
jjjjjjjjjjjjjjjjjjjjjjjjjiiiiiiiiiiiiiiiiiiiiiiiii
```

What will you do? In `vim`, this is a piece of cake, too. First locate the cursor to first "a" in the first line. And change `vim` into normal state, then press the following keys sequentially:

```
<C-v>24l4jd$p
```

where `<C-v>` means "Ctrl + v" here. What about a file with 100 such lines? What you do is just to press one more key:

```
<C-v>24l99jd$p
```

Although these two examples are artificial, they display the powerful functionality of `vim`, comparing with other editors you have used.

### Enabling syntax highlight

`vim` provides more improvements comparing with `vi`. But these improvements are disabled by default. Therefore, you should enable them first.

We take syntax highlight as an example to illustrate how to enable the features of `vim`. To do this, you should modify the `vim` configuration file. The file is called `.vimrc`, and it is located under `/etc/vim` directory. We first make a copy of it to the home directory by `cp` command:

```
cp /etc/vim/vimrc ~/.vimrc
```

And switch to the home directory if you are not under it yet:

```
cd ~
```

If you use `ls` to list files, you will not see the `.vimrc` you just copied. This is because a file whose name starts with a `.` is a hidden file in GNU/Linux. To show hidden files, use `ls` with `-a` option:

```
ls -a
```

Then open `.vimrc` using `vim`:

```
vim .vimrc
```

After you learn some basic operations in `vim` (such as moving, inserting text, deleting text), you can try to modify the `.vimrc` file as following:

```
--- before modification
+++ after modification
@@ -17,3 +17,3 @@
 " Vim5 and later versions support syntax highlighting. Uncommenting the next
 " line enables syntax highlighting by default.
-"syntax on
+syntax on
```

We present the modification with [GNU diff format](http://www.gnu.org/software/diffutils/manual/html_node/Unified-Format.html). If you do not understand the diff format, please search the Internet for more information.

#### 为什么要STFW?

你或许会想, 我问别人是为了节省我的时间.

但现在是互联网时代了, 在网上你能得到各种信息: 比如diff格式这种标准信息, 网上是100%能搜到的; 就包括你遇到的问题, 很大概率也是别人在网上求助过的. 如果对于一个你本来只需要在搜索引擎上输入几个关键字就能找到解决方案的问题, 你都没有付出如此微小的努力, 而是首先想着找人来帮你解决, 占用别人宝贵的时间, 你将是这个时代的失败者.

于是有了STFW (Search The F\*\*king Web) 的说法, 它的意思是, 在向别人求助之前自己先尝试通过正确的方式使用搜索引擎独立寻找解决方案.

正确的STFW方式能够增加找到解决方案的概率, 包括

- 使用[Google搜索引擎](https://ysyx.oscc.cc/docs/ics-pa/www.google.com)搜索一般性问题
- 使用[英文维基百科](http://en.wikipedia.org)查阅概念
- 使用[stack overflow问答网站](http://stackoverflow.com)搜索程序设计相关问题

如果你没有使用上述方式来STFW, 请不要抱怨找不到解决方案而开始向别人求助, 你应该想, "噢我刚才用的是百度, 接下来我应该试试Google". 关于使用Google, 在学校可以尝试设置IPv6, 或者设置"科学上网", 具体设置方式请STFW.

#### 为什么不要用百度?

相信大家都用过百度来搜索一些非技术问题, 而且一般很容易找到答案. 但随着问题技术含量的提高, 百度的搜索结果会变得越来越不靠谱. 坚持使用百度搜索技术问题, 你将很有可能会碰到以下情况之一:

- 搜不到相关结果, 你感到挫败
- 搜到看似相关的结果, 但无法解决问题, 你在感到挫败之余, 也发现自己浪费了不少时间
- 你搜到了解决问题的方案, 但没有发现原因分析, 结果你不知道这个问题背后的细节

你可能会觉得"可以解决问题就行, 不需要了解问题背后的细节". 但对于一些问题(例如编程问题), 你了解这些细节就相当于学到了新的知识, 所以你应该去了解这些细节, 让自己懂得更多.

如果谷歌能以更高的概率提供可以解决问题的方案, 并且带有原因分析, 你应该没有理由使用百度来搜索技术问题. 如果你仍然坚持使用百度, 原因就只有一个: 你不想主动去成长.

After you are done, you should save your modification. Exit `vim` and open the `.vimrc` file again, you should see the syntax highlight feature is enabled.

#### 为什么要这么麻烦?

搞了半天, 你发现其实也就是改动一个字符而已, 为什么不直接说清楚呢?

这是为了"入乡随俗": 我们希望你了解怎么用计算机思维精简准确地表达我们想做的事情. diff格式是一种描述文件改动的常用方式. 实际上, 计算机的世界里面有很多约定俗成的"规矩", 当你慢慢去接触去了解这些规矩的时候, 你就会在不知不觉中明白计算机世界是怎么运转的.

### Enabling more vim features

Modify the `.vimrc` file mentioned above as the following:

```
--- before modification
+++ after modification
@@ -21,3 +21,3 @@
 " If using a dark background within the editing area and syntax highlighting
 " turn on this option as well
-"set background=dark
+set background=dark
@@ -31,5 +31,5 @@
 " Uncomment the following to have Vim load indentation rules and plugins
 " according to the detected filetype.
-"filetype plugin indent on
+filetype plugin indent on
@@ -37,10 +37,10 @@
 " The following are commented out as they cause vim to behave a lot
 " differently from regular Vi. They are highly recommended though.
 "set showcmd            " Show (partial) command in status line.
-"set showmatch          " Show matching brackets.
-"set ignorecase         " Do case insensitive matching
-"set smartcase          " Do smart case matching
-"set incsearch          " Incremental search
+set showmatch          " Show matching brackets.
+set ignorecase         " Do case insensitive matching
+set smartcase          " Do smart case matching
+set incsearch          " Incremental search
 "set autowrite          " Automatically save before commands like :next and :make
-"set hidden             " Hide buffers when they are abandoned
+set hidden             " Hide buffers when they are abandoned
 "set mouse=a            " Enable mouse usage (all modes)
```

You can append the following content at the end of the `.vimrc` file to enable more features. Note that contents after a double quotation mark `"` are comments, and you do not need to include them. Of course, you can inspect every features to determine to enable or not.

```
setlocal noswapfile " 不要生成swap文件
set bufhidden=hide " 当buffer被丢弃的时候隐藏它
colorscheme evening " 设定配色方案
set number " 显示行号
set cursorline " 突出显示当前行
set ruler " 打开状态栏标尺
set shiftwidth=2 " 设定 << 和 >> 命令移动时的宽度为 2
set softtabstop=2 " 使得按退格键时可以一次删掉 2 个空格
set tabstop=2 " 设定 tab 长度为 2
set nobackup " 覆盖文件时不备份
set autochdir " 自动切换当前目录为当前文件所在的目录
set backupcopy=yes " 设置备份时的行为为覆盖
set hlsearch " 搜索时高亮显示被找到的文本
set noerrorbells " 关闭错误信息响铃
set novisualbell " 关闭使用可视响铃代替呼叫
set t_vb= " 置空错误铃声的终端代码
set matchtime=2 " 短暂跳转到匹配括号的时间
set magic " 设置魔术
set smartindent " 开启新行时使用智能自动缩进
set backspace=indent,eol,start " 不设定在插入状态无法用退格键和 Delete 键删除回车符
set cmdheight=1 " 设定命令行的行数为 1
set laststatus=2 " 显示状态栏 (默认值为 1, 无法显示状态栏)
set statusline=\ %<%F[%1*%M%*%n%R%H]%=\ %y\ %0(%{&fileformat}\ %{&encoding}\ Ln\ %l,\ Col\ %c/%L%) " 设置在状态行显示的信息
set foldenable " 开始折叠
set foldmethod=syntax " 设置语法折叠
set foldcolumn=0 " 设置折叠区域的宽度
setlocal foldlevel=1 " 设置折叠层数为 1
nnoremap <space> @=((foldclosed(line('.')) < 0) ? 'zc' : 'zo')<CR> " 用空格键来开关折叠
```

#### 提高开发效率的编辑器

程序设计课上你学会了使用Visual Studio, 然后你可能会认为, 程序员就是这样写代码的了. 其实并不是, 程序员会追求那些提高效率的方法. 不是GUI不好, 而是你只是用记事本的操作方式来写代码. 所以你需要改变, 去尝试一些可以帮助你提高开发效率的工具.

在GNU/Linux中, 与记事本的操作方式相比, 学会`vim`的基本操作就已经可以大大提高开发效率. 还有各种插件来增强`vim`的功能, 比如可以在代码中变量跳转的`ctags`等等. 你可以花点时间去配置一下`vim`, 具体配置方式请STFW. 总之, "编辑器之神"可不是浪得虚名的.


---

> 来源：[https://ysyx.oscc.cc/docs/ics-pa/0.5.html](https://ysyx.oscc.cc/docs/ics-pa/0.5.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# More Exploration

### Learning to use basic tools

After installing tools for PAs, it is time to explore GNU/Linux again! [Here](misc.md) is a small tutorial for GNU/Linux written by jyy. If you are new to GNU/Linux, read the tutorial carefully, and most important, try every command mentioned in the tutorial. Remember, you can not learn anything by only reading the tutorial. Besides, [鸟哥的Linux私房菜](http://linux.vbird.org/linux_basic) is a book suitable for freshman in GNU/Linux. Another book recommended by us is [Harley Hahn's Guide to Unix and Linux](http://www.harley.com/books/sg3.html).

#### RTFM

The most important command in GNU/Linux is `man` - the on-line manual pager. This is because `man` can tell you how to use other commands. [Here](misc.md) is a small tutorial for `man`. Remember, learn to use `man`, learn to use everything. Therefore, if you want to know something about GNU/Linux (such as shell commands, system calls, library functions, device files, configuration files...), [RTFM](http://en.wikipedia.org/wiki/RTFM).

#### 为什么要RTFM?

RTFM是STFW的长辈, 在互联网还不是很流行的年代, RTFM是解决问题的一种有效方法. 这是因为手册包含了查找对象的所有信息, 关于查找对象的一切问题都可以在手册中找到答案.

你或许会觉得翻阅手册太麻烦了, 所以可能会在百度上随便搜一篇博客来尝试寻找解决方案. 但是, 你需要明确以下几点:

- 你搜到的博客可能也是转载别人的, 有可能有坑
- 博主只是分享了他的经历, 有些说法也不一定准确
- 搜到了相关内容, 也不一定会有全面的描述

最重要的是, 当你尝试了上述方法而又无法解决问题的时候, 你需要明确"我刚才只是在尝试走捷径, 看来我需要试试RTFM了".

#### Write a "Hello World" program under GNU/Linux

Write a "Hello World" program, compile it, then run it under GNU/Linux. If you do not know what to do, refer to the GNU/Linux tutorial above.

#### Write a Makefile to compile the "Hello World" program

Write a Makefile to compile the "Hello World" program above. If you do not know what to do, refer to the GNU/Linux tutorial above.

Now, stop here. [Here](https://linuxconfig.org/gdb-debugging-tutorial-for-beginners) is a small tutorial for GDB. GDB is the most common used debugger under GNU/Linux. If you have not used a debugger yet (even in Visual Studio), blame the 程序设计基础 course first, then blame yourself, and finally, read the tutorial to learn to use GDB.

#### Learn to use GDB

Read the GDB tutorial above and use GDB following the tutorial. In PA1, you will be required to implement a simplified version of GDB. If you have not used GDB, you may have no idea to finish PA1.

#### 嘿! 别偷懒啊!

上文让你写个"Hello World"程序, 然后写个Makefile来编译它, 并且看教程学习一下GDB的基本使用呢!

### Installing tmux

`tmux` is a terminal multiplexer. With it, you can create multiple terminals in a single screen. It is very convenient when you are working with a high resolution monitor. To install `tmux`, just issue the following command:

```
apt-get install tmux
```

Now you can run `tmux`, but let's do some configuration first. Go back to the home directory:

```
cd ~
```

New a file called `.tmux.conf`:

```
vim .tmux.conf
```

Append the following content to the file:

```
bind-key c new-window -c "#{pane_current_path}"
bind-key % split-window -h -c "#{pane_current_path}"
bind-key '"' split-window -c "#{pane_current_path}"
```

These three lines of settings make `tmux` "remember" the current working directory of the current pane while creating new window/pane.

Maximize the terminal windows size, then use `tmux` to create multiple normal-size terminals within single screen. For example, you may edit different files in different directories simultaneously. You can edit them in different terminals, compile them or execute other commands in another terminal, without opening and closing source files back and forth. You can scroll the content in a `tmux` terminal up and down. For how to use `tmux`, please STFW.

#### 又要没完没了地STFW了?

对.

PA除了让大家巩固ICS理论课的知识之外, 还承担着一个重要的任务: 把大家培养成一个素质合格的CSer. 事实上, 一个素质合格的CSer, 需要具备独立搜索解决方案的能力. 这是IT企业和科研机构对程序员的一个基本要求: 你将来的老板很可能会把一个任务直接丢给你, 如果你一遇到困难就找人帮忙, 老板就会认为你没法创造价值.

PA在尝试让你重视这些业界和学术界都看重的基本要求, 从而让你锻炼这些能力和心态: 遇到问题了, 第一反应不是赶紧找个大神帮忙搞定, 而是"我来试试STFW和RTFM, 看能不能自己解决". 所以PA不是按部就班的中学实验, 不要抱怨讲义没写清楚导致你走了弯路, 我们就是故意的: 我们会尽量控制路不会太弯, 只要你摆正心态, 你是有能力去独立解决这些问题的. 重要的是, 你得接受现实: 你走的弯路, 都在说明你的能力有待提升, 以后少走弯路的唯一方法, 就是你现在认真把路走下去.

#### 提问的智慧/别像弱智一样提问

一个素质合格的CSer需要具备的另一个标准是, 懂得如何提问.

相信大家作为CSer, 被问如何修电脑的事情应该不会少. 比如你有一个文科小伙伴, 他QQ跟你说一句"我的电脑出问题了", 让你帮他修. 然后你得问东问西才了解具体的问题, 接着你让他尝试各种方案, 让他给你尝试的反馈. 如果你有10个这样的小伙伴, 相信你肯定受不了了. 这下你多少能体会到助教的心情了吧.

事实上, 如果希望能提高得到回答的概率, 提问者应该学会如何更好地提问. 换句话说, 提问者应该去积极思考 "我可以主动做些什么来让对方更方便地帮助我诊断问题". 文科小伙伴确实不是学习计算机专业的, 你可以选择原谅他; 但你是CSer, 至少你得在问题中描述具体的现象以及你做过的尝试, 而不是直接丢一句"我的程序挂了", 就等着别人来救场. 在你将来的职业生涯中也很有可能需要向别人求助, 比如在github等开源社区中发issue, 或者是在stackoverflow等论坛上发帖, 或者给技术工程师发邮件等, 如果你的提问方式非常不专业, 很可能没有人愿意关注你的问题, 因为这不仅让人觉得你随便提的问题没那么重要, 而且大家也不愿意花费大量的时间向你来回地咨询.

一种推荐的提问方式如下:

```
我在xxx的时候遇到了xxx的错误. 这个错误可以通过以下步骤重现: (描述具体的现象)
1. 我的系统版本是xxx, 相关的工具版本是xxx
2. 我做了xxx (必要的时候贴个图)
3. 然后xxx (必要的时候贴个图)
...
为了排查这个错误, 我进行了以下尝试: (说明我很希望可以解决问题, 真的没办法才提问的)
1. 我做了xxx, 出现了xxx的结果 (必要的时候贴个图)
2. 我还做了xxx, 出现了xxx的结果 (必要的时候贴个图)
...
最后问题还没有解决, 请问我还需要做哪些事情?
```

另外请大家务必阅读[提问的智慧](https://github.com/ryanhanwu/How-To-Ask-Questions-The-Smart-Way/blob/master/README-zh_CN.md)和[别像弱智一样提问](https://github.com/tangx/Stop-Ask-Questions-The-Stupid-Ways/blob/master/README.md)这两篇文章, 里面有不少例子供大家参考.

The following picture shows a scene working with multiple terminals within single screen. Is it COOL?

![tmux](https://ysyx.oscc.cc/docs/assets/Tmux1.63e8f26f.png)

#### 为什么要使用tmux?

这其实是一个"使用正确的工具做事情"的例子.

计算机天生就是为用户服务的, 只要你有任何需求, 你都可以想, "有没有工具能帮我实现?". 我们希望每个终端做不同的事情, 能够在屏幕上一览无余的同时, 还能在终端之间快速切换. 事实上, 通过STFW和RTFM你就可以掌握如何使用一款正确的工具: 你只要在搜索引擎上搜索"Linux 终端 分屏", 就可以搜到`tmux`这个工具; 然后再搜索"tmux 使用教程", 就可以学习到`tmux`的基本使用方法; 在终端中输入`man tmux`, 就可以查阅关于`tmux`的任何疑问.

当然, 学习不是零成本的. 往届有学长提出一种零学习成本的分屏方式: 打开4个终端, 并将它们分别拖动到屏幕的4个角落, 发现用Alt+Tab快捷键不方便选择窗口(因为4个窗口的外貌都差不多), 就使用鼠标点击的方式来切换. 然后形容安装学习`tmux`是"脱裤子放屁 -- 多此一举".

`tmux`的初衷就是为用户节省上述的操作成本. 如果你抱着不愿意付出任何学习成本的心态, 就无法享受到工具带来的便利.

#### Things behind scrolling

You should have used scroll bars in GUI. You may take this for granted. So you may consider the original un-scrollable terminal (the one you use when you just log in) the hell. But think of these: why the original terminal can not be scrolled? How does `tmux` make the terminals scrollable? And last, do you know how to implement a scroll bar?

GUI is not something mysterious. Remember, behind every elements in GUI, there is a story about it. Learn the story, and you will learn a lot. You may say "I just use GUI, and it is unnecessary to learn the story." Yes, you are right. The appearance of GUI is to hide the story for users. But almost everyone uses GUI in the world, and that is why you can not tell the difference between you and them.

### Why GNU/Linux and How to

#### 为什么要使用Linux?

我们先来看两个例子.

**如何比较两个文件是否完全相同?** 这个例子看上去非常简单, 在Linux下使用`diff`命令就可以实现. 如果文件很大, 那不妨用`md5sum`来计算并比较它们的MD5. 对一个Linux用户来说, 键入这些命令只需要花费大约3秒的时间. 但在Windows下, 这件事要做起来就不那么容易了. 也许你下载了一个MD5计算工具, 但你需要点击多少次鼠标才能完成比较呢? 也许你觉得一次好像也省不了多少时间, 然而真相是, 你的开发效率就是这样一点点降低的.

**如何列出一个C语言项目中所有被包含过的头文件?** 这个例子比刚才的稍微复杂一些, 但在Windows下你几乎无法通过GUI工具高效地做到它. 在Linux中, 我们只需要通过一行命令就可以做到了:

```
find . -name "*.[ch]" | xargs grep "#include" | sort | uniq
```

通过查阅`man`, 你应该不难理解上述命令是如何实现所需功能的. 这个例子再次体现了Unix哲学:

- 每个工具只做一件事情, 但做到极致
- 工具采用文本方式进行输入输出, 从而易于使用
- 通过工具之间的组合来解决复杂问题

Unix哲学的最后一点最能体现Linux和Windows的区别: 编程创造. 如果把工具比作代码中的函数, 工具之间的组合就是一种编程. 而对初学者来说, Windows的GUI工具之间几乎无法组合, 因为面向普通用户的Windows需要强调易用性.

所以, 你应该使用Linux的原因非常简单: 作为一个码农, Windows一直在阻碍你思想, 能力和效率的提升.

#### 如何用好Linux?

1. ~~卸载Windows~~, 解放思想, 摆脱Windows对你的阻碍. 与其默认"没办法, 也只能这样了", 你应该去尝试"看看能不能把这件事做好".
   - Linux下也有相应的常用软件, 如Chrome, WPS, 中文输入法, mplayer...
   - 没有Windows你也可以活下去
   - 实在不行可以装个Windows虚拟机备用
2. 熟悉一些常用的命令行工具, 并强迫自己在日常操作中使用它们
   - 文件管理 - `cd`, `pwd`, `mkdir`, `rmdir`, `ls`, `cp`, `rm`, `mv`, `tar`
   - 文件检索 - `cat`, `more`, `less`, `head`, `tail`, `file`, `find`
   - 输入输出控制 - 重定向, 管道, `tee`, `xargs`
   - 文本处理 - `vim`, `grep`, `awk`, `sed`, `sort`, `wc`, `uniq`, `cut`, `tr`
   - 正则表达式
   - 系统监控 - `jobs`, `ps`, `top`, `kill`, `free`, `dmesg`, `lsof`
   - 上述工具覆盖了程序员绝大部分的需求
     - 可以先从简单的尝试开始, 用得多就记住了, 记不住就`man`
3. RTFM + STFW
4. 坚持.

- 心态上, 相信总有对的工具能帮助我做得更好
- 行动上, 愿意付出时间去找到它, 学它, 用它

#### 墙裂推荐: The Missing Semester of Your CS Education

[The Missing Semester of Your CS Education](https://missing.csail.mit.edu/)是jyy墙裂推荐的Linux工具系列教程, 教你如何使用各种工具来帮助你在计算机上高效地完成各种任务, 让你终身收益.

这套教程有中文版, 去看看吧.

#### 克服恐惧, 累积最初的信心

事实上, 学习使用Linux是一个低成本, 高成功率的锻炼机会. 只要你愿意STFW和RTFM, 就能解决绝大部分的问题. 相比较而言, 你之后(后续PA中/后续课程中/工作中)遇到的问题只会更加困难. 因此, 独立解决这些简单的小问题, 你就会开始积累最初的信心, 从而也慢慢相信自己有能力解决更难的问题.


---

> 来源：[https://ysyx.oscc.cc/docs/ics-pa/0.6.html](https://ysyx.oscc.cc/docs/ics-pa/0.6.html)  
> 许可：CC BY-NC-SA 3.0 中国大陆  
> 本文件由官网正文转换为 Markdown，内容更新请以官网为准。

# Getting Source Code for PAs

### Getting Source Code

Go back to the home directory by

```
cd ~
```

Usually, all works unrelated to system should be performed under the home directory. Other directories under the root of file system (`/`) are related to system. Therefore, do NOT finish your PAs and Labs under these directories by `sudo`.

#### 不要使用root账户做实验!!!

使用root账户进行实验, 会改变实验相关文件的权限属性, 可能会导致开发跟踪系统无法正常工作; 更严重的, 你的误操作可能会无意中损坏系统文件, 导致系统无法启动! 往届有若干学长因此而影响了实验进度, 甚至由于损坏了实验相关的文件而影响了分数. 请大家引以为鉴, 不要贪图方便, 否则后果自负!

如果你仍然不理解为什么要这样做, 你可以阅读这个页面: [Why is it bad to login as root?](http://askubuntu.com/questions/16178/why-is-it-bad-to-login-as-root) 正确的做法是: 永远使用你的普通账号做那些安分守己的事情(例如写代码), 当你需要进行一些需要root权限才能进行的操作时, 使用`sudo`.

#### 在github上添加ssh key

在获取框架代码之前, 首先请你在github上添加一个ssh key, 具体操作请STFW.

Now get the source code for PA by the following command:

#### 参加"一生一芯"的同学, 请参考"一生一芯"讲义获取代码链接

如果你参加"一生一芯", 请勿使用下面的代码链接. 此外, PA讲义中关于作业提交的要求, "一生一芯"的同学可以全部忽略, 但需要关注"一生一芯"讲义中的提交要求.

```
git clone -b 2025 git@github.com:NJU-ProjectN/ics-pa.git ics2025
```

A directory called `ics2025` will be created. This is the project directory for PAs. Details will be explained in PA1.

Then issue the following commands to perform `git` configuration:

```
git config --global user.name "241220000-Zhang San" # your student ID and name
git config --global user.email "zhangsan@foo.com"   # your email
git config --global core.editor vim                 # your favorite editor
git config --global color.ui true
```

You should configure `git` with your student ID, name, and email. Before continuing, please read [this](misc.md) `git` tutorial to learn some basics of `git`. Another material recommended by jyy is [Visualizing Git Concepts with D3](http://onlywei.github.io/explain-git-with-d3). You can learn some `git` commands with the help of visualization.

Enter the project directory `ics2025`, then run

```
git branch -m master
bash init.sh nemu
bash init.sh abstract-machine
```

to initialize some subprojects. The script will pull some subprojects from github. We will explain them later.

Besides, the script will also add some environment variables into the bash configuration file `~/.bashrc`. These variables are defined by absolute path to support the compilation of the subprojects. Therefore, DO NOT move your project to another directory once finishing the initialization, else these variables will become invalid. Particularly, if you use shell other than `bash`, please set these variables in the corresponding configuration file manually.

To let the environment variables take effect, run

```
source ~/.bashrc
```

Then try

```
echo $NEMU_HOME
echo $AM_HOME
cd $NEMU_HOME
cd $AM_HOME
```

to check whether these environment variables get the right paths. If both the `echo` commands report the right paths, and both the `cd` command change to the target paths without errors, we are done. If not, please double check the steps above and the shell you are using.

### Git usage

We will use the `branch` feature of `git` to manage the process of development. A branch is an ordered list of commits, where a commit refers to some modifications in the project.

You can list all branches by

```
git branch
```

You will see there is only one branch called "master" now.

```
* master
```

To create a new branch, use `git checkout` command:

```
git checkout -b pa0
```

This command will create a branch called `pa0`, and check out to it. Now list all branches again, and you will see we are now at branch `pa0`:

```
  master
* pa0
```

From now on, all modifications of files in the project will be recorded in the branch `pa0`.

Now have a try! Modify the `STUID` and `STUNAME` variables in `ics2025/Makefile`:

```
STUID = 241220000  # your student ID
STUNAME = 张三     # your Chinese name
```

Run

```
git status
```

to see those files modified from the last commit:

```
On branch pa0
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git checkout -- <file>..." to discard changes in working directory)

	modified:   Makefile

no changes added to commit (use "git add" and/or "git commit -a")
```

Run

```
git diff
```

to list modifications from the last commit:

```
diff --git a/Makefile b/Makefile
index c9b1708..b7b2e02 100644
--- a/Makefile
+++ b/Makefile
@@ -1,4 +1,4 @@
-STUID = 241220000
-STUNAME = 张三
+STUID = 241221234
+STUNAME = 李四
 
  # DO NOT modify the following code!!!
```

You should see `STUID` and `STUNAME` are modified. Now add the changes to commit by `git add`, and issue `git commit`:

```
git add .
git commit
```

The `git commit` command will call the text editor. Type `modified my info` in the first line, and keep the remaining contents unchanged. Save and exit the editor, and this finishes a commit. Now you should see a log labeled with your student ID and name by

```
git log
```

Now switch back to the `master` branch by

```
git checkout master
```

Open `ics2025/Makefile`, and you will find that `STUID` and `STUNAME` are still unchanged! By issuing `git log`, you will find that the commit log you just created has disappeared!

Don't worry! This is a feature of branches in `git`. Modifications in different branches are isolated, which means modifying files in one branch will not affect other branches. Switch back to `pa0` branch by

```
git checkout pa0
```

You will find that everything comes back! At the beginning of PA1, you will merge all changes in branch `pa0` into `master`.

The workflow above shows how you will use branch in PAs:

- before starting a new PA, new a branch `pa?` and check out to it
- coding in the branch `pa?` (this will introduce lot of modifications)
- after finish the PA, merge the branch `pa?` into `master`, and check out back to `master`

### Compiling and Running NEMU

Now enter `nemu/` directory. Before the first time to compile NEMU, a configuration file should be generated by

```
make menuconfig
```

#### 编译报错了

你有可能会遇到这个错误信息, 好吧确实是讲义疏忽了. 那就正好当作一个练习吧: 你需要把缺少的工具装上. 至于怎么装, 当然是STFW了.

注意, 你需要**仔细阅读输出的每一个字符**, 如果你阅读得足够仔细, 你应该能明白问题的根源是什么. 否则, 你可能会花费很多不必要的时间, 我们已经见到过不少这样的同学了,

A menu will pop up. DO NOT modify anything. Just choose `Exit` and `Yes` to save the new configuration. After that, compile the project by `make`:

```
make
```

If nothing goes wrong, NEMU will be compiled successfully.

#### What happened?

You should know how a program is generated in the 程序设计基础 course. But do you have any idea about what happened when a bunch of information is output to the screen during `make` is executed?

To perform a fresh compilation, type

```
make clean
```

to remove the old compilation result, then `make` again.

To run NEMU, type

```
make run
```

However, you will see an error message:

```
[src/monitor/monitor.c:35 welcome] Exercise: Please remove me in the source code and compile NEMU again.
riscv32-nemu-interpreter: src/monitor/monitor.c:36: welcome: Assertion `0' failed.
```

This message tells you that the program has triggered an assertion fail at line 36 of the file `nemu/src/monitor/monitor.c`. If you do not know what is assertion, blame the 程序设计基础 course. But just ignore it now, and you will fix it in PA1.

To debug NEMU with gdb, type

```
make gdb
```

### Development Tracing

Once the compilation succeeds, the change of source code will be traced by `git`. Type

```
git log
```

If you see something like

```
commit 4072d39e5b6c6b6837077f2d673cb0b5014e6ef9
Author: tracer-ics2025 <tracer@njuics.org>
Date:   Sun Jul 26 14:30:31 2025 +0800

    >  run NEMU
    241220000 张三
    Linux 9900k 5.10.0-10-amd64 #1 SMP Debian 5.10.84-1 (2021-12-08) x86_64 GNU/Linux
    15:57:01 up 22 days,  6:01, 16 users,  load average: 0.00, 0.00, 0.00
```

this means the change is traced successfully.

#### "一生一芯"的代码跟踪日志位于另一个分支

如果你参加"一生一芯", 请通过`git log tracer-ysyx`查看代码跟踪日志.

If you see the following message while executing make, this means the tracing fails.

```
fatal: Unable to create '/home/user/ics2025/.git/index.lock': File exists.

If no other git process is currently running, this probably means a
git process crashed in this repository earlier. Make sure no other git
process is running and remove the file manually to continue.
```

Try to clean the compilation result and compile again:

```
make clean
make
```

If the error message above always appears, please contact us as soon as possible.

#### 开发跟踪

我们使用`git`对你的实验过程进行跟踪, 不合理的跟踪记录会影响你的成绩. 往届有学长"完成"了某部分实验内容, 但我们找不到相应的git log, 最终该部分内容被视为没有完成. git log是独立完成实验的最有力证据, 完成了实验内容却缺少合理的git log, 不仅会损失大量分数, 还会给抄袭判定提供最有力的证据. 因此, 请你注意以下事项:

- 请你不定期查看自己的git log, 检查是否与自己的开发过程相符.
- 提交往届代码将被视为没有提交.
- 不要把你的代码上传到公开的地方(现在github个人账号也可以创建私有仓库了).
- 总是在工程目录下进行开发, 不要在其它地方进行开发, 然后一次性将代码复制到工程目录下, 这样`git`将不能正确记录你的开发过程.
- 不要修改`Makefile`中与开发跟踪相关的内容.
- 不要删除我们要求创建的分支, 否则会影响我们的脚本运行, 从而影响你的成绩
- 不要清除git log

偶然的跟踪失败不会影响你的成绩. 如果上文中的错误信息总是出现, 请尽快联系我们.

#### 我不是修读本课程的学生, 是否能够关闭开发跟踪?

可进行如下修改关闭开发跟踪:

```
diff --git a/Makefile b/Makefile
index c9b1708..b7b2e02 100644
--- a/Makefile
+++ b/Makefile
@@ -9,6 +9,6 @@
 define git_commit
-  -@git add .. -A --ignore-errors
-  -@while (test -e .git/index.lock); do sleep 0.1; done
-  -@(echo "> $(1)" && echo $(STUID) $(STUNAME) && uname -a && uptime) | git commit -F - $(GITFLAGS)
-  -@sync
+# -@git add .. -A --ignore-errors
+# -@while (test -e .git/index.lock); do sleep 0.1; done
+# -@(echo "> $(1)" && echo $(STUID) $(STUNAME) && uname -a && uptime) | git commit -F - $(GITFLAGS)
+# -@sync
 endef
```

### Local Commit

Although the development tracing system will trace the change of your code after every successful compilation, the trace record is not suitable for your development. This is because the code is still buggy at most of the time. Also, it is not easy for you to identify those bug-free traces. Therefore, you should trace your bug-free code manually.

When you want to commit the change, type

```
git add .
git commit --allow-empty
```

The `--allow-empty` option is necessary, because usually the change is already committed by development tracing system. Without this option, `git` will reject no-change commits. If the commit succeeds, you can see a log labeled with your student ID and name by

```
git log
```

To filter out the commit logs corresponding to your manual commit, use `--author` option with `git log`. For details about how to use this option, RTFM.

### Writing Report

#### 实验报告内容

你必须在实验报告中描述以下内容:

- 实验进度. 简单描述即可, 例如"我完成了所有内容", "我只完成了xxx".  
  缺少实验进度的描述, 或者描述与实际情况不符, 将被视为没有完成本次实验.
- 必答题.

你可以自由选择报告的其它内容. 你不必详细地描述实验过程, 但我们鼓励你在报告中描述如下内容:

- 你遇到的问题和对这些问题的思考
- 对讲义中蓝框思考题的看法
- 或者你的其它想法, 例如实验心得, 对提供帮助的同学的感谢等

认真描述实验心得和想法的报告将会获得分数的奖励; 蓝框题为选做, 完成了也不会得到分数的奖励, 但它们是经过精心准备的, 可以加深你对某些知识的理解和认识. 因此当你发现编写实验报告的时间所剩无几时, 你应该选择描述实验心得和想法. 如果你实在没有想法, 你可以提交一份不包含任何想法的报告, 我们不会强求. 但请不要

- 大量粘贴讲义内容
- 大量粘贴代码和贴图, 却没有相应的详细解释(让我们明显看出来是凑字数的)

来让你的报告看起来十分丰富, 编写和阅读这样的报告毫无任何意义, 你也不会因此获得更多的分数, 同时还可能带来扣分的可能.

### Submission

#### 如果你参加"一生一芯", 请忽略这里的提交要求

具体请参考"一生一芯"讲义中的要求.

Finally, you should submit your project to the submission website (具体提交方式请咨询ICS实验课程老师). To submit PA0, put your report file (ONLY `.pdf` file is accepted) under the project directory.

```
ics2025
├── 241220000.pdf   # put your report file here
├── abstract-machine
├── fceux-am
├── init.sh
├── Makefile
├── nemu
└── README.md
```

Double check whether everything is fine. In particular, you should check whether your `.pdf` file can be opened with a PDF reader.

#### 如何打开PDF文件?

STFW.

#### 又报错了

我知道, 那你说该怎么办呢?

## RTFSC and Enjoy

If you are new to GNU/Linux and finish this tutorial by yourself, congratulations! You have learned a lot! The most important, you have learned STFW and RTFM for using new tools and trouble-shooting. (反思一下, 你真的做到了吗?) With these skills, you can solve lots of troubles by yourself during PAs, as well as in the future.

In PA1, the first thing you will do is to [RTFSC](http://i.linuxtoy.org/docs/guide/ch48s06.html). If you have troubles during reading the source code, go to RTFM:

- If you can not find the definition of a function, it is probably a library function. Read `man` for more information about that function.
- If you can not understand the code related to hardware details, refer to the manual.

By the way, you will use C language for programming in all PAs. [Here](http://akaedu.github.io/book/) is an excellent tutorial about C language. It contains not only C language (such as how to use `printf()` and `scanf()`), but also other elements in a computer system (data structure, computer architecture, assembly language, linking, operating system, network...). It covers most parts of this course. You are strongly recommended to read this tutorial.

Finally, enjoy the journey of PAs, and you will find hardware is not mysterious, so does the computer system! But remember:

- STFW
- RTFM
- RTFSC

#### 必答题

独立解决问题是作为码农的一项十分重要的生存技能. 往届有同学在群里提出如下问题:

- su认证失败是怎么回事?
- grep提示no such file or directory是什么意思?
- 请问怎么卸载Ubuntu?
- C语言的xxx语法是什么意思?
- ignoring return vaule of 'scanf'是什么意思?
- 出现curl: not found该怎么办?
- 为什么strtok返回NULL?
- 为什么会有Segmentation fault这个错误?
- 什么是busybox?

请仔细阅读[提问的智慧](https://github.com/ryanhanwu/How-To-Ask-Questions-The-Smart-Way/blob/master/README-zh_CN.md)和[别像弱智一样提问](https://github.com/tangx/Stop-Ask-Questions-The-Stupid-Ways/blob/master/README.md) (这篇文章很短, 1分钟就能看完)这两篇文章, 结合自己在大一时提问和被提问, 以及完成PA0的经历, 写一篇不少于800字的读后感, 谈谈你对"好的提问"以及"通过STFW和RTFM独立解决问题"的看法.

Hint: 我们设置这道题并不是为了故意浪费大家的时间, 也不是为了禁止大家提出任何问题, 而是为了让大家知道"什么是正确的". 当你愿意为这些"正确的做法"去努力, 并且尝试用专业的方式提出问题的时候, 你就已经迈出了成为"成为专业人士"的第一步.

#### Reminder

This ends PA0. Please submit your project and report.
