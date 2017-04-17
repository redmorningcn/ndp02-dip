#include <includes.h>

uint32_t GulSrcDat[50] = { 	 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 
	                         0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 
	                         0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 
	                         0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 
	                         0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 
	                         0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 
	                         0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 
	                         0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555, 0x55555555,
							 0x55555555 };                                /* ���Դ��ַ����               */

uint32_t GulDesDat[50] = {0};                                             /* ���Ŀ���ַ����             */


//
//void GPDMA_Init(void);
////Status GPDMA_Setup(GPDMA_Channel_CFG_Type *GPDMAChannelConfig, fnGPDMACbs_Type *pfnGPDMACbs);
//Status GPDMA_Setup(GPDMA_Channel_CFG_Type *GPDMAChannelConfig);
//IntStatus GPDMA_IntGetStatus(GPDMA_Status_Type type, uint8_t channel);
//void GPDMA_ClearIntPending(GPDMA_StateClear_Type type, uint8_t channel);
//void GPDMA_ChannelCmd(uint8_t channelNum, FunctionalState NewState);

//void dmaInit (uint32_t *pulSrc_Address,  uint32_t *pulDest_Address,  uint32_t ulDMA_Size)
void m2mdmaInit (uint32_t *pulSrc_Address,  uint32_t *pulDest_Address,  uint32_t ulDMA_Size)
{
	GPDMA_Channel_CFG_Type	GPDMAChannelConfig_Test;

	GPDMA_Init();				

	GPDMAChannelConfig_Test.ChannelNum 		= 0;
	GPDMAChannelConfig_Test.TransferSize 	= ulDMA_Size/4;
	GPDMAChannelConfig_Test.TransferWidth	= GPDMA_WIDTH_WORD;
	GPDMAChannelConfig_Test.SrcMemAddr 		= (uint32_t)pulSrc_Address;
	GPDMAChannelConfig_Test.DstMemAddr 		= (uint32_t)pulDest_Address;
	GPDMAChannelConfig_Test.TransferType 	= GPDMA_TRANSFERTYPE_M2M;
	GPDMAChannelConfig_Test.SrcConn 		= 0;
	GPDMAChannelConfig_Test.DstConn 		= 0;
	GPDMAChannelConfig_Test.DMALLI 			= 0;

	GPDMA_Setup((GPDMA_Channel_CFG_Type *)&GPDMAChannelConfig_Test);

	GPDMA_ChannelCmd(0,ENABLE);
                                                                     
}

/*********************************************************************************************************
** Function name:       main
** Descriptions:        GPDMA���ԣ�LPC1700GPDMA���Է�������SRAM��ֻ�趨���������飬����DMA�����
**                      �ж������������������ȼ�֤��GPDMA������ȷ.����ʱ�̽�JP17��������ʵ������Ϊ��
**                      ���GPDMA������ȷ����������������
**                      ���GPDMA������󣬷�������һ����
** input parameters:    ��
** Output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void m2mdmaTask(void)
{
    uint32_t i;
    uint32_t ulflag = 0;                                                /* �жϴ����Ƿ���ȷ��1��ʾDMA   */
                                                                        /* ������ȷ��0��ʾDMA�������   */

    m2mdmaInit(GulSrcDat,GulDesDat,200);                                   /* GPDMA��ʼ��                  */    

    
    /*
     *  �Ƚ�Դ������Ŀ�������Ƿ���ȣ��������GPDMA������ȷ��flag = 1 
     */ 
    for (i = 0; i <50; i++) {
        if (GulDesDat[i] != GulSrcDat[i]) {
            ulflag = 0;
            break;
        } else {
            ulflag = 1;
        }
    }



    /* 
     *  ���GPDMA������ȷ�������������������GPDMA������󣬷�������һ��
     */
    if (1 == ulflag) {
		printfcom0("\r\n  DMA test success!");                                                
        //beepNumber(2);
    } else {
        //beepNumber(1);
		printfcom0("\r\n  DMA test fault!");
    }
    while (1)
	{
		OSTimeDlyHMSM(0,0,0,100);
	}
}


