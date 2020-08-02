#ifndef _ZS_GLOBALVARIABLE_H
#define _ZS_GLOBALVARIABLE_H

#include "stdint.h"

#define BUZZ_DELAY_X5MS 15 //>>zjs:������������ʱ��
#define RECEIVE_SIZE 512 //>>zjs:�������ݵĻ����С

//>>zjs:����������״̬
typedef enum
{
	BUZZ_STOP,
	BUZZ_START=0x98
}BuzzStatus;

//>>zjs:����������״̬
typedef enum
{
	BUZZ_DISABLE,
	BUZZ_ENABLE
}BuzzRunStatus;

//>>zjs:����Ϊ�ⲿ������������.c�ļ�����
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


