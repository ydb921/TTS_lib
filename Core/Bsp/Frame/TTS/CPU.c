#include "CPU.h"
/**
 * ����ϵͳͨ���ӳٺ���(�Ƽ�)
 * @param nTime
 */
void Delay_us(uint32_t nTime)
{
    uint32_t told = SysTick->VAL, tnow,
        reload = SysTick->LOAD, tcnt = 0;
    uint32_t ticks = nTime * (Config_CPU_CLOCK_HZ / 1000000);
    while (1) {
        tnow = SysTick->VAL;          //��ȡ��ǰ��ֵ�Ĵ���ֵ
        if (tnow != told)              //��ǰֵ�����ڿ�ʼֵ˵�����ڼ���
        {
            if (tnow < told)             //��ǰֵС�ڿ�ʼ��ֵ��˵��δ�Ƶ�0
                tcnt += told - tnow;     //����ֵ=��ʼֵ-��ǰֵ
            else                  //��ǰֵ���ڿ�ʼ��ֵ��˵���ѼƵ�0�����¼���
                tcnt += reload - tnow + told;   //����ֵ=��װ��ֵ-��ǰֵ+��ʼֵ  ���Ѵӿ�ʼֵ�Ƶ�0��
            told = tnow;                //���¿�ʼֵ
            if (tcnt >= ticks)break;     //ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
        }
    }
}
/**
 * ����ϵͳͨ���ӳٺ���
 * @param nTime
 */
void CPU_Delay_us(uint32_t nTime)
{
    uint32_t told = SysTick->VAL, tnow,
        reload = SysTick->LOAD, tcnt = 0;
    uint32_t ticks = nTime * (Config_CPU_CLOCK_HZ / 1000000);
    while (1) {
        tnow = SysTick->VAL;          //��ȡ��ǰ��ֵ�Ĵ���ֵ
        if (tnow != told)              //��ǰֵ�����ڿ�ʼֵ˵�����ڼ���
        {
            if (tnow < told)             //��ǰֵС�ڿ�ʼ��ֵ��˵��δ�Ƶ�0
                tcnt += told - tnow;     //����ֵ=��ʼֵ-��ǰֵ
            else                  //��ǰֵ���ڿ�ʼ��ֵ��˵���ѼƵ�0�����¼���
                tcnt += reload - tnow + told;   //����ֵ=��װ��ֵ-��ǰֵ+��ʼֵ  ���Ѵӿ�ʼֵ�Ƶ�0��
            told = tnow;                //���¿�ʼֵ
            if (tcnt >= ticks)break;     //ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
        }
    }
}

/**
 * @brief ϵͳʱ�ӳ�ʼ��
 *
 */
static void Hal_CoreClockInit(void)
{
//	/* set reload register */
//	NVIC_SetPriority(SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
//	SysTick->VAL = 0UL;                                             /* Load the SysTick Counter Value */
//	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
//					SysTick_CTRL_TICKINT_Msk |
//					SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
    SysTick_Config(Config_CPU_CLOCK_HZ / Config_TICK_RATE_HZ);
}

// uint32_t __get_PRIMASK(void)
//{
//   uint32_t result=0;

//  __ASM volatile ("MRS %0, primask" : "=r" (result) );
//  return(result);
//}

static unsigned char hal_getprimask(void)
{
    return (!__get_PRIMASK());
}

void CPU_Critical_Control(CPU_EA_t cmd, unsigned char *pSta)
{
    if (cmd == CPU_ENTER_CRITICAL) {
        *pSta = hal_getprimask(); //�����ж�״̬
        __disable_irq();          //�ر�CPU���ж�
    }
    else if (cmd == CPU_EXIT_CRITICAL) {
        if (*pSta)
            __enable_irq(); //�жϴ�
        else
            __disable_irq(); //�жϹر�
    }
}

void hal_CPUInit(void)
{
    Hal_CoreClockInit();
    TTS_CPUInterruptCBSRegister(CPU_Critical_Control);
}
