//#include 	"config.h"
//#include 	"String.h"
//#include	"Globe.h"
//#include	"HardDrive.h"
//#include	"StoreRec.h"
//#include	"CpuDrive.h"
//#include	"FramStore.h"
//#include	"OperateCard.h"
//#include	"stdlib.h" 

#include    "includes.h"  
#include	"Card.h"
#include	"OperateCard.h"
//#include	"flash.h"

#define		CARD_BUF_LEN		1024			//IC������������С	


//----------------------------------------------------------------------
//��������:  	uint32  GetWritePageLen(uint32 Start, uint32 WriteLen,uint32 MaxWriteLen)
//��������:  	��д��Ҫ�����ҳд����
//��ڲ���:   	StartAddr:IC����ʼд��ַ;FinishLen:��д��ַ,MaxWriteLen:Ҫд��ַ
//���ڲ���:   	
//˵��:                 
//-----------------------------------------------------------------------
uint32  GetWritePageLen(uint32 StartAddr, uint32 FinishLen,uint32 MaxWriteLen)
{
    uint32  	PageSize;
    uint32  	PageSegLen;
    uint32  	NoWriteLen;
	
	PageSize = GetCardPageSize();
	
    PageSegLen = PageSize - ((StartAddr + FinishLen) % PageSize);		//������βд

    NoWriteLen = MaxWriteLen - FinishLen;

    if( PageSegLen < NoWriteLen)
    {
         return PageSegLen;
    }
    else
    {
        return  NoWriteLen;
    }
}

//----------------------------------------------------------------------
//��������:  	stcFlshRec    FlshRecToCardRec( stcFlshRec   sFlshRec)
//��������:  	���ͳ߼�¼FLASHת��ΪIC����¼
//��ڲ���:   	FLASH��¼
//���ڲ���:   	IC����¼
//˵��:                 
//-----------------------------------------------------------------------
stcFlshRec    FlshRecToCardRec( stcFlshRec   sFlshRec)
{
	stcFlshRec  sCardRec;		
	memcpy((uint8 *)&sCardRec,(uint8 *)&sFlshRec,sizeof(sCardRec));
	
	return	sCardRec;
}

//extern	void	SysHoldTast(void);

//----------------------------------------------------------------------
//��������:  	void    ReadCardDisplay(uint8	 Sct)
//��������:  	���ͳ߼�¼FLASHת��ΪIC����¼
//��ڲ���:   	FLASH��¼
//���ڲ���:   	IC����¼
//˵��:                 
//-----------------------------------------------------------------------
void    ReadCardDisplay(uint8	 Sct)
{
	uint8	i = 0;
	
//	if(GetSysTime() % 100 < 12)
	{
		i = 0;
		while(i < 10 )
		{
			DisplaySet(10,2,"%u  %u",Sct,i);
			i++;
		}
		
		//OnLed(WRITE_CARD_LED,10,5,5);
	}													//xitong 
}

//----------------------------------------------------------------------
//��������:  	uint8  StoreCardRec(uint32   FlshStartRecNum,uint32	FlshRecCnt,uint32	CardStartAddr )
//��������:  	��IC����¼
//��ڲ���:   	FlshStartRecNum:��ʼFlsh��¼��,FlshRecCnt:��¼����,StartCardRecAddr:IC����ʼ��ַ
//���ڲ���:   	
//˵��:                 
//-----------------------------------------------------------------------
uint8  StoreCardRec(uint32   FlshStartRecNum,uint32	FlshRecCnt,uint32	CardStartAddr,uint32	WriteTimes )
{
	uint8			CardBuf[1024];
	uint32			FlshRecNum;											//Flsh��¼��ˮ��
	uint32			MaxWriteLen;										//���Ҫд������
	uint32			FinishLen = 0;										//��д����
	uint32			WritePageLen;	
	uint32			NextRecCardAddr;
	uint32			BufWriteLen = 0;
	
	stcFlshRec		sFlshRec;
	
	FlshRecNum	= FlshStartRecNum;
	MaxWriteLen = FlshRecCnt * sizeof(sFlshRec);					
				
	BufWriteLen = 0;
	while( FinishLen < MaxWriteLen)
	{
		ReadFlshRec((stcFlshRec *)&sFlshRec,FlshRecNum++);

		WritePageLen = GetWritePageLen(CardStartAddr,FinishLen,MaxWriteLen);
			
		memcpy(&CardBuf[BufWriteLen],(uint8 *)&sFlshRec,sizeof(sFlshRec));
		BufWriteLen += sizeof(sFlshRec);

		if(WritePageLen == BufWriteLen || WritePageLen < BufWriteLen)
		{
			NextRecCardAddr = CardStartAddr + FinishLen;				//IC����һ��ַ
			 	
   			WriteCard(NextRecCardAddr,CardBuf,WritePageLen);      		//д��
     		
     		FinishLen += WritePageLen;									//��Ҫ���д����

     		ReadCardDisplay(WriteTimes);								//ָʾ���ڶ���

			BufWriteLen = 0;
		}
		if(GetPlugFlg() == NO_PLUG_IN_CARD)								//�����˳�
		{
			return FALSE;
		}
	}

	return TRUE;
}

