#ifndef _APP_LED_H
#define _APP_LED_H

#include "app_battery.h"

#include "drv_led.h"
#include "drv_timer.h"

typedef struct _led_para_t
{
    uint8_t timer;
    uint16_t delayCnt;
    
}led_para_t;

void App_Led_Init(void );
void App_Led_All_Off(void );
void App_Led_All_On(void );
void App_Led_Bat_Unchg_Level_5(void );
void App_Led_Bat_Unchg_Level_25(void );
void App_Led_Bat_Unchg_Level_50(void );
void App_Led_Bat_Unchg_Level_75(void );
void App_Led_Bat_Unchg_Level_100(void );

void App_Led_Bat_Chg_Level_5(void );
void App_Led_Bat_Chg_Level_25(void );
void App_Led_Bat_Chg_Level_50(void );
void App_Led_Bat_Chg_Level_75(void );
void App_Led_Bat_Chg_Level_100(void );

void App_Led_Earbud_Chg_Done(void );

void App_Led_Bat_Chg(batt_level_t battLevel );
void App_Led_Bat_Unchg(batt_level_t battLevel );

void App_Led_Light_5S(batt_level_t battLevel );


#endif 

