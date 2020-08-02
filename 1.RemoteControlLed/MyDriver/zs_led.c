/**
  * @name led灯应用驱动程序
  * @brief 可以控制led亮灭翻转
  * @date 2020-03-02
  * @version 1.0(版本)
  * @author  zjs(作者)
  * @other ... (其它)
  */	
#include "zs_led.h"

/**
  * @name GPIO初始化配置
  * @brief 配置对应的GPIO引脚为输出模式
  * @param none
  * @retval  none
  * @other ...
  */
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(LED1_CLK | LED2_CLK | BUZZ1_CLK | RST_CLK | LED4_CLK,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;	
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;	
	GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
	
	GPIO_InitStruct.GPIO_Pin = LED1_PIN;
	GPIO_Init(LED1_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED2_PIN;
	GPIO_Init(LED2_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED3_PIN;
	GPIO_Init(LED3_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED4_PIN;
	GPIO_Init(LED4_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = BUZZ1_PIN;
	GPIO_Init(BUZZ1_PORT,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = RST_PIN;
	GPIO_Init(RST_PORT,&GPIO_InitStruct);
}

/**
  * @name led初始化函数
  * @brief 初始化led相关配置
  * @param none
  * @retval  none
  * @other ...
  */
void LED_Init(void)
{
	LED_GPIO_Config();
	LED1_OFF();
	LED2_OFF();
	LED3_OFF();
	LED4_OFF();
	BUZZ1_OFF();
	RST_HIGH();
}

//>>zjs:根据指令控制LED灯亮灭
void CmdControlLed(uint16_t ch)
{
	switch(ch)
		{
			case '1':
			{
				LED1_Toggle();
				break;
			}
			case '2':
			{
				LED2_Toggle();
				break;
			}
			case '3':
			{
				LED3_Toggle();
				break;
			}
			case '4':
			{
				BUZZ1_Toggle();
				break;
			}
			default:
			{
				break;
			}
		}
}


