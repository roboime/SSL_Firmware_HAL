/*
 * Robo.cpp
 *
 *  Created on: 20 de mar de 2022
 *      Author: Vinicius Moraes
 */

#include "Robo.hpp"
#define sin_phi 0.50
#define cos_phi 0.866
#define sin_theta 0.707
#define cos_theta 0.707
#define R 0.075 //Raio do robo = 9cm
#define charge_time 0
#define recharge_time 0

extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim14;

Robo::Robo(uint8_t roboId) {
	for(int i=0; i<4; ++i){
		R_Motors[i]= new Motor(i);
	}
	R_Kick = new Kick(CHIP_KICK_GPIO_Port, KICK_GPIO_Port, CHARGE_EN_GPIO_Port, CHIP_KICK_Pin, KICK_Pin, CHARGE_EN_Pin, &htim7, &htim10, &htim14, charge_time);
	R_Dribble = new Dribble();
}

void Robo::set_robo_speed(float v_r, float v_t, float w){
	R_Motors[0]->ControlSpeed(-v_t*cos_phi - v_r*sin_phi - w*R);
	R_Motors[1]->ControlSpeed(-v_t*cos_theta + v_r*sin_theta - w*R);
	R_Motors[2]->ControlSpeed(v_t*cos_phi - v_r*sin_phi - w*R);
	R_Motors[3]->ControlSpeed(v_t*cos_theta + v_r*sin_theta - w*R);
}

void Robo::set_kick(float kickspeedx, float kickspeedz){
	R_Kick->SetKick(kickspeedx,kickspeedz);
}

