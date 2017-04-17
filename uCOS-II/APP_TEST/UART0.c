#include <includes.h>


#define		TXD0	2
#define		RXD0	3
#define		EN_485_0		27
#define		COM0_FRAM_END	0x7e

#define 	UART0_BPS     	115200                                    	/* ����ͨ�Ų�����               */
#define   COM0_REVBUF_LEN	256        				//���ڽ���


static		stcFIFO     sUART0RecFIFO;                          //���崮��0����FIFO�ṹ
static		uint8       UART0RecBuf[COM0_REVBUF_LEN];           //������ջ�����
uint8		l_COM0TempRev;
uint8       RecNumCOM0;                                 /* ���ڽ������ݵĸ���           */
uint8		l_COM0EndFlg = 0;
uint32		l_COM0ConnTime = 0;
uint8		l_COM0StartFlg = 0;
uint8		l_COM0TimeOutFlg = 0;
uint8		l_COM0FramRecEndFlg = 0;

void WriteEN_485_0(uint8 temp)
{	
	if(temp)		
	{
		GPIO_SetOrClearValue(EN_485_0,1);
	}
	else
	{
		GPIO_SetOrClearValue(EN_485_0,0);		
	}	
}

/*********************************************************************************************************
* Function Name:        UART0_IRQHandler
* Description:          UART0 �жϴ�����
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void UART0_IRQHandler (void)
{
   RecNumCOM0 = 0;
       
    while ((LPC_UART0->IIR & 0x01) == 0){                               /*  �ж��Ƿ����жϹ���          */
       	l_COM0ConnTime = GetSysTime();
		l_COM0StartFlg = 1;
		//l_COM0TimeOutFlg = 0;

	    switch (LPC_UART0->IIR & 0x0E){                                 /*  �ж��жϱ�־                */
        
            case 0x04:                                                  /*  ���������ж�                */
                for (RecNumCOM0 = 0; RecNumCOM0 < 8; RecNumCOM0++){                 /*  ��������8���ֽ�             */
			        l_COM0TempRev = LPC_UART0->RBR;                    	//ע���U0RBR����ս����жϱ�־
    				WriteFIFO((stcFIFO *)&sUART0RecFIFO,(uint8 *)&l_COM0TempRev,1); 
				   	
					//printfcom0("%c",l_COM0TempRev);

					if(l_COM0TempRev == COM0_FRAM_END )
					{
						l_COM0FramRecEndFlg = 1;							//֡������ɣ���־λ��ֵ	
					}
                }
                break;
            
            case 0x0C:                                                  /*  �ַ���ʱ�ж�                */
                while ((LPC_UART0->LSR & 0x01) == 0x01){                /*  �ж������Ƿ�������        */ 
			        l_COM0TempRev = LPC_UART0->RBR;                    	//ע���U0RBR����ս����жϱ�־
    				WriteFIFO((stcFIFO *)&sUART0RecFIFO,(uint8 *)&l_COM0TempRev,1);    
					//printfcom0("%c",l_COM0TempRev);

					if(l_COM0TempRev == COM0_FRAM_END )
					{
						l_COM0FramRecEndFlg = 1;							//֡������ɣ���־λ��ֵ	
					}   
				}
				l_COM0TimeOutFlg = 1;
                break;
                
            default:
                break;
        }
    } 
}
 
void	HoldCOM0ConnSta(void)
{
	if((GetSysTime()-l_COM0ConnTime > 2 && l_COM0StartFlg == 1 )
		||(l_COM0TimeOutFlg == 1))
	{
		l_COM0EndFlg = 1;
		l_COM0StartFlg = 0;
		l_COM0TimeOutFlg = 0;
	}
}
 
uint8	GetCOM0EndFlg(void)
{
	HoldCOM0ConnSta();
	return l_COM0EndFlg;
}

void	ClearCOM0EndFlg(void)
{
	l_COM0EndFlg 	= 0;
	l_COM0StartFlg 	= 0;
	l_COM0TimeOutFlg = 0;
}  

