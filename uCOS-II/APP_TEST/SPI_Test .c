#include <includes.h>

/*
 *  ������������ڲ����ĺ�
 */
#define	RDADDR		4090
#define	NOBYTES	    20
#define	RCVBUFPT	GucRdBuf

/*
 *  д����������ڲ����ĺ� 
 */
#define	WRADDR		4090
#define	SNDBUFPT	GucWrBuf
#define	WRNOBYTES	20

uint32_t 	GulChipID = 0;
uint8_t 	GucWrBuf[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
uint8_t 	GucRdBuf[20];


/*********************************************************************************************************
** Function name:       main
** Descriptions:        ����SPI��дNorFlash���̽�JP25��ѡ�񵥲����е�102�У���kiel��鿴GuiChipIDΪ
**                      0x00c22015��ȫ�����У���SPI��дNorFlash�������������һ����������
**                      ���ر�ע�⣺SPI��UART1�������ţ��ڱ����̵���ʱ�뽫JP20�Ķ���ñ�Ͽ�
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void SPITask (void)
{
    uint32_t 	i = 0;
    SPI_CFG_Type	SPI_ConfigStruct_Test;
	PINSEL_CFG_Type PinCfg_Test;

	PinCfg_Test.Portnum = PINSEL_PORT_0;
	PinCfg_Test.Funcnum = PINSEL_FUNC_3;

	PinCfg_Test.Pinnum = PINSEL_PIN_15;
	PINSEL_ConfigPin((PINSEL_CFG_Type *)&PinCfg_Test);
	PinCfg_Test.Pinnum = PINSEL_PIN_17;
	PINSEL_ConfigPin((PINSEL_CFG_Type *)&PinCfg_Test);
	PinCfg_Test.Pinnum = PINSEL_PIN_18;
	PINSEL_ConfigPin((PINSEL_CFG_Type *)&PinCfg_Test);

	PinCfg_Test.Pinnum = PINSEL_PIN_16;
	PinCfg_Test.Funcnum = PINSEL_FUNC_0;
	PINSEL_ConfigPin((PINSEL_CFG_Type *)&PinCfg_Test);
	GPIO_SetDir(PINSEL_PORT_0, 0x01ul<<PINSEL_PIN_16, 1);

	SPI_ConfigStructInit((SPI_CFG_Type *)&SPI_ConfigStruct_Test);
	SPI_Init((LPC_SPI_TypeDef *)LPC_SPI, (SPI_CFG_Type *)&SPI_ConfigStruct_Test);


//    SPIInit();    
    MX25L1602_RdID(Jedec_ID, &GulChipID);		                        /* �������е��˴�ʱ,��IAR��鿴 */

   	printfcom0("\r\n GulChipID %x %x",GulChipID,&GulChipID);
                                                                        /* GuiChipID��ֵ�Ƿ�0x00c22015  */
    GulChipID &= ~0xFF000000;                                           /* ��������24λ����             */            
    if (GulChipID != 0x00C22015) {
        while (1) {
           //BEEPON() ;
		   OSTimeDlyHMSM(0,0,0,100); 
        }
    }
    MX25L1602_Erase(0, 511);                                            /* ����оƬ                     */

	i = 0xfaaf;
	MX25L1602_WR(0,(uint8_t *)&i,sizeof(i));
	MX25L1602_RD(0,sizeof(i),(uint8_t *)&i);
  	printfcom0("\r\n i %x %x",i,&i);

	i = 0xaffa;
	MX25L1602_WR(0,(uint8_t *)&i,sizeof(i));
	MX25L1602_RD(0,sizeof(i),(uint8_t *)&i);
  	printfcom0("\r\n i %x %x",i,&i);

    MX25L1602_WR(WRADDR, SNDBUFPT, WRNOBYTES);	                        /* ��0x2007Ϊ��ʼ��ַ����WrBuf  */
   	                                                                     /* �������20������д��оƬ     */
    MX25L1602_RD(RDADDR, NOBYTES, RCVBUFPT);                            /* ��0x2007Ϊ��ʼ��ַ����20��   */
     
    for (i = 0;i < 19;i++) {
        if (GucRdBuf[i] != GucWrBuf[i] ) {                              /* ��SPI��д����ȷ����������  */
                                                                        /*  һ��������SPI��д��ȷ       */
            //beepNum(1); 
            while (1)
			{ 
				OSTimeDlyHMSM(0,0,0,100);  
			}    
        }
    }

    while (1)
	{
		OSTimeDlyHMSM(0,0,0,100);
	}
}
