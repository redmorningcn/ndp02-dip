//#include "config.h"
//#include "CpuDrive.h" 
//#include "HardDrive.h" 

#include <includes.h>
/*
#define		Led0	P216							
#define		Led1	P217							
#define		Led2	P218							
#define		Led3	P219							
#define		Led4	P220
#define		Led5	P221
#define		Led6	P222
#define		Led7	P223
*/

//#define		Led3	P216							
//#define		Led2	P217							
//#define		Led1	P218							
//#define		Led0	P219							
//#define		Led7	P220
//#define		Led6	P221
//#define		Led5	P222
//#define		Led4	P223

#define		Led_3	115							
#define		Led_2	116							
#define		Led_1	109							
#define		Led_0	110							
#define		Led_7	114
#define		Led_6	117
#define		Led_4	108
#define		Led_5	104


#define		Led0	Led_7							
#define		Led1	Led_0							
#define		Led2	Led_1							
#define		Led3	Led_4							
#define		Led4	Led_5
#define		Led5	Led_6
#define		Led6	Led_2
#define		Led7	Led_3
/**/
#define		LED_MAX	8

typedef struct _stcLed_
                {
                    volatile 	uint32  WorkingFlag;            //ָʾ�ƿ�����־
                    volatile 	uint32  times;            		//ָʾ����˸�Ĵ���
                    volatile 	uint32  WorkXms;              	//ָʾ������ʱ��
                    volatile 	uint32  unWorkXms;             	//ָʾ�Ʋ�����ʱ��
                    volatile 	uint32	TotalTime;
                    volatile 	uint32  StarTimer;
                }stcLed;

stcLed	sLed[8] =
			{
				{0,0,0,0,1,0},
				{0,0,0,0,1,0},
				{0,0,0,0,1,0},
				{0,0,0,0,1,0},
				{0,0,0,0,1,0},
				{0,0,0,0,1,0},
				{0,0,0,0,1,0},
				{0,0,0,0,1,0},
			};
			
uint8  	HLAB_i;
uint32  CurentTime;

//------------------------------------------------------------------------
//	��	�� ��void LedUnLight(void)
//	��	�� ��ָʾ�Ƴ�����
// ��ڲ�����
// ���ڲ�����
//------------------------------------------------------------------------
void UnLightLed(uint8 num)
{
	uint16	LedBuf[LED_MAX] = {Led0,Led1,Led2,Led3,Led4,Led5,Led6,Led7};

	if(num>8)
	{
		return ;
	}
	if(num<8)
	{
//2014	 	IO2SET  |=  (0x00000001 << ( num+16 ));
		GPIO_SetOrClearValue(LedBuf[num],1);
	}
}
//------------------------------------------------------------------------
//	��	�� ��void LedLight(void)
//	��	�� ��ָʾ�Ƴ�����
// ��ڲ�����
// ���ڲ�����
//------------------------------------------------------------------------
void LightLed(uint8 num)
{
	uint16	LedBuf[LED_MAX] = {Led0,Led1,Led2,Led3,Led4,Led5,Led6,Led7};

	if(num>8)
	{
		return ;
	}
	if(num<8)
	{
//2014	 	IO2CLR  |=  (0x00000001 << ( num+16 ));
		GPIO_SetOrClearValue(LedBuf[num],0);
	}
}

//------------------------------------------------------------------------
//	��	�� ��void OnLed(uint8 num,uint32 times,uint16 LightTime,uint16 unLightTime)
//	��	�� ������ָʾ��
// ��ڲ�����uint8 Num			���ƵĶ�Ӧ���	 ���� Driver.h �й�����
//			 uint16	times			��������Ĵ���
//			 uint16	LightTime		���ʱ��  �� 0.1sΪ��λ
//			 uint16	unLightTime		�����ʱ�� �� 0.1s Ϊ��λ
// ���ڲ����������ɹ����� TRUE	����ʧ�ܷ��� FAULSE
//------------------------------------------------------------------------
void OnLed(uint8 num,uint32 times,uint16	LightTime,uint16 unLightTime)
{
	FeedDog();
	
	if(num >= LED_MAX || times == 0 || sLed[num].WorkingFlag)
	{
	    return;
	}
	if( LightTime ==0 || times == 0 )
	{
		return;
	}
	
	sLed[num].times 		= times;
	sLed[num].WorkXms		= LightTime * 10;
	sLed[num].unWorkXms 	= unLightTime * 10;
	sLed[num].WorkXms		= LightTime;
	sLed[num].unWorkXms 	= unLightTime;	
	sLed[num].TotalTime 	= sLed[num].WorkXms + sLed[num].unWorkXms ;
	sLed[num].StarTimer		= GetSysTime();
	sLed[num].WorkingFlag	= 1;
	LightLed(num);	
}

