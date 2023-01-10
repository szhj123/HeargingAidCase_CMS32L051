/********************************************************
* @file       app_event.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "app_event.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Event_Handler(void *arg );
/* Private variables ------------------------------------*/

void App_Event_Init(void )
{
    Drv_Task_Regist_Period(App_Event_Handler, 0, 1, NULL);
}

static void App_Event_Handler(void *arg )
{
    static msg_t msg;

    if(Drv_Msg_Get(&msg) == MSG_ERR)
    {
        return ;
    }

    switch((app_evt_t )msg.event)
    {
        case APP_EVT_BATT_UNCHG_LEVEL:
        {
            break;
        }
        case APP_EVT_EARBUD_CUR:
        {
            break;
        }
        default: break;
    }
}

