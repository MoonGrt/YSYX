# E阶段
## E1 C语言程序设计
## E2 硬件描述语言
## E3 Linux系统安装和基本使用
## E4.1 从C代码到二进制程序
## E4.2 C程序的执行
## E4.3 指令集模拟器
## E5.1 RTL代码的仿真
## E5.2 逻辑综合

1. 尝试使用综合器
    make syn error: `/bin/bash: line 1: yosys: command not found`
    > 查看 OSCPU/yosys-sta README. 安装yosys.
    > !!! 注意该部分运行后会改变默认 verilator

    `misc/test/yosys` 文件夹中:
    ```bash
    yosys alu.v
    ```
    ```yosys
    # Step1 细化(Elaboration)
    # 细化阶段的工作包括解析模块间的实例化关系, /
    # 计算模块实例的参数, 完成模块实例化的实例名和端口绑定等.
    hierarchy -check -top alu
    # 可视化
    show

    # Step2 粗粒度综合(Coarse-grain synthesis)
    # 采用字级单元(word-level cells)来描述设计:
    # $add, $and, $or, $not, $mux, $mem, $dff, $latch, $sr ...
    proc; opt; fsm; opt; memory; opt
    # 可视化
    show

    # Step3 细粒度综合(Fine-grain synthesis)
    techmap; opt
    # 可视化
    show

    # Step4 写出中间网表
    write_verilog alu.rtlil

    # Step5 工艺映射(Technology mapping)
    # 工艺映射是指从工艺无关的电路表示映射到具体工艺的实现.
    dfflibmap -liberty cell.lib
    read_liberty -lib cell.lib
    # 可视化
    show
    abc -liberty cell.lib
    # 可视化
    show

    # Step6 网表和报告生成
    write_verilog alu.netlist
    stat -liberty cell.lib

    ```

## E5.3 Verilog的RTL综合语义
## E5.4 标准单元库
## E5.5 物理设计

