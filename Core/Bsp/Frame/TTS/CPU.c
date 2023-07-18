#include "CPU.h"
/**
 * 操作系统通用延迟函数(推荐)
 * @param nTime
 */
void Delay_us(uint32_t nTime)
{
    uint32_t told = SysTick->VAL, tnow,
        reload = SysTick->LOAD, tcnt = 0;
    uint32_t ticks = nTime * (Config_CPU_CLOCK_HZ / 1000000);
    while (1) {
        tnow = SysTick->VAL;          //获取当前数值寄存器值
        if (tnow != told)              //当前值不等于开始值说明已在计数
        {
            if (tnow < told)             //当前值小于开始数值，说明未计到0
                tcnt += told - tnow;     //计数值=开始值-当前值
            else                  //当前值大于开始数值，说明已计到0并重新计数
                tcnt += reload - tnow + told;   //计数值=重装载值-当前值+开始值  （已从开始值计到0）
            told = tnow;                //更新开始值
            if (tcnt >= ticks)break;     //时间超过/等于要延迟的时间,则退出.
        }
    }
}
/**
 * 操作系统通用延迟函数
 * @param nTime
 */
void CPU_Delay_us(uint32_t nTime)
{
    uint32_t told = SysTick->VAL, tnow,
        reload = SysTick->LOAD, tcnt = 0;
    uint32_t ticks = nTime * (Config_CPU_CLOCK_HZ / 1000000);
    while (1) {
        tnow = SysTick->VAL;          //获取当前数值寄存器值
        if (tnow != told)              //当前值不等于开始值说明已在计数
        {
            if (tnow < told)             //当前值小于开始数值，说明未计到0
                tcnt += told - tnow;     //计数值=开始值-当前值
            else                  //当前值大于开始数值，说明已计到0并重新计数
                tcnt += reload - tnow + told;   //计数值=重装载值-当前值+开始值  （已从开始值计到0）
            told = tnow;                //更新开始值
            if (tcnt >= ticks)break;     //时间超过/等于要延迟的时间,则退出.
        }
    }
}

/**
 * @brief 系统时钟初始化
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
        *pSta = hal_getprimask(); //保存中断状态
        __disable_irq();          //关闭CPU总中断
    }
    else if (cmd == CPU_EXIT_CRITICAL) {
        if (*pSta)
            __enable_irq(); //中断打开
        else
            __disable_irq(); //中断关闭
    }
}

void hal_CPUInit(void)
{
    Hal_CoreClockInit();
    TTS_CPUInterruptCBSRegister(CPU_Critical_Control);
}
