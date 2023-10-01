/*
 * RoboIME_SX1280.hpp
 *
 *  Created on: Apr 25, 2023
 *      Author: Frese
 */

#ifndef SRC_COMPONENTS_ROBOIME_SX1280_HPP_
#define SRC_COMPONENTS_ROBOIME_SX1280_HPP_


#include "usbd_cdc_if.h"
#include "string.h"
#include <cstring>
#include "SerialDebug.hpp"
#include "sx1280/sx1280-hal.h"

class SX1280_Send_Packet_t{
public:
	uint8_t id = 0;
	float kickspeedx = 0;
	float kickspeedz = 0;
	float veltangent = 0;
	float velnormal = 0;
	float velangular = 0;
	uint8_t status = 0;
	uint8_t packetId = 0;
};
class SX1280_Feedback_Packet_t{
public:
	uint8_t id = 2;
	float battery = 3;
	float encoder1 = 4;
	float encoder2 = 0;
	float encoder3 = 0;
	float encoder4 = 0;
	uint8_t status = 0;
	uint8_t packetId = 0;
};

class RoboIME_SX1280 {
public:
	int  setRobotId(uint8_t id);
	void GPIOCallback(uint32_t GPIO);
	void setPayload( uint8_t *buffer, uint8_t size, uint8_t offset );
	uint8_t  sendPayload (SX1280_Send_Packet_t *payload, uint8_t payloadSize);
	uint8_t  receivePayload(SX1280_Send_Packet_t *payload);
	void setRX(void);
	int setupDataRadio();
	int setupFeedbackRadio();
	uint8_t receiveFeedback(SX1280_Feedback_Packet_t *payload);
	uint8_t sendFeedback(SX1280_Feedback_Packet_t *payload, uint8_t payloadSize);
	void  OnTxDone( void );
	void  OnRxDone( void );
	void  OnTxTimeout( void );
	void OnRxTimeout( void );
	void  OnRxError( IrqErrorCode_t errorCode );
	static const uint8_t bufferSize = sizeof(SX1280_Send_Packet_t);
private:
	uint8_t payloadTemp[bufferSize];
	uint8_t payloadTempFeedback[bufferSize];
	uint8_t roboId;
	uint8_t oldCount;
	PacketParams_t PacketParams;
	PacketParams_t PacketParams1;
	PacketStatus_t PacketStatus;
	PacketStatus_t PacketStatus1;
	ModulationParams_t ModulationParams;
	ModulationParams_t ModulationParams1;
		//uint8_t syncWord[5] = { 0xDD, 0xA0, 0x96, 0x69, 0xDD };

	uint16_t TxIrqMask = IRQ_TX_DONE | IRQ_RX_TX_TIMEOUT;
	uint16_t RxIrqMask = IRQ_RX_DONE | IRQ_RX_TX_TIMEOUT;


	//Private variables
	uint8_t spiBuf[64];
	uint8_t status;
};






#endif /* SRC_COMPONENTS_ROBOIME_SX1280_HPP_ */
