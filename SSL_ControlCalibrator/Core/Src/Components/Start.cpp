/*
 * Start.hpp
 *
 *  Created on: 01 de jul de 2023
 *      Author: Gabriel Lima
 */

#include "Start.hpp"
#include "Robot.hpp"

extern TIM_HandleTypeDef htim6;

Robot robot;

void usbCallback(uint8_t* Buf, uint32_t *Len){
	robot.usbCallback(Buf, Len);
}

void controlCallback(TIM_HandleTypeDef* htim){
	robot.controlCallback();
}

void Start(){
	htim6.PeriodElapsedCallback = controlCallback;
	HAL_TIM_Base_Start_IT(&htim6);
	robot.init();
	while(true){

	}
}
