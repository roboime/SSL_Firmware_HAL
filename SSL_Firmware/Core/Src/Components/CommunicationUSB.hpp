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
	CommunicationUSB();
	void TransmitEncoderReadingRPM(uint32_t reading);
};



#endif /* SRC_COMPONENTS_COMMUNICATIONUSB_HPP_ */
