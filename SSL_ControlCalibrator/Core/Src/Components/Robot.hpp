/*
 * Robot.hpp
 *
 *  Created on: Mar 17, 2023
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_ROBOT_HPP_
#define SRC_COMPONENTS_ROBOT_HPP_

#include "main.h"
#include "BTS7960B.hpp"
#include "Encoder.hpp"
#include "Definitions.hpp"

class Robot {
public:
	Robot();
	virtual ~Robot();
	void usbCallback(uint8_t* Buf, uint32_t *Len);
	void controlCallback();
	void init();
private:
#ifdef CARENTE
	const float reductionRatio = -4;
	const float wheelRadius = 0.019;	//m
#endif
#ifdef DEEPWEB
	const float reductionRatio = 8;
	const float wheelRadius = 0.029;	//m
#endif
#ifdef ROBO2023
	const float reductionRatio = -3.6;
	const float wheelRadius = 0.026;	//m
#endif
	const float ticksPerSecond = 100;
	uint8_t rxBuffer[1500] = "0.000000,0.000000";
	uint8_t txBuffer[1500];
#if defined DEEPWEB || defined ROBO2023
	Encoder encoder0 = Encoder(&(TIM3->CNT), &(TIM3->ARR), 64);
#endif
#ifdef CARENTE
	Encoder encoder0 = Encoder(&(TIM3->CNT), &(TIM3->ARR), 52);
#endif
	BTS7960B motor0 = BTS7960B(&(TIM8->CCR4), &(TIM8->CCR2), &(TIM8->ARR), &(TIM8->ARR),
			M0_MAL_GPIO_Port, M0_MAL_Pin, M0_MBL_GPIO_Port, M0_MBL_Pin);
};

#endif /* SRC_COMPONENTS_ROBOT_HPP_ */
