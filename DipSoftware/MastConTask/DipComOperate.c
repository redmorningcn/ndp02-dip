#include <includes.h>


uint8	l_led0com1flg = 0;

StrDipCommData	l_sDip1CommData,l_sDip2CommData;

/////////////////////////////////////////
unsigned int GetDipVal(void)
{
	unsigned int  dipval;
	dipval = g_DipVal;
	return dipval;
}

short	GetAddSpeed(void)
{
	short addspeed;
	if(GetMyAddSpeed1())
	{
		if( GetMyAddSpeed1() )
		{
			addspeed = GetMyAddSpeed1();
		}
	}
	else
	{
		if( GetMyAddSpeed2() )
		{
			addspeed = GetMyAddSpeed2();
		}
	}

	while(abs(addspeed) > 0x10000 )
	{
		printfcom0("\r\n addspeed %d",addspeed);
		addspeed /=10;
	}
	return addspeed;
}

unsigned short GetSpeed(void)
{
	unsigned short speed;
	
	if(GetMySpeed1() && GetMySpeed2())
	{
		speed = (GetMySpeed1()+GetMySpeed2())/2;
	}
	else  if(GetMySpeed1() )
	{
		speed = GetMySpeed1(); 	
	}
	else if(GetMySpeed2() )
	{
		speed = GetMySpeed2(); 	
	}
	else
	{
		speed = 0;	
	}
	return	speed;
}

//unsigned char GetLocoSta(void)
//{
//	unsigned char locosta;
//	
//	locosta = 1;
//	return  locosta;
//}

//////////////////////////////////////////
uint8	GetFramRecEndFlgDip(void)
{
	return GetCOM1EndFlg();
}

//�������ɱ�־  ����
void	ClearFramRecEndFlgDip(void)
{
	ClearCOM1EndFlg();
}

uint16	ReadRs485DataDip(uint8 *Buf)
{
	return	ReadCOM1(Buf,64);
}


uint8	l_recaddrdip = 0;
unsigned char GetRecaddrDip()
{
	return	l_recaddrdip;
}

unsigned char l_com1dip1Errflg = 0;
unsigned char l_com1dip2Errflg = 0;

unsigned char l_com1SetModelflg = 0;


uint8	GetCom1Dip1ErrFlg(void)
{
	return	l_com1dip1Errflg;	
}

uint8	GetCom1Dip2ErrFlg(void)
{
	return	l_com1dip2Errflg;	
}

unsigned char l_recFlgdip = 0;
unsigned char GetRecFlgdip(void)
{
	return l_recFlgdip;
}



void DipComOperate(unsigned char *buf,unsigned int Len)		
{
	short			hig;
	unsigned short 	den;
	unsigned char	sta;
	char			tmp;
	static	unsigned int	dip1time,dip2time;

	unsigned int   datalen = 0;
	
//	memcpy((unsigned char *)&hig,&buf[datalen],sizeof(hig));
	hig = buf[datalen]*256 + buf[datalen+1]; 
	datalen += sizeof(hig);

//	memcpy((unsigned char *)&den,&buf[datalen],sizeof(den));
	den = buf[datalen+1]*256 + buf[datalen]; 
	datalen += sizeof(den);

	memcpy((unsigned char *)&sta,&buf[datalen],sizeof(sta));
	datalen += sizeof(sta);

  memcpy((unsigned char *)&tmp,&buf[datalen],sizeof(tmp));
	datalen += sizeof(tmp);		
	
	if(GetRecaddrDip()==0xA1)
	{
		l_com1dip1Errflg = ~ERROR;
		l_Dip1Prs 		= hig;
		l_dip1den 		= den;
		l_Dip1ErrCod 	= sta;
		l_Dip1Tmp		= tmp;
		dip1time  		= GetSysTime(); 
		
		memcpy((uint8 *)&l_sDip1CommData,buf,sizeof(l_sDip1CommData));
		//l_sDip1CommData

//		if(l_Dip1ErrCod & 0x03 == 0x03)
//		{
//			l_Dip1Prs 
//		}

//		printfcom0("\r\n dip1 %d, %d, %d, %d,l_com1dip1Errflg %x",hig,den,sta,tmp,l_com1dip1Errflg);
	}
	else if(GetRecaddrDip()==0xA2)
	{	
		l_com1dip2Errflg = ~ERROR;

		l_Dip2Prs 		= hig;
		l_dip2den 		= den;
		l_Dip2ErrCod 	= sta;
		l_Dip2Tmp			= tmp;
		dip2time  		= GetSysTime(); 
		
		memcpy((uint8 *)&l_sDip2CommData,buf,sizeof(l_sDip2CommData));

//		printfcom0("\r\n dip2 %d, %d, %d, %d,l_com1dip2Errflg %x",hig,den,sta,tmp,l_com1dip2Errflg);
	}

	if((GetSysTime() - dip1time > 1000) )
	{
		l_com1dip1Errflg = ERROR;
	}
	if((GetSysTime() - dip2time > 1000) )
	{
		l_com1dip2Errflg = ERROR;
	}
}



