/*
 * Kick.cpp
 *
 *  Created on: 20 de mar de 2022
 *      Author: Vinicius Moraes
 *
 *
 *     Modified by Léo
 *
 */

#include "Kick.hpp"


Kick::Kick(GPIO_TypeDef* _KICK_H_GPIO_Port, GPIO_TypeDef* _KICK_L_GPIO_Port, GPIO_TypeDef* _KICK_C_GPIO_Port, uint16_t _KICK_H_Pin,uint16_t _KICK_L_Pin,uint16_t _KICK_C_Pin, TIM_HandleTypeDef* _KICK_HL_TIM, TIM_HandleTypeDef* _KICK_RC_TIM, TIM_HandleTypeDef* _KICK_C_TIM, uint32_t _chargeTime, uint32_t _rechargeTime){
	KICK_H_GPIO_Port = _KICK_H_GPIO_Port;
	KICK_L_GPIO_Port = _KICK_L_GPIO_Port;
	KICK_C_GPIO_Port = _KICK_C_GPIO_Port;
	KICK_HL_TIM = _KICK_HL_TIM;
	KICK_RC_TIM = _KICK_RC_TIM;
	KICK_C_TIM = _KICK_C_TIM;
	KICK_H_Pin = _KICK_H_Pin;
	KICK_L_Pin = _KICK_L_Pin;
	KICK_C_Pin = _KICK_C_Pin;
	kickCharged = GPIO_PIN_RESET;
	kickEnable = GPIO_PIN_RESET;
	KICK_C_TIM->Instance->ARR=10000*_chargeTime;
	KICK_RC_TIM->Instance->ARR=10000*_rechargeTime;
}

void Kick::SetKick(float kickspeedx, float kickspeedz){
	uint32_t kickPower = 0;
	uint32_t kickHigh = 0;
	uint32_t kickLow = 0;

	if(kickspeedx !=0){
		KickHigh(1);
	}

	//fazer conversões aqui: speed é o que recebe da intel e kick power é o tempo em ms que manda para a placa

	//if(kickHigh == 1){

		//KickHigh(kickPower);

	//} else if(kickLow==1) {

		//KickLow(kickPower);

	//}
}

void Kick::KickHigh(uint32_t kickPower){
	if(kickCharged){
		HAL_GPIO_WritePin(KICK_C_GPIO_Port, KICK_C_Pin, GPIO_PinState(RESET));

		kickCharged = GPIO_PIN_RESET;

		kickEnable = GPIO_PIN_SET;

		KICK_HL_TIM->Instance->ARR=10000*kickPower;

		__HAL_TIM_SET_COUNTER(KICK_HL_TIM,0);

		HAL_GPIO_WritePin(KICK_H_GPIO_Port, KICK_H_Pin, GPIO_PinState(SET));
	}
}

void Kick::KickLow(uint32_t kickPower){
	if(kickCharged){
		HAL_GPIO_WritePin(KICK_C_GPIO_Port, KICK_C_Pin, GPIO_PinState(RESET));

		KICK_HL_TIM->Instance->ARR=10000*kickPower;

		__HAL_TIM_SET_COUNTER(KICK_HL_TIM,0);

		__HAL_TIM_SET_COUNTER(KICK_RC_TIM,0);

		kickEnable=GPIO_PIN_SET;

		HAL_GPIO_WritePin(KICK_L_GPIO_Port, KICK_L_Pin, GPIO_PinState(SET));
	}
}

void Kick::Charge(){
	__HAL_TIM_SET_COUNTER(KICK_C_TIM,0);

	HAL_GPIO_WritePin(KICK_C_GPIO_Port, KICK_C_Pin, GPIO_PinState(SET));
}
