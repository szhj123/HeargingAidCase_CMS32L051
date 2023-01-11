#ifndef _DRV_BATTERY_H
#define _DRV_BATTERY_H

#include "hal_battery.h"

#define USB_STATE_PLUG_IN                 1
#define USB_STATE_PLUG_OUT                0

void Drv_Batt_Init(void );
void Drv_Usb_Regist_Callback(hal_isr_callback_t callback );
uint16_t Drv_Batt_Get_Vol(void );
uint16_t Drv_Earbud_Get_Cur(void );
uint8_t Drv_Usb_Get_State(void );
uint8_t Drv_Batt_Get_Chg_State(void );

#endif 

