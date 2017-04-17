#ifndef  _RecDataTypeDef_h_
#define  _RecDataTypeDef_h_

//TAXIIǰ-------------------------------------------------------------------------------------
typedef struct _stcTAX2Bef_     //������TAX2��󲿷ֵ����ݽṹ (32)
{
    uint8   TAX2BefAdrCod;      //�����ַ(38H)     1   ָͨѶ��¼��Ԫ�ĵ�ַ����Ϊ38H
    uint8   CharacterCod;       //������            1   ��,����0
    uint8  	NewFlg;      		//��־     			1   ��Э��:67H
    uint8   SoftVerNum;      	//����汾��      	1   
 	
	uint8   Reserve0;      		//Ԥ��0       			1   
    uint8   E_StationNum;       //��վ����չ�ֽ�    1   ��վ����չ�ֽ�
    uint8   TrainTyp[4];        //��������          4   ��������,���α����·���(����[2005]72���ļ�)
    														//						�ĳ��������ʶ��,������LKJ2000��ʽ��ͬ 
    uint8   E_MstDriverNum;     //˾������չ�ֽ�    1     
    uint8   E_SlvDriverNum;     //��˾������չ�ֽ�  1     
    
    uint8   Reserve1[2];      	//Ԥ��1 			2
    uint8   E_LocoTyp;          //�����ͺ���չ�ֽ�  1   �����ͺ������ֽ�,������LKJ2000��ʽ��ͬ
    uint8   RelRoadNum;         //ʵ�ʽ�·��        1   �����ʽ��LKJ2000��ͬ   
    
    uint8   Reserve2[11];      	//Ԥ��2 			11
    uint8   Car_Truck;          //��/������/��      1   D0��0/1 �� ��/��   D1��0/1 �� ��/��
    
    uint8   TrainNum[3];        //�������ֲ���      3   ���α����·���(����[2005]72����)�ĳ������ݲ���
    uint8   CheckSum;           //����            1   Ϊǰ�������ֽ��ۼӺ͵Ķ����Ʋ���
}stcTAX2Bef;

//TAXII��----------------------------------------------------------------------------------
typedef struct _stcTAX2Bak_     //������TAX2��󲿷ֵ����ݽṹ
{
    uint8   TAX2BakAdrCod;      //�����ַ(39H)     1   ָͨѶ��¼��Ԫ�ĵ�ַ����Ϊ39H
    uint8   CharacterCod;       //������            1   ��4λΪ3���ϴν��ճɹ���ΪC��
                                //                      �ϴν���ʧ�ܣ�����˵����������
                                //                      ͨѶ�������ܸ��ţ�Ӧ����Ч���ݴ���
                                //                      ����λ��Ϊ0
    uint8   DetectCellCod;      //��ⵥԪ����      1   ָ����ͨѶ��¼��ԪͨѶ�ļ�ⵥԪ���š�
                                //                      ��Ϊ01-�����⣬
                                //                          02-������⣬03-TMIS��04-DMIS��
                                //                          06-����¼����05��07-09Ԥ�������õ�Ԫ��
    uint8   Time[4];            //��/��/ʱ/��/��    4   D5~D0���룬D11~D6���֣�D16~D12��
                                //                          ʱD21~D17���գ�D25~D22����
    uint8   RelSpeed[3];        //ʵ��              3   D9~D0��ʵ�٣�D19~D10��Ԥ��
    uint8   LocoSign;           //�����ź�          1   B4 = 0/1  ����/���;   B3~B0 0-�޵�,1-��,2-��, 
    uint8   LocoWorkState;      //��������          1   b0-��λ,B1-���,B2-��ǰ,B3-�ƶ�,B4-ǣ��
    uint8   SignalNum[2];       //�źŻ����        2   
    uint8   SignalTyp;          //�źŻ�����        1   B2-B0 :2-��վ,3-��վ,4-ͨ��,5-Ԥ��,6-����
                                //                  3   -˫��,4-���,5-��,6-��,7-�̻�,8-��
    uint8   KmMark[3];   				//�����    3   ��λ����
    uint8   Weight[2];          //����              2
    uint8   PlanLen[2];         //�Ƴ�              2   ��λ��0.1
    uint8   VoitureCnt;         //����              1
    uint8   Car_Truck;          //��/������/��      1   D0��0/1 �� ��/��   D1��0/1 �� ��/��
    uint8   TrainNum[2];       	//����              2
    uint8   RoadNum;            //���κ�(��·��)    1
    uint8   StationNum;         //��վ��            1
    uint8   MstDriverNum[2];    //˾����            2
    uint8   SlvDriverNum[2];    //��˾����          2
    uint8   LocoNum[2];         //������            2
    uint8   LocoTyp;            //�����ͺ�          1   ��δ����
    uint8   LocoPipePress[2];   //�г���ѹ          2   B9-B0:��ѹ(��λ:1kPa)    
    uint8   LocoState;          //װ��״̬          1   B0 = 1/0 - ����/���; B2 = 1/0 - ����/�ǵ���
    uint8   Reserve1;           //Ԥ��0 						1
    uint8   CheckSum;           //����            1   Ϊǰ�������ֽ��ۼӺ͵Ķ����Ʋ���
}stcTAX2Bak;

