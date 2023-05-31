set_property CFGBVS VCCO [current_design]
set_property CONFIG_VOLTAGE 3.3 [current_design]
set_property BITSTREAM.GENERAL.COMPRESS true [current_design]
set_property BITSTREAM.CONFIG.CONFIGRATE 50 [current_design]
set_property BITSTREAM.CONFIG.SPI_BUSWIDTH 4 [current_design]
set_property BITSTREAM.CONFIG.SPI_FALL_EDGE Yes [current_design]
set_property BITSTREAM.CONFIG.CONFIGFALLBACK ENABLE [current_design]
set_property CONFIG_MODE SPIx4 [current_design]

set_property PACKAGE_PIN H26 [get_ports reset_n]
set_property IOSTANDARD LVCMOS33 [get_ports reset_n]

set_property PACKAGE_PIN G22 [get_ports sys_clk]
set_property IOSTANDARD LVCMOS33 [get_ports sys_clk]
create_clock -name sys_clk -period 20 [get_ports sys_clk]

set_property IOSTANDARD LVCMOS33 [get_ports {qspi_flash_ss_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports qspi_flash_io0_io]
set_property IOSTANDARD LVCMOS33 [get_ports qspi_flash_io1_io]
set_property IOSTANDARD LVCMOS33 [get_ports qspi_flash_io2_io]
set_property IOSTANDARD LVCMOS33 [get_ports qspi_flash_io3_io]
set_property PACKAGE_PIN C23 [get_ports {qspi_flash_ss_io[0]}]
set_property PACKAGE_PIN B24 [get_ports qspi_flash_io0_io]
set_property PACKAGE_PIN A25 [get_ports qspi_flash_io1_io]
set_property PACKAGE_PIN B22 [get_ports qspi_flash_io2_io]
set_property PACKAGE_PIN A22 [get_ports qspi_flash_io3_io]


set_property PACKAGE_PIN B17 [get_ports uart_0_rxd]
set_property IOSTANDARD LVCMOS33 [get_ports uart_0_rxd]
set_property PACKAGE_PIN A17 [get_ports uart_0_txd]
set_property IOSTANDARD LVCMOS33 [get_ports uart_0_txd]


set_property PACKAGE_PIN G26 [get_ports {gpio_tri_io[7]}]
set_property PACKAGE_PIN E26 [get_ports {gpio_tri_io[6]}]
set_property PACKAGE_PIN G25 [get_ports {gpio_tri_io[5]}]
set_property PACKAGE_PIN D26 [get_ports {gpio_tri_io[4]}]

set_property PACKAGE_PIN D25 [get_ports {gpio_tri_io[3]}]
set_property PACKAGE_PIN C26 [get_ports {gpio_tri_io[2]}]
set_property PACKAGE_PIN D23 [get_ports {gpio_tri_io[1]}]
set_property PACKAGE_PIN A23 [get_ports {gpio_tri_io[0]}]
set_property IOSTANDARD LVCMOS33 [get_ports {gpio_tri_io[*]}]