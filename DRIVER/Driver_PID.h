#ifndef __DRIVER_PID_H
#define __DRIVER_PID_H

#include "BSP_TIM.h"

typedef struct
{
	float P;
	float I;
	float D;
	float Imax;
	
  float NowErr;
  float LstErr;
	float SumErr;
	
  float Expect;
  float Measured;
	
	float OutPut;
	float MaxOutput;
}POS_PID_Struct;


extern POS_PID_Struct PID_Rotation;
extern POS_PID_Struct PID_X;
extern POS_PID_Struct PID_Y;
extern POS_PID_Struct PID_Base_Motor1;
extern POS_PID_Struct PID_Base_Motor2;
extern POS_PID_Struct PID_Base_Motor3;
extern POS_PID_Struct PID_Base_Motor4;
void PID_Init(void);
float PID_Calc(POS_PID_Struct *pid);
void PID_Param_Init(POS_PID_Struct *pid,\
	                  float p,float i,float d,\
										float im,float output);
void PID_Reset_SumErr(POS_PID_Struct *pid);

#endif
