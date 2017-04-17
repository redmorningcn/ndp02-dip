#include <includes.h>

#define		TXD2									10
#define		RXD2									11
#define		EN_485_2							128
#define		COM2_FRAM_END					0x2c
#define		COM2_FRAM_END0				0x10

#define 	UART2_BPS        			57600               		/* ����ͨ�Ų�����               */
#define     COM2_REVBUF_LEN   	256        				//���ڽ���

static		stcFIFO     sUART2RecFIFO;            		//���崮��0����FIFO�ṹ
static		uint8       UART2RecBuf[COM2_REVBUF_LEN]; 	//������ջ�����
uint8		l_COM2TempRev;
uint8       RecNumCOM2;                                 /* ���ڽ������ݵĸ���           */
uint8		l_COM2EndFlg   = 0;
uint32		l_COM2ConnTime = 0;
uint8		l_COM2StartFlg = 0;
uint8		l_COM2TimeOutFlg = 0;
uint8		l_COM2FramRecEndFlg = 0;


void WriteEN_485_2(uint8 temp)
{	
	if(temp)		
	{
		GPIO_SetOrClearValue(EN_485_2,1);
	}
	else
	{
		GPIO_SetOrClearValue(EN_485_2,0);		
	}	
}

uint8	com2RecTmp0 = 0,com2RecTmp1 = 0,com2RecTmp2 = 0;
uint8 com2framend0times = 0;
/*********************************************************************************************************
* Function Name:        UART2_IRQHandler
* Description:          UART2 �жϴ�����
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void UART2_IRQHandler (void)
{
   RecNumCOM2 = 0;
       
    while ((LPC_UART2->IIR & 0x01) == 0){                               /*  �ж��Ƿ����жϹ���          */
       	l_COM2ConnTime = GetSysTime();
		l_COM2StartFlg = 1;
		//l_COM2TimeOutFlg = 0;

	    switch (LPC_UART2->IIR & 0x0E){                                 /*  �ж��жϱ�־                */
        
            case 0x04:                                                  /*  ���������ж�                */
                for (RecNumCOM2 = 0; RecNumCOM2 < 8; RecNumCOM2++){                 /*  ��������8���ֽ�             */
			        l_COM2TempRev = LPC_UART2->RBR;                    	//ע���U0RBR����ս����жϱ�־
							WriteFIFO((stcFIFO *)&sUART2RecFIFO,(uint8 *)&l_COM2TempRev,1); 
								
							//com2RecTmp3 = com2RecTmp2;
							com2RecTmp2 = com2RecTmp1;
							com2RecTmp1 = com2RecTmp0;
							com2RecTmp0	= l_COM2TempRev;

							if(		(com2RecTmp0 == COM2_FRAM_END)
								 && (com2RecTmp1 == COM2_FRAM_END0)
								 &&	(				com2RecTmp2 	!= COM2_FRAM_END0  
											//	|| (com2RecTmp2 	== COM2_FRAM_END0 && com2RecTmp3 == COM2_FRAM_END0) 
										)
								)
									{
//										if(com2framend0times %2 )
										{
											l_COM2FramRecEndFlg = 1;							//֡������ɣ���־λ��ֵ	
										}
									}
                }
								
//								if(l_COM2TempRev == COM2_FRAM_END0)		
//								{
//									com2framend0times++;
//								}	
//								else
//								{
//									com2framend0times = 0;
//								}
                break;
            
            case 0x0C:                                                  /*  �ַ���ʱ�ж�                */
                while ((LPC_UART2->LSR & 0x01) == 0x01){                /*  �ж������Ƿ�������        */ 
								l_COM2TempRev = LPC_UART2->RBR;                    	//ע���U0RBR����ս����жϱ�־
								WriteFIFO((stcFIFO *)&sUART2RecFIFO,(uint8 *)&l_COM2TempRev,1);    


					com2RecTmp2 = com2RecTmp1;
					com2RecTmp1 = com2RecTmp0;
					com2RecTmp0	= l_COM2TempRev;

					if(		(com2RecTmp0 == COM2_FRAM_END)
						 && (com2RecTmp1 == COM2_FRAM_END0)
						 && (com2RecTmp2 != COM2_FRAM_END0) )
					{
	//					if(com2framend0times %2)
						{
							l_COM2FramRecEndFlg = 1;							//֡������ɣ���־λ��ֵ
						}							
					}
					
//					if(l_COM2TempRev == COM2_FRAM_END0)		
//					{
//						com2framend0times++;
//					}	
//					else
//					{
//						com2framend0times = 0;
//					}
				}
				l_COM2TimeOutFlg = 1;
                break;
                
            default:
                break;
        }
    } 
}
 
void	HoldCOM2ConnSta(void)
{
	if((GetSysTime()-l_COM2ConnTime > 2 && l_COM2StartFlg == 1 )
		||(l_COM2TimeOutFlg == 1))
	{
		l_COM2EndFlg = 1;
		l_COM2StartFlg = 0;
		l_COM2TimeOutFlg = 0;
	}
}

uint8	GetCOM2FramRecEndFlg(void)
{
	return	l_COM2FramRecEndFlg;
}

