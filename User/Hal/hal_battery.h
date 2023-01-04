#ifndef _HAL_BATTERY_H
#define _HAL_BATTERY_H

#include "hal_cms32l051.h"

void Hal_Batt_Init(void );
uint16_t Hal_Batt_Get_AdcVal(adc_channel_t channel );

#endif 

