# MEMU

`make run`

MEMU(NJU Emulator) is a simple but complete full-system emulator designed for teaching purpose.
Currently it supports x86, mips32, riscv32 and riscv64.
To build programs run above MEMU, refer to the [AM project](https://github.com/NJU-ProjectN/abstract-machine).

The main features of MEMU include
* a small monitor with a simple debugger
  * single step
  * register/memory examination
  * expression evaluation without the support of symbols
  * watch point
  * differential testing with reference design (e.g. QEMU)
  * snapshot
* CPU core with support of most common used instructions
  * x86
    * real mode is not supported
    * x87 floating point instructions are not supported
  * mips32
    * CP1 floating point instructions are not supported
  * riscv32
    * only RV32IM
  * riscv64
    * only RV64IM
* memory
* paging
  * TLB is optional (but necessary for mips32)
  * protection is not supported
* interrupt and exception
  * protection is not supported
* 5 devices
  * serial, timer, keyboard, VGA, audio
  * most of them are simplified and unprogrammable
* 2 types of I/O
  * port-mapped I/O and memory-mapped I/O

## DiffTest

执行 `make menuconfig`，打开 `Enable differential testing`，再在
`Reference design` 中选择：

- `NEMU (MEMU interpreter)`：使用 MEMU 内置解释器作为参考模型。
- `Spike`：使用 Spike 作为参考模型。

之后照常执行：

```sh
make run IMG=/path/to/program.bin
```

参考模型会自动构建并通过 `--diff` 加载。SoC 模式会同时覆盖
`0x20000000` 的 MROM 和 `0x0f000000` 的 SRAM；UART 等 MMIO 指令仍由
DUT 执行，并在提交时同步参考模型。
