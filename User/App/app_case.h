#ifndef _APP_CASE_H
#define _APP_CASE_H

#include "drv_timer.h"
#include "drv_task.h"
#include "drv_case.h"
#include "drv_event.h"

#define CMD_CASE_OPEN                 150 //ms
#define CMD_CASE_CLOSE                300 //ms
#define CMD_TWS_PAIRING               450 //ms

#define COM_TX_IDLE                   0
#define COM_TX_BUSY                   (!COM_TX_IDLE)

typedef enum
{
    COM_STATE_TX_INIT = 0,
    COM_STATE_TX_HIGH,
    COM_STATE_TX_LOW,
    COM_STATE_TX_EXIT
}com_state_t;


typedef struct _com_para_t
{
    uint8_t  timer;
    com_state_t comState;
    uint16_t lowTime;
    uint16_t delayCnt;
    uint8_t  txCnt;
}com_para_t;

void App_Case_Init(void );
uint8_t App_Case_Get_State(void );
void App_Com_Tx_Cmd(uint16_t lowTime );

#endif 

