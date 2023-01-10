/********************************************************
* @file       app_battery.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "app_battery.h"
#include "app_event.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
#define ADC_DET_COUNT                200  
#define BATT_CHG_TIMEOUT             1800 //second
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Usb_Plug_Handler(void );
static void App_Batt_Charge_Handler(void *arg );
static void App_Batt_Uncharge_Handler(void *arg );
/* Private variables ------------------------------------*/
batt_para_t battPara;
static uint8_t battSampleEndFlag;

void App_Batt_Init(void )
{
    Drv_Batt_Init();

    battPara.battVol = Drv_Batt_Get_Vol();

    Drv_Usb_Regist_Callback(App_Usb_Plug_Handler);

    App_Usb_Plug_Handler();
}

static void App_Usb_Plug_Handler(void )
{
    if(battPara.task != NULL)
    {
        Drv_Task_Delete(battPara.task);

        battPara.task = NULL;
    }
    
    if(Drv_Usb_Get_State() == USB_STATE_PLUG_IN)
    {
        battPara.battChgState = BATT_CHG_INIT;
        battPara.task = Drv_Task_Regist_Period(App_Batt_Charge_Handler, 0, 5, NULL);
    }
    else
    {
        battPara.battUnchgState = BATT_UNCHG_INIT;
        battPara.task = Drv_Task_Regist_Period(App_Batt_Uncharge_Handler, 0, 5, NULL);
    }
}

void Drv_Batt_Adc_Sample(uint8_t *battSampleEndFlag )
{
    static uint16_t adcSampleCnt;
    static uint32_t batVolSum;
    static uint32_t earbudCurSum;

    uint16_t tmpBatVol;
    uint16_t tmpEarbudCur;
	    
    tmpBatVol = Drv_Batt_Get_Vol();
    
    tmpEarbudCur = Drv_Earbud_Get_Cur();
        
    *battSampleEndFlag = 0;

    if(adcSampleCnt < ADC_DET_COUNT)
    {            
        batVolSum += tmpBatVol;
        earbudCurSum += tmpEarbudCur;
        
        adcSampleCnt++;
    }
    else
    {
        battPara.battVol = batVolSum / ADC_DET_COUNT;

        battPara.earBudCur = earbudCurSum / ADC_DET_COUNT;
     
        *battSampleEndFlag = 1;

        adcSampleCnt = 0;
        batVolSum = 0;
        earbudCurSum = 0;
    } 
}

static void App_Batt_Uncharge_Handler(void *arg )
{
    Drv_Batt_Adc_Sample(&battSampleEndFlag);

    if(!battSampleEndFlag)
    {
        return ;
    }
    
    switch(battPara.battUnchgState)
    {
        case BATT_UNCHG_INIT:
        {
            if(battPara.battLevel == BATT_LEVEL_NULL)
            {
                battPara.battVol = Drv_Batt_Get_Vol();
                
                battPara.battVolSave = battPara.battVol;
                
                battPara.battLevel = App_Batt_Cal_Level(battPara.battVol);
            }

            battPara.preBattLevel = battPara.battLevel;

            battPara.earbudChgState = App_Earbud_Cal_Chg_State(battPara.earBudCur);

            battPara.preEarbudChgState = battPara.earbudChgState;

            Drv_Msg_Put((uint8_t )APP_EVT_BATT_UNCHG_LEVEL, (uint8_t *)&battPara.battLevel, 1);

            Drv_Msg_Put((uint8_t )APP_EVT_EARBUD_CUR, (uint8_t *)&battPara.earbudChgState, 1);

            battPara.battUnchgState = BATT_UNCHG_PROCESS;
            
            break;
        }
        case BATT_UNCHG_PROCESS:
        {
            battPara.battVolSave = battPara.battVol;

            battPara.battLevel = App_Batt_Cal_Level(battPara.battVol);

            battPara.earbudChgState = App_Earbud_Cal_Chg_State(battPara.earBudCur);

            if(battPara.preEarbudChgState != battPara.earbudChgState)
            {
                battPara.preEarbudChgState = battPara.earbudChgState;

                Drv_Msg_Put((uint8_t )APP_EVT_EARBUD_CUR, (uint8_t *)&battPara.earbudChgState, 1);
            }

            if(battPara.battLevel < battPara.preBattLevel)
            {
                battPara.preBattLevel = battPara.battLevel;
                
                Drv_Msg_Put((uint8_t )APP_EVT_BATT_UNCHG_LEVEL, (uint8_t *)&battPara.battLevel, 1);
            }
            break;
        }
        default: break;
    }
}

