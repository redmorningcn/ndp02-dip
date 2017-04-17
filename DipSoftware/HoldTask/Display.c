#include 	"string.h"
#include <includes.h>

#define		SCK1			7	
#define		MISO1			8	
#define		MOSI1			9
#define		CS_DIS			213		
#define		SOFT_SPI_CS1	CS_DIS


//����˿ڼ���������---------------------------------------------------------------
//#define     DDR_7219    DDRB 
//#define     PINT_7219   PINB
//#define     PORT_7219   PORTB  
//#define     CS_7219     4                       //��������

//max7219�Ĵ�����ַ����-------------------------------------------------------------
#define     NoOp        0x00                    // �ղ����Ĵ���
#define     Digit0      0x01                    // �����1�Ĵ���
#define     Digit1      0x02                    // �����2�Ĵ���
#define     Digit2      0x03                    // �����3�Ĵ���
#define     Digit3      0x04                    // �����4�Ĵ���
#define     Digit4      0x05                    // �����5�Ĵ���
#define     Digit5      0x06                    // �����6�Ĵ���
#define     Digit6      0x07                    // �����7�Ĵ���
#define     Digit7      0x08                    // �����8�Ĵ���
/**/
#define     DecodeMode  0x09                    // ����ģʽ�Ĵ���
#define     Intensity   0x0a                    // ���ȼĴ���
#define     ScanLimit   0x0b                    // ɨ��λ���Ĵ���
#define     ShutDown    0x0c                    // �͹���ģʽ�Ĵ���
#define     DisplayTest 0x0f                    // ��ʾ���ԼĴ���
//max7219���ƼĴ�������
#define     ShutdownMode    0x00                // �͹��ķ�ʽ
#define     NormalOperation 0x01                // ����������ʽ
//#define     DecodeDigit     0xff                // �������ã�8λ��ΪBCD��;��8����������   
#define     NoDecodeDigit   0x00                // �������ã���8������������   
#define     ScanDigit       0x07                // ɨ��λ�����ã���ʾ8λ�����
//#define   ScanDigit 0x03                      // ɨ��λ�����ã���ʾ8λ�����
#define   	IntensityGrade  0x0f                // ���ȼ�������
//#define     IntensityGrade  0x03              // ���ȼ�������
#define     TestMode    0x01                    // ��ʾ����ģʽ 
#define     TextEnd     0x00                    // ��ʾ���Խ������ָ���������ģʽ

////---------------------------------------------------------------------------------
////��������:             void InitIOForSPI1( void )
////��    ��:             ����Ӧ�˿ڳ�ʼ��ΪSPI��
////��ڲ���:             
////���ڲ���:             
////----------------------------------------------------------------------------------
void InitIOForSPI1( void )
{
	GPIO_PinselConfig(SCK1,0);
	GPIO_PinselConfig(MOSI1,0);
	GPIO_PinselConfig(MISO1,0);
	GPIO_PinselConfig(SOFT_SPI_CS1,0);
}
//void SPI1_Init(void)
//{
//	SSP_CFG_Type SSP_ConfigStruct;
//
//	SSP_ConfigStructInit(&SSP_ConfigStruct);
//	// Initialize SSP peripheral with parameter given in structure above
//	SSP_Init(LPC_SSP1, &SSP_ConfigStruct);
//
//	// Enable SSP peripheral
//	SSP_Cmd(LPC_SSP1, ENABLE);
//}
//
//
//void InitIOForSPI1( void )
//{
//	GPIO_PinselConfig(SCK1,2);
//	GPIO_PinselConfig(MOSI1,2);
//	GPIO_PinselConfig(MISO1,2);
//	GPIO_PinselConfig(SOFT_SPI_CS1,0);
//
//	SPI1_Init();
//}

//------------------------------------------------------------------------
//  ��  �� ��void WriteSCK1( uint8 temp )
//  ��  �� ������ SCK1
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteSCK1(uint8 temp)
{	
	if(temp)		
	{
		GPIO_SetOrClearValue(SCK1,1);
	}
	else
	{
		GPIO_SetOrClearValue(SCK1,0);		
	}	
	nop();	
}

