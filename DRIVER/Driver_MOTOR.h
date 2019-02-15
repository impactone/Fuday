#ifndef __DRIVER_MOTOR_H
#define __DRIVER_MOTOR_H

#include "stm32f10x.h"

void WindMotor_Init(void);
void SetWindMotor(int16_t pwm);

#endif
