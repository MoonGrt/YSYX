yosys counter.v

### 开展细化工作
hierarchy -check -top counter
### 输出 RTLIL 到终端
dump
### 将 RTLIL 写入文件
write_rtlil counter.rtlil
### 显示 RTLIL 内容
show

### 将所有过程描述转换为粗粒度表示
proc

### 优化 RTLIL 代码
opt

### 有限状态机的识别和处理
fsm

### 存储器的识别和处理
memory

### 粗粒度表示转换为细粒度表示
techmap

### 合并连续的信号
splitnets -ports


### 工艺映射
dfflibmap -liberty cell.lib



