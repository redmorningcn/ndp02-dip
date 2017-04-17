////#include 	"config.h"   
////#include 	"string.h"   
////#include	"Globe.h"
////#include	"CpuDrive.h"
////#include	"HardDrive.h"
//
#include <includes.h>
#include "FRAM.h"
/*
#define		CUR_FLSH_REC_NUM				0		//CPU��ǰ��¼��ˮ����������׵�ַ 
#define		LST_RED_FLSH_REC_NUM			12		//CPU����״̬��������׵�ַ
#define		OIL_REVISE_HIGHT_ADDR			24		//�ͳ������߶�
#define		OIL_DENSITY_ADDR				32		//�ͳ��ܶ�
#define		ADD_DIP_VAL_ADDR				72		//��������ֵ
#define		SELECT_MODEL_ADDR				90		//����ģ��ѡ���ַ
#define		HOST_DEVICE_INFO_ADDR			100		//����������Ϣ���������ַ
#define		FIX_INFO_ADDR					150		//�豸��װ����������׵�ַ
#define		CUR_REC_ADDR					200		//���¼�¼��ַ
#define		DEBUG_INFO_ADDR					350		//���Ե�ַ
#define		LOG_INFO_ADDR					500		//��־�����׵�ַ
//#define		LOG_INFO_ADDR					600		//��־�����׵�ַ

#define		OIL_BOX_MODEL_ADDR				2000	//����ģ�͵�ַ	

#define		FRAM_ERR_EVT					33
*/

