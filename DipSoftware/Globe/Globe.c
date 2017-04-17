#include <includes.h>

extern 	void 	InputDebugState(void);
extern	void	PrinfDebugState(void);


//----------------------------------------------------------------------------
// ��    �ƣ�   void HardInit(void)
// ��    ��:    Ӳ����ʼ��
// ��ڲ�����	
// ���ڲ�����	
//----------------------------------------------------------------------------
void HardInit(void)
{
	//MCU
	InitTimer1();							//��ʼ����ʱ��1ϵͳʱ��
	
	OpenCOM0Tax(28800);						//����0��ʼ��,������57600( ����δ��)
	
	OpenCOM1(9600);							//��ʼ������1
	
#ifdef	HARD_VER_111122	
	mInitCH376Host();						//��ʼ��USB
#endif

	InitI2CIO();							//��ʼ��I2C����

	InitAdc();								//��ʼ��ADC
	
	InitPulse1T0();							//��ʼ��Ƶ�ʲ���
	//�ⲿӲ��
	InitDisplay();							//��ʼ����ʾ
	
	InitICCard();							//��ʼ��IC��
	
	InitKey();								//��ʼ������
	
	InitLed();								//��ʼ����	
	
	InitDS3231();							//��ʼ��ʱ��
		
	ResetFlash();							//��λFlsh
	
	InitFlshInfo();							//��ʼ��Flsh
	
	ProtectFlash();							//Flashд����
	
	ScanPowerAddr();						//ɨ�������ַ
}

extern	uint8 GetLocoModInfo(uint32	LocoTyp,uint32 ModeNum,stcLocoModNum *sLocoModNum);
//----------------------------------------------------------------------------
// ��    �ƣ�   void PrinfSysInfo(void)
// ��    ��:    ϵͳ��ʼ��
// ��ڲ�����
// ���ڲ�����
//----------------------------------------------------------------------------
void	PrinfSysInfo(void)
{
	stcDeviceInfo		sDeviceInfo;
	stcReviseHight		sReviseHight;
	stcFixInfo  		sFix;
	stcDensity			sDensity;
	float				Density;
	int16				ReviseHight;
	uint8				OilBoxCod;

	ReadHostInfo((stcDeviceInfo *)&sDeviceInfo);		//��������Ϣ
	
	printfcom0("\r\n �ܺ�Ӳ���汾��:	");
	SendCOM0(sDeviceInfo.HardwareVer,sizeof(sDeviceInfo.HardwareVer));
	printfcom0("\r\n �ܺ�����汾��:	");
	SendCOM0(sDeviceInfo.SoftwareVer,sizeof(sDeviceInfo.SoftwareVer));
	
	printfcom0("\r\n ");
	OilBoxCod = GetOilBoxCod();
	printfcom0("\r\n ����ģ�ͺ�:	%d",OilBoxCod);

	DisplaySet(150,1,"C_%u",OilBoxCod);	

  	if(ReadReviseHight((stcReviseHight *) &sReviseHight))
  	{	
  		ReviseHight = sReviseHight.ReviseHight / 10;
  		printfcom0("\r\n �����߶�Ϊ:	%d",ReviseHight*10);
  		DisplaySet(100,1,"%d.",ReviseHight*10);		
	}
		
  	if( ReadDensity((stcDensity *) &sDensity))			//ȡ�ܶ�
	{
		Density	=  ((float)sDensity.Density / 1000);
//  		printfcom0("\r\n �ܶ�ֵ:	%f",Density);
  		DisplaySet(60,1,"%d.",(uint16)(1000*Density));		
  	}
  	
 	ReadFixInfo((stcFixInfo *)&sFix);
 	DisplaySet(100,1,"%d",sFix.LocoTyp);		
 	//DisplaySet(100,1,"%d",(uint16)*sFix.LocoNum);		
 	DisplaySet(100,1,"%d",sFix.LocoNum[0]+sFix.LocoNum[1]*256);		
 
  	printfcom0("\r\n ");

  	DisplaySet(60,1,"88888888");		
 	DisplaySet(60,1,"        ");		
}

