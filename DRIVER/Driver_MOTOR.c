#include "Driver_MOTOR.h"
#include "delay.h"
void WindMotor_Init()
{
	TIM8->CCR3 = 10;	
	delay_ms(1000);		
}
void SetWindMotor(int16_t pwm)
{
	TIM8->CCR3 = pwm;
}

