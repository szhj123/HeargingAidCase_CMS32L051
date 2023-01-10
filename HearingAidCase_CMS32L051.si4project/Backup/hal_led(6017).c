/********************************************************
* @file       hal_led.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_led.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/

void Hal_Led_Init(void )
{
    Gpio_Init();
}

void Hal_Led_Off(PORT_Typedef port, PIN_TypeDef pin )
{
    PORT_SetBit(port, pin);
}

void Hal_Led_On(PORT_Typedef port, PIN_TypeDef pin )
{
    PORT_ClrBit(port, pin);
}

