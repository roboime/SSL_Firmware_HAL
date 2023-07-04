/*
 * Start.hpp
 *
 *  Created on: 01 de jul de 2023
 *      Author: Gabriel Lima
 */

#ifndef SRC_COMPONENTS_START_HPP_
#define SRC_COMPONENTS_START_HPP_
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void Start();
void usbCallback(uint8_t* Buf, uint32_t *Len);

#ifdef __cplusplus
}
#endif

#endif /* SRC_COMPONENTS_START_HPP_ */
