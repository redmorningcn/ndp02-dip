//#include  "config.h"
#include <includes.h>

//#define		EX_DOG		sp706
#define		WATCHDOG	28		//P028

/****************************************************************************
* ���ƣ�void  InitWatchDog(void)
* ���ܣ���ʼ�����Ź�
* ��ڲ�������
* ���ڲ�������
****************************************************************************/
void  InitWatchDog(void)
{
	WDT_Init(WDT_CLKSRC_IRC,WDT_MODE_RESET);
	WDT_Start(2000000);
	FeedDog();
//	GPIO_PinselConfig(WATCHDOG,0);	
//
//	FeedDog();

}

/****************************************************************************
* ���ƣ�void  FeedDog(void)
* ���ܣ����Ź�ι��������
* ��ڲ�������
* ���ڲ�������
****************************************************************************/
void  FeedDog(void)
{  
	WDT_Feed();
//   if(GPIO_ReadIoVal(WATCHDOG))
//   {
//   		GPIO_SetOrClearValue(WATCHDOG,0);
//   }
//   else
//   {
//   		GPIO_SetOrClearValue(WATCHDOG,1);	
//   }
}



__asm void JMP_Boot( uint32_t address ){
   LDR SP, [R0]		;Load new stack pointer address
   LDR PC, [R0, #4]	;Load new program counter address
}

#define	Boot_APP_START_ADDR 0
/****************************************************************************
* ���ƣ�void  FeedDog(void)
* ���ܣ����Ź�ι��������
* ��ڲ�������
* ���ڲ�������
****************************************************************************/
void  ResetSys(void)
{  
//	while(1);	
	//����app
//void Boot( void )
//{
//	 void (*userProgram)();   					           /*����ָ��*/

	SCB->VTOR = Boot_APP_START_ADDR & 0x1FFFFF80;	//ƫ���ж�����

	JMP_Boot(Boot_APP_START_ADDR);
//	userProgram = (void (*)()) (USER_APP_START_ADDR+1);
//	(*userProgram)();													/*����						*/	 
	
}

