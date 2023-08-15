# microblaze 最小系统
mb时钟来自mig7, 有dc无ic，通过axi_smc访问mig7, k7支持ddr3速率配置为1600Mbps(clk800M),a7不行(最多600Mbps)

# block design

[doc/system.pdf](doc/system.pdf)

# MicroBlaze 最小系统

# Jtag模式

可以选上 program fpga

也可以不选，先下载bitstream，再debug

