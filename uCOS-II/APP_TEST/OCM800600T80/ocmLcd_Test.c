#include <includes.h>
#include "GUI.h"

void delay_us(uint16 nUs) 
{ 
uint8 time=12; 
for(;nUs>0;nUs--) 
{ 
time=12; 
while(time>0) 
time--; 
} 
} 

void page5()                                                           
{
//������ͼ����ɫ
SetBcolor(65504);
GUI_CleanScreen();

//��ʵ����Բ 
SetFcolor(0);
GUI_EllipseFill(32, 47, 182, 121);

//��ʵ�ľ��� 
SetFcolor(40544);
GUI_RectangleFill(14, 27, 46, 49);

//��������Բ 
SetFcolor(13945);
GUI_Ellipse(79, 11, 144, 99);

//��ʵ����Բ 
SetFcolor(65535);
GUI_CircleFill(174, 102, 17);

//��ʵ����Բ 
SetFcolor(40147);
GUI_CircleFill(174, 102, 8);

//������Բ 
SetFcolor(40147);
GUI_Circle(174, 101, 27);

//����
SetFcolor(51225);
GUI_Line(7, 134, 209, 19);

//�ı���ʾ
SetFcolor(0);
SetFont_Region(1, 169,59);
SetTextSpace(0,0);
DisText(132, 200, 0, 6, "������");

}

//void ocmLcdTask()
//{
//// delay_us(5000);
////// UartInit();     //���ڳ�ʼ��
//// page5(); 
//// while(1);     
//}
extern	 void Draw8Point(int x0,int y0, int xoff, int yoff);
extern   void SendChar(uint8	Data);
void LcdTask()
{
	uint32	i;
	delay_us(5000);
	  
	GUI_Init(); 

	while(1)
	{	   
		//GUI_Line(7, 134, 209, 19);
		//page5();


         //GUI_SetBkColor(GUI_BLUE);  
         //GUI_SetColor(GUI_RED); 
        GUI_Clear();  

		 //GUI_DispString("Hello world!");
         //GUI_DrawCircle(100,100,50);//��Բ

		Draw8Point(100,100,10,10);
		OSTimeDlyHMSM(0,0,0,500);
	}	
}