/*********************************************************************************************************
** Function name:     	uartInit
** Descriptions:	    ���ڳ�ʼ��������Ϊ8λ����λ��1λֹͣλ������żУ�飬������Ϊ115200
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void UART0Init (void)
{
	UART_CFG_Type		UART_ConfigStruct_Test;
	UART_FIFO_CFG_Type 	FIFOCfg_Test;
	UART_INT_Type 		UARTIntCfg_Test;

	GPIO_PinselConfig(RXD0,1);
	GPIO_PinselConfig(TXD0,1);	
	GPIO_PinselConfig(EN_485_0,0);
	WriteEN_485_0(0);

	UART_ConfigStruct_Test.Baud_rate = UART0_BPS;
	UART_ConfigStruct_Test.Databits = UART_DATABIT_8;
	UART_ConfigStruct_Test.Parity = UART_PARITY_NONE;
	UART_ConfigStruct_Test.Stopbits = UART_STOPBIT_1;
	
	UART_Init((LPC_UART_TypeDef *)LPC_UART0,(UART_CFG_Type *)&UART_ConfigStruct_Test);
	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0,ENABLE);

	FIFOCfg_Test.FIFO_DMAMode = DISABLE;
	FIFOCfg_Test.FIFO_Level = UART_FIFO_TRGLEV2;
	FIFOCfg_Test.FIFO_ResetRxBuf = ENABLE;
	FIFOCfg_Test.FIFO_ResetTxBuf = ENABLE;	
	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, (UART_FIFO_CFG_Type *)&FIFOCfg_Test);

	UARTIntCfg_Test = UART_INTCFG_RBR;	
	UART_IntConfig((LPC_UART_TypeDef *)LPC_UART0, UARTIntCfg_Test,ENABLE);
  	
	InitFIFO((stcFIFO *)&sUART0RecFIFO,UART0RecBuf,sizeof(UART0RecBuf));

	NVIC_EnableIRQ(UART0_IRQn);
	NVIC_SetPriority(UART0_IRQn, UART0_IRQn);									
}

uint32 ReadCOM0(uint8 *buf,uint32 len) 
{
    uint32 RealLen;                                             //ʵ�ʶ��ĳ���
    uint32 RevBufLen;                                           //����д���ֵ,�������������ܳ���

    RevBufLen = GetNoReadSizeFIFO((stcFIFO *)&sUART0RecFIFO);   //��û�ж�ȡ�ռ����ݸ���
    
    if(RevBufLen > len)
    {
        RealLen = len;                                  		//��ȡ��Ҫ������ݳ���
    }
    else
    {
        RealLen = RevBufLen;                        			//��ȡʵ�����ݳ���
    }
    
    ReadFIFO((stcFIFO *)&sUART0RecFIFO,buf,RealLen);

    return RealLen;
}

uint32 ReadCOM0NoClear(uint8 *buf,uint32 len) 
{
    uint32 RealLen;                                             //ʵ�ʶ��ĳ���
    uint32 RevBufLen;                                           //����д���ֵ,�������������ܳ���

    RevBufLen = GetNoReadSizeFIFO((stcFIFO *)&sUART0RecFIFO);   //��û�ж�ȡ�ռ����ݸ���
    
    if(RevBufLen > len)
    {
        RealLen = len;                                  		//��ȡ��Ҫ������ݳ���
    }
    else
    {
        RealLen = RevBufLen;                        			//��ȡʵ�����ݳ���
    }
    
    OnlyReadFIFO((stcFIFO *)&sUART0RecFIFO,buf,RealLen);

    return RealLen;
}

uint8	GetUart0Status(void)
{
	return	UART_GetLineStatus((LPC_UART_TypeDef *)LPC_UART0);
}

uint8 SendCOM0(void *buf,uint32 len)
{
	uint8	station;
    if( (!len) )
    {
        return FALSE;
    }   

	station = GetUart0Status();
	while(!(station & (0x01<<6)))
	{
		station = GetUart0Status();
	}

	WriteEN_485_0(1);

	UART_Send((LPC_UART_TypeDef *)LPC_UART0,buf,len,BLOCKING);

	station = GetUart0Status();
	while(!(station & (0x01<<6)))
	{
		station = GetUart0Status();
	}

	WriteEN_485_0(0);    

    return TRUE;   
}

uint8	SendCOM0s(void *buf)
{
	UARTPuts((LPC_UART_TypeDef *)LPC_UART0,buf);
	return 1;
}

uint8	GetCOM0FramRecEndFlg(void)
{
	return	l_COM0FramRecEndFlg;
}

void	ClearCOM0FramRecEndFlg(void)
{
	l_COM0FramRecEndFlg = 0;
}
