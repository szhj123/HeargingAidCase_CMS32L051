/********************************************************
* @file       app_battery.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_task.h"

#include "app_battery.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
batt_para_t battPara;

void App_Batt_Init(void )
{
    static uint16_t vccVol;

    Drv_Batt_Init();

    battPara.battVol = Drv_Batt_Get_Vol();
    
    battPara.preBattVol = battPara.battVol;

    
}

