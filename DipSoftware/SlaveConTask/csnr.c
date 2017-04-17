#include <includes.h>


#define         FRAM_HERD0     		0x10         	//����ͷ
#define         FRAM_HERD1     		0x28       		//����ͷ				
#define     	HOST_ID      		10				//��λ����ַ	  		   
#define   		DEVICE_ID0      	15				//������ַ0	
#define   		DEVICE_ID1      	15				//������ַ1	
	   
#define			RS485_CHK_SUM		0x02			//b0001��CRC��ʽ��b0010���ۼӺͷ�ʽ�� b0011;�ۼӺͶ����Ʋ��뷽ʽ 
#define			RS485_CHK_CRC		0x01			//b0001��CRC��ʽ��b0010���ۼӺͷ�ʽ�� b0011;�ۼӺͶ����Ʋ��뷽ʽ 
#define			RS485_CHK_RESUM		0x03			//b0001��CRC��ʽ��b0010���ۼӺͷ�ʽ�� b0011;�ۼӺͶ����Ʋ��뷽ʽ 

#define         FRAM_END0     		0x10         	//����β
#define         FRAM_END1     		0x2C       		//����β	

////////////////////////////////////mdk 0

 

////////////////////////////////////////////

unsigned char   l_recslaveaddr = 0;

//----------------------------------------------------------------------------
// ��    �ƣ�   
// ��    �ܣ�   ��
// ��ڲ�����   ��
// ���ڲ�����   ��
//----------------------------------------------------------------------------
unsigned char  CSNR_GetData(unsigned char	*RecBuf,unsigned char RecLen,unsigned char	*DataBuf,unsigned char	*InfoLen)
{
    unsigned short		i,j,k;
    unsigned char			SumCheck8;
    unsigned char			Tmp;
    unsigned short		RecCRC16,Check16;
	
		unsigned char 		SourceAddr;	
		unsigned char			DataLen;

	
//	*InfoLen  = 0��
	
	if(RecLen < 10)  //(8+4)
			return 0;
  
	for(j = 0;j < RecLen ;j++ )														//ȥ�ظ�ͨѶ���ֽ�
	{
		if(	 	RecBuf[j] 	== FRAM_HERD0
			&& 	RecBuf[j+1] == FRAM_HERD0
		   )
		{
			for(k = j;k < RecLen; k++)
			{
				Tmp	 = RecBuf[k+1];
				
				RecBuf[k] = Tmp;
			}
		}
	}
	
    for(i = 0; i < RecLen - (8+4);i++)												//ѭ������
    {
		if(		((RecBuf[i+0]) == FRAM_HERD0) 
			&& 	((RecBuf[i+1]) == FRAM_HERD1)		
		  )																		//��ͷ
		{
			DataLen = RecBuf[i+6];
			//PrintfCOM0(("\r\n DataLen %d,%x,%x",DataLen,RecBuf[i+10+DataLen],RecBuf[i+11+DataLen]);
			if(		
					//	(RecBuf[i+2] != DeviceID) 				||
					  //	(RecBuf[i+3] != HOST_ID) 				||
						 (i+10+DataLen)  > RecLen							||
				 		(RecBuf[i+10+DataLen] 	!= FRAM_END0)	||
				 	 	(RecBuf[i+11+DataLen] 	!= FRAM_END1)
			 )
			 {	
//			 	i = i + 10 + DataLen;											//��ַ���Ի�֡β����������֡
			 	continue;
			 }
			
			 
			SumCheck8 = GetCheckSumNR((unsigned char *)&RecBuf[i+2],5);		   				//������У��
			
			if(		SumCheck8 != 	RecBuf[i+7] )
			{	
				continue;
			}
			 
			SourceAddr = RecBuf[i+2];	
			l_recslaveaddr = RecBuf[i+3];	
			//PrintfCOM0(("\r\n �� %x",RecBuf[i+4]);				
			DataLen = RecBuf[i+6];
			*InfoLen = DataLen; 
			
			 
			RecCRC16 = ((unsigned short)RecBuf[i+8+DataLen]) *256 + RecBuf[i+9+DataLen];	//У��	

			switch(RecBuf[i+5]>>4)													//У����㷨�ж�
			{
					case	RS485_CHK_SUM:
									//Check16 = GetCheckSum16(&RecBuf[i+2],6+DataLen);
									////PrintfCOM0(("\r\n 16λУ��ͣ�");
									break;
					case	RS485_CHK_CRC:
									Check16 = GetCrc16Check(&RecBuf[i+2],6+DataLen);
									////PrintfCOM0(("\r\n CRCУ�飡");
									break;
					case	RS485_CHK_RESUM:
									break;
			}
			
			if(	RecCRC16  ==	Check16 )
			{
				 memcpy(DataBuf,&RecBuf[i+8],DataLen);				//���ݿ���
				 
				 //return	1;				//SourceAddr
				 return		SourceAddr;
			}
		}
	}
		
		DataLen = 0;
    return	0;
}


