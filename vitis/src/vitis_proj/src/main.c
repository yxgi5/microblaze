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

#include <stdio.h>
#include "platform.h"
#ifndef __PPC__
#include "xil_printf.h"
#endif
#include "xstatus.h"
//#include "xvidc.h"
//#include "tpg/tpg.h"
//#include "clk_wiz.h"
//#include "xvtc.h"
//#include "vtc/video_resolution.h"
//#include "vtc/vtiming_gen.h"
#if defined (ARMR5) || (__aarch64__) || (__arm__)
#include "xscugic.h"
#else
#include "xintc.h"
#endif
#include "xil_cache.h"
#include "xgpio.h"
#include "sleep.h"

#define VDMA_ID          		XPAR_AXIVDMA_0_DEVICE_ID
#define VDMA_BASE_ADDR 			0x08000000
//#define VDMA1_ID          		XPAR_AXIVDMA_1_DEVICE_ID
//#define VDMA1_BASE_ADDR			0x10000000

//#define FRAME_BUFFER_BASE_ADDR  0x10000000 // for zynq
////#define FRAME_BUFFER_BASE_ADDR  0x81000000 // for microblaze

#if defined (__MICROBLAZE__)
	#define DDR_BASEADDR XPAR_MICROBLAZE_DCACHE_BASEADDR
#else
	#define DDR_BASEADDR XPAR_DDR_MEM_BASEADDR
#endif

#define FRAME_BUFFER_BASE_ADDR  	(DDR_BASEADDR + (0x10000000))

//#define FRAME_BUFFER_BASE_ADDR	0x10000000
#define FRAME_BUFFER_BASE_ADDR	0x81000000
//#define FRAME_BUFFER_SIZE		0x400000	//0x400000 for max 1080p YCbCr422 8bpc
#define FRAME_BUFFER_SIZE		0x600000	//0x600000 for max 1080p RGB888 8bpc
#define FRAME_BUFFER_1			FRAME_BUFFER_BASE_ADDR
#define FRAME_BUFFER_2			FRAME_BUFFER_BASE_ADDR + FRAME_BUFFER_SIZE
#define FRAME_BUFFER_3			FRAME_BUFFER_BASE_ADDR + (FRAME_BUFFER_SIZE*2)

#define FRAME_BUFFER_BASE_ADDR1	FRAME_BUFFER_BASE_ADDR + (FRAME_BUFFER_SIZE*3)
#define FRAME_BUFFER_4			FRAME_BUFFER_BASE_ADDR1
#define FRAME_BUFFER_5			FRAME_BUFFER_BASE_ADDR1 + FRAME_BUFFER_SIZE
#define FRAME_BUFFER_6			FRAME_BUFFER_BASE_ADDR1 + (FRAME_BUFFER_SIZE*2)

#define  XGPIO_ID  XPAR_AXI_GPIO_0_DEVICE_ID
XGpio XGpioInst;

//XGPIO初始化
int xgpio_init(void)
{
	int Status ;

	u32 ret;

	Status = XGpio_Initialize(&XGpioInst, XGPIO_ID) ;
	if (Status != XST_SUCCESS)
	{
		return XST_FAILURE ;
	}

	/* set as output */
	//设置 gpio端口 为输出
//	XGpio_DiscreteWrite(&XGpioInst, 1, 0xfff);
	XGpio_SetDataDirection(&XGpioInst, 1, 0xf0);
	XGpio_DiscreteWrite(&XGpioInst, 1, 0xf0);
//	XGpio_SetDataDirection(&XGpioInst, 2, 0x0);
//	XGpio_DiscreteWrite(&XGpioInst, 2, 1);

	return XST_SUCCESS ;
}

int main()
{
    init_platform();
    xgpio_init();
    print("\n\r");
    print("Hello World\n\r");
    print("Successfully ran Hello World application\n\r");

//    clkwiz_vtc_cfg();
//    tpg_config();
//    clear_display();
//    vdma_config();

	while(1)
	{
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

    cleanup_platform();
    return 0;
}
