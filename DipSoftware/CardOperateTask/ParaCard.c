////#include 	"config.h"
////#include 	"String.h"
////#include	"Globe.h"
////#include	"HardDrive.h"
////#include	"CpuDrive.h"
////#include	"OperateCard.h"
////#include	"FramStore.h"
////#include	"CardTest.h"
//
//
#include    "includes.h"  
#include	"Card.h"
#include	"OperateCard.h" 
#include	"FRAM.h" 
//
////-------------------------------------------------------------------------------------------------
////��������:             uint8	SetSucceedIndicate(void)
////��������:             ���ô���ɹ�ָʾ
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
void	SetSucceedIndicate(void)
{
//	DisplaySet(60,0,"SETS");	
//	DisplaySet(60,0,"        ");	
}

////-------------------------------------------------------------------------------------------------
////��������:             uint8	StoreErrIndicate(void)
////��������:             ��������Ϣʧ��ָʾ
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
void	StoreErrIndicate(void)
{
	DisplaySet(60,100,"STRE");	
	DisplaySet(60,100,"        ");	
}

////-------------------------------------------------------------------------------------------------
////��������:             uint8	CrcCheckErrIndicate(void)
////��������:             ������ϢУ���ʧ��ָʾ
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
void	CrcCheckErrIndicate(void)
{
	DisplaySet(60,100,"CRCE");	
	DisplaySet(60,100,"        ");	
}

////-------------------------------------------------------------------------------------------------
////��������:             uint8	ModCard(stcCardFlg	sCardFlg)
////��������:             ��ͨ������
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
uint8	ModCard(void)
{
	uint8	buf[256];
	uint32	writedsize = 0;
	uint32	readsize = 0;
		
	while(writedsize < sizeof(stcModelCard))
	{
		readsize = (sizeof(stcModelCard)- writedsize)>256?
					256:(sizeof(stcModelCard)- writedsize);

		ReadCard(CARD_DATA_ADDR+writedsize,buf,readsize);

		StoreOilBoxModel(writedsize,buf,readsize);

		writedsize +=readsize;
	}

	DisplaySet(60,3,"      ");
	DisplaySet(60,3,"SETS");	
		
	return	1;
} 
//
//extern	stcModelCard	l_sModelCard;	 
////-------------------------------------------------------------------------------------------------
////��������:             uint8	COM0ModData(void)
////��������:             ��ͨ������
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
//uint8	COM0ModData(void)
//{
//	uint16	CrcCheck;
//		
//	CrcCheck = GetCrc16Check((uint8 *)&l_sModelCard,sizeof(stcModelCard) - 2);
//		
//	if(CrcCheck == l_sModelCard.CrcCheck)				//У������		
//	{			
//		//printfcom0("\r\nModCard(void) CCrcCheck == sModelCard.CrcCheck %d",l_sModelCard.CrcCheck);	
//
//		if(StoreOilBoxModel((stcModelCard *)&l_sModelCard))
//		{
//			SetSucceedIndicate();
//			return	1;
//		}
//		else
//		{
//			StoreErrIndicate();
//			return	0;
//		}
//	}
//	
//	CrcCheckErrIndicate();	
//
//	return	0;
//} 
////-------------------------------------------------------------------------------------------------
////��������:             uint8	DensityCard(stcCardFlg	sCardFlg)
////��������:             ��ͨ������
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
////uint8	DensityCard(stcCardFlg *	sCardFlg)
////{
////	static	stcDensity	sDensity;						//�ܶ�
////	uint16		CrcCheck;
////	
////	CrcCheck = GetCrc16Check((uint8 *)&sCardFlg->sCardPara,sizeof(sCardFlg->sCardPara) - 2);
////	
////	if(CrcCheck == sCardFlg->sCardPara.CrcCheck)
////	{
////		sDensity = sCardFlg->sCardPara.sDensity;
////		
////		CrcCheck = GetCrc16Check((uint8 *)&sDensity,sizeof(sDensity) - 2);
////		
////		if(CrcCheck == sDensity.CrcCheck)				//У������		
////		{			
////			//PrintfDebug("\r\n sDensity.Density %d",sDensity.Density );
////			
////			if(StoreDensity((stcDensity *)&sDensity))
////			{
////				DisplaySet(150,1,"%d",sDensity.Density);
////				
////				SetSucceedIndicate();	
////				
////				return	1;
////			}
////			else
////			{
////				StoreErrIndicate();	
////				
////				return	0;
////			}
////		}
////	}
////	
////	CrcCheckErrIndicate();
////		
////	return	0;
////}

