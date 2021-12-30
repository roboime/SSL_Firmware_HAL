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
#include "grSim_Commands.pb.h"
#include "Feedback.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"

//extern sendUSBStruct_t sendUSBStruct;
//extern struct recvUSBStruct_t *recvUSBStruct;
//char package[24];
extern grSim_Robot_Command receivedPacket;
extern Feedback sendPacket;
extern uint8_t sendBuffer[64];

/**
 * @param _usbRecvCallback pointer to global variable which is a function pointer to be called inside usbd_cdc_if.h
 */
CommunicationUSB::CommunicationUSB(void (**_usbRecvCallback)(uint8_t*, uint32_t*))
{
	*_usbRecvCallback = &CommunicationUSB::ReceiveCallback;
}

void CommunicationUSB::ReceiveCallback(uint8_t* Buf, uint32_t* Len){
	HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
	pb_istream_t stream = pb_istream_from_buffer(Buf, *Len);
	pb_decode(&stream, grSim_Robot_Command_fields, &receivedPacket);
	packetReceivedCallback();
}

void CommunicationUSB::TransmitFeedbackPacket(void){
	pb_ostream_t stream = pb_ostream_from_buffer(sendBuffer, 64);
	pb_encode(&stream, Feedback_fields, &sendPacket);
	CDC_Transmit_FS(sendBuffer, stream.bytes_written);
}

void CommunicationUSB::TransmitEncoderReadingRPM(int32_t reading){
	float readingRPM = (float)(reading)/(float)1; //Explicar no comentário
	//sendUSBStruct.motorEnc[0] = (int32_t)(readingRPM);
	//CDC_Transmit_FS((uint8_t*)&sendUSBStruct, 24);
	//sprintf(package, "%20.2f\n\r", readingRPM);
	//CDC_Transmit_FS((uint8_t*)package, 24);

	sendPacket.id = receivedPacket.id;
	sendPacket.status = 1;
	sendPacket.battery = 20.0;
	sendPacket.encoder1 = readingRPM;
	sendPacket.encoder2 = receivedPacket.velangular;
	sendPacket.encoder3 = 0;
	sendPacket.encoder4 = 0;
}


