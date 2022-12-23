/********************************************************
* @file       drv_task.c
* @author     szhj13
* @version    V1.0
* @date       2022-05-18
* @brief      the start address of program
**********************************************************
* @Modify

**********************************************************/

/* Includes ---------------------------------------------*/
#include "drv_task.h"
/* Private typedef --------------------------------------*/
/* Private define ---------------------------------------*/
/* Private macro ----------------------------------------*/
/* Private function -------------------------------------*/
static void Drv_Task_Isr_Callback(void );
/* Private variables ------------------------------------*/
task_ctrl_block_t *taskHead = NULL;

void Drv_Task_Init(void )
{
    Hal_Task_Init();    

    Hal_Task_Regist_Isr_Callback(Drv_Task_Isr_Callback);
}

static task_ctrl_block_t * Drv_Task_Regist(void (*handler)(void *), uint16_t ticks, uint16_t period, void *arg )
{
    task_ctrl_block_t *task = (task_ctrl_block_t *)malloc(sizeof(task_ctrl_block_t));

    if(task == NULL)
    {
        return NULL;
    }

    task->handler = handler;
    task->arg = arg;
    task->ticks = ticks;
    task->period = period;
    if(ticks)
    {
        task->state = TASK_SUSPEND;
    }
    else
    {
        task->state = TASK_READY;
    }

    task->prev = NULL;
    task->next = NULL;

    if(taskHead == NULL)
    {
        taskHead = task;
    }
    else
    {
        task_ctrl_block_t *pTask = taskHead;

        while(pTask->next != NULL)
        {
            pTask = pTask->next;
        }

        pTask->next = task;
        task->prev = pTask;
    }

    return task;
}

task_ctrl_block_t * Drv_Task_Regist_Oneshot(void (*handler)(void *), uint16_t ticks, void *arg )
{
    return Drv_Task_Regist(handler, ticks, 0, arg );
}

task_ctrl_block_t * Drv_Task_Regist_Period(void (*handler)(void *), uint16_t ticks, uint16_t period, void *arg )
{
    return Drv_Task_Regist(handler, ticks, period, arg );
}

uint8_t Drv_Task_Delay(task_ctrl_block_t *task, uint16_t ticks )
{
    if(task == NULL)
    {
        return TASK_ERR;
    }

    task->ticks = ticks;
    task->state = TASK_SUSPEND;

    return TASK_OK;
}

uint8_t Drv_Task_Delete(task_ctrl_block_t *task )
{
    if(task == NULL)
    {
        return TASK_ERR;
    }

    if(task == taskHead)
    {
        if(taskHead->next != NULL)
        {
            taskHead = taskHead->next;
            taskHead->prev = NULL;
        }
        else
        {
            taskHead = NULL;
        }
    }
    else if(task->next == NULL)
    {
        task->prev->next = NULL;
    }
    else
    {
        task->prev->next = task->next;
        task->next->prev = task->prev;
    }

    task->handler = NULL;
    task->arg = NULL;
    task->ticks = 0;
    task->period = 0;
    task->state = TASK_IDLE;
    task->prev = NULL;
    task->next = NULL;
    
    free(task);

    task = NULL;

    return TASK_OK;
}

static void Drv_Task_Isr_Callback(void )
{
    task_ctrl_block_t *pTask = taskHead;

    while(pTask != NULL)
    {
        if(pTask->state == TASK_SUSPEND)
        {
            if(pTask->ticks)
            {
                pTask->ticks--;
            }

            if(pTask->ticks == 0)
            {
                pTask->state = TASK_READY;
            }
        }

        pTask = pTask->next;
    }
}

void Drv_Task_Scheduler(void )
{
    task_ctrl_block_t *pTask = taskHead;

    while(pTask != NULL)
    {
        if(pTask->state == TASK_READY)
        {
            if(pTask->handler != NULL)
            {
                pTask->handler(pTask->arg);
            
                if(pTask->period)
                {
                    if(pTask->state == TASK_READY)
                    {
                        pTask->ticks = pTask->period;
                        pTask->state = TASK_SUSPEND;
                    }
                }
                else
                {
                    pTask = pTask->next;
                    
                    Drv_Task_Delete(pTask->prev);

                    return ;
                }
            }
        }

        pTask = pTask->next;
    }
}




