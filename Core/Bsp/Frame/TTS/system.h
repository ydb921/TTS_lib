/**
 * @file system.h
 * @author Lucky_DB(ydbdby921@gmail.com)
 * @brief 简化框架创建过程，优化框架使用
 * @version 2.4
 * @date 2023-07-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __SYSTEM_H
#define __SYSTEM_H

typedef enum
{
    OS_TASK_Proc,
    OS_TASK_Pin,
    OS_TASK_SUM,
} OS_Task_ID_TypeDef;


#define Config_CPU_CLOCK_HZ ((uint32_t)SystemCoreClock)//系统时钟72Mhz
#define Config_TICK_RATE_HZ (1000U)// OS系统节拍中断的频率。即一秒中断的次数，每次中断OS都会进行任务调度
#define delay_ms(x)  Delay_ms(x)
#define delay_us(x)  Delay_us(x)
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)//针对不同的编译器调用不同的stdint.h文件

#include <stdint.h>

extern uint32_t SystemCoreClock;

#endif

// #define _Bool Bool
typedef unsigned int SystemTick_t;

typedef unsigned char SystemSize_t;

typedef enum
{
    CPU_ENTER_CRITICAL,
    CPU_EXIT_CRITICAL,
} CPU_EA_t;

typedef enum
{
    OS_SLEEP,           //任务休眠模式
    OS_RUN,                 //任务运行
    OS_Pause,           //任务暂停
} TTS_TaskStatus_t;

/**系统任务句柄**/
typedef struct
{
    void (*task)(void);           //任务函数指针
    TTS_TaskStatus_t RunFlag; //任务运行状态
    SystemTick_t RunPeriod;   //任务调度频率
    SystemTick_t RunTimer;    //任务调度计时器
} TTS_Task_t;

//CPU中断控制指针
typedef void (*CPUInterrupt_t)(CPU_EA_t cmd, uint8_t *pSta);

typedef void (*TTS_FUNC_t)(void);

/**
 * 注册控制中断
 * @param CBS CPU中断控制回调函数指针
 */
void TTS_CPUInterruptCBSRegister(CPUInterrupt_t CBS);

/**
 *
 * @param Sum 句柄初始化数量
 */
void TTS_TaskInit(unsigned char Sum);

/**
 * 根据句柄创建任务
 * @param ID 任务句柄
 * @param Proc 任务函数
 * @param Period 任务调度时间
 * @param Flag 默认任务状态
 * @return 任务是否可以运行
 */
TTS_TaskStatus_t TTS_TaskCreation(SystemSize_t ID, TTS_FUNC_t Proc,
                                  SystemTick_t Period, TTS_TaskStatus_t Flag);

/**
 * 创建任务
 * @param Proc 任务函数
 * @param Period 任务调度时间
 * @return 任务是否自建运行
 */
TTS_TaskStatus_t TTS_IdleTaskCreation(TTS_FUNC_t Proc, SystemTick_t Period);

/**
 * 写入当前任务调度频率
 * @param Period 任务调度频率
 */
_Bool TTS_CurrentTask_WritePeriod(SystemTick_t Period);

/**
 * 写入指定任务调度频率
 * @param Id 任务句柄
 * @param Period 任务调度频率
 */
void TTS_Task_WritePeriod(SystemSize_t Id, SystemTick_t Period);

/**
 * @brief 读取当前任务调度频率
 *
 * @return SystemTick_t 当前任务调度频率
 */
SystemTick_t TTS_CurrentTask_ReadPeriod(void);

/**
 * @brief 读取当前任务计数器
 * @return 当前任务计数器
 */
SystemTick_t TTS_CurrentTask_ReadTimer(void);

/**
 * @brief 读取当前任务调度频率
 *
 * @return SystemTick_t 当前任务调度频率
 */
SystemTick_t TTS_Task_ReadPeriod(SystemSize_t Id);

/**
 * @brief 读取当前任务计数器
 * @return 当前任务计数器
 */
SystemTick_t TTS_Task_ReadTimer(SystemSize_t Id);

/**
 * 修改当前任务状态
 * @param Id 任务句柄
 * @param Value 任务状态值
 */
void TTS_SetStatus(SystemSize_t Id, TTS_TaskStatus_t Value);

void CPU_Delay(uint32_t nTime);

void Delay_ms(uint32_t nTime);

void CPU_Delay_us(uint32_t nTime);

void Delay_us(uint32_t nTime);

/*--------------必须调用函数--------------*/
void TSS_SysTickHandler(void);

void TTS_Start(void);
/*--------------END---------------------*/
/*--------------任务的扩展操作------------*/


void TTS_TaskGetUp(SystemSize_t Id);

void TTS_TaskGetSleep(SystemSize_t Id);
/*--------------END---------------------*/
#endif /* __BSP_LED_H */
