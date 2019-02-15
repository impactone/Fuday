#ifndef __DRIVER_CAN_H
#define __DRIVER_CAN_H

#include "BSP_CAN.h"


void CAN1_Process(void);
void ZGYRO_Reset(void);
void CAN_Send(s16 buf[4]);
#endif
