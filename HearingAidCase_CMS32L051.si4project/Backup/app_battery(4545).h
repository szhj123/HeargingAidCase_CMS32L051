#ifndef _APP_BATTERY_H
#define _APP_BATTERY_H

#include "drv_task.h"
#include "drv_battery.h"

#define BATT_VOL_0                3200
#define BATT_VOL_25               3620
#define BATT_VOL_50               3820
#define BATT_VOL_75               4020
#define BATT_VOL_100              4120

typedef enum _batt_chg_state_t
{
    BATT_CHG_INIT = 0,
    BATT_CHG_GET_VOL_ERR,
    BATT_CHG_PROCESS,
    BATT_CHG_DONE
}batt_chg_state_t;

typedef enum _batt_unchg_state_t
{
    BATT_UNCHG_INIT = 0,
    BATT_UNCHG_PROCESS
}batt_unchg_state_t;

typedef enum _batt_level_t
{
    BATT_LEVEL_NULL = 0,
    BATT_LEVEL_0,
    BATT_LEVEL_5,
    BATT_LEVEL_25, 
    BATT_LEVEL_50,
    BATT_LEVEL_75,
    BATT_LEVEL_100
}batt_level_t;

typedef struct _batt_para_t
{
    uint16_t battVol;
    uint16_t battVolSave;
    uint16_t battVolErr;
    uint16_t earBudCur;

    uint16_t chgDelayCnt;

    task_ctrl_block_t *task;
    batt_chg_state_t chgState;
    batt_unchg_state_t unchgState;
    batt_level_t battLevel;
    batt_level_t preBattLevel;
}batt_para_t;

void App_Batt_Init(void );
batt_level_t App_Batt_Cal_Level(uint16_t battVol );

#endif 

