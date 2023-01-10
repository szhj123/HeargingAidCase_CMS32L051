#ifndef _HAL_BATTERY_H
#define _HAL_BATTERY_H

#include "hal_cms32l051.h"

void Hal_Batt_Init(void );
void Hal_Usb_Regist_Callback(hal_isr_callback_t callback );
uint16_t Hal_Batt_Get_AdcVal(adc_channel_t channel );
uint8_t Hal_Usb_Get_Plug_State(void );
uint8_t Hal_Batt_Get_Chg_State(void );
void Hal_Usb_Plug_Isr_Handler(void );

#endif 

