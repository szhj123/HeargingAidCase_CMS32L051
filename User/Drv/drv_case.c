/********************************************************
* @file       drv_case.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_case.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Drv_Case_Init(hal_isr_callback_t callback )
{
    Hal_Case_Init(callback);
}

uint8_t Drv_Case_Get_State(void )
{
    if(Hal_Hall_Get_State())
    {
        return CASE_STATE_OPEN;
    }
    else
    {
        return CASE_STATE_CLOSE;        
    }
}


