#include "BSP_CAN.h"
#include "Driver_CAN.h"
void BSP_CAN_InitConfig(void)
{
	GPIO_InitTypeDef 		    GPIO_InitStructure; 
	CAN_InitTypeDef        	CAN_InitStructure;
	CAN_FilterInitTypeDef  	CAN_FilterInitStructure;
	NVIC_InitTypeDef        NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);		

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);			
	  
	//CAN单元设置
	CAN_InitStructure.CAN_TTCM        = DISABLE;			//非时间触发通信模式  
	CAN_InitStructure.CAN_ABOM        = DISABLE;			//软件自动离线管理	 
	CAN_InitStructure.CAN_AWUM        = DISABLE;			//睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位)
	CAN_InitStructure.CAN_NART        = ENABLE;			  //禁止报文自动传送 
	CAN_InitStructure.CAN_RFLM        = DISABLE;		 	//报文不锁定,新的覆盖旧的  
	CAN_InitStructure.CAN_TXFP        = DISABLE;			//优先级由报文标识符决定 
	CAN_InitStructure.CAN_Mode        = 0;	          //模式设置： mode:0,普通模式;1,回环模式; 
	//设置波特率
	CAN_InitStructure.CAN_SJW         = CAN_SJW_1tq;				  //重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位  CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
	CAN_InitStructure.CAN_BS1         = CAN_BS1_9tq; 			  //Tbs1=tbs1+1个时间单位CAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructure.CAN_BS2         = CAN_BS2_8tq;			  	//Tbs2=tbs2+1个时间单位CAN_BS2_1tq ~	CAN_BS2_8tq
	CAN_InitStructure.CAN_Prescaler   = 2;          //分频系数(Fdiv)为brp+1	
	CAN_Init(CAN1, &CAN_InitStructure);             	//初始化CAN1 

	CAN_FilterInitStructure.CAN_FilterNumber          = 0;	
	CAN_FilterInitStructure.CAN_FilterMode            = CAN_FilterMode_IdMask; 	
	CAN_FilterInitStructure.CAN_FilterScale           = CAN_FilterScale_32bit; 	
	CAN_FilterInitStructure.CAN_FilterIdHigh          = 0x0000;	
	CAN_FilterInitStructure.CAN_FilterIdLow           = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh      = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow       = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment  = CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation      = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);			
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);				//接收完成中断 
	CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);         //发送完成中断
	
	//CAN接收中断
	NVIC_InitStructure.NVIC_IRQChannel                    = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 1;    
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 1;        
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel                    = USB_HP_CAN1_TX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;    
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;        
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
  ZGYRO_Reset();
}



