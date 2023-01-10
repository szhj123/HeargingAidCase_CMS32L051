/********************************************************
* @file       app_case.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "app_case.h"
#include "app_event.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Hall_Detect_Handler(void );
/* Private variables ------------------------------------*/

void App_Case_Init(void )
{
    Drv_Case_Init(App_Hall_Detect_Handler);
}

static void App_Hall_Detect_Handler(void )
{
    uint8_t caseState;
    
    if(Drv_Case_Get_State())
    {
        caseState = CASE_STATE_OPEN;
    }
    else
    {
        caseState = CASE_STATE_CLOSE;
    }

    Drv_Msg_Put(APP_EVT_CASE_OPEN_CLOSE, (uint8_t *)&caseState, 1);
}

void App_Com_Tx_Cmd(uint16_t lowTime )
{
    
}

