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


```
microblaze最小系统有几个设置要点，取舍后形成合适的vivado工程

1. 是否64bit模式，一般bare是32bit, 跑linux系统最好用64bit模式
2. 是否要用DDR
3. MB时钟来源是从DDR还是其他时钟源，频率值采用多少
4. 是否开启DC，这样可以访问DDR
5. 是否开启IC，这样体积大的程序可以执行在DDR
6. 与MIG用SMC互联还是用AXICON
7. 系统时钟直接来自MIG的，应保证其sys_rst稳定(比如直接拉高或者外部输入)


kcu040不同点 (具体例子见`intr_system/microblaze`)
. 启动用的 qspi 不进行约束
. 网络约束 iodelay 是直接给时间(3.3v RTL8211E-VB直接可以用)，7系列是给tips
. MIG不一样


Jtag Uart 虚拟串口
如果要使用 Jtag Uart, MDM 应勾选 enable Jtag Uart
(zynq/zynqmp自带有)


bootloader
. 要注意 elf 偏移量设置
. 根据 qspi flash 大小 去注释或打开 #define QFLASH_LE_16MB
. 如果采用 rs485 打印，打开对应注释
. bootloader 的 lib 目录的 linker 文件可能需根据实际情况修改
```