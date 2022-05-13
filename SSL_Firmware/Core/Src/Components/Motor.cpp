/*
 * Motor.cpp
 *
 *  Created on: 20 de mar de 2021
 *      Author: Moraes
 */

#include "Motor.hpp"

float Motor::cp=(10000.0f/10000)*65536;           //Valores do código antigo
float Motor::ci=(1000.0f/10000)*65536;
float Motor::cd=(1000.0f/10000)*65536;
extern nRF_Feedback_Packet_t nRF_Feedback_Packet;

Motor::Motor (uint8_t motorId){
	motorId_attrib = motorId;
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
	Pwm_Max = TIM8->ARR;
	if(spd>0){
		HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PinState(SET));
		*MBH_Pwm = Pwm_Max; //MBH
		HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PinState(RESET));
		*MAH_Pwm = Pwm_Max - spd; //MAH
	}else if(spd<0){
		HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PinState(RESET));
		*MBH_Pwm = Pwm_Max + spd; //MBH
		HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PinState(SET));
		*MAH_Pwm = Pwm_Max; //MAH
	}else{
		HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PinState(SET));
		*MBH_Pwm = Pwm_Max; //MBH
		HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PinState(SET));
		*MAH_Pwm = Pwm_Max; //MAH
	}
}


void Motor::GetSpeed(){
	int32_t distance=-M_Enc->ReadEncoder();

	float speed=(float)distance*CONVERSION; //converte da unidade da roda para m/s (vel do centro da roda)
	                                     //talvez seja melhor converter de m/s pra unidade da roda
	real_wheel_speed=(float)speed;
};

void Motor::ControlSpeed(float desired_speed){
	//real_wheel_speed=0;
	GetSpeed();
	error = desired_speed-real_wheel_speed;
	ierror = 0;
	for(int j = 18; j >= 0; j--){
		last_error[j+1]=last_error[j];
		ierror += last_error[j+1];
	}
	last_error[0]=error;
	ierror += last_error[0];
	if(ierror > 65535) ierror = 65535;
	if(ierror < -65535) ierror = -65535;

	derror=error-last_error[1];

	float out=cp*error + ci * ierror + cd * derror + (desired_speed/2.75)*65535; //Soma de duty cycle (linear)
	switch (motorId_attrib){
	case 0:
		nRF_Feedback_Packet.encoder1 = real_wheel_speed;
		break;
	case 1:
		nRF_Feedback_Packet.encoder2 = real_wheel_speed;
		break;
	case 2:
		nRF_Feedback_Packet.encoder3 = real_wheel_speed;
		break;
	case 3:
		nRF_Feedback_Packet.encoder4 = real_wheel_speed;
		break;
	}
#ifdef SEMCONTROLE
	dutycycle=(desired_speed/2.75)*65535;	//73,3333 de angular coloca duty 100%
#else
	dutycycle=out;
#endif
	if(dutycycle>65535) dutycycle=65535;
	if(dutycycle<-65535) dutycycle=-65535;
	SetSpeed(dutycycle);
};
