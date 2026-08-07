# 单周期 NPC 综合与时序报告

测试对象为 `f2fc3f3c`（`npc & OpenBus Joint Compilation`）节点的 `Riscv32ETOP`。使用 Yosys 0.48、`thirdpartys/yosys-sta` 和 Nangate45 典型工艺库，目标时钟为 500 MHz。

STA 模型为取指和访存各接入一个异步读的 `256×32 bit` 寄存器存储器，并移除 DPI-C/difftest。为了让存储器与 CPU 保持在同一个 `core_clock` 时钟域，综合时临时跳过 clock-gating，采用 `share` 和 `DELAY-0`；功耗分析未运行。

结果：

- 关键路径延迟：`2.507 ns`
- 估计最高主频：`392.510 MHz`
- 500 MHz 下 WNS：`-0.548 ns`
- 标准单元：`63,107`
- 触发器：`17,696`
- 单元面积：`149,132.634 µm²`
- 综合检查：0 个问题

文件说明：

- `timing.rpt`：完整 setup/hold 时序路径和关键路径详情。
- `synthesis-stat.txt`：单元数量、类型和面积统计。
- `synthesis-check.txt`：Yosys 网表一致性检查。
- `max-fanout.rpt`：最大扇出检查。
- `max-capacitance.rpt`：最大负载电容检查。
- `max-transition.rpt`：最大转换时间检查。
- `setup-skew.rpt`、`hold-skew.rpt`：时钟偏斜报告。
- `abc.sdc`：ABC 映射时采用的驱动和负载约束。
- `sta.log`：iEDA STA 完整运行日志。

未保存门级网表和 Yosys 调试日志，它们约占 70 MiB，可由 RTL 和上述配置重新生成。
