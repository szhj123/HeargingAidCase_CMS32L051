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
hal_isr_callback_t usb_plug_isr_callback = NULL;


void Hal_Batt_Init(void )
{
    Adc_Init();

    Gpio_Init();

    Gpio_Interrupt_Init();
}

void Hal_Usb_Regist_Callback(hal_isr_callback_t callback )
{
    usb_plug_isr_callback = callback;
}

uint16_t Hal_Batt_Get_AdcVal(adc_channel_t channel )
{
    return Adc_Get_Val(channel);
}

uint8_t Hal_Usb_Get_Plug_State(void )
{
    return PORT_GetBit(PORT12, PIN1);
}

uint8_t Hal_Batt_Get_Chg_State(void )
{
    return PORT_GetBit(PORT2, PIN3);
}

void Hal_Usb_Plug_Isr_Handler(void )
{
    if(usb_plug_isr_callback != NULL)
    {
        usb_plug_isr_callback();
    }
}