uint8	ReadCardPara(stcCardPara * sCardPara)
{
	uint16		CrcCheck;
	ReadCard(CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType),
			(uint8 *)sCardPara,sizeof(stcCardPara));

	CrcCheck = GetCrc16Check((uint8 *)sCardPara,sizeof(stcCardPara) - 2);
	
	if(CrcCheck == sCardPara->CrcCheck)		
	{
		return	1;
	}
	else
	{
		return	0;
	}
}

uint8	WriteCardPara(stcCardPara * sCardPara)
{
	uint16		CrcCheck;

	CrcCheck = GetCrc16Check((uint8 *)sCardPara,sizeof(stcCardPara) - 2);

	sCardPara->CrcCheck = CrcCheck;

	WriteCard(CARD_FLG_ADDR+sizeof(stcCardID)+sizeof(stcCardType),
			(uint8 *)sCardPara,sizeof(stcCardPara));
	
	return 1;	
}

uint16	GetCardDensityVal(void)
{
	stcDensity	sDensity;						//�ܶ�
	stcCardPara	sCardPara;
	uint16		CrcCheck;
	
	if(ReadCardPara((stcCardPara *)	&sCardPara))
	{
		sDensity = sCardPara.sDensity;
		
		CrcCheck = GetCrc16Check((uint8 *)&sDensity,sizeof(sDensity) - 2);
		
		if(CrcCheck == sDensity.CrcCheck)				//У������		
		{			
			if(StoreDensity((stcDensity *)&sDensity))
			{
				DisplaySet(150,1,"%d",sDensity.Density);
				
				SetSucceedIndicate();	
				
				return	1;
			}
			else
			{
				StoreErrIndicate();	
				
				return	0;
			}
		}
	}
	
	CrcCheckErrIndicate();
		
	return	0;
}

uint8	DensityCard(void)
{
	stcDensity	sDensity;						//�ܶ�
	stcCardPara	sCardPara;
	uint16		CrcCheck;
	
	if(ReadCardPara((stcCardPara *)	&sCardPara))
	{
		sDensity = sCardPara.sDensity;
		
		CrcCheck = GetCrc16Check((uint8 *)&sDensity,sizeof(sDensity) - 2);
		
		if(CrcCheck == sDensity.CrcCheck)				//У������		
		{			
			if(StoreDensity((stcDensity *)&sDensity))
			{
				DisplaySet(150,1,"%d",sDensity.Density);
				
				SetSucceedIndicate();	
				
				return	1;
			}
			else
			{
				StoreErrIndicate();	
				
				return	0;
			}
		}
	}
	
	CrcCheckErrIndicate();
		
	return	0;
} 
 
//
//extern	uint8 StoreDenChangeTimes(uint32  Times);
//
////------------------------------------------------------------------------
////  ��  �� ��	uint8 	ReadCurFlshTimes(void)
////  ��  �� ��	����ǰ��¼װ�ü�¼��ˮ��
//// ��ڲ�����	��
//// ���ڲ�����	��ǰ��ˮ��
////------------------------------------------------------------------------
//extern	uint32 ReadDenChangeTimes(void);
//
////-------------------------------------------------------------------------------------------------
////��������:             uint8	DenDataCard(stcCardFlg	sCardFlg)
////��������:             ��ͨ������
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
uint8	DenDataCard(stcCardFlg *	sCardFlg)
{

	DensityCard();

	DisplaySet(100,1,"DATA.");
	
	DataCard(0);												//���ݿ�����������תȡ
		
	return	1;
} 

