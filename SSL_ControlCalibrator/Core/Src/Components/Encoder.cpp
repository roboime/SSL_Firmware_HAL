/*
 * Encoder.cpp
 *
 *  Created on: Mar 17, 2023
 *      Author: Gabriel
 */

#include "Encoder.hpp"

Encoder::Encoder(__IO uint32_t* cnt, __IO uint32_t* arr, uint32_t countsPerRevolution) :
	cnt(cnt), arr(arr), countsPerRevolution(countsPerRevolution)
{

}

Encoder::~Encoder() {

}

uint32_t Encoder::getCount(){
	lastCount = *cnt;
	return lastCount;
}

int16_t Encoder::getDelta(){
	int16_t delta =  *cnt - lastCount;
	lastCount = *cnt;
	return delta;
}

uint32_t Encoder::getCountsPerRevolution(){
	return countsPerRevolution;
}
