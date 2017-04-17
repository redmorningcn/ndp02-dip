////#include 	"config.h"
////#include 	"String.h"
////#include	"Globe.h"
////#include	"HardDrive.h"
////#include	"CpuDrive.h"
////#include	"OperateCard.h"
////#include	"Tax2.h"
////#include	"FramStore.h"
//
#include    "includes.h"  
#include	"Card.h"
#include	"OperateCard.h"
#include	"FRAM.h"
//
uint16	l_CardType;
uint8	l_FlgZoneErrEvent	= NO_OCCUR;
////-------------------------------------------------------------------------------------------------
////��������:             ReadCardFlg()
////��������:             ����������ʶҳ,������Ҫ������
////��ڲ���:             ��
////���ڲ���:             IC����ҳ��ȡ
////˵��:                 
////--------------------------------------------------------------------------------------------------
//uint8	ReadCardFlg(stcCardFlg * sCardFlg)
//{	
//	////printfcom0("\r\n ReadCardFlg(stcCardFlg * sCardFlg)");
//	
//	ReadCard(CARD_FLG_ADDR,(uint8 *)sCardFlg,sizeof(stcCardFlg));		
//	
//	////printfcom0("\r\n ReadCard(CARD_FLG_ADDR,(uint8 *)sCardFlg,sizeof(stcCardFlg));");
//
//	////printfcom0("\r\n sCardFlg->sCardType.CrcCheck %d, CrcCheck %d",sCardFlg->sCardType.CrcCheck,GetCrc16Check((uint8 *)&sCardFlg->sCardType,sizeof(sCardFlg->sCardType) -2));
//
//	if(     (sCardFlg->sCardType.CardType[0] == sCardFlg->sCardType.CardType[1]) 
//		&& 	(sCardFlg->sCardType.CardType[1] == sCardFlg->sCardType.CardType[2])
//		&&	(sCardFlg->sCardType.CrcCheck == 
//		    GetCrc16Check((uint8 *)&sCardFlg->sCardType,sizeof(sCardFlg->sCardType) -2))
//	   )
//	{
//		l_CardType 		= sCardFlg->sCardType.CardType[0];			//IC�� ����
//		
//		l_FlgZoneErrEvent = NO_OCCUR;								//IC�� ��ʶҳ�����¼�
//		
//		//PrintfDebug("\r\n l_CardType %d",l_CardType);
//		
//		return 	1;
//	}
//	else
//	{
//		l_FlgZoneErrEvent = OCCUR;
//		l_CardType = 0x0000;
//		
//		return	0;
//	}
//}

uint8	ReadCardFlg(void)
{	
	////printfcom0("\r\n ReadCardFlg(stcCardFlg * sCardFlg)");
	stcCardType		sCardType;

	ReadCard(CARD_FLG_ADDR+sizeof(stcCardID),(uint8 *)&sCardType,sizeof(stcCardType));		
	
	////printfcom0("\r\n ReadCard(CARD_FLG_ADDR,(uint8 *)sCardFlg,sizeof(stcCardFlg));");

	////printfcom0("\r\n sCardFlg->sCardType.CrcCheck %d, CrcCheck %d",sCardFlg->sCardType.CrcCheck,GetCrc16Check((uint8 *)&sCardFlg->sCardType,sizeof(sCardFlg->sCardType) -2));

	if(     (sCardType.CardType[0] == sCardType.CardType[1]) 
		&& 	(sCardType.CardType[1] == sCardType.CardType[2])
		&&	(sCardType.CrcCheck == 
		    GetCrc16Check((uint8 *)&sCardType,sizeof(sCardType) -2))
	   )
	{
		l_CardType 		= sCardType.CardType[0];			//IC�� ����
		
		l_FlgZoneErrEvent = NO_OCCUR;								//IC�� ��ʶҳ�����¼�
		
		//PrintfDebug("\r\n l_CardType %d",l_CardType);
		
		return 	1;
	}
	else
	{
		l_FlgZoneErrEvent = OCCUR;
		l_CardType = 0x0000;
		
		return	0;
	}
}

