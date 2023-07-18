#ifndef __CPU_WHITE_HOUSE_H
#define __CPU_WHITE_HOUSE_H
/**
 * @file CPU.h
 * @author Lucky_DB(ydbdby921@gmail.com)
 * @brief ��Ҫ�����ȹ���ѡ���Ӧ�ͺŵ��ں˰汾��Lib�汾��֧���ںˣ�
 * @version 0.1
 * @date 2022-07-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "main.h"
#include "system.h"

#define  TTS_CPU_TmrRd()  *(__IO uint32_t *)0xE0001004
#define GET_CPU_ClkFreq()       (SystemCoreClock)

void hal_CPUInit(void);

#endif /* __CPU_WHITE_HOUSE_H */
