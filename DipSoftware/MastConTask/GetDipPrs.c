#include    "includes.h"  


#define		COM_START_CODE		0x55
#define		PC_ADDR				0xaa
#define		HOST_ADDR			0x80
#define		DIP1_ADDR			0xA1
#define		DIP2_ADDR			0xA2
#define		BROAD_ADDR			0xAF
#define		SENSOR1_ADDR		0xB1
#define		SENSOR2_ADDR		0xB2

#define		GET_DIP_PRS			0xc0
#define		SET_DIP_MOD			0xD7
#define		SET_PRS_LIN			0xD6
#define		OUT_SET_PRS			0xD4
//
////------------------------------------------------------------------------
//// ��    �ƣ�   void SentDatToDip1(uint8 *Buf,uint32	BufLen)
//// ��    �ܣ�   �����ݷ��͵��ͳ�1 
//// ��ڲ�����	Buf:���ݻ����� BufLen:���ݻ��������ݳ��� ��Typ:��������
//// ���ڲ�����	��
////------------------------------------------------------------------------
void SentDatToDip1(uint8 *Buf,uint32 BufLen,uint8 Typ)		
{
	uint8	SourceAddr,TargetAddr,DatTyp,StartCode,FramLen;
	uint8	BufTmp[50];
	uint8	i = 0;
	uint16	CrcCheck;
	
	DatTyp		=	Typ;
	StartCode 	= 	COM_START_CODE;
	TargetAddr  = 	DIP1_ADDR;	
	SourceAddr 	=	HOST_ADDR;
	FramLen		= 	BufLen + sizeof(DatTyp);
	
	BufTmp[i++] =	StartCode;
	BufTmp[i++] =	TargetAddr;
	BufTmp[i++] =	SourceAddr;
	BufTmp[i++] =	FramLen;
	BufTmp[i++] =	DatTyp;
 	
	memcpy(&BufTmp[i],Buf,BufLen);
							 
	CrcCheck 	=	GetCrc16Check(BufTmp,BufLen + i);				//��У���
	
	memcpy(&BufTmp[BufLen + i],(uint8 *)&CrcCheck,sizeof(CrcCheck));	

	SendCOM0(BufTmp,i + BufLen + sizeof(CrcCheck));					//��������
}

