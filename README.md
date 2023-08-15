# microblaze 最小系统
mb时钟(200MHz)来自clk_wiz, 有dc有ic，通过axi_interconnect访问mig7, ddr3速率配置为1600Mbps(clk800M),k7适用,a7不行(最多800Mbps)

# block design

[doc/system.pdf](doc/system.pdf)

# MicroBlaze 最小系统

# Jtag模式

可以选上 program fpga

也可以不选，先下载bitstream，再debug

