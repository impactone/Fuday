#include "Driver_CAN.h"
#include "Driver_PID.h"

void CAN1_Process(void)
{
	CanRxMsg RxMsg;
	
	CAN_Receive(CAN1,CAN_FIFO0,&RxMsg);	
	switch(RxMsg.StdId)
	{
		case 0x401:
		   PID_Rotation.Measured= -0.01f*((int32_t)(RxMsg.Data[0]<<24)|(int32_t)(RxMsg.Data[1]<<16) | (int32_t)(RxMsg.Data[2]<<8) | (int32_t)(RxMsg.Data[3])); 			
		break;
		case 0x201:
		   PID_Base_Motor1.Measured= (s16)((s16)RxMsg.Data[2]<<8)|RxMsg.Data[3];       
		break;
		case 0x202:
		   PID_Base_Motor2.Measured = (s16)((s16)RxMsg.Data[2]<<8)|RxMsg.Data[3];
		break;  
		case 0x203:
		   PID_Base_Motor3.Measured = (s16)((s16)RxMsg.Data[2]<<8)|RxMsg.Data[3];		   
		break;
		case 0x204:
			 PID_Base_Motor4.Measured = (s16)((s16)RxMsg.Data[2]<<8)|RxMsg.Data[3];
		break;
	}
}
u8 State;
void ZGYRO_Reset(void)
{
    CanTxMsg tx_message;
    
    tx_message.StdId = 0x404;
    tx_message.IDE = CAN_Id_Standard;
    tx_message.RTR = CAN_RTR_Data;
    tx_message.DLC = 0x08;
    
    tx_message.Data[0] = 0x00;
    tx_message.Data[1] = 0x01;
    tx_message.Data[2] = 0x02;
    tx_message.Data[3] = 0x03;
    tx_message.Data[4] = 0x04;
    tx_message.Data[5] = 0x05;
    tx_message.Data[6] = 0x06;
    tx_message.Data[7] = 0x07;
    State=1;
    CAN_Transmit(CAN1,&tx_message);		
	  while(State);
}

#define h8(x) (x>>8)
#define l8(x) ((x)&0xff)
void CAN_Send(s16 buf[4])
{
	CanTxMsg TxMsg;
	TxMsg.StdId=0x200;
	TxMsg.IDE=CAN_Id_Standard;
	TxMsg.RTR=CAN_RTR_Data;
	TxMsg.DLC=8;	
	TxMsg.Data[0] = h8(buf[0]);
	TxMsg.Data[1] = l8(buf[0]);
	TxMsg.Data[2] = h8(buf[1]);
	TxMsg.Data[3] = l8(buf[1]);
	TxMsg.Data[4] = h8(buf[2]);
	TxMsg.Data[5] = l8(buf[2]);
	TxMsg.Data[6] = h8(buf[3]);
	TxMsg.Data[7] = l8(buf[3]);
	State=1;
	CAN_Transmit(CAN1,&TxMsg);	
	while(State);
}	

