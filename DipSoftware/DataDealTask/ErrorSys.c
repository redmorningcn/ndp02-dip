////#include 	"config.h"                             
////#include 	"Globe.h"                             
////#include 	"HardDrive.h"                             
////#include 	"CpuDrive.h"                             
////#include 	"Tax2.h"                             
////#include 	"DipMath.h"                             
//
#include <includes.h>
////
////#define		ERR_DEAL_LEN		10
////stcFIFO		sErrDealFIFO;							//���崮��0����FIFO�ṹ
////uint8		ErrDealBuf[ERR_DEAL_LEN];				//������ջ�����
//////
////typedef    struct  _stcErrDeal_
////{
////     uint8  CurErrFlg;                 			//�����ʶ
////     uint8  LstErrFlg;                 			//�����ʶ
////     uint8	Rev0;								//
////     uint8  TypCod;                   			//���ʹ���
////}stcErrDeal;
////
////static	stcErrDeal		sErrDeal[100];
//
//#define     ERR_BUF_LEN     	12         //
////stcFIFO     sErrFIFO;                      //���崮��0����FIFO�ṹ
//uint8       gErrBuf[ERR_BUF_LEN];           //������ջ�����
//
//stcFIFO     sStoreErrFIFO;                      //���崮��0����FIFO�ṹ
//uint8       gStoreErrBuf[ERR_BUF_LEN];           //������ջ�����
               
