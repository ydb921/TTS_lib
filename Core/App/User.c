#include "User.h"
/* 核心任务句柄 */

void Debug(void)
{
    HAL_GPIO_TogglePin(Led_Green_GPIO_Port, Led_Green_Pin);
}

void Debug1(void)
{
    HAL_GPIO_TogglePin(Led_Red_GPIO_Port, Led_Red_Pin);
}

void User_Create_task(void)
{
    /** Task Creation **/
    if (TTS_TaskCreation(OS_TASK_Pin, Debug, 500, OS_RUN) != OS_RUN)
        Error_Handler();
    if (TTS_TaskCreation(OS_TASK_Proc, Debug1, 500, OS_RUN) != OS_RUN)
        Error_Handler();
}

void User_Bsp_Init(void)
{
    HAL_Delay(100);//等待系统稳定运行
    /** Task Init **/
    TTS_TaskInit(OS_TASK_SUM);
    /** Queue Configuration **/
}