//------------------------------------------------------------------------
// ��    �ƣ�   void SentDatToDip2(uint8 *Buf,uint32	BufLen)
// ��    �ܣ�   �����ݷ��͵�����װ��2
// ��ڲ�����	Buf:���ݻ����� BufLen:���ݻ��������ݳ��� ��Typ:��������
// ���ڲ�����	��
//------------------------------------------------------------------------
void SentDatToDip2(uint8 *Buf,uint32 BufLen,uint8 Typ)		
{
	uint8	SourceAddr,TargetAddr,DatTyp,StartCode,FramLen;
	uint8	BufTmp[50];
	uint8	i = 0;
	uint16	CrcCheck;
	
	DatTyp		=	Typ;
	StartCode 	= 	COM_START_CODE;
	TargetAddr  = 	DIP2_ADDR;	
	SourceAddr 	=	HOST_ADDR;
	FramLen		= 	BufLen + sizeof(DatTyp);
	
	BufTmp[i++] =	StartCode;
	BufTmp[i++] =	TargetAddr;
	BufTmp[i++] =	SourceAddr;
	BufTmp[i++] =	FramLen;
	BufTmp[i++] =	DatTyp;
	
	memcpy(&BufTmp[i],Buf,BufLen);
	
	CrcCheck 	=	GetCrc16Check(BufTmp,BufLen + i);				//��У���
	
	memcpy(&BufTmp[BufLen + i],(uint8 *)&CrcCheck,sizeof(CrcCheck));	

	SendCOM0(BufTmp,i + BufLen + sizeof(CrcCheck));					//��������
}
//
////------------------------------------------------------------------------
//// ��    �ƣ�   void SentDatToDip2(uint8 *Buf,uint32	BufLen)
//// ��    �ܣ�   �����װ�ù㲥��Ϣ
//// ��ڲ�����	Buf:���ݻ����� BufLen:���ݻ��������ݳ��� ��Typ:��������
//// ���ڲ�����	��
////------------------------------------------------------------------------
//void SendBroadInfo(uint8 *Buf,uint32	BufLen,uint8 Typ)		
//{
//	uint8	SourceAddr,TargetAddr,DatTyp,StartCode,FramLen;
//	uint8	BufTmp[50];
//	uint8	i = 0;
//	uint16	CrcCheck;
//	
//	DatTyp		=	Typ;
//	StartCode 	= 	COM_START_CODE;
//	TargetAddr  = 	BROAD_ADDR;	
//	SourceAddr 	=	HOST_ADDR;
//	FramLen		= 	BufLen + sizeof(DatTyp);
//	
//	BufTmp[i++] =	StartCode;
//	BufTmp[i++] =	TargetAddr;
//	BufTmp[i++] =	SourceAddr;
//	BufTmp[i++] =	FramLen;
//	BufTmp[i++] =	DatTyp;
//	
//	memcpy(&BufTmp[i],Buf,BufLen);
//	
//	CrcCheck 	=	GetCrc16Check(BufTmp,BufLen + i);				
//	
//	memcpy(&BufTmp[BufLen + i],(uint8 *)&CrcCheck,sizeof(CrcCheck));	
//
//	SendCOM0(BufTmp,i + BufLen + sizeof(CrcCheck));					
//}
//
////------------------------------------------------------------------------
//// ��    �ƣ�   void    BroadDipCod(void)	
//// ��    �ܣ�   ��ȡ����ָ��͵�����װ��
//// ��ڲ�����	��
//// ���ڲ�����	��
////------------------------------------------------------------------------
//void    BroadDipCod(void)
//{
//	static	uint32	Time = 0;
//	static	uint32	Times = 0;
//
//
////2014	if(GetPlugFlg()== PLUG_IN_CARD)
//	{
//		if( GetSysTime() - Time > 100 && Times < 1800)
//		{
//			uint8	BufTmp[100] = {0};
//			
//			memcpy(&BufTmp[1],(uint8 *)&g_DipVal,sizeof(g_DipVal));	
//			
//			SendBroadInfo(BufTmp,sizeof(g_DipVal) + 1,GET_DIP_PRS);	
//			
//			Time = GetSysTime();											//����ǰֵ
//			
//			Times++;
//		}
//	}
////2014	else
//	{
//		Times = 0;
//	}
//}
//
uint8 	l_DipComErrFlg = NO_ERROR;
uint8	l_Dip1ComErrFlg =NO_ERROR;
uint8	l_Dip2ComErrFlg =NO_ERROR;
extern	uint8  GetDip1Data(uint8	*Buf,uint32	RecBufLen);
extern	uint8  GetDip2Data(uint8	*Buf,uint32	RecBufLen);
////------------------------------------------------------------------------
//// ��    �ƣ�   uint16  SendReadCOM1DataCod(void)	
//// ��    �ܣ�   ��ȡ����ָ��͵�����װ��
//// ��ڲ�����	��
//// ���ڲ�����	��
////------------------------------------------------------------------------
void    SendReadCOM0DataCod(void)
{
	static	uint32	Time = 0;
	static	uint8	SendTimes = 0;
	static	uint8	Flg=0;
	static	uint8	Err1Times = 0;
	static	uint8	Err2Times = 0;

	uint8	BufTmp[50] = {0};
	uint32	RecBufLen;
	
	BufTmp[0] = 0;

	if(Flg == 0)
	{
		if(SendTimes == 0)
		{
			memcpy(&BufTmp[1],(uint8 *)&g_DipDisVal,sizeof(g_DipVal));	
			SentDatToDip1(BufTmp,sizeof(g_DipVal) + 1,GET_DIP_PRS);	
			
			Time = GetSysTime();
			SendTimes++;
		}

		if(GetSysTime() - Time > 20)
		{
			RecBufLen = ReadCOM0(BufTmp,sizeof(BufTmp));
 						   
			if( RecBufLen )
			{
				if(GetDip1Data(BufTmp,RecBufLen))						
				{
					l_DipComErrFlg = NO_ERROR;
					l_Dip1ComErrFlg = NO_ERROR;
					SendTimes = 0;
					Err1Times  = 0;
					Flg = 1;				
				}
				else
				{
				   Flg = 0;

				   if(GetSysTime() - Time > 50)
				   {
				   		SendTimes = 0;
				   		Flg = 1;	
				   }
				}
			}
			else
			{
				if(Err1Times++ > 5)
				{
					l_Dip1ComErrFlg= ERROR;		
				}

				SendTimes = 0;
				Flg = 1;	
			}
		}
	}
	else
	{
		if(SendTimes == 0)
		{
			memcpy(&BufTmp[1],(uint8 *)&g_DipDisVal,sizeof(g_DipVal));	
			SentDatToDip2(BufTmp,sizeof(g_DipVal) + 1,GET_DIP_PRS);	
			
			Time = GetSysTime();
			SendTimes++;
		}

		if(GetSysTime() - Time > 20)
		{
			RecBufLen = ReadCOM0(BufTmp,sizeof(BufTmp));
 
			if( RecBufLen )
			{
				if(GetDip2Data(BufTmp,RecBufLen))						
				{
					l_DipComErrFlg  = NO_ERROR;
					l_Dip2ComErrFlg = NO_ERROR;
					SendTimes = 0;
					Flg = 0;
					Err2Times = 0;

				}
				else
				{
				   Flg = 1;
				   if(GetSysTime() - Time > 50)
				   {
				   		SendTimes = 0;
				   		Flg = 0;	
				   }
				}
			}
			else
			{
				if(Err2Times++ > 5)
				{
					l_Dip2ComErrFlg = ERROR;
				}
				SendTimes = 0;
				Flg = 0;
			}
		}		
	}

	if(l_Dip1ComErrFlg == ERROR && l_Dip2ComErrFlg == ERROR)
	{
		l_DipComErrFlg = ERROR;
	}
}

uint8	GetDip1ComErrFlg(void)
{
	return  l_Dip1ComErrFlg;
}

uint8	GetDip2ComErrFlg(void)
{
	return  l_Dip2ComErrFlg;
}

