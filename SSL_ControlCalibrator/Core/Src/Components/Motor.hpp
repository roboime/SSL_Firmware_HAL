/*
 * Motor.hpp
 *
 *  Created on: Mar 17, 2023
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_MOTOR_HPP_
#define SRC_COMPONENTS_MOTOR_HPP_

#include "main.h"
#include "Encoder.hpp"

class Motor {
public:
	Motor();
	virtual ~Motor();
	virtual void setPower(float power){}
	void setEncoder(Encoder* _encoder);
	float getCurrentRevPerTick();
	void pid(float inputRevPerTick);
	float kp;
	float ki;
	float kd;
private:
	Encoder* encoder;
	float error = 0;
	float ierror = 0;
	float derror = 0;
	float lastError = 0;
	float currentRevPerTick = 0;
};

#endif /* SRC_COMPONENTS_MOTOR_HPP_ */