void	DataSend_CSNR(unsigned char SourceAddr,unsigned char DistAddr,unsigned char	*DataBuf,unsigned int	DataLen)
{
	unsigned char	SndBuf[256] = {0};
	unsigned char	SndBufTmp[256] = {0};
	unsigned char	SumCheck8;
	unsigned short	Crc16;
	unsigned short	AddHeadNum;
	unsigned short	i;
	unsigned char	ByteStation;
	static	unsigned char FramNum =0;						//���
	
	ByteStation = 0;
	SndBuf[ByteStation++] = FRAM_HERD0;
	SndBuf[ByteStation++] = FRAM_HERD1;
	SndBuf[ByteStation++] = SourceAddr;	 
	SndBuf[ByteStation++] = DistAddr;				//��ַ
	SndBuf[ByteStation++] = FramNum++;	
	SndBuf[ByteStation++] = RS485_CHK_CRC<<4;	
	SndBuf[ByteStation++] = DataLen;
	
//	SumCheck8 = GetCheckSum(&SndBuf[2],5);		   	//������У��
	SumCheck8 = GetCheckSumNR(&SndBuf[2],5);		   	//������У��

	SndBuf[ByteStation++] = SumCheck8;

	memcpy(&SndBuf[8],DataBuf,DataLen);

	Crc16 = GetCrc16Check(&SndBuf[2],6+DataLen);

	//memcpy(&SndBuf[2+6+DataLen],(unsigned char *)&Crc16,sizeof(Crc16));
	
	SndBuf[2+6+DataLen+1] = Crc16;
	SndBuf[2+6+DataLen]   = Crc16>>8;

	SndBufTmp[0] = SndBuf[0];						//׼�����ݷ���
	SndBufTmp[1] = SndBuf[1];
	
	AddHeadNum = 0;
	for(i = 2; i< 2+6+DataLen + 2;i++ )				//���ݣ�����λ FRAM_HERD0
	{
		SndBufTmp[i+AddHeadNum] = SndBuf[i];
		
		if(SndBuf[i] == FRAM_HERD0)
		{
			SndBufTmp[i+AddHeadNum+1] = FRAM_HERD0;
			AddHeadNum++;
		}
	}

	SndBufTmp[2+6+DataLen + 2 +AddHeadNum] = FRAM_END0;
	SndBufTmp[2+6+DataLen + 2 +AddHeadNum+1] = FRAM_END1;      
	
	//��ַ�ж�
	if((DistAddr & 0xA0) == 0xA0)
	{
		SendCOM1(SndBufTmp, 2+6+DataLen + 2 +AddHeadNum +2) ;
	}
	else if((DistAddr & 0xC0) == 0xC0)
	{
        SendCOM2(SndBufTmp, 2+6+DataLen + 2 +AddHeadNum +2) ; 
        
//		if(GetGprsCommNum() == 0  ||  DistAddr == 0xca)
//		{	
//			if(	GetPrintfFlg()== 0)
//			{
//				SendCOM2(SndBufTmp, 2+6+DataLen + 2 +AddHeadNum +2) ; 
//			}
//			SendCOM3(SndBufTmp, 2+6+DataLen + 2 +AddHeadNum +2) ; 
//		}
//		else
//		{
//			if(GetGprsCommNum() == 2)
//			{
//				SendCOM3(SndBufTmp, 2+6+DataLen + 2 +AddHeadNum +2) ; 
//			}
//			else
//			{
//				SendCOM2(SndBufTmp, 2+6+DataLen + 2 +AddHeadNum +2) ; 
//			}
//		}
		
		
//		///
//			if(DistAddr == 0xCA)
//			{
//				SendCOM3(SndBufTmp, 2+6+DataLen + 2 +AddHeadNum +2) ; 
//				SendCOM2(SndBufTmp, 2+6+DataLen + 2 +AddHeadNum +2) ; 
//			}
//			else
//			{
//				//SendCOM3(SndBufTmp, 2+6+DataLen + 2 +AddHeadNum +2) ; 
//				SendCOM2(SndBufTmp, 2+6+DataLen + 2 +AddHeadNum +2) ; 
//			}
	}
//	else
//	{
//		SendCOM1(SndBufTmp, 2+6+DataLen + 2 +AddHeadNum +2) ; 	
//	}
	//SendCOM1(SndBufTmp,2+6+DataLen + 2 + 2 + AddHeadNum);
	//SendCOM0(SndBufTmp,2+6+DataLen + 2 + 2 + AddHeadNum);
}
