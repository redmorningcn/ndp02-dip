//#include    "config.h"   
//#include    "CpuDrive.h"

#include <includes.h>
#include "IIC.h"
					  
//�������
#define		FRAM_SIZE               8192						         	//1024*8�ռ�����
#define		FRAM_START_ADDR	        0x0000	                                //�������ʼ��ַ
#define		FRAM_DIVICE_ADDR        0xa0	                                //������豸��ַ
#define		FRAM_END_ADDR	      	(FRAM_START_ADDR + FRAM_SIZE)	

#define		FRMA_PROTECT			121//P121

//------------------------------------------------------------------------
//  ��  �� ��void WriteSCL( uint8 temp )
//  ��  �� ������ SCL
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteFRAM_PROTECT(uint8 temp)
{
//    IO1DIR_OUT(FRMA_PROTECT);    
//    IO1PIN_W(temp,FRMA_PROTECT);
}

//-------------------------------------------------------------------------------------------------------
//��������:         WriteFM24CL16()
//��    ��:         ��FM24CL16ָ����ַ����д����
//��ڲ���:         ADDR:       ������ַ    ��ַ��0 ~ sizeof(FM24CL16)
//                  *DataBuf:   ���ݻ���
//                  Len:        ���ݳ���
//���ڲ���:         ��
//˵����            
//--------------------------------------------------------------------------------------------------------
uint8 WriteFM24CL64(uint16  Addr, uint8 *DataBuf, uint32 DataBufLen)            
{
    uint32  i = 0;
    uint8   SlaveAddr;                                      //�ӻ���ַ
    uint16  AddrTemp = 0;                                   //��ַ����
    
    WriteFRAM_PROTECT(0);									//��д����
    
    AddrTemp = Addr;
    AddrTemp += FRAM_START_ADDR;                            //�����ַ

    if( (uint16)AddrTemp + DataBufLen > FRAM_END_ADDR ) 
    {
        return  FALSE;                                      //��ַδ����
    }
        
    SlaveAddr = FRAM_DIVICE_ADDR & (~(0x01));               //��FM24CL64�豸д��ַ
    
    StartI2C();                                             //����IIC����
    
    WriteByteWithI2C(SlaveAddr);                            //дFM24CL64��ַ
    CheckSlaveAckI2C();
 
    WriteByteWithI2C(Addr >> 8);                            //дFM24CL64��λ��ַ
    CheckSlaveAckI2C();
    
    WriteByteWithI2C( Addr );                               //дFM24CL64��λ��ַ
    CheckSlaveAckI2C();     
  
    for(i = 0; i < DataBufLen; i++)                         //��������
    {
        WriteByteWithI2C(DataBuf[i]);                       //д����
        CheckSlaveAckI2C();                                 //���ӻ�Ӧ���ź�
    }
    
    StopI2C();                                              //ֹͣIIC����   
    
    return  TRUE;                                           //��ȷ
}

//-------------------------------------------------------------------------------------------------------
//��������:         ReadFM24CL16()
//��    ��:         ��ȡFM24CL16ָ����ַ��������
//��ڲ���:         ADDR:       ������ַ   ��ַ��0 ~ sizeof(FM24CL16)
//                  *DataBuf:   ���ݻ��� 
//                  Len:        ���ݳ���
//���ڲ���:         ��
//˵����            
//--------------------------------------------------------------------------------------------------------
uint8 ReadFM24CL64(uint16  Addr, uint8 *DataBuf, uint32 DataBufLen)            
{
    uint32  i = 0;
    uint8   SlaveAddr;                                      //�ӻ���ַ
    uint16  AddrTemp;                                       //��ַ����
    
	WriteFRAM_PROTECT(0);									//��д����

    AddrTemp = Addr;
    
    AddrTemp += FRAM_START_ADDR;                            //�����ַ
    
    if( (uint16)AddrTemp + DataBufLen > FRAM_END_ADDR ) 
    {
        return  FALSE;                                      //��ַδ����
    }
    
    SlaveAddr = FRAM_DIVICE_ADDR & (~(0x01));               //��FM24CL64�豸д��ַ
    
    StartI2C();                                             //����IIC����
    
    WriteByteWithI2C(SlaveAddr);                            //дFM24CL64�豸д��ַ
    CheckSlaveAckI2C();                                     //���ӻ�Ӧ���ź�
    
    WriteByteWithI2C(Addr >> 8 );                           //д���ݸ�λ��ַ
    CheckSlaveAckI2C();                                     //���ӻ�Ӧ���ź�
    
    WriteByteWithI2C( Addr );                               //д���ݵ�λ��ַ
    CheckSlaveAckI2C();                                     //���ӻ�Ӧ���ź�
        
    SlaveAddr = (FRAM_DIVICE_ADDR)|(0x01);                  //��FM24CL64�豸����ַ
    
    StartI2C();                                             //����IIC����
    
    WriteByteWithI2C(SlaveAddr);                            //дFM24CL16��ַ
    CheckSlaveAckI2C();                                     //���ӻ�Ӧ���ź�
   
    for(i = 0; i < (DataBufLen -1); i++)                    //��������
    {
        DataBuf[i] = ReadByteWithI2C();                     //д����
        MasterAckI2C();                                     //����Ӧ��ӻ�
    }
    DataBuf[i] = ReadByteWithI2C();                         //д����
    
    MasterNoAckI2C();                                       //����Ӧ��ӻ�
    
    StopI2C();
    
    return  TRUE;                                           //��ȷ
}

//#endif
    