//
////-------------------------------------------------------------------------------------------------
////��������:             ReadCOM0CardFlg()
////��������:             ����������ʶҳ,������Ҫ������
////��ڲ���:             ��
////���ڲ���:             IC����ҳ��ȡ
////˵��:                 
////--------------------------------------------------------------------------------------------------
//uint8	ReadCOM0CardFlg(stcCardFlg * sCardFlg)
//{	
//	//PrintfDebug("\r\n ReadCardFlg(stcCardFlg * sCardFlg)");
//	
//	//ReadCard(CARD_FLG_ADDR,(uint8 *)sCardFlg,sizeof(stcCardFlg));		
//	
//	//PrintfDebug("\r\n ReadCard(CARD_FLG_ADDR,(uint8 *)sCardFlg,sizeof(stcCardFlg));");
//
//	if(     (sCardFlg->sCardType.CardType[0] == sCardFlg->sCardType.CardType[1]) 
//		&& 	(sCardFlg->sCardType.CardType[1] == sCardFlg->sCardType.CardType[2])
//		&&	(sCardFlg->sCardType.CrcCheck == 
//		    GetCrc16Check((uint8 *)&sCardFlg->sCardType,sizeof(sCardFlg->sCardType) -2))
//	   )
//	{
//		l_CardType 		= sCardFlg->sCardType.CardType[0];			//IC�� ����
//		
//		l_FlgZoneErrEvent = NO_OCCUR;								//IC�� ��ʶҳ�����¼�
//		
//		//PrintfDebug("\r\n l_CardType %d",l_CardType);
//		
//		return 	1;
//	}
//	else
//	{
//		l_FlgZoneErrEvent = OCCUR;
//		l_CardType = 0x0000;
//		
//		return	0;
//	}
//}
//
////--------------------------------------------------------------------------------------------
////��������:             WriteNormCard(void)   
////��������:             StartCardRecNum:��ʼ��ˮ��,EndCardRecNum:������ˮ��
////��ڲ���:             ��ˮ��
////���ڲ���:             ��
////˵��:                 
////---------------------------------------------------------------------------------------------
void    WriteCardFlg(stcCardFlg*	sCardFlg)  
{
////	uint16	CrcTmp;
//	
////	CrcTmp = GetCrc16Check((uint8 *)sCardFlg,sizeof(stcCardFlg)-2);
//	
////	sCardFlg->CrcCheck = CrcTmp;
//	
//    WriteCard(CARD_FLG_ADDR,(uint8 *)sCardFlg,sizeof(stcCardFlg));
}

//extern	stcCardFlg	l_sCardFlg;
//
////--------------------------------------------------------------------------------------------
////��������:             uint8    CheckWriteCardFlgCrc(uint16 Crc16)    
////��������:             ����־ҳУ��
////��ڲ���:             ��
////���ڲ���:             ��־ҳУ��,��ȷ����1������Ϊ��
////˵��:                 
////---------------------------------------------------------------------------------------------
//uint8    CheckWriteCardFlgCrc(uint16 Crc16 )  
//{
////	uint16	CrcTmp;
////	
////	ReadCardFlg((stcCardFlg *)&l_sCardFlg);
////    
////    ReadCard(CARD_FLG_ADDR + sizeof(stcCardFlg)-2,(uint8 *)&CrcTmp,sizeof(CrcTmp));
////    
////    CrcTmp = GetCrc16Check((uint8 *)&l_sCardFlg,sizeof(stcCardFlg) -2);
////
////    ////printfcom0("\r\n CrcTmp %d,Crc16 ,%d",CrcTmp,Crc16);
////    
////    if(Crc16 == CrcTmp)
////    {
////    	return	NO_ERROR;
////    }
////    else
////    {
////    	return	ERROR;
////    }
//}
//

