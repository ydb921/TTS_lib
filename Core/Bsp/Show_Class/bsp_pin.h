#ifndef __BSP_USER_PIN_H
#define __BSP_USER_PIN_H

#include "main.h"

typedef enum
{
    Led_Green,
    Led_Red,
    Pin_SUM
} TTS_Pin_Status; // PIN∂®“Â

void TTS_PinInit(void);

#endif /* __BSP_USER_PIN_H */
