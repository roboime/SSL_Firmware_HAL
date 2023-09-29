/*
 *  RoboIME_SX1280.cpp
 *
 *  Created on: April 25, 2023 (lib)
 *  Changed on: September 2, 2023 (dual antenna)
 *
 *  Author: Frese
 */


#include "RoboIME_SX1280.hpp"
#include "Defines.hpp"

#define RX_TIMEOUT_VALUE 100
#define TX_TIMEOUT_VALUE  100

extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim6;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi1;
extern SerialDebug debug;
extern bool transmitter;

typedef enum
{
    APP_LOWPOWER,
    APP_RX,
    APP_RX_TIMEOUT,
    APP_RX_ERROR,
    APP_TX,
    APP_TX_TIMEOUT,
}AppStates_t;

AppStates_t AppState = APP_LOWPOWER;  // Appstate (radio 0) master sender or slave receiver/sender
AppStates_t AppState2 = APP_LOWPOWER; // Appstate2 (radio 1) master receiver

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
    &OnTxDone,          // txDone
    &OnRxDone,          // rxDone
    NULL,             	// syncWordDone
    NULL,          	   	// headerDone
	&OnTxTimeout,       // txTimeout
	&OnRxTimeout,       // rxTimeout
	&OnRxError,       	// rxError
    NULL,             	// rangingDone
    NULL,             	// cadDone
};
RadioCallbacks_t callbacksFeedback =
{
    &OnTxDone,          // txDone
    &OnRxDone,          // rxDone
    NULL,             	// syncWordDone
    NULL,          	   	// headerDone
	&OnTxTimeout,       // txTimeout
	&OnRxTimeout,       // rxTimeout
	&OnRxError,       	// rxError
    NULL,             	// rangingDone
    NULL,             	// cadDone
};

SX1280Hal radio0(&hspi1, SX1280_CSn_GPIO_Port, SX1280_CSn_Pin, SX1280_BUSY_GPIO_Port, SX1280_BUSY_Pin, SX1280_RST_GPIO_Port, SX1280_RST_Pin, &callbacks);
#ifdef ANTENNA
SX1280Hal radio1(&hspi2, SX1280_1_CSn_GPIO_Port, SX1280_1_CSn_Pin, SX1280_1_BUSY_GPIO_Port, SX1280_1_BUSY_Pin, SX1280_1_RST_GPIO_Port, SX1280_1_RST_Pin, &callbacksFeedback);
#endif


//Public methods

/* ---- CALLBACK IRQ RADIO -------*/
void RoboIME_SX1280::GPIOCallback(uint32_t GPIO){
	if(GPIO >> 5  == 1)
	{
		radio0.HalInterruptCallback();
	}
#ifdef ANTENNA
	else if (GPIO >> 12 == 1){ //era 12

		radio1.HalInterruptCallback();
	}
#endif


}
uint16_t TxIrqMask = IRQ_TX_DONE | IRQ_RX_TX_TIMEOUT;
uint16_t RxIrqMask = IRQ_RX_DONE | IRQ_RX_TX_TIMEOUT;


