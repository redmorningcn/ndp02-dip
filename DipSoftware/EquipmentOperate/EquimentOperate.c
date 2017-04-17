#include    "includes.h"


uint8	SetDen(short density)
{
	stcDensity	sDensity;						//�ܶ�
	uint16		CrcCheck;

	sDensity.Density = density ;
	
	CrcCheck = GetCrc16Check((uint8 *)&sDensity,sizeof(sDensity) - 2);
	
	sDensity.CrcCheck = CrcCheck;
			
	if(StoreDensity((stcDensity *)&sDensity))
	{
		DisplaySet(100,1,"         ");
		DisplaySet(250,1,"D-%d",sDensity.Density);
		DisplaySet(100,1,"         ");
		
		printfcom0("\r\n ���õ��ܶ�ֵ %d",sDensity.Density);
		SetSucceedIndicate();	
		
		return	1;
	}
	else
	{
		StoreErrIndicate();	
		
		return	0;
	}
} 

uint8	SetCalcPara(uint32 calcpara)
{
	if(StoreCalcPara(calcpara))
	{
		DisplaySet(100,1,"         ");
		DisplaySet(250,1,"C-%d",calcpara);
		DisplaySet(100,1,"         ");
		
		SetSucceedIndicate();	
		
		return	1;
	}
	else
	{
		StoreErrIndicate();	
		
		return	0;
	}
} 