////------------------------------------------------------------------------
//// ��    �ƣ�   void    SetPrs2Line(stcPrsLine * sPrsLine)	
//// ��    �ܣ�   ��ȡ����ָ��͵�����װ��
//// ��ڲ�����	��
//// ���ڲ�����	��
////------------------------------------------------------------------------
//void    SentPrs1Line(stcPrsLine * sPrsLine)
//{
//	uint8	BufTmp[50] = {0};
//
//	BufTmp[0] = 0;
//
//	memcpy(&BufTmp[1],(uint8 *)&g_DipDisVal,sizeof(g_DipVal));	
//
//	SentDatToDip1(BufTmp,sizeof(g_DipVal) + 1,SET_DIP_MOD);	
//	
//	DelayX10ms(5);
//
//	memcpy(BufTmp,(uint8 *)sPrsLine,sizeof(stcPrsLine));
//	
//	SentDatToDip1(BufTmp,sizeof(stcPrsLine),SET_PRS_LIN);		
//}
//
//
////------------------------------------------------------------------------
//// ��    �ƣ�   void    SetPrs2Line(stcPrsLine * sPrsLine)	
//// ��    �ܣ�   ��ȡ����ָ��͵�����װ��
//// ��ڲ�����	��
//// ���ڲ�����	��
////------------------------------------------------------------------------
//void    SentOutSetPrs(void)
//{
//	uint8	BufTmp[50] = {0};
//
//	BufTmp[0] = 0;
//
//	memcpy(&BufTmp[1],(uint8 *)&g_DipDisVal,sizeof(g_DipVal));	
//
//	SendBroadInfo(BufTmp,sizeof(g_DipVal) + 1,OUT_SET_PRS);
//}
//
//
////------------------------------------------------------------------------
//// ��    �ƣ�   void    SetPrs2Line(stcPrsLine * sPrsLine)	
//// ��    �ܣ�   ��ȡ����ָ��͵�����װ��
//// ��ڲ�����	��
//// ���ڲ�����	��
////------------------------------------------------------------------------
//void    SentPrs2Line(stcPrsLine * sPrsLine)
//{
//	uint8	BufTmp[50] = {0};
//
//	BufTmp[0] = 0;
//
//	memcpy(&BufTmp[1],(uint8 *)&g_DipDisVal,sizeof(g_DipVal));	
//
//	SentDatToDip2(BufTmp,sizeof(g_DipVal) + 1,SET_DIP_MOD);	
//	
//	DelayX10ms(5);
//	
//	memcpy(BufTmp,(uint8 *)sPrsLine,sizeof(stcPrsLine));
//	
//	SentDatToDip2(BufTmp,sizeof(stcPrsLine),SET_PRS_LIN);		
//}
//
//
#define		DIP_REC_FRAM_LEN		15									//����װ�÷��ص�����֡��
#define		INF_START_POS			4
int16		l_Dip1Prs = 0;							
int16		l_Dip2Prs = 0;
int8		l_Dip1Tmp = 0;
int8		l_Dip2Tmp = 0;
uint8		l_Dip1ErrCod = 0;
uint8		l_Dip2ErrCod = 0;





unsigned short 	l_dip1den;
unsigned short 	l_dip2den;

uint8	GetMyDip1Tmp(void)	  		//�ͳ�1�¶�
{
	return	l_Dip1Tmp;
}


uint8	GetMyDip2Tmp(void)			//�ͳ�2�¶�
{
	return	l_Dip2Tmp;
}
		
uint8  GetMyDip1Err(void)
{
	return	l_Dip1ErrCod;
}
		
uint8  GetMyDip2Err(void)
{
	return	l_Dip2ErrCod;
}

		
uint16  GetMyDip1Den(void)
{
	return	l_dip1den;
}

uint16  GetMyDip2Den(void)
{
	return	l_dip2den;
}		

//
uint8		l_Dip1DataErrFlg = NO_ERROR;
uint8		l_Dip2DataErrFlg = NO_ERROR;
////----------------------------------------------------------------------------
//// ��    �ƣ�   uint8  GetDip1Data(uint8	*Buf,uint32	RecBufLen)
//// ��    �ܣ�   ȡ�ͳ�1����
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
uint8  GetDip1Data(uint8	*Buf,uint32	RecBufLen)
{
    uint16			CrcCheck;
    uint16			i;
    uint8			StartCode,TargetAddr,SourceAddr,DataLen;
    static			uint32	ErrTimes = 0;
    static			uint32	Times = 0;
	        
	StartCode 	= COM_START_CODE;
	TargetAddr 	= HOST_ADDR;
	SourceAddr 	= DIP1_ADDR;
	DataLen		= DIP_REC_FRAM_LEN - INF_START_POS - 2;
	
	Times++;

	if(RecBufLen >= DIP_REC_FRAM_LEN)
    {
	    for(i = 0; i <= (RecBufLen - DIP_REC_FRAM_LEN);i++)
	    {  	
			if(	(Buf[i] == StartCode )		&&		
				(Buf[i + 1] == TargetAddr) 	&& 
				(Buf[i + 2] == SourceAddr) 	&& 
				(Buf[i + 3] == DataLen)  )
			{					
				memcpy((uint8 *)&CrcCheck,&Buf[i+DIP_REC_FRAM_LEN - 2],sizeof(CrcCheck));
				
				if(CrcCheck == GetCrc16Check(&Buf[i],DIP_REC_FRAM_LEN - 2))
				{
					memcpy((uint8 *)&l_Dip1Prs,&Buf[i+INF_START_POS],sizeof(l_Dip1Prs));
					memcpy((uint8 *)&l_Dip1Tmp,&Buf[i+INF_START_POS+sizeof(l_Dip1Prs)],
									sizeof(l_Dip1Tmp));
					memcpy((uint8 *)&l_Dip1ErrCod,
							&Buf[i+INF_START_POS+sizeof(l_Dip1Prs)+sizeof(l_Dip1Tmp)],sizeof(l_Dip1ErrCod));
					
					l_Dip1DataErrFlg = NO_ERROR;
					
					Times = 0;
					ErrTimes = 0;						
					return 1;
				}
			}
	    }
	    
	    if(Times > 5)
	    {
	    	l_Dip1Prs = 0;
	    }
    }    
	
	ErrTimes++;
	
	if(ErrTimes > 10)
	{
		l_Dip1DataErrFlg = ERROR;
	}
	
    return	0;												//����ʧ��
}

