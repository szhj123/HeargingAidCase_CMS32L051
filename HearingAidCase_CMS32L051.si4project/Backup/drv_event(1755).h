#ifndef _DRV_EVENT_H
#define _DRV_EVENT_H

#include "hal_cms32l051.h"

#define MSG_DATA_MAX_LEN                 8
#define MSG_QUEUE_MAX_LEN                8

#define MSG_OK                           0
#define MSG_ERR                          (!MSG_OK)

typedef struct _msg_t
{
    uint8_t event;
    uint8_t buf[MSG_DATA_MAX_LEN];
    uint8_t len;
}msg_t;

typedef struct _msg_queue_t
{
    msg_t buf[MSG_QUEUE_MAX_LEN];

    uint8_t head;
    uint8_t rear;
}msg_queue_t;

void Drv_Msg_Add(uint8_t event, uint8_t *buf, uint8_t len );
uint8_t Drv_Msg_Get(msg_t *msg );


#endif 

