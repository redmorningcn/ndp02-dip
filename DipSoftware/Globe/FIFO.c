#include 	<includes.h>
#include	"FIFO.h"

//------------------------------------------------------------------------
// ��    �ƣ�   InitFIFO(stcFIFO *FIFO,uint8 *Buf,uint16 Size)
// ��    �ܣ�   ��ʼ��FIFO������
// ��ڲ�����	FIFO:Ҫ��ʼ����FIFO�������ṹ,Buf:��������ַ,SIZE:��������С
// ���ڲ�����
//------------------------------------------------------------------------
void   InitFIFO(stcFIFO *FIFO,uint8 *Buf,uint16 Size)
{
    FIFO->pWrite = 0;
    FIFO->pRead  = 0;
    FIFO->Size   = Size;
    FIFO->BufAddr= Buf;
}

//------------------------------------------------------------------------
// ��    �ƣ�   void   ClearFIFO(stcFIFO *FIFO)
// ��    �ܣ�   ��ʼ��FIFO������
// ��ڲ�����	FIFO:Ҫ��ʼ����FIFO�������ṹ,Buf:��������ַ,SIZE:��������С
// ���ڲ�����
//------------------------------------------------------------------------
void   ClearFIFO(stcFIFO *FIFO)
{
    FIFO->pWrite = 0;
    FIFO->pRead  = 0;	
}

//------------------------------------------------------------------------
// ��    �ƣ�   uint16  GetNoReadSizeFIFO(stcFIFO *FIFO)
// ��    �ܣ�   ��FIFO��������δ���ռ��С
// ��ڲ�����	FIFO:��FIFO�������ṹ
// ���ڲ�����	������δ�����ݴ�С
//------------------------------------------------------------------------
uint16  GetNoReadSizeFIFO(stcFIFO *FIFO)
{
    uint16  pWrite = FIFO->pWrite;
    uint16  pRead  = FIFO->pRead;
    uint16  pBufSize = FIFO->Size;

    return (pWrite + pBufSize - pRead) % pBufSize;
}

//------------------------------------------------------------------------
// ��    �ƣ�   uint16  GetNoWriteSizeFIFO(stcFIFO *FIFO)
// ��    �ܣ�   ��FIFO��������δд�ռ��С
// ��ڲ�����	FIFO:��FIFO�������ṹ
// ���ڲ�����	������δд���ݴ�С
//------------------------------------------------------------------------
uint16  GetNoWriteSizeFIFO(stcFIFO *FIFO)
{
    uint16  pBufSize = FIFO->Size;
    return  pBufSize - GetNoReadSizeFIFO(FIFO);
}

//------------------------------------------------------------------------
// ��    �ƣ�   uint8   WriteFIFO(stcFIFO *FIFO,uint8 *DatBuf,uint16 DatLen)
// ��    �ܣ�   дFIFO������
// ��ڲ�����	FIFO:��FIFO�������ṹ,DatBuf:д������,DatLen:���ݳ���
// ���ڲ�����	дFIFO�������ɹ�����1,���󷵻�0
//------------------------------------------------------------------------
uint8   WriteFIFO(stcFIFO *FIFO,uint8 *DatBuf,uint16 DatLen)
{
    uint16  i,j;
    uint16  NoWriteSize;
    uint16  pWrite = FIFO->pWrite;
    uint16  pBufSize = FIFO->Size;
    uint8   *FIFOBuf = FIFO->BufAddr;

    NoWriteSize =  GetNoWriteSizeFIFO(FIFO);   		//ȷ�ϻ�������û��δд�ռ��С
	
//	
    if(DatLen >= NoWriteSize)
    {
        return  FALSE;                     	 		//���ݱȻ�����ʣ��ռ��,����д����
    }

    for(i = 0; i < DatLen; i++)             		//������д�뻺����
    {
        j =(pWrite + i) % pBufSize;         		//����д��ַ

        FIFOBuf[j] =  DatBuf[i];            		//д����
    }

    FIFO->pWrite = (pWrite + DatLen ) % pBufSize; 	//дָ��++

    return  TRUE;
}

//------------------------------------------------------------------------
// ��    �ƣ�   uint8   ReadFIFO(stcFIFO *FIFO,uint8 *DatBuf,uint16 DatLen)
// ��    �ܣ�   ��FIFO������
// ��ڲ�����	FIFO:��FIFO�������ṹ,DatBuf:�����ݻ���λ��,DatLen:Ҫ�����ݳ������ݳ���
// ���ڲ�����	��FIFO�������ɹ�1,����Ϊ0
//------------------------------------------------------------------------
uint8   ReadFIFO(stcFIFO *FIFO,uint8 *DatBuf,uint16 DatLen)
{
    uint16  i,j;
    uint16  NoReadSize;
    uint16  pRead = FIFO->pRead;
    uint16  pBufSize = FIFO->Size;
    uint8   *FIFOBuf = FIFO->BufAddr;

    NoReadSize = GetNoReadSizeFIFO(FIFO);      	//��δ���ռ��С

//	printfcom0("\r\n NoReadSize %d",NoReadSize);
    if(DatLen > NoReadSize )                 	//���ռ�С��Ҫ������,���ض�ȡ����
    {
        return FALSE;
    }

    for(i = 0; i < DatLen; i++)
    {
        j = (pRead + i) % pBufSize;         	//�������ַ

        DatBuf[i] = FIFOBuf[j];             	//��ȡ����
    }

    FIFO->pRead = (pRead + DatLen) % pBufSize;  //��ָ��++

    return  TRUE;
}


//------------------------------------------------------------------------
// ��    �ƣ�   uint8   ReadFIFO(stcFIFO *FIFO,uint8 *DatBuf,uint16 DatLen)
// ��    �ܣ�   ��FIFO������
// ��ڲ�����	FIFO:��FIFO�������ṹ,DatBuf:�����ݻ���λ��,DatLen:Ҫ�����ݳ������ݳ���
// ���ڲ�����	��FIFO�������ɹ�1,����Ϊ0
//------------------------------------------------------------------------
uint8   OnlyReadFIFO(stcFIFO *FIFO,uint8 *DatBuf,uint16 DatLen)
{
    uint16  i,j;
    uint16  NoReadSize;
    uint16  pRead = FIFO->pRead;
    uint16  pBufSize = FIFO->Size;
    uint8   *FIFOBuf = FIFO->BufAddr;

    NoReadSize = GetNoReadSizeFIFO(FIFO);      	//��δ���ռ��С

    if(DatLen > NoReadSize )                 	//���ռ�С��Ҫ������,���ض�ȡ����
    {
        return FALSE;
    }

    for(i = 0; i < DatLen; i++)
    {
        j = (pRead + i) % pBufSize;         	//�������ַ

        DatBuf[i] = FIFOBuf[j];             	//��ȡ����
    }

	FIFO->pRead = (pRead ) % pBufSize;  //��ָ��++

    return  TRUE;
}
