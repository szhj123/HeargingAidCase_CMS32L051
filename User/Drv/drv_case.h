#ifndef _DRV_CASE_H
#define _DRV_CASE_H

#include "hal_case.h"

#define CASE_STATE_CLOSE                 0
#define CASE_STATE_OPEN                  1

void Drv_Case_Init(hal_isr_callback_t callback );
uint8_t Drv_Case_Get_State(void );


#endif 

