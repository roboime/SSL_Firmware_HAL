/*
 * Motor.cpp
 *
 *  Created on: 20 de mar de 2021
 *      Author: Moraes
 */

#include "Motor.hpp"

float Motor::cp=10000.0f;           //Valores do código antigo
float Motor::ci=10.0f;
float Motor::cd=1000.0f;

Motor::Motor (uint8_t motorId){
	Pwm_Max = TIM8->ARR;
	M_Enc =  new Encoder(motorId);
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


void Motor::GetSpeed(){
	int16_t distance=M_Enc->ReadEncoder();

	float speed=(float)distance*CONVERSION; //converte da unidade da roda para m/s (vel do centro da roda)
	                                     //talvez seja melhor converter de m/s pra unidade da roda
	real_wheel_speed=speed;
};

void Motor::ControlSpeed(float desired_speed){
	GetSpeed();
	error = desired_speed-real_wheel_speed;
	ierror = 0;
	for(int j = 18; j > 0; j--){
		last_error[j+1]=last_error[j];
		ierror = ierror + last_error[j+1];
	}
	last_error[0]=error;
	ierror = ierror + last_error[0];
	//if(ierror > 1000) ierror = 1000;
	//if(ierror < -1000) ierror = -1000;

	derror=error-last_error[1];

	float out=cp*error + ci * ierror + cd * derror;


	dutycycle=out;
	if(dutycycle>1000) dutycycle=1000;           //Conferir valores pq no código antigo a variável dutycycle era uint16_t
	if(dutycycle<-1000) dutycycle=-1000;

	SetSpeed(dutycycle);
};