typedef struct _stcTAX2Full_  	//������TAX2���ݽṹ
{
	stcTAX2Bef	sTAX2Bef;		//TAX2ǰ����			
	stcTAX2Bak	sTAX2Bak;		//TAX2�󲿷�
}stcTAX2Full;




//typedef struct _stcFlshRec   	//??????????
//{
//	uint32	StoreCnt;         	//?????    		4   ?????

//	uint8	RecTypCod;       	//????          	1   ????(???????????????)
//	uint8	RelSpeed[3];      	//??              	3   D9~D0:??,D19~D10:??

//	uint8	Time[4];          	//?/?/?/?/?      	4   D5~D0:?,D11~D6:?,D16~D12:?D21~D17:?,
//	                               	//                      	D25~D22:? ;D26~D31:?
//	uint8	LocoTyp;          	//????          	1   
//	uint8	E_LocoTyp;        	//????????  	1   ????????,???LKJ2000????
//	uint8 	LocoNum[2];       	//???            	2	

//	uint8 	TrainTyp[4];     	//????          	4   ????,???????(??[2005]72???)
//	                             	//                      	????????,???LKJ2000????
//	                             	
//	uint8	TrainNum[3];     	//??????      	3   ???????(??[2005]72??)???????
//	uint8 	Car_Truck;       	//?/???/?       	1   D0=0/1 ? ?/?   D1=0/1 ? ?/?   
//	 
//	uint8 	VoitureCnt;       	//??              	1	
//	uint8 	KmMark[3];   		//???            	3   ??:?

//	uint8 	Weight[2];       	//??              	2
//	uint8 	PlanLen[2];       	//??              	2   ??:0.1   

//	uint8 	MstDriverNum[2];  	//???            	2	
//	uint8 	E_MstDriverNum; 	//???????    	1   
//	uint8 	E_SlvDriverNum;   	//????????  	1   

//	uint8 	SlvDriverNum[2];  	//????          	2   
//	uint8	DriverUnitNum[2];  	//??????      	2   //????????

//	uint8 	RoadNum;          	//???(???)     	1	
//	uint8  	RelRoadNum;     	//?????         	1   ?????LKJ2000??   
//	uint8  	StationNum;     	//???            	1
//	uint8  	E_StationNum;   	//???????    	1   ???????

//	uint8 	SignalTyp;        	//?????        	1   B2-B0 :2-??,3-??,4-??,5-??,6-??
//	uint8 	LocoSign;        	//????          	1   B4 = 0/1  ??/??;   B3~B0 0-??,1-?,2-?, 
//	                            	//                      	3-??,4-??,5-?,6-?,7-??,8-?
//	uint8 	LocoWorkState;    	//????          	1   b0-??,B1-??,B2-??,B3-??,B4-??
//	uint8 	LocoState;      	//????          	1   B0 = 1/0 - ??/??; B2 = 1/0 - ??/???