////-------------------------------------------------------------------------------------------------
////��������:             uint8	DataDensityCard(stcCardFlg	sCardFlg)
////��������:             ��ͨ������
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
//void	DataDensityCard(stcCardFlg *	sCardFlg)
//{
//	static	stcDensity	sDensity;						//�ܶ�
//	uint16		CrcCheck;
//	
//	CrcCheck = GetCrc16Check((uint8 *)&sCardFlg->sCardPara,sizeof(sCardFlg->sCardPara) - 2);
//	
//	if(CrcCheck == sCardFlg->sCardPara.CrcCheck)
//	{
//		sDensity = sCardFlg->sCardPara.sDensity;
//		
//		CrcCheck = GetCrc16Check((uint8 *)&sDensity,sizeof(sDensity) - 2);
//		
//		if(CrcCheck == sDensity.CrcCheck)				//У������		
//		{			
//			if(sDensity.AddOilStationNum == 1)
//			{
//				//PrintfDebug("\r\n sDensity.Density %d",sDensity.Density );
//				
//				if(StoreDensity((stcDensity *)&sDensity))
//				{
//					SetSucceedIndicate();	
//				}
//			}
//		}
//	}	
//} 
//
////-------------------------------------------------------------------------------------------------
////��������:             void	ComModCard(stcCardFlg	sCardFlg)
////��������:           	����ģ�Ϳ�
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
//uint8	ComModCard(stcCardFlg	* sCardFlg)
//{
//	static	stcModelComplex	sModelComplex;	
//	uint32	CardAddLen = 0;
//	uint32	FlshAddLen = 0;
//	uint8	i;
//	uint8	CardFlg;
//	uint8	FlshFlg;
//	uint8   *p;
//	uint32	j;
//	
//	FlshAddLen = 0;
//		
//	UnProtectFlash();
//	
//	CardAddLen = sizeof(stcModelCard);
//
//	for(i = 0; i< 1; i++)
//	{
//		CardFlg = ReadCard(CARD_DATA_ADDR + CardAddLen,(uint8 *)&sModelComplex,sizeof(stcModelComplex));
//		FlshFlg = WriteFlsh(FRAM_SIZE + FlshAddLen,(uint16 *)&sModelComplex,sizeof(stcModelComplex));
//    	
//    	p = (uint8 *)&sModelComplex;
//    	
//    	
//    	
//    	
//    	
//    	//printfcom0("\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
//    	for(j=0;j < sizeof(stcModelComplex);j++)
//    	{
//    		//printfcom0("%2x",*(p++));
//    	}
//    	//printfcom0("\r\n\r\n\r\n\r\n\r\n\r\n\r\n");
//
//    	//printfcom0("\r\n  ModelNum %d;i =%d,CardFlg %d,CARD_DATA_ADDR + CardAddLen %d",sModelComplex.ModelNum,i,CardFlg,CARD_DATA_ADDR + CardAddLen);
//
//		////printfcom0("\r\n\r\n  OilBoxTypCod  %d   %d \r\n",OilBoxTypCod,sComplexModel->ModelNum);
//
//		CardAddLen += sizeof(stcModelComplex);
//		FlshAddLen += sizeof(stcModelComplex);
//	}
//	
//
//	ProtectFlash();
//
//	if(CardFlg == TRUE && FlshFlg == TRUE)
//	{
//		SetSucceedIndicate();
//		DisplaySet(60,2,"SETS");	
//		DisplaySet(60,2,"        ");	
//	}
//	else
//	{
//		DisplaySet(60,2,"ERRO");	
//		DisplaySet(60,2,"        ");	
//		//printfcom0("\r\n CardFlg =%d,FlshFlg =%d,",CardFlg,FlshFlg);
//	}
//	
//	return	1;
//} 
//
////-------------------------------------------------------------------------------------------------
////��������:             void	DensityCard(stcCardFlg	sCardFlg)
////��������:             ��ͨ������
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
//uint8	TimeCard(stcCardFlg	* sCardFlg)
//{
///*
//	stcTime			sTime;							
//	uint16			CrcCheck;
//
//	CrcCheck = GetCrc16Check((uint8 *)&sCardFlg->sCardPara,sizeof(sCardFlg->sCardPara) - 2);
//	
//	if(CrcCheck == sCardFlg->sCardPara.CrcCheck)
//	{
//		sTime = sCardFlg->sCardPara.sTime;
//		
//		CrcCheck = GetCrc16Check((uint8 *)&sTime,sizeof(sTime) - 2);
//		
//		if(CrcCheck == sTime.CrcCheck)				//У������		
//		{
//			DisplaySet(100,1,"STIM");	
//			
//			WriteTime(sTime);
//	
//			SetSucceedIndicate();	
//			return	1;
//		}
//	}
//	
//	CrcCheckErrIndicate();
//*/		
//	return	0;
//} 
//
////extern	void	UsbSetAddDipVal( int16	Dip );
////-------------------------------------------------------------------------------------------------
////��������:             uint8	SetDataCard(stcCardFlg	* sCardFlg)
////��������:             �����ݿ�
////��ڲ���:             �������ṹ��
////���ڲ���:             �Ƿ�ɹ�
////--------------------------------------------------------------------------------------------------
uint8	SetDataCard(void)
{
	stcCardPara	sCardPara;
	
	if(ReadCardPara((stcCardPara *)	&sCardPara))
	{
//		 AddDipVal = sCardPara.SetVal;
	}
	
	return 1;
} 


