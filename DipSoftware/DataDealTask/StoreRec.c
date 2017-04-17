////#include  	"config.h"   
////#include	"string.h"
////#include	"Globe.h"
////#include	"HardDrive.h"
////#include	"CpuDrive.h"
////#include	"FramStore.h"
////#include	"Tax2.h"
////#include	"DipMath.h"
////#include	"SysDeal.h"
////#include	"DieselSpeed.h"
//
#include    <includes.h>
#include    "tmp.h"
//

#define		STORE_REC_TIME	60


uint8	GetStoreTime(void)
{
	stcSysRunPara 	sSysRunPara;

	if(GetSysRunPara((stcSysRunPara * )&sSysRunPara))
	{
		if(sSysRunPara.StoreTime)
		{
			//printfcom0("\r\n sSysRunPara.StoreTime %d",sSysRunPara.StoreTime);
			return	sSysRunPara.StoreTime;
		}	
	}

	//printfcom0("\r\n STORE_REC_TIME %d",sSysRunPara.StoreTime);
	return	STORE_REC_TIME;
}




//
//uint32			l_StoreDivide = 1;
//
///*
//uint32			l_StoreCnt;				//��ˮ��				
//uint8			l_RecTypCod;       		//��¼����          	1   �������ͣ��������ϰ࿨���°࿨�����ݼ�¼��
//uint8			l_DriverUnitNum[2];  	//˾����λ���      	2   //����Ψһȷ��˾��
//uint32			l_MstLocoPower;        	//����������          	2   ����豸����
//uint32			l_SlvLocoPower;        	//�ӻ�������          	2   ����豸����
//uint16 			l_MstDip;           	//��������          	2   ���ͳ�����(���ӻ�����ʱΪ��������,����Ϊ����������)
//uint16 			l_SlvDip;           	//�ӻ�����          	2   ���ͳ�����(���ӻ�����ʱΪ�ӻ�����,���������ֵΪ��)
//uint16			l_MstDip1Prs;        	//ѹǿ            		2   �����ͳ�1ѹǿֵ
//uint16			l_MstDip2Prs;        	//ѹǿ            		2   �����ͳ�2ѹǿֵ
//uint16			l_SlvDip1Prs;       	//ѹǿ            		2   �ӻ��ͳ�1ѹǿֵ
//uint16 			l_SlvDip2Prs;       	//ѹǿ            		2   �ӻ��ͳ�2ѹǿֵ
//uint16			l_MstDensity;			//�ܶ�					2	����ȼ���ܶ�
//uint16			l_SlvDensity;			//�ܶ�					2	�ӻ�ȼ���ܶ�
//uint32			l_GpsLongitude;			//����					4	������
//uint32			l_GpsLatitude;			//γ��					4	����γ��
//uint16			l_GpsHeight;			//�߶�					4	����߶�
//uint16			l_MstEngRotSpd;			//�������ͻ�ת��		2	�������ͻ�ת��
//uint16			l_SlvEngRotSpd;			//�ӻ����ͻ�ת��		2	�ӻ����ͻ�ת��
//uint16 			l_JcRealType;			//�����ͺ�				2   �ⲿ���õĻ����ͺ�
//uint16 			l_JcRealNo;				//�������				2   �ⲿ���õĻ������
//uint8			l_ErrorCode;			//���ϴ���				1   0~255
//uint8 			l_DipValChgState;  		//�����仯״̬   		1   �����仯����֣����ͳ�����/��С���仯ƽ�ȡ���΢���������Ҳ���
//uint8			l_MstDipTemp;			//�¶�					1	�����¶�
//uint8			l_OilBoxModel;			//����ģ�ʹ���			1	�ӻ��¶�		
//
//
////-------------------------------------------------------------------------------
////��������:        void  ReadyStoreData(void)
////��������:        ׼���洢�õ�����
////��ڲ���:        ��
////���ڲ���:         
////��������:			
////-------------------------------------------------------------------------------
//void  ReadyStoreData(void)
//{
//	l_StoreCnt 			= g_CurFlshRecNum;
//	l_MstDip1Prs		= GetDip1Prs();
//	l_MstDip2Prs		= GetDip2Prs();	
//	l_MstDipTemp		= GetDipTmp();
//	l_DipValChgState	= GetPrsChgState();
//	l_MstDip			= g_DipVal;
//	l_ErrorCode			= GetStoreErrTypCod();
//	l_RecTypCod			= GetStoreEvtTypCod();
//	l_MstEngRotSpd		= GetDieselSpeed();	
//	l_OilBoxModel		= GetOilBoxCod();	
//}
//*/
//
//stcLogZone		l_sLogZone;
//
////-------------------------------------------------------------------------------------------------
////��������:             void  StoreLog(void) 	
////��������:             ����־�ļ�
////��ڲ���:             ��
////���ڲ���:             ��
////--------------------------------------------------------------------------------------------------
//void  StoreLog(void) 	
//{
//	static	stcFlshRec		sFlshRec;										//Flsh��¼
//	static	stcDeviceInfo	sDeviceInfo;
//	
//	uint16			CrcCheck;		
//	uint16			DriveNum = 0xffff;		
//	
//	ReadCurFlshRec((stcFlshRec *)&sFlshRec);
//	
//	ReadHostInfo((stcDeviceInfo *)&sDeviceInfo);
//	
//	CrcCheck = GetCrc16Check((uint8 *)&sDeviceInfo,sizeof(stcDeviceInfo) - 2);
//
//	if(CrcCheck != sDeviceInfo.CrcCheck)
//	{
//		DriveNum = sDeviceInfo.DeviceNum;
//		
//		////printfcom0("\r\n����������Ϣ���ô����û�����ã�");
//	}
//	
//	ReadLogZone((stcLogZone *)&l_sLogZone);
//	
//	CrcCheck = GetCrc16Check((uint8 *)&l_sLogZone,sizeof(stcLogZone) - 2);
//	
//	if(CrcCheck != l_sLogZone.CrcCheck)
//	{
//		l_sLogZone.Times = 0;
//		
//		//printfcom0("\r\n��־�ļ�����");
//	}
//
//	l_sLogZone.sLog[l_sLogZone.Times].StoreCnt 		= sFlshRec.StoreCnt;
//	l_sLogZone.sLog[l_sLogZone.Times].ErrorCode		= sFlshRec.ErrorCode;
//	l_sLogZone.sLog[l_sLogZone.Times].RecTypCod	 	= sFlshRec.RecTypCod;
//	l_sLogZone.sLog[l_sLogZone.Times].LocoTyp[0]	= sFlshRec.LocoTyp;
//	l_sLogZone.sLog[l_sLogZone.Times].LocoTyp[1]	= sFlshRec.E_LocoTyp;
//	l_sLogZone.sLog[l_sLogZone.Times].LocoNum[0]	= sFlshRec.LocoNum[0];
//	l_sLogZone.sLog[l_sLogZone.Times].LocoNum[1]	= sFlshRec.LocoNum[1];	
//	l_sLogZone.sLog[l_sLogZone.Times].DriveNum		= DriveNum;
//	
//	l_sLogZone.Times++;
//	
//	CrcCheck = GetCrc16Check((uint8 *)&l_sLogZone,sizeof(stcLogZone) - 2);
//	l_sLogZone.CrcCheck = CrcCheck;
//	
//	StoreLogZone((stcLogZone *)&l_sLogZone);
//}
//
////-------------------------------------------------------------------------------
////��������:        uint32  GetRecNumAddr(uint32 FlshRecNum)
////��������:        ȡ��¼��ˮ�ŵ�ַ
////��ڲ���:        ��¼��ˮ��
////���ڲ���:        ��¼��ˮ����FLASH�еĵ�ַ
////��������:			
////-------------------------------------------------------------------------------
uint32  GetRecNumAddr(uint32 FlshRecNum)
{
    //return  (uint32)(FLSH_PROTECT_SIZE + ((FlshRecNum * sizeof(stcFlshRec)) % (FLSH_MAX_SIZE - FLSH_PROTECT_SIZE)));  //�������					
    return  (uint32)(((FlshRecNum * sizeof(stcFlshRec)) % FLSH_MAX_SIZE));  //�������					
}
//
//#define     FREQ_DOWN_STATE     1
//#define     FREQ_WAVE_STATE     2
//#define     FREQ_LAG_WAVE_STATE 3
//#define     FREQ_UP_STATE       4           		//Ƶ�ʱ仯״̬
//#define     FREQ_STOP_STATE     5
////-------------------------------------------------------------------------------
////��������:        uint32  MathStoreDivede()
////��������:        ȡ��¼��ˮ�ŵ�ַ
////��ڲ���:        ��¼��ˮ��
////���ڲ���:        ��¼��ˮ����FLASH�еĵ�ַ
////��������:			
////-------------------------------------------------------------------------------
//void	MathStoreDivide(void)
//{
//	static	uint32	Time = 0 ;
//	static	uint8	LstDipValChgState = FREQ_WAVE_STATE;
//	static	uint32	Timer = 0;
//	uint8	DipValChgState = FREQ_WAVE_STATE;
//	
//	if(GetSysTime() - Timer > 100)
//	{
//		Timer = GetSysTime();
//		
//		DipValChgState = GetPrsChgState();
//		
//		/*
//		if( DipValChgState == FREQ_UP_STATE)
//		{
//			l_StoreDivide = 12;
//			Time = 0;
//		}
//		
//		if((DipValChgState == FREQ_STOP_STATE) && ((LstDipValChgState == FREQ_WAVE_STATE) || (LstDipValChgState == FREQ_LAG_WAVE_STATE)))
//		{
//			l_StoreDivide = 12;
//			Time = 0;
//		}
//
//		if(((DipValChgState == FREQ_WAVE_STATE) || (DipValChgState == FREQ_LAG_WAVE_STATE)) && (LstDipValChgState == FREQ_STOP_STATE))
//		{
//			l_StoreDivide = 12;
//			Time = 0;
//		}			
//		*/
//		if(l_StoreDivide == 12)
//		{
//			Time++;
//			
//			if( Time > 60)
//			{
//				l_StoreDivide = 1;
//			}
//		}
//		
//		LstDipValChgState = DipValChgState;
//	}
//}
//
////-------------------------------------------------------------------------------
////��������:        uint32  GetStoreDivede()
////��������:        ȡ��¼��ˮ�ŵ�ַ
////��ڲ���:        ��¼��ˮ��
////���ڲ���:        ��¼��ˮ����FLASH�еĵ�ַ
////��������:			
////-------------------------------------------------------------------------------
//uint32  GetStoreDivide()
//{
//    return  l_StoreDivide;  //�������					
//}
//    
//uint8	l_FlshStoreErrEvtFlg = RIGHT_DATA;
//#define		FLSH_WRT_ERR_EVT	32
//
//extern	uint8	ReadFlshRec(stcFlshRec * sFlshRec,uint32	FlshRecNum);
//extern	uint8	JudgeLstFlsh(void);
//
//extern	uint16	GetReviseHight(void);
//

