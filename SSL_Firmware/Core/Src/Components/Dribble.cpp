/*
 * Dribble.cpp
 *
 *  Created on: Mar 20, 2022
 *      Author: Vinicius Moraes
 */

#include "Dribble.hpp"

Dribble::Dribble() {
	Pwm_Max = TIM8->ARR;
	MD_Pwm = &(TIM9->CCR1);
}

void Dribble::SetSpeed(int32_t spd){
	*MD_Pwm = Pwm_Max - spd; //O drible só tem um pino
	//TIM9->CCR1 = Pwm_Max - spd;
}