//-------------------------------------------------------------------------------------------------
//��������:             uint32	GetReadFlshRecCnt(uint32 ZoneMaxRecNum)	   
//��������:             ȡ����Ӧ��ȡ�ļ�¼��
//��ڲ���:             ��������¼��
//���ڲ���:             ��¼��
//--------------------------------------------------------------------------------------------------
uint32	GetReadFlshRecCnt(uint32 NoReadRecNum,uint32 ZoneMaxRecNum)
{	
	uint32	FlshMaxRec;
	
	FlshMaxRec = (FLSH_MAX_SIZE)/(sizeof(stcFlshRec));
	
	////printfcom0("\r\n FlshMaxRec %d",FlshMaxRec);
	if(NoReadRecNum >= ZoneMaxRecNum)
	{
		if(ZoneMaxRecNum > FlshMaxRec)
		{
			return	FlshMaxRec;
		}
		
		return	ZoneMaxRecNum;
	}
	else
	{
		if(NoReadRecNum > FlshMaxRec)
		{
			return	FlshMaxRec;
		}
			
		return	NoReadRecNum;
	}
}

//-------------------------------------------------------------------------------------------------
//��������:             void	void	IndicateWriteCardFinsh(void)	   
//��������:             ��ͨ������
//��ڲ���:             ��
//���ڲ���:             ��
//--------------------------------------------------------------------------------------------------
void	IndicateWriteCardFinsh(void)
{
	DelayX10ms(10);	
	ClaerDisplaySetWithoutStore();
//	OnLed(WRITE_CARD_LED,0xffffff,5,0);										
	DisplaySet(60,100,"good");
	DisplaySet(60,100,"    ");	
	//printfcom0("\r\n Good!!");
}

//-------------------------------------------------------------------------------------------------
//��������:             void	void	IndicateWriteCardFlgErr(void)	   
//��������:             ��ͨ������
//��ڲ���:             ��
//���ڲ���:             ��
//--------------------------------------------------------------------------------------------------
void	IndicateWriteCardFlgErr(void)
{
	DelayX10ms(10);	
	OnLed(WRITE_CARD_LED,0xffffff,5,0);										
	DisplaySet(60,100,"E_IC");
	DisplaySet(60,100,"    ");	
}

//-------------------------------------------------------------------------------------------------
//��������:             void	void	IndicateWriteCardFlgErr(void)	   
//��������:             ��ͨ������
//��ڲ���:             ��
//���ڲ���:             ��
//--------------------------------------------------------------------------------------------------
void	IndicateUSBFlgErr(void)
{
	DelayX10ms(10);	
	OnLed(WRITE_CARD_LED,0xffffff,5,0);										
	DisplaySet(60,100,"E_US");
	DisplaySet(60,100,"    ");	
}

//-------------------------------------------------------------------------------------------------
//��������:             void	IndicateRecordFinsh(void)	   
//��������:             ��ͨ������
//��ڲ���:             ��
//���ڲ���:             ��
//--------------------------------------------------------------------------------------------------
void	IndicateRecordFinsh(void)
{
	DelayX10ms(10);	
	ClaerDisplaySetWithoutStore();
	OnLed(WRITE_CARD_LED,0xffffff,5,0);										
	DisplaySet(60,100,"ALL");
	DisplaySet(60,100,"    ");	
}

//-------------------------------------------------------------------------------------------------
//��������:             void	void	IndicateWriteCardFinsh(void)	   
//��������:             ��ͨ������
//��ڲ���:             ��
//���ڲ���:             ��
//--------------------------------------------------------------------------------------------------
void	IndicateCardFull(void)
{
	ClaerDisplaySetWithoutStore();
	DisplaySet(60,100,"FULL");
	DisplaySet(60,100,"    ");
	OnLed(CARD_FULL_LED,0xffffff,5,5);
}

//-------------------------------------------------------------------------------------------------
//��������:             void	void	IndicateWriteCardFinsh(void)	   
//��������:             ��ͨ������
//��ڲ���:             ��
//���ڲ���:             ��
//--------------------------------------------------------------------------------------------------
void	IndicateWriteNoFinsh(void)
{
	ClaerDisplaySetWithoutStore();
	DisplaySet(60,0xffff,"NUNF");
	DisplaySet(60,0xffff,"    ");
}

uint8	l_UnFihCardEvtFlg = NO_ERROR;
//uint8	l_WriteFlgErrCardEvtFlg = NO_ERROR;