////----------------------------------------------------------------------------
//// ��    �ƣ�   uint8  GetDip2Data(uint8	*Buf,uint32	RecBufLen)
//// ��    �ܣ�   ȡ�ͳ�2����
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
uint8  GetDip2Data(uint8	*Buf,uint32	RecBufLen)
{
    uint16		CrcCheck;
    uint16		i;
    uint8		StartCode,TargetAddr,SourceAddr,DataLen;
    static		uint32	ErrTimes = 0;
    static	uint32	Times = 0;
    
	StartCode 	= COM_START_CODE;
	TargetAddr 	= HOST_ADDR;
	SourceAddr 	= DIP2_ADDR;
	DataLen		= DIP_REC_FRAM_LEN - INF_START_POS - 2;
	
	Times++;

    if(RecBufLen >= DIP_REC_FRAM_LEN)
    {    
	    for(i = 0; i <= (RecBufLen - DIP_REC_FRAM_LEN);i++)
	    {
			if(	(Buf[i] == StartCode )		&&		
				(Buf[i + 1] == TargetAddr) 	&& 
				(Buf[i + 2] == SourceAddr) 	&& 
				(Buf[i + 3] == DataLen)  )
			{									
				memcpy((uint8 *)&CrcCheck,&Buf[i+DIP_REC_FRAM_LEN - 2],sizeof(CrcCheck));
				
				if(CrcCheck == GetCrc16Check(&Buf[i],DIP_REC_FRAM_LEN - 2))
				{
					memcpy((uint8 *)&l_Dip2Prs,&Buf[i+INF_START_POS],sizeof(l_Dip2Prs));
					memcpy((uint8 *)&l_Dip2Tmp,&Buf[i+INF_START_POS + sizeof(l_Dip2Prs)],
									sizeof(l_Dip2Tmp));
					memcpy((uint8 *)&l_Dip2ErrCod,
					&Buf[i+INF_START_POS + sizeof(l_Dip2Prs)+sizeof(l_Dip2Tmp)],sizeof(l_Dip2ErrCod));
					
					l_Dip2DataErrFlg = NO_ERROR;
					
					Times = 0;
					ErrTimes = 0;						
					return 1;
				}
			}
	    }
	    
	    if(Times > 5)
	    {
	    	l_Dip2Prs = 0;
	    }	    
    }    
    
	ErrTimes++;
	
	if(ErrTimes > 10)
	{
		l_Dip2DataErrFlg = ERROR;
	}

    return	0;												//����ʧ��
}

////----------------------------------------------------------------------------
//// ��    �ƣ�   uint8  Dip2DataErrFlg(void)
//// ��    �ܣ�   ȡ���ͳ�2�����Ƿ���ȷ��ʶ
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
uint8  GetDip2DataErrFlg(void)
{
	return	l_Dip2DataErrFlg;
}
//
////----------------------------------------------------------------------------
//// ��    �ƣ�   uint8  Dip2DataErrFlg(void)
//// ��    �ܣ�   ����TAX2�󲿷֡�
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
//uint8  GetDip2ErrCod(void)
//{
//	return	l_Dip2ErrCod;
//}
//
////----------------------------------------------------------------------------
//// ��    �ƣ�   uint8  Dip2DataErrFlg(void)
//// ��    �ܣ�   ����TAX2�󲿷֡�
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
//uint8  GetDip1ErrCod(void)
//{
//	return	l_Dip1ErrCod;
//}
////----------------------------------------------------------------------------
//// ��    �ƣ�   uint8  Dip1DataErrFlg(void)
//// ��    �ܣ�   ȡ�ͳ�1ͨ��������ȷ��ʶ��
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
uint8  GetDip1DataErrFlg(void)
{
	return	l_Dip1DataErrFlg;
}