//------------------------------------------------------------------------
//  ��  �� ��uint8 ReadSCK1(void)
//  ��  �� ����ȡ SCK1 ��ֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
uint8 ReadSCK1(void)
{
	uint8 temp;
	
	temp = 	GPIO_ReadIoVal(SCK1);
	nop();
	return temp;
}

//------------------------------------------------------------------------
//  ��  �� ��void WriteMOSI1( uint8 temp )
//  ��  �� ������ MOSI1
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteMOSI1(uint8 temp)
{
	if(temp)		
	{
		GPIO_SetOrClearValue(MOSI1,1);
	}
	else
	{
		GPIO_SetOrClearValue(MOSI1,0);		
	}	
	nop();		
}

//------------------------------------------------------------------------
//  ��  �� ��uint8 ReadMOSI1(void)
//  ��  �� ����ȡ MOSI1 ��ֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
uint8 ReadMOSI1(void)
{
	uint8 temp;
	
	temp = 	GPIO_ReadIoVal(MOSI1);
	nop();
	return temp;
}

//------------------------------------------------------------------------
//  ��  �� ��void WriteMOSI1( uint8 temp )
//  ��  �� ������ MOSI1
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteMISO1(uint8 temp)
{
	if(temp)		
	{
		GPIO_SetOrClearValue(MISO1,1);
	}
	else
	{
		GPIO_SetOrClearValue(MISO1,0);		
	}
		
	nop();		
}

//------------------------------------------------------------------------
//  ��  �� ��uint8 ReadMOSI1(void)
//  ��  �� ����ȡ MOSI1 ��ֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
uint8 ReadMISO1(void)
{
	uint8 temp;

	temp = 	GPIO_ReadIoVal(MISO1);

	nop();
	return temp;
}

//------------------------------------------------------------------------
//  ��  �� ��void WriteMOSI1( uint8 temp )
//  ��  �� ������ MOSI1
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteSoftSpiCS1(uint8 temp)
{
	if(temp)		
	{
		GPIO_SetOrClearValue(SOFT_SPI_CS1,1);
	}
	else
	{
		GPIO_SetOrClearValue(SOFT_SPI_CS1,0);		
	}	

	nop();		
}

void WriteCS_DIS(uint8 temp)
{
	WriteSoftSpiCS1(temp);
}

//---------------------------------------------------------------------------------
//��������:             void SentByte_SPI1(uint8 ch)
//��    ��:             SPI����һ�ֽ�����
//��ڲ���:             Data8
//���ڲ���:             ��
//˵    ��:				��ģ��SPI���߷�ʽ��������
//----------------------------------------------------------------------------------
void SentByte_SPI1(uint8 ch)
{
	uint8 i,temp;   
	
	WriteSCK1 ( 0 );

    for (i=0;i<8;i++)
    {
		temp=ch&0x80;
    	ch=ch<<1;
        if(temp)
        {
        	WriteMOSI1( 1 );	

        	WriteSCK1 ( 0 );

        	WriteSCK1 ( 1 );	        	
        }
        else
        {
        	WriteMOSI1( 0 );	

            WriteSCK1 ( 0 );
            
        	WriteSCK1 ( 1 );
        }
		NOP();
    }
        
    WriteSCK1 ( 0 );
}
//void SentByte_SPI1(uint8 ch)
//{
//	uint32	time;
//	time = GetSysTime();
//
//	SSP_SendData(LPC_SSP1,ch);
//	while(SSP_GetStatus(LPC_SSP1,SSP_STAT_TXFIFO_EMPTY)!=SET)
//	{	
//		printfcom0("\r\n test");
//		if(GetSysTime()-time>100)
//		{
//			
//			return;	
//		}	
//	}
//}

