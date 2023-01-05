#ifndef _APP_BATTERY_H
#define _APP_BATTERY_H

#include "drv_battery.h"

typedef struct _batt_para_t
{
    uint16_t battVol;
    uint16_t preBattVol;
    uint16_t earBudCur;
    
}batt_para_t;

void App_Batt_Init(void );

#endif 

