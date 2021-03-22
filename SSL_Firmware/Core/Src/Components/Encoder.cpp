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
			ENC = htim3;
		}
		case 1:
		{
			ENC = htim2;
		}
		case 2:
		{
			ENC = htim5;
		}
		case 3:
		{
			ENC = htim4;
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
	timCntVal = ENC.Instance->CNT;
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

/*void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim6){
		Encoder encoder(0);
		encoder.ReadEncoder();
	}
}*/

