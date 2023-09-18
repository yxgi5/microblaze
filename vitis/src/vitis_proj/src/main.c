/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include "bsp.h"

#if defined (XPAR_AXI_LITE_REG_NUM_INSTANCES) && (XPAR_AXI_LITE_REG_0_DEVICE_ID == 0)
volatile u32 __HW_VER__;
#endif

#if defined(XPAR_XGPIO_NUM_INSTANCES) && (XPAR_XCSI2TX_NUM_INSTANCES)
XGpio XGpioOutput;
#endif

int main()
{
	int Status ;

    init_platform();

#if defined(XPAR_XGPIO_NUM_INSTANCES) && (XPAR_XCSI2TX_NUM_INSTANCES)
    Status = xgpio_setup(&XGpioOutput, XPAR_GPIO_0_DEVICE_ID, 0, 0) ;
    if (Status != XST_SUCCESS)
	{
    	Xil_Assert(__FILE__, __LINE__);
		return XST_FAILURE ;
	}
#endif // XPAR_XGPIO_NUM_INSTANCES


#if defined(XPAR_XGPIO_I2C_0_AXI_GPIO_0_DEVICE_ID)
    Status = xgpio_init();
    if (Status != XST_SUCCESS)
	{
		Xil_Assert(__FILE__, __LINE__);
		return XST_FAILURE ;
	}
#elif defined (XPAR_XGPIO_NUM_INSTANCES)
    Status = xgpio_setup(&XGpioInst, XPAR_AXI_GPIO_0_DEVICE_ID, 0, 0);
    if (Status != XST_SUCCESS)
	{
		Xil_Assert(__FILE__, __LINE__);
		return XST_FAILURE ;
	}
#endif // XPAR_XGPIO_I2C_0_AXI_GPIO_0_DEVICE_ID


    bsp_printf("***************************\n\r");
    bsp_printf("Test common API.\n\r");
    bsp_printf("\r\n%s,%s\r\n",__DATE__,__TIME__);
#if defined (XPAR_AXI_LITE_REG_NUM_INSTANCES) && (XPAR_AXI_LITE_REG_0_DEVICE_ID == 0)
	__HW_VER__ = AXI_LITE_REG_mReadReg(XPAR_AXI_LITE_REG_0_S00_AXI_BASEADDR, AXI_LITE_REG_S00_AXI_SLV_REG0_OFFSET);
	bsp_printf("hardware ver = 0x%08x\n\r", __HW_VER__);
#endif // XPAR_AXI_LITE_REG_NUM_INSTANCES
#if defined (__SW_VER__)
    bsp_printf("software ver = 0x%08x\n\r", __SW_VER__);
    bsp_printf("***************************\n\r");
#endif // __SW_VER__

#if defined(__SIL9136_H__)
    sil9136_config();
#endif

#if defined(XPAR_XGPIO_NUM_INSTANCES) && defined (XPAR_XCSI2TX_NUM_INSTANCES)
	XGpio_DiscreteWrite(&XGpioOutput, 1, 0x24); // RGB888
//	XGpio_DiscreteWrite(&XGpioOutput, 1, 0x2A); // RAW8
//	XGpio_DiscreteWrite(&XGpioOutput, 1, 0x2B); // RAW10
//	XGpio_DiscreteWrite(&XGpioOutput, 1, 0x2C); // RAW12
//	XGpio_DiscreteWrite(&XGpioOutput, 1, 0x1E); // YUV422_8bit
//	XGpio_DiscreteWrite(&XGpioOutput, 2, VIDEO_COLUMNS*24/8<<16); // WC RGB888
//	XGpio_DiscreteWrite(&XGpioOutput, 2, 3840*24/8<<16); // WC RGB888
//	XGpio_DiscreteWrite(&XGpioOutput, 2, (1920*12/8)<<16); // WC RAW12
	XGpio_DiscreteWrite(&XGpioOutput, 2, (1920*24/8)<<16); // WC RGB888
//	XGpio_DiscreteWrite(&XGpioOutput, 2, (VIDEO_COLUMNS*10/8)<<16); // WC RAW10
//	XGpio_DiscreteWrite(&XGpioOutput, 2, (1920*16/8)<<16); // WC YUV422_8bit
#endif // XPAR_XGPIO_NUM_INSTANCES

#if defined (SER_CFG) || defined (DES_CFG)
    // MAX9296 config
    u8 ret8=0;
#if defined (DES_CFG)
    Status = xgpio_i2c_reg16_read(I2C_NO_3, 0x90>>1, 0x0000, &ret8, STRETCH_ON);
    Status = xgpio_i2c_reg16_read(I2C_NO_3, 0x90>>1, 0x0001, &ret8, STRETCH_ON);
#if defined (SERDES_3G)
    Status = xgpio_i2c_reg16_write(I2C_NO_3, 0x90>>1, 0x0001, 0x01, STRETCH_ON); // 3Gbps
    Status = xgpio_i2c_reg16_write(I2C_NO_3, 0x90>>1, 0x0010, 0x21, STRETCH_ON); // reset link
#else
    Status = xgpio_i2c_reg16_write(I2C_NO_3, 0x90>>1, 0x0001, 0x02, STRETCH_ON); // 6Gbps
	Status = xgpio_i2c_reg16_write(I2C_NO_3, 0x90>>1, 0x0010, 0x21, STRETCH_ON); // reset link
#endif // SERDES_3G
    max929x_write_array(I2C_NO_3, max9296_rgb888_gmsl2);
#endif // DES_CFG
#if defined (SER_CFG)
    Status = xgpio_i2c_reg16_read(I2C_NO_3, 0x80>>1, 0x0000, &ret8, STRETCH_ON);
    Status = xgpio_i2c_reg16_read(I2C_NO_3, 0x80>>1, 0x0001, &ret8, STRETCH_ON);
#if defined (SERDES_3G)
    Status = xgpio_i2c_reg16_write(I2C_NO_3, 0x80>>1, 0x0001, 0x04, STRETCH_ON); // 3Gbps
    Status = xgpio_i2c_reg16_write(I2C_NO_3, 0x80>>1, 0x0010, 0x21, STRETCH_ON); // reset link
#else
    Status = xgpio_i2c_reg16_write(I2C_NO_3, 0x80>>1, 0x0001, 0x08, STRETCH_ON); // 6Gbps
    Status = xgpio_i2c_reg16_write(I2C_NO_3, 0x80>>1, 0x0010, 0x21, STRETCH_ON); // reset link
#endif // SERDES_3G
//    max929x_write_array(I2C_NO_3, max9295_rgb888_gmsl2);
    max929x_write_array(I2C_NO_3, max96717_rgb888_gmsl2);
#endif // SER_CFG
#if defined (DES_CFG)
    Status = xgpio_i2c_reg16_read(I2C_NO_3, 0x90>>1, 0x0000, &ret8, STRETCH_ON);
	Status = xgpio_i2c_reg16_read(I2C_NO_3, 0x90>>1, 0x0001, &ret8, STRETCH_ON);
#endif // DES_CFG
#if defined (SER_CFG)
    Status = xgpio_i2c_reg16_read(I2C_NO_3, 0x80>>1, 0x0000, &ret8, STRETCH_ON);
    Status = xgpio_i2c_reg16_read(I2C_NO_3, 0x80>>1, 0x0001, &ret8, STRETCH_ON);
#endif // SER_CFG
#endif // SER_CFG || DES_CFG

#if defined (XPAR_XAXIS_SWITCH_NUM_INSTANCES)
    Status = axis_switch_cfg();
    if (Status != XST_SUCCESS)
	{
		Xil_Assert(__FILE__, __LINE__);
		return XST_FAILURE ;
	}
#endif // XPAR_XAXIS_SWITCH_NUM_INSTANCES

#if defined (XPAR_XCLK_WIZ_NUM_INSTANCES)
    Status = clkwiz_config();
    if (Status != XST_SUCCESS)
	{
		Xil_Assert(__FILE__, __LINE__);
		return XST_FAILURE ;
	}
#endif // XPAR_XCLK_WIZ_NUM_INSTANCES

#if defined (XPAR_XVTC_NUM_INSTANCES)
    Status = vtc_config();
    if (Status != XST_SUCCESS)
	{
		Xil_Assert(__FILE__, __LINE__);
		return XST_FAILURE ;
	}
#endif // XPAR_XVTC_NUM_INSTANCES

#if defined (XPAR_XV_TPG_NUM_INSTANCES)
    Status = tpg_config();
    if (Status != XST_SUCCESS)
	{
		Xil_Assert(__FILE__, __LINE__);
		return XST_FAILURE ;
	}
#endif // XPAR_XV_TPG_NUM_INSTANCES


#if defined (XPAR_XAXIVDMA_NUM_INSTANCES)
    clear_display();
//    vdma_config_direct();
	Status = vdma_config();
	if (Status != XST_SUCCESS)
	{
		Xil_Assert(__FILE__, __LINE__);
		return XST_FAILURE ;
	}
#endif // XPAR_XAXIVDMA_NUM_INSTANCES


#if defined (XPAR_XCSI2TX_NUM_INSTANCES)
	Status = csi_tx_config();
	if (Status != XST_SUCCESS)
	{
		Xil_Assert(__FILE__, __LINE__);
		return XST_FAILURE ;
	}
#endif // XPAR_XCSI2TX_NUM_INSTANCES

#if defined (XPAR_XCSI_NUM_INSTANCES)
	Status = csi_rx_config();
	if (Status != XST_SUCCESS)
	{
		Xil_Assert(__FILE__, __LINE__);
		return XST_FAILURE ;
	}
#endif // XPAR_XCSI_NUM_INSTANCES

#if defined (UDP_UPDATE)
	udp_server_setup();
#elif defined (TCP_UPDATE)
	tcp_server_setup();
#endif

    while(1)
    {
#if defined (UDP_UPDATE)
    	udp_transfer_data();
#elif defined (TCP_UPDATE)
    	tcp_transfer_data();
#endif

//    	bsp_printf("pi=%f\n\r",3.1415);
//    	ret32 = xgpio_i2c_reg16_read(I2C_NO_0, 0x80>>1, 0x0000, &ret8, STRETCH_ON);

		XGpio_DiscreteWrite(&XGpioInst, 1, 0xf0);
		usleep(1000000);
		XGpio_DiscreteWrite(&XGpioInst, 1, 0xf1);
		usleep(1000000);
		XGpio_DiscreteWrite(&XGpioInst, 1, 0xf2);
		usleep(1000000);
		XGpio_DiscreteWrite(&XGpioInst, 1, 0xf4);
		usleep(1000000);
		XGpio_DiscreteWrite(&XGpioInst, 1, 0xf8);
		usleep(1000000);
    }
	// never reached
    cleanup_platform();
    return 0;
}
//
//
//#include <stdio.h>
//#include "platform.h"
//#ifndef __PPC__
//#include "xil_printf.h"
//#endif
//#include "xstatus.h"
////#include "xvidc.h"
////#include "tpg/tpg.h"
////#include "clk_wiz.h"
////#include "xvtc.h"
////#include "vtc/video_resolution.h"
////#include "vtc/vtiming_gen.h"
//#if defined (ARMR5) || (__aarch64__) || (__arm__)
//#include "xscugic.h"
//#else
//#include "xintc.h"
//#endif
//#include "xil_cache.h"
//#include "xgpio.h"
//#include "sleep.h"
//
//#define VDMA_ID          		XPAR_AXIVDMA_0_DEVICE_ID
//#define VDMA_BASE_ADDR 			0x08000000
////#define VDMA1_ID          		XPAR_AXIVDMA_1_DEVICE_ID
////#define VDMA1_BASE_ADDR			0x10000000
//
////#define FRAME_BUFFER_BASE_ADDR  0x10000000 // for zynq
//////#define FRAME_BUFFER_BASE_ADDR  0x81000000 // for microblaze
//
//#if defined (__MICROBLAZE__)
//	#define DDR_BASEADDR XPAR_MICROBLAZE_DCACHE_BASEADDR
//#else
//	#define DDR_BASEADDR XPAR_DDR_MEM_BASEADDR
//#endif
//
//#define FRAME_BUFFER_BASE_ADDR  	(DDR_BASEADDR + (0x10000000))
//
////#define FRAME_BUFFER_BASE_ADDR	0x10000000
//#define FRAME_BUFFER_BASE_ADDR	0x81000000
////#define FRAME_BUFFER_SIZE		0x400000	//0x400000 for max 1080p YCbCr422 8bpc
//#define FRAME_BUFFER_SIZE		0x600000	//0x600000 for max 1080p RGB888 8bpc
//#define FRAME_BUFFER_1			FRAME_BUFFER_BASE_ADDR
//#define FRAME_BUFFER_2			FRAME_BUFFER_BASE_ADDR + FRAME_BUFFER_SIZE
//#define FRAME_BUFFER_3			FRAME_BUFFER_BASE_ADDR + (FRAME_BUFFER_SIZE*2)
//
//#define FRAME_BUFFER_BASE_ADDR1	FRAME_BUFFER_BASE_ADDR + (FRAME_BUFFER_SIZE*3)
//#define FRAME_BUFFER_4			FRAME_BUFFER_BASE_ADDR1
//#define FRAME_BUFFER_5			FRAME_BUFFER_BASE_ADDR1 + FRAME_BUFFER_SIZE
//#define FRAME_BUFFER_6			FRAME_BUFFER_BASE_ADDR1 + (FRAME_BUFFER_SIZE*2)
//
//#define  XGPIO_ID  XPAR_AXI_GPIO_0_DEVICE_ID
//XGpio XGpioInst;
//
////XGPIO初始化
//int xgpio_init(void)
//{
//	int Status ;
//
//	u32 ret;
//
//	Status = XGpio_Initialize(&XGpioInst, XGPIO_ID) ;
//	if (Status != XST_SUCCESS)
//	{
//		return XST_FAILURE ;
//	}
//
//	/* set as output */
//	//设置 gpio端口 为输出
////	XGpio_DiscreteWrite(&XGpioInst, 1, 0xfff);
//	XGpio_SetDataDirection(&XGpioInst, 1, 0xf0);
//	XGpio_DiscreteWrite(&XGpioInst, 1, 0xf0);
////	XGpio_SetDataDirection(&XGpioInst, 2, 0x0);
////	XGpio_DiscreteWrite(&XGpioInst, 2, 1);
//
//	return XST_SUCCESS ;
//}
//
//int main()
//{
//    init_platform();
//    xgpio_init();
////#define  XGPIO_ID  XPAR_AXI_GPIO_0_DEVICE_ID
////XGpio XGpioInst;
////	Status = XGpio_Initialize(&XGpioInst, XGPIO_ID) ;
////	if (Status != XST_SUCCESS)
////	{
////		return XST_FAILURE ;
////	}
////	XGpio_SetDataDirection(&XGpioInst, 1, 0xf0);
////	XGpio_DiscreteWrite(&XGpioInst, 1, 0xf0);
//    print("\n\r");
//    print("Hello World\n\r");
//    print("Successfully ran Hello World application\n\r");
//
////    clkwiz_vtc_cfg();
////    tpg_config();
////    clear_display();
////    vdma_config();
//
//	while(1)
//	{
//		XGpio_DiscreteWrite(&XGpioInst, 1, 0xf0);
//		usleep(1000000);
//		XGpio_DiscreteWrite(&XGpioInst, 1, 0xf1);
//		usleep(1000000);
//		XGpio_DiscreteWrite(&XGpioInst, 1, 0xf2);
//		usleep(1000000);
//		XGpio_DiscreteWrite(&XGpioInst, 1, 0xf4);
//		usleep(1000000);
//		XGpio_DiscreteWrite(&XGpioInst, 1, 0xf8);
//		usleep(1000000);
//	}
//
//    cleanup_platform();
//    return 0;
//}
