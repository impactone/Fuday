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
	  
	//CAN��Ԫ����
	CAN_InitStructure.CAN_TTCM        = DISABLE;			//��ʱ�䴥��ͨ��ģʽ  
	CAN_InitStructure.CAN_ABOM        = DISABLE;			//����Զ����߹���	 
	CAN_InitStructure.CAN_AWUM        = DISABLE;			//˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)
	CAN_InitStructure.CAN_NART        = ENABLE;			  //��ֹ�����Զ����� 
	CAN_InitStructure.CAN_RFLM        = DISABLE;		 	//���Ĳ�����,�µĸ��Ǿɵ�  
	CAN_InitStructure.CAN_TXFP        = DISABLE;			//���ȼ��ɱ��ı�ʶ������ 
	CAN_InitStructure.CAN_Mode        = 0;	          //ģʽ���ã� mode:0,��ͨģʽ;1,�ػ�ģʽ; 
	//���ò�����
	CAN_InitStructure.CAN_SJW         = CAN_SJW_1tq;				  //����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ  CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
	CAN_InitStructure.CAN_BS1         = CAN_BS1_9tq; 			  //Tbs1=tbs1+1��ʱ�䵥λCAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructure.CAN_BS2         = CAN_BS2_8tq;			  	//Tbs2=tbs2+1��ʱ�䵥λCAN_BS2_1tq ~	CAN_BS2_8tq
	CAN_InitStructure.CAN_Prescaler   = 2;          //��Ƶϵ��(Fdiv)Ϊbrp+1	
	CAN_Init(CAN1, &CAN_InitStructure);             	//��ʼ��CAN1 

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
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);				//��������ж� 
	CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE);         //��������ж�
	
	//CAN�����ж�
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



