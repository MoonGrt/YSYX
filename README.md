# YSYX

本仓库用于“一生一芯”学习与开发，包含 RISC-V 模拟器、Abstract Machine、测试程序、硬件实现以及相关第三方工具。仓库采用 Git 子模块管理外部项目，并通过补丁维护不适合单独创建远端仓库的本地适配。

## 目录结构

| 目录 | 内容 |
| --- | --- |
| `memu/` | 处理器模拟、调试及 RTL/Chisel 相关实现 |
| `abstract-machine/` | Abstract Machine 运行时环境 |
| `am-kernels/` | AM 测试、示例和 benchmark |
| `source/` | 学习与实现源码归档 |
| `thirdpartys/` | 通过 Git 子模块管理的外部项目 |
| `misc/` | 零散测试、MiniRV 工程和本地补丁 |
| `docs/` | 文档、学习记录和参考资料 |

原 README 中的阶段学习记录已迁移至 [`docs/notes.md`](docs/notes.md)。

## 获取项目

推荐在克隆时一并获取子模块：

```bash
git clone --recursive <repository-url>
cd YSYX
```

已经克隆主仓库时，可通过初始化脚本补齐子模块和环境变量：

```bash
./init.sh
source ~/.bashrc
```

`init.sh` 会根据自身所在位置确定项目根目录，因此仓库无需放在固定路径。脚本会设置以下变量：

- `YSYX_HOME`
- `MEMU_HOME`
- `AM_HOME`
- `AM_TEST_HOME`
- `NVBOARD_HOME`

脚本可以重复执行；它会更新 `.bashrc` 中受管理的环境块，并避免重复应用 `rt-thread-am` 补丁。

## 常用操作

根目录 Makefile 主要提供跨项目操作：

```bash
make clean-all
```

具体构建和运行应进入对应子项目。例如：

```bash
cd "$MEMU_HOME"
make menuconfig
make
```

AM 测试可以从 `am-kernels` 中选择目标：

```bash
cd "$AM_TEST_HOME/tests/am-tests"
make ARCH=riscv32-memu run
```

实际可用的架构和配置以各子项目 Makefile 为准。

## 子模块管理

外部项目位于 `thirdpartys/`，首次使用或更新后执行：

```bash
git submodule update --init --recursive
git submodule status
```

主仓库只记录子模块的提交指针。修改普通子模块时，应先在子模块仓库提交并推送，再回到主仓库提交更新后的指针。

### rt-thread-am 补丁

`rt-thread-am` 保持指向官方仓库，本地适配保存在：

```text
misc/patches/rt-thread-am.patch
```

运行 `./init.sh` 会自动应用该补丁。更新补丁前，先在 `thirdpartys/rt-thread-am` 中完成修改，再重新生成并验证补丁；不要让主仓库指向仅存在于本地的子模块提交。

#### 继续修改并生成新补丁

随后直接修改 `thirdpartys/rt-thread-am` 中的文件。当前工作区的差异同时包含“原补丁内容”和“本次新增修改”，因此从官方子模块提交生成的 diff 就是完整的新补丁：

```bash
git -C thirdpartys/rt-thread-am diff --binary \
  > misc/patches/rt-thread-am.patch
```

此时 `thirdpartys/rt-thread-am` 显示为已修改是正常现象。不要在子模块中提交，也不要把主仓库的子模块指针更新到仅存在于本机的提交；需要保存的是主仓库中的 `misc/patches/rt-thread-am.patch`。

## Dev Container

`.devcontainer/` 提供 Ubuntu 22.04、Verilator、GTKWave、SBT、Mill 和 RISC-V 交叉编译环境。在 VS Code 中打开仓库后，执行 **Dev Containers: Reopen in Container** 即可使用。

Dockerfile 的 `YSYX_HOME` 是可覆盖的构建参数，其他项目路径均由它派生：

```bash
docker build \
  --build-arg YSYX_HOME=/workspace/YSYX \
  -f .devcontainer/Dockerfile \
  -t ysyx:latest .
```

容器启动后仍建议运行一次 `./init.sh`，以初始化子模块并写入当前工作区对应的 shell 环境。

## 提交前检查

```bash
git status
git diff --check
git submodule status
```

提交时注意区分主仓库改动、子模块指针变化和子模块内部未提交修改。
