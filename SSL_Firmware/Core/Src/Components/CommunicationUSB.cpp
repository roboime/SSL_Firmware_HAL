/*
 * ComunicationUSB.cpp
 *
 *  Created on: Mar 21, 2021
 *      Author: Gabriel Marcellino
 */

#include "main.h"
#include "Start.hpp"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "CommunicationUSB.hpp"

extern sendUSBStruct_t sendUSBStruct;
extern struct recvUSBStruct_t *recvUSBStruct;
char package[24];

/**
 * @param _usbRecvCallback pointer to global variable which is a function pointer to be called inside usbd_cdc_if.h
 */
CommunicationUSB::CommunicationUSB(void (**_usbRecvCallback)(uint8_t*, uint32_t*))
{
	*_usbRecvCallback = &CommunicationUSB::ReceiveCallback;
}

void CommunicationUSB::ReceiveCallback(uint8_t* Buf, uint32_t* Len){
	HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
}

void CommunicationUSB::TransmitEncoderReadingRPM(int32_t reading){
	float readingRPM = (float)(reading)/(float)1; //Explicar no comentário
	sendUSBStruct.motorEnc[0] = (int32_t)(readingRPM);
	//CDC_Transmit_FS((uint8_t*)&sendUSBStruct, 24);


	sprintf(package, "%20.2f\n\r", readingRPM);
	CDC_Transmit_FS((uint8_t*)package, 24);
}


