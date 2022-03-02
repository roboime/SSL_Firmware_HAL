/*
 * Start.hpp
 *
 *  Created on: 20 de mar de 2021
 *      Author: Moraes
 */

#ifndef SRC_COMPONENTS_START_HPP_
#define SRC_COMPONENTS_START_HPP_

#include "main.h"
#include "grSim_Commands.pb.h"
#include "Feedback.pb.h"

#ifdef __cplusplus
extern "C" {
#endif

/*struct sendUSBStruct_t{
	uint32_t motorEnc_s;
	int32_t motorEnc[4];
	uint32_t button;
};*/

void Start();
void USBpacketReceivedCallback(void);

#ifdef __cplusplus
}
#endif

#endif /* SRC_COMPONENTS_START_HPP_ */
