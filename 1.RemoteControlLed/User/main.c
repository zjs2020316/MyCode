/**
  * @name Զ�̿���LED�Ʋ���
  * @brief MCU+ESP8266 ͨ��OneNET��ƽ̨��ʵ��
  * @date 2020-08-01
  * @version 1.0
  * @author  zjs
  * @platform xxx
  * @statement xxx
  * @other �򻯰汾��ֻ�ʺϲ��ԣ�����ʵ��
  */
#include "zs_led.h"
#include "zs_key.h"
#include "zs_systick.h"
#include "zs_spc.h"
#include "zs_esp8266.h"


//>>zjs:Զ�̿���LED�ƿ��ز���
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

