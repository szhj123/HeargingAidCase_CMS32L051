/********************************************************
* @file       drv_timer.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_timer.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void Drv_Timer_Isr_Callback(void );
/* Private variables ------------------------------------*/
timer_ctrl_block_t timerList[TIMER_MAX_NUM];

void test(void *arg )
{
    if((uint32_t )arg == 5)
    {
        PORT_ToggleBit(PORT7, PIN1);
    }

    
    Drv_Timer_Regist_Oneshot(test, 250, (void *)5);
}

void Drv_Timer_Init(void )
{
    uint8_t i;
    
    Hal_Timer_Init();   

    Hal_Timer_Regist_Isr_Callback(Drv_Timer_Isr_Callback);

    for(i=0;i<TIMER_MAX_NUM;i++)
    {
        timerList[i].handler = NULL;
        timerList[i].arg = NULL;
        timerList[i].ticks = 0;
        timerList[i].period = 0;
        timerList[i].isRegistFlag = 0;
    }
    
    PORT_Init(PORT7, PIN1, OUTPUT);

    Drv_Timer_Regist_Oneshot(test, 250, (void *)5);
}   

static uint8_t Drv_Timer_Regist(void (*handler)(void *), uint16_t ticks, uint16_t period, void *arg )
{
    uint8_t i;

    for(i=0;i<TIMER_MAX_NUM;i++)
    {
        if(!timerList[i].isRegistFlag)
        {
            timerList[i].handler = handler;
            timerList[i].arg = arg;
            timerList[i].ticks = ticks;
            timerList[i].period = period;
            timerList[i].isRegistFlag = 1;

            break;
        }
    }

    return i;
}

uint8_t Drv_Timer_Regist_Oneshot(void (*handler)(void *), uint16_t ticks, void *arg )
{
    return Drv_Timer_Regist(handler, ticks, 0, arg);
}

uint8_t Drv_Timer_Regist_Period(void (*handler)(void *arg ), uint16_t ticks, uint16_t period, void *arg )
{
    return Drv_Timer_Regist(handler, ticks, period, arg );
}

void Drv_Timer_Delete(uint8_t timerId )
{
    if(timerId == TIMER_MAX_NUM)
    {
        return ;
    }

    timerList[timerId].handler = NULL;
    timerList[timerId].arg = NULL;
    timerList[timerId].ticks = 0;
    timerList[timerId].period = 0;
    timerList[timerId].isRegistFlag = 0;
}

static void Drv_Timer_Isr_Callback(void )
{
    uint8_t i;

    for(i=0;i<TIMER_MAX_NUM;i++)
    {
        if(timerList[i].isRegistFlag)
        {
            if(timerList[i].ticks)
            {
                timerList[i].ticks--;
            }

            if(timerList[i].ticks == 0)
            {
                if(timerList[i].handler != NULL)
                {
                    timerList[i].handler(timerList[i].arg);

                    if(timerList[i].period)
                    {
                        timerList[i].ticks = timerList[i].period;
                    }
                    else
                    {
                        Drv_Timer_Delete(i);
                    }
                }
            }
        }
    }
}

