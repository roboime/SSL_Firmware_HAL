/*
 * Dribble.hpp
 *
 *  Created on: Mar 20, 2022
 *      Author: Vinicius Moraes
 */

#ifndef SRC_COMPONENTS_DRIBBLE_HPP_
#define SRC_COMPONENTS_DRIBBLE_HPP_

#include "main.h"

class Dribble {
public:
	Dribble();
	void SetSpeed(int32_t spd);

private:
	__IO uint32_t* DAH_Pwm;
	uint32_t Pwm_Max;
};

#endif /* SRC_COMPONENTS_DRIBBLE_HPP_ */
