#ifndef _DRV_LED_H
#define _DRV_LED_H

#include "hal_led.h"

typedef struct _led_ctrl_block_t
{
    PORT_TypeDef port;
    PIN_TypeDef pin;

    uint8_t id;
    
}led_ctrl_block_t;

void Drv_Led_Init(void );
void Drv_Led_Off(led_ctrl_block_t *led );
void Drv_Led_On(led_ctrl_block_t *led );
uint8_t Drv_Led_Get_State(led_ctrl_block_t *led );

#endif 

