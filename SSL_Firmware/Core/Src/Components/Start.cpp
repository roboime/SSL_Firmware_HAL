/*
 * Start.cpp
 *
 *  Created on: 20 de mar de 2021
 *      Author: Moraes
 */

#include "Start.hpp"
#include "usbd_cdc_if.h"

//Component includes
#include "Encoder.hpp"
#include "Motor.hpp"
#include "Robo.hpp"
#include "CommunicationUSB.hpp"
#include "BTS7960B.hpp"
#include "RoboIME_RF24.hpp"
#include "SerialDebug.hpp"
#include "CommunicationNRF.hpp"

//Protobuf includes
#include "grSim_Commands.pb.h"
#include "Feedback.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"

//Constant definitions
#define NUM_ROBOTS 16

//Global variables
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart3;
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern void (*usbRecvCallback)(uint8_t*, uint32_t*);
grSim_Robot_Command receivedPacket = grSim_Robot_Command_init_default;
Feedback sendPacket = Feedback_init_default;
bool transmitter;
nRF_Send_Packet_t nRF_Send_Packet[16];
nRF_Feedback_Packet_t nRF_Feedback_Packet;

//Temporary (only for debug)
char serialBuf[64];

//Objects
Robo robo(1);
CommunicationUSB usb(&usbRecvCallback);
//BTS7960B motorbts(&(TIM10->CCR1), &(TIM11->CCR1), GPIOD, GPIO_PIN_0, GPIOD, GPIO_PIN_1);
//Motor motor[4] = {Motor(0), Motor(1), Motor(2), Motor(3)};
RoboIME_RF24 radio(nRF_CSn_GPIO_Port, nRF_CSn_Pin, nRF_CE_GPIO_Port, nRF_CE_Pin, nRF_IRQ_GPIO_Port, nRF_IRQ_Pin, &hspi1);
SerialDebug debug(&huart3);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim6){
		if(!transmitter && radio.ready){
			HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
			nRF_Feedback_Packet.packetId++;
			radio.UploadAckPayload((uint8_t*)&nRF_Feedback_Packet, sizeof(nRF_Feedback_Packet));
			if(radio.getReceivedPayload((uint8_t*)nRF_Send_Packet)){
				/*sprintf(serialBuf, "Vt %lf", nRF_Send_Packet[0].veltangent);
				debug.debug(serialBuf);*/
				HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
			}
			robo.set_robo_speed(nRF_Send_Packet[0].velnormal, nRF_Send_Packet[0].veltangent, nRF_Send_Packet[0].velangular);
		}
		else if(htim == robo.R_Kick->KICK_C_TIM)
		{
			HAL_GPIO_WritePin(robo.R_Kick->KICK_C_GPIO_Port, robo.R_Kick->KICK_C_Pin, GPIO_PIN_RESET);
			robo.R_Kick->kickCharged = GPIO_PIN_SET;
		}

		else if(htim == robo.R_Kick->KICK_HL_TIM)
		{
			HAL_GPIO_WritePin(robo.R_Kick->KICK_H_GPIO_Port, robo.R_Kick->KICK_H_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(robo.R_Kick->KICK_L_GPIO_Port, robo.R_Kick->KICK_L_Pin,GPIO_PIN_RESET);
			if(!robo.R_Kick->kickCharged)
			{
				robo.R_Kick->Charge(0);
			}
		}

		else if(htim == robo.R_Kick->KICK_RC_TIM)
		{
			robo.R_Kick->Charge(0);
		}
	}
}

void USBpacketReceivedCallback(void){
	if(receivedPacket.id > 16){
		debug.error("USB protobuf ID > 16");
	}else{
		char debugmessage[64];
		sprintf(debugmessage, "ID %lu", receivedPacket.id);
		debug.debug(debugmessage);
		nRF_Send_Packet[receivedPacket.id].kickspeedx = receivedPacket.kickspeedx;
		nRF_Send_Packet[receivedPacket.id].kickspeedz = receivedPacket.kickspeedz;
		nRF_Send_Packet[receivedPacket.id].veltangent = receivedPacket.veltangent;
		nRF_Send_Packet[receivedPacket.id].velnormal = receivedPacket.velnormal;
		nRF_Send_Packet[receivedPacket.id].velangular = receivedPacket.velangular;
		nRF_Send_Packet[receivedPacket.id].spinner = receivedPacket.spinner;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == nRF_IRQ_Pin && HAL_GPIO_ReadPin(nRF_IRQ_GPIO_Port, nRF_IRQ_Pin) == GPIO_PIN_RESET){
		radio.extiCallback();
	}
}

void Start(){
	Robo robo(1);
	debug.setLevel(SerialDebug::DEBUG_LEVEL_DEBUG);
	debug.info("SSL firmware start");
	radio.ce(GPIO_PIN_SET);
	HAL_Delay(500);
	radio.setup();
	if(HAL_GPIO_ReadPin(TX_Detect_GPIO_Port, TX_Detect_Pin) == GPIO_PIN_RESET){
		//TX (placa de COM)
		transmitter = true;
		debug.info("PD10 set as transmitter (computer)");
		radio.setDirection(PWRUP_TX);
	}else{
		//RX (Robô)
		transmitter = false;
		debug.info("PD10 set as receiver (robot)");
		radio.setDirection(PWRUP_RX);
	}
	if(!transmitter){
		radio.setRobotId(6);
	}
	debug.info("ID = 6");
	radio.ready = true;
	while(1){
		if(transmitter){
			for(uint8_t i=0; i<NUM_ROBOTS; i++){
				radio.setRobotId(i);
				nRF_Send_Packet[i].packetId++;
				radio.sendPayload((uint8_t*)&nRF_Send_Packet[i], sizeof(nRF_Send_Packet[i]));	//Conversão do tipo do ponteiro
				if(radio.getReceivedPayload((uint8_t*)&nRF_Feedback_Packet)){
					HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
					//debug.debug((char*)received);
					sendPacket.battery = nRF_Feedback_Packet.battery;
					sendPacket.encoder1 = nRF_Feedback_Packet.encoder1;
					sendPacket.encoder2 = nRF_Feedback_Packet.encoder2;
					sendPacket.encoder3 = nRF_Feedback_Packet.encoder3;
					sendPacket.encoder4 = nRF_Feedback_Packet.encoder4;
					sendPacket.status = nRF_Feedback_Packet.status;
					sendPacket.id = 6;
					usb.TransmitFeedbackPacket();
				}
				HAL_Delay(1);
			}
			debug.debug("sent");
		}else{
			nRF_Feedback_Packet.status +=1;
			HAL_Delay(1000);
		}
	}
}
