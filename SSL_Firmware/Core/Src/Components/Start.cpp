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
#include "BTS7960B.hpp"
//#include "RF24.hpp"
#include "RoboIME_RF24.hpp"

extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart3;
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern void (*usbRecvCallback)(uint8_t*, uint32_t*);
grSim_Robot_Command receivedPacket = grSim_Robot_Command_init_default;
Feedback sendPacket = Feedback_init_default;
uint8_t sendBuffer[64];

Encoder encoder(0);
CommunicationUSB usb(&usbRecvCallback);
//BTS7960B motorbts(&(TIM10->CCR1), &(TIM11->CCR1), GPIOD, GPIO_PIN_0, GPIOD, GPIO_PIN_1);
//RF24 radio;
RoboIME_RF24 radio(nRF_CSn_GPIO_Port, nRF_CSn_Pin, nRF_CE_GPIO_Port, nRF_CE_Pin, nRF_IRQ_GPIO_Port, nRF_IRQ_Pin, &hspi1);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim6){
		usb.TransmitEncoderReadingRPM(encoder.ReadEncoder());
		usb.TransmitFeedbackPacket();
		//motorbts.setSpeed((int32_t)receivedPacket.velangular);
	}
}

void packetReceivedCallback(void){

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	radio.extiCallback(GPIO_Pin);
}

void Start(){
	uint8_t received[64];
	radio.setup();
	radio.setRobotId(6);
	radio.setDirection(1);
	//Motor motor[4] = {Motor(0), Motor(1), Motor(2), Motor(3)};
	/*radio.begin(nRF_CSn_GPIO_Port, nRF_CSn_Pin, nRF_CE_GPIO_Port, nRF_CE_Pin, hspi1);
	radio.DebugUART_Init(huart3);
	radio.printRadioSettings();*/
	while(1){
		//radio.sendPayload((uint8_t*)"Hello World", 12);
		radio.readRxPayload(received);
		HAL_Delay(20);
	}
}
