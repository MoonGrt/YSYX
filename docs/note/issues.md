# Issue

1. java.lang.ClassNotFoundException: build_.package_$

> build.sc 没被正确编译，或编译产物损坏/缺失

最常见原因: `.mill` 缓存损坏. 直接清缓存:

```bash
rm -rf .mill
rm -rf out
```

然后重新执行: 

```bash
mill clean
mill chisel.runMain Riscv32ETOP
```
