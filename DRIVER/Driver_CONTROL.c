#include "Driver_CONTROL.h"
#include "stdlib.h"
extern uint16_t __10ms_cnt ;
extern uint16_t __20ms_cnt ;

s16 Motor1_Sp=0;
s16 Motor2_Sp=0;
s16 Motor3_Sp=0;
s16 Motor4_Sp=0;

u8 F1_press=0;
u8 F2_press=0;

s16 Base_Motor_Out[4];

s16 R_MPU_XOut=0;
s16 R_MPU_YOut=0;
u8 X_Angle_Loop=0;
u8 Y_Angle_Loop=0;

u8 Hit=0;
u8 Hit_Check_EN=0;
float Dif=0;
extern u8 Tow;
extern	uint8_t index;
u8  Decline=0;
void TIM2_Process(void)
{
	

	//10ms 电机闭环
//	  if(__10ms_cnt>=10)
//	{			
//    PID_Calc(&PID_Rotation);	
//    if(X_Angle_Loop)
//		{
//      R_MPU_XOut=PID_Rotation.OutPut;
//		}		
//		else
//		{
//			R_MPU_XOut=0;  
//		}
//		if(Y_Angle_Loop)
//		{
//			R_MPU_YOut=PID_Rotation.OutPut;
//		}
//		else
//		{
//      R_MPU_YOut=0;
//		}		
//		
//		if(Decline)
//		{
//		   PID_X.Measured=Distance.Back[1];
////			if(Tow)
////			{
////				PID_Y.Measured=Distance.Right[1];
////			}
////			else
////		  {
//				PID_Y.Measured=Distance.Left[1];
////			}
////			if(Tow)
////			{
////			  Motor1_Sp=-PID_Calc(&PID_Y);
////			  Motor3_Sp=PID_Calc(&PID_Y);
////			}
////			else
////			{
//			  Motor1_Sp=PID_Calc(&PID_Y);
//			  Motor3_Sp=-PID_Calc(&PID_Y);
////			}
//		  
//			Motor2_Sp=-PID_Calc(&PID_X);			
//			Motor4_Sp=PID_Calc(&PID_X);
//		}
//		//横向与纵向角度闭环
//		PID_Base_Motor1.Expect=Motor1_Sp+R_MPU_YOut;
//		PID_Base_Motor2.Expect=Motor2_Sp+R_MPU_XOut;
//		PID_Base_Motor3.Expect=Motor3_Sp+R_MPU_YOut;
//		PID_Base_Motor4.Expect=Motor4_Sp+R_MPU_XOut;		
//		
//		Base_Motor_Out[0]=PID_Calc(&PID_Base_Motor1);
//	  Base_Motor_Out[1]=PID_Calc(&PID_Base_Motor2);
//		Base_Motor_Out[2]=PID_Calc(&PID_Base_Motor3);
//		Base_Motor_Out[3]=PID_Calc(&PID_Base_Motor4);
//		CAN_Send(Base_Motor_Out); 
//		//5*10ms 扫描开关是否按下(至少大于50ms)		
//		Switch_Scan();
//		//每10ms检测一次碰撞
//		if(Hit_Check_EN)
//		{
//			if(Motor1_Sp!=0)  //横向检测
//			{
//				Hit_Check(0);				
//			}
//			else  //纵向检测
//			{
//				Hit_Check(1);				
//			}				
//		  __10ms_cnt=0;			
//		}
//	}	
	// 20ms 读一个方向的超声波数据,80ms全部读完
	if(__20ms_cnt>=20)
	{     
		UltraSonic_Trigger();
		__20ms_cnt=0;
	}
	
	
	if(index==4)
	{
		printf("%d\r\n",Distance.Back[1]);
		index = 0;
	}
}
/* 开关扫描*/
void Switch_Scan(void)
{
	 static u8 cnt1=0;	
   static u8 cnt2=0;		
	 static u8 time1=0;	
   static u8 time2=0;	
	 if(F1==0)
	 {		
	   cnt1++;		
     if(cnt1==5)
		 {			 			 
			 cnt1=0;
			 F1_press=1;
			 time1=0;
		 }		 		 		 
	 }	
	 else
	 {
		cnt1=0;
    if(F1_press)		 
		{
			time1++;
		 if(time1==5)
		 {		  	 
		  F1_press=0;
			time1=0;
		 }
		}
		else
		{		
		 F1_press=0;		
		}
	 }
	 	 if(F2==0)
	 {		
	   cnt2++;		
     if(cnt2==5)
		 {			 			
			 cnt2=0;
			 time2=0;
			 F2_press=1;
		 }		 		 		 
	 }	
	 else
	 {
		 cnt2=0;
		 if(F2_press)
		 {
			 time2++;
			 if(time2==5)
			 {				 
			   F2_press=0;
				 time2=0;
			 }
		 }
		 else
		 {			 			 	
			 F2_press=0;			 
		 }
	 }
}
//横向距离
void X_Move(s16 speed)
{	  
		X_Angle_Loop=1;
	  Motor1_Sp=0;
	  Motor2_Sp=speed;
	  Motor3_Sp=0;
	  Motor4_Sp=-speed;	  
	 if(speed==0)
	  X_Angle_Loop=0;
}
//纵向距离
void Y_Move(s16 speed)	
{
		Y_Angle_Loop=1;
	  X_Angle_Loop=1;
	  Motor1_Sp=speed;
	  Motor2_Sp=0;
	  Motor3_Sp=-speed;
	  Motor4_Sp=0;			  
	  if(speed==0)
		{
			X_Angle_Loop=0;
	    Y_Angle_Loop=0;
		}
}
//碰撞检测

