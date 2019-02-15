#include "BSP_ALL.h"
u16 Tow=0xff;
void BSP_ALL_Init(void)
{  	 
   BSP_NVIC_InitConfig();	 
	 delay_init();
	 BSP_TIM_InitConfig();
	 BSP_UART_InitConfig();	 
   //BSP_CAN_InitConfig();	
	 //BSP_EXTI_InitConfig();
   //PID_Init();	
	 //TIM2_IT_ENABLE(); 	 
//	 while(Tow>0)
//	 {
//		 Tow--;
//	 }
   //WindMotor_Init();      	  	
	// SetWindMotor(100);	

//	 X_Angle_Loop=1;
//	 Y_Angle_Loop=1; 
//	 PID_X.Expect=700;
//	 PID_Y.Expect=650;
//	 Decline=1;
}