//----------------------------------------------------------------------------
//��������:   void SentByteTo7219(uint8 Addr,uint8 Num) 
//��    ��:   ��7219����1Byte���ݻ�����
//��ڲ���:   addr:   ���ݽ��յ�ַ
//            num:    Ҫ�������
//���ڲ���:   ��
//-----------------------------------------------------------------------------
void SentByteTo7219(uint8 Addr,uint8 Num) 
{ 
	 WriteCS_DIS( 0 );	
	 		   					   		
  	 SentByte_SPI1( Addr );		
             										
  	 SentByte_SPI1( Num );   
	                  	
  	 WriteCS_DIS( 1 );			  									
}


typedef	struct  _stcDisplay
{
	char	Buf[12];
	uint32	Time;			//��ʾ��ʱ��
	uint32	Degree;			//��ʾ�Ĵ���
//	uint8	Enable;			
}stcDisplay;

#define		DIS_BUF_NUM		10
stcDisplay	sDisplay[DIS_BUF_NUM];
stcDisplay	sDisplayBak[DIS_BUF_NUM];

//----------------------------------------------------------------------------
// ��    �ƣ�   uint32 Displayf(char *fmt, va_list param) 
// ��    �ܣ�   
// ��ڲ�����  

// ���ڲ�����   
//----------------------------------------------------------------------------  
void InitDisplayBuf(void)
{
	uint8	i;
	
	for(i = 0; i < DIS_BUF_NUM;i++)
	{
		sDisplay[i].Degree = 0;
	}
}

//----------------------------------------------------------------------------
// ��    �ƣ�   void ClaerDisplaySet(void)
// ��    �ܣ�   
// ��ڲ�����  

// ���ڲ�����   
//----------------------------------------------------------------------------  
void ClaerDisplaySet(void)
{
	uint8	i;
	
	memcpy((uint8 *)sDisplayBak,(uint8 *)sDisplay,sizeof(sDisplay));  //888888
	
	for(i = 0; i < DIS_BUF_NUM;i++)			//����ʾ
	{
		sDisplay[i].Degree = 0;			
	}
}

//----------------------------------------------------------------------------
// ��    �ƣ�   void ClaerDisplaySetWithoutStore(void)
// ��    �ܣ�   
// ��ڲ�����  

// ���ڲ�����   
//----------------------------------------------------------------------------  
void ClaerDisplaySetWithoutStore(void)
{
	uint8	i;
		
	for(i = 0; i < DIS_BUF_NUM;i++)			//����ʾ
	{
		sDisplay[i].Degree = 0;			
	}
}

extern	void InitDisplay (void);

//----------------------------------------------------------------------------
// ��    �ƣ�   void ResumeDisplaySet(void)
// ��    �ܣ�   
// ��ڲ�����  

// ���ڲ�����   
//----------------------------------------------------------------------------  
void ResumeDisplaySet(void)
{	
	InitDisplay();

	memcpy((uint8 *)sDisplay,(uint8 *)sDisplayBak,sizeof(sDisplay)); 	//888888
}

//-------------------------------------------------------------------
//��������:     void InitDisplay (void)
//��    ��:     7219��ʼ��
//��ڲ���:     ��
//���ڲ���:     ��
//-------------------------------------------------------------------
void InitDisplay (void)
{
	InitIOForSPI1();								//SPI�˿ڳ�ʼ��IO��
	
	InitDisplayBuf();								//��ʼ����ʾ������
	
    SentByteTo7219 (DisplayTest,TextEnd);         	// ���ù���ģʽ
	SentByteTo7219 (ScanLimit,ScanDigit);         	// ����ɨ�����
    SentByteTo7219 (DecodeMode,NoDecodeDigit);      // ���ò�����ģʽ
    SentByteTo7219 (Intensity,IntensityGrade);    	// ��������
    SentByteTo7219 (ShutDown,NormalOperation);    	// ����Ϊ��������ģʽ
}
		  
