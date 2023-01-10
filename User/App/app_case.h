#ifndef _APP_CASE_H
#define _APP_CASE_H

#include "drv_case.h"
#include "drv_event.h"

#define CMD_CASE_OPEN                 150 //ms
#define CMD_CASE_CLOSE                300 //ms
#define CMD_TWS_PAIRING               450 //ms

#define COM_TX_IDLE                   0
#define COM_TX_BUSY                   (!COM_TX_IDLE)

void App_Case_Init(void );
void App_Com_Tx_Cmd(uint16_t lowTime );

#endif 

