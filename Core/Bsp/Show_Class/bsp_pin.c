#include "bsp_pin.h"

static TTS_Pin_TypeDef User_Pin[Pin_SUM];

Pin_Type Led_Dark[] = {500, 500, TTS_PinEND};

Pin_Type Led_Light[] = {100, 100, TTS_PinEND};

Pin_Type Led_Blink1[] = {100, 100};

Pin_Type Led_Blink2[] = {100, 100, 2100, 100,};

void HAL_PinStatus(Pin_Type Num)
{
    switch (Num) {
        case Led_Green: HAL_GPIO_TogglePin(Led_Green_GPIO_Port, Led_Green_Pin);
            break;
        case Led_Red: HAL_GPIO_TogglePin(Led_Red_GPIO_Port, Led_Red_Pin);
            break;
        default: Error_Handler();
            break;
    }
}

void TTS_PinInit(void)
{
    TTS_Pin_Create(Led_Green, User_Pin, Led_Blink1);
//    TTS_Pin_Create(Led_Red, User_Pin, Led_Blink2);
    TTS_Pin_Create_Init(User_Pin, HAL_PinStatus);
}
