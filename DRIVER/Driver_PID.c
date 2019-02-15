#include "Driver_PID.h"

POS_PID_Struct PID_Rotation;
POS_PID_Struct PID_X;
POS_PID_Struct PID_Y;
POS_PID_Struct PID_Base_Motor1;
POS_PID_Struct PID_Base_Motor2;
POS_PID_Struct PID_Base_Motor3;
POS_PID_Struct PID_Base_Motor4;

/*PID结构体初始化*/
void PIDStruct_Init(POS_PID_Struct *pid)
{
	pid->P          = 0;
	pid->I          = 0;
	pid->D          = 0;
	pid->Imax       = 0;
	pid->NowErr     = 0;
	pid->LstErr     = 0;
	pid->SumErr     = 0;
	pid->Expect     = 0;
	pid->Measured   = 0;
	pid->OutPut     = 0;
	pid->MaxOutput  = 0;
}

/*PID参数初始化*/
void PID_Param_Init(POS_PID_Struct *pid,\
	                  float p,float i,float d,\
										float im,float output)
{
	pid->P          = p;
	pid->I          = i;
	pid->D          = d;
	pid->Imax       = im;
	pid->MaxOutput  = output;
}

/*清空积分项*/
void PID_Reset_SumErr(POS_PID_Struct *pid)
{
	pid->SumErr = 0;
}

/*PID初始化*/
void PID_Init(void)
{
	PIDStruct_Init(&PID_Rotation);
	PIDStruct_Init(&PID_X);
	PIDStruct_Init(&PID_Y);
	PIDStruct_Init(&PID_Base_Motor1);
	PIDStruct_Init(&PID_Base_Motor2);
	PIDStruct_Init(&PID_Base_Motor3);
	PIDStruct_Init(&PID_Base_Motor4);
//
	PID_Param_Init(&PID_X,8,0,4,0,5000);	
	PID_Param_Init(&PID_Y,8,0,4,0,5000);	
 	PID_Param_Init(&PID_Base_Motor1,0.4,0.1,0,10000,5000);	
	PID_Param_Init(&PID_Base_Motor2,0.4,0.1,0,10000,5000);	
	PID_Param_Init(&PID_Base_Motor3,0.5,0.1,0,10000,5000);	
	PID_Param_Init(&PID_Base_Motor4,0.3,0.1,0,10000,5000);	
  PID_Param_Init(&PID_Rotation,50,0,10,0,5000);
   
	//	PID_Param_Init(&PID_Rotation,0,0,0,500,MAX_MOTOR_PWM_OUTPUT);
//	PID_Param_Init(&PID_X,0,0,0,500,MAX_MOTOR_PWM_OUTPUT);
//	PID_Param_Init(&PID_Y,0,0,0,500,MAX_MOTOR_PWM_OUTPUT);
//	PID_Param_Init(&PID_Rotation,0,0,0,500,MAX_MOTOR_PWM_OUTPUT);
//	PID_Param_Init(&PID_X,0,0,0,500,MAX_MOTOR_PWM_OUTPUT);
//	PID_Param_Init(&PID_Y,0,0,0,500,MAX_MOTOR_PWM_OUTPUT);
}

/*PID计算函数*/
float PID_Calc(POS_PID_Struct *pid)
{
	volatile float Pout = 0,Iout = 0,Dout = 0;
	/*误差计算*/
	pid->NowErr  =  pid->Expect-pid->Measured ;
	pid->SumErr += (pid->I == 0) ? 0 : pid->NowErr;
	
	/*P-I-D*/
	Pout = pid->P * pid->NowErr;
	Iout = pid->I * pid->SumErr;
	Dout = pid->D * (pid->NowErr - pid->LstErr);
	
	/*积分限幅*/
	if (pid->SumErr >= pid->Imax)
	{
		pid->SumErr  = pid->Imax; 
	}
	else if (pid->SumErr <= -pid->Imax)
	{
		pid->SumErr  = -pid->Imax;
	}
	
	/*PID输出*/
	pid->OutPut = Pout + Iout + Dout;

	/*输出限幅*/
	if (pid->OutPut >= pid->MaxOutput) 
		pid->OutPut = pid->MaxOutput;
	else if (pid->OutPut <= -pid->MaxOutput)
	  pid->OutPut = -pid->MaxOutput;
	
	/*误差更新*/
	pid->LstErr = pid->NowErr;
		
	return pid->OutPut;
}

