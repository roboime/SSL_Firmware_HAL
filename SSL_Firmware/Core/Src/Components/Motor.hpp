/*
 * Motor.hpp
 *
 *  Created on: 20 de mar de 2021
 *      Author: Moraes
 */

#ifndef SRC_COMPONENTS_MOTOR_HPP_
#define SRC_COMPONENTS_MOTOR_HPP_

#include "main.h"
#include "Encoder.hpp"

//ROBO NOVO:
#define R_roda 0.019
#define PI 3.1415926
#define TIM6_delay 0.001
#define ENC_DIV 400
#define FT_TRANS -4 //transmissao invertida devido a engrenagem encaixada por baixo
#define CONVERSION 2*PI*R_roda/(TIM6_delay*ENC_DIV*FT_TRANS)


class Motor{
public:
	Motor(uint8_t motorId);
	void SetSpeed(int32_t spd);
	void SetDribble(int32_t spd);
	void GetSpeed();
	void ControlSpeed(float desiredSpd);

	float real_wheel_speed;

private:
	GPIO_TypeDef* MAL_GPIO_Port;
	GPIO_TypeDef* MBL_GPIO_Port;
	uint16_t MAL_Pin;
	uint16_t MBL_Pin;
	__IO uint32_t* MAH_Pwm;
	__IO uint32_t* MBH_Pwm;
	__IO uint32_t* DAH_Pwm;
	uint32_t Pwm_Max;
	Encoder* M_Enc;
	int32_t dutycycle;
	float lasterror;
	float error;
	float derror;
	float last_error[20];
	float ierror;
	static float cp;
	static float cd;
	static float ci;
};







#endif /* SRC_COMPONENTS_MOTOR_HPP_ */
