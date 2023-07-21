/**
 * @file bsp_Button.c
 * @author DB (ydbdby921@gmail.com)
 * @brief 按键处理程序
 * @version 0.1
 * @date 2021-08-14
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef _SYSTEM_BUTTON_H
#define _SYSTEM_BUTTON_H

#define Button_Type unsigned short int

//扫描按键的定时器Tick,以Button_Scant_Tick为单位
#define TTS_ButtonProcTick (20U)
//按键消抖时间,以10ms为Tick,2=20ms //20ms
#define Button_ScanTime (2)
//双击间隔时间
#define Button_Press_double_Time (6)
//连续长按时间
#define Button_Press_Long_Time (1000 / TTS_ButtonProcTick)
//持续长按间隔时间
#define Button_Press_Continue_Time (1000 / TTS_ButtonProcTick)

#define Button_TimerSet(x, y, z)  Button_RestoreDefault(x, y, z, 0, sizeof(x)/sizeof (TTS_Button_TypeDef))

// 按键内部检测过程
typedef enum
{
    Button_Step_Wait = 0U,            //等待按键
    Button_Step_Click = 1U,            //按键按下
    Button_Step_Long_Press = 2U,       //长按
    Button_Step_Continuous_Press = 3U, //持续按下
} Button_Step_TypeDef;

typedef enum
{
    /* 按键空闲 */
    Button_IDLE,
    /* 单击确认 */
    Button_Click,
    /* 单击释放 */
    Button_Click_Release,
    /* 按键双击确认 */
    Button_Dblclick,
    /* 按键双击释放 */
    Button_DblclickRelease,
    /* 长按确认 */
    Button_Long_Press,
    /* 长按持续 */
    Button_Long_Press_Continuous,
    /* 长按释放 */
    Button_Long_Press_Release
} Button_Event_TypeDef;

typedef struct
{
    Button_Type Filtering;//Button滤波
    Button_Type DblclickTick;
    Button_Type ScanTimer;//Button滤波
    Button_Type DblclickTimer;//存活周期
    Button_Step_TypeDef Step;//当前进度
} TTS_Button_TypeDef;

typedef void (*Button_Event_CallBack_t)(Button_Type Buttons, Button_Event_TypeDef State);

typedef _Bool (*GPIO_Read_CallBack_t)(unsigned char Button_Value);

/**
 * Button Init
 * @param pCBS Button反馈
 * @param cCBS 底层反馈
 */
void Button_Init(TTS_Button_TypeDef *User_Button, Button_Event_CallBack_t pCBS, GPIO_Read_CallBack_t cCBS);

/**
 * 修改长按反馈周期
 * @param Timer 长按时间间隔
 * @param IntervalTimer 长按反馈时间间隔
 */
void Button_LongPressInterval(Button_Type Timer, Button_Type IntervalTimer);

/**
 * 设置按键反馈程序
 * @param pCBS 程序
 */
void Button_ScanCBSRegister(Button_Event_CallBack_t pCBS);

/**
 * @brief 按键扫描
 *
 */
void TTS_ButtonProc(void); // Button_task
/**
 * 恢复初始设置
 * @param Button 键
 * @param Start 开始位置
 * @param Stop 停止位置
 */
void Button_RestoreDefault(TTS_Button_TypeDef *Button, Button_Type DblclickTimer,
                           Button_Type ScanTimer, Button_Type Start, Button_Type Stop);
#endif
