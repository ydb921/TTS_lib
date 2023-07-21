/**
 * @file bsp_Button.c
 * @author DB (ydbdby921@gmail.com)
 * @brief �����������
 * @version 0.1
 * @date 2021-08-14
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef _SYSTEM_BUTTON_H
#define _SYSTEM_BUTTON_H

#define Button_Type unsigned short int

//ɨ�谴���Ķ�ʱ��Tick,��Button_Scant_TickΪ��λ
#define TTS_ButtonProcTick (20U)
//��������ʱ��,��10msΪTick,2=20ms //20ms
#define Button_ScanTime (2)
//˫�����ʱ��
#define Button_Press_double_Time (6)
//��������ʱ��
#define Button_Press_Long_Time (1000 / TTS_ButtonProcTick)
//�����������ʱ��
#define Button_Press_Continue_Time (1000 / TTS_ButtonProcTick)

#define Button_TimerSet(x, y, z)  Button_RestoreDefault(x, y, z, 0, sizeof(x)/sizeof (TTS_Button_TypeDef))

// �����ڲ�������
typedef enum
{
    Button_Step_Wait = 0U,            //�ȴ�����
    Button_Step_Click = 1U,            //��������
    Button_Step_Long_Press = 2U,       //����
    Button_Step_Continuous_Press = 3U, //��������
} Button_Step_TypeDef;

typedef enum
{
    /* �������� */
    Button_IDLE,
    /* ����ȷ�� */
    Button_Click,
    /* �����ͷ� */
    Button_Click_Release,
    /* ����˫��ȷ�� */
    Button_Dblclick,
    /* ����˫���ͷ� */
    Button_DblclickRelease,
    /* ����ȷ�� */
    Button_Long_Press,
    /* �������� */
    Button_Long_Press_Continuous,
    /* �����ͷ� */
    Button_Long_Press_Release
} Button_Event_TypeDef;

typedef struct
{
    Button_Type Filtering;//Button�˲�
    Button_Type DblclickTick;
    Button_Type ScanTimer;//Button�˲�
    Button_Type DblclickTimer;//�������
    Button_Step_TypeDef Step;//��ǰ����
} TTS_Button_TypeDef;

typedef void (*Button_Event_CallBack_t)(Button_Type Buttons, Button_Event_TypeDef State);

typedef _Bool (*GPIO_Read_CallBack_t)(unsigned char Button_Value);

/**
 * Button Init
 * @param pCBS Button����
 * @param cCBS �ײ㷴��
 */
void Button_Init(TTS_Button_TypeDef *User_Button, Button_Event_CallBack_t pCBS, GPIO_Read_CallBack_t cCBS);

/**
 * �޸ĳ�����������
 * @param Timer ����ʱ����
 * @param IntervalTimer ��������ʱ����
 */
void Button_LongPressInterval(Button_Type Timer, Button_Type IntervalTimer);

/**
 * ���ð�����������
 * @param pCBS ����
 */
void Button_ScanCBSRegister(Button_Event_CallBack_t pCBS);

/**
 * @brief ����ɨ��
 *
 */
void TTS_ButtonProc(void); // Button_task
/**
 * �ָ���ʼ����
 * @param Button ��
 * @param Start ��ʼλ��
 * @param Stop ֹͣλ��
 */
void Button_RestoreDefault(TTS_Button_TypeDef *Button, Button_Type DblclickTimer,
                           Button_Type ScanTimer, Button_Type Start, Button_Type Stop);
#endif
