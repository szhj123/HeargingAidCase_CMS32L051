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
/* Private variables ------------------------------------*/


led_ctrl_block_t led1 = 
{
    .port = PORT12,
    .pin  = PIN3
};

led_ctrl_block_t led2 = 
{
    .port = PORT12,
    .pin  = PIN4
};

led_ctrl_block_t led3 = 
{
    .port = PORT1,
    .pin  = PIN4
};

led_ctrl_block_t led4 = 
{
    .port = PORT1,
    .pin  = PIN3
};

void App_Led_Init(void )
{
    Drv_Led_Init();

    App_Led_All_Off();
}

void App_Led_All_Off(void )
{
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

void App_Led_Unchg_Level_5(void )
{
    App_Led_All_Off();

}

