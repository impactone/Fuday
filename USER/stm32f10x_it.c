/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "Driver_CAN.h"
#include "Driver_CONTROL.h"
 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
void SVC_Handler(void)
{
}
 
void DebugMon_Handler(void)
{
}
 
void PendSV_Handler(void)
{
}
 
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
uint32_t __cnt=0;
uint16_t __10ms_cnt = 0;
uint16_t __20ms_cnt = 0;
uint16_t __2s_cnt=0;
uint16_t __1s_cnt=0;
u8 start=0;
u8 open=0;
void TIM2_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 	
	__10ms_cnt++;
	__20ms_cnt++;
	if(open)
	{
		__1s_cnt++;	
	}
	else
	{
		__1s_cnt=0;
	}
	if(start)
  {
		__2s_cnt++;
	}
	else
	{
		__2s_cnt=0;
	}
	__cnt++;	
}
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	CAN_ClearITPendingBit(CAN1,CAN_IT_FMP0);
	CAN1_Process();
}
extern u8 State;
void USB_HP_CAN1_TX_IRQHandler(void)                             //发送完成 进入中断
{		 
    if (CAN_GetITStatus(CAN1,CAN_IT_TME) != RESET) 
	  {
       
	     CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
       State = 0;
    }
}
void USART2_IRQHandler(void)                	
{
	uint8_t Res;
	(void)USART2->SR;
	(void)USART2->DR;
	Res = USART_ReceiveData(USART2);	//读取接收到的数据
	USART2_Process(Res);
} 

void USART3_IRQHandler(void)                	
{
	uint8_t Res;
	(void)USART3->SR;
	(void)USART3->DR;
	Res = USART_ReceiveData(USART3);	//读取接收到的数据
	USART3_Process(Res);
} 

void UART4_IRQHandler(void)                	
{
	uint8_t Res;
	(void)UART4->SR;
	(void)UART4->DR;
	Res = USART_ReceiveData(UART4);	//读取接收到的数据
	UART4_Process(Res);
} 
