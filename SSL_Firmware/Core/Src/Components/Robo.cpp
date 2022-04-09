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

extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim14;

Robo::Robo(uint8_t roboId) {
	for(int i=0; i<4; ++i){
		R_Motors[i]= new Motor(i);
	}
	R_Kick = new Kick(LD5_GPIO_Port, LD4_GPIO_Port, LD6_GPIO_Port, LD5_Pin, LD4_Pin, LD6_Pin, &htim7, &htim10, &htim14);
	R_Dribble = new Dribble();
}

void Robo::set_robo_speed(float v_r, float v_t, float w){
	R_Motors[0]->ControlSpeed(v_t*cos_phi - v_r*sin_phi + w*R);
	R_Motors[1]->ControlSpeed(v_t*cos_theta + v_r*sin_theta + w*R);
	R_Motors[2]->ControlSpeed(-v_t*cos_phi - v_r*sin_phi + w*R);
	R_Motors[3]->ControlSpeed(-v_t*cos_theta + v_r*sin_theta + w*R);

	/*R_Motors[0]->SetSpeed(v_t);
	R_Motors[1]->SetSpeed(v_t);
	R_Motors[2]->SetSpeed(v_t);
	R_Motors[3]->SetSpeed(v_t);*/
}
