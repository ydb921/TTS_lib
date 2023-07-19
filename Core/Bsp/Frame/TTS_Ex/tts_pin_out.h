/**
 * @file system.h
 * @author Lucky_DB(ydbdby921@gmail.com)
 * @brief 修复类型导致的意外并且自动算实际周期
 * @version 1.2
 * @date 2023-07-19
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __TTS_PIN_OUT_H
#define __TTS_PIN_OUT_H

#define Pin_Type unsigned short

#define TTS_PinProcTick (100U)
#define TTS_PinEND   0xFFFF  //结束标志
#define TTS_Pin_Create(z, x, y) TTS_Pin_TaskCreate(&x[z],z,y,sizeof (y),TTS_PinProcTick)
#define TTS_Pin_Create_Init(x, y) TTS_Pin_Init(x, (TTS_PinNoT_t)y, sizeof (x)/sizeof (TTS_Pin_TypeDef))

typedef void (*TTS_PinNoT_t)(Pin_Type Pin);

typedef struct
{
    Pin_Type Pin;
    Pin_Type Length;
    Pin_Type Run_Time;
    Pin_Type Run_Num;
    Pin_Type *Period;
} TTS_Pin_TypeDef;

/**
 * @brief 设置显示效果
 *
 * @param Pin_flg 显示效果的函数
 */
void TTS_Pin_TaskCreate(TTS_Pin_TypeDef *Task, Pin_Type Pin, Pin_Type *Period, Pin_Type Size, Pin_Type Clock);

/**
 * @brief Pin状态初始化
 *
 */
void TTS_Pin_Init(TTS_Pin_TypeDef *User_Pin, TTS_PinNoT_t User_TTS_PinNoT, Pin_Type Size);

void TTS_PinProc(void);

#endif /* __TTS_PIN_OUT_H */