////----------------------------------------------------------------------------
//// ��    �ƣ�   uint8  GetDipData(void)
//// ��    �ܣ�   ȡ��������
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
uint8  GetCOM0Data(void)
{
	uint8			Buf[64];									
	static	uint32			Time = 0;
	static	uint32			Times = 0;
	uint32					RecBufLen;		
	static	uint32			ErrTimes = 0;	
	
	if(GetSysTime() - Time > 150 )						
	{
		if(Times++)
		{
			RecBufLen = ReadCOM0(Buf,sizeof(Buf));
 
			if( RecBufLen )
			{
				l_DipComErrFlg = NO_ERROR;
				////printfcom0("\r\n l_DipComErrFlg = NO_ERROR;;");

				if(!GetDip1Data(Buf,RecBufLen))						
				{
//					PrintfDebug("\r\n!GetDip1Data(Buf,RecBufLen)");
				}	
//				
				if(!GetDip2Data(Buf,RecBufLen))							
				{
//					PrintfDebug("\r\n!GetDip2Data(Buf,RecBufLen)");
				}	
//				
//				if(!GetPowerVal(Buf,RecBufLen))	
				{
//					PrintfDebug("\r\n!GetPowerVal(Buf,RecBufLen)");
				}	
//				
//				ErrTimes = 0;
		    }
		    else
		    {
				ErrTimes++;
				
				if(ErrTimes > 2)
				{
					l_DipComErrFlg = ERROR;		
				}
				
				////printfcom0("\r\n l_DipComErrFlg = ERROR;");
		    }
	    }
	    
	    Time = GetSysTime();
    }
    
    return	0;
}
//
////----------------------------------------------------------------------------
//// ��    �ƣ�   uint8  DipComErrFlg(void)
//// ��    �ܣ�   ȡ����װ��1ѹǿ
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
uint8  GetDipComErrFlg(void)
{
	return	l_DipComErrFlg;
}
	    
////----------------------------------------------------------------------------
//// ��    �ƣ�   uint16  GetDip1Prs(void)
//// ��    �ܣ�   ȡ����װ��1ѹǿ
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
int16  GetDip1Prs(void)
{
	return	l_Dip1Prs;
}

////----------------------------------------------------------------------------
//// ��    �ƣ�   uint16  GetDip1Prs(void)
//// ��    �ܣ�   ȡ����װ��1ѹǿ
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
int16  GetDip1Hig(void)
{
	return	l_Dip1Prs;
}
//
////----------------------------------------------------------------------------
//// ��    �ƣ�   uint16  GetDip2Prs(void)
//// ��    �ܣ�   ȡ����װ��2ѹǿ
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
int16  GetDip2Prs(void)
{
	return	l_Dip2Prs;
}

int16  GetDip2Hig(void)
{
	return	l_Dip2Prs;
}
//
////----------------------------------------------------------------------------
//// ��    �ƣ�   uint16  GetDipTmp(void)
//// ��    �ܣ�   ȡ����װ��1ѹǿ
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
int8	GetDipTmp(void)
{
	if(l_Dip1Tmp && l_Dip2Tmp)
	{
		return	(l_Dip1Tmp + l_Dip2Tmp) / 2;
	}
	else if(l_Dip1Tmp)
	{
		return l_Dip1Tmp;
	}
	else
	{
		return l_Dip2Tmp;
	}

}

////----------------------------------------------------------------------------
//// ��    �ƣ�   uint16  JudgeDip1Prs(void)
//// ��    �ܣ�   ȡ����װ��1ѹǿֵ�Ƿ��ޱ�ʶ
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
uint8	JudgeDip1Prs(void)
{
	static 	uint32	Time 	=	0;	//ʱ��
	static	uint32	Times	=	0;	//����
	static	uint8	Flg  	=   NO_ERROR;

	int16	DipPrs;
	
	if(GetSysTime() - Time > 100)
	{
		Time = GetSysTime();
		
		DipPrs = GetDip1Prs();
		
		if((DipPrs > DIP_PRS_MAX_VAL) || (DipPrs < - (DIP_PRS_MAX_VAL/10)))
		{
		
			Times++;
			if(Times > 30)
			{
				Flg = ERROR;
			}
		}
		else
		{
			Times = 0;
			Flg = NO_ERROR;
		}
	}
	
	return	Flg;
}
//
//
////----------------------------------------------------------------------------
//// ��    �ƣ�   uint16  GetDipTmp(void)
//// ��    �ܣ�   ȡ����װ��2ѹǿֵ�Ƿ���
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
uint8	JudgeDip2Prs(void)
{
	static 	uint32	Time 	=	0;	//ʱ��
	static	uint32	Times	=	0;	//����
	static	uint8	Flg  	=  NO_ERROR;
	
	int16	DipPrs;
	
	if(GetSysTime() - Time > 100)
	{
		Time = GetSysTime();

		DipPrs = GetDip2Prs();
		
		if(DipPrs > DIP_PRS_MAX_VAL || DipPrs < (-DIP_PRS_MAX_VAL/10))
		{
		
			Times++;
			if(Times > 30)
			{
				Flg = ERROR;
			}
		}
		else
		{
			Times = 0;
			Flg = NO_ERROR;
		}
	}

	return	Flg;
}
//
//
//extern	uint8	JudgeDipPrsDif(void);