#define		START_EVT		31	
uint8	 GetRecTyp(void)
{
	static uint8	times = 0;
	
	if(times == 0)	 
	{
		times++;	
		return	START_EVT;
	}

	return	RIGHT_DATA;
}

uint32	GetMyMstLocoPower(void)
{
	return	GetPosEnergy();
}

extern	StrDipCommData	l_sDip1CommData,l_sDip2CommData;

#define		SOFT_VER	11
////-------------------------------------------------------------------------------
////��������:        void  StoreData(void)
////��������:        �洢����
////��ڲ���:        ��
////���ڲ���:         
////��������:			
////-------------------------------------------------------------------------------
void  StoreData(void)
{	
	uint32				FlshAddr;										//Flash�洢��ַ
	stcFlshRec		    sFlshRec={0};									//Flsh��¼
	stcTime				sTime;											//ϵͳʱ��
	stcFixInfo 		    sFixInfo;		
	uint16				u16tmp;
    uint32              u32tmp;

	g_CurFlshRecNum 	    = GetCurFlshRecNum();
	sFlshRec.StoreCnt	    = g_CurFlshRecNum;						 

    sFlshRec.GpsLatitude    = GetNegEnergy();                   //������
    sFlshRec.GpsLongitude   = GetPosEnergy();                   //������
    
    sFlshRec.MstEngRotSpd   = GetVol();                         //��ѹ
//	
//	memcpy((uint8 *)&sFlshRec.GpsLongitude,(uint8 *)&l_sDip1CommData.LPressure,sizeof(sFlshRec.GpsLongitude));
//	memcpy((uint8 *)&sFlshRec.GpsLatitude,(uint8 *)&l_sDip2CommData.LPressure,sizeof(sFlshRec.GpsLatitude));

	memcpy((uint8 *)&sFlshRec.SlvDriverNum[0],(uint8 *)&l_sDip1CommData.Pressure,sizeof(l_sDip1CommData.Pressure));
	memcpy((uint8 *)&sFlshRec.RoadNum,(uint8 *)&l_sDip2CommData.Pressure,sizeof(l_sDip2CommData.Pressure));

	memcpy((uint8 *)&sFlshRec.Weight[0],(uint8 *)&l_sDip1CommData.CalcDensity,sizeof(l_sDip1CommData.CalcDensity));
	memcpy((uint8 *)&sFlshRec.PlanLen[0],(uint8 *)&l_sDip2CommData.CalcDensity,sizeof(l_sDip2CommData.CalcDensity));

	memcpy((uint8 *)&sFlshRec.MstDriverNum[0],(uint8 *)&l_sDip1CommData.HightDiff,sizeof(l_sDip1CommData.HightDiff));
	memcpy((uint8 *)&sFlshRec.E_MstDriverNum,(uint8 *)&l_sDip2CommData.HightDiff,sizeof(l_sDip2CommData.HightDiff));
	
	sFlshRec.RecTypCod	= GetRecTyp();

	sFlshRec.Myspeed1	= GetMySpeed1();
	sFlshRec.Myspeed2	= GetMySpeed2();

	sFlshRec.MstDip		= g_DipVal;
	
	sFlshRec.MyKileMeter= GetMyKileMeter();

	//sFlshRec.MyMstLocoPower= GetMyMstLocoPower(); GetPosEnergy()
    sFlshRec.MyMstLocoPower= GetPosEnergy();
    sFlshRec.MyPower    = GetPow();
    
	sFlshRec.Myhig1		= GetDip1Hig();
	sFlshRec.Myhig2		= GetDip2Hig();	

	ReadTime((stcTime *)&sTime);
	sFlshRec.MyYear		= sTime.Year;			
	sFlshRec.MyMonth	= sTime.Month;			
	sFlshRec.MyData		= sTime.Date;			
	sFlshRec.MyHour		= sTime.Hour;			
	sFlshRec.MyMinute	= sTime.Min;			
	sFlshRec.MySecond	= sTime.Sec;

	sFlshRec.MstDensity = GetDensityVal();
	
	u16tmp = GetReviseHight();
	memcpy(sFlshRec.PlanLen,(uint8 *)&u16tmp,sizeof(sFlshRec.PlanLen))	;

	sFlshRec.MyAddspeed	= 0;

	sFlshRec.MyDip		= (uint16)g_DipVal;

	sFlshRec.MyEngRotSpd= GetMyEngRotSpd();

	ReadFixInfo((stcFixInfo *)&sFixInfo);
	sFlshRec.JcRealType	= sFixInfo.LocoTyp + sFixInfo.E_LocoTyp*256 ;
	memcpy((uint8 *)&sFlshRec.JcRealNo,(uint8 *)&sFixInfo.LocoNum,sizeof(sFlshRec.JcRealNo));

	sFlshRec.ErrNum		= GetHostErrNum();
	sFlshRec.ErrorCode	= GetErrorCode();

	sFlshRec.MyLocoWorkState = GetMyLocoWorkState();

	sFlshRec.OilBoxModel= GetOilBoxCod();

	sFlshRec.SoftVes 	= SOFT_VER;

	sFlshRec.MyDip1Tmp = GetMyDip1Tmp();	  		    //�ͳ�1�¶�
	sFlshRec.MyDip2Tmp = GetMyDip2Tmp();				//�ͳ�2�¶�
		
	sFlshRec.MyDip1Err = GetMyDip1Err();
	sFlshRec.MyDip2Err = GetMyDip2Err();
		
	sFlshRec.MyDip1Den = GetMyDip1Den();
	sFlshRec.MyDip2Den = GetMyDip2Den();

	sFlshRec.CrcCheck = GetCrc16Check((uint8 *)&sFlshRec,sizeof(sFlshRec) - 2);

    FlshAddr = GetRecNumAddr( g_CurFlshRecNum );
	if(!WriteFlsh(FlshAddr, (uint16 *)&sFlshRec, sizeof(sFlshRec)))
	{}
	ReadFlshRec((stcFlshRec *)&sFlshRec,g_CurFlshRecNum);
	printfcom0("\r\n stcFlshRec.StoreCnt %d",sFlshRec.StoreCnt);

	g_CurFlshRecNum++;
	
	StoreCurFlshRecNum( g_CurFlshRecNum );              //����ˮ�Ŵ�������
}