uint8 LedNumCode[]={0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B,0x77,
                   // 0    1    2    3    4    5    6    7    8    9    A 
                     0x1F,0x4E,0x3D,0x4F,0x47};  
                   // b   C    d     E    F      

uint8 LedCharCode[] = {0x00,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0x80,0x01,0x80,0xE5,
					//       !    "    #    $    %    &    '    (     )    *    +    ,    -    .   /
					  0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B, 
					// 0    1    2		3   4    5    6    7    8    9	
					  0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,0xE5,
					// :    ;    <    =     >   ?    @
					  0x77,0x1F,0x4E,0x3d,0x4F,0x47,0x5F,0x37,0x30,0x3c,0x87,0x0e,0xE5,
                    //  A    B   C    D     E    F    G    H   I    J    K    L    M    
                      0x76,0x7E,0x67,0xFE,0x66,0x5B,0x0F,0x3E,0x3E,0xE5,0x37,0x33,0x6D,
                    //  N    O    P   Q    R     S    T    U    V   W    X    Y    Z     
                      0xE5,0xE5,0xE5,0xE5,0x08,0xE5,
                     // [    \    ]    ^    _    `
                      0x77,0x1F,0x0D,0x3D,0x4F,0x47,0x7B,0x17,0x30,0x3c,0x87,0x0e,0xE5,
                     // a    b   c    d     e    f    g    h    i    j     k    l    m
					  0x15,0x1D,0x67,0x73,0x05,0x5B,0x0F,0x1C,0x1C,0xD3,0x37,0x33,0x6D,
                     // n    o   p    q     r    s    t    u    v   w    x    y    z     
                      0xE5,0xE5,0xE5,0xE5,0xE5,0x00//
                      // {    |    }    ~       ��
					   };     
           
#define     LED_CHAR_NNM    	16                  //�������ʾ������� 


#define     DISPLAY_LED_NUM 	8                   //����ܸ���   

        
//--------------------------------------------------------------------
//void          DisplayNum (uint32 Unmber)
//��    ��:     ������ܽ�����������ʾ����
//��ڲ���:     number
//���ڲ���:     ��
//-------------------------------------------------------------------
void    DisplayNum (uint32 Unmber)
{
    unsigned char i  = DISPLAY_LED_NUM;
	unsigned char digit[8] = {Digit0,Digit1,Digit2,Digit3,Digit4,Digit5,Digit6,Digit7};
	
	InitDisplay();                                //��ʾ��ʼ��
	
	do
	{ 		
		i--;
		SentByteTo7219(digit[i],LedNumCode[Unmber % 10] );       //�ӵ�λ����λ��ʾ
		Unmber /= 10;                       
	}while(i && Unmber);
		
	while(i)
	{
        i--;
        SentByteTo7219(digit[i],0x00);            //��û����λ����ʾ���        
    }	  
}

//--------------------------------------------------------------------
//void          DisplayNumWithDoit (uint32 Unmber)
//��    ��:     ������ܽ�����������ʾ����
//��ڲ���:     number
//���ڲ���:     ��
//-------------------------------------------------------------------
void    DisplayNumWithDot (uint32 Unmber)
{
    unsigned char i  = DISPLAY_LED_NUM;
	unsigned char digit[8] = {Digit0,Digit1,Digit2,Digit3,Digit4,Digit5,Digit6,Digit7};

	do
	{ 		
		i--;
		SentByteTo7219(digit[i],LedNumCode[Unmber % 10] + 0x80);	//�ӵ�λ����λ��ʾ
		Unmber /= 10;                       
	}while(i && Unmber);
		
	while(i)
	{
        i--;
        SentByteTo7219(digit[i],0x00);            					//��û����λ����ʾ���        
    }	  
}

