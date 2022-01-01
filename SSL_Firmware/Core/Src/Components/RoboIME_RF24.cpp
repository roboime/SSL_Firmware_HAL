/*
 * RoboIME_RF24.cpp
 *
 *  Created on: Jan 1, 2022
 *      Author: Gabriel
 */

#include "RoboIME_RF24.hpp"

#include <cstring>

RoboIME_RF24::RoboIME_RF24(
		GPIO_TypeDef* CSN_GPIO_PORT, uint16_t CSN_GPIO_PIN,
		GPIO_TypeDef* CE_GPIO_PORT, uint16_t CE_GPIO_PIN,
		GPIO_TypeDef* IRQ_GPIO_PORT, uint16_t IRQ_GPIO_PIN,
		SPI_HandleTypeDef* SPI_HANDLE
		)
: CSN_PORT(CSN_GPIO_PORT), CSN_PIN(CSN_GPIO_PIN),
  CE_PORT(CE_GPIO_PORT), CE_PIN(CE_GPIO_PIN),
  IRQ_PORT(IRQ_GPIO_PORT), IRQ_PIN(IRQ_GPIO_PIN),
  hspi(SPI_HANDLE)
{

}

void RoboIME_RF24::setup(){
	writeRegister(0x00, &REG_CONFIG, 1);
	writeRegister(0x01, &REG_EN_AA, 1);
	writeRegister(0x02, &REG_EN_RXADDR, 1);
	writeRegister(0x03, &REG_SETUP_AW, 1);
	writeRegister(0x04, &REG_SETUP_RETR, 1);
	writeRegister(0x05, &REG_RF_CH, 1);
	writeRegister(0x06, &REG_RF_SETUP, 1);
	writeRegister(0x0A, &REG_RX_ADDR_P0, 4);
	writeRegister(0x10, &REG_TX_ADDR, 4);
	writeRegister(0x1C, &REG_DYNPD, 1);
	writeRegister(0x1D, &REG_FEATURE, 1);
}

inline void RoboIME_RF24::csn(GPIO_PinState state){
	HAL_GPIO_WritePin(CSN_PORT, CSN_PIN, state);
}

inline void RoboIME_RF24::ce(GPIO_PinState state){
	HAL_GPIO_WritePin(CE_PORT, CE_PIN, state);
}

int RoboIME_RF24::writeRegister(uint8_t regAddr, uint8_t* data, uint8_t length){
	if(regAddr > 31){
		return 1;
	}else if(length > 5){
		return 2;
	}
	spiBuf[0] = regAddr;
	memcpy(&spiBuf[1], data, length);
	csn(GPIO_PIN_RESET);
	HAL_SPI_Transmit_IT(hspi, spiBuf, length + 1);
	while (hspi->State == HAL_SPI_STATE_BUSY_TX);
	csn(GPIO_PIN_SET);
	return 0;
}

int RoboIME_RF24::readRegister(uint8_t regAddr, uint8_t* data, uint8_t length){
	if(regAddr > 31){
		return 1;
	}else if(length > 5){
		return 2;
	}
	spiBuf[0] = 0x20 | regAddr;
	csn(GPIO_PIN_RESET);
	HAL_SPI_Transmit_IT(hspi, spiBuf, 1);
	while (hspi->State == HAL_SPI_STATE_BUSY_TX);
	HAL_SPI_Receive_IT(hspi, data, length);
	while (hspi->State == HAL_SPI_STATE_BUSY_RX);
	csn(GPIO_PIN_SET);
	return 0;
}
