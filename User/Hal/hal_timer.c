/********************************************************
* @file       hal_timer.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_timer.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
hal_isr_callback_t timer_isr_callback = NULL;

void Hal_Timer_Init(void )
{
    Tim40_Interval_Init();
}

void Hal_Timer_Regist_Isr_Callback(hal_isr_callback_t callback )
{
    timer_isr_callback = callback;
}

void Hal_Timer_Isr_Handler(void )
{
    if(timer_isr_callback != NULL)
    {
        timer_isr_callback();
    }
}


