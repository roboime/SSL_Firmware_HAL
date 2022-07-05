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
#define recharge_time 10 //sec

extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim14;
extern ADC_HandleTypeDef hadc2;

Robo::Robo(uint8_t roboId) {
	for(int i=0; i<4; ++i){
		R_Motors[i]= new Motor(i);
	}
	R_Kick = new Kick(CHIP_KICK_GPIO_Port, KICK_GPIO_Port, CHARGE_EN_GPIO_Port, CHIP_KICK_Pin, KICK_Pin, CHARGE_EN_Pin, &htim7, &htim10, &htim14, recharge_time);
	R_Dribble = new Dribble();
}

void Robo::set_robo_speed(float v_r, float v_t, float w, float kp, float kc){
	R_Motors[0]->ControlSpeed(-v_t*cos_phi - v_r*sin_phi - w*R, kp,kc,v_r);
	R_Motors[1]->ControlSpeed(-v_t*cos_theta + v_r*sin_theta - w*R, kp,kc,v_r);
	R_Motors[2]->ControlSpeed(v_t*cos_phi - v_r*sin_phi - w*R, kp,kc,v_r);
	R_Motors[3]->ControlSpeed(v_t*cos_theta + v_r*sin_theta - w*R, kp,kc,v_r);
}

void Robo::set_kick(float kickspeedx, float kickspeedz){
	R_Kick->SetKick(kickspeedx,kickspeedz);
}

bool Robo::hasBall(void){
	return (bool)HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin);
}

float Robo::calc_vbat(){
	int BATREF;
	float VBAT;
	HAL_ADC_Start(&hadc2);
	if(HAL_ADC_PollForConversion(&hadc2, 5) == HAL_OK){
		//Leitura analógica na porta PC0
		BATREF = HAL_ADC_GetValue(&hadc2);
	}
	HAL_ADC_Stop(&hadc2);
	//HAL_Delay(100);
	//Variável de retorno com o fator de conversão
	VBAT = float(57*BATREF/(2*16364))                                                                                                                                                                                                                                                                                                                                                                                                             ;
	return VBAT;
}

