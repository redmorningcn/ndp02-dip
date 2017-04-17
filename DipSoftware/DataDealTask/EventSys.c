//////#include 	"config.h"                             
//////#include 	"Globe.h"                             
//////#include 	"HardDrive.h"                             
//////#include 	"CpuDrive.h"                             
//////#include 	"Tax2.h"                             
//////#include 	"DipMath.h"                             
//////#include 	"FramStore.h"                             
//////#include 	"StoreRec.h"                             
//////#include 	"OperateCard.h"                             
//
//#include <includes.h>
//
////#define		EVT_DEAL_LEN		20
////stcFIFO		sEvtDealFIFO;						//���崮��0����FIFO�ṹ
////uint8		EvtDealBuf[EVT_DEAL_LEN];			//������ջ�����
//
//#define     EVT_BUF_LEN     	12         //
//stcFIFO     sEvtFIFO;                      //���崮��0����FIFO�ṹ
//uint8       gEvtBuf[EVT_BUF_LEN];           //������ջ�����
//
////��������
//#define   	TAX2_EVT     	90                  //TAX2��������
//#define   	HOST_DIP1_EVT	80                  //�ͳ�1��������
//#define   	HOST_DIP2_EVT 	70                  //�ͳ�2��������
//#define    	CARD_EVT     	60                  //IC������
//#define    	HOST_PRO_EVT 	30                  //����װ�÷�������
////
////typedef    struct  _stcEvtDeal_
////{
////     uint8  CurEvtFlg;                 			//��ǰ�¼���ʶ
////     uint8  LstEvtFlg;                 			//�ϴ��¼���ʶ
////     uint8  TypCod;                   			//���ʹ���
////     uint8	Reserve0;							//Ԥ��0	
////}stcEvtDeal;
////
////stcEvtDeal		sEvtDeal[100];
////
//////------------------------------------------------------------------------
////// ��    �ƣ�   void  InitEvtSys(void)
////// ��    �ܣ�   ��ʼ��IC����ϵͳ
////// ��ڲ����� 	��
////// ���ڲ���:	
//////------------------------------------------------------------------------
////void  InitEvtSysFlg(void)
////{
////	uint32	i;
////	
////	for(i = 0 ; i < 100; i++)
////	{
////		//SysFastHoldTast();
////		
////		sEvtDeal[i].CurEvtFlg	= RIGHT_DATA;	//��ǰ��ʶ
////		sEvtDeal[i].LstEvtFlg	= RIGHT_DATA;	//�ϴα�ʶ
////		sEvtDeal[i].TypCod 		= RIGHT_DATA;	//���ʹ���
////	}
////}
////
/////*
//////------------------------------------------------------------------------
////// ��    �ƣ�   void  StoreCurEvtFlg(uint8	EvtFlg)
////// ��    �ܣ�   ���¼����� 
////// ��ڲ�����   ��
////// ���ڲ�����   ���ϴ���
//////------------------------------------------------------------------------
////void  StoreCurEvtFlg(uint8	EvtFlg)
////{
////	uint32	i;
////	
////	for(i = 0 ; i < 100 ; i++)
////	{
////		if(EvtFlg != RIGHT_DATA)
////		{
////			if(i == EvtFlg)
////			{
////				sEvtDeal[i].CurEvtFlg 	= EvtFlg;
////			}
////		}
////	}
////}
////
////*/
//////------------------------------------------------------------------------
////// ��    �ƣ�   void  ErrDeal(void)
////// ��    �ܣ�   �ͳ�1���ϴ���
////// ��ڲ�����   ��
////// ���ڲ�����   ���ϴ���
//////------------------------------------------------------------------------
//void  StoreCurEvtFlg(uint8	EvtFlg,uint8 EvtTyp)
//{
//	uint32	i,j;
//	uint8	Buf[EVT_BUF_LEN];
//	uint32	EvtNum;
//	uint8	Tmp;
//
//	EvtNum = GetNoReadSizeFIFO((stcFIFO *)&sEvtFIFO);      	//��δ���ռ��С
//	OnlyReadFIFO((stcFIFO *)&sEvtFIFO,Buf,EvtNum);
//	printfcom0("\r\n EvtNum = %d, EvtTyp = %d,EvtFlg = %d",EvtNum,EvtTyp,EvtFlg);
//
//	if(EvtFlg != RIGHT_DATA)
//	{
//		for(i = 0;i < EvtNum ;i++)
//		{
//			if(Buf[i] == EvtFlg)
//			{
//				return;
//			}		
//		}
//
//		printfcom0("\r\n sizeof(gErrBuf)11 %d,%d,",sizeof(gEvtBuf), GetNoReadSizeFIFO((stcFIFO *)&sEvtFIFO));	
//		WriteFIFO((stcFIFO *)&sEvtFIFO,(uint8 *)&EvtFlg,sizeof(EvtFlg));
//	}
////	if(ErrFlg != RIGHT_DATA)
////	{	
////		for(i = ErrTyp ; i < ErrTyp + 10 ; i++)
////		{
////			if(i == ErrFlg)							
////			{
////				sEvtDeal[i].CurEvtFlg 	= ErrFlg;
////
////				return	;
////			}
////			//else if(ErrTyp != HOST_PRO_EVT)
////			else
////			{
////				sEvtDeal[i].CurEvtFlg 	= RIGHT_DATA;
////			}
////		}
////	}
////	else
////	{
////		for(i = ErrTyp ; i < ErrTyp + 10 ; i++)
////		{
////			sEvtDeal[i].CurEvtFlg 	= RIGHT_DATA;
////		}	
////	}
//}
//
//////------------------------------------------------------------------------
////// ��    �ƣ�   void  EvtDeal(void)
////// ��    �ܣ�   �ͳ�1���ϴ���
////// ��ڲ�����   ��
////// ���ڲ�����   ���ϴ���
//////------------------------------------------------------------------------
////void  EvtDeal(void)
////{
////	uint32	i;
////	
////	for(i = 0 ; i < 100 ; i++)
////	{
////		//SysFastHoldTast();
////		
////		if(sEvtDeal[i].CurEvtFlg != RIGHT_DATA)
////		{
////			sEvtDeal[i].TypCod 		= sEvtDeal[i].CurEvtFlg;					//���ʹ���
////			
////			//PrintfCOM0("\r\n sEvtDeal[i].CurEvtFlg %d",sEvtDeal[i].CurEvtFlg);
////		}
////		else
////		{
////			sEvtDeal[i].TypCod		= RIGHT_DATA;					//�¼��ָ����͹��ϴ���ͬ���¼�ֻ��¼������ʱ�䣬����¼����ʱ�䣩 
////		}
////		
////		sEvtDeal[i].LstEvtFlg 	= sEvtDeal[i].CurEvtFlg;			
////	}
////}
////
//////------------------------------------------------------------------------
////// ��    �ƣ�   void	InitEvtDealSys(void)
////// ��    �ܣ�   ��ʼ���¼���Ż�����
////// ��ڲ�����	��
////// ���ڲ���:	��
//////------------------------------------------------------------------------
//void	InitEvtDealSys(void)
//{
////	InitEvtSysFlg();																			
//	
//	InitFIFO((stcFIFO *)&sEvtFIFO,gEvtBuf,sizeof(gEvtBuf));	
//}
////
//////------------------------------------------------------------------------
////// ��    �ƣ�   void  CardEvtDeal(void)
////// ��    �ܣ�   ��ʼ��������뻺����
////// ��ڲ�����	��
////// ���ڲ���:	��
////// ˵��:������ֶ����,������Ӧ���ȼ��ߵĹ���
//////------------------------------------------------------------------------
////uint8	GetEvtNoWriteNum(void)
////{
////	uint8	NoWriteNum;
////	static	uint32	Time 	= 0;
////	static	uint32	Timer 	= 0;
////	
////	NoWriteNum = GetNoReadSizeFIFO((stcFIFO *)&sEvtDealFIFO);
////	
////	if((NoWriteNum &&  (GetSysTime() > 60*100)) && GetSysTime() - Timer > 100)
////	{
////		Timer = GetSysTime();
////		Time++;
////	}
////	
////	if(Time > 30)					//�����¼���Ӱ�����ݴ洢
////	{
////		NoWriteNum = 0;
////	}
////	
////	return	NoWriteNum;
////}
////
//////------------------------------------------------------------------------
////// ��    �ƣ�   void  StoreEvtCode(void)
////// ��    �ܣ�   ���¼����� 
////// ��ڲ�����   ��
////// ���ڲ�����   ���ϴ���
//////------------------------------------------------------------------------
////void  StoreEvtCode(void)
////{
////	uint32	i;
////	uint8	EvtTypCod;
////	
////	for(i = 0 ; i < 100 ; i++)
////	{
////		//SysFastHoldTast();
////		
////		if(sEvtDeal[i].TypCod != RIGHT_DATA)
////		{
////			EvtTypCod = sEvtDeal[i].TypCod;
////
////			WriteFIFO((stcFIFO *)&sEvtDealFIFO,(uint8 *)&EvtTypCod,1 );
////			
////			//PrintfCOM0("\r\n sEvtDeal[%d].TypCod %d",i,EvtTypCod);
////		}
////	}
////}
////
//////------------------------------------------------------------------------
////// ��    �ƣ�   uint8  GetStoreEvtTyp(void)
////// ��    �ܣ�   ȡFlsh�洢ʱ�Ĺ��ϴ���
////// ��ڲ�����	��
////// ���ڲ���:	��
////// ˵��:		����ϴ���
//////------------------------------------------------------------------------
//uint8  GetStoreEvtTypCod(void)
//{
//	uint8	EvtTypCod = RIGHT_DATA;
//	
//	if( ReadFIFO(&sEvtFIFO,&EvtTypCod,sizeof(EvtTypCod)) )
//	{
//		return	EvtTypCod;								//�ɹ�,���ض�ȡ����
//	}
//	else
//	{
//		return 	EvtTypCod;								//��ȷ,����0xFF
//	}
//}
//
//////----------------------------------------------------------------------------
////// ��    �ƣ�   uint8 JudgeStartEvt(void)
////// ��    ��:    ���ؿ����¼���ʶ
////// ��ڲ����� 
////// ���ڲ�����
//////----------------------------------------------------------------------------
//uint8 	JudgeHostEvt(void)
//{
//	uint8	EvtTypeTmp;
//	uint8	EvtType[10];
//	uint8	i;
//	uint8	EvtBuf[10];
//	uint8	Time = 0;
//		
//	EvtTypeTmp    = RIGHT_DATA;
//	
//	for(i = 0; i< 10;i++)
//	{
//		EvtType[i] = RIGHT_DATA;
//	}
//	
//	EvtType[0] = JudgeStartEvt();
//	EvtType[1] = JudgeFlshEvt();	
//	EvtType[2] = JudgeFramEvt();	
//	EvtType[3] = JudgeOilEvt();
//	
//	for(i = 0 ; i < 10;i++)
//	{
//		if(EvtType[i] != RIGHT_DATA)
//		{
//			EvtBuf[Time++%10] = EvtType[i];
//			
//			//PrintfCOM0("\r\n \r\n EvtType[i] %d",EvtType[i]);
//		}
//	}
//	
//	if( Time )
//	{
//		EvtTypeTmp = EvtBuf[--Time%10];
//	}
//
//	return	EvtTypeTmp;
//}
//
/////**/
//////------------------------------------------------------------------------
////// ��    �ƣ�   void  EvtDealSys(void)
////// ��    �ܣ�   �¼�����ϵͳ
////// ��ڲ�����	��
////// ���ڲ���:	��
////// 
//////------------------------------------------------------------------------
//void  EvtDealSys(void)
//{
//	static	uint32	Time = 0;
//	
//	uint8	EvtFlg;
//		
//	if(GetSysTime() - Time > 100)
//	{
////		/*
////		EvtFlg = JudgeStartEvt();									
////		StoreCurEvtFlg(EvtFlg);
////		
////		EvtFlg = JudgeFlshEvt();									
////		StoreCurEvtFlg(EvtFlg);		
////		
////		//EvtFlg = JudgeFramEvt();									
////		//StoreCurEvtFlg(EvtFlg);			
////			
////		EvtFlg = JudgeOilEvt();									
////		StoreCurEvtFlg(EvtFlg);			
////					
////		EvtFlg = JudgeTAX2Evt();						//TAX2ͨ���¼�
////		StoreCurEvtFlg(EvtFlg);
////		
////		EvtFlg = JudgeCardEvt();						//Card�¼�
////		StoreCurEvtFlg(EvtFlg);
////		*/
//		EvtFlg = JudgeHostEvt();						//
//		StoreCurEvtFlg(EvtFlg,HOST_PRO_EVT);
//		
////		EvtFlg = JudgeTAX2Evt();						//TAX2ͨ���¼�
////		StoreCurEvtFlg(EvtFlg,TAX2_EVT);
////				
////		EvtFlg = JudgeCardEvt();						//Card�¼�
////		StoreCurEvtFlg(EvtFlg,CARD_EVT);
////			
////		EvtDeal();										//��������
////		
////		StoreEvtCode();									//����ϴ���
////			
////		Time = GetSysTime();	
//	}
//}
//
