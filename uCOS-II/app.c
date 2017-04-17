/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2012; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                        IAR Development Kits
*                                               on the
*
*                                            NXP LPC1768
*                                      LPC1766-SK KICKSTART KIT
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : FT
*                 DC
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


void	CirculatesTask(void)
{
	DisplayDipVal();

	LedTast();	

	Diptask();
}

uint8	GetPrintfFlg(void)
{
	stcSysRunPara 	sSysRunPara;

	if(GetSysRunPara((stcSysRunPara * )&sSysRunPara))
	{
		if(sSysRunPara.PrintfFlg)
		{
			return	sSysRunPara.PrintfFlg;
		}	
	}

	return	0;	
}

void	PrintfComSysInfo(void)
{
	static	uint32	time;
//	stcSysRunPara	sSysRunPara;
   	
	if(GetPrintfFlg())
	{
		if(GetSysTime() - time > 100)
		{
			printfcom0("\r\n�߶�1,%d,�߶�2,%d,");
			printfcom2("\r\n�߶�1,%d,�߶�2,%d,�ܶ�1,%d,�ܶ�2,%d,�¶�1,%d,�¶�2,%d,�ٶ�1,%d,�ٶ�2,%d,����,%d,����,%d",
			GetDip1Hig(),GetDip2Hig(),GetMyDip1Den(),GetMyDip2Den(),GetMyDip1Tmp(),GetMyDip2Tmp(),GetMySpeed1(),
			GetMySpeed2(),GetMyEngRotSpd(),GetMyLocoWorkState());	
				
			time = GetSysTime();
		}
	}
}

int  main (void)
{
    SystemInit();

	GPIO_Test();

    //nop();
    
	OneTaskTimes();

	DisplayString("         ");
	
	InitWatchDog();

//	PrintfTime();
	while(1)
	{	
		//printfcom2("\r\n");
		Diptask();
		//printfcom2("\r\n 2");
		
		EquipmentComTask();
		
		printfcom2("\r\n 3");
		
		CalcDip();
		//printfcom0("\r\n 4");
		StoreRecTask();
		
		printfcom2("\r\n 5");
	 	SpeedAndDistTast();
		
		//printfcom0("\r\n 6");
		CheckLocoStaTask();
		
		printfcom2("\r\n 7");	
		ErrDealTask();
		
		printfcom2("\r\n 8");
		if(GetSysTime() - GetReadDataDisplayTime() > 700)
		{
			if(GetSysTime() - GetReadDataDisplayTime() < 800)
			{
				ClaerDisplaySetWithoutStore();
			}
			DisplayDipVal();
		}
		//printfcom0("\r\n 9");
		LedTast();

		PrintfComSysInfo();
		//printfcom0("\r\n 10");
		//printfcom2flshrec();
		////
		
		
		////
//
//	RecRs485();
	}
//	GUI_Init();
//
//	OSInit();
//
//    OSTaskCreateExt((void (*)(void *))GPIO_Test,            /* Create the start task                                */                
//					(void          *)0,
//                    (OS_STK        *)&GPIO_TaskStartStk[GPIO_CFG_TASK_START_STK_SIZE - 1],
//                    (INT8U          )APP_CFG_TASK_START_PRIO+1,
//                    (INT16U         )APP_CFG_TASK_START_PRIO+1,
//                    (OS_STK        *)&GPIO_TaskStartStk[0],
//                    (INT32U         )GPIO_CFG_TASK_START_STK_SIZE,
//                    (void          *)0,
//                    (INT16U         )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
//
////     OSTaskCreateExt((void (*)(void *))uartTask,            /* Create the start task                                */                
////					(void          *)0,
////                    (OS_STK        *)&Uart_TaskStartStk[UART_CFG_TASK_START_STK_SIZE - 1],
////                    (INT8U          )APP_CFG_TASK_START_PRIO+2,
////                    (INT16U         )APP_CFG_TASK_START_PRIO+2,
////                    (OS_STK        *)&Uart_TaskStartStk[0],
////                    (INT32U         )UART_CFG_TASK_START_STK_SIZE,
////                    (void          *)0,
////                    (INT16U         )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
//
// 						
//	OSStart();	
//
//	return(1);
}