#define		OIL_BOX_MODEL_ADDR				2000	//����ģ�͵�ַ	
extern	stcModelComplex	l_sModel ;	;
void	StoreSetModelVal(stcModelComplex *comsModel,unsigned char nodeletnum)
{
	uint32		i,j,z;
	stcModel 	sModel;
	uint16 		Crc16;
	
	printfcom0("\r\n��ӡ����ǰ��ģ��,������Ϊ %d",nodeletnum);
	for(i = 0 ;i < comsModel->PotNum;i++)
	{
	  printfcom0("\r\n �߶� %d,���� %d",comsModel->sModPot[i].HigVal,comsModel->sModPot[i].DipVal);
	}

	for(i = 0;i < (comsModel->PotNum-1);i++)	
	{
		if(comsModel->sModPot[i].HigVal == comsModel->sModPot[i+1].HigVal)
		{
			printfcom0("\r\n comsModel->sModPot[%d].HigVal %d == comsModel->sModPot[i+1].HigVal %d",
			i,comsModel->sModPot[i].HigVal,comsModel->sModPot[i+1].HigVal);

			z = i;
			if(nodeletnum == i)
			{				
				z++;
				printfcom0("\r\n z %d,i %d",z,i);
			}

			for(j = z;j <(comsModel->PotNum-1);j++)
			{		
				comsModel->sModPot[j].HigVal = comsModel->sModPot[j+1].HigVal;
				comsModel->sModPot[j].DipVal = comsModel->sModPot[j+1].DipVal;				
			} 	

			comsModel->PotNum = comsModel->PotNum -1;

			nodeletnum<i?nodeletnum:nodeletnum--;
		}
		else if(comsModel->sModPot[i].HigVal > comsModel->sModPot[i+1].HigVal)
		{
			printfcom0("\r\n comsModel->sModPot[%d].HigVal %d > comsModel->sModPot[i+1].HigVal %d",
			i,comsModel->sModPot[i].HigVal,comsModel->sModPot[i+1].HigVal);

			z = i;
			if(nodeletnum == i)
			{			
				z++;
				printfcom0("\r\n z %d,i %d",z,i);

			}
			for(j = z;j <(comsModel->PotNum-1);j++)
			{		
				comsModel->sModPot[j].HigVal = comsModel->sModPot[j+1].HigVal;
				comsModel->sModPot[j].DipVal = comsModel->sModPot[j+1].DipVal;	
			}	

			comsModel->PotNum = comsModel->PotNum -1;

			nodeletnum<i?nodeletnum:nodeletnum--;			
		}
		else if(comsModel->sModPot[i].HigVal < comsModel->sModPot[i+1].HigVal)
		{
			if(comsModel->sModPot[i+1].HigVal - 50 < comsModel->sModPot[i].HigVal)	//����仯����Ϊ50L
			{
				printfcom0("\r\n comsModel->sModPot[%d].HigVal %d < comsModel->sModPot[i+1].HigVal %d",
				i,comsModel->sModPot[i].HigVal,comsModel->sModPot[i+1].HigVal);
				z = i;
				if(nodeletnum == i)
				{
					z++;
					printfcom0("\r\n z %d,i %d",z,i);
				}
				for(j = z;j <(comsModel->PotNum-1);j++)
				{		
					comsModel->sModPot[j].HigVal = comsModel->sModPot[j+1].HigVal;
					comsModel->sModPot[j].DipVal = comsModel->sModPot[j+1].DipVal;
				}  
				comsModel->PotNum = comsModel->PotNum -1;

				nodeletnum<i?nodeletnum:nodeletnum--;				
			}
		}
	}


	for(i = 0;i < (comsModel->PotNum-1);i++)	
	{
		if(comsModel->sModPot[i].DipVal == comsModel->sModPot[i+1].DipVal)
		{
   			printfcom0("\r\n comsModel->sModPot[%d].DipVal %d == comsModel->sModPot[i+1].DipVal %d",
			i,comsModel->sModPot[i].DipVal,comsModel->sModPot[i+1].DipVal);
			z = i;
			if(nodeletnum == i)
			{
				z++;
				printfcom0("\r\n z %d,i %d",z,i);
			}
			for(j = z;j <(comsModel->PotNum-1);j++)
			{		
				comsModel->sModPot[j].HigVal = comsModel->sModPot[j+1].HigVal;
				comsModel->sModPot[j].DipVal = comsModel->sModPot[j+1].DipVal;
			}  	
			comsModel->PotNum = comsModel->PotNum -1;

			nodeletnum<i?nodeletnum:nodeletnum--;
		}
		else if(comsModel->sModPot[i].DipVal > comsModel->sModPot[i+1].DipVal)
		{
 			printfcom0("\r\n comsModel->sModPot[%d].DipVal %d == comsModel->sModPot[i+1].DipVal %d",
			i,comsModel->sModPot[i].DipVal,comsModel->sModPot[i+1].DipVal);		
			z = i;
			if(nodeletnum == i)
			{
				z++;
				printfcom0("\r\n z %d,i %d",z,i);
			}
			for(j = z;j <(comsModel->PotNum-1);j++)
			{		
				comsModel->sModPot[j].HigVal = comsModel->sModPot[j+1].HigVal;
				comsModel->sModPot[j].DipVal = comsModel->sModPot[j+1].DipVal;		
			}
			comsModel->PotNum = comsModel->PotNum -1;	

			nodeletnum<i?nodeletnum:nodeletnum--;		
		}
		else if(comsModel->sModPot[i].DipVal < comsModel->sModPot[i+1].DipVal)
		{
			if(comsModel->sModPot[i+1].DipVal - 50 < comsModel->sModPot[i].DipVal)	//����仯����Ϊ50L
			{
				printfcom0("\r\n comsModel->sModPot[%d].DipVal %d < comsModel->sModPot[i+1].DipVal %d",
				i,comsModel->sModPot[i].DipVal,comsModel->sModPot[i+1].DipVal);
			
				z = i;

				if(nodeletnum == i)
				{
					z++;
					printfcom0("\r\n z %d,i %d",z,i);
				}

				for(j = z;j <(comsModel->PotNum-1);j++)
				{		
					comsModel->sModPot[j].HigVal = comsModel->sModPot[j+1].HigVal;
					comsModel->sModPot[j].DipVal = comsModel->sModPot[j+1].DipVal;
				}	
				comsModel->PotNum = comsModel->PotNum -1;

				nodeletnum<i?nodeletnum:nodeletnum--;				
			}
		}
	}


//	
	sModel.ModelNum = comsModel->ModelNum;
	if(comsModel->PotNum < 50)
	{
		sModel.PotNum = comsModel->PotNum;
	}
	else
	{
		sModel.PotNum = 50;
	}
	sModel.StartHight = comsModel->StartHight;

	memcpy((uint8 *)sModel.sModPot,(uint8 *)comsModel->sModPot,sizeof(sModel.sModPot));
	if(comsModel->PotNum > 50)
	{
		sModel.sModPot[49].DipVal = comsModel->sModPot[comsModel->PotNum  -1].DipVal;	
		sModel.sModPot[49].HigVal = comsModel->sModPot[comsModel->PotNum  -1].HigVal;
	}

	Crc16 = GetCrc16Check((uint8 *)&sModel,sizeof(sModel) - 2);
	
	sModel.CrcCheck  	= Crc16;	

  	WriteFM24CL64(OIL_BOX_MODEL_ADDR,(uint8 *)&sModel, sizeof(sModel));

	printfcom0("\r\n��ӡ�������ģ��,������Ϊ %d,comsModel->PotNum %d",nodeletnum,comsModel->PotNum);
	for(i = 0 ;i < comsModel->PotNum;i++)
	{
	  printfcom0("\r\n �߶� %d,���� %d",comsModel->sModPot[i].HigVal,comsModel->sModPot[i].DipVal);
	}

}

