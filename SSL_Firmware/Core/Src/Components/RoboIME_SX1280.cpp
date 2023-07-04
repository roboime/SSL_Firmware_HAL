/*
 * RoboIME_SX1280.cpp
 *
 *  Created on: April 25, 2023
 *      Author: Frese
 */


#include "RoboIME_SX1280.hpp"
#include "Defines.hpp"

#define RX_TIMEOUT_VALUE 0
#define TX_TIMEOUT_VALUE  100
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim6;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi1;

extern SerialDebug debug;

typedef enum
{
    APP_LOWPOWER,
    APP_RX,
    APP_RX_TIMEOUT,
    APP_RX_ERROR,
    APP_TX,
    APP_TX_TIMEOUT,
}AppStates_t;

AppStates_t AppState = APP_LOWPOWER;

/*!
 * \brief Function to be executed on Radio Tx Done event
 */
void OnTxDone( void );

/*!
 * \brief Function to be executed on Radio Rx Done event
 */
void OnRxDone( void );

/*!
 * \brief Function executed on Radio Tx Timeout event
 */
void OnTxTimeout( void );

/*!
 * \brief Function executed on Radio Rx Timeout event
 */
void OnRxTimeout( void );

/*!
 * \brief Function executed on Radio Rx Error event
 */
void OnRxError( IrqErrorCode_t );

RadioCallbacks_t callbacks =
{
    &OnTxDone,        // txDone
    &OnRxDone,       // rxDone
    NULL,             	// syncWordDone
    NULL,          	   	// headerDone
	&OnTxTimeout,     // txTimeout
	&OnRxTimeout,     // rxTimeout
	&OnRxError,       		// rxError
    NULL,             	// rangingDone
    NULL,             	// cadDone
};

SX1280Hal radio0(&hspi1, SX1280_CSn_GPIO_Port, SX1280_CSn_Pin, SX1280_BUSY_GPIO_Port, SX1280_BUSY_Pin, SX1280_RST_GPIO_Port, SX1280_RST_Pin, &callbacks);
// Feedback Radio
//SX1280Hal radio1(&hspi2, SX_FB_NSS_GPIO_Port, SX_FB_NSS_Pin, SX_FB_BUSY_GPIO_Port, SX_FB_BUS0_Pin, SX_FB_RST_GPIO_Port, SX_FB_RST_Pin, &callbacks);

