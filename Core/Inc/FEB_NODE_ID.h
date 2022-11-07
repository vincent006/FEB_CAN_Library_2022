/*
 * FED_NODE_ID.h
 *
 *  Created on: Oct 27, 2022
 *      Author: Wenhao Li
 */

#ifndef INC_FED_NODE_ID_H_
#define INC_FED_NODE_ID_H_



#endif /* INC_FED_NODE_ID_H_ */


#include <string.h>

/* SETTINGS */
#define ID_LENGTH_BITS 11
#define BITS_PER_ID 7
#define BITS_PER_MESSAGE_TYPE (ID_LENGTH_BITS - BITS_PER_ID)

/*** BMS ***/
#define BMS_ID 0b0000001

#define BMS_TEMPERATURE ((BMS_ID << BITS_PER_MESSAGE_TYPE) + 0b0001)
#define BMS_VOLTAGE ((BMS_ID << BITS_PER_MESSAGE_TYPE) + 0b0010)

/*** State Machine ***/
#define SM_ID 0b0000010

#define SM_CMD1 ((SM_ID << BITS_PER_MESSAGE_TYPE) + 0b0001)

/*** APPS ***/
#define APPS_ID 0b0000011

#define APPS_ACCELERATOR1_PEDAL     ((APPS_ID << BITS_PER_MESSAGE_TYPE) + 0b0001)
#define APPS_ACCELERATOR2_PEDAL     ((APPS_ID << BITS_PER_MESSAGE_TYPE) + 0b0010)
#define APPS_BRAKE_PEDAL            ((APPS_ID << BITS_PER_MESSAGE_TYPE) + 0b0011)



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
		case BMS_TEMPERATURE:
			memcpy(&(BMS_MESSAGE.temperature), RxData, data_length);
			break;
		case BMS_VOLTAGE:
			memcpy(&(BMS_MESSAGE.voltage), RxData, data_length);
			break;
	}
}

#define BMS_TEMPERATURE_TYPE float
#define BMS_VOLTAGE_TYPE float

const AddressIdType BMS_RX_ID[] = {SM_ID};
const FilterArrayLength BMS_RX_NUM = 1;


/*** Buffer for SM messages ***/
typedef struct SM_MESSAGE_TYPE {
	uint8_t command_1;
} SM_MESSAGE_TYPE;
SM_MESSAGE_TYPE SM_MESSAGE;

void Store_SM_Msg(uint32_t RxId, uint8_t *RxData, uint32_t data_length) {
	switch(RxId){
		case SM_CMD1:
			memcpy(&(SM_MESSAGE.command_1), RxData, data_length);
			break;
	}
}

#define SM_COMMAND_TYPE uint8_t

const AddressIdType SM_RX_ID[] = {BMS_ID, APPS_ID};
const FilterArrayLength SM_RX_NUM = 2;


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
			memcpy(&(APPS_MESSAGE.accelerator_1), RxData, data_length);
			break;
		case APPS_ACCELERATOR2_PEDAL:
			memcpy(&(APPS_MESSAGE.accelerator_2), RxData, data_length);
			break;
		case APPS_BRAKE_PEDAL:
			memcpy(&(APPS_MESSAGE.brake), RxData, data_length);
			break;
	}
}

#define APPS_ACCELERATOR_TYPE uint16_t
#define APPS_BRAKE_TYPE uint16_t

const AddressIdType APPS_RX_ID[] = {SM_ID};
const FilterArrayLength APPS_RX_NUM = 1;


const AddressIdType* assign_filter_array(uint32_t NODE_ID) {
	switch(NODE_ID) {
		case BMS_ID:
			return BMS_RX_ID;
			break;
		case SM_ID:
			return SM_RX_ID;
			break;
		case APPS_ID:
			return APPS_RX_ID;
			break;
	}
	return 0;
}

FilterArrayLength assign_filter_array_legnth(uint32_t NODE_ID) {
	switch(NODE_ID) {
		case BMS_ID:
			return BMS_RX_NUM;
			break;
		case SM_ID:
			return SM_RX_NUM;
			break;
		case APPS_ID:
			return APPS_RX_NUM;
			break;
	}
	return -1;
}

void store_msg(CAN_RxHeaderTypeDef *pHeader, uint8_t RxData[]) {
	switch(pHeader->StdId >> BITS_PER_MESSAGE_TYPE) {
		case BMS_ID:
			Store_BMS_Msg(pHeader->StdId, RxData, pHeader->DLC);
			break;
		case SM_ID:
			Store_SM_Msg(pHeader->StdId, RxData, pHeader->DLC);
			break;
		case APPS_ID:
			Store_APPS_Msg(pHeader->StdId, RxData, pHeader->DLC);
			break;
	}
}
