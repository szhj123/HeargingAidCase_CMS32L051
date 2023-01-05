/********************************************************
* @file       main.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "hal_cms32l051.h"

/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
uint16_t adcTmpBuf[32];

void Gpio_Init(void )
{
    //p136, hall detect, input
    PORT_Init(PORT13, PIN6, PULLUP_INPUT);
    //p124, led2, output
    //p123, led1, output
    //p122,
    //p121, usb detect, input    
    PORT_Init(PORT12, PIN4, OUTPUT);
    PORT_Init(PORT12, PIN3, OUTPUT);
    PORT_Init(PORT12, PIN1, INPUT);
    //p23, charge stat, input
    PORT_Init(PORT2, PIN3, PULLUP_INPUT);
    //p14, led3, output
    //p13, led4, output
    //p12, tx, output
    //p11, uv led, output
    //p10, en boost, output
    PORT_Init(PORT1, PIN4, OUTPUT);
    PORT_Init(PORT1, PIN3, OUTPUT);
    PORT_Init(PORT1, PIN2, OUTPUT);
    PORT_Init(PORT1, PIN1, OUTPUT);
    PORT_Init(PORT1, PIN0, OUTPUT);
    PORT_Init(PORT12, PIN1, INPUT);
}

void Tim40_Interval_Init(void )
{
    SystemCoreClockUpdate();
    
    CGC->PER0 |= CGC_PER0_TM40EN_Msk;    /* enables input clock supply */
    TM40->TPS0 = _0000_TM4_CKM3_fCLK_8 | _0000_TM4_CKM2_fCLK_1 | _00F0_TM4_CKM1_fCLK_15 | _0000_TM4_CKM0_fCLK_0; 

    /* stop specify channel */
    TM40->TT0 |= TM4_CHANNEL_0;
    
    /* clear interrupt flag */
    INTC_ClearPendingIRQ(TM00_IRQn);
    NVIC_ClearPendingIRQ(TM00_IRQn);
    /* Channel 0 is used as interval timer */
    TM40->TMR00 = _0000_TM4_CLOCK_SELECT_CKM0 | _0000_TM4_CLOCK_MODE_CKS | _0000_TM4_TRIGGER_SOFTWARE |
                  _0000_TM4_MODE_INTERVAL_TIMER | _0000_TM4_START_INT_UNUSED;
    TM40->TDR00 = SystemCoreClock/1000 - 1;
    TM40->TOE0 &= ~_0001_TM4_CH0_OUTPUT_ENABLE;
    /* enable interrupt */
    INTC_EnableIRQ(TM00_IRQn);

    TM40->TS0 |= TM4_CHANNEL_0;
}

void Adc_Init(void )
{
    ADC_Init();
}

uint16_t Adc_Get_Val(adc_channel_t  channel )
{
    ADC_Converse(channel, sizeof(adcTmpBuf)/sizeof(uint16_t ), adcTmpBuf);

    return ADC_MidAvg_Filter(adcTmpBuf, sizeof(adcTmpBuf)/sizeof(uint16_t ));
}

