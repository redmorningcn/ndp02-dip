////#include 	"config.h"   
////#include 	"string.h"   
////#include	"Globe.h"
////#include	"CpuDrive.h"
////#include	"HardDrive.h"
//
//#include <includes.h>
//#include "FRAM.h"
////------------------------------------------------------------------------
////  ��  �� ��	uint8 StoreCurFlashRecNum(uint32  RecNum)
////  ��  �� ��	���ܺ�ͳ��װ�ü�¼��ˮ��
//// ��ڲ�����	��ǰ��¼��ˮ��
//// ���ڲ�����	��ɹ�,����TRUE,����,����FALSE
////------------------------------------------------------------------------
//void StoreFramToFlsh(void)
//{
////	static	uint8	Buf[128];
////	uint32	i;
////	
////	UnProtectFlash();
////	
////	printfcom0("\r\n ˢ��FLsh������!");
////
////	for(i = 0;i < FRAM_SIZE ;)
////	{
////		//SysFastHoldTast();
////		
////		ReadFM24CL64(i,Buf,128);
////		WriteFlsh(i,(uint16 *)Buf,128);
////		i+=128;
////	}
////	
////	ProtectFlash();
//}
//
////------------------------------------------------------------------------
////  ��  �� ��	uint8 	ReadCurFlshRecNum(void)
////  ��  �� ��	����ǰ��¼װ�ü�¼��ˮ��
//// ��ڲ�����	��
//// ���ڲ�����	��ǰ��ˮ��
////------------------------------------------------------------------------
//uint32 ReadCurFlshRecNum_Flsh(void)
//{
//	uint16	CrcCheck;
//	uint8	Buf[6];
//	uint32	FlshRecNum = 0;
//
//	if(!ReadFlsh(CUR_FLSH_REC_NUM, (uint16 *)Buf, sizeof(Buf)))
//	{
//		printfcom0("\r\n ȡFlsh����ǰ��ˮ�Ŵ���!");
//	}
//	else
//	{
//		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
//		
//		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
//		{
//			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
//			
//			return	FlshRecNum;
//		}
//		else
//		{
//			printfcom0("\r\n ȡFlsh����ǰ��ˮ��У�����");
//			//l_FramReadErrEvtFlg = FRAM_ERR_EVT;
//		}
//	}
//
//	if(!ReadFlsh(CUR_FLSH_REC_NUM + sizeof(Buf), (uint16 *)Buf, sizeof(Buf)))
//	{
//		printfcom0("\r\n ȡFlsh����ǰ��ˮ�ű��ݴ���!");
//	}
//	else
//	{
//		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
//		
//		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
//		{
//			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
//
//			return	FlshRecNum;
//		}
//		else
//		{
//			printfcom0("\r\n ȡFlsh��ǰ��ˮ�ű���У�����");
//			//l_FramReadErrEvtFlg = FRAM_ERR_EVT;
//		}		
//	}
// 	
// 	return	FlshRecNum;
//}
//
////------------------------------------------------------------------------
////  ��  �� ��	uint32 ReadLstRedFlshRecNum(void)
////  ��  �� ��	�����ܺ�ͳ��װ���ϴ�д��¼��ˮ��
//// ��ڲ�����	��
//// ���ڲ�����	���д���ļ�¼��ˮ��
////------------------------------------------------------------------------
//uint32 ReadLstRedFlshRecNum_Flsh(void)
//{
//	uint16	CrcCheck;
//	uint8	Buf[6];
//	uint32	FlshRecNum = 0;
//
//	if(!ReadFlsh(LST_RED_FLSH_REC_NUM, (uint16 *)Buf, sizeof(Buf)))
//	{
//		printfcom0("\r\n ȡFlsh�����һ��д����ˮ�Ŵ���!");
//	}
//	else
//	{
//		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
//		
//		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
//		{
//			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
//	
//			return	FlshRecNum;
//		}
//		else
//		{
//			printfcom0("\r\n ȡFlsh���һ��д����ˮ��У�����");
//		}			
//	}
//
//	if(!ReadFlsh(LST_RED_FLSH_REC_NUM + sizeof(Buf),(uint16 *)Buf, sizeof(Buf)))
//	{
//		printfcom0("\r\n ȡFlsh�����һ��д����ˮ�Ŵ���!");
//	}
//	else
//	{
//		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
//		
//		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
//		{
//			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
//			
//			return	FlshRecNum;
//		}
//		else
//		{
//			printfcom0("\r\n ȡFlsh���һ��д����ˮ��У�����");
//		}			
//	}
// 	
// 	return	FlshRecNum;
//}
//
//
////------------------------------------------------------------------------
////  ��  �� ��uint32 ReadOilBoxModel(stcModel sModel)
////  ��  �� ��������ģ��
//// ��ڲ�������
//// ���ڲ�������ǰ��ˮ��
////------------------------------------------------------------------------
//uint8	ReadOilBoxModel_Flsh(stcModelCard * sModelCard)
//{
////	uint16	CrcCheck;
////	uint16	Flg;
////	static	uint8	Buf[sizeof(stcModelCard)] = {0};
////
////	Flg = FALSE;
////
////	if( ReadFlsh(OIL_BOX_MODEL_ADDR,(uint16 *)sModelCard, sizeof(stcModelCard)))
////	{
////		CrcCheck = GetCrc16Check((uint8 *)sModelCard,sizeof(stcModelCard) - 2);
////		
////		if((CrcCheck == sModelCard->CrcCheck))
////		{
////			if(CrcCheck)
////			{
////				printfcom0("\r\n ȡFlsh�е��ͳ�ģ�ͳɹ���");
////
////				Flg = TRUE;
////			}
////			else if( memcmp( (uint8 *)sModelCard,Buf,sizeof(Buf)))
////			{
////				printfcom0("\r\n ȡFlsh�е��ͳ�ģ��ʧ�ܣ�");
////			
////				Flg = TRUE;
////			}
////		}
////	}
////
////	return	Flg;
//}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8	ReadDensity(stcDensity * sDensity)
////  ��  �� ����ȼ���ܶȴ���
//// ��ڲ�����ȼ���ܶ�ָ��
//// ���ڲ����������ɹ�������1�����򣬷���0
////------------------------------------------------------------------------
//uint8	ReadDensity_Flsh(stcDensity * sDensity)
//{
////	uint16	CrcCheck;
////	uint16	Flg;
////	static	uint8	Buf[sizeof(stcDensity)] = {0};
////
////	Flg = FALSE;
////
////	if( ReadFlsh(OIL_DENSITY_ADDR,(uint16 *)sDensity, sizeof(stcDensity)))
////	{
////		CrcCheck = GetCrc16Check((uint8 *)sDensity,sizeof(stcDensity) - 2);
////		
////		if((CrcCheck == sDensity->CrcCheck))
////		{		
////			if(CrcCheck)
////			{
////				Flg = TRUE;
////				
////				printfcom0("\r\n ȡFlsh�е��ܶȳɹ���");
////
////				return	Flg;
////			}
////			else if( memcmp( (uint8 *)sDensity,Buf,sizeof(Buf)))
////			{
////				Flg = TRUE;
////				
////				printfcom0("\r\n ȡFlsh�е��ܶȳɹ���");
////				return	Flg;
////			}
////			else
////			{
////				printfcom0("\r\n ȡFlsh��ȼ���ܶ�У�����");
////			}
////		}
////		else
////		{
////			printfcom0("\r\n ȡFlsh��ȼ���ܶ�У�����");
////		}
////	}
////	else
////	{
////		printfcom0("\r\n  ȡFlsh��ȼ�����ܶȴ���");
////	}
////	
////	if( ReadFlsh(OIL_DENSITY_ADDR + sizeof(stcDensity),(uint16 *)sDensity, sizeof(stcDensity)))
////	{
////		CrcCheck = GetCrc16Check((uint8 *)sDensity,sizeof(sDensity) - 2);
////		
////		if((CrcCheck == sDensity->CrcCheck))
////		{
////			if(CrcCheck)
////			{
////				Flg = TRUE;
////				
////				printfcom0("\r\n ȡFlsh�е��ܶȳɹ���");
////
////				return	Flg;
////			}
////			else if( memcmp( (uint8 *)sDensity,Buf,sizeof(Buf)))
////			{
////				Flg = TRUE;
////				
////				printfcom0("\r\n ȡFlsh�е��ܶȳɹ���");
////
////				return	Flg;				
////			}
////			else
////			{
////				printfcom0("\r\n ȡFlsh��ȼ���ܶ�У�����");
////			}
////		}
////		else
////		{
////			printfcom0("\r\n ȡFlsh��ȼ���ܶ�У�����");
////		}
////	}
////	else
////	{
////		printfcom0("\r\n ȡFlsh��ȼ�����ܶȴ���");
////	}
////		
////	return	Flg;
//}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8	ReadReviseHight(stcReviseHight * sReviseHight)
////  ��  �� ���������߶�ֵ
//// ��ڲ����������߶Ƚṹ��ָ��
//// ���ڲ������ɹ�������1�����򣬷���0
////------------------------------------------------------------------------
//uint8	ReadReviseHight_Flsh(stcReviseHight * sReviseHight)
//{
//	uint16	CrcCheck;
//	uint8	Flg;
//	uint8	Buf[sizeof(stcReviseHight)] = {0};	
//
//	Flg = FALSE;
//
//	if( ReadFlsh(OIL_REVISE_HIGHT_ADDR,(uint16 *)sReviseHight, sizeof(stcReviseHight)))
//	{
//		
//		CrcCheck = GetCrc16Check((uint8 *)sReviseHight,sizeof(stcReviseHight) - 2);
//		
//		if((CrcCheck == sReviseHight->CrcCheck))
//		{
//			if(CrcCheck)
//			{
//				Flg = TRUE;
//				
//				printfcom0("\r\n ȡFlsh�еĸ߶ȳɹ���");
//				return	Flg;
//			}
//			else if( memcmp( (uint8 *)sReviseHight,Buf,sizeof(Buf)))
//			{
//				Flg = TRUE;
//				
//				printfcom0("\r\n ȡFlsh�еĸ߶ȳɹ���");
//				return	Flg;
//			}
//			else
//			{
//				Flg = TRUE;
//
//				printfcom0("\r\n  ȡFlsh�������߶ȼ���� %d",CrcCheck);
//				return	Flg;
//			}
//		}
//		else
//		{
//			printfcom0("\r\n  ȡFlsh�������߶ȼ���ʹ���");
//		}
//	}
//	else
//	{
//		printfcom0("\r\n  ȡFlsh��ȡ�����߶ȴ���");
//	}
//	
//	if( ReadFlsh(OIL_REVISE_HIGHT_ADDR + sizeof(stcReviseHight),
//									(uint16 *)sReviseHight, sizeof(stcReviseHight)))
//	{
//		CrcCheck = GetCrc16Check((uint8 *)sReviseHight,sizeof(stcReviseHight) - 2);
//		
//		if((CrcCheck == sReviseHight->CrcCheck))
//		{
//			if(CrcCheck)
//			{
//				Flg = TRUE;
//				
//				printfcom0("\r\n ȡFlsh�еĸ߶ȳɹ���");
//
//				return	Flg;
//			}
//			else if( memcmp( (uint16 *)sReviseHight,Buf,sizeof(Buf)))
//			{
//				Flg = TRUE;
//
//				printfcom0("\r\n ȡFlsh�еĸ߶ȳɹ���");
//				
//				return	Flg;
//			}
//			else
//			{
//				Flg = TRUE;
//
//				printfcom0("\r\n ȡFlsh�������߶ȼ���� %d",CrcCheck);
//				return	Flg;			
//			}					
//		}
//		else
//		{
//			printfcom0("\r\n ȡFlsh�������߶ȼ���ʹ���");
//		}		
//	}
//	else
//	{
//		printfcom0("\r\n ȡFlsh��ȡ�����߶ȴ���");
//	}	
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8	ReadReviseHight(stcReviseHight * sReviseHight)
////  ��  �� ���������߶�ֵ
//// ��ڲ����������߶Ƚṹ��ָ��
//// ���ڲ������ɹ�������1�����򣬷���0
////------------------------------------------------------------------------
//uint8	ReadAddDipVal_Flsh(stcAddDipVal * sAddDipVal)
//{
//	uint16	CrcCheck;
//	uint8	Flg;
//	static	uint8	Buf[sizeof(stcAddDipVal)] = {0};	
//
//	Flg = FALSE;
//
//	if( ReadFlsh(ADD_DIP_VAL_ADDR,(uint16 *)sAddDipVal, sizeof(stcAddDipVal)))
//	{
//		CrcCheck = GetCrc16Check((uint8 *)sAddDipVal,sizeof(stcAddDipVal) - 2);
//		
//		if((CrcCheck == sAddDipVal->CrcCheck))
//		{
//			if(CrcCheck)
//			{
//				Flg = TRUE;
//				return	Flg;
//			}
//			else if( memcmp( (uint8 *)sAddDipVal,Buf,sizeof(Buf)))
//			{
//				Flg = TRUE;
//				return	Flg;
//			}
//			else
//			{
//				Flg = TRUE;
//
//				printfcom0("\r\n ȡFlsh��������������� %d",CrcCheck);
//				return	Flg;
//			}
//		}
//		else
//		{
//			printfcom0("\r\n ȡFlsh����������������ʹ���");
//		}
//	}
//	else
//	{
//		printfcom0("\r\n ȡFlsh����������������");
//	}
//	
//	if( ReadFlsh(ADD_DIP_VAL_ADDR + sizeof(stcAddDipVal),
//									(uint16 *)sAddDipVal, sizeof(stcAddDipVal)))
//	{
//		CrcCheck = GetCrc16Check((uint8 *)sAddDipVal,sizeof(stcAddDipVal) - 2);
//		
//		if((CrcCheck == sAddDipVal->CrcCheck))
//		{
//			if(CrcCheck)
//			{
//				Flg = TRUE;
//				return	Flg;
//			}
//			else if( memcmp( (uint8 *)sAddDipVal,Buf,sizeof(Buf)))
//			{
//				Flg = TRUE;
//				return	Flg;
//			}
//			else
//			{
//				Flg = TRUE;
//
//				printfcom0("\r\n ȡFlsh��������������� %d",CrcCheck);
//				return	Flg;			
//			}					
//		}
//		else
//		{
//			printfcom0("\r\n ȡFlsh��������������ͼ���ʹ���");
//		}		
//	}
//	else
//	{
//		printfcom0("\r\n ȡFlsh��������������ʹ���");
//	}	
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8	ReadSelectModel(uint8	ModelNum)
////  ��  �� ��������ģ��ѡ��
//// ��ڲ�������
//// ���ڲ�������
////------------------------------------------------------------------------
//uint8	ReadSelectModel_Flsh(uint8	*ModelNum)
//{
//	uint16	CrcCheck;
//	uint16	CrcCheckTmp;
//	uint8	Buf[4];
//	uint8	Flg;
//	
//	Flg = FALSE;
//	
//	if( ReadFlsh(SELECT_MODEL_ADDR,(uint16 *)Buf, sizeof(Buf)))
//	{	
//		
//		CrcCheckTmp = GetCrc16Check(Buf,2);
//		memcpy((uint8 *)&CrcCheck,&Buf[2],2); 
//		
//		if((CrcCheckTmp == CrcCheck) && (Buf[0] == Buf[1]))	
//		{
//			*ModelNum = Buf[0];
//			
//			if(Buf[0])					//��Ϊ��
//			{
//				Flg = TRUE;
//				
//				printfcom0("\r\n ȡFlsh�е��ͳ�ģ�ͱ�ųɹ���");
//
//				return	Flg;
//			}
//		}
//	}
//
//	if( ReadFlsh(SELECT_MODEL_ADDR + sizeof(Buf),(uint16 *)Buf, sizeof(Buf)))
//	{	
//		CrcCheckTmp = GetCrc16Check(Buf,2);
//		memcpy((uint8 *)&CrcCheck,&Buf[2],2); 
//		
//		if((CrcCheckTmp == CrcCheck) && (Buf[0] == Buf[1]))	
//		{
//			*ModelNum = Buf[0];
//			
//			if(Buf[0])					//��Ϊ��
//			{
//				Flg = TRUE;
//				
//				printfcom0("\r\n ȡFlsh�е��ͳ�ģ�ͱ�ųɹ���");
//	
//				return	Flg;
//			}
//		}
//	}
//	
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////  ��  �� ��	uint8	ReadHostInfo(stcDeviceInfo * sDeviceInfo)
////  ��  �� ��	����¼װ�ó�����Ϣ
//// ��ڲ�����	��
//// ���ڲ�����	��ɹ�,����TRUE,����,����FALSE
////------------------------------------------------------------------------
//uint8	ReadHostInfo_Flsh(stcDeviceInfo * sDeviceInfo)
//{
//	uint16	CrcCheck;
//	uint8	Flg;
//	static	uint8 	Buf[sizeof(stcDeviceInfo)];
//	
//	Flg = FALSE;
//	
//	if( ReadFlsh(HOST_DEVICE_INFO_ADDR, (uint16 *)sDeviceInfo, sizeof(stcDeviceInfo)))
//	{		
//		//PrintfDebug("\r\nReadFM24CL64(HOST_DEVICE_INFO_ADDR, (uint8 *)sDeviceInfo, sizeof(stcDeviceInfo))");
//
//		CrcCheck = GetCrc16Check((uint8 *)sDeviceInfo,sizeof(stcDeviceInfo) - 2);
//		
//		//PrintfDebug("\r\nCrcCheck %d,sDeviceInfo->CrcCheck %d",CrcCheck,sDeviceInfo->CrcCheck);
//
//		if((CrcCheck == sDeviceInfo->CrcCheck))
//		{
//			if(CrcCheck)
//			{
//				Flg = TRUE;
//			}
//			else if( memcmp( (uint8 *)sDeviceInfo,Buf,sizeof(Buf)))
//			{
//				Flg = TRUE;
//			}
//			else
//			{
//				printfcom0("\r\n ȡFlsh��������ϢУ�����!");
//			}				
//		}		
//		else
//		{
//			printfcom0("\r\n ȡFlsh��������ϢУ�����!");
//		}	
//	}
//	else
//	{
//		printfcom0("\r\n ȡFlsh��������Ϣ����!");
//	}
//	
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8 StoreHostStation(stcHostStation  sHostSta)
////  ��  �� �����ܺ�ͳ��װ�ó�װ����Ϣ
//// ��ڲ�������
//// ���ڲ�������ɹ�,����TRUE,����,����FALSE
////------------------------------------------------------------------------
//uint8 ReadFixInfo_Flsh(stcFixInfo * sFix)
//{
//	uint16	CrcCheck;
//	uint8	Flg;
//	static	uint8 	Buf[sizeof(stcFixInfo)] = {0};	
//	
//	Flg = FALSE;
//	 
//	if( ReadFlsh(FIX_INFO_ADDR, (uint16 *)sFix, sizeof(stcFixInfo)))
//	{		
//		CrcCheck = GetCrc16Check((uint8 *)sFix,sizeof(stcFixInfo) - 2);
//		
//		if(CrcCheck == (sFix->CrcCheck))
//		{
//			if(CrcCheck)
//			{
//				Flg = TRUE;
//			}
//			else if( memcmp( (uint8 *)sFix,Buf,sizeof(Buf)))
//			{
//				Flg = TRUE;
//			}
//		}	
//		else
//		{
//			printfcom0("\r\n ȡFlsh��װ����Ϣ�������!");
//		}			
//	}
//	else
//	{
//		printfcom0("\r\n ȡFlsh��װ����Ϣ����!");
//	}
//	
//	return	Flg;
//}
//
