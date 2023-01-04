/********************************************************
* @file       hal_battery.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_battery.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Hal_Batt_Init(void )
{
    Adc_Init();
}

uint16_t Hal_Batt_Get_AdcVal(adc_channel_t channel )
{
    return Adc_Get_Val(channel);
}

