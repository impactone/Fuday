#include "BSP_TIM.h"

void BSP_TIM_InitConfig(void)
{
	GPIO_InitTypeDef         GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;
	NVIC_InitTypeDef         NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	//TIM2 1ms定时中断
	TIM_TimeBaseStructure.TIM_Period = 99; 
	TIM_TimeBaseStructure.TIM_Prescaler = 719;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_TimeBaseStructure.TIM_Period = 199; 
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;	
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0xff;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
  // CH3 风机
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);	
	
	TIM_CtrlPWMOutputs(TIM8,ENABLE);	//MOE 主输出使能		
	
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  
	
	TIM_ARRPreloadConfig(TIM8, ENABLE);
	
	TIM_Cmd(TIM8, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	
}

void TIM2_IT_ENABLE(void)
{
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);		
	TIM_Cmd(TIM2, ENABLE);
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	
}

