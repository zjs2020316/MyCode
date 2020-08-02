#ifndef _ZS_SYSTICK_H
#define _ZS_SYSTICK_H

#include "stm32f4xx.h"
#include "zs_led.h"

//zjs:相关函数声明
void Systick_Init(void);
void Delay_10us(__IO u32 nTime);
void Delay_xms(uint32_t xms);

void SystickTest(void);


#endif

