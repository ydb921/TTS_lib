#ifndef __BSP_USER_BUTTON_H
#define __BSP_USER_BUTTON_H
#include "main.h"

typedef enum
{
    Button_Up,
    Button_0,
    Button_1,
    Button_SUM
} Button_TypeDef; // Button_Custom

/**
 * ∞¥≈•≥ı ºªØ
 * @param pCBS
 */
void TTS_ButtonInit(Button_Event_CallBack_t pCBS);

#endif /* __BSP_USER_BUTTON_H */
