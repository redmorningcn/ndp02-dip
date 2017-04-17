#include <includes.h>

#define			SCK0					15    	//p1.20  
#define			MISO0					17			//p1.23  
#define			MOSI0					18			//p1.24 
#define   		SOFT_SPI_CS0			16			//p1.22

//#define		Hard_SPI0   //ӲSPI����
void	nop(void)
{
	uint8 i;
    i =20;
	NOP();
	while(i--);
}

void	InitFlshIO(void)
{
	GPIO_PinselConfig(SCK0,0);
	GPIO_PinselConfig(MOSI0,0);	
	GPIO_PinselConfig(MISO0,0);	
}

//------------------------------------------------------------------------
//  ��  �� ��void WriteSCK0( uint8 temp )
//  ��  �� ������ SCK0
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteSCK0(uint8 temp)
{
	if(temp)		
	{
		GPIO_SetOrClearValue(SCK0,1);
	}
	else
	{
		GPIO_SetOrClearValue(SCK0,0);		
	}	
	//nop();	
}

//------------------------------------------------------------------------
//  ��  �� ��uint8 ReadSCK0(void)
//  ��  �� ����ȡ SCK0 ��ֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
uint8 ReadSCK0(void)
{
	uint8 temp;
	
	temp = 	GPIO_ReadIoVal(SCK0);
	//nop();
	return temp;
}

//------------------------------------------------------------------------
//  ��  �� ��void WriteMOSI0( uint8 temp )
//  ��  �� ������ MOSI0
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteMOSI0(uint8 temp)
{
	
	if(temp)		
	{
		GPIO_SetOrClearValue(MOSI0,1);
	}
	else
	{
		GPIO_SetOrClearValue(MOSI0,0);		
	}	
	//nop();		
}

//------------------------------------------------------------------------
//  ��  �� ��uint8 ReadMOSI0(void)
//  ��  �� ����ȡ MOSI0 ��ֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
uint8 ReadMOSI0(void)
{
	uint8 temp;

	temp = 	GPIO_ReadIoVal(MOSI0);
	//nop();
	return temp;
}

//------------------------------------------------------------------------
//  ��  �� ��void WriteMOSI0( uint8 temp )
//  ��  �� ������ MOSI0
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteMISO0(uint8 temp)
{
	GPIO_PinselConfig(MISO0,0);
	
	if(temp)		
	{
		GPIO_SetOrClearValue(MISO0,1);
	}
	else
	{
		GPIO_SetOrClearValue(MISO0,0);		
	}
		
	//nop();		
}

//------------------------------------------------------------------------
//  ��  �� ��uint8 ReadMOSI0(void)
//  ��  �� ����ȡ MOSI0 ��ֵ
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
uint8 ReadMISO0(void)
{
	uint8 temp;
	
	temp = 	GPIO_ReadIoVal(MISO0);

	nop();
	return temp;
}

//------------------------------------------------------------------------
//  ��  �� ��void WriteMOSI0( uint8 temp )
//  ��  �� ������ MOSI0
// ��ڲ�������
// ���ڲ�������
//------------------------------------------------------------------------
void WriteSoftSpiCS0(uint8 temp)
{
	if(temp)		
	{
		GPIO_SetOrClearValue(SOFT_SPI_CS0,1);
	}
	else
	{
		GPIO_SetOrClearValue(SOFT_SPI_CS0,0);		
	}	

	nop();		
}

//---------------------------------------------------------------------------------
//��������:             SentByte_SPI()
//��    ��:             SPI����һ�ֽ�����
//��ڲ���:             Data8
//���ڲ���:             ��
//˵    ��:				��ģ��SPI���߷�ʽ��������
//----------------------------------------------------------------------------------
uint8 SendOrRecByte_SPI0(uint8 ch)
{
	uint8 i,temp;   
	
    for (i=0;i<8;i++)
    {
	  temp=ch&0x80;
      ch=ch<<1;

      if(temp)
      {
      	WriteMOSI0( 1 );	

      	WriteSCK0 ( 0 );

      	WriteSCK0 ( 1 );	        	
      }
      else
      {
      	WriteMOSI0( 0 );	

        WriteSCK0 ( 0 );
          
      	WriteSCK0 ( 1 );
      }
      
      ch |= ReadMISO0();
    }
    
    return	ch;
}

void	SendByte_SPI0(uint8	ch)
{
	SendOrRecByte_SPI0(ch);
}

uint8	RecByte_SPI0(void)
{
	uint8	ch =0;
	return	SendOrRecByte_SPI0(ch);
}

