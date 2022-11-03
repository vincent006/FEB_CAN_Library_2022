/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : FEB_CAN.h
  * @brief          : Header for FEB_CAN library.
  *                   This file contains the functions to encapsulate the process
  *                   to initialize a CAN node, transmitting and receiving messages.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#include "FED_NODE_ID.h"

CAN_TxHeaderTypeDef my_TxHeader;
CAN_RxHeaderTypeDef my_RxHeader;
uint8_t TxData[8];
uint8_t RxData[8];
uint32_t TxMailbox;
uint8_t flag = 0;


void SM_Buffer(){
	switch (my_RxHeader.StdId){
		case FEB_BMS_TEMP:
			BMS_MESSAGE_TYPE.temperature=(float) *RxData;
			break;
		case FEB_BMS_VOLT:
			BMS_MESSAGE_TYPE.voltage=(float) *RxData;
			break;
		case FEB_APPS_GAS:
			APPS_MESSAGE_TYPE.gas=(float) *RxData;
			break;
		case FEB_APPS_BRAKE:
			APPS_MESSAGE_TYPE.brake=(float) *RxData;
	}
}

void APPS_Buffer(){
	switch(my_RxHeader.StdId){
		case FEB_SM_CMD1:
			SM_MESSAGE_TYPE.command_1=(float) *RxData;
	}
}

void FEB_CAN_Filter_Config(CAN_HandleTypeDef *hcan, const FilterArrayType* filter_array, uint8_t filter_array_len) {

	for (int i=0; i < filter_array_len; i++) {
		CAN_FilterTypeDef my_can_filter_config;

		my_can_filter_config.FilterActivation = CAN_FILTER_ENABLE;
		my_can_filter_config.FilterBank = i;
		my_can_filter_config.FilterFIFOAssignment = 0;
		my_can_filter_config.FilterIdHigh = filter_array[i] << 5; //Std ID is 11 bits, FilterIDHigh is the higher 16 bits
		my_can_filter_config.FilterIdLow = 0;
		my_can_filter_config.FilterMaskIdHigh = 0x7F0 << 5; //check the first 7 bit (node address)
		my_can_filter_config.FilterMaskIdLow = 0;
		my_can_filter_config.FilterMode = CAN_FILTERMODE_IDMASK;
		my_can_filter_config.FilterScale = CAN_FILTERSCALE_32BIT;
		my_can_filter_config.SlaveStartFilterBank = 27;

		if(HAL_CAN_ConfigFilter(hcan, &my_can_filter_config))
		{
		  Error_Handler();
		}
	}
}

void FEB_CAN_init(CAN_HandleTypeDef *hcan, const FilterArrayType* filter_array, uint8_t filter_array_len)
{
	my_TxHeader.DLC = 1;
	my_TxHeader.StdId = 0x7FF;
	my_TxHeader.ExtId = 0;
	my_TxHeader.IDE = CAN_ID_STD;
	my_TxHeader.RTR = CAN_RTR_DATA;
	my_TxHeader.TransmitGlobalTime = DISABLE;

	FEB_CAN_Filter_Config(hcan, filter_array, filter_array_len);

	if (HAL_CAN_Start(hcan) != HAL_OK) {
	  Error_Handler();
	}
	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

}
