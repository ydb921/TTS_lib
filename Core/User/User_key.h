#include "../Bsp/Control_Class/bsp_button.h"

void Button_EventCallBack(Button_Type Buttons, Button_Event_TypeDef State)
{
    if (State == Button_Click_Release) {
        switch (Buttons) {
            case Button_Up: {
                TTS_Task_WritePeriod(OS_TASK_Pin, 1000);
                break;
            }
            case Button_0: {
                TTS_Task_WritePeriod(OS_TASK_Pin, 500);
                break;
            }
            case Button_1: {
                TTS_Task_WritePeriod(OS_TASK_Pin, 50);
                break;
            }
        }
    }

}