extern	stcModelComplex	l_sModel;

uint8	l_setmodelflg = 0;
uint8	GetSetModelFlg(void)
{
	return	l_setmodelflg;
}
void	DipModelSet	(unsigned char *buf,unsigned int Len)		
{
	short			hig;
	unsigned short 	den;
	unsigned short	valadd;
	unsigned short	setnum;
	static	unsigned short   firstmodelsetval = 0;
	static	unsigned short   firstaddval = 0;
	static	short	lsthig = 0;
	static  short	lstval = 0;
	uint32	i,j;
	uint32	portnum;
	static	char	addflg = 0;

//	static	unsigned int	dip1time,dip2time;

	unsigned int   datalen = 0;
		
//	memcpy((unsigned char *)&hig,&buf[datalen],sizeof(hig));
	hig = buf[datalen]*256 + buf[datalen+1]; 
	datalen += sizeof(hig);

//	memcpy((unsigned char *)&den,&buf[datalen],sizeof(den));
	den = buf[datalen]*256 + buf[datalen+1]; 
	datalen += sizeof(den);

//	memcpy((unsigned char *)&valadd,&buf[datalen],sizeof(valadd));
	valadd = buf[datalen]*256 + buf[datalen+1]; 
	datalen += sizeof(valadd);

//  memcpy((unsigned char *)&setnum,&buf[datalen],sizeof(setnum));
	setnum = buf[datalen]*256 + buf[datalen+1]; 
	datalen += sizeof(setnum);		
	
	if(GetRecaddrDip()==0xA5)
	{
		l_setmodelflg = 1;
		printfcom0("\r\n Set %d, %d, %d, %d,l_com1dip1Errflg %x",hig,den,valadd,setnum);
		
		if(setnum == 0)
		{
			firstmodelsetval = 0;
			if(g_DipVal>valadd)
			{
				firstmodelsetval = g_DipVal-valadd;
				firstaddval      = valadd;
			}
			else
			{
				firstmodelsetval = valadd;	
				firstaddval      = valadd;
			}
			addflg = 0;
			DisplaySet(150,2,"SET_%d",setnum);
		   	printfcom0("\r\n У׼���У׼");
			GetMathModelPara((stcModelComplex *)&l_sModel,0);		//ģ�Ͳ���	
			
			portnum = l_sModel.PotNum;
			
			if(portnum > 199)
			{
				portnum = 199;	
			}

			printfcom0("\r\n portnum %d",portnum);
			for(i = portnum;i>0;i--)
			{
				if(hig < l_sModel.sModPot[i-1].HigVal)
				{
					l_sModel.sModPot[i].HigVal =  l_sModel.sModPot[i-1].HigVal;
					l_sModel.sModPot[i].DipVal =  l_sModel.sModPot[i-1].DipVal;

					if(i == 1)
					{
						l_sModel.sModPot[i-1].HigVal = hig;
						l_sModel.sModPot[i-1].DipVal = firstmodelsetval;
						l_sModel.PotNum++;

						StoreSetModelVal((stcModelComplex *)&l_sModel,i-1);
					}

					//printfcom0("\r\n i-1 %d",i-1);

					printfcom0("\r\n hig %d < l_sModel.sModPot[i-1].HigVal %d,l_sModel.PotNum %d",
											hig,l_sModel.sModPot[i-1].HigVal,l_sModel.PotNum);
				}
				else if(hig == l_sModel.sModPot[i-1].HigVal)
				{
					l_sModel.sModPot[i-1].DipVal = firstmodelsetval;
					for(j=i;j<portnum-1;j++)
					{
						l_sModel.sModPot[i].HigVal =  l_sModel.sModPot[i+1].HigVal;
						l_sModel.sModPot[i].DipVal =  l_sModel.sModPot[i+1].DipVal;
					} 

					printfcom0("\r\n i-1 %d",i-1);

					printfcom0("\r\n hig %d = l_sModel.sModPot[i-1].HigVal %d,l_sModel.PotNum %d",hig,l_sModel.sModPot[i-1].HigVal,l_sModel.PotNum);

					StoreSetModelVal((stcModelComplex *)&l_sModel,i-1);
					break;
				}
				else
				{
					l_sModel.sModPot[i].HigVal =  hig;
					l_sModel.sModPot[i].DipVal =  firstmodelsetval;

					l_sModel.PotNum ++;
					
					printfcom0("\r\n i %d",i);

					printfcom0("\r\n hig %d > l_sModel.sModPot[i-1].HigVal %d,l_sModel.PotNum %d",hig,l_sModel.sModPot[i-1].HigVal,l_sModel.PotNum);

					StoreSetModelVal((stcModelComplex *)&l_sModel,i);
					break;
				}
			}
		}
		else  if(setnum != 0xffff)	   //�����
		{
			DisplaySet(150,2,"SET_%d",setnum);

			GetMathModelPara((stcModelComplex *)&l_sModel,0);		//ģ�Ͳ���	
			
			portnum = l_sModel.PotNum;
			
			if(portnum > 199)
			{
				portnum = 199;	
			}
			
			if(abs(valadd-lstval)<50 ||abs(hig-lsthig)<50)
			{
				printfcom0("\r\n ������С valadd %d,lstval %d,hig %d,lsthig %d",valadd,lstval,hig,lsthig);
				return;
			}

			printfcom0("\r\n portnum %d",portnum);
			for(i = portnum;i>0;i--)
			{
				if(hig < l_sModel.sModPot[i-1].HigVal)
				{
					l_sModel.sModPot[i].HigVal =  l_sModel.sModPot[i-1].HigVal;
					l_sModel.sModPot[i].DipVal =  l_sModel.sModPot[i-1].DipVal;
					
					if(i == 1)
					{
						l_sModel.sModPot[i-1].HigVal = hig;
						if(hig > lsthig)
						{
							l_sModel.sModPot[i-1].DipVal = firstmodelsetval + (valadd - firstaddval);
							printfcom0("\r\n ����У׼");
						}
						else
						{
							l_sModel.sModPot[i-1].DipVal = firstmodelsetval - (valadd - firstaddval);
							printfcom0("\r\n ж��У׼");
						}
						l_sModel.PotNum ++;
					}

					printfcom0("\r\n hig %d > l_sModel.sModPot[i-1].HigVal %d,l_sModel.PotNum %d",hig,l_sModel.sModPot[i-1].HigVal,l_sModel.PotNum);

				}
				else if(hig == l_sModel.sModPot[i-1].HigVal)
				{
					if(hig > lsthig)
					{
						l_sModel.sModPot[i-1].DipVal = firstmodelsetval + (valadd - firstaddval);
						printfcom0("\r\n ����У׼");
					}
					else
					{
						l_sModel.sModPot[i-1].DipVal = firstmodelsetval - (valadd - firstaddval);
						printfcom0("\r\n ж��У׼");
					}

					for(j=i;j<portnum-1;j++)
					{
						l_sModel.sModPot[i].HigVal =  l_sModel.sModPot[i+1].HigVal;
						l_sModel.sModPot[i].DipVal =  l_sModel.sModPot[i+1].DipVal;
					} 

					printfcom0("\r\n hig %d = l_sModel.sModPot[i-1].HigVal %d,l_sModel.PotNum %d",hig,l_sModel.sModPot[i-1].HigVal,l_sModel.PotNum);

					StoreSetModelVal((stcModelComplex *)&l_sModel,i-1);
					break;
				}
				else
				{

					l_sModel.sModPot[i].HigVal =  hig;
					if(hig > lsthig)
					{
						l_sModel.sModPot[i].DipVal = firstmodelsetval + (valadd - firstaddval);
						printfcom0("\r\n ����У׼");
					}
					else
					{
						l_sModel.sModPot[i].DipVal = firstmodelsetval - (valadd - firstaddval);
						printfcom0("\r\n ж��У׼");
					}

					l_sModel.PotNum ++;

					printfcom0("\r\n hig %d < l_sModel.sModPot[i-1].HigVal %d,l_sModel.PotNum %d",hig,l_sModel.sModPot[i-1].HigVal,l_sModel.PotNum);

					StoreSetModelVal((stcModelComplex *)&l_sModel,i);
					break;
				}
			}
		}

		lsthig = hig;
		lstval = valadd;

	}
}

