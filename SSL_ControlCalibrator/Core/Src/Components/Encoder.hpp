/*
 * Encoder.hpp
 *
 *  Created on: Mar 17, 2023
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_ENCODER_HPP_
#define SRC_COMPONENTS_ENCODER_HPP_

#include "main.h"

class Encoder {
public:
	Encoder(__IO uint32_t* cnt, __IO uint32_t* arr, uint32_t countsPerRevolution);
	virtual ~Encoder();
	uint32_t getCount();
	int16_t getDelta();
	uint32_t getCountsPerRevolution();
private:
	__IO uint32_t* cnt;
	__IO uint32_t* arr;
	uint32_t lastCount = 0;
	uint32_t countsPerRevolution = 0;
};

#endif /* SRC_COMPONENTS_ENCODER_HPP_ */