//------------------------------------------------------
//��������:     DisplayString ()
//��    ��:     ���������ʾ�ַ�������
//��ڲ���:     String: �ַ�����
//���ڲ���:     ��
//��ʾ����:     String
//���ݴ���:	    ���ø�ʽ  DisplayString("ABCD");
//-------------------------------------------------------
void DisplayString(char * String)
{
	uint8   i = 0;
	uint8   digit[8] = {Digit0,Digit1,Digit2,Digit3,Digit4,Digit5,Digit6,Digit7};
	uint8   CharTemp;
	uint8	DotNum = 0;
	
	while( i < DISPLAY_LED_NUM)
	{
        SentByteTo7219(digit[i],0x00);                      						//��û����λ����ʾ���  
          
        i++;    
    }	
	
	i = 0;
	while(i < DISPLAY_LED_NUM + DotNum  && strlen((char *)String) - i > 0)
	{ 		
		i++;
		if(String[strlen((char *)String) - i - DotNum] >= ' '  )					//
		{
			if(String[strlen((char *)String) - i - DotNum] != '.' )					//��'.'���д���
			{
				CharTemp = String[strlen((char *)String)- i - DotNum] - ' ' ; 		//����ʾ�ַ�λ��,LedCharCodeλ��
				SentByteTo7219(digit[DISPLAY_LED_NUM - i],LedCharCode[CharTemp] );	//�ӵ�λ����λ��ʾ      
			}
			else
			{	
				if(String[strlen((char *)String)- i - DotNum - 1] != '.')
				{
					CharTemp = String[strlen((char *)String)- i - DotNum - 1] - ' ';  
					SentByteTo7219(digit[DISPLAY_LED_NUM - i],LedCharCode[CharTemp] + 0x80);
					DotNum++;
				}  
				else
				{
					CharTemp = String[strlen((char *)String)- i - DotNum ] - ' ' ; 
					SentByteTo7219(digit[DISPLAY_LED_NUM - i],LedCharCode[CharTemp]); 
				}
			}
		}      
	}
}

//------------------------------------------------------
//��������:MovDisplayChar ()
//��    ��:���������ʾ�ַ����Ѷ��ַ�
//��ڲ���:character: �ַ�����
//���ڲ���:��
//��ʾ����:   -   E   H   L   P   Black
//���ݴ���:	  A	  B	  C	  D	  E	  F	  
//-------------------------------------------------------
void MovDisplayChar (uint8 character)
{
	uint8 i = DISPLAY_LED_NUM ,j;
	uint8 digit[8] = {Digit0,Digit1,Digit2,Digit3,Digit4,Digit5,Digit6,Digit7};
		
	for(j = 0;j < 12; j++)
	{
	 	 i = DISPLAY_LED_NUM;
		 while(i)
		 {
            i--;
            SentByteTo7219(digit[i],0x00);            						//��û����λ����ʾ���
         }	
		 
		SentByteTo7219(digit[j%4],LedNumCode[character%LED_CHAR_NNM]);       //�ӵ�λ����λ��ʾ   
		DelayX10ms(20);                 
	}
}

//----------------------------------------------------------------------------
// ��    �ƣ�   uint32 Displayf(char *fmt, va_list param) 
// ��    �ܣ�   
// ��ڲ�����  

// ���ڲ�����   
//----------------------------------------------------------------------------  
uint32 Displayf(char *fmt, ...) 
{ 
   va_list  argptr;
   uint32   cnt;
   char     a[255];
   
   strlen(fmt);
   if(strlen(fmt) > (sizeof(a) - 55))
   {
        return FALSE;
   }
   va_start(argptr, fmt);
   
   cnt = vsprintf(a, fmt, argptr);
   
   va_end(argptr);
   
   DisplayString(a); 
	
   return(cnt);
}

