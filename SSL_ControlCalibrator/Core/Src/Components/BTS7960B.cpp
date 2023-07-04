/*
 * BTS7960B.cpp
 *
 *  Created on: Dec 29, 2021
 *      Author: Gabriel
 */

#include "BTS7960B.hpp"

BTS7960B::BTS7960B(__IO uint32_t* ina_ccr, __IO uint32_t* inb_ccr, __IO uint32_t* ina_arr, __IO uint32_t* inb_arr, GPIO_TypeDef* inha_gpio_port, uint16_t inha_gpio_pin, GPIO_TypeDef* inhb_gpio_port, uint16_t inhb_gpio_pin)
 : ina(ina_ccr), inb(inb_ccr), ina_max(ina_arr), inb_max(inb_arr), inha_port(inha_gpio_port), inha_pin(inha_gpio_pin), inhb_port(inhb_gpio_port), inhb_pin(inhb_gpio_pin){

}

void BTS7960B::setPower(float power){
	if(power >= 0 && power <= 1){
		*ina = power*(*ina_max);
		*inb = 0;
	}else if(power < 0 && power >= -1){
		*ina = 0;
		*inb = -power*(*inb_max);
	}
}

void BTS7960B::setEnabled(bool enabled){
	if(enabled){
		HAL_GPIO_WritePin(inha_port, inha_pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(inhb_port, inhb_pin, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(inha_port, inha_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(inhb_port, inhb_pin, GPIO_PIN_RESET);
	}
}