void	DataDensityCard(stcCardFlg *	sCardFlg);
////-------------------------------------------------------------------------------------------------
////��������:             void	OperationNormCard(void);	   
////��������:             ��ͨ������
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
//void	DataCard(void)
//{
//	uint32	FlshRecCnt;	
//	uint32	FlshStartRecNum;
//	uint32	CardEndAddr;
//	uint32	CardStartAddr;
//	uint32	CardMaxRecNum;
//	uint32	NoReadRecNum;
//	uint16	CrcCheck;
//	static	stcDeviceInfo 	sDeviceInfo;
//	static	stcFixInfo		sFixInfo;						
//	
//	//PrintfDebug("\r\nDataCard");
//	
////	DataDensityCard(sCardFlg);  					//�����ܶȿ�
//	
//	g_LshRedFlshRecNum = ReadLstRedFlshRecNum();
//	
//	if(sCardFlg->WriteCardTimes >= 100)	
//	{	
//		sCardFlg->WriteCardTimes = 0;
//	}
//		
//	if(sCardFlg->WriteCardTimes == 0)
//	{
//		CardStartAddr = CARD_DATA_ADDR;
//	}
//	else
//	{
//		CardStartAddr 	= sCardFlg->sCardIndex[sCardFlg->WriteCardTimes - 1].EndAddr;
//		
//		if(CardStartAddr < CARD_DATA_ADDR)
//		{
//			CardStartAddr = CARD_DATA_ADDR;
//		}
//	}
//	
//	if(g_CurFlshRecNum > g_LshRedFlshRecNum)
//	{
//		NoReadRecNum	= (g_CurFlshRecNum - g_LshRedFlshRecNum);		//Flsh��δ����¼����
//	}
//	else
//	{
//		NoReadRecNum = 0;
//	}
//	
//	CardMaxRecNum	= GetToEndLen(CardStartAddr) / sizeof(stcFlshRec);	//ȡIC��δд�ռ䳤��
//		
//	FlshRecCnt 		= GetReadFlshRecCnt(NoReadRecNum,CardMaxRecNum);	//Ҫд���ݳ���
//	
//	FlshStartRecNum = g_CurFlshRecNum  - FlshRecCnt ;
//
//	////printfcom0("\r\nNoReadRecNum %d,CardMaxRecNum %d,FlshRecCnt %d,FlshStartRecNum %d sCardFlg->WriteCardTimes %d,GetToEndLen(CardStartAddr) %d",
//	//NoReadRecNum,CardMaxRecNum,FlshRecCnt,FlshStartRecNum,sCardFlg->WriteCardTimes,GetToEndLen(CardStartAddr));
//	//printfcom0("\r\n FlshStartRecNum %d NoReadRecNum %d",FlshStartRecNum,NoReadRecNum);
//
//	if((sCardFlg->WriteCardTimes < 100)  && ( CardMaxRecNum >20))			//��д��
//	{
//		l_UnFihCardEvtFlg = NO_ERROR;
//
//		if( NoReadRecNum > 1 )												//δ����¼���������1���ܶ�ȡ����	
//		{
//			if( StoreCardRec(FlshStartRecNum,FlshRecCnt,CardStartAddr,sCardFlg->WriteCardTimes))		//����1 д�����
//			{
//				uint8	i;
//				uint8	Tmp;
//				uint16	DataTmp;
//				uint8	Buf[5] = {'0','0','0','0','0'};
//			
//				ReadHostInfo((stcDeviceInfo * )&sDeviceInfo);
//				
//				ReadFixInfo((stcFixInfo * )&sFixInfo);
//				
//				memcpy(sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].ProNum
//							,sDeviceInfo.ProduceDate,sizeof(sDeviceInfo.ProduceDate));
//		
//				DataTmp = sDeviceInfo.DeviceNum;
//				for(i = 0; i < 5;i++)
//				{
//					Tmp = DataTmp%10;
//					DataTmp /= 10;
//					if(DataTmp != 0)
//					{
//						Buf[5-1-i] = Tmp + '0';
//					}
//				}
//				
//				memcpy(&sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].ProNum[sizeof(sDeviceInfo.ProduceDate)],Buf,5);
//				sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].LocoType[0]	= sFixInfo.LocoTyp;
//				sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].LocoType[1]	= sFixInfo.E_LocoTyp;	
//				memcpy(sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].LocoNum,sFixInfo.LocoNum,sizeof(sFixInfo.LocoNum));		
//				sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].StartAddr	= CardStartAddr;
//				CardEndAddr	= CardStartAddr + ( FlshRecCnt * sizeof(stcFlshRec));
//				sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].EndAddr 		= CardEndAddr;
//				//sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].RecLen		= CardEndAddr - CardStartAddr;
//				sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].RecLen		=  FlshRecCnt * sizeof(stcFlshRec);
//				sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].RecNum		= FlshRecCnt;
//				
//				sCardFlg->WriteCardTimes++;									
//
//				CrcCheck = GetCrc16Check((uint8 *)sCardFlg,sizeof(stcCardFlg) -2);
//
//				sCardFlg->CrcCheck = CrcCheck;									
//
//				WriteCardFlg(sCardFlg);									//�޸�IC����־ҳ
//							
// 				if(CheckWriteCardFlgCrc(CrcCheck) == NO_ERROR)
// 				{
//					StoreLstRedFlshRecNum(g_CurFlshRecNum);				//�����µ��Ѷ���¼��ˮ��
//				
//					g_LshRedFlshRecNum = g_CurFlshRecNum;				//
// 				
//					IndicateWriteCardFinsh();							//
//					
//					DelayX10ms(10);	
//				}
//				else
//				{
//					l_WriteFlgErrCardEvtFlg = ERROR;
//					
//					sCardFlg->sCardID.Reserve1 = 65;					//��д��־ҳ�ı�־
//					
//					CrcCheck = GetCrc16Check((uint8 *)sCardFlg,sizeof(stcCardFlg) -2); //��дУ��
//
//					sCardFlg->CrcCheck = CrcCheck;					
//					
//					WriteCardFlg(sCardFlg);									//�����޸�IC����־ҳ,�����ж�
//	 				
//	 				if(CheckWriteCardFlgCrc(CrcCheck) == NO_ERROR)			//����ˢ��
//	 				{
//						StoreLstRedFlshRecNum(g_CurFlshRecNum);				//�����µ��Ѷ���¼��ˮ��
//					
//						g_LshRedFlshRecNum = g_CurFlshRecNum;				//
//	 				
//						IndicateWriteCardFinsh();							//
//					}
//					else
//					{
//						IndicateWriteCardFlgErr();							//
//					}
//				}
//			}
//			else														//д���������
//			{
//				l_UnFihCardEvtFlg = ERROR;
//				
//				DelayX10ms(10);	
//				
//				IndicateWriteNoFinsh();									//д��δ���ָʾ
//				
//				DelayX10ms(500);										//δд��
//			}
//		}
//		else
//		{
//			IndicateWriteCardFinsh();									//
//		}
//	}
//	else
//	{
//		IndicateCardFull();
//	}
//} 

