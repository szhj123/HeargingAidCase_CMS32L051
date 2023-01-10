#ifndef _HAL_LED_H
#define _HAL_LED_H

#include "hal_cms32l051.h"

void Hal_Led_Init(void );
void Hal_Led_Off(PORT_TypeDef port, PIN_TypeDef pin );
void Hal_Led_On(PORT_TypeDef port, PIN_TypeDef pin );
uint8_t Hal_Led_Get_State(PORT_TypeDef port, PIN_TypeDef pin );

#endif 

