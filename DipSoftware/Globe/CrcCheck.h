
#ifndef  _CrcCheck_h_
#define  _CrcCheck_h_

#include <includes.h>


//----------------------------------------------------------------------------
// ��    �ƣ�   uint16 GetCrc16Check(uint8 *Buf, uint16 Len)
// ��    �ܣ�   ȡCRC16У���
// ��ڲ�����  
// ���ڲ�����   
//----------------------------------------------------------------------------
extern	uint16 GetCrc16Check(uint8 *Buf, uint16 Len);
    
extern	uint16 GetModBusCrc16(uint8 *puchMsg,uint16  usDataLen);    

extern	uint16 GetModBusCrc16Up(unsigned char *puchMsg,unsigned short  usDataLen);
#endif