//-------------------------------------------------------------------------------------------------
//��������:             void	void	IndicateWriteCardFinsh(void)	   
//��������:             ��ͨ������
//��ڲ���:             ��
//���ڲ���:             ��
//--------------------------------------------------------------------------------------------------
void	IndicatePullOutCard(void)
{
	OffLed(WRITE_CARD_LED);
	OffLed(CARD_FULL_LED);	
	OffLed(CARD_LED);	
}
//-------------------------------------------------------------------------------------------------
//��������:             void	void	IndicateWriteCardFinsh(void)	   
//��������:             ��ͨ������
//��ڲ���:             ��
//���ڲ���:             ��
//--------------------------------------------------------------------------------------------------
void	IndicateCardTypErr(void)
{
	ClaerDisplaySetWithoutStore();
	DisplaySet(60,0xffff,"NCTP");									//IC�����ʹ���		
	DisplaySet(60,0xffff,"    ");									//IC�����ʹ���		
	OnLed(CARD_LED,1,50000,0);		
}

//-------------------------------------------------------------------------------------------------
//��������:             void	void	IndicateWriteCardFinsh(void)	   
//��������:             ��ͨ������
//��ڲ���:             ��
//���ڲ���:             ��
//--------------------------------------------------------------------------------------------------
void	IndicateCardNoSet(void)
{
	ClaerDisplaySetWithoutStore();
	DisplaySet(60,0xffff,"NSET");									//IC�����ʹ���		
	DisplaySet(60,0xffff,"    ");									//IC�����ʹ���		
	OnLed(CARD_LED,1,50000,0);		
}

//-------------------------------------------------------------------------------------------------
//��������:             void	void	IndicateWriteCardFinsh(void)	   
//��������:             ��ͨ������
//��ڲ���:             ��
//���ڲ���:             ��
//--------------------------------------------------------------------------------------------------
void	IndicateCardNoDef(void)
{
	ClaerDisplaySetWithoutStore();
	DisplaySet(60,0xffff,"NDEF");									//IC�����ʹ���		
	DisplaySet(60,0xffff,"    ");									//IC�����ʹ���	
	OnLed(CARD_LED,1,50000,0);		
}

