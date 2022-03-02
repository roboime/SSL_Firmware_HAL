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
#include "CommunicationUSB.hpp"
#include "BTS7960B.hpp"
#include "RoboIME_RF24.hpp"
#include "SerialDebug.hpp"

//Protobuf includes
#include "grSim_Commands.pb.h"
#include "Feedback.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"

//Constant definitions
#define NUM_ROBOTS 16

//Type efinitions
struct nRF_Send_Packet_t{
	float kickspeedx;
	float kickspeedz;
	float veltangent;
	float velnormal;
	float velangular;
	bool spinner;
};
struct nRF_Receive_Packet_t{
	uint32_t status;
	float battery;
	float encoder1;
	float encoder2;
	float encoder3;
	float encoder4;
};

//Global variables
extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart3;
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
extern void (*usbRecvCallback)(uint8_t*, uint32_t*);
grSim_Robot_Command receivedPacket = grSim_Robot_Command_init_default;
Feedback sendPacket = Feedback_init_default;
bool transmitter;
nRF_Send_Packet_t nRF_Send_Packet[16];
nRF_Receive_Packet_t nRF_Receive_Packet[16];

//Objects
Encoder encoder(0);
CommunicationUSB usb(&usbRecvCallback);
//BTS7960B motorbts(&(TIM10->CCR1), &(TIM11->CCR1), GPIOD, GPIO_PIN_0, GPIOD, GPIO_PIN_1);
//Motor motor[4] = {Motor(0), Motor(1), Motor(2), Motor(3)};
RoboIME_RF24 radio(nRF_CSn_GPIO_Port, nRF_CSn_Pin, nRF_CE_GPIO_Port, nRF_CE_Pin, nRF_IRQ_GPIO_Port, nRF_IRQ_Pin, &hspi1);
SerialDebug debug(&huart3);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim6){
		/*usb.TransmitEncoderReadingRPM(encoder.ReadEncoder());
		usb.TransmitFeedbackPacket();*/
		if(!transmitter && radio.ready){
			radio.UploadAckPayload((uint8_t*)"Com de volta OK", 16);
		}
		//motorbts.setSpeed((int32_t)receivedPacket.velangular);
	}
}

void USBpacketReceivedCallback(void){
	if(receivedPacket.id > 16){
		debug.error("USB protobuf ID > 16");
	}else{
		char debugmessage[64];
		sprintf(debugmessage, "USB protobuf ID = %lu", receivedPacket.id);
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
		debug.debug("nRF IRQ");
	}
}

void Start(){
	debug.setLevel(SerialDebug::DEBUG_LEVEL_DEBUG);
	debug.info("SSL firmware start");
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
	uint8_t received[64];
	radio.setup();
	radio.setRobotId(6);
	debug.info("ID = 6");
	radio.ready = true;
	while(1){
		if(transmitter){
			//radio.sendPayload((uint8_t*)"Hello World", 12);
			for(uint8_t i=0; i<NUM_ROBOTS; i++){
				radio.setRobotId(i);
				radio.sendPayload((uint8_t*)&nRF_Send_Packet[i], sizeof(nRF_Send_Packet[i]));	//Conversão do tipo do ponteiro
				radio.getReceivedPayload(received);
				debug.debug((char*)received);
				HAL_Delay(1);
			}
			debug.debug("radio sent");
		}else{

		}
	}
}
