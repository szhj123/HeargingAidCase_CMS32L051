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
static void App_Com_Tx_Cmd_Callback(void *arg );
/* Private variables ------------------------------------*/
com_para_t comPara;

void App_Case_Init(void )
{
    Drv_Case_Init(App_Hall_Detect_Handler);

    comPara.timer = TIMER_NULL;
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

uint8_t App_Case_Get_State(void )
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

    return caseState;
}

void App_Com_Tx_Cmd(uint16_t lowTime )
{
    if(comPara.timer != TIMER_NULL)
    {
        Drv_Timer_Delete(comPara.timer);

        comPara.timer = TIMER_NULL;
    }

    comPara.lowTime = lowTime;

    comPara.comState = COM_STATE_TX_INIT;

    comPara.delayCnt = 0;

    comPara.txCnt = 0;

    Drv_Timer_Regist_Period(App_Com_Tx_Cmd_Callback, 0, 1, NULL);
}

static void App_Com_Tx_Cmd_Callback(void *arg )
{
    if(comPara.delayCnt < 0xffff)
    {
        comPara.delayCnt++;
    }

    switch(comPara.comState)
    {
        case COM_STATE_TX_INIT:
        {
            Drv_Com_Set_Tx_High();

            comPara.delayCnt = 0;
            
            comPara.comState = COM_STATE_TX_HIGH;
            break;
        }
        case COM_STATE_TX_HIGH:
        {
            if(comPara.delayCnt > 50)
            {
                Drv_Com_Set_Tx_Low();

                comPara.delayCnt = 0;

                comPara.comState = COM_STATE_TX_LOW;
            }
            
            break;
        }
        case COM_STATE_TX_LOW:
        {
            if(comPara.delayCnt > comPara.lowTime)
            {
                comPara.delayCnt = 0;

                if(++comPara.txCnt >= 10)
                {
                    Drv_Com_Set_Tx_High();
                    
                    comPara.txCnt = 0;

                    comPara.comState = COM_STATE_TX_EXIT;
                }
                else
                {
                    comPara.comState = COM_STATE_TX_INIT;
                }
            }
            break;
        }
        case COM_STATE_TX_EXIT:
        {
            if(comPara.timer != TIMER_NULL)
            {
                Drv_Timer_Delete(comPara.timer);

                comPara.timer = TIMER_NULL;

                comPara.comState = COM_STATE_TX_INIT;
            }
            break;
        }
        default: break;
    }
}

