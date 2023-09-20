#ifndef __CONFIG_H__
#define __CONFIG_H__

/*
 * for rs485 tcl settings(mb/zynq/znyqmp)
bsp config stdin axi_uartlite_0
bsp config stdout axi_uartlite_0
#bsp config stdin processer_ss_axi_uartlite_0
#bsp config stdout processer_ss_axi_uartlite_0
 */

/*
 * for sd card tcl settings(zynq/znyqmp)
bsp setlib -name xilffs
 */

/*
 * for dp port (znyqmp)
bsp setdriver -ip psu_dp -driver dppsu -ver 1.2
bsp regenerate
 */

/*
ps i2c dosen't support streching, use MIO/XGPIO or XIIC
 */
//#define	SER_CFG
//#define	DES_CFG
//#define	SERDES_3G

//#define SIL9136
//#define IT6801
//#define ADS7128

/*
 * for remote update tcl settings(zynq/znyqmp)
bsp setlib -name lwip211
bsp config mem_size 524288
bsp config memp_n_pbuf 1024
bsp config memp_n_tcp_pcb 32
bsp config memp_n_tcp_seg 1024
bsp config pbuf_pool_size 16384
bsp config tcp_snd_buf 65536
bsp config tcp_wnd 65535
bsp config n_rx_descriptors 512
bsp config n_tx_descriptors 512
 *
 */
#define UDP_UPDATE
//#define TCP_UPDATE

#endif // __CONFIG_H__