void	ClearCOM2FramRecEndFlg(void)
{
	l_COM2FramRecEndFlg = 0;
} 

uint8	GetCOM2EndFlg(void)
{
	HoldCOM2ConnSta();
	if(GetCOM2FramRecEndFlg())
	{
		//printfcom0("\r\n GetCOM1FramRecEndFlg %d",GetCOM1FramRecEndFlg());
		return GetCOM2FramRecEndFlg();
	}
	else
	{
		return l_COM2EndFlg;
	}
}

void	ClearCOM2EndFlg(void)
{
	l_COM2EndFlg 	= 0;
	l_COM2StartFlg 	= 0;
	l_COM2TimeOutFlg = 0;

	ClearCOM2FramRecEndFlg();
}  

/*********************************************************************************************************
** Function name:     	uartInit
** Descriptions:	    ���ڳ�ʼ��������Ϊ8λ����λ��1λֹͣλ������żУ�飬������Ϊ115200
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void UART2Init (void)
{
	UART_CFG_Type		UART_ConfigStruct_Test;
	UART_FIFO_CFG_Type 	FIFOCfg_Test;
	UART_INT_Type 		UARTIntCfg_Test;

	GPIO_PinselConfig(RXD2,1);
	GPIO_PinselConfig(TXD2,1);	
	GPIO_PinselConfig(EN_485_2,0);
	WriteEN_485_2(0);

	UART_ConfigStruct_Test.Baud_rate = UART2_BPS;
	UART_ConfigStruct_Test.Databits = UART_DATABIT_8;
	UART_ConfigStruct_Test.Parity = UART_PARITY_NONE;
	UART_ConfigStruct_Test.Stopbits = UART_STOPBIT_1;
	
	UART_Init((LPC_UART_TypeDef *)LPC_UART2,(UART_CFG_Type *)&UART_ConfigStruct_Test);
	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART2,ENABLE);

	FIFOCfg_Test.FIFO_DMAMode = DISABLE;
	FIFOCfg_Test.FIFO_Level = UART_FIFO_TRGLEV2;
	FIFOCfg_Test.FIFO_ResetRxBuf = ENABLE;
	FIFOCfg_Test.FIFO_ResetTxBuf = ENABLE;	
	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART2, (UART_FIFO_CFG_Type *)&FIFOCfg_Test);

	UARTIntCfg_Test = UART_INTCFG_RBR;	
	UART_IntConfig((LPC_UART_TypeDef *)LPC_UART2, UARTIntCfg_Test,ENABLE);
 	
	InitFIFO((stcFIFO *)&sUART2RecFIFO,UART2RecBuf,sizeof(UART2RecBuf));

	NVIC_EnableIRQ(UART2_IRQn);
	NVIC_SetPriority(UART2_IRQn, UART2_IRQn);									
}

uint32 ReadCOM2(uint8 *buf,uint32 len) 
{
    uint32 RealLen;                                             //ʵ�ʶ��ĳ���
    uint32 RevBufLen;                                           //����д���ֵ,�������������ܳ���

    RevBufLen = GetNoReadSizeFIFO((stcFIFO *)&sUART2RecFIFO);   //��û�ж�ȡ�ռ����ݸ���

    if(RevBufLen > len)
    {
        RealLen = len;                                  		//��ȡ��Ҫ������ݳ���
    }
    else
    {
        RealLen = RevBufLen;                        			//��ȡʵ�����ݳ���
    }
    
    ReadFIFO((stcFIFO *)&sUART2RecFIFO,buf,RealLen);

    return RealLen;
}

uint32 ReadCOM2NoClear(uint8 *buf,uint32 len) 
{
    uint32 RealLen;                                             //ʵ�ʶ��ĳ���
    uint32 RevBufLen;                                           //����д���ֵ,�������������ܳ���

    RevBufLen = GetNoReadSizeFIFO((stcFIFO *)&sUART2RecFIFO);   //��û�ж�ȡ�ռ����ݸ���
    
    if(RevBufLen > len)
    {
        RealLen = len;                                  		//��ȡ��Ҫ������ݳ���
    }
    else
    {
        RealLen = RevBufLen;                        			//��ȡʵ�����ݳ���
    }
    
    OnlyReadFIFO((stcFIFO *)&sUART2RecFIFO,buf,RealLen);

    return RealLen;
}

uint8	GetUART2Status(void)
{
	return	UART_GetLineStatus((LPC_UART_TypeDef *)LPC_UART2);
}

uint8 SendCOM2(void *buf,uint32 len)
{
	uint8	station;
    if( (!len) )
    {
        return FALSE;
    }   

	station = GetUART2Status();
	while(!(station & (0x01<<6)))
	{
		station = GetUART2Status();
	}

	WriteEN_485_2(1);

	UART_Send((LPC_UART_TypeDef *)LPC_UART2,buf,len,BLOCKING);

	station = GetUART2Status();
	while(!(station & (0x01<<6)))
	{
		station = GetUART2Status();
	}

	WriteEN_485_2(0);    

    return TRUE;   
}

uint8	SendCOM2s(void *buf)
{
	UARTPuts((LPC_UART_TypeDef *)LPC_UART2,buf);
	return 1;
}

