/*
 * Robo.cpp
 *
 *  Created on: 20 de mar de 2022
 *      Author: Vinicius Moraes
 */

#include "Robo.hpp"

Robo::Robo(uint8_t roboId) {
	for(int i=0; i<4; ++i){
		R_Motors[i]= new Motor(i);
	}
	R_Kick = new Kick();

}


