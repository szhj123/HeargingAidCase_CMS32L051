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

void Gpio_Init(void );
void Tim40_Interval_Init(void );


#endif 