void	DataCard(uint8 copyflg)
{
	uint32	FlshRecCnt;	
	uint32	FlshStartRecNum;
	uint32	CardEndAddr;
	uint32	CardStartAddr;
	uint32	CardMaxRecNum;
	uint32	NoReadRecNum;
//	uint16	CrcCheck;
	stcDeviceInfo 	sDeviceInfo;
	stcFixInfo		sFixInfo;						
	uint16	WriteCardTimes;
	stcCardIndex	sCardIndex;
	uint32	CardAddrTmp;


	DelayX10ms(10);

	g_LshRedFlshRecNum = ReadLstRedFlshRecNum();
	if(copyflg == 1) //copy
	{
		g_LshRedFlshRecNum = 1;	
	}
	
	CardAddrTmp = CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType)+sizeof(stcCardPara)+sizeof(stcCardIndex)*100;
	ReadCard(CardAddrTmp,(uint8 *)&WriteCardTimes,sizeof(WriteCardTimes));	

	if(WriteCardTimes >= 100)	
	{	
		WriteCardTimes = 0;
	}
			
	if(WriteCardTimes == 0)
	{
		CardStartAddr = CARD_DATA_ADDR;
	}
	else
	{
		CardAddrTmp = CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType)
				+sizeof(stcCardPara)+sizeof(stcCardIndex)*(WriteCardTimes-1);
		ReadCard(CardAddrTmp,(uint8 *)&sCardIndex,sizeof(stcCardIndex));

		CardStartAddr 	= sCardIndex.EndAddr;
		
		if(CardStartAddr < CARD_DATA_ADDR)
		{
			CardStartAddr = CARD_DATA_ADDR;
		}
	}

	CardAddrTmp = CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType)
				+sizeof(stcCardPara)+sizeof(stcCardIndex)*WriteCardTimes;
	ReadCard(CardAddrTmp,(uint8 *)&sCardIndex,sizeof(stcCardIndex));
		
	if(g_CurFlshRecNum > g_LshRedFlshRecNum)
	{
		NoReadRecNum	= (g_CurFlshRecNum - g_LshRedFlshRecNum);		//Flsh��δ����¼����
	}
	else
	{
		NoReadRecNum = 0;
	}
	
	CardMaxRecNum	= GetToEndLen(CardStartAddr) / sizeof(stcFlshRec);	//ȡIC��δд�ռ䳤��
		
	FlshRecCnt 		= GetReadFlshRecCnt(NoReadRecNum,CardMaxRecNum);	//Ҫд���ݳ���
	
	FlshStartRecNum = g_CurFlshRecNum  - FlshRecCnt ;

	printfcom0("\r\n %d,%d,%d,%d,%d",g_CurFlshRecNum,g_LshRedFlshRecNum,NoReadRecNum,FlshRecCnt,FlshStartRecNum);
	if((WriteCardTimes < 100)  && ( CardMaxRecNum >20))			//��д��
	{
		l_UnFihCardEvtFlg = NO_ERROR;

		if( NoReadRecNum > 1 )												//δ����¼���������1���ܶ�ȡ����	
		{
			if( StoreCardRec(FlshStartRecNum,FlshRecCnt,CardStartAddr,WriteCardTimes))		//����1 д�����
			{
				uint8	i;
				uint8	Tmp;
				uint16	DataTmp;
				uint8	Buf[5] = {'0','0','0','0','0'};
			
				ReadHostInfo((stcDeviceInfo * )&sDeviceInfo);
				
				ReadFixInfo((stcFixInfo * )&sFixInfo);
				
				memcpy(sCardIndex.ProNum
							,sDeviceInfo.ProduceDate,sizeof(sDeviceInfo.ProduceDate));
		
				DataTmp = sDeviceInfo.DeviceNum;
				for(i = 0; i < 5;i++)
				{
					Tmp = DataTmp%10;
					DataTmp /= 10;
					if(DataTmp != 0)
					{
						Buf[5-1-i] = Tmp + '0';
					}
				}
				
				memcpy(&sCardIndex.ProNum[sizeof(sDeviceInfo.ProduceDate)],Buf,5);
				sCardIndex.LocoType[0]	= sFixInfo.LocoTyp;
				sCardIndex.LocoType[1]	= sFixInfo.E_LocoTyp;	
				memcpy(sCardIndex.LocoNum,sFixInfo.LocoNum,sizeof(sFixInfo.LocoNum));		
				sCardIndex.StartAddr	= CardStartAddr;
				CardEndAddr	= CardStartAddr + ( FlshRecCnt * sizeof(stcFlshRec));
				sCardIndex.EndAddr 		= CardEndAddr;
				//sCardFlg->sCardIndex[sCardFlg->WriteCardTimes].RecLen		= CardEndAddr - CardStartAddr;
				sCardIndex.RecLen		=  FlshRecCnt * sizeof(stcFlshRec);
				sCardIndex.RecNum		= FlshRecCnt;
				
				WriteCardTimes++;									

				CardAddrTmp = CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType)
							+sizeof(stcCardPara)+sizeof(stcCardIndex)*100; 
				WriteCard(CardAddrTmp,(uint8 *)&WriteCardTimes,sizeof(WriteCardTimes));	

				CardAddrTmp = CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType)
							+sizeof(stcCardPara)+sizeof(stcCardIndex)*(WriteCardTimes-1); 
				WriteCard(CardAddrTmp,(uint8 *)&sCardIndex,sizeof(stcCardIndex));

				if(copyflg == 0)
				{
					StoreLstRedFlshRecNum(g_CurFlshRecNum);				//�����µ��Ѷ���¼��ˮ��
				
					g_LshRedFlshRecNum = g_CurFlshRecNum;				//
				}
				DelayX10ms(10);
				IndicateWriteCardFinsh();							//
				
				DelayX10ms(10);	
			}
			else														//д���������
			{
				l_UnFihCardEvtFlg = ERROR;
				
				DelayX10ms(10);	
				
				IndicateWriteNoFinsh();									//д��δ���ָʾ
				
				DelayX10ms(500);										//δд��
			}
		}
		else
		{
			IndicateWriteCardFinsh();									//
		}
	}
	else
	{
		IndicateCardFull();
	}

	printfcom0("\r\n %d,%d,%d,%d",FlshRecCnt,g_LshRedFlshRecNum,NoReadRecNum,FlshStartRecNum);

} 