void Hit_Check(u8 mode)
{
	static u16 time=0;
	if(mode)
	{
		Dif=abs(Distance.Back[1]-Distance.Back[0]);
	}
	else
	{
		Dif=abs(Distance.Left[1]-Distance.Left[0]);
	}	
	if(abs(PID_Rotation.Measured- PID_Rotation.Expect)>10||Dif<20)
	{ 
		time++;
		if(time>300) 
		{							
			Hit=1;							
		}
	}
	else
	{	
		 time=0;		
	} 
}	
#define Self_Long 280
#define Enter_Width 200
extern u8 Back_Mistake_Check;
extern u8 Left_Mistake_Check;
extern u8 Right_Mistake_Check;
u8 number=0;
u8 Flag=0;
void Esc(u16 back,s16 sp)
{
	static u8 Step=0;
	static u8 Right_Avoid=1;
	static u8 Left_Avoid=0;
  static u32 Enter=0;
	u16 Already=0;
  u8  L_number=0;	
  if(Hit)
	{			
		switch(Step)
		{
			case 0:			
			X_Move(-sp);
			delay_ms(500);
			Step++;
			break;
			case 1:
			Enter++;
			X_Move(0);
			if(Enter%2)
			{
				Y_Move(2500);
			}
			else
			{
				Y_Move(-2500);
			}
			delay_ms(500);
			Step++;
			break;
			case 2:
			Y_Move(0);
			X_Move(sp);			
			delay_ms(500);
			Step=0;
			Hit=0;
			break;
		}
	}
}
//		switch(Step)
//		{
//			case 0:
//			Already=Distance.Back[1];
//			X_Move(-sp);	
//			Step++;
//			break;
//		  case 1:		  	
//		  if(Already-Distance.Back[1]>back)
//		  { 
//  	 	  X_Move(0);					
//		    Already=Distance.Left[1];
//				  //向右闪避的次数
//				if(number==2)
//				{
//					Right_Avoid=0;
//					Left_Avoid=1;
//				}
//				if(number==0)
//				{
//					Right_Avoid=1;
//					Left_Avoid=0;
//				}
//				if(Right_Avoid)
//				{
//					number++;			
//					Y_Move(1500);
//				}
//				if(Left_Avoid)					
//				{            //大于2次之后向左移			  
//					number--;
//					Y_Move(-1500);
//				}					
//				Step++;									
//	    }			
//      break;	
//			case 2:
//			if(Already-Distance.Left[1]>Self_Long)		
//			{
//				Y_Move(0);							    			  
//				X_Move(sp);					
//				Step=0;
//				Hit=0;		
//				if(number-L_number!=0)				
//			   Flag=1;
//				L_number=number;				
//			}			
//			break;		  		             
//		}
//每次闪避后都提取前一次动作
void Last_Step_Action(u8 l_step)
{
	switch(l_step)
	{
	  case 4:
  		Y_Move(0); 					 					 					
   		X_Move(2500);
    break;			
	  case 6:
			Y_Move(0); 					 					 					
			X_Move(-2500);	
		break;
		case 9:
		  Y_Move(0); 					 					 					
			X_Move(-2500);	
		break;
	  case 11:			
		  Y_Move(0); 					 					 					
			X_Move(2500);
		break;
	}
}
u8 StatusMode=0;
extern uint16_t __2s_cnt;
extern uint16_t __1s_cnt;
extern u8 start;
extern u8 open;
//整车路线轮询
void Road(void)
{	
	  static u8 Time=1;
	  static u8 Enter=0;
		switch(StatusMode)
		{
			//找准基墙
			case 0:
				if(Distance.Back[1]<660&&Distance.Back[1]>650)
				{
					 Decline=0;	
					 Y_Move(0);             
					 X_Move(-1500);
					 StatusMode++;
				}
			case 1:				 				 	    				 			
				if(F1_press||F2_press)
				{
					 X_Move(0);			   				
					 Y_Move(2500);
					 StatusMode++;	
				}
			break;
				//进入场内
			case 2:			
         if(Distance.Back[1]<80)
				 {
					 delay_ms(500);
	  			 //Back_Mistake_Check=1;
					 //Left_Mistake_Check=1;
 			     Hit_Check_EN=1;
					 Y_Move(0);
					 X_Move(-2500);					 			   			   				 
			     StatusMode++;	
				 }
      break;					  				  		
			//开始霸场
			case 3:				   
			     if(Distance.Left[1]<400)
					 {
						 start=1;
						 Decline=1;						
						 PID_Y.Expect=100;
						 PID_X.Expect=600;
					 }    
					 open=1;					 
				 	 if(Distance.Back[1]<700&&Distance.Back[1]>500)
					 {
             PID_X.Expect=600;						 
						 PID_Y.Expect=500;						 												 						 
						 StatusMode++;
					 }
           if(__1s_cnt>2000&&(StatusMode==3)) 
					 {
						  __1s_cnt=0;
						  open=0;
						  StatusMode++;
					 } 						 
			break;	
			case 4:
				   open=1; 
			     if(Distance.Left[1]<600&&Distance.Left[1]>400)			     
					 {							 
						 PID_X.Expect=300;						 
						 PID_Y.Expect=500;						 												 						 
						 StatusMode++;					 						 						 						 
					 }
           if(__1s_cnt>2000&&(StatusMode==4)) 
					 {
						  __1s_cnt=0;
						  open=0;
						  StatusMode++;
					 } 							 
			break;	
			case 5:
				   open=1; 
			     if(Distance.Back[1]<350&&Distance.Back[1]>250)			     
					 {		
						 PID_X.Expect=300;						 
						 PID_Y.Expect=100;	
					   StatusMode++;
					 }	
           if(__1s_cnt>2000&&(StatusMode==5)) 
					 {
						  __1s_cnt=0;
						  open=0;
						  StatusMode++;
					 } 							 
			break;		
      case 6:	
           open=1;						
           if(Distance.Left[1]<150&&Distance.Left[1]>50)			     
					 {											
						  StatusMode-=3;				
	
					 }
					 if(__2s_cnt>40000)
					 {						 
							 start=0;
							 Decline=0;	
							 StatusMode=7;	
					 }
					 if(__1s_cnt>2000&&(StatusMode==6)) 
					 {
						  __1s_cnt=0;
						  open=0;
						  StatusMode-=3;
					 } 		
			break;
			case 7:				    		    					 						 
					 X_Move(1000);
			     StatusMode++;
			break;
			case 8:
				  open=1;			   
				  if(__1s_cnt>2000)
					{                 					
						X_Move(0);
						Y_Move(-3000);						
						StatusMode++;
						__1s_cnt=0;
						open=0;
					}
			break;
			case 9:
          open=1;				
				  if(Distance.Left[1]<100&&__1s_cnt>2000)
					{            											
						Y_Move(0);
						X_Move(3000);
						open=0;
						__1s_cnt=0;
						Enter++;
            if(Enter>5)						
						{
							StatusMode++;
						}
						else
						{
							StatusMode--;
						}
					}
					
			break;
			case 10:		
			     X_Move(0);
					 Y_Move(0);
			break;
//			case 3:

//				 Esc(100,-2500);
//			   if(Flag)
//				 {
//					 Last_Step_Action(number*2+3-1);		  //提取即将进行的一步其上一步的动作
//           StatusMode=number*2+3;		
//           Flag=0;					 
//				 }
//				 
//         if(Distance.Back[1]>600)
//				 {
//					   X_Move(0); 
//  					 Y_Move(2500); 
//						 StatusMode++;					 					 					 				
//				 }	                  				
//			break;							
//      case 4:
//				 Esc(100,2500);
//				 if(Distance.Left[1]>Self_Long)				 
//	 			 { 			
// 					   Y_Move(0); 					 					 					
//						 X_Move(2500);												 
//   					 StatusMode++;	
//				 }
//			break;
//		  case 5:				
//         Esc(100,2500);				
//				 if(Flag)
//				 {
//					 Last_Step_Action(number*2+5-1);		  //提取即将进行的一步其上一步的动作
//           StatusMode=number*2+5;		
//           Flag=0;					 
//				 }
//				 if(Distance.Back[1]<200)
//				 {						            					 					
//				    X_Move(0); 					 					 					
//					  Y_Move(2500); 					 					 				
//					  StatusMode++;	
//				 }
//      break; 		
//      case 6:
//				 Esc(200,2500);
//				 if(Distance.Left[1]>2*Self_Long)				 
//	 			 { 			
// 					   Y_Move(0); 					 					 					
//						 X_Move(-2500);												 
//					   StatusMode++;	
//				 }
//			break;
//			case 7:
//				 Esc(200,-2500);
//				 if(Flag)
//				 {
//					 Last_Step_Action(number*2+7-1);		  //提取即将进行的一步其上一步的动作
//           StatusMode=number*2+7;		
//           Flag=0;					 
//				 }
//         if(Distance.Back[1]>600)
//				 {
//					   X_Move(2500); 
//  					 Y_Move(0); 
//						 StatusMode++;					 					 					 				
//				 }
//	    break;				 
//      case 8:
//				 Esc(200,2500);
//				 if(Flag)
//				 {
//					 Last_Step_Action(number*2+8-1);		  //提取即将进行的一步其上一步的动作
//           StatusMode=number*2+8;		
//           Flag=0;					 
//				 }
//				 if(Distance.Back[1]<200)
//				 {						            					 					
//				    X_Move(0); 					 					 					
//					  Y_Move(-2500); 					 					 				
//					  StatusMode++;	
//				 }
//			break;
//			
//			case 9:
//				 Esc(200,-2500);
//			   if(Distance.Left[1]>Self_Long)				 
//	 			 { 			
// 					   Y_Move(0); 					 					 					
//						 X_Move(-2500);												 
//					   StatusMode++;	
//				 }
//			break;
//			case 10:
//				 Esc(200,-2500);
//				 if(Flag)
//				 {
//					 Last_Step_Action(number*2+10-1);		  //提取即将进行的一步其上一步的动作
//           StatusMode=number*2+10;		
//           Flag=0;					 
//				 }
//				 if(Distance.Back[1]>600)
//				 {
//					   X_Move(0); 
//  					 Y_Move(-2500); 
//						 StatusMode++;					 					 					 				
//				 }
//      break;
//			case 11:
//				 Esc(200,-2500);
//				 if(Distance.Left[1]>Enter_Width)				 
//	 			 { 			
// 					   Y_Move(0); 					 					 					
//						 X_Move(2500);												 
//					   StatusMode++;	
//				 }						 
//			break;
//			case 12:
//				 Esc(200,2500);
//				 if(Flag)
//				 {
//					 Last_Step_Action(number*2+12-10);		  //提取即将进行的一步其上一步的动作
//           StatusMode=number*2+12-9;		
//           Flag=0;					 
//				 }
//				 if(Distance.Back[1]<200)
//				 {	
//					   Y_Move(0);					            					 					
//				     X_Move(-2500); 					 					 										   					 					 			
//					   StatusMode-=9;	
//				 }
//			break;
//				
	  }
}
void Road_Tow(void)
{	  
	  static u8 Time=1;
	  static u8 Enter=0;
		switch(StatusMode)
		{
			//找准基墙
			case 0:
				if(Distance.Back[1]<660&&Distance.Back[1]>650)
				{
					 Decline=0;	
					 Y_Move(0);             
					 X_Move(-1500);
					 StatusMode++;
				}
			case 1:				 				 	    				 			
				if(F1_press||F2_press)
				{
					 X_Move(0);			   				
					 Y_Move(-2500);
					 StatusMode++;	
				}
			break;
				//进入场内
			case 2:			
         if(Distance.Back[1]<80)
				 {
					 open=1; 
					 if(__1s_cnt>1000) 
					 {
						 __1s_cnt=0;
						 open=0;
						 Hit_Check_EN=1;
					   Y_Move(0);
					   X_Move(-2500);					 			   			   				 
			       StatusMode++;
					 }
	  			 //Back_Mistake_Check=1;
					 //Left_Mistake_Check=1;
 			    	
				 }
      break;					  				  		
			//开始霸场
			case 3:				   
			     if(Distance.Right[1]<400)
					 {
						 start=1;
						 Decline=1;						
						 PID_Y.Expect=100;
						 PID_X.Expect=600;
					 }    
					 open=1;					 
				 	 if(Distance.Back[1]<700&&Distance.Back[1]>500)
					 {
             PID_X.Expect=600;						 
						 PID_Y.Expect=500;						 												 						 
						 StatusMode++;
					 }
           if(__1s_cnt>2000&&(StatusMode==3)) 
					 {
						  __1s_cnt=0;
						  open=0;
						  StatusMode++;
					 } 						 
			break;	
			case 4:
				   open=1; 
			     if(Distance.Right[1]<600&&Distance.Right[1]>400)			     
					 {							 
						 PID_X.Expect=300;						 
						 PID_Y.Expect=500;						 												 						 
						 StatusMode++;					 						 						 						 
					 }
           if(__1s_cnt>2000&&(StatusMode==4)) 
					 {
						  __1s_cnt=0;
						  open=0;
						  StatusMode++;
					 } 							 
			break;	
			case 5:
				   open=1; 
			     if(Distance.Back[1]<350&&Distance.Back[1]>250)			     
					 {		
						 PID_X.Expect=300;						 
						 PID_Y.Expect=100;	
					   StatusMode++;
					 }	
           if(__1s_cnt>2000&&(StatusMode==5)) 
					 {
						  __1s_cnt=0;
						  open=0;
						  StatusMode++;
					 } 							 
			break;		
      case 6:	
           open=1;						
           if(Distance.Right[1]<150&&Distance.Right[1]>50)			     
					 {											
						  StatusMode-=3;				
	
					 }
					 if(__2s_cnt>40000)
					 {						 
							 start=0;
							 Decline=0;	
							 StatusMode=7;	
					 }
					 if(__1s_cnt>2000&&(StatusMode==6)) 
					 {
						  __1s_cnt=0;
						  open=0;
						  StatusMode-=3;
					 } 		
			break;
			case 7:				    		    					 						 
					 X_Move(1000);
			     StatusMode++;
			break;
			case 8:
				  open=1;			   
				  if(Distance.Back[1]<100&&__1s_cnt>2000)
					{            					
						X_Move(0);
						Y_Move(3000);						
						StatusMode++;
						__1s_cnt=0;
						open=0;
					}
			break;
			case 9:
          open=1;				
				  if(Distance.Right[1]<100&&__1s_cnt>2000)
					{            											
						Y_Move(0);
						X_Move(3000);
						open=0;
						__1s_cnt=0;
						Enter++;
            if(Enter>5)						
						{
							StatusMode++;
						}
						else
						{
							StatusMode--;
						}
					}
					
			break;
			case 10:		
			     X_Move(0);
					 Y_Move(0);
			break;
}
		}