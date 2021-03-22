/*
 * Encoder.cpp
 *
 *  Created on: Mar 21, 2021
 *      Author: Gabriel Marcellino
 */

# include "Encoder.hpp"
# include "CommunicationUSB.hpp"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim6;

Encoder::Encoder (uint8_t encoderId){
	switch(encoderId)
	{
		case 0:
		{
			ENC_Val = &(TIM3->CNT);
			break;
		}
		case 1:
		{
			ENC_Val = &(TIM2->CNT);
			break;
		}
		case 2:
		{
			ENC_Val = &(TIM5->CNT);
			break;
		}
		case 3:
		{
			ENC_Val = &(TIM4->CNT);
			break;
		}
		default:
			break;
	}
	communicationUSB = CommunicationUSB();
	timCntVal = 0;
	timCntPast = 0;
}

volatile uint32_t Encoder::ReadEncoder(){
	timCntPast = timCntVal;
	timCntVal = *ENC_Val;
	if (timCntVal >= timCntPast)
	{
		communicationUSB.TransmitEncoderReadingRPM(timCntVal - timCntPast);
		//return timCntVal - timCntPast;
	}
	else
	{
		communicationUSB.TransmitEncoderReadingRPM(timCntVal - (65535 - timCntPast));
		//return timCntVal - (65535 - timCntPast);
	}
	return 0;
}