int RoboIME_SX1280::setupDataRadio(){
	/* Modulation Params*/
	   ModulationParams.PacketType                    = PACKET_TYPE_FLRC;
	   ModulationParams.Params.Flrc.BitrateBandwidth  = ( RadioFlrcBitrates_t )       FLRC_BR_1_300_BW_1_2;
	   ModulationParams.Params.Flrc.CodingRate        = ( RadioFlrcCodingRates_t )   FLRC_CR_1_0;
	   ModulationParams.Params.Flrc.ModulationShaping = ( RadioModShapings_t )        RADIO_MOD_SHAPING_BT_1_0;
	   PacketParams.PacketType                        = PACKET_TYPE_FLRC;
	   PacketParams.Params.Flrc.PreambleLength        = ( RadioPreambleLengths_t )     PREAMBLE_LENGTH_32_BITS;
	   PacketParams.Params.Flrc.SyncWordLength        = ( RadioFlrcSyncWordLengths_t )FLRC_SYNCWORD_LENGTH_4_BYTE;
	   PacketParams.Params.Flrc.SyncWordMatch         = ( RadioSyncWordRxMatchs_t )   RADIO_RX_MATCH_SYNCWORD_1;
	   PacketParams.Params.Flrc.HeaderType            = ( RadioPacketLengthModes_t )  RADIO_PACKET_VARIABLE_LENGTH;
	   PacketParams.Params.Flrc.PayloadLength         =  sizeof(SX1280_Send_Packet_t);
	   PacketParams.Params.Flrc.CrcLength             = ( RadioCrcTypes_t )           RADIO_CRC_3_BYTES;
	   PacketParams.Params.Flrc.Whitening             = ( RadioWhiteningModes_t )	  RADIO_WHITENING_OFF;


   	HAL_Delay(500);
   	radio0.Init();
   	radio0.SetRegulatorMode(USE_DCDC);
   	radio0.SetStandby( STDBY_RC);
   //	radio0.SetStandby( STDBY_XOSC); // teste

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
	radio0.SetTxParams( 0, RADIO_RAMP_20_US );


   	return 0;
}
#ifdef ANTENNA
int RoboIME_SX1280::setupFeedbackRadio(){
	/* Modulation Params*/
		   ModulationParams1.PacketType                    = PACKET_TYPE_FLRC;
		   ModulationParams1.Params.Flrc.BitrateBandwidth  = ( RadioFlrcBitrates_t )       FLRC_BR_1_300_BW_1_2;
		   ModulationParams1.Params.Flrc.CodingRate        = ( RadioFlrcCodingRates_t )   FLRC_CR_1_0;
		   ModulationParams1.Params.Flrc.ModulationShaping = ( RadioModShapings_t )        RADIO_MOD_SHAPING_BT_1_0;
		   PacketParams1.PacketType                        = PACKET_TYPE_FLRC;
		   PacketParams1.Params.Flrc.PreambleLength        = ( RadioPreambleLengths_t )     PREAMBLE_LENGTH_32_BITS;
		   PacketParams1.Params.Flrc.SyncWordLength        = ( RadioFlrcSyncWordLengths_t )FLRC_SYNCWORD_LENGTH_4_BYTE;
		   PacketParams1.Params.Flrc.SyncWordMatch         = ( RadioSyncWordRxMatchs_t )   RADIO_RX_MATCH_SYNCWORD_1;
		   PacketParams1.Params.Flrc.HeaderType            = ( RadioPacketLengthModes_t )  RADIO_PACKET_VARIABLE_LENGTH;
		   PacketParams1.Params.Flrc.PayloadLength         =  sizeof(SX1280_Send_Packet_t);
		   PacketParams1.Params.Flrc.CrcLength             = ( RadioCrcTypes_t )           RADIO_CRC_3_BYTES;
		   PacketParams1.Params.Flrc.Whitening             = ( RadioWhiteningModes_t )	  RADIO_WHITENING_OFF;

   	HAL_Delay(500);
   	radio1.Init();
   	radio1.SetRegulatorMode(USE_DCDC);
   	radio1.SetStandby( STDBY_RC);
	radio1.SetLNAGainSetting(LNA_HIGH_SENSITIVITY_MODE);
 	//radio1.SetStandby( STDBY_XOSC); // teste

	radio1.SetPacketType( ModulationParams1.PacketType );
   	radio1.SetModulationParams( &ModulationParams1 );
   	radio1.SetPacketParams( &PacketParams1 );

#ifdef INTEL
   	radio1.SetRfFrequency( 2462000000UL );
#else
   	radio1.SetRfFrequency( 2458000000UL );
#endif

	radio1.SetBufferBaseAddresses( 0x00, 0x00 );
	radio1.SetTxParams( 0, RADIO_RAMP_20_US );


   	return 0;
}
#endif
/* ----------  MASTER FUNCTIONS ------------ */
int count =1;
uint8_t RoboIME_SX1280::sendPayload(SX1280_Send_Packet_t *payload, uint8_t payloadSize){

	if (count == 1)
	{
	radio0.SetDioIrqParams( TxIrqMask, TxIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
	HAL_Delay(5);
	count ++;
	}
	radio0.SendPayload((uint8_t*)payload, payloadSize,( TickTime_t ){ RADIO_TICK_SIZE_1000_US,TX_TIMEOUT_VALUE });
	//HAL_Delay(1);
	while(1)
		{
			if(AppState == APP_TX)  // Tx operation compleated
			{
				return 1;
			}
			else if (AppState == APP_TX_TIMEOUT)// Tx bad operation
			{
				return 0;
			}
		}
	return 1;

}
#ifdef ANTENNA
uint8_t count_2 = 1;
uint8_t RoboIME_SX1280::receiveFeedback(SX1280_Feedback_Packet_t *payload)
{
	if (count_2 == 1)
		{
		radio1.SetDioIrqParams( RxIrqMask, RxIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
		//HAL_Delay(5);
		count_2 ++;
		}
	radio1.SetRx(( TickTime_t ){ RADIO_TICK_SIZE_1000_US, 2 } );
	uint8_t actualBufferSize = 0;
	uint8_t feedId = 0 ;
	oldCount = payloadTempFeedback[25];
while(1){
		if(AppState2 == APP_RX)
		{
			AppState2 = APP_LOWPOWER;
			radio1.GetPayload(payloadTempFeedback, &actualBufferSize, sizeof(SX1280_Feedback_Packet_t));

			feedId = payloadTempFeedback[0];
			if (payloadTempFeedback[25] != 0 && feedId == 2 && payloadTempFeedback[27] != 0)
			{
				memcpy(&payload[feedId], payloadTempFeedback, sizeof(SX1280_Feedback_Packet_t));
				return actualBufferSize;
			}
			else
			{
				 HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin); // Red LED Blinking
				 return 0;
			}

		}
		else if (AppState2 == APP_RX_TIMEOUT)
		{
			HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin); // Red LED Blinking
			AppState2 = APP_LOWPOWER;
			return 0;
		}

}
	}


