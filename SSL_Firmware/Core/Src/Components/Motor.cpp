/*
 * Motor.cpp
 *
 *  Created on: 20 de mar de 2021
 *      Author: Moraes
 */

#include "Motor.hpp"

#ifdef DEEPWEB
	float Motor::cp=(1)*65536;
	float Motor::ci=(0.2)*65536;
	float Motor::cd=(0.5)*65536; //0.3
	float Motor::cl=(0.15)*65536; // 0.15
#else
#ifdef CARENTE
	float Motor::cp=0.65149*65536;
	float Motor::ci=6.6822*65536*0.01;
	float Motor::cd=0*65536/0.01;
#else
#ifdef ROBO2023
	float Motor::cp=0.21829*65536;
	float Motor::ci=4.094*65536*0.01;
	float Motor::cd=0*65536/0.01;
#else
	float Motor::cp=(10000.0f/10000)*65536;           //Valores do código antigo
	float Motor::ci=(1500.0f/10000)*65536;
	float Motor::cd=(10000.0f/10000)*65536;
	float Motor::cl=(0.36)*65536;
#endif
#endif
#endif
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

#ifndef BTS7960
void Motor::SetSpeed(int32_t spd){
	Pwm_Max = TIM8->ARR;
	if(speed_anterior*spd<=0){
//		TIM8-> CNT &= 0x0; // restart the timer
		speed_anterior = spd;
		if(spd>0){
			HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PinState(RESET));
				*MBH_Pwm = Pwm_Max; //MBH
				TIM8-> CNT = Pwm_Max; // restart the timer
				TIM1-> CNT = Pwm_Max; // restart the timer
			HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PinState(SET));
				*MAH_Pwm = Pwm_Max - spd; //MAH
		}else if(spd<0){
				HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PinState(RESET));
				*MAH_Pwm = Pwm_Max; //MAH
				TIM8-> CNT = Pwm_Max; // restart the timer
				TIM1-> CNT = Pwm_Max; // restart the timer
				HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PinState(SET));
				*MBH_Pwm = Pwm_Max + spd; //MBH
		}else{
			*MBH_Pwm = Pwm_Max; //MBH
			*MAH_Pwm = Pwm_Max; //MAH
			TIM8-> CNT = Pwm_Max; // restart the timer
			TIM1-> CNT = Pwm_Max; // restart the timer
			HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PinState(SET));
			HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PinState(SET));
			}
	}
	else{
		speed_anterior = spd;
		if(spd>0){
					HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PinState(RESET));
							*MBH_Pwm = Pwm_Max; //MBH
					HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PinState(SET));
							*MAH_Pwm = Pwm_Max - spd; //MAH
			}else if(spd<0){
						HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PinState(RESET));
						*MAH_Pwm = Pwm_Max; //MAH
						HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PinState(SET));
						*MBH_Pwm = Pwm_Max + spd; //MBH
			}else{
				*MBH_Pwm = Pwm_Max; //MBH
				*MAH_Pwm = Pwm_Max; //MAH
				HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PinState(SET));
				HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PinState(SET));
			}
	}

}
#endif

#ifdef BTS7960
void Motor::SetSpeed(int32_t spd){
	if(spd > 0){
		HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PIN_SET);
		*MAH_Pwm = spd;
		*MBH_Pwm = 0;
	}else if(spd < 0){
		HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PIN_SET);
		*MAH_Pwm = 0;
		*MBH_Pwm = -spd;
	}else{
		HAL_GPIO_WritePin(MAL_GPIO_Port, MAL_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(MBL_GPIO_Port, MBL_Pin, GPIO_PIN_RESET);
	}
}
#endif

void Motor::GetSpeed(){
#if defined DEEPWEB || defined ROBO2023
	int32_t distance=M_Enc->ReadEncoder();
#else
	int32_t distance=-M_Enc->ReadEncoder();
#endif

	float speed=(float)distance*CONVERSION; //converte da unidade da roda para m/s (vel do centro da roda)
	                                     //talvez seja melhor converter de m/s pra unidade da roda
	real_wheel_speed=(float)speed;
};

void Motor::ControlSpeed(float desired_speed){
	//real_wheel_speed=0;
	last_real_wheel_speed = real_wheel_speed;
	GetSpeed();
	error = desired_speed-real_wheel_speed;
	ierror += error;
	if(ci*ierror > 65536){		// Anti-windup (verificar possibilidades)
		ierror = 65536/ci;
	}else if(ci*ierror < -65536){
		ierror = -65536/ci;
	}
	derror=-(real_wheel_speed - last_real_wheel_speed);
	float out = cp*error + ci * ierror + cd * derror;
	/*switch (motorId_attrib){
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
	}*/
#if defined DEEPWEB
#ifdef SEMCONTROLE
	dutycycle=-(desired_speed/2.75)*65535;	//73,3333 de angular coloca duty 100%//2.75
#else
	dutycycle=-out; // -out
#endif
#else
#ifdef SEMCONTROLE
	dutycycle=(desired_speed/2.75)*65535;	//73,3333 de angular coloca duty 100%//2.75
#else
	dutycycle=out;
#endif
#endif

	if(dutycycle>65535) dutycycle=65535;
	if(dutycycle<-65535) dutycycle=-65535;
	SetSpeed(dutycycle);
};
