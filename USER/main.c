#include "main.h"
  
 int main()
{   	
	 BSP_ALL_Init();	
   //while(1);
	 while(1) 
	 {   
//	// CAN_Send(Base_Motor_Out); 
	     TIM2_Process();		  
//		 if(Tow)
//		 {
//			 Road_Tow();
//		 }
//		 else
//		 {
//	 	   Road();
//		 }
		 
		 //printf("%d\r\n",StatusMode);
 		 //ANO_DT_Send _Senser(PID_Rotation.Measured,PID_Base_Motor2.Measured,PID_Base_Motor3.Measured,PID_Base_Motor4.Measured,PID_Base_Motor1.SumErr,PID_Base_Motor1.OutPut,R_MPU_XOut,0,0,0);		
		 //printf("%f %f %d\r\n",Distance.Back[1],Add,Mistake);
	   //printf("%f %f %f %d %d\r\n",Distance.Left[1],Distance.Right[1],Distance.Back[1],F1,F2); 				
		 
	 }
			 
}