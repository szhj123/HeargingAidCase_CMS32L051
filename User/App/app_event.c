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
#include "app_battery.h"
#include "app_led.h"
#include "app_case.h"
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
            batt_level_t battLevel = (batt_level_t )msg.buf[0];

            App_Led_Bat_Unchg(battLevel);

            break;
        }
        case APP_EVT_BATT_CHG_LEVEL:
        {
            batt_level_t battLevel = (batt_level_t )msg.buf[0];

            App_Led_Bat_Chg(battLevel);
            
            break;
        }
        case APP_EVT_EARBUD_CUR:
        {
            earbud_chg_state_t earbudState = (earbud_chg_state_t )msg.buf[0];

            switch(earbudState)
            {
                case EARBUD_CHG_STATE_PROCESS:
                {
                    break;
                }
                case EARBUD_CHG_STATE_DONE:
                {
                    if(App_Usb_Get_State() == USB_STATE_PLUG_OUT)
                    {
                        App_Led_Earbud_Chg_Done();
                    }
                    break;
                }
                case EARBUD_CHG_STATE_OVERCUR:
                {
                    break;
                }
                default: break;
            }
            break;
        }
        case APP_EVT_CASE_OPEN_CLOSE:
        {
            uint8_t caseState = msg.buf[0];

            if(caseState == CASE_STATE_OPEN)
            {
                App_Com_Tx_Cmd(CMD_CASE_OPEN);
            }
            else
            {
                App_Com_Tx_Cmd(CMD_CASE_CLOSE);
            }

            App_Led_Light_5S(App_Batt_Get_Chg_State());
            
            break;
        }
        default: break;
    }
}

