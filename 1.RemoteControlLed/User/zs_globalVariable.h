#ifndef _ZS_GLOBALVARIABLE_H
#define _ZS_GLOBALVARIABLE_H

#include "stdint.h"

#define BUZZ_DELAY_X5MS 15 //>>zjs:蜂鸣器，鸣叫时长
#define RECEIVE_SIZE 512 //>>zjs:接收数据的缓存大小

//>>zjs:蜂鸣器工作状态
typedef enum
{
	BUZZ_STOP,
	BUZZ_START=0x98
}BuzzStatus;

//>>zjs:蜂鸣器运行状态
typedef enum
{
	BUZZ_DISABLE,
	BUZZ_ENABLE
}BuzzRunStatus;

//>>zjs:声明为外部变量，供其它.c文件调用
extern uint32_t systick_1ms;
extern uint32_t r_keyPressDelay_5ms;
extern uint16_t LedToggleDelay_5ms;
extern uint16_t LedToggleDelay2_5ms;
extern uint16_t buzzDelay_5ms;
extern BuzzStatus buzz_flag;
extern BuzzRunStatus buzzRun_flag;

extern uint8_t ReceiveArray[RECEIVE_SIZE];
extern uint16_t ReveiveIndex;
extern uint8_t ReceiveFlag;
extern uint16_t sendPingCmdDelay_5ms;

#endif


