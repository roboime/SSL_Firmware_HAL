/*
 * RoboIME_RF24.hpp
 *
 *  Created on: Jan 1, 2022
 *      Author: Gabriel
 */

#ifndef SRC_COMPONENTS_ROBOIME_RF24_HPP_
#define SRC_COMPONENTS_ROBOIME_RF24_HPP_

#include "main.h"

class RoboIME_RF24 {
public:
	RoboIME_RF24(GPIO_TypeDef* CSN_GPIO_PORT, uint16_t CSN_GPIO_PIN, GPIO_TypeDef* CE_GPIO_PORT, uint16_t CE_GPIO_PIN, GPIO_TypeDef* IRQ_GPIO_PORT, uint16_t IRQ_GPIO_PIN, SPI_HandleTypeDef* SPI_HANDLE);
	void setup();

	//Setup parameters = default
	uint8_t REG_CONFIG = 0b00001000;		//Default config
	uint8_t REG_EN_AA = 0b00000001;			//Only pipe 0 auto-acknowledge
	uint8_t REG_EN_RXADDR = 0b00000001;		//Only pipe 0 enabled
	uint8_t REG_SETUP_AW = 0b00000010;		//4-byte address
	uint8_t REG_SETUP_RETR = 0b00010001;	//500us, 1 retransmit
	uint8_t REG_RF_CH = 8;					//2400 + 8 = 2408MHz
	uint8_t REG_RF_SETUP = 0b00001110;		//2mbps, 0dBm
	uint8_t REG_RX_ADDR_P0[4] =
		{0xE7, 0xE7, 0x00, 0x00};			//This robot id
	uint8_t REG_TX_ADDR[4] =
		{0xE7, 0xE7, 0x00, 0x00};		//Will send to this id
	uint8_t REG_DYNPD = 0b00000001;			//Dynamic payload size enabled
	uint8_t REG_FEATURE = 0b00000111;		//Features

private:
	//Ports and pins
	GPIO_TypeDef* CSN_PORT;
	uint16_t CSN_PIN;
	GPIO_TypeDef* CE_PORT;
	uint16_t CE_PIN;
	GPIO_TypeDef* IRQ_PORT;
	uint16_t IRQ_PIN;
	SPI_HandleTypeDef* hspi;

	//Private variables
	uint8_t spiBuf[64];

	//Methods
	void csn(GPIO_PinState state);
	void ce(GPIO_PinState state);
	int writeRegister(uint8_t regAddr, uint8_t* data, uint8_t length);
	int readRegister(uint8_t regAddr, uint8_t* data, uint8_t length);
};

#endif /* SRC_COMPONENTS_ROBOIME_RF24_HPP_ */