static void App_Batt_Charge_Handler(void *arg )
{
    switch(battPara.battChgState)
    {
        case BATT_CHG_INIT:
        {
            battPara.battVol = Drv_Batt_Get_Vol();

            battPara.earBudCur = Drv_Earbud_Get_Cur();

            battPara.battVolSave = battPara.battVol;

            battPara.battLevel = App_Batt_Cal_Level(battPara.battVol);

            battPara.preBattLevel = battPara.battLevel;  

            battPara.earbudChgState = App_Earbud_Cal_Chg_State(battPara.earBudCur);

            battPara.preEarbudChgState = battPara.earbudChgState;

            Drv_Msg_Put((uint8_t )APP_EVT_BATT_CHG_LEVEL, (uint8_t *)&battPara.battLevel, 1);

            Drv_Msg_Put((uint8_t )APP_EVT_EARBUD_CUR, (uint8_t *)&battPara.earbudChgState, 1);

            battPara.chgDelayCnt = 0;

            battPara.battChgState = BATT_CHG_GET_VOL_ERR;

            Drv_Task_Delay(battPara.task, 5000);
            
            break;
        }
        case BATT_CHG_GET_VOL_ERR:
        {
            Drv_Batt_Adc_Sample(&battSampleEndFlag);

            if(!battSampleEndFlag)
            {
                return ;
            }

            if(battPara.battVol > battPara.battVolSave)
            {
                battPara.battVolErr = battPara.battVol - battPara.battVolSave;

                
                battPara.battChgState = BATT_CHG_PROCESS;
            }
            break;
        }
        case BATT_CHG_PROCESS:
        {
            Drv_Batt_Adc_Sample(&battSampleEndFlag);

            if(!battSampleEndFlag)
            {
                return ;
            }

            
            battPara.earbudChgState = App_Earbud_Cal_Chg_State(battPara.earBudCur);
            
            if(battPara.preEarbudChgState != battPara.earbudChgState)
            {
                battPara.preEarbudChgState = battPara.earbudChgState;

                Drv_Msg_Put((uint8_t )APP_EVT_EARBUD_CUR, (uint8_t *)&battPara.earbudChgState, 1);
            }

            if(battPara.battVol > 4200)
            {
                if(++battPara.chgDelayCnt > BATT_CHG_TIMEOUT || Drv_Batt_Get_Chg_State())
                {
                    battPara.chgDelayCnt  = 0;

                    battPara.battLevel = BATT_LEVEL_100;
                }
            }
            else
            {
                battPara.battLevel = App_Batt_Cal_Level(battPara.battVol - battPara.battVolErr);
            }
            
            if(battPara.battLevel > battPara.preBattLevel)
            {
                battPara.preBattLevel = battPara.battLevel;

                Drv_Msg_Put((uint8_t )APP_EVT_BATT_CHG_LEVEL, (uint8_t *)&battPara.battLevel, 1);
            }
            break;
        }
        default: break;
    }
}

batt_level_t App_Batt_Cal_Level(uint16_t battVol )
{
    const uint8_t faultTolerantVal = 25;//mv
    
    if(battPara.battLevel == BATT_LEVEL_NULL)
    {
        if(battVol > BATT_VOL_100)
        {
            battPara.battLevel = BATT_LEVEL_100;
        }
        else if(battVol >= BATT_VOL_75 && battVol < BATT_VOL_100)
        {
            battPara.battLevel = BATT_LEVEL_75;
        }
        else if(battVol >= BATT_VOL_50 &&  battVol < BATT_VOL_75)
        {
            battPara.battLevel = BATT_LEVEL_50;
        }
        else if(battVol >= BATT_VOL_25 &&  battVol < BATT_VOL_50)
        {
            battPara.battLevel = BATT_LEVEL_25;
        }
        else if(battVol >= BATT_VOL_0 &&  battVol < BATT_VOL_25)
        {
            battPara.battLevel = BATT_LEVEL_5;
        }
        else
        {
            battPara.battLevel = BATT_LEVEL_0;
        }
    }
    else 
    {
        if(battPara.battLevel == BATT_LEVEL_100)
        {
            if(battVol < (BATT_VOL_100 - faultTolerantVal))
            {
                battPara.battLevel = BATT_LEVEL_75;
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_75)
        {
            if(battVol < (BATT_VOL_75 - faultTolerantVal))
            {
                battPara.battLevel = BATT_LEVEL_50;                
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_50)
        {
            if(battVol > (BATT_VOL_75 + faultTolerantVal))
            {
                battPara.battLevel = BATT_LEVEL_75;
            }
            else if(battVol < (BATT_VOL_50 - faultTolerantVal))
            {
                battPara.battLevel = BATT_LEVEL_25;                
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_25)
        {
            if(battVol > (BATT_VOL_50 + faultTolerantVal))
            {
                battPara.battLevel = BATT_LEVEL_50;
            }
            else if(battVol < (BATT_VOL_25 - faultTolerantVal))
            {
                battPara.battLevel = BATT_LEVEL_5;                
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_5)
        {
            if(battVol > (BATT_VOL_25 + faultTolerantVal))
            {
                battPara.battLevel = BATT_LEVEL_25;
            }
            else if(battVol < (BATT_VOL_0 - faultTolerantVal))
            {
                battPara.battLevel = BATT_LEVEL_0;                
            }
        }
        else if(battPara.battLevel == BATT_LEVEL_0)
        {
            if(battVol > (BATT_VOL_0 + faultTolerantVal))
            {
                battPara.battLevel = BATT_LEVEL_5;
            }
        }
    }

    return battPara.battLevel;
}

batt_level_t App_Batt_Get_Chg_State(void )
{
    return battPara.battLevel;
}

earbud_chg_state_t App_Earbud_Cal_Chg_State(uint16_t earbudCur )
{
    if(earbudCur  <= 7)
    {
        battPara.earbudChgState = EARBUD_CHG_STATE_DONE;
    }
    else if(earbudCur >= 300)
    {
        battPara.earbudChgState = EARBUD_CHG_STATE_OVERCUR;
    }
    else
    {
        battPara.earbudChgState = EARBUD_CHG_STATE_PROCESS;
    }

    return battPara.earbudChgState;
}

earbud_chg_state_t App_Earbud_Get_Chg_State(void )
{
    return battPara.earbudChgState;
}

uint8_t App_Usb_Get_State(void )
{
    return Drv_Usb_Get_State();
}



