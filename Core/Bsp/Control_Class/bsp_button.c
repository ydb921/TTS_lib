
#include "bsp_button.h"

static TTS_Button_TypeDef Button[Button_SUM];

/**
 * @brief 读取独立按键的GPIO电平
 *
 * @param Key 第几个按键
 * @return _Bool 返回是否按下
 */
_Bool GPIO_Read(unsigned char Button_Value)
{
    switch (Button_Value) {
        case Button_Up: {
            return HAL_GPIO_ReadPin(Button_Up_GPIO_Port, Button_Up_Pin);
        }
        case Button_0: {
            return !HAL_GPIO_ReadPin(Button_0_GPIO_Port, Button_0_Pin);
        }
        case Button_1: {
            return !HAL_GPIO_ReadPin(Button_1_GPIO_Port, Button_1_Pin);
        }
        default: {
            Error_Handler();
            return 0;
        }
    }
}

void TTS_ButtonInit(Button_Event_CallBack_t pCBS)
{
    Button_RestoreDefault(Button, Button_Press_double_Time, Button_ScanTime, 0, Button_SUM);
    Button_Init(Button, pCBS, (GPIO_Read_CallBack_t) GPIO_Read);
    Button_LongPressInterval(Button_Press_Long_Time, Button_Press_Continue_Time);
}
