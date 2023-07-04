/*
 * BTS7960B.hpp
 *
 *  Created on: Dec 29, 2021
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_BTS7960B_HPP_
#define SRC_COMPONENTS_BTS7960B_HPP_

#include "main.h"
#include "Motor.hpp"

class BTS7960B : public Motor{
public:
	BTS7960B(__IO uint32_t* ina_ccr, __IO uint32_t* inb_ccr, __IO uint32_t* ina_arr, __IO uint32_t* inb_arr, GPIO_TypeDef* inha_gpio_port, uint16_t inha_gpio_pin, GPIO_TypeDef* inhb_gpio_port, uint16_t inhb_gpio_pin);
	void setPower(float power);
	void setEnabled(bool enabled);
private:
	__IO uint32_t* ina;
	__IO uint32_t* inb;
	__IO uint32_t* ina_max;
	__IO uint32_t* inb_max;
	GPIO_TypeDef* inha_port;
	uint16_t inha_pin;
	GPIO_TypeDef* inhb_port;
	uint16_t inhb_pin;
};







#endif /* SRC_COMPONENTS_BTS7960B_HPP_ */