#endif


/* ----------  ROBOT FUNCTIONS ------------ */
uint8_t RoboIME_SX1280::receivePayload(SX1280_Send_Packet_t *payload){
	uint8_t actualBufferSize = 0;
	radio0.SetDioIrqParams( RxIrqMask, RxIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
	HAL_Delay(1);
	radio0.SetRx(( TickTime_t ){ RADIO_TICK_SIZE_1000_US, RX_TIMEOUT_VALUE} );
	oldCount = payloadTemp[25];
	while(1){
 		if(AppState == APP_RX)
		{
			radio0.GetPayload(payloadTemp, &actualBufferSize, sizeof(SX1280_Send_Packet_t));
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
			HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
			return 0;
		}
	}
}

uint8_t RoboIME_SX1280::sendFeedback(SX1280_Feedback_Packet_t *payload, uint8_t payloadSize) // SLAVE
{
		radio0.SetDioIrqParams( TxIrqMask, TxIrqMask, IRQ_RADIO_NONE, IRQ_RADIO_NONE );
		//HAL_Delay(1);
		radio0.SendPayload((uint8_t*)payload, payloadSize,( TickTime_t ){ RADIO_TICK_SIZE_1000_US,TX_TIMEOUT_VALUE } );
		//HAL_Delay(5);
		while(1)
			{
				if(AppState == APP_TX)  // Tx operation compleated
				{
					return 1;
				}
				else// Tx bad operation
				{
					return 0;
				}
			}
		return 1;
}

/* ----------  OTHER FUNCITONS ------------ */
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


/* ----------  CALLBACKS IRQ ------------ */
void OnTxDone( void )
{
    AppState = APP_TX;
}

void  OnRxDone( void )
{
	if (!transmitter)
	{
		AppState = APP_RX;
	}
	else
		{

		AppState2 = APP_RX;

		}
}

void OnTxTimeout( void )
{
    AppState = APP_TX_TIMEOUT;
}

void OnRxTimeout( void )
{
    if (!transmitter)
    {
    	AppState = APP_RX_TIMEOUT;
    }

	else
		{
		AppState2 = APP_RX_TIMEOUT;
		}
}

void  OnRxError( IrqErrorCode_t errorCode )
{
    if (!transmitter)
    {
    	AppState = APP_RX_ERROR;
    }

	else
		{
		AppState2 = APP_RX_ERROR;
		}

}
