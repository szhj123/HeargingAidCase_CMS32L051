/********************************************************
* @file       hal_case.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_case.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
hal_isr_callback_t hall_isr_callback = NULL;

void Hal_Case_Init(hal_isr_callback_t callback )
{
    Gpio_Init();

    Gpio_Interrupt_Init();

    hall_isr_callback = callback;
}

uint8_t Hal_Hall_Get_State(void )
{
    return PORT_GetBit(PORT13, PIN6);
}

void Hal_Hall_Isr_Handler(void )
{
    if(hall_isr_callback != NULL)
    {
        hall_isr_callback();
    }
}


