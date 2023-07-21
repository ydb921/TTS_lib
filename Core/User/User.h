//
// Created by dby on 2023/7/12.
//

#ifndef USER_H
#define USER_H

#include "main.h"
#include "../Bsp/Show_Class/bsp_pin.h"

/* ºËÐÄÈÎÎñ¾ä±ú */
typedef enum
{
    OS_TASK_Pin,
    OS_TASK_Button,
    OS_TASK_Proc,
    OS_TASK_SUM,
} OS_TaskID_t;

/**
 * @brief Task Start
 *
 */
void User_Create_task(void);
/**
 * @brief Handle the underlying architecture creation
 *
 */
void User_Bsp_Init(void);

#endif //USER_H