unsigned char sentendflgdip = 0;
void HostScanDip(void)
{
	static	unsigned char 	tmp = 0;
	static	unsigned int 	time = 0;
	unsigned char 		 	ScanAddrList[9]={0xA1,0xA2,0xA3,0xA5};
	unsigned char   		buf[12];
	unsigned char 			datalen;
	
	unsigned int            dipval;
	short                   addspeed;
	unsigned short			speed;
	unsigned char           locosta;
	unsigned char           tmpbuf[3]={0};
	
	if(		GetSysTime() - time > 50 
		|| (GetRecFlgdip() && (GetSysTime() - time > 10))
		)
	{
		time 	= GetSysTime(); 
		datalen = 0;
		
//		dipval = g_DipVal;	  	//

#ifdef	CVISOFT
		dipval = GetDipVal();
		memcpy(&buf[datalen],(unsigned char *)&dipval,sizeof(dipval));
		datalen += sizeof(dipval);
		
		addspeed = GetAddSpeed();
		memcpy(&buf[datalen],(unsigned char *)&addspeed,sizeof(addspeed));
		datalen += sizeof(addspeed);
		
		speed = GetSpeed();
		memcpy(&buf[datalen],(unsigned char *)&speed,sizeof(speed));
		datalen += sizeof(speed);
		
		locosta = GetMyLocoWorkState();
		memcpy(&buf[datalen],(unsigned char *)&locosta,sizeof(locosta));
		datalen += sizeof(locosta);

		memcpy(&buf[datalen],tmpbuf,sizeof(tmpbuf));
		datalen += sizeof(tmpbuf);
#endif		
		dipval = GetDipVal();
		//memcpy(&buf[datalen],(unsigned char *)&dipval,sizeof(dipval));
		buf[datalen] 	= dipval>>24;
		buf[datalen+1] 	= dipval>>16;
		buf[datalen+2] 	= dipval>>8;
		buf[datalen+3] 	= dipval>>0;

		datalen += sizeof(dipval);
		
		addspeed = GetAddSpeed();
//		memcpy(&buf[datalen],(unsigned char *)&addspeed,sizeof(addspeed));
		buf[datalen] 	= addspeed>>8;
		buf[datalen+1] 	= addspeed>>0;

		datalen += sizeof(addspeed);
		
		speed = GetSpeed();
//		memcpy(&buf[datalen],(unsigned char *)&speed,sizeof(speed));
		buf[datalen] 	= speed>>8;
		buf[datalen+1] 	= speed>>0;

		datalen += sizeof(speed);
		
		locosta = GetMyLocoWorkState();
		memcpy(&buf[datalen],(unsigned char *)&locosta,sizeof(locosta));
		datalen += sizeof(locosta);

		memcpy(&buf[datalen],tmpbuf,sizeof(tmpbuf));
		datalen += sizeof(tmpbuf);

		DataSend_CSNR(0x80,ScanAddrList[tmp%4],(unsigned char *)&buf,datalen);

		tmp++;
		sentendflgdip = 1;
		l_recFlgdip 	= 0;
		DelayX10ms(1);
	}
}


