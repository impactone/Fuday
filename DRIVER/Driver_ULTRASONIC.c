#include "Driver_ULTRASONIC.h"
#include "stdlib.h"
DisType  Distance  = {{0},{0},{0}};
BuffType LeftBuff  = {0,{0}};
BuffType RightBuff = {0,{0}};
BuffType BackBuff  = {0,{0}};
extern s16 Motor1_Sp;
extern s16 Motor2_Sp;
u8 Left_Mistake_Check=0;
uint8_t index = 0;
/*左超声*/
void UART4_Process(uint8_t res)
{
//	static float Add=0;
//	static u8 Mistake=0;
	LeftBuff.data[LeftBuff.index++] = res;
	if (LeftBuff.index >= 2)
	{
//		if(Left_Mistake_Check)
//	  {
//			if(Distance.Left [0]-Distance.Left [1]>100) //突然有车挡住
//			{
//				 Mistake=1;
//				 Add+=(Distance.Left [0]-Distance.Left [1]);       
//			}							
//			if(Distance.Left [1]-Distance.Left [0]>100) //挡住又立即闪开
//			{
//				 Mistake=0;
//			}
//	  }					
//		else
//		{
//			 Mistake=0;
//		}
//		Distance.Left[0]=Distance.Left[1];						
  	Distance.Left[1] = LeftBuff.data[0]<<8|LeftBuff.data[1];
//		if(Mistake)
//		{
//			Distance.Left[1]+=Add;
//		}
    LeftBuff.index = 0;	
		return;
	}
}
u8 Right_Mistake_Check=0;
/*右超声*/
void USART2_Process(uint8_t res)
{
//	static float Add=0;
//	static u8 Mistake=0;
	RightBuff.data[RightBuff.index++] = res;
	if (RightBuff.index >= 2)
	{
//	  if(Right_Mistake_Check)
//	  {
//			if(Distance.Right [0]-Distance.Right[1]>100) //突然有车挡住
//			{
//				 Mistake=1;
//				 Add+=(Distance.Right[0]-Distance.Right[1]);       
//			}							
//			if(Distance.Right [1]-Distance.Right [0]>100) //挡住又立即闪开
//			{
//				 Mistake=0;
//			}
//	  }					
//		else
//		{
//			 Mistake=0;
//		}
//		Distance.Right[0]=Distance.Right[1];						
		Distance.Right[1] = RightBuff.data[0]<<8|RightBuff.data[1];
//		if(Mistake)
//		{
//			Distance.Right[1]+=Add;
//		}
		RightBuff.index = 0;
		return;
	}
}
//u8 Back_Mistake_Check=0;
//float Add=0;
//u8 Mistake=0;
/*后超声*/
void USART3_Process(uint8_t res)
{
	
	
	BackBuff.data[BackBuff.index++] = res;
	if (BackBuff.index >= 2)
	{
//		if(Back_Mistake_Check)
//	  {
//			if(Distance.Back [0]-Distance.Back [1]>100) //突然有车挡住
//			{
//				 Mistake=1;
//				 Add=Distance.Back [0]-Distance.Back [1];       
//			}							
//			if(Distance.Back [1]-Distance.Back [0]>100) //挡住又立即闪开
//			{
//				 Mistake=0;
//			}
//	  }
//		else
//		{
//		  Mistake=0;
//		}
		//Distance.Back [0]=Distance.Back [1];	
		Distance.Back[1] = BackBuff.data[0]<<8|BackBuff.data[1];
//		if(Mistake)
//		{
//			Distance.Back[1]+=Add;	
//		}
		BackBuff.index = 0;
		return;
 }
}

void UltraSonic_Trigger(void)
{
	
	switch (index)
	{
		case 0:
			USART_SendData(USART2,0X55);
			break;
		case 1:
			USART_SendData(USART3,0X55);
			break;
		case 2:
			USART_SendData(UART4,0X55);
			break;
		default:
			break;
	}
//	LeftBuff.index  = 0;
//	RightBuff.index = 0;
//	BackBuff.index  = 0;
	
	index = (index + 1) % 3; //3 means Numbers Of UltraSonic 
}



