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
#include "app_battery.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void App_Batt_Init(void )
{
    static uint16_t vccVol;

    Drv_Batt_Init();

    vccVol = Drv_Batt_Get_Vol();
}

