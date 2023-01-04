/********************************************************
* @file       drv_battery.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_battery.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
#define ADC_REF_VOL                1450
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Drv_Batt_Init(void )
{
    Hal_Batt_Init();
}

uint16_t Drv_Batt_Get_Vol(void )
{
    uint16_t adcRefVal;
    
    adcRefVal = Hal_Batt_Get_AdcVal(ADC_INTERREFVOLT);

    return (uint16_t )(ADC_REF_VOL * 4096u / adcRefVal);
}
