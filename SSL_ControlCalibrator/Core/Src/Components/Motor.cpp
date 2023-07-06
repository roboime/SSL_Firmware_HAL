/*
 * Motor.cpp
 *
 *  Created on: Mar 17, 2023
 *      Author: Gabriel
 */

#include "Motor.hpp"
#include <cstdio>
#include "Definitions.hpp"

Motor::Motor() {

}

Motor::~Motor() {

}

void Motor::setEncoder(Encoder* _encoder){
	encoder = _encoder;
}

float Motor::getCurrentRevPerTick(){
#ifdef CONTROL_DISABLED
#if defined DEEPWEB || defined ROBO2023
	currentRevPerTick = -(float)encoder->getDelta()/encoder->getCountsPerRevolution();
#endif
#ifdef CARENTE
	currentRevPerTick = (float)encoder->getDelta()/encoder->getCountsPerRevolution();
#endif
#endif
	return currentRevPerTick;
}

void Motor::pid(float inputRevPerTick){
#if defined DEEPWEB || defined ROBO2023
	currentRevPerTick = -(float)encoder->getDelta()/encoder->getCountsPerRevolution();
#endif
#ifdef CARENTE
	currentRevPerTick = (float)encoder->getDelta()/encoder->getCountsPerRevolution();
#endif
	lastError = error;
	error = inputRevPerTick - currentRevPerTick;
	derror = error - lastError;
	ierror += error;
	if(ki*ierror > 1){		// Anti-windup (verificar possibilidades)
		ierror = 1/ki;
	}else if(ki*ierror < -1){
		ierror = -1/ki;
	}
	float pid = kp*error + ki*ierror + kd*derror;
	if(pid > 1){		// Clamp
		pid = 1;
	}else if(pid < -1){
		pid = -1;
	}
	setPower(pid);
}