////------------------------------------------------------------------------
//// ��    �ƣ�   void  InitErrSys(void)
//// ��    �ܣ�   ��ʼ��IC����ϵͳ
//// ��ڲ����� 	��
//// ���ڲ���:	
////------------------------------------------------------------------------
//
////��������
//#define   	TAX2_ERR     	90                  //TAX2��������
//#define   	HOST_DIP1_ERR	80                  //�ͳ�1��������
//#define   	HOST_DIP2_ERR 	70                  //�ͳ�2��������
//#define    	CARD_ERR     	60                  //IC������
//#define    	HOST_PRO_ERR 	30                  //����װ�÷�������
//
//extern stcFIFO     sUART1RecFIFO;                          //���崮��0����FIFO�ṹ;
////------------------------------------------------------------------------
//// ��    �ƣ�   void  ErrDeal(void)
//// ��    �ܣ�   �ͳ�1���ϴ���
//// ��ڲ�����   ��
//// ���ڲ�����   ���ϴ���
////------------------------------------------------------------------------
//void  StoreCurErrFlg(uint8	ErrFlg,uint8 ErrTyp)
//{
//	uint32	i,j;
//	uint8	Buf[ERR_BUF_LEN];
//	uint32	ErrNum;
//	uint8	Tmp;
//
//
//	//printfcom0("ErrNum = %d, ErrTyp = %d",ErrNum,ErrTyp);
//
//	ErrNum = GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//��δ���ռ��С
//
//	if(ErrFlg != RIGHT_DATA)
//	{
//		for(i = 0;i < ErrNum ;i++)
//		{
//			if(Buf[i] == ErrFlg)
//			{
//				return;
//			}		
//		}
//
//		printfcom0("\r\n sizeof(gErrBuf)11 %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	
//		//WriteFIFO((stcFIFO *)&sErrFIFO,(uint8 *)&ErrFlg,sizeof(ErrFlg));
//		//WriteFIFO((stcFIFO *)&sStoreErrFIFO,(uint8 *)&ErrFlg,sizeof(ErrFlg));
//	}
//	else  if(ErrFlg == RIGHT_DATA)
//	{		
//		for(i = 0;i < ErrNum;i++)
//		{
//			if((Buf[i] - Buf[i]%10) == ErrTyp)
//			{
//				Tmp = Buf[i]+100;
//				printfcom0("\r\n sizeof(gErrBuf)22 %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	
//				//WriteFIFO((stcFIFO *)&sStoreErrFIFO,(uint8 *)&Tmp,sizeof(Tmp));
//
//				for(j=0; j<ErrNum; j++)						
//				{
//					ReadFIFO((stcFIFO *)&sErrFIFO,(uint8 *)Tmp,sizeof(Tmp));
//					if(j != i )
//					{
//						printfcom0("\r\n sizeof(gErrBuf)33 %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	
//
//						//WriteFIFO((stcFIFO *)&sErrFIFO,(uint8 *)&Buf[j],1);
//					}
//				}
//			}
//		}
//		
//		ErrNum = GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//��δ���ռ��С
//		printfcom0("\R\N ErrNum = %d",ErrNum);
//	}
//}
//
//
//
//
//
////	if(ErrFlg != RIGHT_DATA)
////	{	
////		for(i = ErrTyp ; i < ErrTyp + 10 ; i++)
////		{
////			if(i == ErrFlg)							
////			{
////				sErrDeal[i].CurErrFlg 	= ErrFlg;
////
////				return	;
////			}
////			/*
////			else if(ErrTyp != HOST_PRO_ERR)
////			{
////				sErrDeal[i].CurErrFlg 	= RIGHT_DATA;
////			}
////			*/
////			else
////			{
////				sErrDeal[i].CurErrFlg 	= RIGHT_DATA;
////			}
////		}
////	}
////	else
////	{
////		for(i = ErrTyp ; i < ErrTyp + 10 ; i++)
////		{
////			sErrDeal[i].CurErrFlg 	= RIGHT_DATA;
////		}	
////	}
////}
//
//
////------------------------------------------------------------------------
//// ��    �ƣ�   void  ErrDeal(void)
//// ��    �ܣ�   �������㴦���ж��Ƿ��������
//// ��ڲ�����   ��
//// ���ڲ�����   ���ϴ���
////------------------------------------------------------------------------
//void  ErrDeal(void)
//{
//	uint32	i;
//
//
//
////
////	for(i = 0 ; i < 100 ; i++)
////	{
////		//SysFastHoldTast();
////
////		if(sErrDeal[i].CurErrFlg == sErrDeal[i].LstErrFlg)
////		{
////			sErrDeal[i].TypCod	= RIGHT_DATA;					//���ʹ���
////		}
////		else if(sErrDeal[i].LstErrFlg == RIGHT_DATA)
////		{
////			sErrDeal[i].TypCod	= sErrDeal[i].CurErrFlg;		//���ֹ���
////		}
////		else if(sErrDeal[i].CurErrFlg == RIGHT_DATA)
////		{
////			sErrDeal[i].TypCod	= sErrDeal[i].LstErrFlg + 100;	//���ϻָ�
////		}
////		
////		sErrDeal[i].LstErrFlg 	= sErrDeal[i].CurErrFlg;
////	}
//}
//
////------------------------------------------------------------------------
//// ��    �ƣ�   void  OffErrIndicate(void)
//// ��    �ܣ�   �ع���ָʾ
//// ��ڲ�����   ��
//// ���ڲ�����   
////------------------------------------------------------------------------
//void  ErrLedIndicate(void)
//{
//	uint8	Led;
//	uint8	ErrFlg;
//	uint32	i;
//	uint32	ErrNum;
//	uint8	Buf[ERR_BUF_LEN];
//	uint8	LightFlg;
//	
//	ErrNum =  GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//��δ���ռ��С
//	OnlyReadFIFO((stcFIFO *)&sErrFIFO,Buf,ErrNum);
//
//	LightFlg = 0;
//	for(i = 0; i < ErrNum ;i++)
//	{
//		//SysFastHoldTast();
//
//		ErrFlg	= Buf[i];
//
//		if(ErrFlg != RIGHT_DATA && ErrFlg < 100)
//		{
//			Led 	= (ErrFlg  - (ErrFlg  % 10));		//ָʾ�Ƶ�λ��
//			
//			switch( Led )
//			{
//				case TAX2_ERR:			OnLed(TAX2_LED,0xffffff,5,0);
//										LightFlg |= 0x01<<1;	break;					
//				case HOST_DIP1_ERR:		OnLed(DIP1_LED,0xffffff,5,0);
//										LightFlg |= 0x01<<2;	break;		
//				case HOST_DIP2_ERR:		OnLed(DIP2_LED,0xffffff,5,0);
//										LightFlg |= 0x01<<3;	break;									
//				case CARD_ERR:			OnLed(CARD_LED,0xffffff,5,0);
//										LightFlg |= 0x01<<3;	break;								
//				case HOST_PRO_ERR:		OnLed(HOST_LED,0xffffff,5,0);
//										LightFlg |= 0x01<<4;	break;											
//				default:;
//			}			
//		}
//	}
//
////	for(i = 0; i < ErrNum ;i++)
//	{
//		for(i = 0;i < 8;i++)	
//		{			
//			if(LightFlg & 0x01<<1)
//			{
//				OffLed(TAX2_LED);	
//			}
//			else if(LightFlg & 0x01<<2)
//			{
//				OffLed(DIP1_LED);	
//			}
//			else if(LightFlg & 0x01<<3)
//			{
//				OffLed(CARD_LED);	
//			}
//			else if(LightFlg & 0x01<<4)
//			{
//				OffLed(HOST_LED);	
//			}
//		}
//		//SysFastHoldTast();
//////		
//////		ErrFlg	= sErrDeal[i].TypCod;
//
////		if(ErrFlg != RIGHT_DATA)
////		{
////			Led 	= (ErrFlg - (ErrFlg  % 10));		//ָʾ�Ƶ�λ��
////			
////			switch( LightFlg )
////			{
////				case TAX2_ERR + 100:	OffLed(TAX2_LED);			break;	
////								
////				case HOST_DIP1_ERR+100:	OffLed(DIP1_LED);			break;		
////								
////				case HOST_DIP2_ERR+100:	OffLed(DIP2_LED);			break;	
////								
////				case CARD_ERR + 100:	OffLed(CARD_LED);			break;		
////
////				case HOST_PRO_ERR+100:	OffLed(HOST_LED);			break;		
////									
////				default:;
////			}			
////		}
//	}
//}
//
////------------------------------------------------------------------------
//// ��    �ƣ�   void  ErrDisplayIndicate(void)
//// ��    �ܣ�   ����ָʾ
//// ��ڲ�����   ��
//// ���ڲ�����   
////------------------------------------------------------------------------
//void  ErrDisplayIndicate(void)
//{
//	uint8	Led;
//	uint8	ErrFlg;
//	uint32	i;
//	static	uint32	TaxTime = 0,Dip1Time = 0,Dip2Time = 0,CardTime = 0,HostTime = 0;	
//	uint32	ErrDisplayTime;
//	uint32	ErrNum;
//	uint8	Buf[ERR_BUF_LEN];
//	uint8	LightFlg;
//
//
//	
//	ErrNum =  GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO);      	//��δ���ռ��С
//	OnlyReadFIFO((stcFIFO *)&sErrFIFO,Buf,ErrNum);	
//
//	ErrDisplayTime = 3;
//	
//	for(i = 0; i < ErrNum ;i++)
//	{
//		//SysFastHoldTast();
//		
//		ErrFlg	= Buf[i];
//
//		if(ErrFlg != RIGHT_DATA && ErrFlg < 100 )
//		{
//			Led 	= (ErrFlg  - (ErrFlg  % 10));		//ָʾ�Ƶ�λ��
//			
//			switch( Led )
//			{
//				case TAX2_ERR:		
//								if(GetSysTime() - TaxTime > 200*ErrDisplayTime)					
//								{
//									//DisplaySet(10,1,"         ");
//									//DisplaySet(60,1,"E-%u",ErrFlg);
//									TaxTime = GetSysTime();
//								}
//								break;
//								
//				case HOST_DIP1_ERR:				
//								if(GetSysTime() - Dip1Time > 200*ErrDisplayTime)					
//								{
//									//DisplaySet(10,1,"         ");
//									DisplaySet(60,1,"E-%u",ErrFlg);	
//									Dip1Time = GetSysTime();
//								}							
//								break;	
//							
//				case HOST_DIP2_ERR:			
//								if(GetSysTime() - Dip2Time > 200*ErrDisplayTime)					
//								{
//									//DisplaySet(10,1,"         ");
//									DisplaySet(60,1,"E-%u",ErrFlg);	
//									Dip2Time = GetSysTime();
//								}							
//								break;			
//
//				case CARD_ERR:		
//								if(GetSysTime() - CardTime > 200*ErrDisplayTime)					
//								{
//									//DisplaySet(10,1,"         ");
//									DisplaySet(60,1,"E-%u",ErrFlg);	
//									CardTime = GetSysTime();
//								}
//								break;										
//
//				case HOST_PRO_ERR:			
//								if(GetSysTime() - HostTime > 200*ErrDisplayTime)					
//								{
//									//DisplaySet(10,1,"         ");
//									DisplaySet(60,1,"E-%u",ErrFlg);	
//									HostTime = GetSysTime();
//								}							
//								break;										
//				default:;
//			}			
//		}
//	}	
//}
//
////------------------------------------------------------------------------
//// ��    �ƣ�   void	ErrIndicate(void)
//// ��    �ܣ�   ����ָʾ
//// ��ڲ�����	��
//// ���ڲ���:	��
////------------------------------------------------------------------------
//void	ErrIndicate(void)
//{
//	ErrDisplayIndicate();
//	
//	ErrLedIndicate();
//}
//
////------------------------------------------------------------------------
//// ��    �ƣ�   void	InitErrDealSys(void)
//// ��    �ܣ�   ��ʼ��������뻺����
//// ��ڲ�����	��
//// ���ڲ���:	��
////------------------------------------------------------------------------
//void	InitErrDealSys(void)
//{																
//// 	InitFIFO((stcFIFO *)&sErrFIFO,gErrBuf,sizeof(gErrBuf));
////	InitFIFO((stcFIFO *)&sStoreErrFIFO,gStoreErrBuf,sizeof(gStoreErrBuf));
////	printfcom0("sizeof(gErrBuf) %d,%d,",sizeof(gErrBuf), GetNoReadSizeFIFO((stcFIFO *)&sErrFIFO));	
//}
//
////------------------------------------------------------------------------
//// ��    �ƣ�   void  StoreErrCode(void)
//// ��    �ܣ�   �ͳ�1���ϴ���
//// ��ڲ�����   ��
//// ���ڲ�����   ���ϴ���
////------------------------------------------------------------------------
//void  StoreErrCode(void)
//{
//	uint32	i;
//	uint8	ErrTypCod;
////	
////	for(i = 0 ; i < 100 ; i++)
////	{
////		//SysFastHoldTast();
////		
////		if(sErrDeal[i].TypCod != RIGHT_DATA)
////		{
////			ErrTypCod = sErrDeal[i].TypCod;
////			
////			WriteFIFO((stcFIFO *)&sErrDealFIFO,(uint8 *)&ErrTypCod,1 );
////		}
////	}
//}
//
////------------------------------------------------------------------------
//// ��    �ƣ�   uint8  GetStoreErrTyp(void)
//// ��    �ܣ�   ȡFlsh�洢ʱ�Ĺ��ϴ���
//// ��ڲ�����	��
//// ���ڲ���:	��
//// ˵��:		����ϴ���
////------------------------------------------------------------------------
//uint8  GetStoreErrTypCod(void)
//{
//	uint8	ErrTypCod = RIGHT_DATA;
//	
//	if( ReadFIFO(&sStoreErrFIFO,&ErrTypCod,sizeof(ErrTypCod)) )
//	{
//		return	ErrTypCod;								//�ɹ�,���ض�ȡ����
//	}
//	else
//	{
//		return 	ErrTypCod;								//��ȷ,����0xFF
//	}
//}
//
//extern	uint8 JudgeFlashIDErrFlg( void );
//extern	uint8 JudgeFramWordEvt( void );
//
//#define		FLSH_ID_ERR		36
////------------------------------------------------------------------------
//// ��    �ƣ�   void  JudgeHostError(void)
//// ��    �ܣ�   ���ϴ���ϵͳ
//// ��ڲ�����	��
//// ���ڲ���:	��
////------------------------------------------------------------------------
//uint8  JudgeHostError(void)
//{
//	uint8	ErrFlg1,ErrFlg2,ErrFlg;
//	uint8	ErrFlg3;
//	uint8	ErrFlg4;
////	static	uint32	Times = 0;
//	
//	ErrFlg1 = JudgeCalcError();						//�������
//	ErrFlg2 = JudgeEr2450Err();						//��ص�ѹ
//	ErrFlg3 = JudgeFlashIDErrFlg();					//FLSH��ID�Ŷ�ȡ����
//	ErrFlg4 = JudgeFramWordEvt();					//����ⵥ��
//
//	if(ErrFlg2 != RIGHT_DATA)
//	{	
//		ErrFlg = ErrFlg2;
//	}
//	else if(ErrFlg3 != RIGHT_DATA)
//	{	
//		ErrFlg = ErrFlg3;
//	}
//	else if (ErrFlg4 != RIGHT_DATA)
//	{
//		ErrFlg = ErrFlg4;
//	}
//	else if (ErrFlg1 != RIGHT_DATA)
//	{
//		ErrFlg = ErrFlg1;
//	}	
//	else
//	{
//		ErrFlg = RIGHT_DATA;
//	/*
//		if(Times++ % 2)
//		{
//			ErrFlg = ErrFlg1;
//		}
//		else
//		{
//			ErrFlg = ErrFlg2;
//		}
//	*/
//	}
//	
//	return	ErrFlg;
//}
//
////------------------------------------------------------------------------
//// ��    �ƣ�   void  ErrDealSys(void)
//// ��    �ܣ�   ���ϴ���ϵͳ
//// ��ڲ�����	��
//// ���ڲ���:	��
//// ˵��:������ֶ����,������Ӧ���ȼ��ߵĹ���
////------------------------------------------------------------------------
//void  ErrDealSys(void)
//{
//	static	uint32	Time = 0;
//	static	uint32	Times = 0;
//	
//	uint8	ErrFlg;
//	uint8	i;
//	
//
//	if((GetSysTime() - Time > 100) && (GetSysTime() - g_PullCardTime) > 100)
//	{
//		if( Times > 0)
//		{
//			i=0;
//			printfcom0("\r\n  Error %d ",i++);
//			ErrFlg = JudgeTAX2Error();						//TAX2ͨ��
//			StoreCurErrFlg(ErrFlg,TAX2_ERR); 
//
//			printfcom0("\r\n  Error %d ",i++);
//			ErrFlg = JudgeDip1Error();						//����װ�ù���
//			StoreCurErrFlg(ErrFlg,HOST_DIP1_ERR); 
//		
//			printfcom0("\r\n  Error %d ",i++);
//			ErrFlg = JudgeDip2Error();						//����װ�ù���
//			StoreCurErrFlg(ErrFlg,HOST_DIP2_ERR);		
//			
//			printfcom0("\r\n  Error %d ",i++);
//			ErrFlg = JudgeHostError();						//�������
//			StoreCurErrFlg(ErrFlg,HOST_PRO_ERR);	
//			
//			printfcom0("\r\n  Error %d ",i++);
//			ErrFlg = JudgeCardError();						//IC������
//			StoreCurErrFlg(ErrFlg,CARD_ERR);	
//			
//			printfcom0("\r\n  Error %d ",i++);																						
//			ErrDeal();										//��������
//
//			printfcom0("\r\n  Error %d ",i++);
//			StoreErrCode();									//����ϴ���	
//				
//			ErrIndicate();									//ָʾ���� 
//		}
//		
//		Times++;
//			
//		Time = GetSysTime();								
//	}
//}
