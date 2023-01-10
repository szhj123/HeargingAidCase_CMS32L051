#ifndef _APP_EVENT_H
#define _APP_EVENT_H

#include "drv_task.h"
#include "drv_event.h"

typedef enum _app_evt_t
{
    APP_EVT_BATT_UNCHG_LEVEL = 0,
    APP_EVT_BATT_CHG_LEVEL,
    APP_EVT_EARBUD_CUR,
    APP_EVT_CASE_OPEN_CLOSE
}app_evt_t;

void App_Event_Init(void );


#endif 