uint8	SetHight(short 	Hight)
{
	stcReviseHight	sReviseHight;							//�߶ȵ���
	uint16		CrcCheck;
	short       StoreHight; 
		
	if(ReadReviseHight((stcReviseHight *)&sReviseHight))
	{
		StoreHight = sReviseHight.ReviseHight;
	}
	else
	{
		StoreHight = 0;
	}
	
	sReviseHight.ReviseHight = Hight;
	
	StoreHight = StoreHight + sReviseHight.ReviseHight;
	 	
	if(StoreHight > 500 ||  StoreHight < -500)
	{
		if(StoreHight > 500)
		{
			sReviseHight.ReviseHight = 500;
//			DisplaySet(60,2,"TO_H");
//			DisplaySet(60,2,"    ");
            if(g_DipDisVal)
            {
                DisplaySet(60,1,"%u",g_DipDisVal % 10000);	//��ʾ����ֵ
            }	
//			DelayX10ms(60);
		}
		else
		{
			sReviseHight.ReviseHight = -500;
//			DisplaySet(60,2,"TO_L");
//			DisplaySet(60,2,"    ");
//			DelayX10ms(250);					
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
//		DisplaySet(100,1,"         ");
//		DisplaySet(250,1,"H %d.",sReviseHight.ReviseHight);
//		DisplaySet(100,1,"         ");
        
        
        printfcom0("\r\n ���õĸ߶�ֵ %d",sReviseHight.ReviseHight);

		SetSucceedIndicate();	
		
		return	1;
	}
	else
	{
		StoreErrIndicate();	
		
		return	0;
	}
} 

uint8	SetSel(uint8	ModelNum)
{						
	if(StoreSelectModel(ModelNum))
	{
		DisplaySet(100,1,"         ");
		DisplaySet(250,1,"S-%d.",ModelNum);
		DisplaySet(100,1,"         ");					
		SetSucceedIndicate();	
		
		return	1;
	}
	else
	{
		StoreErrIndicate();	
		
		return	0;
	}
}


uint8	SetFix(unsigned short 	locotype,unsigned short 	loconum)
{
	stcFixInfo	sFixInfo;							//�߶ȵ���
	uint16		CrcCheck;
		
	memcpy((uint8 *)&sFixInfo.LocoTyp,(uint8 *)&locotype,sizeof(locotype));
	memcpy((uint8 *)&sFixInfo.LocoNum,(uint8 *)&loconum,sizeof(loconum));

	DisplaySet(100,1,"         ");
	DisplaySet(250,1,"%4d.%4d",locotype,loconum);
	DisplaySet(100,1,"         ");

	CrcCheck = GetCrc16Check((uint8 *)&sFixInfo,sizeof(sFixInfo) - 2);
	sFixInfo.CrcCheck = CrcCheck;

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


unsigned char l_modelcardflg = 0;

unsigned char GetModelCardFlg(void)
{
	return	l_modelcardflg;
}

void ClearModelCardFlg(void)
{
	l_modelcardflg = 0;
}

extern stcModelCard  m_sModelCard;

#define		OIL_BOX_MODEL_ADDR				2000	//����ģ�͵�ַ
void	SetModel(unsigned char *buf,unsigned int Len)
{
 	static	unsigned char *pmodel;

 	unsigned int   modeldatanum = 0;
	unsigned int   readsize;	
	unsigned int   datalen = 0;
	unsigned int   i;
	uint32		ModelNumAdd;
	uint8		ModelNum;	

	datalen = 0;
			
	memcpy((unsigned char *)&modeldatanum,&buf[datalen],sizeof(modeldatanum));
	datalen += sizeof(modeldatanum);
	
	DisplaySet(50,1,"o..",modeldatanum);
	DisplaySet(50,1,"...",modeldatanum);

	if(modeldatanum == 0)
	{
	   pmodel = (unsigned char *)&m_sModelCard;
	   printfcom0("\r\n ָ����ֵ pmodel %x,sizeof(m_sModelCard) %d",pmodel,sizeof(m_sModelCard));
	   l_modelcardflg = 1;
	}
	
	readsize	= 128<(Len-datalen)?128:(Len-datalen);
	memcpy(pmodel,&buf[datalen],readsize);
	
	StoreOilBoxModel(pmodel - (unsigned char *)&m_sModelCard,&buf[datalen],readsize);
	pmodel += readsize;

	printfcom0("\r\n pmodel - (unsigned char *)&m_sModelCard %d",pmodel - (unsigned char *)&m_sModelCard);
	
	if(modeldatanum == 0xffffffff)
	{
		DisplaySet(5,1,"         ");
		DisplaySet(50,1,"boX");		
		
		l_modelcardflg = 0;
		
		printfcom0("\r\n ģ�ͽ��� sModel ��������� %d,%d",m_sModelCard.sModelSemple[1].PotNum,m_sModelCard.sModelSemple[1].ModelNum );
		for(i = 0; i< m_sModelCard.sModelSemple[1].PotNum;i++)
		{
			printfcom0("\r\n �߶ȣ����� %d,%d",m_sModelCard.sModelSemple[1].sModPot[i].HigVal,m_sModelCard.sModelSemple[1].sModPot[i].DipVal ); 
		}

		for( i = 0;i < 64;i++)
		{
			printfcom0("\r\n ��� %d,%d",m_sModelCard.sModelSemple[i].ModelNum ,m_sModelCard.sModelSemple[i].PotNum); 
		}

	  for(i = 0; i < 46;i++)
	  {
		  ModelNumAdd =  OIL_BOX_MODEL_ADDR + sizeof(stcModel)*18 
		  				+ sizeof(stcModelSemple)*i + sizeof(stcModPot)*10 + 2 + 2;

		  ReadFM24CL64(ModelNumAdd,(uint8 *)&ModelNum, sizeof(ModelNum));

	      printfcom0("\r\n ModelNum %d",ModelNum); 
	  }
		ClaerDisplaySetWithoutStore();

		printfcom0("\r\n modeldatanum %d",modeldatanum);
		DisplaySet(20,1,"         ");
		DisplaySet(50,1,"BOX");
		
		DelayX10ms(300);
	}
}

uint8	ComSendData(unsigned int startnum, unsigned int endnum)
{
	uint32	FlshStartRecNum;
//	uint32	CardMaxRecNum;
	uint32	NoReadRecNum;
	uint32	lstrecnum = 0;

	stcFlshRec		sFlshRec;

	unsigned int startrec;
	unsigned int endrec;

	g_LshRedFlshRecNum 		= ReadLstRedFlshRecNum();
//	g_LshRedFlshRecNum_gprs = ReadLstRedFlshRecNum_gprs();

//	if(GetRecaddr() == 0xC1)
	{
		lstrecnum = g_LshRedFlshRecNum;
	}

//	if(GetRecaddr() == 0xC2)
//	{
//		lstrecnum = g_LshRedFlshRecNum_gprs;
//	}
//	
//	printfcom0("\r\n 11 startnum %d,endnum %d",startnum,endnum);
	
	startrec = lstrecnum > startnum?startnum:lstrecnum;
	endrec   = g_CurFlshRecNum > endnum?endnum:g_CurFlshRecNum;


//	printfcom0("\r\n startrec %d, g_LshRedFlshRecNum %d, startnum %d  ",startrec,g_LshRedFlshRecNum,startnum);
//	printfcom0("\r\n endrec %d, g_CurFlshRecNum %d, endnum %d  ",endrec,g_CurFlshRecNum,endnum);
	

//	printfcom0("\r\n 22 startnum %d,endnum %d",startnum,endnum);

	if(endrec > startrec)
	{
		if(g_CurFlshRecNum > (FLSH_MAX_SIZE)/(sizeof(stcFlshRec)) )
		{
			startrec = g_CurFlshRecNum -  (FLSH_MAX_SIZE)/(sizeof(stcFlshRec));
		}
		if(endrec > startrec)
		{
			NoReadRecNum	= (endrec - startrec);							//Flsh��δ����¼����
		}
		else
		{
			NoReadRecNum = 1;				
		}
	}
	else
	{
		NoReadRecNum = 0;
//		if(GetRecaddr() == 0xC1)
		{
			StoreLstRedFlshRecNum(g_CurFlshRecNum);				//�����µ��Ѷ���¼��ˮ��
		}

//		if(GetRecaddr() == 0xC2)
//		{
//			StoreLstRedFlshRecNum_gprs(g_CurFlshRecNum);				//�����µ��Ѷ���¼��ˮ��
//		}
		return 0;
	}
	
	
//	CardMaxRecNum = 0xffffffff;		
//	NoReadRecNum  = GetReadFlshRecCnt(NoReadRecNum,CardMaxRecNum);	//Ҫд���ݳ���
	
//	FlshStartRecNum = endrec  - NoReadRecNum ;
	FlshStartRecNum = startrec;
		
	printfcom0("\r\n FlshStartRecNum %d,%d",FlshStartRecNum,NoReadRecNum);
				
//	while( NoReadRecNum--)
	{
		ReadFlshRec((stcFlshRec *)&sFlshRec,FlshStartRecNum);

		DataSend_CSNR(0x80,GetRecaddr(),(stcFlshRec *)&sFlshRec,sizeof(sFlshRec));	
		
//		DelayX10ms(2);				
//    ReadCardDisplay(0);										//ָʾ���ڶ���
	}

//   	printfcom0("\r\n GetRecaddr() %x",GetRecaddr());
	if(GetRecaddr() == 0xC1)
	{
		g_LshRedFlshRecNum++;				//
		StoreLstRedFlshRecNum(g_LshRedFlshRecNum);
	}
//	if(GetRecaddr() == 0xC2)
//	{
//		g_LshRedFlshRecNum_gprs++;				//
//		StoreLstRedFlshRecNum(g_LshRedFlshRecNum_gprs);
//	}

	return 1;
} 

void  printfcom2flshrec(void)
{
	static	uint32	FlshStartRecNum = 0;
	stcFlshRec		sFlshRec;

	ReadFlshRec((stcFlshRec *)&sFlshRec,FlshStartRecNum++);
	
	printfcom2("\r\n %02d-%02d-%02d %02d:%02d:%02d,%d,%d,%d\r\n ",sFlshRec.MyYear,sFlshRec.MyMonth,sFlshRec.MyData,sFlshRec.MyHour,sFlshRec.MyMinute,
	sFlshRec.MySecond,sFlshRec.Myhig1,sFlshRec.Myhig2,sFlshRec.MstDip);
}
