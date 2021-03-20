/*
 * Motor.cpp
 *
 *  Created on: 20 de mar de 2021
 *      Author: Moraes
 */

#include "Motor.hpp"

Motor::Motor (uint8_t motorId){
	Pwm_Max = TIM8->ARR;
	switch(motorId){
		case 0:
		{
			MAL_GPIO_Port = M0_MAL_GPIO_Port;
			MBL_GPIO_Port = M0_MBL_GPIO_Port;
			MAL_Pin = M0_MAL_Pin;
			MBL_Pin = M0_MBL_Pin;
			MAH_Pwm = &(TIM8->CCR4);
			MBH_Pwm = &(TIM8->CCR2);
			break;
		}
		case 1:
		{
			MAL_GPIO_Port = M1_MAL_GPIO_Port;
			MBL_GPIO_Port = M1_MBL_GPIO_Port;
			MAL_Pin = M1_MAL_Pin;
			MBL_Pin = M1_MBL_Pin;
			MAH_Pwm = &(TIM1->CCR1);
			MBH_Pwm = &(TIM8->CCR3);
			break;
		}

		case 2:
		{
			MAL_GPIO_Port = M2_MAL_GPIO_Port;
			MBL_GPIO_Port = M2_MBL_GPIO_Port;
			MAL_Pin = M2_MAL_Pin;
			MBL_Pin = M2_MBL_Pin;
			MAH_Pwm = &(TIM8->CCR1);
			MBH_Pwm = &(TIM1->CCR2);
			break;
		}
		case 3:
		{
			MAL_GPIO_Port = M3_MAL_GPIO_Port;
			MBL_GPIO_Port = M3_MBL_GPIO_Port;
			MAL_Pin = M3_MAL_Pin;
			MBL_Pin = M3_MBL_Pin;
			MAH_Pwm = &(TIM1->CCR4);
			MBH_Pwm = &(TIM1->CCR3);
			break;
		}
		default:
			break;
	}
}




void Motor::SetSpeed(int32_t spd){
	if(spd>0){
		*MAH_Pwm = Pwm_Max - spd; //MAH
		*MBH_Pwm = Pwm_Max; //MBH
		HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PinState(RESET));
		HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PinState(SET));
	}else if(spd<0){
		*MAH_Pwm = Pwm_Max; //MAH
		*MBH_Pwm = Pwm_Max + spd; //MBH
		HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PinState(SET));
		HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PinState(RESET));
	}else{
		*MAH_Pwm = Pwm_Max; //MAH
		*MBH_Pwm = Pwm_Max; //MBH
		HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PinState(SET));
		HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PinState(SET));
	}


}

void Motor::SetDribble(int32_t spd){
	//*DAH_Pwm = Pwm_Max - spd; //O drible só tem um pino
	TIM9->CCR1 = Pwm_Max - spd;
}
