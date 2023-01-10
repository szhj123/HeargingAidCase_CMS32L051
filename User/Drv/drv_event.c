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
#include "drv_event.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
/* Private variables ------------------------------------*/
msg_queue_t msgQueue;

void Drv_Msg_Put(uint8_t event, uint8_t *buf, uint8_t len )
{
    uint8_t i;
    
    msgQueue.buf[msgQueue.rear].event = event;

    if(buf != NULL)
    {
        for(i=0;i<len;i++)
        {
            msgQueue.buf[msgQueue.rear].buf[i] = buf[i];
        }
    }

    msgQueue.buf[msgQueue.rear].len = len;

    msgQueue.rear = (msgQueue.rear + 1) % MSG_QUEUE_MAX_LEN;
}

uint8_t Drv_Msg_Get(msg_t *msg )
{
    if(msgQueue.head != msgQueue.rear)
    {
        *msg = msgQueue.buf[msgQueue.head];

        msgQueue.head = (msgQueue.head + 1) % MSG_QUEUE_MAX_LEN;

        return MSG_OK;
    }

    return MSG_ERR;
}

