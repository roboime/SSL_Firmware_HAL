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

CommunicationUSB::CommunicationUSB()
{

}

void CommunicationUSB::TransmitEncoderReadingRPM(uint32_t reading){
	float readingRPM = (float)3600*(reading)/(float)32; //Explicar no comentário
	sendUSBStruct.motorEnc[0] = (int32_t)(readingRPM);
	CDC_Transmit_FS((uint8_t*)&sendUSBStruct, 24);
}


