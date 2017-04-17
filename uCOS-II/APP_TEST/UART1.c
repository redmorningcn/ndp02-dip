#include <includes.h>


#define		TXD1				15
#define		RXD1				16
#define		EN_485_1 			122
#define		COM1_FRAM_END		0x2c
#define		COM1_FRAM_END0		0x10

#define 	UART1_BPS     		9600                   	/* ����ͨ�Ų�����               */
#define     COM1_REVBUF_LEN		256        					//���ڽ���

static		stcFIFO     sUART1RecFIFO;                          //���崮��0����FIFO�ṹ
static		uint8       UART1RecBuf[COM1_REVBUF_LEN];           //������ջ�����
uint8		l_COM1TempRev;
uint8       RecNumCOM1;                                 /* ���ڽ������ݵĸ���           */
uint8		l_COM1EndFlg = 0;
uint32		l_COM1ConnTime = 0;
uint8		l_COM1StartFlg = 0;
uint8		l_COM1TimeOutFlg = 0;
uint8		l_COM1FramRecEndFlg = 0;


void WriteEN_485_1(uint8 temp)
{	
	if(temp)		
	{
		GPIO_SetOrClearValue(EN_485_1,1);
	}
	else
	{
		GPIO_SetOrClearValue(EN_485_1,0);		
	}	
}

uint8	Com1RecTmp0 = 0,Com1RecTmp1 = 0,Com1RecTmp2 = 0;
uint8	com1framend0times = 0;
/*********************************************************************************************************
* Function Name:        UART1_IRQHandler
* Description:          UART1 �жϴ�����
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void UART1_IRQHandler (void)
{
   RecNumCOM1 = 0;
       
    while ((LPC_UART1->IIR & 0x01) == 0){                               /*  �ж��Ƿ����жϹ���          */
       	l_COM1ConnTime = GetSysTime();
		l_COM1StartFlg = 1;
		//l_COM1TimeOutFlg = 0;

	    switch (LPC_UART1->IIR & 0x0E){                                 /*  �ж��жϱ�־                */
        
            case 0x04:                                                  /*  ���������ж�                */
                for (RecNumCOM1 = 0; RecNumCOM1 < 8; RecNumCOM1++){                 /*  ��������8���ֽ�             */
								l_COM1TempRev = LPC_UART1->RBR;                    	//ע���U0RBR����ս����жϱ�־
								WriteFIFO((stcFIFO *)&sUART1RecFIFO,(uint8 *)&l_COM1TempRev,1); 
								
								//printfCOM1("%c",l_COM1TempRev);
								Com1RecTmp2 = Com1RecTmp1;
								Com1RecTmp1 = Com1RecTmp0;
								Com1RecTmp0	= l_COM1TempRev;
					
												
								if(		(Com1RecTmp0 == COM1_FRAM_END)
									 && (Com1RecTmp1 == COM1_FRAM_END0)
									 && (Com1RecTmp2 != COM1_FRAM_END0) 
									 )
									{
										//if(com1framend0times % 2)
										{
											l_COM1FramRecEndFlg = 1;							//֡������ɣ���־λ��ֵ	
										}
									}
								
//									if(l_COM1TempRev == COM1_FRAM_END0)		
//									{
//										com1framend0times++;
//									}	
//									else
//									{
//										com1framend0times = 0;
//									}
                }
                break;
            
            case 0x0C:                                                  /*  �ַ���ʱ�ж�                */
                while ((LPC_UART1->LSR & 0x01) == 0x01){                /*  �ж������Ƿ�������        */ 
			        l_COM1TempRev = LPC_UART1->RBR;                    	//ע���U0RBR����ս����жϱ�־
    				WriteFIFO((stcFIFO *)&sUART1RecFIFO,(uint8 *)&l_COM1TempRev,1);    
					//printfCOM1("%c",l_COM1TempRev);

					Com1RecTmp2 = Com1RecTmp1;
					Com1RecTmp1 = Com1RecTmp0;
					Com1RecTmp0	= l_COM1TempRev;

					if(		(Com1RecTmp0 == COM1_FRAM_END)
						 && (Com1RecTmp1 == COM1_FRAM_END0)
						 && (Com1RecTmp2 != COM1_FRAM_END0) 
						)
					{
						//if(com1framend0times %2 )
						{
							l_COM1FramRecEndFlg = 1;							//֡������ɣ���־λ��ֵ	
						}
					}  

//					if(l_COM1TempRev == COM1_FRAM_END0)		
//					{
//						com1framend0times++;
//					}	
//					else
//					{
//						com1framend0times = 0;
//					}
				}
				l_COM1TimeOutFlg = 1;
				//printfcom0("\r\n TimeOut");
                break;
                
            default:
                break;
        }
    } 
}
 
void	HoldCOM1ConnSta(void)
{
	if(((GetSysTime()-l_COM1ConnTime) > 3 && l_COM1StartFlg == 1 )
		||(l_COM1TimeOutFlg == 1)
		)
	{
		//printfcom0("\r\n GetSysTime() %d,%d,%d,%d, ",GetSysTime(),l_COM1ConnTime,l_COM1TimeOutFlg,l_COM1StartFlg);
		l_COM1EndFlg = 1;
		l_COM1StartFlg = 0;
		l_COM1TimeOutFlg = 0;
		//printfcom0("\r\n GetSysTime() %d,%d,%d,%d,%d, ",GetSysTime(),l_COM1ConnTime,l_COM1TimeOutFlg,l_COM1StartFlg,l_COM1EndFlg);
	}
}
 
uint8	GetCOM1FramRecEndFlg(void)
{
	return	l_COM1FramRecEndFlg;
}

void	ClearCOM1FramRecEndFlg(void)
{
	l_COM1FramRecEndFlg = 0;
}