extern  stcCardFlg	l_sCardFlg;
extern	uint16	l_CardType;

//-------------------------------------------------------------------------------------------------
//��������:             void	DataCardPartRead(void)
//��������:             ��ͨ������
//��ڲ���:             ��
//���ڲ���:             ��
//--------------------------------------------------------------------------------------------------
void	DataCardPartRead(void)
{
/*
	static	stcDeviceInfo 	sDeviceInfo;
	static	stcFixInfo		sFixInfo;		
	uint32	FlshRecCnt;	
	uint32	FlshStartRecNum;
	uint32	CardEndAddr;
	uint32	CardStartAddr;
	uint32	CardMaxRecNum;
	uint32	NoReadRecNum;
	uint16	CrcCheck;
	uint32	FinshRecCnt = 0;
	uint32	CardTime = 0;

	PrintfDebug("\r\nDataCard");
	
	ClaerDisplaySet();												//����ʾ������
	OffAllLed();													//�����з��������
	OnLed(RUN_LED,30000,5,5);										//����ʾ������		
	//CloseTax2();
		
	PrintfDebug("\r\n OperationCard");
	
	DisplaySet(100,1,"PRCD");

	while(1)
	{
		if(PlugICCard() == TRUE)										//�п����룬�ٽ�����ز���
		{	
			ClaerDisplaySet();												//����ʾ������
				
			ReadCardFlg((stcCardFlg *)&l_sCardFlg);
			
			if( l_CardType == DATA_CARD )
			{
				CardTime++;
				
				if(l_sCardFlg.WriteCardTimes >= 100)	
				{	
					l_sCardFlg.WriteCardTimes = 0;
				}
					
				if(l_sCardFlg.WriteCardTimes == 0)						//��ַ����
				{
					CardStartAddr = CARD_DATA_ADDR;
				}
				else
				{
					CardStartAddr 	= l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes - 1].EndAddr;
					
					if(CardStartAddr < CARD_DATA_ADDR)
					{
						CardStartAddr = CARD_DATA_ADDR;
					}
					
					if((CardStartAddr - CARD_DATA_ADDR) %  sizeof(stcFlshRec))	//��ַ����
					{
						CardStartAddr = CardStartAddr - (CardStartAddr - CARD_DATA_ADDR) %  sizeof(stcFlshRec);
					}
				}
				
				g_LshRedFlshRecNum = 0;												//
				
				if((g_CurFlshRecNum - g_LshRedFlshRecNum) /(FLSH_MAX_SIZE/(sizeof(stcFlshRec))))
				{
					NoReadRecNum = FLSH_MAX_SIZE/(sizeof(stcFlshRec));
				}
				else
				{
					NoReadRecNum	= (g_CurFlshRecNum - g_LshRedFlshRecNum);			//Flsh��δ����¼����
				}
				
				if(NoReadRecNum <=  FinshRecCnt + 100)									//���ݼ�¼ȫ����
				{
					IndicateRecordFinsh();
					
					while(PlugICCard() == TRUE)
					{
						NOP();
					}
					
					break;
				}
				
				CardMaxRecNum	= GetToEndLen(CardStartAddr) / sizeof(stcFlshRec);		//ȡIC��δд�ռ䳤��
					
				FlshRecCnt 		= GetReadFlshRecCnt(NoReadRecNum,CardMaxRecNum);		//Ҫд���ݳ���
				
				FlshStartRecNum = g_CurFlshRecNum  - FlshRecCnt -  FinshRecCnt;    		//��ʼ����дʱ��ʼ��ˮ��
				
				FinshRecCnt += FlshRecCnt;												//����ɵ���ˮ�Ÿ���

				//printfcom0("\r\nNoReadRecNum %d,CardMaxRecNum %d,FlshRecCnt %d,FlshStartRecNum %d l_sCardFlg.WriteCardTimes %d,GetToEndLen(CardStartAddr) %d",
				NoReadRecNum,CardMaxRecNum,FlshRecCnt,FlshStartRecNum,l_sCardFlg.WriteCardTimes,GetToEndLen(CardStartAddr));
				
				if((l_sCardFlg.WriteCardTimes < 100)  && ( CardMaxRecNum > 20))			//��д��
				{
					l_UnFihCardEvtFlg = NO_ERROR;

					if( NoReadRecNum > 1 )											//δ����¼���������1���ܶ�ȡ����	
					{
						if( StoreCardRec(FlshStartRecNum,FlshRecCnt,CardStartAddr,l_sCardFlg.WriteCardTimes))		//����1 д�����
						{
							uint8	i;
							uint8	Tmp;
							uint16	DataTmp;
							uint8	Buf[5] = {'0','0','0','0','0'};
						
							ReadHostInfo((stcDeviceInfo * )&sDeviceInfo);
							
							ReadFixInfo((stcFixInfo * )&sFixInfo);
							
							memcpy(l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].ProNum
										,sDeviceInfo.ProduceDate,sizeof(sDeviceInfo.ProduceDate));
					
							DataTmp = sDeviceInfo.DeviceNum;
							for(i = 0; i < 5;i++)
							{
								Tmp = DataTmp%10;
								DataTmp /= 10;
								if(DataTmp != 0)
								{
									Buf[5-1-i] = Tmp + '0';
								}
							}
							
							memcpy(&l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].ProNum[sizeof(sDeviceInfo.ProduceDate)],Buf,5);
							l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].LocoType[0]	= sFixInfo.LocoTyp;
							l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].LocoType[1]	= sFixInfo.E_LocoTyp;	
							memcpy(l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].LocoNum,sFixInfo.LocoNum,sizeof(sFixInfo.LocoNum));		
							l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].StartAddr= CardStartAddr;
							CardEndAddr	= CardStartAddr + ( FlshRecCnt * sizeof(stcFlshRec));
							l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].EndAddr 	= CardEndAddr;
							//l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].RecLen	= CardEndAddr - CardStartAddr;
							l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].RecLen	=  FlshRecCnt * sizeof(stcFlshRec);
							l_sCardFlg.sCardIndex[l_sCardFlg.WriteCardTimes].RecNum	= FlshRecCnt;
							
							l_sCardFlg.WriteCardTimes++;									

							CrcCheck = GetCrc16Check((uint8 *)&l_sCardFlg,sizeof(stcCardFlg) -2);

							l_sCardFlg.CrcCheck = CrcCheck;									

							WriteCardFlg((stcCardFlg *)&l_sCardFlg);					//�޸�IC����־ҳ
										
							//StoreLstRedFlshRecNum(g_CurFlshRecNum);					//�����µ��Ѷ���¼��ˮ��
							
							//g_LshRedFlshRecNum = g_CurFlshRecNum;
							
							IndicateWriteCardFinsh();									//

						}
						else															//д���������
						{
							l_UnFihCardEvtFlg = ERROR;
							
							DelayX10ms(10);	
							
							IndicateWriteNoFinsh();										//д��δ���ָʾ
							
							DelayX10ms(500);											//δд��
						}
					}
					else
					{
						IndicateWriteCardFinsh();								//

					}

				}
				else
				{
					IndicateCardFull();
				}
				
				while(PlugICCard() == TRUE)
				{
					NOP();
				}				
				
				DelayX10ms(500);												//��������ʱ5S
				ClaerDisplaySet();												//����ʾ������
				DisplaySet(100,5,"%u",CardTime);
			}
			else
			{
				DisplaySet(100,10,"UNDF");
				DisplaySet(100,10,"     ");
				while( PlugICCard() != TRUE)
				{
					NOP();
				}
				
				ClaerDisplaySet();												//����ʾ������
			}
		}
		else
		{
			DisplaySet(100,1,"PRCD");

			while( PlugICCard() != TRUE)
			{
				NOP();
			}
		}
	}
*/
} 


