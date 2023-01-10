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

void Drv_Usb_Regist_Callback(hal_isr_callback_t callback )
{
    Hal_Usb_Regist_Callback(callback);
}

uint16_t Drv_Batt_Get_Vol(void )
{
    uint16_t adcRefVal;
    
    adcRefVal = Hal_Batt_Get_AdcVal(ADC_INTERREFVOLT);

    return (uint16_t )((uint32_t )ADC_REF_VOL * 4096 / adcRefVal);
}

uint16_t Drv_Earbud_Get_Cur(void )
{
    uint16_t adcRefVal;
    uint16_t adcCurVal;

    adcRefVal = Hal_Batt_Get_AdcVal(ADC_INTERREFVOLT);
    
    adcCurVal = Hal_Batt_Get_AdcVal(ADC_CHANNEL_0);

    return (uint16_t )((uint32_t )ADC_REF_VOL * adcCurVal / adcRefVal);
}

uint8_t Drv_Usb_Get_State(void )
{
    uint8_t ret;
    
    if(Hal_Usb_Get_Plug_State())
    {
        ret = USB_STATE_PLUG_IN;
    }
    else
    {
        ret = USB_STATE_PLUG_OUT;
    }

    return ret;
}

uint8_t Drv_Batt_Get_Chg_State(void )
{
    return Hal_Batt_Get_Chg_State();
}

