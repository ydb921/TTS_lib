/**
 * @file system.h
 * @author Lucky_DB(ydbdby921@gmail.com)
 * @brief �򻯿�ܴ������̣��Ż����ʹ��
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


#define Config_CPU_CLOCK_HZ ((uint32_t)SystemCoreClock)//ϵͳʱ��72Mhz
#define Config_TICK_RATE_HZ (1000U)// OSϵͳ�����жϵ�Ƶ�ʡ���һ���жϵĴ�����ÿ���ж�OS��������������
#define delay_ms(x)  Delay_ms(x)
#define delay_us(x)  Delay_us(x)
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)//��Բ�ͬ�ı��������ò�ͬ��stdint.h�ļ�

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
    OS_SLEEP,           //��������ģʽ
    OS_RUN,                 //��������
    OS_Pause,           //������ͣ
} TTS_TaskStatus_t;

/**ϵͳ������**/
typedef struct
{
    void (*task)(void);           //������ָ��
    TTS_TaskStatus_t RunFlag; //��������״̬
    SystemTick_t RunPeriod;   //�������Ƶ��
    SystemTick_t RunTimer;    //������ȼ�ʱ��
} TTS_Task_t;

//CPU�жϿ���ָ��
typedef void (*CPUInterrupt_t)(CPU_EA_t cmd, uint8_t *pSta);

typedef void (*TTS_FUNC_t)(void);

/**
 * ע������ж�
 * @param CBS CPU�жϿ��ƻص�����ָ��
 */
void TTS_CPUInterruptCBSRegister(CPUInterrupt_t CBS);

/**
 *
 * @param Sum �����ʼ������
 */
void TTS_TaskInit(unsigned char Sum);

/**
 * ���ݾ����������
 * @param ID ������
 * @param Proc ������
 * @param Period �������ʱ��
 * @param Flag Ĭ������״̬
 * @return �����Ƿ��������
 */
TTS_TaskStatus_t TTS_TaskCreation(SystemSize_t ID, TTS_FUNC_t Proc,
                                  SystemTick_t Period, TTS_TaskStatus_t Flag);

/**
 * ��������
 * @param Proc ������
 * @param Period �������ʱ��
 * @return �����Ƿ��Խ�����
 */
TTS_TaskStatus_t TTS_IdleTaskCreation(TTS_FUNC_t Proc, SystemTick_t Period);

/**
 * д�뵱ǰ�������Ƶ��
 * @param Period �������Ƶ��
 */
_Bool TTS_CurrentTask_WritePeriod(SystemTick_t Period);

/**
 * д��ָ���������Ƶ��
 * @param Id ������
 * @param Period �������Ƶ��
 */
void TTS_Task_WritePeriod(SystemSize_t Id, SystemTick_t Period);

/**
 * @brief ��ȡ��ǰ�������Ƶ��
 *
 * @return SystemTick_t ��ǰ�������Ƶ��
 */
SystemTick_t TTS_CurrentTask_ReadPeriod(void);

/**
 * @brief ��ȡ��ǰ���������
 * @return ��ǰ���������
 */
SystemTick_t TTS_CurrentTask_ReadTimer(void);

/**
 * @brief ��ȡ��ǰ�������Ƶ��
 *
 * @return SystemTick_t ��ǰ�������Ƶ��
 */
SystemTick_t TTS_Task_ReadPeriod(SystemSize_t Id);

/**
 * @brief ��ȡ��ǰ���������
 * @return ��ǰ���������
 */
SystemTick_t TTS_Task_ReadTimer(SystemSize_t Id);

/**
 * �޸ĵ�ǰ����״̬
 * @param Id ������
 * @param Value ����״ֵ̬
 */
void TTS_SetStatus(SystemSize_t Id, TTS_TaskStatus_t Value);

void CPU_Delay(uint32_t nTime);

void Delay_ms(uint32_t nTime);

void CPU_Delay_us(uint32_t nTime);

void Delay_us(uint32_t nTime);

/*--------------������ú���--------------*/
void TSS_SysTickHandler(void);

void TTS_Start(void);
/*--------------END---------------------*/
/*--------------�������չ����------------*/


void TTS_TaskGetUp(SystemSize_t Id);

void TTS_TaskGetSleep(SystemSize_t Id);
/*--------------END---------------------*/
#endif /* __BSP_LED_H */