//-------------------------------------------------------------------------------------------------
//��������:             void	GetUnFihCardEvtFlg(void)
//��������:             ȡδ�������ת����ʶ
//��ڲ���:             ��
//���ڲ���:             ��
//--------------------------------------------------------------------------------------------------
uint8	GetUnFihCardEvtFlg(void)
{
	return	l_UnFihCardEvtFlg;
}

//-------------------------------------------------------------------------------------------------
//��������:             void	GetUnFihCardEvtFlg(void)
//��������:             ȡδ�������ת����ʶ
//��ڲ���:             ��
//���ڲ���:             ��
//--------------------------------------------------------------------------------------------------
//uint8	GetWriteFlgErrCardEvtFlg(void)
//{
//	return	l_WriteFlgErrCardEvtFlg;
//}

//-------------------------------------------------------------------------------------------------
//��������:             void	GetUnFihCardEvtFlg(void)
//��������:             ȡδ�������ת����ʶ
//��ڲ���:             ��
//���ڲ���:             ��
//--------------------------------------------------------------------------------------------------
void	ResetUnFihCardEvtFlg(void)
{
	l_UnFihCardEvtFlg = NO_ERROR;
}

//----------------------------------------------------------------------
//��������:  	void    ReadCopyCardDisplay(uint8	 Sct)
//��������:  	���ͳ߼�¼FLASHת��ΪIC����¼
//��ڲ���:   	FLASH��¼
//���ڲ���:   	IC����¼
//˵��:                 
//-----------------------------------------------------------------------
void    ReadCopyCardDisplay(uint8	 Sct)
{
	uint8	i = 0;
	
	while(i < 10 )
	{
		DisplaySet(3,10000,"       %u",i);
		i++;
	}
}

