/*
 * Motor.hpp
 *
 *  Created on: 20 de mar de 2021
 *      Author: Moraes
 */

#ifndef SRC_COMPONENTS_MOTOR_HPP_
#define SRC_COMPONENTS_MOTOR_HPP_

#include "main.h"

class Motor{
public:
	Motor(uint8_t motorId);
	void SetSpeed(int32_t spd);
	void SetDribble(int32_t spd);

private:
	GPIO_TypeDef* MAL_GPIO_Port;
	GPIO_TypeDef* MBL_GPIO_Port;
	uint16_t MAL_Pin;
	uint16_t MBL_Pin;
	__IO uint32_t* MAH_Pwm;
	__IO uint32_t* MBH_Pwm;
	__IO uint32_t* DAH_Pwm;
	uint32_t Pwm_Max;
};







#endif /* SRC_COMPONENTS_MOTOR_HPP_ */
