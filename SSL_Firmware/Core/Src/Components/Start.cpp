/*
 * Start.cpp
 *
 *  Created on: 20 de mar de 2021
 *      Author: Moraes
 */

#include "Start.hpp"
#include "usbd_cdc_if.h"

#include "Encoder.hpp"
#include "Motor.hpp"
#include "CommunicationUSB.hpp"


extern TIM_HandleTypeDef htim6;
extern void (*usbRecvCallback)(uint8_t*, uint32_t*);


/*struct recvUSBStruct_t{
	uint32_t motorSpd_s;
	int32_t motorSpd[4] = {0, 0, 0, 0};
	int32_t dribbleSpd = 0;
	uint32_t led;
	uint32_t sevSeg;
	uint32_t kickPow_s;
	uint32_t kickPow[2];
}*recvUSBStruct;*/

/*struct sendUSBStruct_t{
	uint32_t motorEnc_s = 4;
	int32_t motorEnc[4] = {0, 0, 0, 0};
	uint32_t button;
}sendUSBStruct;*/

/*sendUSBStruct_t sendUSBStruct = {
	4,
	{0, 0, 0, 0},
	0
};*/

/*struct usbStruct_t{
	int32_t val1;
	int32_t val2;
}usbStruct;*/

Encoder encoder(0);
CommunicationUSB usb(&usbRecvCallback);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim6){
		encoder.ReadEncoder();
	}
}


void Start(){
	Motor motor[4] = {Motor(0), Motor(1), Motor(2), Motor(3)};
	while(1){
		/*usbStruct.val1 = 100;
		usbStruct.val2 = 101;*/
		/*motor[0].SetDribble(recvUSBStruct->dribbleSpd);
		for(int i=0;i<4;i++){
			motor[i].SetSpeed(recvUSBStruct->motorSpd[i]);
		}*/
		//sendUSBStruct.button = HAL_GPIO_ReadPin(Btn_GPIO_Port, Btn_Pin);
		//HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PinState(recvUSBStruct->led & 1));
		//HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PinState(recvUSBStruct->led & 2));
		//HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PinState(recvUSBStruct->led & 4));
		//HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PinState(recvUSBStruct->led & 8));
		HAL_Delay(1);
		//while(CDC_Transmit_FS((uint8_t*)&sendUSBStruct, 24) == USBD_BUSY);
	}
}