//Public methods
void RoboIME_SX1280::GPIOCallback(void){
	radio0.HalInterruptCallback();
	HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
}
int RoboIME_SX1280::setupDataRadio(){
	/* Modulation Params*/

	   ModulationParams.Params.Flrc.BitrateBandwidth  = ( RadioFlrcBitrates_t )       FLRC_BR_1_300_BW_1_2;
	   ModulationParams.Params.Flrc.CodingRate        = ( RadioFlrcCodingRates_t )   FLRC_CR_1_0;
	   ModulationParams.Params.Flrc.ModulationShaping = ( RadioModShapings_t )        RADIO_MOD_SHAPING_BT_1_0;

	   PacketParams.Params.Flrc.PreambleLength        = ( RadioPreambleLengths_t )     PREAMBLE_LENGTH_32_BITS;
	   PacketParams.Params.Flrc.SyncWordLength        = ( RadioFlrcSyncWordLengths_t )FLRC_SYNCWORD_LENGTH_4_BYTE;
	   PacketParams.Params.Flrc.SyncWordMatch         = ( RadioSyncWordRxMatchs_t )   RADIO_RX_MATCH_SYNCWORD_1;
	   PacketParams.Params.Flrc.HeaderType            = ( RadioPacketLengthModes_t )  RADIO_PACKET_VARIABLE_LENGTH;
	   PacketParams.Params.Flrc.PayloadLength         =                               sizeof(SX1280_Send_Packet_t);
	   PacketParams.Params.Flrc.CrcLength             = ( RadioCrcTypes_t )           RADIO_CRC_3_BYTES;
	   PacketParams.Params.Flrc.Whitening             = ( RadioWhiteningModes_t )	  RADIO_WHITENING_OFF;

	   ModulationParams.PacketType = PACKET_TYPE_FLRC;
	   PacketParams.PacketType     = PACKET_TYPE_FLRC;


   	HAL_Delay(500);
   	radio0.Init();
   	radio0.SetRegulatorMode(USE_DCDC);
   	radio0.SetStandby( STDBY_XOSC);
   	radio0.SetLNAGainSetting(LNA_HIGH_SENSITIVITY_MODE);
   	radio0.SetPacketType( ModulationParams.PacketType );
   	radio0.SetModulationParams( &ModulationParams );
   	radio0.SetPacketParams( &PacketParams );
#ifdef INTEL
   	radio0.SetRfFrequency( 2462000000UL );
#else
   	radio0.SetRfFrequency( 2458000000UL );
#endif
   	radio0.SetBufferBaseAddresses( 0x00, 0x00 );
   	// only used in GFSK, FLRC (4 bytes max) and BLE mode
   	//radio0.SetSyncWord( 1, syncWord ); // NAO USEI
   	// only used in GFSK, FLRC
   	//uint8_t crcSeedLocal[2] = {0x45, 0x67}; // NAO USEI
   	//radio0.SetCrcSeed( crcSeedLocal ); // NAO USEI
   	//radio0.SetCrcPolynomial( 0x0123 ); // NAOP USEI
   	radio0.SetTxParams( 0, RADIO_RAMP_20_US );
   	uint16_t RxIrqMask = IRQ_RX_DONE | IRQ_RX_TX_TIMEOUT;
   	radio0.SetDioIrqParams( RxIrqMask, RxIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
   	return 0;
}
int RoboIME_SX1280::setupFeedbackRadio(){
	/* Modulation Params*/
	   ModulationParams.Params.Flrc.BitrateBandwidth  = ( RadioFlrcBitrates_t )       FLRC_BR_0_260_BW_0_3;
	   ModulationParams.Params.Flrc.CodingRate        = ( RadioFlrcCodingRates_t )   FLRC_CR_1_2;
	   ModulationParams.Params.Flrc.ModulationShaping = ( RadioModShapings_t )        RADIO_MOD_SHAPING_BT_1_0;

	   PacketParams.Params.Flrc.PreambleLength        = ( RadioPreambleLengths_t )     PREAMBLE_LENGTH_32_BITS;
	   PacketParams.Params.Flrc.SyncWordLength        = ( RadioFlrcSyncWordLengths_t )FLRC_SYNCWORD_LENGTH_4_BYTE;
	   PacketParams.Params.Flrc.SyncWordMatch         = ( RadioSyncWordRxMatchs_t )   RADIO_RX_MATCH_SYNCWORD_1;
	   PacketParams.Params.Flrc.HeaderType            = ( RadioPacketLengthModes_t )  RADIO_PACKET_VARIABLE_LENGTH;
	   PacketParams.Params.Flrc.PayloadLength         =                               bufferSize-1;
	   PacketParams.Params.Flrc.CrcLength             = ( RadioCrcTypes_t )           RADIO_CRC_3_BYTES;
	   PacketParams.Params.Flrc.Whitening             = ( RadioWhiteningModes_t )	  RADIO_WHITENING_OFF;

	   ModulationParams.PacketType = PACKET_TYPE_FLRC;
	   PacketParams.PacketType     = PACKET_TYPE_FLRC;

   	HAL_Delay(500);
   	radio0.Init();
   	radio0.SetRegulatorMode(USE_LDO);
   	radio0.SetStandby( STDBY_RC);
   	radio0.SetLNAGainSetting(LNA_HIGH_SENSITIVITY_MODE);
   	radio0.SetPacketType( ModulationParams.PacketType );
   	radio0.SetModulationParams( &ModulationParams );
   	radio0.SetPacketParams( &PacketParams );
   	radio0.SetRfFrequency( 2350000000UL );
   	radio0.SetBufferBaseAddresses( 0x00, 0x00 );
   	// only used in GFSK, FLRC (4 bytes max) and BLE mode
   	//radio0.SetSyncWord( 1, syncWord ); // NAO USEI
   	// only used in GFSK, FLRC
   	//uint8_t crcSeedLocal[2] = {0x45, 0x67}; // NAO USEI
   	//radio0.SetCrcSeed( crcSeedLocal ); // NAO USEI
   	//radio0.SetCrcPolynomial( 0x0123 ); // NAOP USEI
   	radio0.SetTxParams( 0, RADIO_RAMP_20_US );
   	uint16_t RxIrqMask = IRQ_RX_DONE | IRQ_RX_TX_TIMEOUT;
   	radio0.SetDioIrqParams( RxIrqMask, RxIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
   	return 0;
}
int count =1;
uint8_t RoboIME_SX1280::sendPayload(SX1280_Send_Packet_t *payload, uint8_t payloadSize){
	if(count == 1)
	{
		count ++;
		radio0.SetDioIrqParams( TxIrqMask, TxIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
		HAL_Delay(1);
	}
	radio0.SendPayload((uint8_t*)payload, payloadSize,( TickTime_t ){ RADIO_TICK_SIZE_1000_US,TX_TIMEOUT_VALUE } );
	HAL_Delay(5);
	while(1)
		{
			if(AppState == APP_TX)
			{
				return 1;
			}
			else if (AppState == APP_TX_TIMEOUT)
			{
				return 0;
			}
		}
	return 1;

}

//char dbgMessage[64];

uint8_t RoboIME_SX1280::receivePayload(SX1280_Send_Packet_t *payload){
	uint8_t actualBufferSize = 0;
	AppState = APP_LOWPOWER;
	radio0.SetRx( ( TickTime_t ) { RADIO_TICK_SIZE_1000_US, 0x0000 } );
	oldCount = payloadTemp[25];
	while(1){
		if(AppState == APP_RX)
		{
			radio0.GetPayload(payloadTemp, &actualBufferSize, sizeof(SX1280_Send_Packet_t));
			//sprintf(dbgMessage, "id = %d", payloadTemp[0]);
			//debug.debug(dbgMessage);
			if (payloadTemp[25] != oldCount && payloadTemp[0] == roboId)
			{
				memcpy(payload, payloadTemp, sizeof(SX1280_Send_Packet_t));
				HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
				return actualBufferSize;
			}
			else
			{
				 HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
				 return 0;
			}
		}
		else if (AppState == APP_RX_TIMEOUT)
		{
			return 0;
		}
	}
}
void RoboIME_SX1280::setPayload( uint8_t *buffer, uint8_t size, uint8_t offset ){
	radio0.SetPayload( buffer, size, offset );
}
int RoboIME_SX1280::setRobotId(uint8_t id){
	roboId = id;
	return 0;
}

void RoboIME_SX1280::setRX(void)
{
	radio0.SetRx( ( TickTime_t ) { RADIO_TICK_SIZE_1000_US, RX_TIMEOUT_VALUE } );
}

uint8_t RoboIME_SX1280::receiveFeedback(uint8_t* payload)
{
	uint8_t actualBufferSize;
	radio0.SetDioIrqParams( RxIrqMask, RxIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
	 radio0.SetRx( ( TickTime_t ) { RADIO_TICK_SIZE_1000_US, RX_TIMEOUT_VALUE} );
	 while(1)
	 	{
	 		if(AppState == APP_RX)
	 		{
	 			radio0.GetPayload(payloadTemp, &actualBufferSize, bufferSize);
				memcpy(payload, payloadTemp, bufferSize);
				HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);
				return actualBufferSize;

	 		}
	 		else if (AppState == APP_RX_TIMEOUT)
	 		{
             HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
             return 0;
	 		}
	 		else if (AppState == APP_RX_ERROR)
			{
			 HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
			 return 0;
			}
	 	}

}
uint8_t RoboIME_SX1280::sendFeedback(void)
{
	uint8_t buffFeedback[128];
	buffFeedback[0] = 7;
	radio0.SetDioIrqParams( TxIrqMask, TxIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
	radio0.SendPayload( buffFeedback, 128,( TickTime_t ){ RADIO_TICK_SIZE_1000_US, TX_TIMEOUT_VALUE} );
	while(1)
	{
		if(AppState == APP_TX)
		{
			HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);
			return 1;
		}
		else if (AppState == APP_TX_TIMEOUT)
		{
			return 0;
		}
	}
}
void OnTxDone( void )
{
    AppState = APP_TX;
}

void  OnRxDone( void )
{
    AppState = APP_RX;
}

void OnTxTimeout( void )
{
    AppState = APP_TX_TIMEOUT;
}

void OnRxTimeout( void )
{
    AppState = APP_RX_TIMEOUT;
}

void  OnRxError( IrqErrorCode_t errorCode )
{
    AppState = APP_RX_ERROR;

}
