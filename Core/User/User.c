#include "User.h"
/*點擊控制*/
#include "User_Motor.h"
/*協議解析*/
#include "User_Spcp.h"
/*顯示代碼*/
#include "User_Display.h"
/*輸入控制*/
#include "User_key.h"

void UserProc(void)
{

}

void User_Create_task(void)
{
    /** Task Creation **/
    if (TTS_TaskCreation(OS_TASK_Proc, UserProc, 500, OS_RUN) != OS_RUN)
        Error_Handler();
    if (TTS_TaskCreation(OS_TASK_Pin, TTS_PinProc, TTS_PinProcTick, OS_RUN) != OS_RUN)
        Error_Handler();
    if (TTS_TaskCreation(OS_TASK_Button, TTS_ButtonProc, TTS_ButtonProcTick, OS_RUN) != OS_RUN)
        Error_Handler();
}

void User_Bsp_Init(void)
{
    HAL_Delay(100);//等待系统稳定运行
    /* Task Init */
    TTS_TaskInit(OS_TASK_SUM);
    /* Buzzer&Led Init */
    TTS_PinInit();
    /* Button Init */
    TTS_ButtonInit(Button_EventCallBack);
    /* Queue Configuration */
    /* Spcp Init */
    /* Motor Init */
    /* Time Init */
}