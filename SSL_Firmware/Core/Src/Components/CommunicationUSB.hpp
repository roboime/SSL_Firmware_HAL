/*
 * ComunicationUSB.hpp
 *
 *  Created on: Mar 21, 2021
 *      Author: Gabriel Marcellino
 */

#ifndef SRC_COMPONENTS_COMMUNICATIONUSB_HPP_
#define SRC_COMPONENTS_COMMUNICATIONUSB_HPP_

#include "main.h"

class CommunicationUSB{
public:
	CommunicationUSB(void (**usbRecvCallback)(uint8_t*, uint32_t*));
	void TransmitEncoderReadingRPM(int32_t reading);
	void TransmitFeedbackPacket(void);
	static void ReceiveCallback(uint8_t* Buf, uint32_t* Len);
};



#endif /* SRC_COMPONENTS_COMMUNICATIONUSB_HPP_ */
