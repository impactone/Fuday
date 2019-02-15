#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#include "stm32f10x.h"

#define F1 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)
#define F2 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)

void BSP_EXTI_InitConfig(void);

#endif