///*********************************************************************************************************
//** Function name:       dmaInit
//** Descriptions:        DMAͨ��0��ʼ������(�洢�����洢��)
//** input parameters:    puiSrc_Address��   �洢��Դ��ַ
//**                      puiDest_Address��  �洢��Ŀ���ַ
//**                      uiDMA_Size��       �����ֽڸ���
//** Output parameters:   ��
//** Returned value:      ��
//*********************************************************************************************************/
//void dmaInit (uint32_t *pulSrc_Address,  uint32_t *pulDest_Address,  uint32_t ulDMA_Size)
//{
//    
//	LPC_SC->PCONP  |= (1 << 29);                                        /* ʹ��GPDMAʱ��                */
//    LPC_GPDMA->DMACIntTCClear   |= 0x01;                                /* ����ն˼����жϵı�־       */
//    LPC_GPDMA->DMACIntErrClr    |= 0x01;                                /* ��������жϱ�־             */
//                                                                        /* ��ʼ��DMA������              */
//    LPC_GPDMACH0->DMACCLLI = 0;                                         /* ��һ����������Ч������DMA��  */
//                                                                        /* ����ʹ�������洢�ռ�         */
//    LPC_GPDMACH0->DMACCControl    |=  ((ulDMA_Size/4)&0x0fff)
//                     |   (0x04 << 12)                                   /* ָ��Դͻ�������СΪ32λ     */
//                     |   (0x04 << 15)                                   /* ָ��Ŀ��ͻ�������СΪ32λ   */
//                     |   (0x02 << 18)                                   /* ָ��Դ�������ݿ��Ϊ32λ     */
//                     |   (0x02 << 21)                                   /* ָ��Ŀ�괫�����ݿ��Ϊ32λ   */
//                     |   (1 << 26)                                      /* ָ��Դ��ַ�Զ�����           */
//                     |   (1 << 27)                                      /* ָ��Ŀ���ַ�Զ�����         */
//                     |   (0x80000000);                                  /* ���ô��������ж�             */
//                                                                        /* ʹ��ͨ��0���ն˼����ж�      */  
//    LPC_GPDMACH0->DMACCSrcAddr = (uint32_t)pulSrc_Address;              /* ���ô洢��Դ��ַ             */
//    LPC_GPDMACH0->DMACCDestAddr= (uint32_t)pulDest_Address;             /* ���ô洢��Ŀ���ַ           */                                                                       
//}
//
///*********************************************************************************************************
//** Function name:       gpdmaEnabe
//** Descriptions:        DMA��DMAͨ��0ʹ��
//** input parameters:    ��
//** Output parameters:   ��
//** Returned value:      ��
//*********************************************************************************************************/
//void gpdmaEnabe (void)
//{
//    LPC_GPDMA->DMACConfig    = 0x01;                                    /* ʹ��DMA��ʹ��С��ģʽ        */
//    LPC_GPDMACH0->DMACCConfig |= 0x01;                                  /* ʹ��ͨ��0                    */
//}
//
///*********************************************************************************************************
//** Function name:       main
//** Descriptions:        GPDMA���ԣ�LPC1700GPDMA���Է�������SRAM��ֻ�趨���������飬����DMA�����
//**                      �ж������������������ȼ�֤��GPDMA������ȷ.����ʱ�̽�JP17��������ʵ������Ϊ��
//**                      ���GPDMA������ȷ����������������
//**                      ���GPDMA������󣬷�������һ����
//** input parameters:    ��
//** Output parameters:   ��
//** Returned value:      ��
//*********************************************************************************************************/
//int main (void)
//{
//    uint32_t i;
//    uint32_t ulflag = 0;                                                /* �жϴ����Ƿ���ȷ��1��ʾDMA   */
//                                                                        /* ������ȷ��0��ʾDMA�������   */
//    SystemInit();                                                       /* ϵͳ��ʼ��������ɾ��         */
//
//    BEEPOFF();
//    dmaInit(GulSrcDat,GulDesDat,200);                                   /* GPDMA��ʼ��                  */    
//    gpdmaEnabe();                                                       /* DMAʹ��                      */
//    
//    /*
//     *  �Ƚ�Դ������Ŀ�������Ƿ���ȣ��������GPDMA������ȷ��flag = 1 
//     */ 
//    for (i = 0; i <50; i++) {
//        if (GulDesDat[i] != GulSrcDat[i]) {
//            ulflag = 0;
//            break;
//        } else {
//            ulflag = 1;
//        }
//    }
//
//    /* 
//     *  ���GPDMA������ȷ�������������������GPDMA������󣬷�������һ��
//     */
//    if (1 == ulflag) {                                                
//        beepNumber(2);
//    } else {
//        beepNumber(1);
//    }
//    while (1);
//}
