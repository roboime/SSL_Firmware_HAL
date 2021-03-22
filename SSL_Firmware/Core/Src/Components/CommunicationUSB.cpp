/*
 * ComunicationUSB.cpp
 *
 *  Created on: Mar 21, 2021
 *      Author: Gabriel Marcellino
 */

#include "main.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "CommunicationUSB.hpp"

CommunicationUSB::CommunicationUSB()
{

}

void CommunicationUSB::TransmitEncoderReadingRPM(uint32_t reading){
	float readingRPM = (float)3600*(reading)/(float)32; //Explicar no comentário
	uint8_t package[14] = "Hello";
	//sprintf((char*)package, "%f\n\r", readingRPM);
	while(CDC_Transmit_FS(package, 14)==USBD_BUSY);
	readingRPM = (float)3600*(reading)/(float)32;
}


