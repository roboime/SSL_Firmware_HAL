/*
 * Start.cpp
 *
 *  Created on: 20 de mar de 2021
 *      Author: Moraes
 *
 *  Modified on: September 9 2023
 *  	Author: Frese
 */

#include "Start.hpp"
#include "usbd_cdc_if.h"

//Component includes
#include "Encoder.hpp"
#include "Motor.hpp"
#include "Robo.hpp"
#include "CommunicationUSB.hpp"
#include "BTS7960B.hpp"
#include "SerialDebug.hpp"
#include "Defines.hpp"
#include "RoboIME_SX1280.hpp"

//Protobuf includes
#include "grSim_Commands.pb.h"
#include "Feedback.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"

//Constant definitions
#define NUM_ROBOTS 8

//Global variables
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim14;
extern UART_HandleTypeDef huart3;
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

extern void (*usbRecvCallback)(uint8_t*, uint32_t*);
extern USBD_HandleTypeDef hUsbDeviceFS;
grSim_Robot_Command receivedPacket = grSim_Robot_Command_init_default;
Feedback sendPacket[NUM_ROBOTS];

// Master true , Slave = false
bool transmitter = false;

SX1280_Send_Packet_t SX1280_Send_Packet[16];
SX1280_Feedback_Packet_t SX1280_Feedback_Packet;
SX1280_Feedback_Packet_t SX1280_FeedbackReceive_Packet[16];
uint8_t commCounter = 0;
uint32_t usbCounter = 0;

//Temporary (only for debug)
char serialBuf[64];

//Objects
Robo robo(1);
CommunicationUSB usb(&usbRecvCallback);
Motor motor[4] = {Motor(0), Motor(1), Motor(2), Motor(3)};
RoboIME_SX1280 radio_SX1280;
SerialDebug debug(&huart3);

bool checaNotANumber(SX1280_Send_Packet_t pacote){
	if(isnan(pacote.velangular)){
		return false;
	}
	if(isnan(pacote.veltangent)){
		return false;
	}
	if(isnan(pacote.velnormal)){
		return false;
	}
	if(isnan(pacote.kickspeedx)){
		return false;
	}
	if(isnan(pacote.kickspeedz)){
		return false;
	}
	return true;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim6){
		if(!transmitter ){
			/*FEEDBACK DATA*/

			/*NORMAL DATA*/
			if(HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin)){
					HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin,GPIO_PIN_SET);
				}
				else{
					HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin,GPIO_PIN_RESET);
				}
			if(commCounter < 100){	//Verifica se recebeu pacote no último 1s
				if(checaNotANumber(SX1280_Send_Packet[0])){
					robo.set_robo_speed(SX1280_Send_Packet[0].velnormal, SX1280_Send_Packet[0].veltangent, SX1280_Send_Packet[0].velangular);
					robo.set_kick(SX1280_Send_Packet[0].kickspeedx,SX1280_Send_Packet[0].kickspeedz);
					robo.set_dribble(SX1280_Send_Packet[0].spinner);
				}else{
					//Perdeu a comunicação
					robo.set_robo_speed(0, 0, 0);
					robo.set_kick(0, 0);
					robo.set_dribble(false);
				}
			}else{
				//Perdeu a comunicação
				robo.set_robo_speed(0, 0, 0);
				robo.set_kick(0, 0);
				robo.set_dribble(false);
				HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
				commCounter = 100;
			}
		}
	}
	else if(htim == robo.R_Kick->KICK_C_TIM)
	{
		if(HAL_GPIO_ReadPin(robo.R_Kick->KICK_C_GPIO_Port, robo.R_Kick->KICK_C_Pin) == GPIO_PIN_SET){
			HAL_GPIO_WritePin(robo.R_Kick->KICK_C_GPIO_Port, robo.R_Kick->KICK_C_Pin, GPIO_PIN_RESET);

			robo.R_Kick->kickCharged = GPIO_PIN_SET;

			__HAL_TIM_SET_COUNTER(robo.R_Kick->KICK_RC_TIM,0);
		}
	}
	else if(htim == robo.R_Kick->KICK_HL_TIM)
	{
		if(robo.R_Kick->kickEnable == GPIO_PIN_SET){
			HAL_GPIO_WritePin(robo.R_Kick->KICK_H_GPIO_Port, robo.R_Kick->KICK_H_Pin, GPIO_PIN_RESET);

			HAL_GPIO_WritePin(robo.R_Kick->KICK_L_GPIO_Port, robo.R_Kick->KICK_L_Pin,GPIO_PIN_RESET);

			robo.R_Kick->kickEnable = GPIO_PIN_RESET;
			robo.R_Kick->kickCharged = GPIO_PIN_RESET;

			robo.R_Kick->Charge(5);
		}
	}
	else if(htim == robo.R_Kick->KICK_RC_TIM)
	{
		if(robo.R_Kick->kickEnable == GPIO_PIN_RESET){
			robo.R_Kick->Charge(1);
		}
	}
}