extern	uint8	l_CardErrorFlg;
//
////static stcCardFlg	l_sCardFlg;
////static	stcCardFlg	l_sCardFlg = {0};
//stcCardFlg	l_sCardFlg = {0};
//
//
//extern	void    KeySetDensity(void);
////extern	void	ClosePluseInput(void);
////extern	void	ReStartPluse(void);
//extern	void	ReCalPara(uint8 Flg)	;
//extern	uint8	ComModCard(stcCardFlg	* sCardFlg);
//extern	uint8	ExpandCard(stcCardFlg	* sCardFlg);
//extern	uint8   WriteExpandAddTest(void);
//extern	uint8	l_WriteFlgErrCardEvtFlg;
//extern	uint8	DenDataCard(stcCardFlg *	sCardFlg);
//
////-------------------------------------------------------------------------------------------------
////��������:             OperationCard(void)    
////��������:             ����IC��
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
void    OperationCard(void)  
{
	uint8	ResetFlg;
	static	uint32	PlugTime = 0;
	static	uint32	SysTime = 0;
	static	uint8	PlugErrFlg = 0;
	static	uint8	PlugCardLongTime = 0;
	
	ResetFlg = FALSE ;
		
	if(GetPlugFlg() == PLUG_IN_CARD)
	{
		if(PlugCardLongTime == 1)
		{
			if(PlugErrFlg == 1)
			{
				DisplaySet(100,1,"NCTP");									//IC�����ʹ���		
				DisplaySet(100,1,"    ");									//IC�����ʹ���		
				DelayX10ms(250);
			}

			return;
		}

		ClaerDisplaySet();													//����ʾ������
		OffAllLed();														//�����з��������
		OnLed(RUN_LED,30000,5,5);											//����ʾ������		
		DisplaySet(50,1,"    ");										

		//CloseTax2();

		if(PlugICCard() == TRUE)										//�п����룬�ٽ�����ز���
		{	
			if(ReadCardFlg())					//��IC����־ҳ
			{
				switch( l_CardType )
				{
					case DATA_CARD:	DisplaySet(100,1,"DATA");
									DataCard(0);	
									break;									
					case DENSITY_CARD:									//�ܶȿ�
									DisplaySet(100,1,"DENS");						
									if(DensityCard())
									{
										ResetFlg = TRUE;
									}		
									break;
					case MODEL_CARD:									//ģ�Ϳ�
									DisplaySet(100,1,"MODE");						
									if(ModCard())
									{
										ResetFlg = TRUE;
									}	
										
									break;				
//					case COM_MODEL_CARD:								//ʱ�俨
//									DisplaySet(100,1,"SETC");						
//									if(ComModCard())
//									{
//										ResetFlg = TRUE;
//									}	
//									break;	
					case SET_DATA_CARD:									//������	
									DisplaySet(100,1,"SETD");						
									if(SetDataCard())
									{
										ResetFlg = TRUE;
									}
									break;		
					case HIGHT_CARD:									//�߶ȵ�����
									DisplaySet(100,1,"HIGT");						
									if(HightCard())
									{
										ResetFlg = TRUE;
									}
									break;															
					case COPY_CARD:										//���ݿ�����//��δд������
									DisplaySet(100,1,"COPY");						
									DataCard(1);
									break;
					case MODEL_SELECT_CARD:								//ģ��ѡ��
									DisplaySet(100,1,"SELE");						
 									if(ModelSelectCard())
									{
										ResetFlg = TRUE;
									} 									
 									break;	
//					case DEBUG_CARD:									//���Կ�
//									DisplaySet(100,1,"DEBU");						
//									DebugCard((stcCardFlg *)&l_sCardFlg);									
//									break;
					case FIX_CARD:										//װ����
									DisplaySet(100,1,"FIXC");						
									if(FixCard())
									{
										ResetFlg = TRUE;
									}									
									break;					
//					case COPY_FRAM_CARD:								//���縴�ƿ�
//									DisplaySet(100,1,"FRAC");						
//									CopyFramCard((stcCardFlg *)&l_sCardFlg);									
//									break;		
					case EXPAND_CARD:									//��չ�� //20120409
									DisplaySet(100,1,"EXPD");						
									ExpandCard();									
									break;		
					case DATA_CARD + DENSITY_CARD:						//�ܶȿ�+���ݿ� (������ˢ������)  �ܶȽṹ����DenChageTimes��
									DisplaySet(100,1,"DDEN");						
									DenDataCard();
//		
//									break;
					case DATA_CARD + DENSITY_CARD+HIGHT_CARD:						//�ܶȿ�+���ݿ�������ˢ�����ݣ�
									DisplaySet(100,1,"DDHN");						
									DenDataCard();
									ResetFlg = TRUE;
									break;			
//														
//					case DENSITY_CARD + MODEL_CARD:						//�ܶȿ�+ģ�Ϳ�
//									DisplaySet(100,1,"DEMO");						
//									
//									if(DensityCard((stcCardFlg *)&l_sCardFlg))
//									{
//										ResetFlg = TRUE;
//									}									
//									
//									if(ModCard())
//									{
//										ResetFlg = TRUE;
//									}									
//									break;
					case DENSITY_CARD + FIX_CARD + MODEL_CARD:			//�ܶȿ�+װ����+ģ�Ϳ�
									DisplaySet(100,1,"DFMC");						
									if(DensityCard())
									{
										ResetFlg = TRUE;
									}
																		
									if(ModCard())
									{
										ResetFlg = TRUE;
									}									
									
									if(FixCard())
									{
										ResetFlg = TRUE;
									}
									break;
									
					case DENSITY_CARD + FIX_CARD + MODEL_CARD + HIGHT_CARD:	//�ܶȿ�+װ����+ģ�Ϳ�+�߶ȿ�
									DisplaySet(100,1,"DFMH");						
									if(DensityCard())
									{
										ResetFlg = TRUE;
									}
																		
									if(ModCard())
									{
										ResetFlg = TRUE;
									}
																		
									if(FixCard())
									{
										ResetFlg = TRUE;
									}
																		
									if(HightCard())
									{
										ResetFlg = TRUE;
									}
																		
									break;
					case DENSITY_CARD + FIX_CARD + HIGHT_CARD:				//�ܶȿ�+װ����+�߶ȿ�
									if(DisplaySet(100,1,"DFHC"))
									{
										ResetFlg = TRUE;
									}
																		
									if(DensityCard())
									{
										ResetFlg = TRUE;
									}
																		
									if(FixCard())
									{
										ResetFlg = TRUE;
									}
																		
									if(HightCard())
									{
										ResetFlg = TRUE;
									}									
									break;									
					default:	
									IndicateCardNoDef();	
				}
			}	
			else
			{
				DelayX10ms(10);
				IndicateCardNoSet();
			}	
			
			PlugErrFlg = 0;		
		}
		else 
		{
			PlugErrFlg = 1;
			
			IndicateCardTypErr();
		}		

		while(GetPlugFlg() == PLUG_IN_CARD)								//��IC���˳�		
		{
			PlugTime++;													//����IC������ʱ
							
			SysTime = GetSysTime();		
			while(GetSysTime() - SysTime < 100)							//1S
			{
				NOP();
			}
				
			if(PlugErrFlg == 1)											//�����󣬵�10�����˳�
			{
				if(PlugTime	> 20)
				{
					PlugCardLongTime = 1;
					break;
				}			
			}
			else														////������5�������˳�
			{
				if(PlugTime	> 90)
				{
					PlugCardLongTime = 1;
					break;
				}			
			}

			NOP();
		}
		DelayX10ms(150);												//�ο��Ƴ��µȴ�

		
		if(PlugErrFlg == 1 && PlugTime > 500)							//�忨�����˳�����
		{
			DelayX10ms(50);
		}
		
		if(ResetFlg == TRUE)											//������ú�����
		{
			ReCalPara(1);												//�ͳ߲������¼���

			DelayX10ms(20);
			
//			ResetSys();													//
		}		
											//����ʾ������
		ResumeDisplaySet();												//�ָ���ʾ������
		
		if(PlugCardLongTime == 1 && PlugErrFlg == 0)
		{
			//OffLed(WRITE_CARD_LED);
			//OffLed(CARD_FULL_LED);	
			//OffLed(CARD_LED);	
		}
		else
		{
			IndicatePullOutCard();
		}
		
		g_PullCardTime = GetSysTime();
	}
	else
	{
		PlugTime = 0;													//�����������
		PlugErrFlg = 0;
			
		l_CardErrorFlg = NO_ERROR;
		
		PlugCardLongTime = 0;
		
		OffLed(WRITE_CARD_LED);
		OffLed(CARD_FULL_LED);	
	}
}
//
///*
//uint8	SetKeyPressed(void)
//{
//	//return 1;
//	return	(KeyPressed());
//}
//*/
//
//#define		MAX_SET_TIME  20
//extern	float		l_Density;							//�ܶ�ֵ
//extern	uint16	GetDensityVal(void);
////20111024
////-------------------------------------------------------------------------------------------------
////��������:             void    KeySetDensity(void)     
////��������:             ����IC��
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
//void    KeySetDensity(void)  
//{
////	uint8	ResetFlg;
//	
////	ResetFlg = FALSE ;
//
////  
//	static	stcDensity sDensity;
//
//	uint32	DisplayVal;
//	uint32	KeyDownTime = 0;
//	uint32	SysTime;
//	uint16	Density;
//	uint32	CalDensity;
//	uint16  CrcCheck;
//	
//	DisplayVal = g_DipVal;													//������ʾ������
//	
//	while(GetPlugFlg() == PLUG_IN_CARD)										//
//	{ 
//		SysTime = GetSysTime();												
//		
//		//SysHoldTast();
//		//while(1)
//		{
//			if(SetKeyPressed())												//�������ü�
//			{
//				if(KeyDownTime == 0)										// ��һ�ΰ������ü�
//				{
//					ClaerDisplaySet();										//����ʾ������
//					
//					DisplayVal = g_DipVal;
//					
//					DisplaySet(100,1,"%u",DisplayVal);
//				}
//				else
//				{
//					if(KeyDownTime < (MAX_SET_TIME/2))
//					{
//						DisplayVal = g_DipVal + KeyDownTime*10;
//					}
//					else
//					{
//						if(g_DipVal > MAX_SET_TIME*10)						//�򸺷���ѭ��
//						{
//							DisplayVal = g_DipVal + KeyDownTime*10 - MAX_SET_TIME*10;
//						}		
//						else
//						{
//							DisplayVal = 10*MAX_SET_TIME /2 + KeyDownTime*10 - MAX_SET_TIME*10;
//						}		
//					}
//					
//					ClaerDisplaySet();										//����ʾ������
//					DisplaySet(60,1,"%u",DisplayVal);
//				}
//				
//				KeyDownTime = (KeyDownTime+1)%MAX_SET_TIME;					//����������
//				while(SetKeyPressed()){};										//�ȴ������ɿ�
//				DelayX10ms(20);												//�ȴ�һ��ʱ���˳�	
//				
//				SysTime = GetSysTime();	
//			}
//			else															//δ���»��ɿ�����
//			{
//				//DelayX10ms(10);											//�ȴ�һ��ʱ���˳�	
//			}
//		}
//		
//		if(GetSysTime() - SysTime > 1000)
//		{
//			break;
//		}
//	}
//	
//	
//	if(KeyDownTime != 0)													//׼�������ܶ�
//	{
//		Density = GetDensityVal();											//ȡ�ܶ�ֵ
//		
//		//printfcom0("\n \rDisplayVal %u,g_DipVal %u",DisplayVal,g_DipVal);
//
//		if(g_DipVal > 3400)
//		{
//			if(DisplayVal > g_DipVal)
//			{
//				CalDensity = Density -  ((uint32)Density *(DisplayVal - g_DipVal) / (g_DipVal - 3400));
//			}
//			else
//			{
//				CalDensity = Density + ((uint32)Density *(g_DipVal - DisplayVal) / (g_DipVal - 3400));
//			}
//	  	}
//	  	else
//	  	{
//			if(DisplayVal > g_DipVal)
//			{
//				CalDensity = Density -  ((uint32)Density *(DisplayVal - g_DipVal) / (g_DipVal));
//			}
//			else
//			{
//				CalDensity = Density +  ((uint32)Density *(g_DipVal - DisplayVal) / (g_DipVal));
//			}
//	  	}
//	  	
//	  	//printfcom0("\n \rCalDensity %u,Density %u",CalDensity,Density);
//	  	
//	  	if(CalDensity > 770 && CalDensity < 900)							//��ֵ
//	  	{
//	  		sDensity.Density = CalDensity;
//	  	}
//	  	
//		CrcCheck = GetCrc16Check((uint8 *)&sDensity,sizeof(sDensity) - 2);
//		//GetCrc16Check((uint8 *)&sDensity,sizeof(sDensity) - 2);
//		sDensity.CrcCheck = CrcCheck;
//		
//		//if(CrcCheck == sDensity.CrcCheck)									//У������,���ܶ�		
//		//{			
//		//PrintfDebug("\r\n sDensity.Density %d",sDensity.Density );
//		
//		if(StoreDensity((stcDensity *)&sDensity))
//		{
//			//SetSucceedIndicate();	
//		}
//		else
//		{
//			//StoreErrIndicate();	
//		}
//		//}
//		
//		//printfcom0("\r\n l_Density %f",l_Density);
//		
//		l_Density = (float)CalDensity / 1000;
//		
//		//printfcom0("\r\n l_Density %f",l_Density);	
//	}
//	/*	*/
//	ClaerDisplaySet();										//����ʾ������
//
//}
////-------------------------------------------------------------------------------------------------
////��������:             OperationCOM0ModelCard(void)    
////��������:             �����Ӵ���0���ܵ�������
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
//void    OperationCOM0ModelCard(void)  
//{
///*
//	uint16	ResetFlg;
//	
//	ClaerDisplaySet();											//����ʾ������
//	OffAllLed();												//�����з��������
//	OnLed(RUN_LED,30000,5,5);									//����ʾ������		
//	CloseTax2();
//		
//	PrintfDebug("\r\n OperationCard");
//
//	if(ReadCOM0CardFlg((stcCardFlg	*)&l_sCardFlg))					//��IC����־ҳ
//	{
//		switch( l_CardType )
//		{
//			case DATA_CARD:	DisplaySet(100,1,"DATA");
//							DataCard((stcCardFlg *)&l_sCardFlg);	
//							break;									
//				
//			case DENSITY_CARD:									//�ܶȿ�
//							DisplaySet(150,1,"DENS");						
//							
//							if(DensityCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}		
//							break;				
//			case MODEL_CARD:									//ģ�Ϳ�
//							DisplaySet(150,1,"MODE");						
//							if(COM0ModData())
//							{
//								ResetFlg = TRUE;
//							}		
//							break;				
//			case COM_FIX_CARD:										//ʱ�俨
//							//DisplaySet(100,1,"SETT");						
//							//TimeCard((stcCardFlg *)&l_sCardFlg);		
//							break;	
//			case SET_DATA_CARD:									//������	//��δд������
//							DisplaySet(100,1,"SETD");						
//							if(SetDataCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//							break;		
//			case HIGHT_CARD:									//�߶ȵ�����
//							DisplaySet(150,1,"HIGT");						
//							if(HightCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//							break;															
//			case COPY_CARD:										//���ݿ�����//��δд������
//							DisplaySet(100,1,"COPY");						
//							DataCopyCard((stcCardFlg *)&l_sCardFlg);
//							break;
//			case MODEL_SELECT_CARD:								//ģ��ѡ��
//							DisplaySet(100,1,"SELE");						
//							if(ModelSelectCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							} 									
//							break;	
//			case DEBUG_CARD:									//���Կ�
//							DisplaySet(100,1,"DEBU");						
//							DebugCard((stcCardFlg *)&l_sCardFlg);									
//							break;
//			case FIX_CARD:										//װ����
//							DisplaySet(100,1,"FIXC");						
//							if(FixCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}									
//							break;					
//			case COPY_FRAM_CARD:								//���縴�ƿ�
//							DisplaySet(100,1,"FRAC");						
//							CopyFramCard((stcCardFlg *)&l_sCardFlg);									
//							break;						
//			case DENSITY_CARD + MODEL_CARD:						//�ܶȿ�+ģ�Ϳ�
//							DisplaySet(100,1,"DEMO");						
//							
//							if(DensityCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}									
//							
//							if(COM0ModData())
//							{
//								ResetFlg = TRUE;
//							}									
//							break;
//			case DENSITY_CARD + FIX_CARD + MODEL_CARD:			//�ܶȿ�+װ����+ģ�Ϳ�
//							DisplaySet(100,1,"DFMC");						
//							if(DensityCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//																
//							if(COM0ModData())
//							{
//								ResetFlg = TRUE;
//							}									
//							
//							if(FixCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//							break;
//							
//			case DENSITY_CARD + FIX_CARD + MODEL_CARD + HIGHT_CARD:	//�ܶȿ�+װ����+ģ�Ϳ�+�߶ȿ�
//							DisplaySet(100,1,"DFMH");						
//							if(DensityCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//																
//							if(COM0ModData())
//							{
//								ResetFlg = TRUE;
//							}
//																
//							if(FixCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//																
//							if(HightCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//																
//							break;
//			case DENSITY_CARD + FIX_CARD + HIGHT_CARD:				//�ܶȿ�+װ����+�߶ȿ�
//							if(DisplaySet(100,1,"DFHC"))
//							{
//								ResetFlg = TRUE;
//							}
//																
//							if(DensityCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//																
//							if(FixCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}
//																
//							if(HightCard((stcCardFlg *)&l_sCardFlg))
//							{
//								ResetFlg = TRUE;
//							}									
//							break;									
//			default:	
//							IndicateCardNoDef();	
//		}
//	}	
//	else
//	{
//		DelayX10ms(10);
//		IndicateCardNoSet();
//	}	
//*/		
//}
//
////-------------------------------------------------------------------------------------------------
////��������:             CardTask(void)    
////��������:             ����IC������
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
void    CardTask(void)  
{
	OperationCard();
}
//
#define		PLUG_CARD_EVT			61
#define		NU_FINISH_CARD_EVT		62
#define		SET_PARA_EVT			63
#define		READ_DATA_EVT			64
#define		WRITE_FLGA_EVT			65
#define		PLUG_USB_EVT			66
#define		USB_READ_EVT			67
#define		USB_SET_EVT				68

