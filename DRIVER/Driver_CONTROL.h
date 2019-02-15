#ifndef __DRIVER_CONTROL_H
#define __DRIVER_CONTROL_H

#include "main.h"
#include "math.h"
#include "Driver_ULTRASONIC.h"
void TIM2_Process(void);
void X_Move(s16 speed);
void Y_Move(s16 speed);
void Switch_Scan(void);
void Hit_Check(u8 mode);
void Road(void);
void Road_Tow(void);
#endif