void  CSNR_RecDealDip(void)     												//����
{
	unsigned char		RecBuf[64] = {0};								//���ջ�����
	unsigned char		DataBuf[64] = {0};								//
	unsigned int		RecLen;		
	unsigned int		DataLen = 16;
	static	uint32		rectime = 0;
	static	uint8		errtimes;
	static	uint32		errtime;		
			
	if( GetFramRecEndFlgDip() == 1 && sentendflgdip == 1)						//���µ�֡β���������ݴ���	  ////////////////////////
	{
		rectime = GetSysTime();
		errtimes = 0;

//		l_led0com1flg = COM_LED_REC;
		l_recFlgdip = 1;
		sentendflgdip = 0;  
																										//����ָ��󣬵ȴ�����
		RecLen 	= ReadRs485DataDip(RecBuf);
		
		ClearFramRecEndFlgDip();												//���־��������ȡ��
		
		if(RecLen < 10)
			return ;
		
		l_recaddrdip = CSNR_GetData(RecBuf,RecLen,DataBuf,(unsigned char*)&DataLen); 
	
//	����ת�����������δ��ͨѶЭ��Ҫ����Ӵ���2��3������		
		if(l_recaddrdip == 0)
		{
			SendCOM2(RecBuf,RecLen);
			SendCOM3(RecBuf,RecLen);
			return	;
		}
		
		switch(l_recaddrdip)
		{
			case 0xA1: 
						l_led0com1flg =  COM_LED_DATA;
					   	DipComOperate(DataBuf,DataLen); 				//�������Խ��յ���Ϣ���д��� 
				break;
				
			case 0xA2: 
						l_led0com1flg =  COM_LED_DATA;
					   	DipComOperate(DataBuf,DataLen); 				//�������Խ��յ���Ϣ���д��� 
				break;

			case 0xA5: 
						l_led0com1flg =  COM_LED_DATA;
					 //  	DipModelSet(DataBuf,DataLen); 				//�������Խ��յ���Ϣ���д��� 
				break;

			default: ;
		}
	}
	else
	{
		if(GetSysTime() - rectime > 100)
		{
			if(GetSysTime() - errtime > 100 )
			{
					errtimes++;
			    errtime	= GetSysTime();
			}
			if(errtimes	> 3)
			{
				l_led0com1flg	= 0; 
	
				l_com1dip1Errflg = ERROR;
				l_com1dip2Errflg = ERROR;
			}
		}
	}
}

uint8	GetLed0Com1Flg(void)
{
	return	 l_led0com1flg;
}


extern  uint8  GetCOM1Data(void);

void Diptask(void)
{
    static  int     time;

    HostScanDip();                  //������
    
    CSNR_RecDealDip();              //���մ���

//	if(GetSysTime() - time > 200)   //2sһ��
//    {
//        SendReadPowerCode();        //������
//        time = GetSysTime();
//    }
    
    GetCOM1Data();                  //ȡ��������
    
//    MathPower();                    //�������
}