//
//extern	uint8	GetSetParaFlg(void);
//extern	uint8	GetReadDataFlg(void);
//extern	void	SetReadDataFlgTrue(void);
//extern	uint8	SetParaFlgTrue(void);
//extern	void	ResetPlugFlgEvt(void);
//extern	void	ResetUnFihCardEvtFlg(void);
//extern	uint8	GetWriteFlgErrCardEvtFlg(void);
////extern	uint8	GetPlugUsbFlg(void);
////extern	void	SetPlugUsbFlgTrue(void);
////extern	void	SetUsbSetFlgTrue(void);
//extern	void	SetUsbReadDataFlgTrue(void);
////extern	uint8	GetUsbSetFlg(void);
//extern	uint8	GetUsbReadDataFlg(void);
//
////-------------------------------------------------------------------------------
////��������:        	uint8	JudgeCardEvt(void)
////��������:       	�ж�Flsh�¼�
////��ڲ���:        	��
////���ڲ���:      	��
////-------------------------------------------------------------------------------
uint8	JudgeCardEvt(void)
{
	uint8	EvtType = RIGHT_DATA;

	if(GetPlugFlg() == PLUG_IN_CARD)
	{
		EvtType = PLUG_CARD_EVT;
		ResetPlugFlgEvt();
	}
	else if(GetUnFihCardEvtFlg() == ERROR)
	{
		EvtType = NU_FINISH_CARD_EVT;
		ResetUnFihCardEvtFlg();
	}
	else if(GetSetParaFlg() == ERROR)   
	{
		EvtType = SET_PARA_EVT;
		SetParaFlgTrue();
	}	
	else if(GetReadDataFlg() == ERROR)
	{
		EvtType = READ_DATA_EVT;
		SetReadDataFlgTrue();
	}		
//	else if(GetWriteFlgErrCardEvtFlg() == ERROR)
//	{
//		EvtType = WRITE_FLGA_EVT;
//		SetReadDataFlgTrue();
//	}
////	else if(GetPlugUsbFlg() == ERROR)
////	{
////		EvtType = PLUG_USB_EVT;
////		SetPlugUsbFlgTrue();
////	}
////	else if(GetUsbSetFlg() == ERROR)
////	{
////		EvtType = USB_SET_EVT;
////		SetUsbSetFlgTrue();
////	}
////	else if(GetUsbReadDataFlg() == ERROR)
////	{
////		EvtType = USB_READ_EVT;
////		SetUsbReadDataFlgTrue();
////	}
//	
	return	EvtType;
}
////
