#ifndef  _DataTypeDef_h_
#define  _DataTypeDef_h_

#include "IdDataTypeDef.h"
#include "CardDataTypeDef.h"
#include "RecDataTypeDef.h"
#include "LocoModTypeDef.h"
#include "GlobePara.h"


//����ģ�Ϳ�����
typedef struct _stcSysRunPara_ 					//IC ��cd���� 352
{
	uint8			StoreTime;					//�洢ʱ����  //Ĭ��Ϊ
	uint8			PrintfFlg;					//��ӡ����
	uint8			DisHigFlg;					//��ӡ����
	uint8			NoAvgFlg;
	uint16			CrcCheck;					//CRC����
}stcSysRunPara;


#define			RIGHT_DATA		0xff

#endif
