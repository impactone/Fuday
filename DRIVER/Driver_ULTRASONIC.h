#ifndef __DRIVER_ULTRASONIC_H
#define __DRIVER_ULTRASONIC_H

#include "stm32f10x.h"

typedef struct
{
	float Left[2];
	float Right[2];
	float Back[2];
}DisType;

typedef struct
{
	uint8_t index;
	uint8_t data[4];
}BuffType;
 
extern DisType Distance;

void USART2_Process(uint8_t res);
void USART3_Process(uint8_t res);
void UART4_Process(uint8_t res);
void UltraSonic_Trigger(void);

#endif

