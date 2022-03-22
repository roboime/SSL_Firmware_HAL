/*
 * Kick.cpp
 *
 *  Created on: 20 de mar de 2022
 *      Author: Vinicius Moraes
 */

#include "Kick.hpp"


Kick::Kick() {

	KICK_L_GPIO_Port = LD4_GPIO_Port;	//Chute BAIXO
	KICK_L_Pin = LD4_Pin;

	KICK_H_GPIO_Port = LD5_GPIO_Port; //Chute ALTO
	KICK_H_Pin = LD5_Pin;

	KICK_C_GPIO_Port = LD6_GPIO_Port; //CHARGE
	KICK_C_Pin = LD6_Pin;

	isCharge = GPIO_PIN_RESET;
}

void Kick::SetPower(uint32_t power){
	kickPower = power;
}

void Kick::KickHigh(uint32_t power){
	SetPower(power);
	HAL_GPIO_WritePin(KICK_H_GPIO_Port, KICK_H_Pin, GPIO_PinState(SET));
	//delay_ticks((uint32_t) (power*611)); //611 = Gustavo's magic number          //Refatorar tempo mínimo
	HAL_GPIO_WritePin(KICK_H_GPIO_Port, KICK_H_Pin, GPIO_PinState(RESET));
	GPIO_PinState isCharge = GPIO_PIN_RESET;
}

void Kick::KickLow(uint32_t power){
	SetPower(power);
	HAL_GPIO_WritePin(KICK_L_GPIO_Port, KICK_L_Pin, GPIO_PinState(SET));
	//delay_ticks((uint32_t) (power*611)); //611 = Gustavo's magic number          //Refatorar tempo mínimo
	HAL_GPIO_WritePin(KICK_L_GPIO_Port, KICK_L_Pin, GPIO_PinState(RESET));
	GPIO_PinState isCharge = GPIO_PIN_RESET;
}

void Kick::Charge(){
	HAL_GPIO_WritePin(KICK_C_GPIO_Port, KICK_C_Pin, GPIO_PinState(SET));
	//delay_ticks((uint32_t) (power*611)); //611 = Gustavo's magic number          //Refatorar tempo de carga 6.11s?
	HAL_GPIO_WritePin(KICK_C_GPIO_Port, KICK_C_Pin, GPIO_PinState(RESET));
	GPIO_PinState isCharge = GPIO_PIN_SET;
}
