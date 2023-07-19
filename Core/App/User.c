#include "User.h"

void Debug(void)
{

}

void User_Create_task(void)
{
    /** Task Creation **/
    if (TTS_TaskCreation(OS_TASK_Pin, Debug, 500, OS_RUN) != OS_RUN)
        Error_Handler();
    if (TTS_TaskCreation(OS_TASK_Proc, TTS_PinProc, TTS_PinProcTick, OS_RUN) != OS_RUN)
        Error_Handler();
}

void User_Bsp_Init(void)
{
    HAL_Delay(100);//等待系统稳定运行
    /** Task Init **/
    TTS_TaskInit(OS_TASK_SUM);
    /** Queue Configuration **/
    TTS_PinInit();
}