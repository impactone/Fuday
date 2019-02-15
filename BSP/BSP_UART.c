#include "BSP_UART.h"


/**
  * @brief  UART初始化
  * @param  void
  * @retval void
  */
void BSP_UART_InitConfig(void)
{
    USART_InitTypeDef   USART_InitStructure;
    GPIO_InitTypeDef	  GPIO_InitStructure;
    NVIC_InitTypeDef    NVIC_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);    
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	  
	 //端口设置
	  //Tx U1_A9 U2_A2 U3_B10 U4_C10
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		GPIO_Init(GPIOA,&GPIO_InitStructure);	 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	  GPIO_Init(GPIOB,&GPIO_InitStructure);	
		GPIO_Init(GPIOC,&GPIO_InitStructure);	
	
	  //Rx U1_A10 U2_A3 U3_B11 U4_C11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	  GPIO_Init(GPIOB,&GPIO_InitStructure);	
		GPIO_Init(GPIOC,&GPIO_InitStructure);			
	
    //USART1
    USART_InitStructure.USART_BaudRate              =   115200;
    USART_InitStructure.USART_HardwareFlowControl   =   USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                  =   USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity                =   USART_Parity_No;
    USART_InitStructure.USART_StopBits              =   USART_StopBits_1;
    USART_InitStructure.USART_WordLength            =   USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);
    
    //USART2
    USART_InitStructure.USART_BaudRate              =   115200;
    USART_InitStructure.USART_HardwareFlowControl   =   USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                  =   USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity                =   USART_Parity_No;
    USART_InitStructure.USART_StopBits              =   USART_StopBits_1;
    USART_InitStructure.USART_WordLength            =   USART_WordLength_8b;
    USART_Init(USART2, &USART_InitStructure);

    //USART3
    USART_InitStructure.USART_BaudRate              =   115200;
    USART_InitStructure.USART_HardwareFlowControl   =   USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                  =   USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity                =   USART_Parity_No;
    USART_InitStructure.USART_StopBits              =   USART_StopBits_1;
    USART_InitStructure.USART_WordLength            =   USART_WordLength_8b;
    USART_Init(USART3, &USART_InitStructure);
		
    //UART4
    USART_InitStructure.USART_BaudRate              =   115200;
    USART_InitStructure.USART_HardwareFlowControl   =   USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                  =   USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity                =   USART_Parity_No;
    USART_InitStructure.USART_StopBits              =   USART_StopBits_1;
    USART_InitStructure.USART_WordLength            =   USART_WordLength_8b;
    USART_Init(UART4, &USART_InitStructure);
		
		//使能串口
    USART_Cmd(USART1, ENABLE);	
		USART_Cmd(USART2, ENABLE);
		USART_Cmd(USART3, ENABLE);
		USART_Cmd(UART4,  ENABLE);
		
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启接收中断
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启接收中断
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启接收中断
		USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启接收中断
		
		NVIC_InitStructure.NVIC_IRQChannel                      = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 0;		
		NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;			
		NVIC_Init(&NVIC_InitStructure);
		NVIC_InitStructure.NVIC_IRQChannel                      = USART2_IRQn;
		NVIC_Init(&NVIC_InitStructure);
		NVIC_InitStructure.NVIC_IRQChannel                      = USART3_IRQn;
		NVIC_Init(&NVIC_InitStructure);
		NVIC_InitStructure.NVIC_IRQChannel                      = UART4_IRQn;
		NVIC_Init(&NVIC_InitStructure);
}