uint8	GetCOM1EndFlg(void)
{
	HoldCOM1ConnSta();
	if(GetCOM1FramRecEndFlg())
	{
		//printfcom0("\r\n GetCOM1FramRecEndFlg %d",GetCOM1FramRecEndFlg());
		return GetCOM1FramRecEndFlg();
	}
	else
	{
		//printfcom0("\r\n l_COM1EndFlg %d",l_COM1EndFlg);
		return l_COM1EndFlg;
	}
}

void	ClearCOM1EndFlg(void)
{
	l_COM1EndFlg 	= 0;
	l_COM1StartFlg 	= 0;
	l_COM1TimeOutFlg = 0;

	ClearCOM1FramRecEndFlg();
}  



/*********************************************************************************************************
** Function name:     	uartInit
** Descriptions:	    ���ڳ�ʼ��������Ϊ8λ����λ��1λֹͣλ������żУ�飬������Ϊ115200
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void UART1Init (void)
{
	UART_CFG_Type		UART_ConfigStruct_Test;
	UART_FIFO_CFG_Type 	FIFOCfg_Test;
	UART_INT_Type 		UARTIntCfg_Test;

	GPIO_PinselConfig(RXD1,1);
	GPIO_PinselConfig(TXD1,1);	
	GPIO_PinselConfig(EN_485_1,0);
	WriteEN_485_1(0);

	UART_ConfigStruct_Test.Baud_rate = UART1_BPS;
	UART_ConfigStruct_Test.Databits = UART_DATABIT_8;
	UART_ConfigStruct_Test.Parity = UART_PARITY_NONE;
	UART_ConfigStruct_Test.Stopbits = UART_STOPBIT_1;
	
	UART_Init((LPC_UART_TypeDef *)LPC_UART1,(UART_CFG_Type *)&UART_ConfigStruct_Test);
	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART1,ENABLE);

	FIFOCfg_Test.FIFO_DMAMode = DISABLE;
	FIFOCfg_Test.FIFO_Level = UART_FIFO_TRGLEV2;
	FIFOCfg_Test.FIFO_ResetRxBuf = ENABLE;
	FIFOCfg_Test.FIFO_ResetTxBuf = ENABLE;	
	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART1, (UART_FIFO_CFG_Type *)&FIFOCfg_Test);

	UARTIntCfg_Test = UART_INTCFG_RBR;	
	UART_IntConfig((LPC_UART_TypeDef *)LPC_UART1, UARTIntCfg_Test,ENABLE);

	InitFIFO((stcFIFO *)&sUART1RecFIFO,UART1RecBuf,sizeof(UART1RecBuf));

	NVIC_EnableIRQ(UART1_IRQn);
	NVIC_SetPriority(UART1_IRQn, UART1_IRQn);									
}

void	SetCOM1Bout(uint32	bount)
{
	UART_CFG_Type		UART_ConfigStruct_Test;

	UART_ConfigStruct_Test.Baud_rate = bount;
	UART_ConfigStruct_Test.Databits = UART_DATABIT_8;
	UART_ConfigStruct_Test.Parity = UART_PARITY_NONE;
	UART_ConfigStruct_Test.Stopbits = UART_STOPBIT_1;
	
	UART_Init((LPC_UART_TypeDef *)LPC_UART1,(UART_CFG_Type *)&UART_ConfigStruct_Test);
	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART1,ENABLE);		
}

uint32 ReadCOM1(uint8 *buf,uint32 len) 
{
    uint32 RealLen;                                             //ʵ�ʶ��ĳ���
    uint32 RevBufLen;                                           //����д���ֵ,�������������ܳ���

    RevBufLen = GetNoReadSizeFIFO((stcFIFO *)&sUART1RecFIFO);   //��û�ж�ȡ�ռ����ݸ���
    
    if(RevBufLen > len)
    {
        RealLen = len;                                  		//��ȡ��Ҫ������ݳ���
    }
    else
    {
        RealLen = RevBufLen;                        			//��ȡʵ�����ݳ���
    }
    
    ReadFIFO((stcFIFO *)&sUART1RecFIFO,buf,RealLen);

    return RealLen;
}

uint32 ReadCOM1NoClear(uint8 *buf,uint32 len) 
{
    uint32 RealLen;                                             //ʵ�ʶ��ĳ���
    uint32 RevBufLen;                                           //����д���ֵ,�������������ܳ���

    RevBufLen = GetNoReadSizeFIFO((stcFIFO *)&sUART1RecFIFO);   //��û�ж�ȡ�ռ����ݸ���
    
    if(RevBufLen > len)
    {
        RealLen = len;                                  		//��ȡ��Ҫ������ݳ���
    }
    else
    {
        RealLen = RevBufLen;                        			//��ȡʵ�����ݳ���
    }
    
    OnlyReadFIFO((stcFIFO *)&sUART1RecFIFO,buf,RealLen);

    return RealLen;
}

uint8	GetUART1Status(void)
{
	return	UART_GetLineStatus((LPC_UART_TypeDef *)LPC_UART1);
}

uint8 SendCOM1(void *buf,uint32 len)
{
	uint8	station;
    if( (!len) )
    {
        return FALSE;
    }   

	station = GetUART1Status();
	while(!(station & (0x01<<6)))
	{
		station = GetUART1Status();
	}

	WriteEN_485_1(1);

	UART_Send((LPC_UART_TypeDef *)LPC_UART1,buf,len,BLOCKING);

	station = GetUART1Status();
	while(!(station & (0x01<<6)))
	{
		station = GetUART1Status();
	}

	WriteEN_485_1(0);    

    return TRUE;   
}

uint8	SendCOM1s(void *buf)
{
	UARTPuts((LPC_UART_TypeDef *)LPC_UART1,buf);
	return	1;
}





