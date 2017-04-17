#ifndef  _CardDataTypeDef_h_
#define  _CardDataTypeDef_h_

//ʱ��----------------------------------------
typedef		struct	_stcTime_
{
	uint8	Sec;
	uint8	Min;
	uint8	Hour;
	uint8	Date;
	uint8	Month;
	uint8	Year;
	uint16	CrcCheck;
}stcTime;

typedef struct _stcCardID_						//IC ��ID��	  32
{
	uint8	ProductNum[12];						//IC�����
	uint8	DriverNum[4];						//˾������
	uint8	DriverUnit[8];						//˾�����ڵ�λ���
	uint8	Reserve0[4];						//Ԥ��0
	uint16	Reserve1;	 						//Ԥ��1
	uint16	CrcCheck;							//CRC����
}stcCardID;

typedef struct _stcCardType_					//IC ������ 8
{
	uint16	CardType[3];						//IC������
	uint16	CrcCheck;							//CRC����
}stcCardType;

typedef struct _stcDensity_						//IC ���ܶ� 24
{
	uint8		LocoType[2];					//�����ͺ�
	uint8		LocoNum[2];						//�������
	//uint8		DriverNum[4];					//˾�����
	uint32		DenChageTimes;					//�ܶȱ仯��
	uint32		Density;						//�����ܶ�
	uint32		AddOilStationNum;				//���ͻ����
	uint32		AddOilerNum;					//������Ա���	
	uint16		AddVol;							//��������
	uint16		CrcCheck;						//CRC����
}stcDensity;

typedef struct _stcModPot_						//IC ��cd����
{
	uint16	HigVal;								//ѹ��ֵ
	uint16	DipVal;								//����ֵ
}stcModPot;

typedef struct _stcModel_						//����ģ�͸������ݽṹ
{
	stcModPot	sModPot[50];					//����ģ��
	uint16		PotNum;							//����ģ�͵�ĸ���	
	uint16		StartHight;						//��ʼ�߶�
	uint8		ModelNum;						//ģ�ͱ��
	uint8		Reserve0;						//Ԥ��    //100919   0x01��ʾʹ�ã�0x00��ʾδ��
	uint16		CrcCheck;						//CRCУ��
}stcModel;

typedef struct _stcModelSemple_					//����ģ�ͼ����ݽṹ
{
	stcModPot	sModPot[10];					//����ģ��
	uint16		PotNum;							//����ģ�͵�ĸ���	
	uint16		StartHight;						//��ʼ�߶�
	uint8		ModelNum;						//ģ�ͱ��
	uint8		Reserve0;						//Ԥ��	//100919	0x01��ʾʹ�ã�0x00��ʾδ��	
	uint16		CrcCheck;						//CRCУ��
}stcModelSemple;

typedef struct _stcModelComplex_				//����ģ�ͼ����ݽṹ
{
	stcModPot	sModPot[200];					//����ģ��
	uint16		PotNum;							//����ģ�͵�ĸ���	
	uint16		StartHight;						//��ʼ�߶�
	uint8		ModelNum;						//ģ�ͱ��
	uint8		Reserve0;						//Ԥ��
	uint16		CrcCheck;						//CRCУ��
}stcModelComplex;


typedef struct _stcModelCard_					//����ģ�͸������ݽṹ
{
	stcModel		sModel[18];					//��������ģ��
	stcModelSemple	sModelSemple[46];			//������ģ��

//	stcModel		sModel[18];					//��������ģ��
//	stcModelSemple	sModelSemple[18];			//������ģ��
//	stcModelComplex	sModelComplex;	   			
	uint16			Reserve0;					//Ԥ��
	uint16			CrcCheck;					//CRCУ��	
}stcModelCard;


typedef struct _stcReviseHight_					//IC �����߶�
{
	int16		ReviseHight;					//�����߶���ʼ�߶�
	uint16		CrcCheck;						//CRCУ��
}stcReviseHight;

typedef struct _stcAddDipVal_					//IC ��������
{
	int16		AddDipVal;						//��������
	uint16		CrcCheck;						//CRCУ��
}stcAddDipVal;

typedef struct _stcDebugCard_					//
{
	uint16		DebugCode;						//���Դ���
	uint16		BufLen;							//��Ч���ݳ���
	uint8		Buf[100];						//������
	uint16		Reserve0;						//Ԥ��
	uint16		CrcCheck;						//CRCУ��
}stcDebugCard;

//����ģ�Ϳ�����
typedef struct _stcCardPara_ 					//IC ��cd���� 352
{
	stcDensity		sDensity;					//�ܶ�
	uint32			SetVal;						//����ֵ
	stcTime			sTime;						//ʱ��
 	stcReviseHight	sReviseHight;				//������ʼ�߶�
	stcFixInfo      sFixInfo;              	 	//װ����
	stcDebugCard	sDebugCard;					//���Կ�
	uint16			Reserve0;					//Ԥ��
	uint16			CrcCheck;					//CRC����
}stcCardPara;

typedef struct _stcCardIndex_					//IC ���ļ����� 36
{
	uint8			LocoType[2];				//�����ͺ�
	uint8			LocoNum[2];					//�������
	uint8			ProNum[16];					//��Ʒ���
	uint32			StartAddr;					//��ʼ��ַ
	uint32			EndAddr;					//������ַ
	uint16			RecLen;						//��¼����
	uint16			RecNum;						//��¼����	
}stcCardIndex;

typedef struct _stcCardFlg_						//IC ����ʶ
{
	stcCardID		sCardID;					//IC�� ID�ṹ
	stcCardType		sCardType;					//IC�� IC�����ͣ����ݿ����ܶȿ�����
	stcCardPara		sCardPara;					//IC�� ������
	stcCardIndex	sCardIndex[100];			//IC�� �ļ�����
	uint16			WriteCardTimes;				//��д������
	uint16			CrcCheck;					//CRC����
}stcCardFlg;


#endif