////-------------------------------------------------------------------------------------------------
////��������:             void	HightCard(stcCardFlg	sCardFlg)
////��������:             �߶�����������
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
uint8	HightCard(void)
{
	stcReviseHight	sReviseHight;							//�߶ȵ���
	uint16		CrcCheck;
	int16		StoreHight;	
	stcCardPara	sCardPara;
		
	if(ReadReviseHight((stcReviseHight *)&sReviseHight))
	{
		StoreHight = sReviseHight.ReviseHight;
	}
	else
	{
		StoreHight = 0;
	}
		
	if(ReadCardPara((stcCardPara *)	&sCardPara))
	{
		sReviseHight = sCardPara.sReviseHight;
		
		CrcCheck = GetCrc16Check((uint8 *)&sReviseHight,sizeof(sReviseHight) - 2);
		
		if(CrcCheck == sReviseHight.CrcCheck)				//У������		
		{
		//	DisplaySet(150,1,"SHIG");
			StoreHight = StoreHight + sReviseHight.ReviseHight; 	
			if(StoreHight > 500 ||  StoreHight < -500)
			{
				if(StoreHight > 500)
				{
					sReviseHight.ReviseHight = 500;
					DisplaySet(60,2,"TO_H");
					DisplaySet(60,2,"    ");
					DelayX10ms(250);
				}
				else
				{
					sReviseHight.ReviseHight = -500;
					DisplaySet(60,2,"TO_L");
					DisplaySet(60,2,"    ");
					DelayX10ms(250);					
				}
			}
			else
			{
				sReviseHight.ReviseHight = StoreHight;
			}
			
			CrcCheck = GetCrc16Check((uint8 *)&sReviseHight,sizeof(sReviseHight) - 2);
			sReviseHight.CrcCheck = CrcCheck;
			
			if(StoreReviseHight((stcReviseHight *)&sReviseHight))
			{
				DisplaySet(150,1,"%d",sReviseHight.ReviseHight);

				SetSucceedIndicate();	
				
				return	1;
			}
			else
			{
				StoreErrIndicate();	
				
				return	0;
			}
		}
	}
	
	CrcCheckErrIndicate();
		
	return	0;
} 