//#define	STORE_REC_ONE_SEC	1
////-------------------------------------------------------------------------------
////��������:        void  StoreDataPro(void)
////��������:        �洢����
////��ڲ���:        ��
////���ڲ���:         
////��������:			
////-------------------------------------------------------------------------------
void  StoreDataPro(void)
{
	static	uint32	Time = 0;	
	
	if(
			#ifndef	STORE_REC_ONE_SEC	
	(GetSysTime() - Time > (100 * GetStoreTime() )) &&  
			#endif	    
	(GetSysTime() > 30*100) && (GetSysTime() - Time > 200)
	  )	
	{
		StoreData();
		
		Time = GetSysTime();
	}
}
//
//
////-------------------------------------------------------------------------------
////��������:        	uint8	GetFlshStoreErrEvtFlg(void)
////��������:       	�洢��ˮ����
////��ڲ���:        	��
////���ڲ���:      	��
////-------------------------------------------------------------------------------
//uint8	JudgeLstFlsh(void)
//{
//	static	uint32	Times = 0;
//	stcFlshRec		LstsFlshRec;
//	uint16			CrcCheck;
//	uint8			Flg;
//
//	Times++;
//	
//	Flg = TRUE;
//	
//	if(g_CurFlshRecNum)
//	{
//		if(ReadFlshRec((stcFlshRec *)&LstsFlshRec,g_CurFlshRecNum - 1))
//		{	
//			CrcCheck = GetCrc16Check((uint8 *)&LstsFlshRec,sizeof(stcFlshRec) - 2);
//
//			if((CrcCheck != LstsFlshRec.CrcCheck))
//			{
//				l_FlshStoreErrEvtFlg = FLSH_WRT_ERR_EVT;
//
//				if((Times == 1) ) 
//				{
//					Flg = FALSE;
//				}
//			}
//		}
//	}	
//	
//	return	Flg;
//}
//
////-------------------------------------------------------------------------------
////��������:        	uint8	GetFlshStoreErrEvtFlg(void)
////��������:       	�洢��ˮ����
////��ڲ���:        	��
////���ڲ���:      	��
////-------------------------------------------------------------------------------
//uint8	GetFlshStoreErrEvtFlg(void)
//{
//	return	l_FlshStoreErrEvtFlg;
//}
//
//
////-------------------------------------------------------------------------------
////��������:        	void	StoreRecTask(void)
////��������:       	���¼����
////��ڲ���:        	��
////���ڲ���:      	��
////-------------------------------------------------------------------------------
void	StoreRecTask(void)
{
	StoreDataPro();							//�����ݽ���
}
//
//#define		FLSH_WRT_ERR_EVT	32
////-------------------------------------------------------------------------------
////��������:        	stcFlshRec	ReadFlshRec(uint32	FlshRecNum)
////��������:       	��ָ����ˮ�ŵ�FLSH��¼
////��ڲ���:        	��
////���ڲ���:      	ָ����ˮ�ŵ�Flsh��¼
////-------------------------------------------------------------------------------
uint8	ReadFlshRec(stcFlshRec * sFlshRec,uint32	FlshRecNum)
{
	uint32		FlshAddr;
	//uint16		CrcCheck;
	
	FlshAddr = GetRecNumAddr( FlshRecNum );						
	
	if(ReadFlsh(FlshAddr,(uint16 *)sFlshRec,sizeof(stcFlshRec)))
	{
	/*
		CrcCheck = GetCrc16Check((uint8 *)sFlshRec,sizeof(stcFlshRec) - 2);
		
		if(CrcCheck != sFlshRec->CrcCheck)
		{
			if(sFlshRec->RecTypCod == RIGHT_DATA)
			{
				sFlshRec->RecTypCod = FLSH_WRT_ERR_EVT;
			}
			
			CrcCheck = GetCrc16Check((uint8 *)sFlshRec,sizeof(stcFlshRec) - 2);

			sFlshRec->CrcCheck = CrcCheck;
		}
	*/	
		return 1;
	}
	
	return	0;
}
//
////-------------------------------------------------------------------------------------------------
////��������:             void  ShowFlshRec(stcFlshRec sDip) 
////��������:             ����¼ת��Ϊ�Ƚ����׶��ĸ�ʽ
////��ڲ���:             ��
////���ڲ���:             ��
////˵��:                 
////--------------------------------------------------------------------------------------------------
//void  ShowFlshRec(stcFlshRec sDip) 
//{
//	uint8       Second,Minute,Data,Mouth,Hour;
//	uint16      RelSpeed;
//	uint32      Time;
//	uint16		CrcCheck;				
//	
//	int16 		MstDip1Prs;
//	int16 		MstDip2Prs;	
//	int8 		DipValChgState;
//	int16 		MstDip;
//	int16 		SlvDip;
//	int8 		ErrorCode;
//	int8 		RecTypCod;
//
//	MstDip1Prs  	= sDip.MstDip1Prs;
//	MstDip2Prs		= sDip.MstDip2Prs;	
//	DipValChgState	= sDip.DipValChgState;
//	MstDip			= sDip.MstDip;
//	SlvDip			= sDip.SlvDip;
//	ErrorCode		= sDip.ErrorCode;
//	RecTypCod		= sDip.RecTypCod;
//		
//	CrcCheck = GetCrc16Check((uint8 *)&sDip,sizeof(stcFlshRec) - 2);
//	
//	if(CrcCheck != sDip.CrcCheck)
//	{
//		//printfcom0("\r\n��¼У�����");   
//	}
//		
//    RelSpeed= (uint16)sDip.RelSpeed[0] + (sDip.RelSpeed[1] &(1))*256;
//    
//	memcpy((uint8 *)&Time,sDip.Time,sizeof(Time));
//
//    Second 	= Time  & (0xff >> 2);
//    Minute 	= (Time >> 6 ) & (0xff >> 2);
//    Hour   	= (Time >> 12) & (0xff >> 3);
//    Data   	= (Time >> 17) & (0xff >> 3);
//    Mouth  	= (Time >> 22) & (0xff >> 4);
//    
//   // //printfcom0("\r\n%u-%u %u:%u:%u,",Mouth,Data,Hour,Minute,Second);
//    //printfcom0("\r\n%u-%u %u:%u:%u,",sDip.MyMonth,sDip.MyData,sDip.MyHour,sDip.MyMinute,sDip.MySecond);   
//    //printfcom0("%u,",RelSpeed);      
//  	//printfcom0("%u,%u,%u,%u,%u,%u,%u",MstDip1Prs,MstDip2Prs,MstDip,SlvDip,DipValChgState,ErrorCode,RecTypCod);
//
//}
//
////-------------------------------------------------------------------------------------------------
////��������:             void  PrintfAllFlshRec(void) 
////��������:             ��ӡ��¼
////��ڲ���:             ��
////���ڲ���:             ��
////˵��:                 
////--------------------------------------------------------------------------------------------------
//void  PrintfAllFlshRec(void) 
//{
//	uint32	i;
//	uint32	StartFlshRecNum;		
//	uint32	FlshMaxNum;		
//	stcFlshRec	sFlshRec;		
//	
//	FlshMaxNum		= FLSH_MAX_SIZE/sizeof(stcFlshRec);
//	
//	if(g_CurFlshRecNum > FlshMaxNum)
//	{
//		StartFlshRecNum = g_CurFlshRecNum - FlshMaxNum ;
//	}
//	else
//	{
//		StartFlshRecNum = 1;
//	}
//	
//	//printfcom0("\r\n��ˮ��,�ͳ�1,�ͳ�2,����,��ʾ����,�ٶ�,����,�����,���ϴ���,�仯״̬\r\n");
//	//printfcom0("\r\nStartFlshRecNum:%u,g_CurFlshRecNum:%u\r\n",StartFlshRecNum,g_CurFlshRecNum);
//	for(i = g_CurFlshRecNum;i >= StartFlshRecNum;i--)			//��ˮ�Ŵ��������ͼ�¼��
//	{
//		//SysFastHoldTast();
//			
//		ReadFlshRec((stcFlshRec *)&sFlshRec,i);		
//		
//		ShowFlshRec(sFlshRec);									//����¼��ӡ����
//	}
//}
