/********************************************************
* @file       hal_task.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_task.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
static hal_isr_callback_t task_isr_callback = NULL;

void Hal_Task_Init(void )
{
    SystemCoreClockUpdate();

    SysTick_Config(SystemCoreClock/1000);
}

void Hal_Task_Regist_Isr_Callback(hal_isr_callback_t callback )
{
    task_isr_callback = callback;
}

void Hal_Task_Isr_Handler(void )
{
    if(task_isr_callback != NULL)
    {
        task_isr_callback();
    }
}

