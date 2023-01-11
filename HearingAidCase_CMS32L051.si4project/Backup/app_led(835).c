/********************************************************
* @file       app_led.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "app_led.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void App_Led_Flash(void *arg );
/* Private variables ------------------------------------*/
led_para_t ledPara;

led_ctrl_block_t led1 = 
{
    .port = PORT12,
    .pin  = PIN3,
    .id   = 1
};

led_ctrl_block_t led2 = 
{
    .port = PORT12,
    .pin  = PIN4,
    .id   = 2
};

led_ctrl_block_t led3 = 
{
    .port = PORT1,
    .pin  = PIN4,
    .id   = 3
};

led_ctrl_block_t led4 = 
{
    .port = PORT1,
    .pin  = PIN3,
    .id   = 4
};

void App_Led_Init(void )
{
    Drv_Led_Init();

    App_Led_All_Off();

    ledPara.timer = TIMER_NULL;
}

void App_Led_All_Off(void )
{
    if(ledPara.timer != TIMER_NULL)
    {
        Drv_Timer_Delete(ledPara.timer);
        
        ledPara.timer = TIMER_NULL;
    }
    
    Drv_Led_Off(&led4);
    
    Drv_Led_Off(&led3);

    Drv_Led_Off(&led2);

    Drv_Led_Off(&led1);
}

void App_Led_All_On(void )
{
    Drv_Led_On(&led4);
    
    Drv_Led_On(&led3);

    Drv_Led_On(&led2);

    Drv_Led_On(&led1);
}

void App_Led_Bat_Unchg_Level_5(void )
{
    App_Led_All_Off();

    ledPara.timer = Drv_Timer_Regist_Period(App_Led_Flash, 0, 500, (void *)led1.id);
}   

void App_Led_Bat_Unchg_Level_25(void )
{
    App_Led_All_Off();

    Drv_Led_On(&led1);
}

void App_Led_Bat_Unchg_Level_50(void )
{
    App_Led_All_Off();

    Drv_Led_On(&led1);

    Drv_Led_On(&led2);
}

void App_Led_Bat_Unchg_Level_75(void )
{
    App_Led_All_Off();

    Drv_Led_On(&led1);

    Drv_Led_On(&led2);
    
    Drv_Led_On(&led3);
}

void App_Led_Bat_Unchg_Level_100(void )
{
    App_Led_All_On();
}

void App_Led_Bat_Chg_Level_5(void )
{
    App_Led_All_Off();

    ledPara.timer = Drv_Timer_Regist_Period(App_Led_Flash, 0, 500, (void *)led1.id);
}

void App_Led_Bat_Chg_Level_25(void )
{
    App_Led_All_Off();

    Drv_Led_On(&led1);

    ledPara.timer = Drv_Timer_Regist_Period(App_Led_Flash, 0, 500, (void *)led2.id);
}

void App_Led_Bat_Chg_Level_50(void )
{
    App_Led_All_Off();

    Drv_Led_On(&led1);

    Drv_Led_On(&led2);

    ledPara.timer = Drv_Timer_Regist_Period(App_Led_Flash, 0, 500, (void *)led3.id);
}

void App_Led_Bat_Chg_Level_75(void )
{
    App_Led_All_Off();

    Drv_Led_On(&led1);

    Drv_Led_On(&led2);
    
    Drv_Led_On(&led3);

    ledPara.timer = Drv_Timer_Regist_Period(App_Led_Flash, 0, 500, (void *)led4.id);
}

void App_Led_Bat_Chg_Level_100(void )
{
    if(ledPara.timer != TIMER_NULL)
    {
        Drv_Timer_Delete(ledPara.timer);
        
        ledPara.timer = TIMER_NULL;
    }
    
    App_Led_All_On();
}

void App_Led_Earbud_Chg_Done(void )
{
    App_Led_All_Off();
}

void App_Led_Bat_Chg(batt_level_t battLevel )
{
    switch(battLevel)
    {
        case BATT_LEVEL_100: App_Led_Bat_Chg_Level_100(); break;
        case BATT_LEVEL_75: App_Led_Bat_Chg_Level_75(); break;
        case BATT_LEVEL_50: App_Led_Bat_Chg_Level_50(); break;
        case BATT_LEVEL_25: App_Led_Bat_Chg_Level_25(); break;
        case BATT_LEVEL_5: App_Led_Bat_Chg_Level_5(); break;
        case BATT_LEVEL_0: App_Led_All_Off(); break;
        default: break;
    }
}

void App_Led_Bat_Unchg(batt_level_t battLevel )
{
    switch(battLevel)
    {
        case BATT_LEVEL_100: App_Led_Bat_Unchg_Level_100(); break;
        case BATT_LEVEL_75: App_Led_Bat_Unchg_Level_75(); break;
        case BATT_LEVEL_50: App_Led_Bat_Unchg_Level_50(); break;
        case BATT_LEVEL_25: App_Led_Bat_Unchg_Level_25(); break;
        case BATT_LEVEL_5: App_Led_Bat_Unchg_Level_5(); break;
        case BATT_LEVEL_0: App_Led_All_Off(); break;
        default: break;
    }
}

void App_Led_Light_5S_Callback(void *arg )
{
    if(App_Earbud_Get_Chg_State() == EARBUD_CHG_STATE_DONE)
    {
        App_Led_All_Off();
    }
}

void App_Led_Light_5S(batt_level_t battLevel )
{
    static uint8_t timer = TIMER_NULL;
    
    if(App_Usb_Get_State() == USB_STATE_PLUG_OUT)
    {
        App_Led_Bat_Unchg(battLevel);

        if(timer != TIMER_NULL)
        {
            Drv_Timer_Delete(timer);

            timer = TIMER_NULL;
        }

        timer = Drv_Timer_Regist_Oneshot(App_Led_Light_5S_Callback, 5000, NULL);
    }
}

static void App_Led_Flash(void *arg )
{
    led_ctrl_block_t led;

    if((uint32_t)arg == led1.id)
    {
        led = led1;
    }
    else if((uint32_t)arg == led2.id)
    {
        led = led2;
    }
    else if((uint32_t)arg == led3.id)
    {
        led = led3;
    }
    else if((uint32_t)arg == led4.id)
    {
        led = led4;
    }

    if(Drv_Led_Get_State(&led))
    {
        Drv_Led_Off(&led);
    }
    else
    {
        Drv_Led_On(&led);
    }
}



