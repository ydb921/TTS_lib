#include "User.h"
/*�c������*/
#include "User_Motor.h"
/*�f�h����*/
#include "User_Spcp.h"
/*�@ʾ���a*/
#include "User_Display.h"
/*ݔ�����*/
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
    HAL_Delay(100);//�ȴ�ϵͳ�ȶ�����
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