//	uint8 	SignalNum[2];      	//?????        	2   
//	uint8 	LocoPipePress[2]; 	//????          	2   B9-B0:??(??:1kPa)
//	  
//	uint32 	MstDip;           	//????          	4   ?????(???????????,????????)
//	uint32 	SlvDip;           	//????          	4   ?????(???????????,????????)
//	int32 	MstLocoPower;       //??????       	4   ????????
//	int32 	SlvLocoPower;     	//??????       	4   ????????	
//	//090901
// 	uint16	MstDip1Prs;        	//??            		2   ????1???
//	uint16	MstDip2Prs;        	//??            		2   ????2???
//	
//	uint16	SlvDip1Prs;       	//??            		2   ????1???
//	uint16 	SlvDip2Prs;       	//??            		2   ????2???
//	
//	uint8  	MyYear;           	//?      				1   ??????
//	uint8 	MyMonth;         	//?      				1   ??????
//	uint8 	MyData;          	//?      				1   ??????
//	uint8 	MyHour;           	//?      				1   ??????
//	
//	uint8 	MyMinute;     		//?      				1   ??????
//	uint8 	MySecond;       	//?       				1   ??????
//	uint16	MstDensity;			//??					2	??????
//	
//	uint16	SlvDensity;			//??					2	??????
//	uint16	GpsHeight;			//??					2	????
//	
//	int32	GpsLongitude;		//??					4	????
//	int32	GpsLatitude;		//??					4	????
//		
//	int16	MstEngRotSpd;		//???????		2	???????
//	int16	SlvEngRotSpd;		//???????		2	???????
//	//???? 
//	//?????????????
//	uint16 	JcRealType;			//????				2   ?????????
//	uint16 	JcRealNo;			//????				2   ?????????
//	
//	uint16 	MstPotPress;		//????				2	?????	
//	uint16 	SlvPotPress;		//????				2	?????	
//	
//	uint16 	MstPot1;			//????1				2	?????	
//	uint16 	MstPot2;			//????2				2	?????
//	
//	uint16 	SlvPot1;			//????1				2	?????		
//	uint16 	SlvPot2;			//????2				2	?????
//	
//	uint16 	MaxSpeed;			//??					2	?????	
//	uint16 	MstOcurrent;		//??????   		2	?????	
//	
//	uint8	ErrorCode;			//????				1   0~255
//	uint8 	DipValChgState;  	//??????   		1   ???????:?????/?????????????????
//	//090901
//	uint8	MstDipTemp;			//??					1	????
//	uint8	OilBoxModel;		//????				1	??????
//	
//	uint8	SoftVes;        	//????          	1   
//	uint8	Reserve1;        	//??          		1  	
////	uint16	Reserve0;        	//??          		2   
//	uint16 	CrcCheck;         	//??????    		2   Flash????CRC??
//}stcFlshRec;

