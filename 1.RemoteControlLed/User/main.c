/**
  * @name 远程控制LED灯测试
  * @brief MCU+ESP8266 通过OneNET云平台来实现
  * @date 2020-08-01
  * @version 1.0
  * @author  zjs
  * @platform xxx
  * @statement xxx
  * @other 简化版本，只适合测试，不能实用
  */
#include "zs_led.h"
#include "zs_key.h"
#include "zs_systick.h"
#include "zs_spc.h"
#include "zs_esp8266.h"


//>>zjs:远程控制LED灯开关测试
int main(void)
{
	UART_Init();
	LED_Init();
	KEY_Init();
	Systick_Init();
	
	DEBUGG_PINFO("System Start...");
	
	RemoteControlLedTest();
	
	while(1)
	{
	
	}
}