//----------------------------------------------------------------------------
// ��    �ƣ�   void	GetDeviceInfoStr(uint8 *Buf)
// ��    ��:    �����ʼ��
// ��ڲ����� 
// ���ڲ�����
//----------------------------------------------------------------------------
void	GetDeviceInfoStr(uint8 *Buf)
{
	stcDeviceInfo		sDeviceInfo;
	uint8	Tmp;
	uint32	strLen,AllStrLen = 0;
	
	ReCalPara(0);
	
	printfcom0("\r\n װ����Ϣ����!");
	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n \r\n װ����Ϣ���£�");
	
	printfcom0("\r\n �ܺ�Ӳ���汾��:	");
	AllStrLen += strLen;
	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n ���õĲ�Ʒ���: %d",sDeviceInfo.DeviceNum);
	//printfcom0("\r\n strLen %d, AllStrLen = %d",strLen,AllStrLen);	
	
	AllStrLen += strLen;
	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n ���õĲ�ƷӲ���汾��: %s",sDeviceInfo.HardwareVer);
	//printfcom0("\r\n strLen %d, AllStrLen = %d",strLen,AllStrLen);		
	//printfcom0("\r\n �ܺ�����汾��:	");
	
	AllStrLen += strLen;
	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n ���õĲ�Ʒ����汾��: %s",sDeviceInfo.SoftwareVer);
	printfcom0("\r\n strLen %d, AllStrLen = %d",strLen,AllStrLen);
//	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n ���õĲ�Ʒ����汾��: %d",Tmp);
	
#ifdef	HARD_VER_111122	
	Tmp = 1;
#endif		
	
#ifdef	HARD_VER_090426		
	if(Tmp == 0)
	{	
		printfcom0("\r\n �ܺ�����汾��:	");
		AllStrLen += strLen;
		strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n Ӳ���汾: HV02");	
	}
	else
	{
		AllStrLen += strLen;
		strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n Ӳ���汾: HV03");			
	}	
#endif		

#ifdef	HARD_VER_090214			
		AllStrLen += strLen;
		strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n Ӳ���汾: HV01");			
#endif		

	AllStrLen += strLen;
	strLen = sprintf((int8 *)&Buf[AllStrLen],"\r\n ����汾: SV12.03.12");		
}

extern	void	TestFramOneWord(void);
extern	void	TestFlashID(void);
extern	uint32	GetLstFlshRecNum(void);
//----------------------------------------------------------------------------
// ��    �ƣ�   void SoftInit(void)
// ��    ��:    �����ʼ��
// ��ڲ����� 
// ���ڲ�����
//----------------------------------------------------------------------------
void SoftInit(void)
{	
	g_CurFlshRecNum 	= GetCurFlshRecNum();
	
	g_LshRedFlshRecNum  = GetLstFlshRecNum();
	
	if(g_CurFlshRecNum < g_LshRedFlshRecNum)  //�����ǰ��ˮ��С����ȡ��ˮ�ţ�����ȡ��ˮ�ų��¸�ֵ
	{
		printfcom0("\r\n g_CurFlshRecNum < g_LshRedFlshRecNum");
		g_LshRedFlshRecNum = g_CurFlshRecNum;
	}
	
	InputDebugState();						//����ϵͳ��ʽģʽ	
	
	InitErrDealSys();						//������ϵͳ
	
	InitEvtDealSys();						//��ʼ���¼�ϵͳ
	
	OpenTax2();								//��TAX2ͨ��
	
	InitWatchDog();							//��ʼ��dog
	
	TestFlashID();

	TestFramOneWord();
	
	DelayX10ms(50);							//
}

extern	void IniLocoModTab(void);
//----------------------------------------------------------------------------
// ��    �ƣ�   void SysInit(void)
// ��    ��:    ϵͳ��ʼ��
// ��ڲ�����
// ���ڲ�����
//----------------------------------------------------------------------------
void SysInit(void)
{ 
	uint8	Tmp = 0;
	DisplaySet(100,1,"SV12");		
	DisplaySet(100,1,"10.02");
	
#ifdef	HARD_VER_111122	
	Tmp = 1;
#endif		
	
#ifdef	HARD_VER_090426		
	if(Tmp == 0)
	{	
		DisplaySet(100,1,"HV02");	
	}
	else
	{
		DisplaySet(100,1,"HV03");	
	}	
#endif		
#ifdef	HARD_VER_090214			
	DisplaySet(100,1,"HV01");		
#endif		
	//g_LshRedFlshRecNum 	= 0;
	
	printfcom0("\r\n ��ǰ��¼�ţ�	%u",g_CurFlshRecNum);
	
	printfcom0("\r\n ������¼�ţ�	%u",g_LshRedFlshRecNum);	
	
	printfcom0("\r\n ");
	
//	printfcom0("\r\n ����ģʽ��	%d  ˵����1��Ϊ����ģʽ��0��Ϊ��������ģʽ",g_TestModelFlg);	
		
	PrinfSysInfo();			
	
	PrinfDebugState();	
	
	IniLocoModTab();			//װ�ó�ʼװ�õ�ģ�ͱ��
	
	DisplayTime();				//ʱ����ʾ

	DelayX10ms(50);			
	
	printfcom0("\r\n ");
}


