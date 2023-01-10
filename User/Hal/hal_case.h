#ifndef _HAL_CASE_H
#define _HAL_CASE_H

#include "hal_cms32l051.h"

void Hal_Case_Init(hal_isr_callback_t callback );
uint8_t Hal_Hall_Get_State(void );
void Hal_Hall_Isr_Handler(void );

#endif 