////-------------------------------------------------------------------------------------------------
////��������:             uint8	ModelSelectCard(stcCardFlg	* sCardFlg)
////��������:             ģ��ѡ��
////��ڲ���:             �������ṹ��
////���ڲ���:             �Ƿ�ɹ�
////--------------------------------------------------------------------------------------------------
uint8	ModelSelectCard(void)
{
	uint8			ModelNum;							

	stcCardPara	sCardPara;

	if(ReadCardPara((stcCardPara *)	&sCardPara))
	{
		ModelNum = sCardPara.SetVal;

		if(StoreSelectModel(ModelNum))
		{
			DisplaySet(150,1,"%d",ModelNum);			
			SetSucceedIndicate();	
			
			return	1;
		}
		else
		{
			StoreErrIndicate();	
			
			return	0;
		}
		
	}
	
	CrcCheckErrIndicate();
		
	return	0;
}
//
//extern	float		l_Density;		
//extern	float  		l_ReviseHight;              		//�����߶�
//extern  void		ReCalPara(uint8	Flg);
//extern	int16  		GetDip1Prs(void);
//extern	int16  		GetDip2Prs(void);
//extern	uint8  		GetOilBoxCod(void);
//
////-------------------------------------------------------------------------------------------------
////��������:             uint8	DebugCard(stcCardFlg	* sCardFlg)
////��������:             ���Կ�
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
//uint8	DebugCard(stcCardFlg	* sCardFlg)
//{
//	uint32	AllStrLen = 0;
//	int16	CurDip1Prs;
//	int16	CurDip2Prs;
//	uint8	ModNum;
//	uint16	Density;
//	uint16	Hight;
//	uint16	CrcCheck;
//	
//	ReCalPara(1);
//
//	CurDip1Prs	=	GetDip1Prs();
//	CurDip2Prs	=	GetDip2Prs();
//	ModNum		=  	GetOilBoxCod();
//	Density		=  	(uint16)(l_Density*1000);
//	Hight		= 	(uint16)l_ReviseHight;
//	
//	DisplaySet(150,1,"DIP1");								
//	DisplaySet(200,1,"%d",CurDip1Prs);					
//	
//	DisplaySet(150,1,"DIP2");								
//	DisplaySet(200,1,"%d",CurDip2Prs);					
//	
//	DisplaySet(150,1,"MODE");								
//	DisplaySet(200,1,"C_%d",ModNum);							
//	
//	DisplaySet(150,1,"DENS");
//	DisplaySet(200,1,"%d",Density);
//	
//	DisplaySet(150,1,"HIGH");
//	DisplaySet(200,1,"%d",Hight);	
//	
//	PrintfTime();
//	DisplayTime();
//
//	memcpy((int8 *)&sCardFlg->sCardPara.sDebugCard.Buf[AllStrLen],(int8 *)&CurDip1Prs,2);
//	
//	AllStrLen += 2;
//	memcpy((int8 *)&sCardFlg->sCardPara.sDebugCard.Buf[AllStrLen],(int8 *)&CurDip2Prs,2);
//	
//	AllStrLen += 2;
//	memcpy((int8 *)&sCardFlg->sCardPara.sDebugCard.Buf[AllStrLen],(int8 *)&ModNum,2);
//	
//	AllStrLen += 2;
//	memcpy((int8 *)&sCardFlg->sCardPara.sDebugCard.Buf[AllStrLen],(int8 *)&Density,2);
//	
//	AllStrLen += 2;
//	memcpy((int8 *)&sCardFlg->sCardPara.sDebugCard.Buf[AllStrLen],(int8 *)&Hight,2);
//	
//	AllStrLen += 2;
//	sCardFlg->sCardPara.sDebugCard.BufLen = AllStrLen;			//��Ч���ݳ���
//
//	CrcCheck = GetCrc16Check((uint8 *)&sCardFlg->sCardPara.sDebugCard,sizeof(sCardFlg->sCardPara.sDebugCard )- 2);
//	sCardFlg->sCardPara.sDebugCard.CrcCheck = CrcCheck;
//
//	CrcCheck = GetCrc16Check((uint8 *)&sCardFlg->sCardPara,sizeof(sCardFlg->sCardPara) - 2);
//	sCardFlg->sCardPara.CrcCheck = CrcCheck;	
//	
//	CrcCheck = GetCrc16Check((uint8 *)sCardFlg,sizeof(stcCardFlg) - 2);
//	sCardFlg->CrcCheck = CrcCheck;		
//	
//	WriteCardFlg(sCardFlg);										//�޸�IC����־ҳ	
//	
//	return 	1;
//	
///*
//	static	stcDebugCard	sDebugCard;							//�߶ȵ���
//	uint16	CrcCheck;
//
//	CrcCheck = GetCrc16Check((uint8 *)&sCardFlg->sCardPara,sizeof(sCardFlg->sCardPara) - 2);
//	
//	if(CrcCheck == sCardFlg->sCardPara.CrcCheck)
//	{
//		sDebugCard = sCardFlg->sCardPara.sDebugCard;
//		
//		CrcCheck = GetCrc16Check((uint8 *)&sDebugCard,sizeof(sDebugCard) - 2);
//		
//		if(CrcCheck == sDebugCard.CrcCheck)				//У������		
//		{
//			DisplaySet(100,1,"SDBG");	
//			
//			if(StoreReviseHight((stcReviseHight *)&sDebugCard))
//			{
//				SetSucceedIndicate();	
//				
//				return	1;
//			}
//			else
//			{
//				StoreErrIndicate();	
//				
//				return	0;
//			}
//		}
//	}
//	
//	CrcCheckErrIndicate();
//		
//	return	0;
//*/
//}
//
////-------------------------------------------------------------------------------------------------
////��������:             uint8	FixCard(stcCardFlg	* sCardFlg)
////��������:             �߶�����������
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
uint8	FixCard(void)
{
	stcFixInfo		sFixInfo;							//�߶ȵ���
	uint16		CrcCheck;
	stcCardPara	sCardPara;

	if(ReadCardPara((stcCardPara *)	&sCardPara))
	{
		sFixInfo = sCardPara.sFixInfo;
		
		CrcCheck = GetCrc16Check((uint8 *)&sFixInfo,sizeof(sFixInfo) - 2);
		
		if(CrcCheck == sFixInfo.CrcCheck)				//У������		
		{
			DisplaySet(100,1,"%d",sFixInfo.LocoTyp);	
			DisplaySet(100,1,"%d",sFixInfo.LocoNum[1]*256+sFixInfo.LocoNum[0]);	
			
			if(StoreFixInfo((stcFixInfo *)&sFixInfo))
			{
				SetSucceedIndicate();	
				return	1;
			}
			else
			{
				StoreErrIndicate();	
				return	0;
			}
		}

	}
	
	CrcCheckErrIndicate();
		
	return	0;
} 
//
////-------------------------------------------------------------------------------------------------
////��������:             uint8	CopyFramCard(stcCardFlg	* sCardFlg)
////��������:             �߶�����������
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
//uint8	CopyFramCard(stcCardFlg	* sCardFlg)
//{
//	DisplaySet(100,1,"CFRA");	
//
//	FramToCard();
//	
//	SetSucceedIndicate();	
//	
//	return	1;
//} 
//
#define	TIME_ADD_CARD	0x01
#define	TIME_SUB_CARD	0x02
////-------------------------------------------------------------------------------------------------
////��������:             uint8	ExpandCard(stcCardFlg	* sCardFlg)
////��������:             ��չ��
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
uint8	ExpandCard(void)
{
	uint8	CardType;
	uint32	i;
	uint32	DisTime = 40;		//500ms
	uint32	Time 	= 0;		//500ms
	uint32	Times 	= 0;	
	
	stcTime		sTime;
	stcCardPara	sCardPara;

	if(!ReadCardPara((stcCardPara *)	&sCardPara))
	{	return 0;}


/*	
#ifdef	HARD_VER_090426	
	DisplaySet(150,1,"%u-%u-%u",sTime.Year,sTime.Month,sTime.Date);
	DisplaySet(60,1,"         ");	
	DisplaySet(350,1,"%u-%u-%u.",sTime.Hour,sTime.Min,sTime.Sec);	//�ȴ�ʱ�䲹��
	DisplaySet(60,1,"         ");	
#endif
*/
	CardType = sCardPara.Reserve0;							//������
	
	ReadTime((stcTime *)&sTime);
	i = sTime.Sec + sTime.Min * 60 +  sTime.Hour * 60 * 60;	

	while(1)
	{
		if(CardType == TIME_ADD_CARD)	
		{
			i++;
		}	
		else if(CardType == TIME_SUB_CARD)	
		{
			i--;	
		}
		else
		{
			//printfcom0("\r\n ����ʱ�俨");
			break;
		}
		
		i = i % (60*60*24);
		
		Times++;
		
		sTime.Sec  =   i % 60;
		sTime.Min  =  (i / 60 ) % 60;
		sTime.Hour =  ((i/60)/60) % 24;
		
		DisplaySet(1,1,"%02u-%02u-%02u.",sTime.Hour,sTime.Min,sTime.Sec);		//
		DelayX10ms(1);		

		Time = GetSysTime();
		while(GetSysTime() - Time < DisTime)
		{
		//SysHoldTast();;
		}
		
		if(DisTime > 4)
		{
			DisTime -= Times/10;		
		}
		
		if(GetPlugFlg() != PLUG_IN_CARD)
		{
			DelayX10ms(200);
			WriteTime(sTime);
			DelayX10ms(100);
			break;
		}
	}
	
	return	1;
} 