extern	uint32		l_CardPageSize;	
extern	uint32		l_CardPageNum;
//-------------------------------------------------------------------------------------------------
//��������:             uint32	GetCardMaxRecNum(void)
//��������:             ȡһ��IC������ܴ��������ݼ�¼��
//��ڲ���:             �������ṹ��
//���ڲ���:             �Ƿ�ɹ�
//--------------------------------------------------------------------------------------------------
uint32	GetCardMaxRecNum(void)
{
	uint32	RecNum;
	
	RecNum = (l_CardPageNum*l_CardPageSize - CARD_DATA_ADDR)/ sizeof(stcFlshRec);
	
	return	RecNum;
}

//-------------------------------------------------------------------------------------------------
//��������:             uint8	DataCopyCard(stcCardFlg	* sCardFlg)
//��������:             �����ݿ�
//��ڲ���:             �������ṹ��
//���ڲ���:             �Ƿ�ɹ�
//--------------------------------------------------------------------------------------------------
//uint8	DataCopyCard(void)
//{
////	uint32	FlshRecCnt;	
////	uint32	FlshStartRecNum;
////	uint32	CardStartAddr;
////	uint32	CardEndAddr;
////	uint32	CardMaxRecNum;
////	uint32	NoReadRecNum;
////	uint16	CrcCheck;	
////	uint32	Time;
////	stcDeviceInfo 	sDeviceInfo;
////	stcFixInfo		sFixInfo;	
////	uint16	WriteCardTimes;
////	stcCardIndex	sCardIndex[100];
////
////	
////	ReadCard(CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType)+sizeof(stcCardPara)+sizeof(stcCardIndex)*100,
////			(uint8 *)&WriteCardTimes,sizeof(stcCardType));	
////	ReadCard(CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType)+sizeof(stcCardPara),
////			(uint8 *)&sCardIndex[0],sizeof(stcCardIndex)*100);			
////	
////	if(g_CurFlshRecNum > 1 && g_CurFlshRecNum > g_LshRedFlshRecNum)
////	{
////		NoReadRecNum	= (g_CurFlshRecNum - g_LshRedFlshRecNum);			//Flsh��δ����¼����
////	}
////	else
////	{
////		NoReadRecNum = 0;
////	}
////	
////	CardMaxRecNum	= GetToEndLen(CardStartAddr) / sizeof(stcFlshRec);			//ȡIC��δд�ռ䳤��
////		
////	FlshRecCnt 		= GetCardMaxRecNum() - 1;	//Ҫд���ݳ���
////	
////	if(g_CurFlshRecNum > FlshRecCnt)
////	{
////		FlshStartRecNum = g_CurFlshRecNum - FlshRecCnt;
////	}
////	else
////	{
////		FlshRecCnt = g_CurFlshRecNum;
////
////		FlshStartRecNum = 0;
////	}
////	
////	CardStartAddr = CARD_DATA_ADDR;
////	
////	if( StoreCardRec(FlshStartRecNum,FlshRecCnt,CardStartAddr,WriteCardTimes))		//����1 д�����
////	{
////		uint8	i;
////		uint8	Tmp;
////		uint16	DataTmp;
////		uint8	Buf[5] = {'0','0','0','0','0'};
////	
////		ReadHostInfo((stcDeviceInfo * )&sDeviceInfo);
////		
////		ReadFixInfo((stcFixInfo * )&sFixInfo);
////		
////		memcpy(sCardIndex[WriteCardTimes].ProNum
////					,sDeviceInfo.ProduceDate,sizeof(sDeviceInfo.ProduceDate));
////
////		DataTmp = sDeviceInfo.DeviceNum;
////		for(i = 0; i < 5;i++)
////		{
////			Tmp = DataTmp%10;
////			DataTmp /= 10;
////			if(DataTmp != 0)
////			{
////				Buf[5-1-i] = Tmp + '0';
////			}
////		}
////		
////		memcpy(&sCardIndex[WriteCardTimes].ProNum[sizeof(sDeviceInfo.ProduceDate)],Buf,5);
////		sCardIndex[WriteCardTimes].LocoType[0]	= sFixInfo.LocoTyp;
////		sCardIndex[WriteCardTimes].LocoType[1]	= sFixInfo.E_LocoTyp;	
////		memcpy(sCardIndex[WriteCardTimes].LocoNum,sFixInfo.LocoNum,sizeof(sFixInfo.LocoNum));		
////		sCardIndex[WriteCardTimes].StartAddr= CardStartAddr;
////		CardEndAddr	= CardStartAddr + ( FlshRecCnt * sizeof(stcFlshRec));
////		sCardIndex[WriteCardTimes].EndAddr 	= CardEndAddr;
////		//sCardIndex[WriteCardTimes].RecLen	= CardEndAddr - CardStartAddr;
////		sCardIndex[WriteCardTimes].RecLen	=  FlshRecCnt * sizeof(stcFlshRec);
////		sCardIndex[WriteCardTimes].RecNum	= FlshRecCnt;
////		
////		WriteCardTimes++;									
////
//////		CrcCheck = GetCrc16Check((uint8 *)sCardFlg,sizeof(stcCardFlg) -2);
//////
//////		CrcCheck = CrcCheck;									
////
//////		WriteCardFlg(sCardFlg);									//�޸�IC����־ҳ
////					
////		//StoreLstRedFlshRecNum(g_CurFlshRecNum );				//�����µ��Ѷ���¼��ˮ��
////		
////		//g_LshRedFlshRecNum = g_CurFlshRecNum;
////		
////		IndicateWriteCardFinsh();								//	
////	}
////	else															//д���������
////	{
////		DelayX10ms(10);	
////		
////		IndicateWriteNoFinsh();										//д��δ���ָʾ
////		
////		DelayX10ms(500);											//δд��
////	}
////
////	Time = GetSysTime();	
////	
////	while(PlugICCard())
////	{
////		NOP();
////		//SysHoldTast();
////		
////		if(GetSysTime() - Time > 20*100)
////		{
////			break;
////		}
////	}
////	
////	return 1;
//}
//		
