/**
  * @name 全局变量定义
  * @brief 主要用于定义整个项目需要用到的全局变量
  * @date 2020-03-02
  * @version 1.0(版本)
  * @author  zjs(作者)
  * @other ... (其它)
  */
#include "zs_globalVariable.h"

uint32_t systick_1ms = 0x00;//>>zjs:1ms自增变量
uint32_t r_keyPressDelay_5ms = 0x00;//>>zjs:按键按下延时时间
uint16_t LedToggleDelay_5ms = 0x00;
uint16_t LedToggleDelay2_5ms = 0x00;
uint16_t buzzDelay_5ms = 0x00;//>>zjs:蜂鸣器计数
BuzzStatus buzz_flag = BUZZ_STOP;//>>zjs:蜂鸣器工作状态标志
BuzzRunStatus buzzRun_flag = BUZZ_ENABLE;//>>zjs:蜂鸣器运行状态标志

uint8_t ReceiveArray[RECEIVE_SIZE] = {0x00};
uint16_t ReveiveIndex = 0x00;//>>zjs:接收数组下标索引
uint8_t ReceiveFlag = 0x00;//>>zjs:接收数据标志
uint16_t sendPingCmdDelay_5ms = 0x00;//>>zjs:发送心跳包时间间隔延时

