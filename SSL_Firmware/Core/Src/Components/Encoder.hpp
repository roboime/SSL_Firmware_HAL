/*
 * Encoder.hpp
 *
 *  Created on: Mar 21, 2021
 *      Author: Gabriel Marcellino
 */

#ifndef SRC_COMPONENTS_ENCODER_HPP_
#define SRC_COMPONENTS_ENCODER_HPP_

#include "main.h"
#include "CommunicationUSB.hpp"

class Encoder{
public:
	Encoder(uint8_t encoderId);
	volatile uint32_t ReadEncoder();
private:
	__IO uint32_t* ENC_Val;
	volatile uint32_t timCntVal;
	volatile uint32_t timCntPast;
	CommunicationUSB communicationUSB;
};



#endif /* SRC_COMPONENTS_ENCODER_HPP_ */