//----------------------------------------------------------------------------
// ��    �ƣ�   uint16  JudgeDipPrsDif(void)
// ��    �ܣ�   ȡ����װ��1ѹǿֵ�Ƿ��ޱ�ʶ
// ��ڲ�����   ��
// ���ڲ�����   ��
//----------------------------------------------------------------------------
uint8	JudgeDipPrsDif(void)
{
	static 	uint32	Time 	=	0;	//ʱ��
	static	uint32	Times	=	0;	//����
	uint8	DipErrorType = RIGHT_DATA;
	
	int16	Dip1Prs;
	int16	Dip2Prs;
	int16	DipPrs;

	if(GetSysTime() - Time > 100)
	{	
		Time = GetSysTime();
		
		if(GetDipComErrFlg() == NO_ERROR  )
		{
			if( GetDip2DataErrFlg() == NO_ERROR && JudgeDip2Prs() == NO_ERROR 
			&& GetDip1DataErrFlg() == NO_ERROR && JudgeDip1Prs() == NO_ERROR)
			{		
				Dip1Prs = GetDip1Prs();
				Dip2Prs = GetDip2Prs();
				DipPrs  = Dip1Prs - Dip2Prs;
				
				if(fabs(Dip1Prs) > 1000 || fabs(Dip2Prs) >1000)
				{
					if((fabs(DipPrs) > 2000))
					{
						Times++;
						if(Times > 120)
						{
							DipErrorType = DIP_PRE_DIF;
							return	DipErrorType;
						}
					}
					else
					{
						Times = 0;
					}
				}
				else
				{
					if((fabs(DipPrs) > 1500))
					{
						Times++;
						if(Times > 60)
						{
							DipErrorType = DIP_PRE_DIF;
							return	DipErrorType;
						}
					}
					else
					{
						Times = 0;
					}			
				}
			}
		}	
		
		DipErrorType = RIGHT_DATA;
	}
	
	return	DipErrorType;
}


#define		DIP_PRE_DIF				84
#define		DIP_NO_COM_ERROR		83
#define		DIP1_DATA_ERROR			85
#define		DIP1_COM_ERROR			81
#define		DIP2_DATA_ERROR			75
#define		DIP2_COM_ERROR			71
#define		DIP1_LIMIT_ERROR		82
#define		DIP2_LIMIT_ERROR		72




uint8  JudgeDip1Error(void) 
{
	uint8	DipErrorType = RIGHT_DATA;
	
	DipErrorType = RIGHT_DATA;
		
	if(GetDipComErrFlg() == ERROR)
	{
		return	DipErrorType = DIP_NO_COM_ERROR;
	}

	if((GetDip1ComErrFlg()==ERROR))
	{
		return	DipErrorType = DIP1_COM_ERROR;
	}

	if(GetDip1DataErrFlg() == ERROR)
	{
		return	DipErrorType = DIP1_DATA_ERROR;
	}

	if(JudgeDip1Prs() == ERROR)
	{
		return	DipErrorType = DIP1_LIMIT_ERROR;
	}

	if(JudgeDipPrsDif() == ERROR)
	{
		 return	DipErrorType = DIP_PRE_DIF;
	}
//		else
//		{
//			//if(JudgeDipPrsDif() == ERROR)						//ѹǿ���
//			//{
//			//	DipErrorType = DIP_PRE_DIF;
//			//}
//			//else
//			Time = GetSysTime();
//
//			{
//				Times++;
//
//			}
//		
//			////printfcom0("\r\n DipErrorType = DIP_NO_COM_ERROR;");
//
//		}
//	}
	
  	
	return	DipErrorType;
}
//
//extern	uint8	JudgeDip2Prs(void);
//
////-------------------------------------------------------------------------------------------------
////��������:             uint8  JudgeDipError(void) 
////��������:             �Բ���װ�ù��Ͻ����ж�
////��ڲ���:             ��
////���ڲ���:             ���ز���װ�ù��ϴ���
////--------------------------------------------------------------------------------------------------
uint8  JudgeDip2Error(void) 
{
	uint8			DipErrorType = RIGHT_DATA;
//	static	uint32	Times 	= 0;
	
	DipErrorType = RIGHT_DATA;
		
	if(GetDipComErrFlg() == ERROR)
	{
//		return	DipErrorType = DIP_NO_COM_ERROR;
		return DipErrorType;
	}

	if((GetDip2ComErrFlg()==ERROR))
	{
		return	DipErrorType = DIP2_COM_ERROR;
	}

	if(GetDip2DataErrFlg() == ERROR)
	{
		return	DipErrorType = DIP2_DATA_ERROR;
	}

	if(JudgeDip2Prs() == ERROR)
	{
		return	DipErrorType = DIP2_LIMIT_ERROR;
	}
//	
//	if(JudgeDipPrsDif() == ERROR)
//	{
//		 return	DipErrorType = DIP_PRE_DIF;
//	}

	return	DipErrorType;
}

