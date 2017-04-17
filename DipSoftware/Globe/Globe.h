#ifndef  _Globe_h_
#define  _Globe_h_

//#include "DataTypeDef.h"
//#include "FIFO.h"
//#include "GlobePara.h"
//#include "CrcCheck.h"
//#include "BackUp.h"

#ifdef		HARD_VER_090214

#define		A1_LED			7
#define		A2_LED			6
#define		A3_LED			5
#define		A4_LED			4
#define		B1_LED			3
#define		B2_LED			2
#define		B3_LED			1
#define		B4_LED			0

#endif
/**/

//#ifdef		HARD_VER_111122
//
//#define		A1_LED			3
//#define		A2_LED			2
//#define		A3_LED			1
//#define		A4_LED			0
//#define		B1_LED			7
//#define		B2_LED			6
//#define		B3_LED			5
//#define		B4_LED			4
//
//#else

//#ifdef		HARD_VER_090426

#define		A1_LED			0
#define		A2_LED			1
#define		A3_LED			2
#define		A4_LED			3
#define		B1_LED			4
#define		B2_LED			5
#define		B3_LED			6
#define		B4_LED			7

//#endif

#endif


#define     DIP1_LED      		A2_LED
#define     DIP2_LED   			A2_LED
#define     CARD_LED      		A1_LED
#define     TAX2_LED   			A3_LED
#define     HOST_LED   			A4_LED
#define     RUN_LED        		B4_LED
#define     WRITE_CARD_LED  	B1_LED
#define     CARD_FULL_LED  		B2_LED

#define     COM3_STA_LED      	A3_LED
#define     COM2_STA_LED   		A2_LED
#define     COM1_STA_LED      	A1_LED
#define     LOCOSTA_LED   		B3_LED
#define     SPEED1_LED   		A4_LED
#define     RUN_STA_LED        	B4_LED
#define     SPEED2_LED  		B1_LED
#define     CSPEED_LED  		B2_LED

//----------------------------------------------------------------------------
// ��    �ƣ�   void HardInit(void)
// ��    ��:    Ӳ����ʼ��
// ��ڲ�����	
// ���ڲ�����	
//----------------------------------------------------------------------------
extern	void HardInit(void);

//----------------------------------------------------------------------------
// ��    �ƣ�   void SysInit(void)
// ��    ��:    ϵͳ��ʼ��
// ��ڲ�����
// ���ڲ�����
//----------------------------------------------------------------------------
extern	void SysInit(void);

//----------------------------------------------------------------------------
// ��    �ƣ�   void SoftInit(void)
// ��    ��:    �����ʼ��
// ��ڲ����� 
// ���ڲ�����
//----------------------------------------------------------------------------
extern	void SoftInit(void);

//----------------------------------------------------------------------------
// ��    �ƣ�   uint8 JudgeStartEvt(void)
// ��    ��:    ���ؿ����¼���ʶ
// ��ڲ����� 
// ���ڲ�����
//----------------------------------------------------------------------------
extern	uint8 	JudgeStartEvt(void);

extern	void	SysHoldTast(void);
extern	void	SysFastHoldTast(void);
extern	void	ReCalPara(uint8 Flg);

//#endif