extern	void   FeedDog(void);
//----------------------------------------------------------------------------
// ��    �ƣ�   uint32 DisplaySet(uint32 Time,uint32 Degree,char *fmt, ... )
// ��    �ܣ�   ����Ҫ��ʾ��ֵ
// ��ڲ�����   Time����ʾʱ�䣬Degree����ʾ������*fmt����ʾ����
// ���ڲ�����   
//----------------------------------------------------------------------------  
uint32 DisplaySet(uint32 Time,uint32 Degree,char *fmt, ... ) 
{ 
   va_list  argptr;
   uint32   cnt;
   char     a[255];
   //char     b[10] = {' ',' ',' ',' '};
   uint32	i,j;
   
   strlen(fmt);
   if(strlen(fmt) > (sizeof(a) - 55))
   {
        return FALSE;
   }
   va_start(argptr, fmt);
   
   cnt = vsprintf(a, fmt, argptr);
   
   va_end(argptr);

   FeedDog();							//ι��

   for(i= 0 ;i < DIS_BUF_NUM; i++)
   {
       if(sDisplay[i].Degree == 0)
       {	
       		for(j = 0; j< sizeof(sDisplay[i].Buf); j++)
       		{
       			sDisplay[i].Buf[j] = '\0';
       		}
       			
       	   	sDisplay[i].Time 	= Time;
       	   	sDisplay[i].Degree 	= Degree;
       	   	memcpy(sDisplay[i].Buf,a,cnt);
			
       	   /*
       	   /////////////////////////////////////
       	   if(cnt > 4)
       	   {
       	   		if(cnt-4<4)
       	   		{
       	   			memcpy(sDisplay[i].Buf,&a[4],cnt-4);
       	   			memcpy(&sDisplay[i].Buf[cnt-4],b,4-(cnt-4));
       	   			memcpy(&sDisplay[i].Buf[4],a,4);
       	   		}
       	   		else
       	   		{
       	   			memcpy(sDisplay[i].Buf,&a[4],4);
       	   			memcpy(&sDisplay[i].Buf[4],a,4);	
       	   		}
       	   }
       	   else
       	   {/ *
				memcpy(sDisplay[i].Buf,&a[4],cnt-4);
				memcpy(&sDisplay[i].Buf[cnt-4],b,4-(cnt-4));
				memcpy(&sDisplay[i].Buf[4],a,4);
			* /	
       	   		memcpy(sDisplay[i].Buf,b,4);
       	   		memcpy(&sDisplay[i].Buf[4],a,cnt);
       	   		memcpy(&sDisplay[i].Buf[4+ cnt],b,(4-cnt));
       	   }
       	   */    	  	
		   return 1;
       }
   }
   
   return(cnt);
}	

//----------------------------------------------------------------------------
// ��    �ƣ�   void DisplayContrl(void) 
// ��    �ܣ�   
// ��ڲ�����  

// ���ڲ�����   
//----------------------------------------------------------------------------  
void DisplayContrl(void) 
{
	static	uint8	i = 0;
	static  uint32	Time = 0;
	static	uint32	DisplayTimes = 0;
	static  uint32	LastTime = 0;
//	static	uint32	DisResTimes = 0;	
		
	while(i < DIS_BUF_NUM)
	{
	   if(sDisplay[i].Degree != 0)
       {	
       	   if(DisplayTimes == 0)
       	   {
       	   	    Time = sDisplay[i].Time;
       	   }

       	   if(Time != 0)
       	   {
				//Time--;
				DisplayString(sDisplay[i].Buf);

				if(Time > GetSysTime() - LastTime)
				{
					Time -= (GetSysTime() - LastTime);
				}
				else
				{
					Time = 0;
				}
				
				DisplayTimes++;
       	   }
       	   else
       	   {
       	   		sDisplay[i].Degree = sDisplay[i].Degree - 1;  
       	   		DisplayTimes = 0;
       	   		i++;
       	   }
       	   
       	   LastTime = GetSysTime();
       	   return ;
       }
	   
	   DisplayTimes = 0;
	   i++;
   	}
   	
   	LastTime = GetSysTime();
   	i = 0;
}

//----------------------------------------------------------------------------
// ��    �ƣ�   void HoldDisplay(void) 
// ��    �ܣ�   ��ʾά��	
// ��ڲ�����  

// ���ڲ�����   
//----------------------------------------------------------------------------  
void HoldDisplay(void) 
{
	DisplayContrl();			
}