uint8		l_FramWriteErrEvtFlg 	= RIGHT_DATA;
uint8		l_FramReadErrEvtFlg 	= RIGHT_DATA;
////------------------------------------------------------------------------
////  ��  �� ��	uint8 StoreCurFlashRecNum(uint32  RecNum)
////  ��  �� ��	���ܺ�ͳ��װ�ü�¼��ˮ��
//// ��ڲ�����	��ǰ��¼��ˮ��
//// ���ڲ�����	��ɹ�,����TRUE,����,����FALSE
////------------------------------------------------------------------------
uint8 StoreCurFlshRecNum(uint32  RecNum)
{
	uint16  Crc16Check;
	uint8	Buf[6];
	uint8	Flg;
	
	Flg = TRUE;
	
	memcpy(Buf,(uint8 *)&RecNum,sizeof(RecNum));

	Crc16Check = GetCrc16Check(Buf,sizeof(Buf) - 2);						//ȡУ��
	
	memcpy(&Buf[sizeof(RecNum)],(uint8 *)&Crc16Check,sizeof(Crc16Check));

	if(!WriteFM24CL64(CUR_FLSH_REC_NUM, Buf, sizeof(Buf)))					//����Ϣ
	{
		printfcom0("\r\nWrite StoreCurFlshRecNum Error!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		Flg = 	FALSE;
	}
	
	if(!WriteFM24CL64(CUR_FLSH_REC_NUM + sizeof(Buf), Buf, sizeof(Buf)))	//����Ϣ����
	{
		printfcom0("\r\nWrite StoreCurFlshRecNumBak Error!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		Flg = FALSE;
	}	
	
	return	Flg;
}
//
////------------------------------------------------------------------------
////  ��  �� ��	uint8 	ReadCurFlshRecNum(void)
////  ��  �� ��	����ǰ��¼װ�ü�¼��ˮ��
//// ��ڲ�����	��
//// ���ڲ�����	��ǰ��ˮ��
////------------------------------------------------------------------------
uint32 ReadCurFlshRecNum(void)
{
	uint16	CrcCheck;
	uint8	Buf[6];
	uint32	FlshRecNum = 0;

	if(!ReadFM24CL64(CUR_FLSH_REC_NUM, Buf, sizeof(Buf)))
	{
		printfcom0("\r\n a����ǰ��ˮ�Ŵ���! ");
	}
	else
	{
		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
		
		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
		{
			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));

			return	FlshRecNum;
		}
		else
		{
			printfcom0("\r\n ����ǰ��ˮ��У�����");
		}
	}

	if(!ReadFM24CL64(CUR_FLSH_REC_NUM + sizeof(Buf), Buf, sizeof(Buf)))
	{
		printfcom0("\r\n����ǰ��ˮ�ű��ݴ���!");
	}
	else
	{
		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
		
		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
		{
			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
			
			return	FlshRecNum;
		}
		else
		{
			printfcom0("\r\n��ǰ��ˮ�ű���У�����");
		}		
	}
 	
 	return	FlshRecNum;
}
//
////------------------------------------------------------------------------
////  ��  �� ��	uint8 StoreCurFlashTimes(uint32  Times)
////  ��  �� ��	���ܺ�ͳ��װ�ü�¼��ˮ��
//// ��ڲ�����	��ǰ��¼��ˮ��
//// ���ڲ�����	��ɹ�,����TRUE,����,����FALSE
////------------------------------------------------------------------------
//uint8 StoreDenChangeTimes(uint32  Times)
//{
////	//uint16  Crc16Check;
////	//uint8	Buf[4];
////	uint8	Flg;
////	
////	Flg = TRUE;
////	
////	//memcpy(Buf,(uint8 *)&Times,sizeof(Times));
////
////	//Crc16Check = GetCrc16Check(Buf,sizeof(Buf) - 2);						//ȡУ��
////	
////	//memcpy(&Buf[sizeof(Times)],(uint8 *)&Crc16Check,sizeof(Crc16Check));
////
////	if(!WriteFM24CL64(OIL_DEN_CHAGE_TIMES_ADDR, (uint8 *)&Times, sizeof(Times)))	//����Ϣ
////	{
////		printfcom0("\r\n	Write OIL_DEN_CHAGE_TIMES_ADDR Error!");
////		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
////		Flg = 	FALSE;
////	}
////	
////	return	Flg;
//}
//
////------------------------------------------------------------------------
////  ��  �� ��	uint8 	ReadCurFlshTimes(void)
////  ��  �� ��	����ǰ��¼װ�ü�¼��ˮ��
//// ��ڲ�����	��
//// ���ڲ�����	��ǰ��ˮ��
////------------------------------------------------------------------------
//uint32 ReadDenChangeTimes(void)
//{
////	//uint16	CrcCheck;
////	//uint8	Buf[6];
////	uint32	Times = 0;
////
////	l_FramReadErrEvtFlg = RIGHT_DATA;
////
////	if(!ReadFM24CL64(OIL_DEN_CHAGE_TIMES_ADDR, (uint8 *)&Times, sizeof(Times)))
////	{
////		printfcom0("\r\n OIL_DEN_CHAGE_TIMES_ADDR����!");
////	}
////
//// 	return	Times;
//}
//
uint8	l_ReadDataFlg = NO_ERROR;
//
////------------------------------------------------------------------------
////  ��  �� ��	uint8 StoreLstRedFlshRecNumBck(uint32  RecNum)
////  ��  �� ��	���ܺ�ͳ��װ�����1�ζ���������ˮ��
//// ��ڲ�����	��ǰ��¼��ˮ��
//// ���ڲ�����	��ɹ�,����TRUE,����,����FALSE
////------------------------------------------------------------------------
uint8 StoreLstRedFlshRecNum(uint32  RecNum)
{
	uint16  Crc16Check;
	uint8	Buf[6];
	uint8	Flg;

	Flg = TRUE;
	
	l_ReadDataFlg = ERROR;
	
	memcpy(Buf,(uint8 *)&RecNum,sizeof(RecNum));

	Crc16Check = GetCrc16Check(Buf,sizeof(Buf) - 2);		
	
	memcpy(&Buf[sizeof(RecNum)],(uint8 *)&Crc16Check,sizeof(Crc16Check));

	if(!WriteFM24CL64(LST_RED_FLSH_REC_NUM, Buf, sizeof(Buf)))					//����Ϣ
	{
		printfcom0("\r\nWrite StoreCurFlshRecNum Error!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;		
		Flg = FALSE;
	}
	
	if(!WriteFM24CL64(LST_RED_FLSH_REC_NUM + sizeof(Buf), Buf, sizeof(Buf)))	//����Ϣ����
	{
		printfcom0("\r\nWrite StoreCurFlshRecNumBak Error!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		Flg = FALSE;
	}	
	
	return	Flg;
}
uint8 StoreLstRedFlshRecNum_gprs(uint32  RecNum)
{
	uint16  Crc16Check;
	uint8	Buf[6];
	uint8	Flg;

	Flg = TRUE;
	
	l_ReadDataFlg = ERROR;
	
	memcpy(Buf,(uint8 *)&RecNum,sizeof(RecNum));

	Crc16Check = GetCrc16Check(Buf,sizeof(Buf) - 2);		
	
	memcpy(&Buf[sizeof(RecNum)],(uint8 *)&Crc16Check,sizeof(Crc16Check));

	if(!WriteFM24CL64(LST_RED_FLSH_REC_NUM_GPRS, Buf, sizeof(Buf)))					//����Ϣ
	{
		printfcom0("\r\nWrite StoreCurFlshRecNum Error!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;		
		Flg = FALSE;
	}
	
	if(!WriteFM24CL64(LST_RED_FLSH_REC_NUM_GPRS + sizeof(Buf), Buf, sizeof(Buf)))	//����Ϣ����
	{
		printfcom0("\r\nWrite StoreCurFlshRecNumBak Error!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		Flg = FALSE;
	}	
	
	return	Flg;
}

//
uint8	GetReadDataFlg(void)
{
	return	l_ReadDataFlg;
}
//
void	SetReadDataFlgTrue(void)
{
	l_ReadDataFlg = NO_ERROR;
}
//
////------------------------------------------------------------------------
////  ��  �� ��	uint32 ReadLstRedFlshRecNum(void)
////  ��  �� ��	�����ܺ�ͳ��װ���ϴ�д��¼��ˮ��
//// ��ڲ�����	��
//// ���ڲ�����	���д���ļ�¼��ˮ��
////------------------------------------------------------------------------
uint32 ReadLstRedFlshRecNum(void)
{
	uint16	CrcCheck;
	uint8	Buf[6];
	uint32	FlshRecNum = 0;

	if(!ReadFM24CL64(LST_RED_FLSH_REC_NUM, Buf, sizeof(Buf)))
	{
		printfcom0("\r\n�����һ��д����ˮ�Ŵ���!");
	}
	else
	{
		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
		
		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
		{
			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
	
			return	FlshRecNum;
		}
		else
		{
			printfcom0("\r\n���һ��д����ˮ��У�����");
		}			
	}

	if(!ReadFM24CL64(LST_RED_FLSH_REC_NUM + sizeof(Buf),Buf, sizeof(Buf)))
	{
		printfcom0("\r\n�����һ��д����ˮ�Ŵ���!");
	}
	else
	{
		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
		
		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
		{
			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
			
			return	FlshRecNum;
		}
		else
		{
			printfcom0("\r\n���һ��д����ˮ��У�����");
		}			
	}
 	
 	return	FlshRecNum;
}

////------------------------------------------------------------------------
////  ��  �� ��	uint32 ReadLstRedFlshRecNum(void)
////  ��  �� ��	�����ܺ�ͳ��װ���ϴ�д��¼��ˮ��
//// ��ڲ�����	��
//// ���ڲ�����	���д���ļ�¼��ˮ��
////------------------------------------------------------------------------
uint32 ReadLstRedFlshRecNum_gprs(void)
{
	uint16	CrcCheck;
	uint8	Buf[6];
	uint32	FlshRecNum = 0;

	if(!ReadFM24CL64(LST_RED_FLSH_REC_NUM_GPRS, Buf, sizeof(Buf)))
	{
		printfcom0("\r\n�����һ��д����ˮ�Ŵ���!");
	}
	else
	{
		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
		
		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
		{
			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
	
			return	FlshRecNum;
		}
		else
		{
			printfcom0("\r\n���һ��д����ˮ��У�����");
		}			
	}

	if(!ReadFM24CL64(LST_RED_FLSH_REC_NUM_GPRS + sizeof(Buf),Buf, sizeof(Buf)))
	{
		printfcom0("\r\n�����һ��д����ˮ�Ŵ���!");
	}
	else
	{
		memcpy((uint8 *)&CrcCheck,&Buf[sizeof(FlshRecNum)],sizeof(CrcCheck));
		
		if(CrcCheck == GetCrc16Check(Buf,sizeof(FlshRecNum)))
		{
			memcpy((uint8 *)&FlshRecNum,Buf,sizeof(FlshRecNum));
			
			return	FlshRecNum;
		}
		else
		{
			printfcom0("\r\n���һ��д����ˮ��У�����");
		}			
	}
 	
 	return	FlshRecNum;
}
//
//extern	uint32 ReadLstRedFlshRecNum_Flsh(void);
//
////------------------------------------------------------------------------
////  ��  �� ��	uint8 	ReadCurFlshRecNum(void)
////  ��  �� ��	����ǰ��¼װ�ü�¼��ˮ��
//// ��ڲ�����	��
//// ���ڲ�����	��ǰ��ˮ��
////------------------------------------------------------------------------
uint32 GetLstFlshRecNum(void)
{
	uint32		FlshRecNum = 0;
//	stcFlshRec 	sFlshRec;
	
	if( ReadLstRedFlshRecNum() )
	{
		FlshRecNum = ReadLstRedFlshRecNum();
	}
	else
	{
//		if(ReadLstRedFlshRecNum_Flsh())
		{
//			FlshRecNum = ReadLstRedFlshRecNum_Flsh();
		}
	}
	
	return	FlshRecNum;
}

////------------------------------------------------------------------------
////  ��  �� ��	uint8 	ReadCurFlshRecNum(void)
////  ��  �� ��	����ǰ��¼װ�ü�¼��ˮ��
//// ��ڲ�����	��
//// ���ڲ�����	��ǰ��ˮ��
////------------------------------------------------------------------------
uint32 GetLstFlshRecNum_gprs(void)
{
	uint32		FlshRecNum = 0;
//	stcFlshRec 	sFlshRec;
	
	if( ReadLstRedFlshRecNum_gprs() )
	{
		FlshRecNum = ReadLstRedFlshRecNum_gprs();
	}
	else
	{
//		if(ReadLstRedFlshRecNum_Flsh())
		{
//			FlshRecNum = ReadLstRedFlshRecNum_Flsh();
		}
	}
	
	return	FlshRecNum;
}

void	StoreSysRunPara(stcSysRunPara  sSysRunPara)
{
	WriteFM24CL64(SYS_RUN_PARA_ADDR,(uint8 *)&sSysRunPara, sizeof(stcSysRunPara));	
}

uint8	GetSysRunPara(stcSysRunPara * sSysRunPara)
{
	uint16	CrcCheck;
  	if(!ReadFM24CL64(SYS_RUN_PARA_ADDR,(uint8 *)sSysRunPara, sizeof(stcSysRunPara)))
	{
		printfcom0("\r\nsSysRunPara����!");
		return	0;
	}
	else
	{
		CrcCheck = GetCrc16Check((uint8 *)sSysRunPara,sizeof(stcSysRunPara) - 2);
		if((CrcCheck == sSysRunPara->CrcCheck ) && (CrcCheck != 0) )
		{
//			printfcom0("\r\n ������ȡ�ɹ���");
			return 1;	
		}

		//printfcom0("\r\n CrcCheck Err ,%d,%d",CrcCheck,sSysRunPara->CrcCheck );
	}
	return	0;
}
//
//
//void	ClearFlshRec(void)
//{
//	uint32	RecNum = 0;
//	
//	printfcom0("\r\n ClearFlshRec!");
//	
//	RecNum = 1;
//	
//	StoreCurFlshRecNum(RecNum);
//	StoreLstRedFlshRecNum(RecNum);
//	ReCalPara(1);												//�ͳ߲������¼���
//}
//
////------------------------------------------------------------------------
////  ��  �� ��uint32 StoreOilBoxModel(stcModel sModel)
////  ��  �� ��������ģ��
//// ��ڲ�������
//// ���ڲ�������ǰ��ˮ��
////------------------------------------------------------------------------

uint8	StoreOilBoxModel(uint32 add,uint8	*buf,uint32	bufsize)
{
	WriteFM24CL64(OIL_BOX_MODEL_ADDR+add,buf,bufsize);
	return 1;	
}
//uint8	StoreOilBoxModel(stcModelCard * sModelCard)
//{
//	uint16	CrcCheck;
//	uint8	Flg;
//	
//	Flg = TRUE;
//	
//	CrcCheck = GetCrc16Check((uint8 *)sModelCard,sizeof(stcModelCard) - 2);
//
//	if(CrcCheck == sModelCard->CrcCheck)
//	{
//		if(! WriteFM24CL64(OIL_BOX_MODEL_ADDR,(uint8 *)sModelCard, sizeof(stcModelCard)))
//		{
//			l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
//			Flg = FALSE;
//		}
//	}	
//	else
//	{
//		printfcom0("\r\nCrcCheck == sModelCard->CrcCheck ERR!");
//		Flg = FALSE;
//	}
//
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////  ��  �� ��uint32 ReadOilBoxModel(stcModel sModel)
////  ��  �� ��������ģ��
//// ��ڲ�������
//// ���ڲ�������ǰ��ˮ��
////------------------------------------------------------------------------
uint8	ReadOilBoxModel(stcModelCard * sModelCard)
{
	uint16	CrcCheck;
	uint16	Flg;
	//uint8	Buf[sizeof(stcModelCard)] = {0};

	Flg = FALSE;

	printfcom0("\r\n ReadOilBoxModel!");
	if( ReadFM24CL64(OIL_BOX_MODEL_ADDR,(uint8 *)sModelCard, sizeof(stcModelCard)))
	{
		printfcom0("\r\n ReadOilBoxModel!22");
		CrcCheck = GetCrc16Check((uint8 *)sModelCard,sizeof(stcModelCard) - 2);
		
		if((CrcCheck == sModelCard->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
			}
//			else if( memcmp( (uint8 *)sModelCard,Buf,sizeof(Buf)))
//			{
//				Flg = TRUE;
//			}
		}
	}
		printfcom0("\r\n ReadOilBoxModel!12");
	return	Flg;
}

uint8	GetOilBoxModelsModel(stcModel * sModel)
{
	  uint32	i;
	  uint32	ModelNumAdd;
	  uint32	ModelAdd;
	  uint8		ModelNum;
	  uint16	CrcCheck;
	  uint8		OilBoxTypCod;

	  OilBoxTypCod	= GetOilBoxCod(); 

	  for(i = 0; i < 18;i++)
	  {
	      ModelNumAdd =  OIL_BOX_MODEL_ADDR + sizeof(stcModel)*i + sizeof(stcModPot)*50 + 2 + 2;

		  ReadFM24CL64(ModelNumAdd,(uint8 *)&ModelNum, sizeof(ModelNum));

//		  printfcom0("\r\n 11 OilBoxTypCod == ModelNum %d ,i = %d",ModelNum,i);

		  if(OilBoxTypCod == ModelNum)
		  {
//		  	  printfcom0("\r\n 2OilBoxTypCod == ModelNum %d,i = %d",ModelNum,i);
			  
			  ModelAdd = OIL_BOX_MODEL_ADDR + sizeof(stcModel)*i;		  		
		      ReadFM24CL64(ModelAdd,(uint8 *)sModel,sizeof(stcModel));
//			  printfcom0("\r\n ModelAdd == ModelNum %d,i = %d",ModelAdd);
//			  for(i = 0;i < sModel->PotNum;i++)
//			  {
//			  	printfcom0("\r\n  gaodu %d,youliang %d",sModel->sModPot[i].HigVal,sModel->sModPot[i].DipVal);
//			  }

			  CrcCheck = GetCrc16Check((uint8 *)sModel,sizeof(stcModel) - 2);

			  if(CrcCheck == sModel->CrcCheck)
			  {
			  	 //printfcom0("\r\n 3PotNum %d",sModel->PotNum);	
			  	 return  1;
			  }
		  }
	  }

	  return  0;
}

uint8	GetOilBoxModelsModelSemple(stcModelSemple * sModelSemple)
{
	  uint32	i;
	  uint32	ModelNumAdd;
	  uint32	ModelAdd;
	  uint8		ModelNum;
	  uint16	CrcCheck;
	  uint8		OilBoxTypCod;

	  OilBoxTypCod	= GetOilBoxCod(); 

	  for(i = 0; i < 46;i++)
	  {
		  ModelNumAdd =  OIL_BOX_MODEL_ADDR + sizeof(stcModel)*18 
		  				+ sizeof(stcModelSemple)*i + sizeof(stcModPot)*10 + 2 + 2;

		  ReadFM24CL64(ModelNumAdd,(uint8 *)&ModelNum, sizeof(ModelNum));

		  //printfcom0("\r\n 22 OilBoxTypCod == ModelNum %d, %d",ModelNum,OilBoxTypCod);

		  if(OilBoxTypCod == ModelNum)
		  {
			  ModelAdd = OIL_BOX_MODEL_ADDR + sizeof(stcModel)*18  
			  			+ sizeof(stcModelSemple)*i ;
		
		      ReadFM24CL64(ModelAdd,(uint8 *)sModelSemple,sizeof(stcModelSemple));

			  CrcCheck = GetCrc16Check((uint8 *)sModelSemple,sizeof(stcModelSemple) - 2);

//			  printfcom0("\r\n 22 CrcCheck == CrcCheck %d, %d",CrcCheck,sModelSemple->CrcCheck);
			  if(CrcCheck == sModelSemple->CrcCheck)
			  {
			  	 return  1;
			  }
		  }
	  }

	  return  0;
}

//
////------------------------------------------------------------------------
////  ��  �� ��uint32 uint8	StoreDensity(stcModel sModel)
////  ��  �� ��������ģ��
//// ��ڲ�������
//// ���ڲ�������ǰ��ˮ��
////------------------------------------------------------------------------
uint8	StoreDensity(stcDensity * sDensity)
{
	uint16	CrcCheck;
	uint8	Flg;
	
	Flg = TRUE;
	
	CrcCheck = GetCrc16Check((uint8 *)sDensity,sizeof(stcDensity) - 2);

	if(CrcCheck == sDensity->CrcCheck)
	{
		if(! WriteFM24CL64(OIL_DENSITY_ADDR,(uint8 *)sDensity, sizeof(stcDensity)))
		{
			l_FramWriteErrEvtFlg = FRAM_ERR_EVT;		
			Flg = FALSE;
		}
		
//		if(! WriteFM24CL64(OIL_DENSITY_ADDR + sizeof(stcDensity),(uint8 *)sDensity, sizeof(stcDensity)))
//		{
//			l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
//			Flg = FALSE;
//		}		
	}	
	else
	{
		#pragma diag_suppress 870, 223
		printfcom0("\r\n ����ȼ���ܶȵ�У��ʹ���");
		Flg = FALSE;
	}

	return	Flg;
}


////------------------------------------------------------------------------

////------------------------------------------------------------------------
uint32	ReadCalcPara(void)
{
    uint32  calcpara1;
    uint32  calcpara2;
    
	if( ReadFM24CL64(CALC_PARA_ADDR,(uint8 *)&calcpara1, sizeof(calcpara1)))
	{
        
	}
	if( ReadFM24CL64(CALC_PARA_ADDR+sizeof(calcpara1),(uint8 *)&calcpara2, sizeof(calcpara2)))
	{
        
	}
    
    if(calcpara2 == calcpara1)
    {
        if(calcpara1 > 8000 && calcpara1 < 12000)
            return calcpara1;
    }
    
	return	10000;
}

uint8	StoreCalcPara(uint32    calcpara)
{
    uint8       Flg = TRUE;
    uint32      storecalcpara;
    uint32      readcalcpara;  
    
    if(calcpara < 8000 || calcpara > 12000)
        return FALSE;
    
    readcalcpara = ReadCalcPara();
    
    storecalcpara = (readcalcpara * calcpara) / 10000;
    
    if(! WriteFM24CL64(CALC_PARA_ADDR,(uint8 *)&storecalcpara, sizeof(storecalcpara)))
    {
        l_FramWriteErrEvtFlg = FRAM_ERR_EVT;		
        Flg = FALSE;
    }
    
    if(! WriteFM24CL64(CALC_PARA_ADDR + sizeof(calcpara),(uint8 *)&storecalcpara, sizeof(storecalcpara)))
    {
        l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
        Flg = FALSE;
    }		

	return	Flg;
}


//
////------------------------------------------------------------------------
////  ��  �� ��uint8	ReadDensity(stcDensity * sDensity)
////  ��  �� ����ȼ���ܶȴ���
//// ��ڲ�����ȼ���ܶ�ָ��
//// ���ڲ����������ɹ�������1�����򣬷���0
////------------------------------------------------------------------------
uint8	ReadDensity(stcDensity * sDensity)
{
	uint16	CrcCheck;
	uint16	Flg;

	Flg = FALSE;

	if( ReadFM24CL64(OIL_DENSITY_ADDR,(uint8 *)sDensity, sizeof(stcDensity)))
	{
		CrcCheck = GetCrc16Check((uint8 *)sDensity,sizeof(stcDensity) - 2);
		
		if((CrcCheck == sDensity->CrcCheck))
		{		
			if(CrcCheck )
			{
				Flg = TRUE;
				return	Flg;
			}
			else if(sDensity->Density)
			{
				Flg = TRUE;
				return	Flg;
			}
			else
			{
				printfcom0("\r\n��ȼ���ܶ�У�����");
			}
		}
		else
		{
			printfcom0("\r\n��ȼ���ܶ�У�����");
		}
	}
	else
	{
		printfcom0("\r\n��ȼ�����ܶȴ���");
	}
//	
//	if( ReadFM24CL64(OIL_DENSITY_ADDR + sizeof(stcDensity),(uint8 *)sDensity, sizeof(stcDensity)))
//	{
//		CrcCheck = GetCrc16Check((uint8 *)sDensity,sizeof(sDensity) - 2);
//		
//		if((CrcCheck == sDensity->CrcCheck))
//		{
//			if(CrcCheck)
//			{
//				Flg = TRUE;
//				return	Flg;
//			}
//			else if(sDensity->Density)
//			{
//				Flg = TRUE;
//				return	Flg;
//			}
//			else
//			{
//				printfcom0("\r\n��ȼ���ܶ�У�����");
//			}
//		}
//		else
//		{
//			printfcom0("\r\n��ȼ���ܶ�У�����");
//		}
//	}
//	else
//	{
//		printfcom0("\r\n��ȼ�����ܶȴ���");
//	}
		
	return	Flg;
}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8	StoreReviseHight(stcReviseHight sReviseHight)
////  ��  �� �������������߶�
//// ��ڲ����������߶ȱ���ָ��
//// ���ڲ������ɹ�������1�����򣬷���0
////------------------------------------------------------------------------
uint8	StoreReviseHight(stcReviseHight * sReviseHight)
{
	uint16	CrcCheck;
	uint8	Flg;
	
	Flg = TRUE;
	
	CrcCheck = GetCrc16Check((uint8 *)sReviseHight,sizeof(stcReviseHight) - 2);

	if(CrcCheck == sReviseHight->CrcCheck)
	{
		if(! WriteFM24CL64(OIL_REVISE_HIGHT_ADDR,(uint8 *)sReviseHight, sizeof(stcReviseHight)))
		{
			l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
			Flg = FALSE;
		}
		
		if(! WriteFM24CL64(OIL_REVISE_HIGHT_ADDR + sizeof(stcReviseHight),(uint8 *)sReviseHight, sizeof(stcReviseHight)))
		{
			l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
			Flg = FALSE;
		}		
	}	
	else
	{
		printfcom0("\r\n�������߶�У��ʹ���");
		Flg = FALSE;
	}

	return	Flg;
}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8	ReadReviseHight(stcReviseHight * sReviseHight)
////  ��  �� ���������߶�ֵ
//// ��ڲ����������߶Ƚṹ��ָ��
//// ���ڲ������ɹ�������1�����򣬷���0
////------------------------------------------------------------------------
uint8	ReadReviseHight(stcReviseHight * sReviseHight)
{
	uint16	CrcCheck;
	uint8	Flg;
	uint8	Buf[sizeof(stcReviseHight)] = {0};	

	Flg = FALSE;

	if( ReadFM24CL64(OIL_REVISE_HIGHT_ADDR,(uint8 *)sReviseHight, sizeof(stcReviseHight)))
	{
		CrcCheck = GetCrc16Check((uint8 *)sReviseHight,sizeof(stcReviseHight) - 2);
		
		if((CrcCheck == sReviseHight->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
				return	Flg;
			}
			else if( memcmp( (uint8 *)sReviseHight,Buf,sizeof(Buf)))
			{
				Flg = TRUE;
				return	Flg;
			}
			else
			{
				Flg = TRUE;

				printfcom0("\r\n�������߶ȼ���� %d",CrcCheck);
				return	Flg;
			}
		}
		else
		{
			printfcom0("\r\n�������߶ȼ���ʹ���");
		}
	}
	else
	{
		printfcom0("\r\n��ȡ�����߶ȴ���");
	}
	
	if( ReadFM24CL64(OIL_REVISE_HIGHT_ADDR + sizeof(stcReviseHight),
									(uint8 *)sReviseHight, sizeof(stcReviseHight)))
	{
		CrcCheck = GetCrc16Check((uint8 *)sReviseHight,sizeof(stcReviseHight) - 2);
		
		if((CrcCheck == sReviseHight->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
				return	Flg;
			}
			else if( memcmp( (uint8 *)sReviseHight,Buf,sizeof(Buf)))
			{
				Flg = TRUE;
				return	Flg;
			}
			else
			{
				Flg = TRUE;

				printfcom0("\r\n�������߶ȼ���� %d",CrcCheck);
				return	Flg;			
			}					
		}
		else
		{
			printfcom0("\r\n�������߶ȼ���ʹ���");
		}		
	}
	else
	{
		printfcom0("\r\n��ȡ�����߶ȴ���");
	}	
	return	Flg;
}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8	StoreReviseHight(stcReviseHight sReviseHight)
////  ��  �� �������������߶�
//// ��ڲ����������߶ȱ���ָ��
//// ���ڲ������ɹ�������1�����򣬷���0
////------------------------------------------------------------------------
uint8	StoreAddDipVal(stcAddDipVal * sAddDipVal)
{
	uint16	CrcCheck;
	uint8	Flg;
	
	Flg = TRUE;
	
	CrcCheck = GetCrc16Check((uint8 *)sAddDipVal,sizeof(stcAddDipVal) - 2);

	if(CrcCheck == sAddDipVal->CrcCheck)
	{
		if(! WriteFM24CL64(ADD_DIP_VAL_ADDR,(uint8 *)sAddDipVal, sizeof(stcReviseHight)))
		{
			l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
			Flg = FALSE;
		}
		
		if(! WriteFM24CL64(ADD_DIP_VAL_ADDR + sizeof(stcAddDipVal),(uint8 *)sAddDipVal, sizeof(stcAddDipVal)))
		{
			l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
			Flg = FALSE;
		}		
	}	
	else
	{
		printfcom0("\r\n��������У��ʹ���");
		Flg = FALSE;
	}

	return	Flg;
}
////------------------------------------------------------------------------
////  ��  �� ��uint8	ReadReviseHight(stcReviseHight * sReviseHight)
////  ��  �� ���������߶�ֵ
//// ��ڲ����������߶Ƚṹ��ָ��
//// ���ڲ������ɹ�������1�����򣬷���0
////------------------------------------------------------------------------
uint8	ReadAddDipVal(stcAddDipVal * sAddDipVal)
{
	uint16	CrcCheck;
	uint8	Flg;
	uint8	Buf[sizeof(stcAddDipVal)] = {0};	

	Flg = FALSE;

	if( ReadFM24CL64(ADD_DIP_VAL_ADDR,(uint8 *)sAddDipVal, sizeof(stcAddDipVal)))
	{
		CrcCheck = GetCrc16Check((uint8 *)sAddDipVal,sizeof(stcAddDipVal) - 2);
		
		if((CrcCheck == sAddDipVal->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
				return	Flg;
			}
			else if( memcmp( (uint8 *)sAddDipVal,Buf,sizeof(Buf)))
			{
				Flg = TRUE;
				return	Flg;
			}
			else
			{
				Flg = TRUE;

				printfcom0("\r\n��������������� %d",CrcCheck);
				return	Flg;
			}
		}
		else
		{
			printfcom0("\r\n����������������ʹ���");
		}
	}
	else
	{
		printfcom0("\r\n����������������");
	}
	
	if( ReadFM24CL64(ADD_DIP_VAL_ADDR + sizeof(stcAddDipVal),
									(uint8 *)sAddDipVal, sizeof(stcAddDipVal)))
	{
		CrcCheck = GetCrc16Check((uint8 *)sAddDipVal,sizeof(stcAddDipVal) - 2);
		
		if((CrcCheck == sAddDipVal->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
				return	Flg;
			}
			else if( memcmp( (uint8 *)sAddDipVal,Buf,sizeof(Buf)))
			{
				Flg = TRUE;
				return	Flg;
			}
			else
			{
				Flg = TRUE;

				printfcom0("\r\n��������������� %d",CrcCheck);
				return	Flg;			
			}					
		}
		else
		{
			printfcom0("\r\n��������������ͼ���ʹ���");
		}		
	}
	else
	{
		printfcom0("\r\n��������������ʹ���");
	}	
	
	return	Flg;
}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8	StoreSelectModel(uint8	ModelNum)
////  ��  �� ��������ģ��ѡ��
//// ��ڲ�������
//// ���ڲ�������
////------------------------------------------------------------------------
uint8	StoreSelectModel(uint8	ModelNum)
{
	uint16	CrcCheck;
	uint8	Buf[4];
	uint8	Flg;
	
	Flg = TRUE;
	
	Buf[0] = ModelNum;
	Buf[1] = ModelNum;
	
	CrcCheck = GetCrc16Check(Buf,2);

	memcpy(&Buf[2],(uint8	*)&CrcCheck,2);
	
	if(! WriteFM24CL64(SELECT_MODEL_ADDR,Buf, sizeof(Buf)))
	{
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		Flg = FALSE;
	}
	
	if(! WriteFM24CL64(SELECT_MODEL_ADDR + sizeof(Buf),Buf, sizeof(Buf)))
	{
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		Flg = FALSE;
	}		


	return	Flg;
}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8	ReadSelectModel(uint8	ModelNum)
////  ��  �� ��������ģ��ѡ��
//// ��ڲ�������
//// ���ڲ�������
////------------------------------------------------------------------------
uint8	ReadSelectModel(uint8	*ModelNum)
{
	uint16	CrcCheck;
	uint16	CrcCheckTmp;
	uint8	Buf[4];
	uint8	Flg;
	
	Flg = FALSE;
	
	if( ReadFM24CL64(SELECT_MODEL_ADDR,Buf, sizeof(Buf)))
	{	
		CrcCheckTmp = GetCrc16Check(Buf,2);
		memcpy((uint8 *)&CrcCheck,&Buf[2],2); 
		
		if((CrcCheckTmp == CrcCheck) && (Buf[0] == Buf[1]))	
		{
			*ModelNum = Buf[0];
			
			if(Buf[0])					//��Ϊ��
			{
				Flg = TRUE;
				
				return	Flg;
			}
		}
	}

	if( ReadFM24CL64(SELECT_MODEL_ADDR + sizeof(Buf),Buf, sizeof(Buf)))
	{	
		CrcCheckTmp = GetCrc16Check(Buf,2);
		memcpy((uint8 *)&CrcCheck,&Buf[2],2); 
		
		if((CrcCheckTmp == CrcCheck) && (Buf[0] == Buf[1]))	
		{
			*ModelNum = Buf[0];
			
			if(Buf[0])					//��Ϊ��
			{
				Flg = TRUE;
				
				return	Flg;
			}
		}
	}
	
	return	Flg;
}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8 StoreHostStation(stcHostStation  sHostSta)
////  ��  �� �����ܺ�ͳ��װ�ó�����Ϣ
//// ��ڲ�������
//// ���ڲ�������ɹ�,����TRUE,����,����FALSE
////------------------------------------------------------------------------
uint8 StoreHostInfo(stcDeviceInfo * sDevice)
{
	if(!WriteFM24CL64(HOST_DEVICE_INFO_ADDR, (uint8 *)sDevice, sizeof(stcDeviceInfo)))
	{
		//printfcom0("\r\n�������Ϣ����!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		return	FALSE;
	}
	return	TRUE;
}
//
////------------------------------------------------------------------------
////  ��  �� ��	uint8	ReadHostInfo(stcDeviceInfo * sDeviceInfo)
////  ��  �� ��	����¼װ�ó�����Ϣ
//// ��ڲ�����	��
//// ���ڲ�����	��ɹ�,����TRUE,����,����FALSE
////------------------------------------------------------------------------
uint8	ReadHostInfo(stcDeviceInfo * sDeviceInfo)
{
	uint16	CrcCheck;
	uint8	Flg;
	uint8 	Buf[sizeof(stcDeviceInfo)];
	
	Flg = FALSE;
	
	if( ReadFM24CL64(HOST_DEVICE_INFO_ADDR, (uint8 *)sDeviceInfo, sizeof(stcDeviceInfo)))
	{		
		//PrintfDebug("\r\nReadFM24CL64(HOST_DEVICE_INFO_ADDR, (uint8 *)sDeviceInfo, sizeof(stcDeviceInfo))");

		CrcCheck = GetCrc16Check((uint8 *)sDeviceInfo,sizeof(stcDeviceInfo) - 2);
		
		//PrintfDebug("\r\nCrcCheck %d,sDeviceInfo->CrcCheck %d",CrcCheck,sDeviceInfo->CrcCheck);

		if((CrcCheck == sDeviceInfo->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
			}
			else if( memcmp( (uint8 *)sDeviceInfo,Buf,sizeof(Buf)))
			{
				Flg = TRUE;
			}
			else
			{
				//printfcom0("\r\n��������ϢУ�����!");
			}				
		}		
		else
		{
			//printfcom0("\r\n��������ϢУ�����!");
		}	
	}
	else
	{
		//printfcom0("\r\n��������Ϣ����!");
	}
	
	return	Flg;
}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8 StoreFixInfo(stcHostStation  sHostSta)
////  ��  �� �����ܺ�ͳ��װ�ó�װ����Ϣ
//// ��ڲ�������
//// ���ڲ�������ɹ�,����TRUE,����,����FALSE
////------------------------------------------------------------------------
uint8 StoreFixInfo(stcFixInfo * sFix)
{
	if(!WriteFM24CL64(FIX_INFO_ADDR, (uint8 *)sFix, sizeof(stcFixInfo)))
	{
		printfcom0("\r\nWrite StoreFixInfo Error!");
		l_FramWriteErrEvtFlg = FRAM_ERR_EVT;
		return	FALSE;
	}
	 
	return	TRUE;
}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8 StoreHostStation(stcHostStation  sHostSta)
////  ��  �� �����ܺ�ͳ��װ�ó�װ����Ϣ
//// ��ڲ�������
//// ���ڲ�������ɹ�,����TRUE,����,����FALSE
////------------------------------------------------------------------------
uint8 ReadFixInfo(stcFixInfo * sFix)
{
	uint16	CrcCheck;
	uint8	Flg;
	uint8 	Buf[sizeof(stcFixInfo)] = {0};	
	
	Flg = FALSE;
	 
	if( ReadFM24CL64(FIX_INFO_ADDR, (uint8 *)sFix, sizeof(stcFixInfo)))
	{		
		CrcCheck = GetCrc16Check((uint8 *)sFix,sizeof(stcFixInfo) - 2);
		
		if(CrcCheck == (sFix->CrcCheck))
		{
			if(CrcCheck)
			{
				Flg = TRUE;
			}
			else if( memcmp( (uint8 *)sFix,Buf,sizeof(Buf)))
			{
				Flg = TRUE;
			}
		}	
		else
		{
			printfcom0("\r\n��װ����Ϣ�������!");
		}			
	}
	else
	{
		printfcom0("\r\n��װ����Ϣ����!");
	}
	
	return	Flg;
}
//
//uint8	GetFramWriteErrEvtFlg(void)
//{
//	return	l_FramWriteErrEvtFlg;
//}
//
//uint8	GetFramReadErrEvtFlg(void)
//{
//	return	l_FramReadErrEvtFlg;
//}
//
//
//
////-------------------------------------------------------------------------------
////��������:        	uint8	JudgeFramEvt(void)
////��������:       	�ж�Flsh�¼�
////��ڲ���:        	��
////���ڲ���:      	��
////-------------------------------------------------------------------------------
uint8	JudgeFramEvt(void)
{
//	uint8	EvtType;
//	
//	if((GetFramWriteErrEvtFlg() == RIGHT_DATA) && (GetFramReadErrEvtFlg() == RIGHT_DATA) )
//	{
//		EvtType = RIGHT_DATA;
//	}
//	else if(GetFramWriteErrEvtFlg() == RIGHT_DATA)
//	{
//		EvtType = GetFramReadErrEvtFlg();
//	}
//	else
//	{
//		EvtType = GetFramWriteErrEvtFlg();
//	}
//	
//	return	EvtType;
	return 1;
}
//
#define		FRAM_WRITE_TEST		0xaa55
uint8		mFramWordTestErrFlg;
////-------------------------------------------------------------------------------
////��������:        	uint8	JudgeFramWordEvt(void)
////��������:       	�ж�Flsh�¼�
////��ڲ���:        	��
////���ڲ���:      	��
////-------------------------------------------------------------------------------
void	TestFramOneWord(void)
{
	uint16	Temp16;
	uint16	TestTmp = FRAM_WRITE_TEST;
	uint16	ReadTmp;

	ReadFM24CL64(FRAM_END_ADDR - 2, (uint8 *)&Temp16, sizeof(Temp16));  	//ȡ���ݴ�
	
	WriteFM24CL64(FRAM_END_ADDR - 2, (uint8 *)&TestTmp, sizeof(TestTmp));	//д������
	
	ReadFM24CL64(FRAM_END_ADDR - 2, (uint8 *)&ReadTmp, sizeof(ReadTmp));  	//ȡ���ݴ�
	
	WriteFM24CL64(FRAM_END_ADDR - 2, (uint8 *)&Temp16, sizeof(Temp16));		//д������
	
	if(ReadTmp == TestTmp)						
	{
		mFramWordTestErrFlg = NO_ERROR;
	}
	else
	{
		mFramWordTestErrFlg = ERROR;
	}
}
//
//-------------------------------------------------------------------------------
//��������:        	uint8	GetFramWordTestErrFlg(void)
//��������:       	�ж�Flsh�¼�
//��ڲ���:        	��
//���ڲ���:      	��
//-------------------------------------------------------------------------------
uint8	GetFramWordTestErrFlg(void)
{
	return	mFramWordTestErrFlg;	
}


#define		FRAM_WORD_ERR	37
////-------------------------------------------------------------------------------
////��������:        	uint8	JudgeFramWordEvt(void)
////��������:       	�ж�Flsh�¼�
////��ڲ���:        	��
////���ڲ���:      	��
////-------------------------------------------------------------------------------
uint8	JudgeFramWordEvt(void)
{
	
	if(GetSysTime() % 60*100 ==1  || GetSysTime() < 60*100)
	{
		TestFramOneWord();
	}

	if(GetFramWordTestErrFlg() == ERROR)
	{
		return	FRAM_WORD_ERR;
	}

	return	RIGHT_DATA;

}

////------------------------------------------------------------------------
////  ��  �� ��	uint8 StoreCurFlshRec(uint32  RecNum)
////  ��  �� ��	���ܺ�ͳ��װ�ü�¼��ˮ��
//// ��ڲ�����	��ǰ��¼��ˮ��
//// ���ڲ�����	��ɹ�,����TRUE,����,����FALSE
////------------------------------------------------------------------------
//uint8 StoreCurFlshRec(stcFlshRec * sFlshRec)
//{
//	uint8	Flg;
//	
//	Flg = TRUE;
//
//	if(!WriteFM24CL64(CUR_REC_ADDR, (uint8 *)sFlshRec, sizeof(stcFlshRec)))	//����Ϣ
//	{
//		Flg = 	FALSE;
//		
//		printfcom0("\r\n�������ݼ�¼����!");
//	}
//	
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8 ReadCurFlshRec(stcFlshRec * sFlshRec)
////  ��  �� �������ܺ�ͳ��װ�ü�¼��ˮ��
//// ��ڲ�������
//// ���ڲ�������ǰ��ˮ��
////------------------------------------------------------------------------
//uint8 ReadCurFlshRec(stcFlshRec * sFlshRec)
//{
//	uint8	Flg;
//	uint16	CrcCheck;
//
//	
//	Flg = TRUE;
//
//	if(!ReadFM24CL64(CUR_REC_ADDR, (uint8 *)sFlshRec, sizeof(stcFlshRec)))
//	{
//		Flg = 	FALSE;
//		
//		printfcom0("\r\nRead ReadCurFlshRec Error!");
//	}
//	else
//	{
//		CrcCheck = GetCrc16Check((uint8 *)sFlshRec,sizeof(stcFlshRec) - 2);
//		
//		if(CrcCheck != (sFlshRec->CrcCheck) || CrcCheck == 0 )
//		{
//			//sFlshRec = 0;
//			Flg = 	FALSE;
//			printfcom0("\r\n���һ�δ��FLASE��CRC����");
//		}	
//	}
//	
// 	return	Flg;
//}
//
////------------------------------------------------------------------------
////  ��  �� ��	uint8 StoreCurFlshRec(uint32  RecNum)
////  ��  �� ��	���ܺ�ͳ��װ�ü�¼��ˮ��
//// ��ڲ�����	��ǰ��¼��ˮ��
//// ���ڲ�����	��ɹ�,����TRUE,����,����FALSE
////------------------------------------------------------------------------
//uint8 StoreLogZone(stcLogZone * sLogZone)
//{
//
//	uint8	Flg;
///*	
//	Flg = TRUE;
//
//	if(!WriteFM24CL64(LOG_INFO_ADDR, (uint8 *)sLogZone, sizeof(stcLogZone)))	//����Ϣ
//	{
//		Flg = 	FALSE;
//		
//		printfcom0("\r\nStoreLogZone Error!");
//	}
//*/	
//	return	Flg;
//
//}
//
////------------------------------------------------------------------------
////  ��  �� ��	uint8 StoreCurFlshRec(uint32  RecNum)
////  ��  �� ��	���ܺ�ͳ��װ�ü�¼��ˮ��
//// ��ڲ�����	��ǰ��¼��ˮ��
//// ���ڲ�����	��ɹ�,����TRUE,����,����FALSE
////------------------------------------------------------------------------
//uint8 ReadLogZone(stcLogZone * sLogZone)
//{
//	uint8	Flg;
//	
//	Flg = TRUE;
//
//	if(!ReadFM24CL64(LOG_INFO_ADDR, (uint8 *)sLogZone, sizeof(stcLogZone)))
//	{
//		Flg = 	FALSE;
//		
//		printfcom0("\r\nReadLogZone Error!");
//	}
//	
// 	return	Flg;
//}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8	ReadDebugCardInfo(stcDebugCard *sDebugCard)
////  ��  �� ���������������Ϣ
//// ��ڲ�������
//// ���ڲ�������ǰ��ˮ��
////------------------------------------------------------------------------
//uint8	StoreDebugCardInfo(stcDebugCard *sDebugCard)
//{
//	uint8	Flg = 	TRUE;
//
//	if(!WriteFM24CL64(DEBUG_INFO_ADDR, (uint8 *)sDebugCard, sizeof(stcDebugCard)))
//	{
//		Flg = 	FALSE;
//		
//		printfcom0("\r\nGetDebugCardInfo");
//	}	
//	
//	return	Flg;
//}
//
////------------------------------------------------------------------------
////  ��  �� ��uint8	ReadDebugCardInfo(stcDebugCard *sDebugCard)
////  ��  �� ���������������Ϣ
//// ��ڲ�������
//// ���ڲ�������ǰ��ˮ��
////------------------------------------------------------------------------
//uint8	ReadDebugCardInfo(stcDebugCard *sDebugCard)
//{
//	uint8	Flg = 	TRUE;
//	uint16	CrcCheck;
//
//	if(!ReadFM24CL64(DEBUG_INFO_ADDR, (uint8 *)sDebugCard, sizeof(stcDebugCard)))
//	{
//		Flg = 	FALSE;
//		
//		printfcom0("\r\nGetDebugCardInfo ERR!");
//	}	
//	else
//	{
//		CrcCheck = GetCrc16Check((uint8 *)sDebugCard,sizeof(stcDebugCard) - 2);
//		
//		if(CrcCheck != sDebugCard->CrcCheck)
//		{
//			Flg = 	FALSE;
//		
//			printfcom0("\r\n�����Կ���ϢУ��ʧ�ܣ�");		
//		}
//	}
//	
//	return	Flg;
//}
//
//
//extern	uint32 ReadCurFlshRecNum_Flsh(void);
//
////------------------------------------------------------------------------
////  ��  �� ��	uint8 	ReadCurFlshRecNum(void)
////  ��  �� ��	����ǰ��¼װ�ü�¼��ˮ��
//// ��ڲ�����	��
//// ���ڲ�����	��ǰ��ˮ��
////------------------------------------------------------------------------
uint32 GetCurFlshRecNum(void)
{
	uint32		CurFlshRecNum = 0;
	 
	CurFlshRecNum = ReadCurFlshRecNum();

	return 	CurFlshRecNum;
}
//
