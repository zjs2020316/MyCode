/**
  * @name ȫ�ֱ�������
  * @brief ��Ҫ���ڶ���������Ŀ��Ҫ�õ���ȫ�ֱ���
  * @date 2020-03-02
  * @version 1.0(�汾)
  * @author  zjs(����)
  * @other ... (����)
  */
#include "zs_globalVariable.h"

uint32_t systick_1ms = 0x00;//>>zjs:1ms��������
uint32_t r_keyPressDelay_5ms = 0x00;//>>zjs:����������ʱʱ��
uint16_t LedToggleDelay_5ms = 0x00;
uint16_t LedToggleDelay2_5ms = 0x00;
uint16_t buzzDelay_5ms = 0x00;//>>zjs:����������
BuzzStatus buzz_flag = BUZZ_STOP;//>>zjs:����������״̬��־
BuzzRunStatus buzzRun_flag = BUZZ_ENABLE;//>>zjs:����������״̬��־

uint8_t ReceiveArray[RECEIVE_SIZE] = {0x00};
uint16_t ReveiveIndex = 0x00;//>>zjs:���������±�����
uint8_t ReceiveFlag = 0x00;//>>zjs:�������ݱ�־
uint16_t sendPingCmdDelay_5ms = 0x00;//>>zjs:����������ʱ������ʱ