void USBpacketReceivedCallback(void){
	if(receivedPacket.id > 16){
	}else{
		usbCounter = 0;
		SX1280_Send_Packet[receivedPacket.id].kickspeedx = receivedPacket.kickspeedx;
		SX1280_Send_Packet[receivedPacket.id].kickspeedz = receivedPacket.kickspeedz;
		SX1280_Send_Packet[receivedPacket.id].veltangent = receivedPacket.veltangent;
		SX1280_Send_Packet[receivedPacket.id].velnormal = receivedPacket.velnormal;
		SX1280_Send_Packet[receivedPacket.id].velangular = receivedPacket.velangular;
		SX1280_Send_Packet[receivedPacket.id].spinner = receivedPacket.spinner;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	switch (GPIO_Pin){
	case GPIO_PIN_5:
		radio_SX1280.GPIOCallback();
		break;
	default:
		break;
	}
}


void Flash_Write(uint8_t data, uint32_t adress, uint32_t sector_num){
	//Unlock the flash
	HAL_FLASH_Unlock();
	//Erase sector
	FLASH_Erase_Sector(sector_num, FLASH_VOLTAGE_RANGE_3);
	//Lock the flash
	HAL_FLASH_Lock();
	FLASH_WaitForLastOperation(1000);
	//Unlock the flash
	HAL_FLASH_Unlock();
	//Write to Flash
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, adress , data);
	//Lock the Flash space
	HAL_FLASH_Lock();

}

void Start(){
	Robo robo(1);
	uint8_t id = *(uint8_t *)0x080E0000;
		if(id>15)
			id = 0;
	debug.setLevel(SerialDebug::DEBUG_LEVEL_DEBUG);
	debug.info("SSL firmware start");
	for (uint32_t i=0; i< NUM_ROBOTS; i++){
		sendPacket[i] = Feedback_init_default;
	}
/* INITIAL PAYLOAD */
	SX1280_Send_Packet[0].velangular = 0;
	SX1280_Send_Packet[0].veltangent = 0;
	SX1280_Send_Packet[0].velnormal = 0;
	SX1280_Send_Packet[0].kickspeedx = 0;
	SX1280_Send_Packet[0].kickspeedz = 0;
	SX1280_Send_Packet[0].spinner = false;

	SX1280_Feedback_Packet.battery = 1;
	SX1280_Feedback_Packet.encoder1 = 1;
	SX1280_Feedback_Packet.encoder2 = 3;
	SX1280_Feedback_Packet.encoder2 = 4;
	SX1280_Feedback_Packet.encoder3 = 5;
	SX1280_Feedback_Packet.encoder4 = 6;
	SX1280_Feedback_Packet.id = 2;
	SX1280_Feedback_Packet.packetId = 1;

/*DEFINING ROBOT ID*/
	for(uint32_t i=0; i<2000; i++){
		HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, (GPIO_PinState)(id & 1));
		HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, (GPIO_PinState)((id>>1) & 1));
		HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, (GPIO_PinState)((id>>2) & 1));
		HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, (GPIO_PinState)((id>>3) & 1));
		if(!HAL_GPIO_ReadPin(Btn_GPIO_Port, Btn_Pin)){
			id = (id+1) % 16;
			i=0;
			HAL_Delay(2);
			while(!HAL_GPIO_ReadPin(Btn_GPIO_Port, Btn_Pin));
		}
		HAL_Delay(1);
	}
	Flash_Write(id, 0x080E0000, 11);