//----------------------------------------------------------------------------
// ��    �ƣ�   void IncDisplay(void)
// ��    ��:    ϵͳ��ʼ��
// ��ڲ�����
// ���ڲ�����
//----------------------------------------------------------------------------
void IncDisplay(void)
{ 
	static	uint32		Time = 0;
	static	uint32		Times = 0;
	static	int16		Prs1,Prs2;	
	static	uint8		i;

	Time = GetSysTime();

	for(i =0 ;i<8;)
	{
		
		COM0Task();
		
		//DelayX10ms(100);
		//COM1Task();
//		SysHoldTast();
			
		Prs1 = GetDip1Prs();
		Prs2 = GetDip2Prs();		
		
		//printfcom0("%4d.%4d",Prs1,Prs2);
		if(GetSysTime() - Time > 100)
		{		
			i++;
			Time = GetSysTime();
	
			if(i%2 == 0)
			{
				DisplaySet(100,1,"%4d.%4d.",Prs1,Prs2);
			}
			else
			{
				DisplaySet(100,1,"%4d.%4d",Prs1,Prs2);
			}
		}
	}

	while(GetPlugFlg() == PLUG_IN_CARD)  //�ж�������
	{
		printfcom0("\r\n Plug Card!");
		
//		SysHoldTast();

		if(Times < 1*60)		//1����ͨ��
		{	
			COM0Task();
		}
		
		//DelayX10ms(50);
					
		Prs1 = GetDip1Prs();
		Prs2 = GetDip2Prs();

		if(GetSysTime() - Time > 100)
		{		
			Time = GetSysTime();

			Times++;
			
			if(Prs1<10000 && Prs2 < 10000)
			{
				printfcom0("%4d.%4d",Prs1,Prs2);
				
				if(Times%2 == 0)
				{
					DisplaySet(100,1,"%4d.%4d.",Prs1,Prs2);
				}
				else
				{
					DisplaySet(100,1,"%4d.%4d",Prs1,Prs2);
				}
			}
			else
			{
				printfcom0("%4d.%4d",Prs1,Prs2);

				DisplaySet(100,1,"%d",Prs1);
				DisplaySet(100,1,"%d.",Prs2);
			}
		}
		
		if(Times > 2*60)		//2�����˳�
		{	
			DelayX10ms(200);
			return;
		}
	}	
	
	DelayX10ms(400);
	
	DisplaySet(150,1,"%d",g_CurFlshRecNum);
	DisplaySet(150,1,"%d.",g_LshRedFlshRecNum);

}

#define		START_EVT		31		
//----------------------------------------------------------------------------
// ��    �ƣ�   uint8 JudgeStartEvt(void)
// ��    ��:    ���ؿ����¼���ʶ
// ��ڲ����� 
// ���ڲ�����
//----------------------------------------------------------------------------
uint8 	JudgeStartEvt(void)
{
	uint8	EvtType = RIGHT_DATA;
	static	uint32	Time = 0;
	
	EvtType = RIGHT_DATA;
	
	if( Time++ == 0 )
	{
		EvtType = START_EVT;	
	}
	
	return	EvtType;
}

//----------------------------------------------------------------------------
// ��    �ƣ�   void PrinfDebugState(void)
// ��    ��:    ϵͳ��ʼ��
// ��ڲ�����
// ���ڲ�����
//----------------------------------------------------------------------------
void	PrinfDebugState(void)
{
	printfcom0("\r\n \r\n ");	
	printfcom0("\r\n ����ģ�Ͷ�Ӧ��ϵ:");
	
	printfcom0("\r\n װ�����У�	<--->	* �豸��Ϣ���ú���������!");
	printfcom0("\r\n ʱ����ʾ��	<--->	* ��ʾʱ��!");
	printfcom0("\r\n ������	   	<--->	* ��δ��ȡ�����ݼ�¼�Ӵ��ڶ���!");
	printfcom0("\r\n д����ɣ�	<--->	* ����������ٴӴ����㷢�ͳ���!");
	printfcom0("\r\n ������	   	<--->	* IC�����ԣ��������ֱȽϼ򵥵Ŀ�!");
	printfcom0("\r\n TAXII�� 	  <--->	* ���н���TAXII����!");
	printfcom0("\r\n ������	  	<--->	* ��IC��ȡװ�������е�����!");
	printfcom0("\r\n IC����	  	<--->	* �豸��Ϣ���ú���������!");
	
	printfcom0("\r\n \r\n ");	
}