//------------------------------------------------------------------------
//	��	�� ��void OnAllLed(void)
//	��	�� ��ȫ��
// ��ڲ�����
// ���ڲ�����
//------------------------------------------------------------------------
void OnAllLed(void)
{
	uint8 num;
	for(num = 0; num < LED_MAX; num++)
	{
		OnLed(num,100,10000,0);						//����
    }
}

//------------------------------------------------------------------------
//	��	�� ��void LedOff(uint8 LedNum)
//	��	�� ���رն�Ӧ���ָʾ��
// ��ڲ������� 
// ���ڲ�����
//------------------------------------------------------------------------
void OffLed(uint8 num)
{
	sLed[num].WorkingFlag	= 0;            //ָʾ�ƿ�����־
    sLed[num].times			= 0;            //ָʾ����˸�Ĵ���
    sLed[num].WorkXms		= 0;            //ָʾ������ʱ��
    sLed[num].unWorkXms		= 0;          	//ָʾ�Ʋ�����ʱ��
    sLed[num].TotalTime		= 1;
    sLed[num].StarTimer		= 0;
    UnLightLed(num);
}

//------------------------------------------------------------------------
//	��	�� ��void OffAllLed(void)
//	��	�� ����ȫ��
// ��ڲ�������
// ���ڲ�����
//------------------------------------------------------------------------
void OffAllLed(void)
{
	uint8 num;
	for(num = 0; num < LED_MAX; num++)
	{
		OffLed(num);								//�ص�
    }
}

//------------------------------------------------------------------------
//	��	�� ��void HoldLed(void)
//	��	�� ��ָʾ��ά��
// ��ڲ�����
// ���ڲ�����
//------------------------------------------------------------------------
void HoldLed(void)
{
	CurentTime = GetSysTime();
	for(HLAB_i =	0; HLAB_i < LED_MAX; HLAB_i++)
	{
		if(sLed[HLAB_i].WorkingFlag)
		{
			if( ( (CurentTime - sLed[HLAB_i].StarTimer) % sLed[HLAB_i].TotalTime) 
					< sLed[HLAB_i].WorkXms)
				LightLed(HLAB_i);
			else
			{
				UnLightLed(HLAB_i);
			}
			if( ( (CurentTime	- sLed[HLAB_i].StarTimer) / sLed[HLAB_i].TotalTime) 
					>= (sLed[HLAB_i].times))
		   	{
		   	 	OffLed(HLAB_i);
		   	}
		}
	}
}

//------------------------------------------------------------------------
//	��	�� ��void InitLed( void )
//	��	�� ��ָʾ�Ƴ�ʼ��
// ��ڲ�����
// ���ڲ�����
//------------------------------------------------------------------------
void InitLed( void )
{
	uint16	LedBuf[LED_MAX] = {Led0,Led1,Led2,Led3,Led4,Led5,Led6,Led7};
	uint8	i;					
    
	for(i = 0; i< LED_MAX;i++)
	{
		GPIO_PinselConfig(LedBuf[i],0);	
	}

	for(i = 0;i < 2; i++)					
	{
		OnAllLed();								
	
	    DelayX10ms(25);

		OffAllLed();						
		
		DelayX10ms(25);
	}

	for(i = 0; i< LED_MAX;i++)
	{
		OnLed(i,100,10000,0);
		DelayX10ms(50);
	}

	OffAllLed();	
}
