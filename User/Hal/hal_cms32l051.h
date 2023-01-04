#ifndef _HAL_CMS32L051_H
#define _HAL_CMS32L051_H

typedef void (*hal_isr_callback_t)(void );

#include <stdint.h>
#include "stdlib.h"
#include "string.h"
#include "CMS32L051.h"
#include "userdefine.h"
#include "clk.h"
#include "gpio.h"
#include "tim4.h"
#include "adc.h"

void Gpio_Init(void );
void Tim40_Interval_Init(void );
void Adc_Init(void );
uint16_t Adc_Get_Val(adc_channel_t  channel );


#endif 

