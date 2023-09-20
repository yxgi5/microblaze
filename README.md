# microblaze 最小系统
mb时钟(200MHz)来自clk_wiz, 有dc有ic，通过axi_interconnect访问mig7, ddr3速率配置为800Mbps(clk400M),k7,a7都适用

# block design

[doc/system.pdf](doc/system.pdf)

# MicroBlaze 最小系统

# Jtag模式

可以选上 program fpga

也可以不选，先下载bitstream，再debug

# FPGA使用RGMII接口与PHY芯片连接时经验总结
```
1、rgmii信号中的接收时钟phy_rxclk为单端时钟，必须将此时钟接到FPGA中多功能时钟引脚（MRCC或SRCC）上，必须从正端（P）输⼊；
2、rgmii中接收信号（rxd、rxclk、rxctl）必须在FPGA中同⼀个bank或者相邻bank上，如果是在相邻bank上，rxclk必须接到MRCC中；
每个PHY芯⽚有4个rxd、4个txd、2个ctl信号，每个PHY共10个，4个PHY共40个信号；接收发送每个PHY各有两个时钟，总共1个PHY占⽤12个引脚。理论上1个bank可以接4个PHY芯⽚；
3、注意PHY芯⽚的供电电压与FPGA的供电电压是否相同；
```