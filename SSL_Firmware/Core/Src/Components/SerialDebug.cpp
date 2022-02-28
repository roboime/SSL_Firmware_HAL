/*
 * UARTDebug.cpp
 *
 *  Created on: Feb 28, 2022
 *      Author: Gabriel
 */

#include "SerialDebug.hpp"

SerialDebug::SerialDebug(UART_HandleTypeDef* huartptr)
: huartptr(huartptr)
{

}

void SerialDebug::setLevel(uint32_t level)
{
	debugLevel = level;
}

void SerialDebug::debug(char* data){
	if (debugLevel <= DEBUG_LEVEL_DEBUG){
		int numChars;
		numChars = sprintf((char*)uartBuf, "[%13lu] DBG: %.42s\r\n", HAL_GetTick(), data);
		if(numChars > 0){
			while (huartptr->gState != HAL_UART_STATE_READY);
			HAL_UART_Transmit_DMA(huartptr, uartBuf, (uint16_t)numChars);
		}
	}
}

void SerialDebug::info(char* data){
	if (debugLevel <= DEBUG_LEVEL_INFO){
		int numChars;
		numChars = sprintf((char*)uartBuf, "[%13lu] INF: %.40s\r\n", HAL_GetTick(), data);
		if(numChars > 0){
			while (huartptr->gState != HAL_UART_STATE_READY);
			HAL_UART_Transmit_DMA(huartptr, uartBuf, (uint16_t)numChars);
		}
	}
}

void SerialDebug::warn(char* data){
	if (debugLevel <= DEBUG_LEVEL_WARN){
		int numChars;
		numChars = sprintf((char*)uartBuf, "[%13lu] WRN: %.42s\r\n", HAL_GetTick(), data);
		if(numChars > 0){
			while (huartptr->gState != HAL_UART_STATE_READY);
			HAL_UART_Transmit_DMA(huartptr, uartBuf, (uint16_t)numChars);
		}
	}
}

void SerialDebug::error(char* data){
	if (debugLevel <= DEBUG_LEVEL_ERROR){
		int numChars;
		numChars = sprintf((char*)uartBuf, "[%13lu] ERR: %.42s\r\n", HAL_GetTick(), data);
		if(numChars > 0){
			while (huartptr->gState != HAL_UART_STATE_READY);
			HAL_UART_Transmit_DMA(huartptr, uartBuf, (uint16_t)numChars);
		}
	}
}
