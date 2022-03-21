/*
 * Kick.hpp
 *
 *  Created on: 20 de mar de 2022
 *      Author: Vinicius Moraes
 */

#ifndef SRC_COMPONENTS_KICK_HPP_
#define SRC_COMPONENTS_KICK_HPP_

#include "main.h"

class Kick{
public:
	Kick();
	void Charge();
	void SetPower(uint32_t power);
	void KickHigh(uint32_t power);
	void KickLow(uint32_t power);
	GPIO_PinState isCharge;

private:
	GPIO_TypeDef* KICK_H_GPIO_Port;
	GPIO_TypeDef* KICK_L_GPIO_Port;
	GPIO_TypeDef* KICK_C_GPIO_Port;
	uint16_t KICK_H_Pin;
	uint16_t KICK_L_Pin;
	uint16_t KICK_C_Pin;
	uint32_t kickPower;

};

#endif /* SRC_COMPONENTS_KICK_HPP_ */