////-------------------------------------------------------------------------------------------------
////��������:             void  COM1Task(void) 
////��������:             ����װ������
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
void  COM0Task(void) 
{
	SendReadCOM0DataCod();				//���Ͳ���װ�òɼ����ݵ�����
}
//
//
//
//#ifdef	TEST_OPEN
////----------------------------------------------------------------------------
//// ��    �ƣ�   uint8  RecTAX2Bef(void)
//// ��    �ܣ�   ����TAX2ǰ���֡�
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
//uint8  RecHostToDip1(uint8 * Buf,uint32 * DipVal,uint32	RecBufLen)
//{
//    uint16		i;
//	uint8	SourceAddr,TargetAddr,DatTyp,StartCode,FramLen;
//	static		uint32	ErrTime = 0;
//
//	DatTyp		=	GET_DIP_PRS;
//	StartCode 	= 	COM_START_CODE;
//	TargetAddr  = 	DIP1_ADDR;	
//	SourceAddr 	=	HOST_ADDR;
//
//	for(i = 0; i <= (RecBufLen  - 6) && RecBufLen > 6;i++)
//    {
////		SysFastHoldTast();
//		
//		if(Buf[i] == StartCode && Buf[i + 1] == TargetAddr 
//			&& Buf[i + 2] == SourceAddr && Buf[i + 4] == GET_DIP_PRS)	//�ж�ͨѶ��ʽ 
//		{
//			memcpy((uint8 *)DipVal,&Buf[i + 6],sizeof(uint32));
//
//			ErrTime = 0;
//			//printfcom0("\r\n ѹǿ1�ɹ���");
//			return 	1;													//���ճɹ����˳�
//		}
//	}
//
//	ErrTime++;
//	
//	if(ErrTime > 5)
//	{
//		*DipVal = 0;
//	}
//		
//	//printfcom0("\r\n ѹǿ1 i  = %d;RecBufLen = %d ",i,RecBufLen);
//
//    return	0;															//����ʧ��
//}
//
////----------------------------------------------------------------------------
//// ��    �ƣ�   uint8  RecTAX2Bef(void)
//// ��    �ܣ�   ����TAX2ǰ���֡�
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
//uint8  RecHostToDip2(uint8 * Buf,uint32 * DipVal,uint32	RecBufLen)
//{
//    uint16		i;
//	uint8		SourceAddr,TargetAddr,DatTyp,StartCode,FramLen;
//	static		uint32	ErrTime = 0;
//	
//	DatTyp		=	GET_DIP_PRS;
//	StartCode 	= 	COM_START_CODE;
//	TargetAddr  = 	DIP2_ADDR;	
//	SourceAddr 	=	HOST_ADDR;
//
//	for(i = 0; i <= (RecBufLen  - 6) && RecBufLen >6 ;i++)
//    {
////    	SysFastHoldTast();
//    	
//		if(Buf[i] == StartCode && Buf[i + 1] == TargetAddr 
//			&& Buf[i + 2] == SourceAddr && Buf[i + 4] == GET_DIP_PRS)	//�ж�ͨѶ��ʽ 
//		{
//			memcpy((uint8 *)DipVal,&Buf[i + 6],sizeof(uint32));
//			
//			ErrTime = 0;
//			//printfcom0("\r\n ѹǿ2�ɹ���");
//			return 	1;								//���ճɹ����˳�
//		}
//	}
//
//	ErrTime++;
//	
//	if(ErrTime > 5)
//	{
//		*DipVal = 0;
//	}
//	
//	//printfcom0("\r\n ѹǿ2 i  = %d;RecBufLen = %d ",i,RecBufLen);
//	
//    return	0;												//����ʧ��
//}
//
//
////----------------------------------------------------------------------------
//// ��    �ƣ�   uint8  RecTAX2Bef(void)
//// ��    �ܣ�   ����TAX2ǰ���֡�
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
//void  SendDip1ToHost(int16 Prs)
//{
//    uint16		i = 0;
//    static	uint8	BufTmp[DIP_REC_FRAM_LEN] = {0};
//    uint16			CrcCheck;
//    uint8			StartCode,TargetAddr,SourceAddr,DataLen;
//    
//	StartCode 	= COM_START_CODE;
//	TargetAddr 	= HOST_ADDR;
//	SourceAddr 	= DIP1_ADDR;
//	DataLen		= DIP_REC_FRAM_LEN - INF_START_POS - 2;
//     
//	BufTmp[i++] = StartCode;
//	BufTmp[i++] = TargetAddr;
//	BufTmp[i++] = SourceAddr;
//	BufTmp[i++] = DataLen;
//		
//	memcpy(&BufTmp[INF_START_POS],(uint8 *)&Prs,sizeof(int16));
//	BufTmp[INF_START_POS + sizeof(int16)] 				= 0;
//	BufTmp[INF_START_POS + sizeof(int16) + sizeof(uint8)] 	= 0;
//	BufTmp[INF_START_POS + sizeof(int16) + sizeof(uint8) + sizeof(uint8)] 	= 0xaa;
//
//	CrcCheck = GetCrc16Check(BufTmp,DIP_REC_FRAM_LEN - 2);
//	memcpy(&BufTmp[DIP_REC_FRAM_LEN - 2],(uint8 *)&CrcCheck,sizeof(CrcCheck));
//	
//	SendCOM0(BufTmp,DIP_REC_FRAM_LEN);
//}
//
////----------------------------------------------------------------------------
//// ��    �ƣ�   uint8  RecTAX2Bef(void)
//// ��    �ܣ�   ����TAX2ǰ���֡�
//// ��ڲ�����   ��
//// ���ڲ�����   ��
////----------------------------------------------------------------------------
//void  SendDip2ToHost(int16 Prs)
//{
//    uint16			i = 0;
//    static	uint8	BufTmp[DIP_REC_FRAM_LEN] = {0};
//    uint16			CrcCheck;
//    uint8			StartCode,TargetAddr,SourceAddr,DataLen;
//    
//	StartCode 	= COM_START_CODE;
//	TargetAddr 	= HOST_ADDR;
//	SourceAddr 	= DIP2_ADDR;
//	DataLen		= DIP_REC_FRAM_LEN - INF_START_POS - 2;
//     
//	BufTmp[i++] = StartCode;
//	BufTmp[i++] = TargetAddr;
//	BufTmp[i++] = SourceAddr;
//	BufTmp[i++] = DataLen;
//	
//	memcpy(&BufTmp[INF_START_POS],(uint8 *)&Prs,sizeof(int16));
//	BufTmp[INF_START_POS+sizeof(int16)] 				= 0;
//	BufTmp[INF_START_POS + sizeof(int16) + sizeof(uint8)] 	= 0;
//	BufTmp[INF_START_POS + sizeof(int16) + sizeof(uint8) + sizeof(uint8)] 	= 0xaa;
//
//	CrcCheck = GetCrc16Check(BufTmp,DIP_REC_FRAM_LEN - 2);
//	memcpy(&BufTmp[DIP_REC_FRAM_LEN - 2],(uint8 *)&CrcCheck,sizeof(CrcCheck));
//	
//	SendCOM0(BufTmp,DIP_REC_FRAM_LEN);
//}
//
//
////------------------------------------------------------------------------
//// ��    �ƣ�   void SentDatToDip1(uint8 *Buf,uint32	BufLen)
//// ��    �ܣ�   �����ݷ��͵��ͳ�1 
//// ��ڲ�����	Buf:���ݻ����� BufLen:���ݻ��������ݳ��� ��Typ:��������
//// ���ڲ�����	��
////------------------------------------------------------------------------
//uint32 SimulateHostAndDip(int16 Prs1,int16 Prs2)		
//{
//	static	uint8	Buf[50] = {0};
//	uint32			DipVal;
//	uint32			RecLen;				
//	uint32			RecStateLen;
//	static		uint32	Times;				
//	
//	RecLen 		= 	ReadCOM1(Buf,sizeof(Buf));		
//
//	////printfcom0("\r\n RecLen = %d",RecLen);
//
//	if(Times++%2==0)
//	{
//		if( RecHostToDip1(Buf,(uint32 *)&DipVal,RecLen ))
//		{
//			SendDip1ToHost(Prs1);
//			////printfcom0("\r\n DipVal = %d",DipVal);
//			return	DipVal;
//		}	
//	}
//	else
//	{
//		if( RecHostToDip2(Buf,(uint32 *)&DipVal,RecLen) )
//		{
//			SendDip2ToHost(Prs2);	
//			////printfcom0("\r\n DipVal = %d",DipVal);
//			
//			return	DipVal;
//		}
//	}
//	
//}
//
//#define	USB_INT_SUCCESS		0x14			/* USB������ߴ�������ɹ� */
//
//
//#endif
// 
////-------------------------------------------------------------------------------------------------
////��������:             void  SimulateTax(void)
////��������:             TAX2ģ����
////��ڲ���:             ��
////���ڲ���:             ��
////˵��:                 
////--------------------------------------------------------------------------------------------------
//void  SimulateDip(void)
//{
//    ////printfcom0("\r\n\r\nTax2Task(void)");
//#ifdef	TEST_OPEN
//	uint32	DipVal;
//	int16	Prs1;
//	int16	Prs2;	
//	static	uint32	Time;
//	
//	//OpenCOM1(9600);							//��ʼ������1  ���ڽ����в��ܳ�ʼ��
//
//    //while(1)
//    {
//
//    	if(GetSysTime() - Time > 20)				//100ms
//		{	
//	#ifdef	HARD_VER_111122	
///**/
//			if( CH376DiskConnect() == USB_INT_SUCCESS )	//����USB,U�̲���
//			{
//	   			UsbSetSimPre();							//��U������TAX��Ϣ					
//	   		}    	
//	
//	#endif   	
//			////printfcom0("\r\n GetSysTime() %d- Time",GetSysTime());
//				
//			Prs1 = GetSimPrs1();					//ȡ������ѹǿ1
//			Prs2 = GetSimPrs2();					//ȡ������ѹǿ2
//			
//			DipVal = SimulateHostAndDip(Prs1,Prs2);	//��TAX��ģ��������
//
//			if( DipVal )								//��ʾ����
//			{
//				DisplaySet(50,1,"%d",DipVal%10000);
//			}
//			else
//			{
//				DisplaySet(20,1,"%d.%d.",Prs1%10000,Prs2%10000);
//			}
//			
//			Time = GetSysTime();
//		}
//	}
//	
//#endif
//}