#ifdef DEEPWEB

#else

#endif
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);

/* RADIO SETUP */
	radio_SX1280.setupDataRadio();

/* ROBOT INITIAL STATE VERIFICATION */

	/* COM STATUS SETUP */
	if(HAL_GPIO_ReadPin(TX_Detect_GPIO_Port, TX_Detect_Pin) == GPIO_PIN_RESET){
		//TX (placa de COM)
		transmitter = true;
		debug.info("PE15 set as transmitter (computer)");
	}else{
		//RX (Robô)
		transmitter = false;
		debug.info("PE15 set as receiver (robot)");
	}

	/* ----------------- MASTER ----------------- */
	if(!transmitter){
		radio_SX1280.setRobotId(id);
	}
	//GAmbiarra
	radio_SX1280.setRobotId(1);
	/* CHARGING CAPACITOR */
	robo.R_Kick->kickCharged = GPIO_PIN_RESET;
	robo.R_Kick->Charge(5);

	/* COM LOOP */
	while(1){
		if(transmitter){
			for(uint8_t i=0; i<NUM_ROBOTS; i++){
				SX1280_Send_Packet[i].id = i;
				for(uint8_t j=0; j<NUM_ROBOTS; j++){
					SX1280_Send_Packet[j].packetId++;
				}
				usbCounter++;
	/* COMMANDS FROM INTEL */
#ifdef INTEL
				if(usbCounter > 500){	//Verifica se recebeu pacote do USb nos últimos Xs
					//Perdeu o USB
					for (uint8_t i=0; i<16; i++)
					{
						SX1280_Send_Packet[i].velangular = 0;
						SX1280_Send_Packet[i].veltangent = 0;
						SX1280_Send_Packet[i].velnormal = 0;
						SX1280_Send_Packet[i].kickspeedx = 0;
						SX1280_Send_Packet[i].kickspeedz = 0;
						SX1280_Send_Packet[i].spinner = false;
					}
				//Blinking red LED
					HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
					usbCounter = 500;
				}else{
					HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
				}
#endif

/* --------- DEGUG DATA -----------*/

/* COMMUNICATION BACK AND FORTH */

				/*SENDING PAYLOAD*/
				CDC_Transmit_FS((uint8_t *)"Sending Package\n",strlen("Sending Package\n"));
				HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);
				if(radio_SX1280.sendPayload(&SX1280_Send_Packet[i], sizeof(SX1280_Send_Packet[i]))){HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);} //Blink LED
				/*RECEIVING FEEDBACK*/
				CDC_Transmit_FS((uint8_t *)"Receiving Feedback Package\n",strlen("Receiving Feedback\n"));
				if(radio_SX1280.receiveFeedback((&SX1280_FeedbackReceive_Packet[i]))){HAL_GPIO_TogglePin(LD4_GPIO_Port, LD5_Pin);} //Blink LED
			//	CDC_Transmit_FS((uint8_t *)SX1280_FeedbackReceive_Packet[i].battery,strlen(SX1280_FeedbackReceive_Packet[i].battery));
			}
		}

	/* ----------------- ROBOT ----------------- */
	if(!transmitter ){
		/*RECEIVING PAYLOAD*/
		if(radio_SX1280.receivePayload((&SX1280_Send_Packet[0]))){
			HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
			commCounter = 0;
			/*SENDING FEEDBACK*/
			if(radio_SX1280.sendFeedback(&SX1280_Feedback_Packet, sizeof(SX1280_Feedback_Packet))){HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);} //Blink LED GREEN
		}else{
			commCounter++;
		}
		}
	}
}
