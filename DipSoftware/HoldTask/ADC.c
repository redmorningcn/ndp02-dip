#include <includes.h>
#include  "lpc17xx_adc.h"

#define  	BATTERY_ADC 		130



void InitAdc(void)
{
	GPIO_PinselConfig(BATTERY_ADC,3);

	ADC_Init(LPC_ADC, 200000);
	ADC_IntConfig(LPC_ADC,ADC_ADINTEN4,DISABLE);
	ADC_ChannelCmd(LPC_ADC,ADC_ADINTEN4,ENABLE);	

//	GPIO_SetOrClearValue(BATTERY_ADC,1);
//	while(1);							
}

float		BatterVal;


uint16 ReadAdc(void)
{
	uint16_t	adc_value = 0;
	uint32	time;
//	InitAdc();
	ADC_StartCmd(LPC_ADC,ADC_START_NOW);
	//Wait conversion complete
	time = GetSysTime();
//	while((GetSysTime() - time) < 100);
	
	while (!(ADC_ChannelGetStatus(LPC_ADC,ADC_ADINTEN4,ADC_DATA_DONE)))
	{
		if(GetSysTime() - time > 100)
		{
			printfcom0("\r\n11 %d",adc_value);
			return 0;
		}
	}
	adc_value = ADC_ChannelGetData(LPC_ADC,ADC_ADINTEN4);
	//printfcom0("\r\n %d",adc_value*3000*2/4096);
	adc_value = adc_value*3000*2/4096;
	return adc_value;
}


//---------------------------------------------------------------------
//��    �ƣ�    void	InitAdc(void)
//��    �ܣ�   	��ʼ��ADC
//��ڲ�����    
//���ڲ�����    
//--------------------------------------------------------------------
//void	InitAdc(void)
//{
//	uint32	AdcCode = 0;
//
// 	PINSEL2 &= 0xFFFFFFDF;								//��ʼ���˿�
// 	PINSEL2 |= 0x00000010;
// 	PINSEL2 |= 0x00000080;
//
//	AdcCode = ADDR;
//	
//	AdcCode = 0;
//	    												/* ����ADCģ�����ã�����x<<n��ʾ��nλ����Ϊx(��x����һλ�������λ˳��) */
//    AdcCode = (1 << 7)                 	|				/* SEL = 1 ��ѡ��ͨ��0 */
//           (0x000000ff << 8) 			| 				/* CLKDIV = Fpclk / 1000000 - 1 ����ת��ʱ��Ϊ1MHz */
//           (0 << 16)                    |				/* BURST = 0 ���������ת������ */
//           (0 << 17)                    | 				/* CLKS = 0 ��ʹ��11clockת�� */
//           (1 << 21)                    | 				/* PDN = 1 �� ��������ģʽ(�ǵ���ת��ģʽ) */
//           (0 << 22)                    | 				/* TEST1:0 = 00 ����������ģʽ(�ǲ���ģʽ) */
//           (1 << 24)                    | 				/* START = 1 ��ֱ������ADCת�� */
//           (0 << 27);									/* EDGE = 0 (CAP/MAT�����½��ش���ADCת��)	 */
//	
//	ADCR = 	AdcCode;
//}

//------------------------------------------------------------------------
//  ��  �� ��void ReadAdc(void)
//  ��  �� ����ADCֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
//uint16 ReadAdc(void)
//{
////	uint32	i;
//	uint32	AdcData;
//	uint16	AdcVal;
//	uint32	Time;
//	
//	
//	Time = GetSysTime();
//	ADCR = ADCR | (1 << 24);      
//
//	do
//	{
//		DelayX10ms(1);
//		AdcData = ADDR;
//		
//		if(GetSysTime() - Time > 1*100)
//		{
//			break;
//		}
//	}while((AdcData & 0x80000000) == 0);
//		
//	AdcVal = ((AdcData>>6) & 0xffff03ff);
//	
//	return	AdcVal;
//}


//------------------------------------------------------------------------
//  ��  �� ��float GetBotVolt(void)
//  ��  �� ��ȡ��ص�ѹֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
int16 GetBotVolt(void)
{
//	int16	AdcVccVal;
	uint16			AdcVal;
	
	AdcVal 		= ReadAdc();

//	AdcVccVal 	= (float)((float)AdcVal / 1024)*3.3*2;
	
	return	AdcVal;
}

#define		RIGHT_DATA			0xff
#define		BOT_LOW_VOL_ERR		31
#define		BOT_LOW_VAL  		2800
								//2800mV
//------------------------------------------------------------------------
//  ��  �� ��uint8 JudgeEr2450Err(void)
//  ��  �� ����ADCֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
uint8	JudgeEr2450Err(void)
{
	int16	Er2450Volt;
	static	uint32	Time  = 0;
	static	uint32	Times = 0;
	static	uint8	ErrTyp = RIGHT_DATA;
	
	if(GetSysTime() - Time > 100)
	{
		Time	= GetSysTime();
	
		Er2450Volt = GetBotVolt();

		//printfcom0("\r\n battery volateg %d",Er2450Volt);

		if(Er2450Volt < BOT_LOW_VAL)
		{
			Times++;
		}
		else
		{
			Times = 0;
		}
		
		if(Times > 10)
		{
			ErrTyp = BOT_LOW_VOL_ERR;
		}
		else
		{
			ErrTyp = RIGHT_DATA;
		}
	}
		
	return	ErrTyp;
}

