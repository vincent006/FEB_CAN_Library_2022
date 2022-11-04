/*
 * FED_NODE_ID.h
 *
 *  Created on: Oct 27, 2022
 *      Author: Wenhao Li
 */

#ifndef INC_FED_NODE_ID_H_
#define INC_FED_NODE_ID_H_



#endif /* INC_FED_NODE_ID_H_ */


/* SETTINGS */
#define ID_LENGTH_BITS 11
#define BITS_PER_ID 7
#define BITS_PER_MESSAGE_TYPE (ID_LENGTH_BITS - BITS_PER_ID)

/*** BMS ***/
#define BMS_ID 0b0000001

#define BMS_TEMP (BMS_ID << BITS_PER_MESSAGE_TYPE + 0b0001)
#define BMS_VOLTAGE (BMS_ID << BITS_PER_MESSAGE_TYPE + 0b0010)

/*** State Machine ***/
#define SM_ID 0b0000010

#define SM_CMD1 (SM_ID << BITS_PER_MESSAGE_TYPE + 0b0001)

/*** APPS ***/
#define APPS_ID 0b0000011

#define APPS_ACCELERATOR1_PEDAL     (APPS_ID << BITS_PER_MESSAGE_TYPE + 0b0001)
#define APPS_ACCELERATOR2_PEDAL     (APPS_ID << BITS_PER_MESSAGE_TYPE + 0b0010)
#define APPS_BRAKE_PEDAL            (APPS_ID << BITS_PER_MESSAGE_TYPE + 0b0011)



typedef uint32_t AddressIdType;
typedef uint8_t FilterArrayLength;


/*** Buffer for BMS messages ***/
typedef struct BMS_MESSAGE_TYPE {
	float temperature;
	float voltage;
} BMS_MESSAGE_TYPE;
BMS_MESSAGE_TYPE BMS_MESSAGE;

void Store_BMS_Msg(uint32_t RxId, uint8_t *RxData, uint32_t data_length) {
	switch (RxId){
		case BMS_TEMP:
			memcpy(BMS_MESSAGE.temperature, RxData, data_length);
			break;
		case BMS_VOLTAGE:
			memcpy(BMS_MESSAGE.voltage, RxData, data_length);
			break;
	}
}

#define BMS_TEMPERATURE_TYPE float
#define BMS_VOLTAGE_TYPE float

const AddressIdType BMS_Rx_ID[] = {FEB_SM_ID};
const FilterAarrayLength BMS_RX_NUM = 1;


/*** Buffer for SM messages ***/
typedef struct SM_MESSAGE_TYPE {
	uint8_t command_1;
} SM_MESSAGE_TYPE;
SM_MESSAGE_TYPE SM_MESSAGE;

void Store_SM_Msg(uint32_t RxId, uint8_t *RxData, uint32_t data_length) {
	switch(RxId){
		case SM_CMD1:
			memcpy(SM_MESSAGE.command_1, RxData, data_length);
	}
}

#define SM_COMMAND_TYPE uint8_t

const AddressIdType SM_Rx_ID[] = {FEB_BMS_ID, FEB_APPS_ID};
const FilterAarrayLength SM_RX_NUM = 2;


/*** Buffer for APPS messages ***/
typedef struct APPS_MESSAGE_TYPE {
	uint16_t accelerator_1;
	uint16_t accelerator_2;
	uint16_t brake;
} APPS_MESSAGE_TYPE;
APPS_MESSAGE_TYPE APPS_MESSAGE;

void Store_APPS_Msg(uint32_t RxId, uint8_t *RxData, uint32_t data_length) {
	switch (RxId){
		case APPS_ACCELERATOR1_PEDAL:
			memcpy(APPS_MESSAGE.accelerator_1, RxData, data_length);
			break;
		case APPS_ACCELERATOR2_PEDAL:
			memcpy(APPS_MESSAGE.accelerator_2, RxData, data_length);
			break;
		case APPS_BRAKE_PEDAL:
			memcpy(APPS_MESSAGE.brake, RxData, data_length);
	}
}

#define APPS_ACCELERATOR_TYPE uint16_t
#define APPS_BRAKE_TYPE uint16_t

const AddressIdType APPS_Rx_ID[] = {FEB_SM_ID};
const FilterAarrayLength APPS_RX_NUM = 1;



