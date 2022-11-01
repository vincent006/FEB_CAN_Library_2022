/*
 * FED_NODE_ID.h
 *
 *  Created on: Oct 27, 2022
 *      Author: Wenhao Li
 */

#ifndef INC_FED_NODE_ID_H_
#define INC_FED_NODE_ID_H_



#endif /* INC_FED_NODE_ID_H_ */


/*** BMS ***/
#define FEB_BMS_ID 0x010

#define FEB_BMS_TEMP (0x010 + 0x001)
#define FEB_BMS_VOLT (0x010 + 0x002)



/*** State Machine ***/
#define FEB_SM_ID 0x020

#define FEB_SM_CMD1 0x021


/*** APPS ***/
#define FEB_APPS_ID 0x030

#define FEB_APPS_GAS 0x031
#define FEB_APPS_BRAKE 0x032



typedef uint16_t FilterArrayType;
/*** Buffer for BMS messages ***/
struct{
	float temperature;
	float voltage;
} BMS_MESSAGE_TYPE;
const FilterArrayType BMS_Rx_ID[] = {FEB_SM_ID};


/*** Buffer for SM messages ***/
struct {
	int command_1;
} SM_MESSAGE_TYPE;
const FilterArrayType SM_Rx_ID[] = {FEB_BMS_ID, FEB_APPS_ID};


/*** Buffer for APPS messages ***/
struct {
	float gas;
	float brake;
} APPS_MESSAGE_TYPE;
const FilterArrayType APPS_Rx_ID[] = {FEB_SM_ID};



