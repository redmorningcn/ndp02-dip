#ifndef  _LocoModTypeDef_h_
#define  _LocoModTypeDef_h_

//TAXIIǰ-------------------------------------------------------------------------------------
typedef struct _stcLocoModNum_     //
{
    uint32  LocoType;      		//��������
    uint32  LocoNum;       		//�������
    uint32  ModeNum;      		//ģ�ͱ��
    uint8   LocoStr[12];      	//������  
}stcLocoModNum;

#endif
