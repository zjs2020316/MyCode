/**
  * @name led��Ӧ����������
  * @brief ���Կ���led����ת
  * @date 2020-03-02
  * @version 1.0(�汾)
  * @author  zjs(����)
  * @other ... (����)
  */	
#include "zs_led.h"

/**
  * @name GPIO��ʼ������
  * @brief ���ö�Ӧ��GPIO����Ϊ���ģʽ
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
  * @name led��ʼ������
  * @brief ��ʼ��led�������
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

//>>zjs:����ָ�����LED������
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