extern	void	 TestUsb(void);
extern	uint8	 ComModCard(stcCardFlg	* sCardFlg);
extern	uint8    WriteCardComModelTest(void);
extern	uint8    WritesSetDipCardTest(void);
extern	uint8    WritesTestCardTest(void);
extern	uint8    WriteExpandAddTest(void);
extern	uint8    WriteExpandSubTest(void);
extern	uint8    WriteDenDataCardTest(void);

const char *MemorySizeInf[]  ={"512k","1M", "2M", "4M", "8M", "16M", "32M","64M"};	

//----------------------------------------------------------------------------
// ��    �ƣ�  void InputDebugState(void)
// ��    ��:   ���°���������Ӧ���Է�ʽ
// ��ڲ�����
// ���ڲ�����
//----------------------------------------------------------------------------
void InputDebugState(void)
{
	uint32 	EndTime;
	uint32	KeyFlag = 0;
	uint32	i,j;
	char*	pString[] = 
	{
		"* ",
		"* ���Դ�����������ģ��",
		"* ��δ��ȡ�����ݼ�¼�Ӵ��ڶ�����",
		"* ���н���TAXII���ԣ�",
		"* IC�����ԣ��������ֱȽϼ򵥵Ŀ���",
		"* ����������ٴӴ����㷢�ͳ�����",
		"* �������ò�����",
		"* ��ʾʱ��",
		"* �豸��Ϣ���ú��������ԣ�",
	};

#ifdef	HARD_VER_090426
	while(KeyPressed())
	{
		KeyFlag = 1;
		for(i = 8 ; 0 < i;i--)
		{
			if(i>4)
			{
				j = 12 - i;
			}
			else
			{
				j = 4 - i;
			}
			
#ifdef	HARD_VER_111122
			LightLed(j);	
#else
			LightLed(i - 1);	
#endif
			printfcom0("\r\n LightLed(%u)",i);	
			EndTime = GetSysTime() + 1*100;	
			while(GetSysTime() < EndTime )
			{
				if(KeyLoosen())
				{
					KeyFlag = 2;
					printfcom0("\r\n * Input Debug State:");
					printfcom0(pString[i]);
		  			printfcom0("\r\n \r\n ");					
					break;
				}
			} 
#ifdef	HARD_VER_111122			
			UnLightLed(j);
#else			
			UnLightLed(i - 1);
#endif
			if(KeyFlag == 2)
			{
				break;
			}
		}
	}
	
	OffAllLed();
	
	if(!KeyFlag || KeyFlag != 2)								//û�а���
	{
		return;
	}
	
	switch(8 - i)
#endif

#ifdef	HARD_VER_090214
	while(KeyPressed())
	{
		KeyFlag = 1;
		for(i = 0 ; 0 < 8;i++)
		{
			LightLed(i);		
			EndTime = GetSysTime() + 1*100;	
			while(GetSysTime() < EndTime )
			{
				if(KeyLoosen())
				{
					KeyFlag = 2;
					printfcom0("\r\n * Input Debug State:");
					printfcom0(pString[i]);
		  			printfcom0("\r\n \r\n ");					
					break;
				}
			} 
			UnLightLed(i);
			if(KeyFlag == 2)
			{
				break;
			}
		}
	}
	
	OffAllLed();
	
	if(!KeyFlag || KeyFlag != 2)									//û�а���
	{
		return;
	}
	
	switch( i )	
#endif
	
	{
		case 0:	
				FactoryTest();	break;								//��������	

		case 1:	DisplayString("DIST");								//��ʾʱ��
				
				while(1)
				{	
					uint32	Time = 0;
					
					if(GetSysTime() - Time > 100)
					{
						PrintfTime();
						DisplayTime();
					}
					
//					SysHoldTast();
				}
				
				break;
//---------------------------------------------				
		case 2:		
				DisplayString("FOUT");	
				OpenCOM0(57600);									//�򿪴���0
				PrintfAllFlshRec();
				while(1);
				break;
//---------------------------------------------				
		case 3:
				DisplayString("CMOD");							
		
				DelayX10ms(100);
		
				//COM0GetModelCard();
						
				break;
//---------------------------------------------				
		case 4: 
				DisplayString("CSET");								//��ʾʱ��
		
				while(1)	
				{
					while(!PlugICCard())
					{;}		
					
						
					DisplayString("OILS");							//ģ��
					WriteCardOilModelTest();				
					printfcom0("\r\n WriteCardOilModelTest\r\n ");					
					DelayX10ms(200);	
					
					DisplayString("DATA");							//����
					printfcom0("\r\n WriteCardDataCardTest\r\n ");					
					WriteCardDataCardTest();
					DelayX10ms(200);	
						
					//DisplayString("TIME");						//ʱ��
					//printfcom0("\r\n WriteCardTimeCardTest\r\n ");					
					//WriteCardTimeCardTest();
					//DelayX10ms(200);
					
					DisplayString("DENS");							//�ܶ�
					printfcom0("\r\n WriteDensityCardTest\r\n ");					
					WriteDensityCardTest();
					DelayX10ms(200);	

					DisplayString("DDNS");							//�ܶ�+����
					printfcom0("\r\n WriteDensityCardTest\r\n ");					
					WriteDenDataCardTest();
					DelayX10ms(200);	
					
					DisplayString("DDHS");							//�ܶ�+����+gao
					printfcom0("\r\n WriteDensityCardTest\r\n ");					
					WriteDenDataCardTest();
					DelayX10ms(200);	
								
					DisplayString("COPY");							//���ƿ�
					printfcom0("\r\n WriteCopyCardTest\r\n ");					
					WriteCopyCardTest();
					DelayX10ms(400);	

					DisplayString("FRMC");							//���ƿ�
					WriteCopyFramTest();
					printfcom0("\r\n WriteCopyFramTest\r\n ");					
					DelayX10ms(200);	
					
					DisplayString("SETV");							//������
					WritesSetDipCardTest();
					printfcom0("\r\n WritesSetDipCardTest\r\n ");					
					DelayX10ms(200);	
									
					DisplayString("TEST");							//������
					WritesTestCardTest();
					printfcom0("\r\n WritesTestCardTest\r\n ");					
					DelayX10ms(200);	
									
					DisplayString("SETC");							//
					WriteCardComModelTest();
					printfcom0("\r\n WriteCardComModelTest\r\n ");					
					DelayX10ms(200);	
					
					DisplayString("TIMA");							//����ģ�Ϳ� 
					WriteExpandAddTest();
					printfcom0("\r\n WriteExpandAddTest\r\n ");					
					DelayX10ms(200);		
									
					DisplayString("TIMS");							//����ģ�Ϳ�
					WriteExpandSubTest();
					printfcom0("\r\n WriteCardComModelTest\r\n ");		
								
					DelayX10ms(200);						DisplayString("RIND");							//������
					printfcom0("\r\n ReadCardIndexTest\r\n ");					
					ReadCardIndexTest();
					DelayX10ms(500);										
				}	
		break;
//---------------------------------------------				
		case 5:
				DisplayString("C0-0.");							
				
				printfcom0("\r\n ���������TAX����Ϣ������0�Բ�����28800ת��TAX����Ϣ;\r\n ");					
				
				//COM0SendCardFlg();
				OpenTax2();											//��TAX2ͨ��

				while(1)
				{						
					TestTAX2Info();				
				}
				break;
				/*
				DisplayString("FTOC");							

				g_LshRedFlshRecNum 	= 0;

				while(!PlugICCard())
				{;}		
				
				FramToCard();
				
				DisplayString("FTRA");							

				while(1)
				{;}
				*/
		break;
//---------------------------------------------		
		case 6:
				
				
				DisplayString("C0-0");	
				OpenTax2();											//��TAX2ͨ��

				while(1)
				{						
					COM0ToCOM0();
				}
		
				//DisplayString("TEST");							
				
				//g_TestModelFlg = 1;
				/**/
				//DisplayString("PARR");	
				
				//DataCardPartRead();
								
				DelayX10ms(200);
				break;
		break;
//---------------------------------------------	
		case 7:
				DisplayString("SMOD");							

				printfcom0("\r\n ���Դ�����������ģ��");
				while(1)
				{
				//	COM0SetModel();
				}
				break;				
		break;
//---------------------------------------------	
				
		default:
		break;
	}
}
/**/