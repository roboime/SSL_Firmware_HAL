/*
 * Robot.cpp
 *
 *  Created on: Mar 17, 2023
 *      Author: Gabriel
 */

#include "Robot.hpp"
#include <cstdlib>
#include "Definitions.hpp"
#include "usbd_cdc_if.h"

#define CONVERSION (reductionRatio/(ticksPerSecond*2*3.14159*wheelRadius))

extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;

uint8_t buf[64];

Robot::Robot() {

}

Robot::~Robot() {

}

void Robot::usbCallback(uint8_t* Buf, uint32_t *Len){
	//HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxBuffer, 256);
	memcpy(rxBuffer, Buf, *Len);
}

void Robot::controlCallback(){
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
	float desiredSpeed0;
	sscanf((char*)rxBuffer, "%f,%f", &desiredSpeed0);	// Desired speed in mm/s
	float convertedSpeed0 = desiredSpeed0*CONVERSION;	// Converted speed in rev/tick
#ifdef CONTROL_DISABLED
	motor0.setPower(desiredSpeed0);
#else
	motor0.pid(convertedSpeed0);
#endif
	sprintf((char*)buf, ">Speed:%+0.6e,%+0.6e,%+0.6e,%+0.6e",
			motor0.getCurrentRevPerTick()/CONVERSION,
			0.,
			desiredSpeed0,
			0.);
	//HAL_UART_Transmit_DMA(&huart1, buf, 64);
	CDC_Transmit_FS(buf, 64);
}

void Robot::init(){
	motor0.setEncoder(&encoder0);
	motor0.kp = 0.44836/CONVERSION;
	motor0.ki = 16.64/(ticksPerSecond*CONVERSION);
	motor0.kd = 0*ticksPerSecond/CONVERSION;
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
	HAL_TIM_Base_Start_IT(&htim6);
	//HAL_UARTEx_ReceiveToIdle_DMA(&huart1, rxBuffer, 256);
	motor0.setEnabled(true);
}