typedef struct _stcFlshRec   	//�����ͳ߼�¼���ݽṹ
{
	uint32	StoreCnt;         	//�洢��ˮ��    		4   ׷�ټ�¼��

	uint8	RecTypCod;       	//��¼����          	1   �������ͣ��������ϰ࿨���°࿨�����ݼ�¼��
	uint8	RelSpeed[3];      	//ʵ��              	3   D9~D0��ʵ�٣�D19~D10��Ԥ��

	uint8	Time[4];          	//��/��/ʱ/��/��      	4   D5~D0:��,D11~D6:��,D16~D12:ʱD21~D17���գ�
	                               	//                      	D25~D22���� ;D26~D31:��
	uint8	LocoTyp;          	//�����ͺ�          	1   
	uint8	E_LocoTyp;        	//�����ͺ���չ�ֽ�  	1   �����ͺ������ֽ�,������LKJ2000��ʽ��ͬ
	uint8 	LocoNum[2];       	//������            	2	

	uint8 	TrainTyp[4];     	//��������          	4   ��������,���α����·���(����[2005]72���ļ�)
	                             	//                      	�ĳ��������ʶ��,������LKJ2000��ʽ��ͬ
	                             	
	uint8	TrainNum[3];     	//�������ֲ���      	3   ���α����·���(����[2005]72����)�ĳ������ݲ���
	uint8 	Car_Truck;       	//��/������/��       	1   D0��0/1 �� ��/��   D1��0/1 �� ��/��   
	 
	uint8 	VoitureCnt;       	//����              	1	
	uint8 	KmMark[3];   		//�����            	3   ��λ����

	uint8 	Weight[2];       	//����              	2
	uint8 	PlanLen[2];       	//�Ƴ�              	2   ��λ��0.1   

	uint8 	MstDriverNum[2];  	//˾����            	2	
	uint8 	E_MstDriverNum; 	//˾������չ�ֽ�    	1   
	uint8 	E_SlvDriverNum;   	//��˾������չ�ֽ�  	1   

	uint8 	SlvDriverNum[2];  	//��˾����          	2   
	uint8	DriverUnitNum[2];  	//˾����λ���      	2   //����Ψһȷ��˾��

	uint8 	RoadNum;          	//���κ�(��·��)     	1	
	uint8  	RelRoadNum;     	//ʵ�ʽ�·��         	1   �����ʽ��LKJ2000��ͬ   
	uint8  	StationNum;     	//��վ��            	1
	uint8  	E_StationNum;   	//��վ����չ�ֽ�    	1   ��վ����չ�ֽ�

	uint8 	SignalTyp;        	//�źŻ�����        	1   B2-B0 :2-��վ,3-��վ,4-ͨ��,5-Ԥ��,6-����
	uint8 	LocoSign;        	//�����ź�          	1   B4 = 0/1  ����/���;   B3~B0 0-�޵�,1-��,2-��, 
	                            	//                      	3-˫��,4-���,5-��,6-��,7-�̻�,8-��
	uint8 	LocoWorkState;    	//��������          	1   b0-��λ,B1-���,B2-��ǰ,B3-�ƶ�,B4-ǣ��
	uint8 	LocoState;      	//װ��״̬          	1   B0 = 1/0 - ����/���; B2 = 1/0 - ����/�ǵ���

//	uint8 	SignalNum[2];      	//�źŻ����        	2   
//	uint8 	LocoPipePress[2]; 	//�г���ѹ          	2   B9-B0:��ѹ(��λ:1kPa)

	uint16	Myspeed1;			//�Բ��ٶ�1				2
	uint16	Myspeed2;			//�Բ��ٶ�2				2	
	  
	uint32 	MstDip;           	//��������          	4   ���ͳ�����(���ӻ�����ʱΪ��������,����Ϊ����������)

//	uint32 	SlvDip;           	//�ӻ�����          	4   ���ͳ�����(���ӻ�����ʱΪ�ӻ�����,���������ֵΪ��)
	uint32	MyKileMeter;		//�����				4
		
	int32 	MyMstLocoPower;     //������������       	4   ��������豸����

//	int32 	SlvLocoPower;     	//�ӻ���������       	4   �ӻ�����豸����
	uint32	MyPower;			//�ۼƵ���				4	
	//090901
 	//uint16	MstDip1Prs;        	//ѹǿ            		2   �����ͳ�1ѹǿֵ
	//uint16	MstDip2Prs;        	//ѹǿ            		2   �����ͳ�2ѹǿֵ
	int16		Myhig1;				//Һλ�߶�1				2	
	int16		Myhig2;				//Һλ�߶�2				2							

	uint16	SlvDip1Prs;       	//ѹǿ            		2   �ӻ��ͳ�1ѹǿֵ
	uint16 	SlvDip2Prs;       	//ѹǿ            		2   �ӻ��ͳ�2ѹǿֵ
	
	uint8  	MyYear;           	//��      				1   װ��ʱ�����
	uint8 	MyMonth;         	//��      				1   װ��ʱ�����
	uint8 	MyData;          	//��      				1   װ��ʱ�����
	uint8 	MyHour;           	//ʱ      				1   װ��ʱ���ʱ
	
	uint8 	MyMinute;     		//��      				1   װ��ʱ��ķ�
	uint8 	MySecond;       	//��       				1   װ��ʱ�����
	uint16	MstDensity;			//�ܶ�							2	����ȼ���ܶ�
	
//	uint16	SlvDensity;			//�ܶ�						2	�ӻ�ȼ���ܶ�
//	uint16	GpsHeight;			//�߶�						2	����߶�
	int16		MyAddspeed;			//�Բ���ٶ�					2
	uint16	MyDip;				//�Բ�����							2
		
	int32	GpsLongitude;		//����					4	������
	int32	GpsLatitude;		//γ��					4	����γ��
		
	int16	MstEngRotSpd;		//�������ͻ�ת��		2	�������ͻ�ת��
//	int16	SlvEngRotSpd;		//�ӻ����ͻ�ת��		2	�ӻ����ͻ�ת��
	int16	MyEngRotSpd;		//�ӻ����ͻ�ת��		2	�ӻ����ͻ�ת��

	//�������� 
	//���Լ�ʱ��оƬ���׵�������
	uint16 	JcRealType;			//�����ͺ�				2   �ⲿ���õĻ����ͺ�
	uint16 	JcRealNo;			//�������				2   �ⲿ���õĻ������
	
//	uint16 	MstPotPress;		//������ѹ				2	Ԥ���Ӽ��	
//	uint16 	SlvPotPress;		//�ӻ���ѹ				2	Ԥ���Ӽ��	
	uint16	MyDip1Tmp;	  		//�ͳ�1�¶�
	uint16	MyDip2Tmp;			//�ͳ�2�¶�
		
//	uint16 	MstPot1;			//��������1				2	Ԥ���Ӽ��	
//	uint16 	MstPot2;			//��������2				2	Ԥ���Ӽ��
	uint16	MyDip1Den;
	uint16	MyDip2Den;	

	
	
//	uint16 	SlvPot1;			//�ӻ�����1				2	Ԥ���Ӽ��		
//	uint16 	SlvPot2;			//�ӻ�����2				2	Ԥ���Ӽ��
	uint16	MyDip1Err;
	uint16	MyDip2Err;
	
	uint16 	MaxSpeed;			//����					2	Ԥ���Ӽ��	
//	uint16 	MstOcurrent;		//����ԭ�ߵ���   		2	Ԥ���Ӽ��
	uint16	ErrNum;				//���й�������			2	
	
	
	uint8	ErrorCode;			//���ϴ���				1   0~255
//	uint8 	DipValChgState;  	//�����仯״̬   		1   �����仯����֣����ͳ�����/��С���仯ƽ�ȡ���΢���������Ҳ���
	uint8	MyLocoWorkState;	//�Բ����״̬			1
	//090901
	uint8	MstDipTemp;			//�¶�					1	�����¶�
	uint8	OilBoxModel;		//����ģ��				1	�����������
	
	uint8	SoftVes;        	//����汾          	1   
	uint8	Reserve1;        	//Ԥ��          		1  	
//	uint16	Reserve0;        	//Ԥ��          		2   
	uint16 	CrcCheck;         	//�洢��У���    		2   Flash��¼�洢CRCУ��
}stcFlshRec;



typedef struct _stcLog_							//Fram��־����   12
{
	uint16			DriveNum;					//�豸���	   2 
	uint8			LocoTyp[2];					//�����ͺ�     2
	uint8			LocoNum[2];					//�������     2
	uint8			ErrorCode;					//���ϴ���     1
	uint8			RecTypCod;					//��¼����	   1
	uint32			StoreCnt;					//��ˮ��       4
}stcLog;

typedef struct _stcLogZone_			//Fram��־����
{
	stcLog			sLog[100];
	uint16			Times;						//Ԥ��
	uint16			CrcCheck;					//CRC����
}stcLogZone;



#endif
