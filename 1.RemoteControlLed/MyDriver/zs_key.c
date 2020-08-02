/**
  * @name key����Ӧ����������
  * @brief ��Ҫ���ڼ�ⰴ�����£���ȡ��ص�����ֵ
  * @date 2020-03-02
  * @version 1.0(�汾)
  * @author   zjs(����)
  * @other ... (����)
  */	
#include "zs_key.h"

static uint8_t key_flag = 0x00;

/**
  * @name GPIO��ʼ������
  * @brief ���ö�Ӧ��GPIO����Ϊ����ģʽ
  * @param none
  * @retval  none
  * @other ...
  */
void KEY_GPIO_Config( void )
{
	GPIO_InitTypeDef GPIO_InitStruct;

	// ��KEY_GPIO��ʱ��
	RCC_AHB1PeriphClockCmd(KEY1_CLK | KEY2_CLK,ENABLE);
	// ����Ϊ����
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;	
	// ��������
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;

	// ѡ��KEY_GPIO�����Ǿ�������ź�
	GPIO_InitStruct.GPIO_Pin = KEY1_PIN;	
	GPIO_Init(KEY1_PORT,&GPIO_InitStruct);

	// ѡ��KEY_GPIO�����Ǿ�������ź�
	GPIO_InitStruct.GPIO_Pin = KEY2_PIN;
	GPIO_Init(KEY2_PORT,&GPIO_InitStruct);
}

/**
  * @name key��ʼ������
  * @brief ��ʼ��key�������
  * @param none
  * @retval  none
  * @other ...
  */
void KEY_Init(void)
{
	KEY_GPIO_Config();
}

/**
  * @name Get key index value.
  * @brief Get key value through Generic method. 
  * @param none
  * @retval  uint8_t key index value.
  * @other ...
  */
KeyPressStatus Get_KeyValue1(void)
{
	if(GET_KEY1_STATUS() == KEY_PRESSED)
	{
		KEY_DELAY_MS(5);
		if(GET_KEY1_STATUS() == KEY_PRESSED)
		{
			if(key_flag == 0x00)//>>zjs:?????????,??????,?????
			{
				key_flag = 0xff; //>>zjs:???????????
				return KEY1_INDEXES_VALUE;
			}
		}
	}
	else if(GET_KEY2_STATUS() == KEY_PRESSED)
	{
		KEY_DELAY_MS(5);
		if(GET_KEY2_STATUS() == KEY_PRESSED)
		{
			if(key_flag == 0x00)//>>zjs:?????????,??????,?????
			{	
				key_flag = 0xff;//>>zjs:???????????
				return KEY2_INDEXES_VALUE;
			}
		}
	}
	else
	{
		key_flag = 0x00;//>>zjs:???????????
	}
	
	return KEY_NO_PRESS;
}

//>>zjs:��ʱ����������ʵ�ֳ����Ͷ̰����� 
KeyPressStatus Get_KeyValue2(void)
{
	KeyPressStatus current_value = KEY_NO_PRESS;//>>zjs:���浱ǰ�İ���ֵ
	static uint8_t old_value = KEY_NO_PRESS;//>>zjs:������һ�εİ���ֵ
	static uint8_t press_flag = KEY1_INDEXES_VALUE;//>>zjs:��¼�Ƿ���Ч���£���ֵ��ΪKEY_NO_PRESS����ֹ����ǰ���а�������
	
	//>>zjs:��ȡ����������ֵ���������û��Ӳ��������·��
	//>>zjs:��ô����������һ�������ж���һ��״̬�ĳ��򣬿�����switchʵ�֣����򰴰������ǻ���ֲ��ȶ������
	if(KEY_PRESSED == GET_KEY1_STATUS())
	{
		current_value = KEY1_INDEXES_VALUE;
	}
	else if(KEY_PRESSED == GET_KEY2_STATUS())
	{
		current_value = KEY2_INDEXES_VALUE;
	}
	
	if(KEY_NO_PRESS != current_value)//>>zjs:����а�������
	{
		if(current_value != old_value)//>>zjs:��һ�ΰ����������������ֵ
		{
			old_value = current_value;
			r_keyPressDelay_5ms = 0x00;
		}
		//>>zjs:������� �����趨����ʱʱ�����ж�Ϊ����
		if((r_keyPressDelay_5ms >= KEY_LONG_DELAY5MS) && (KEY_NO_PRESS == press_flag))
		{
			press_flag = current_value;
			buzz_flag = BUZZ_START;
			if(KEY1_INDEXES_VALUE == current_value)
			{
				current_value =  KEY1_INDEXES_LONG;
			}
			else if(KEY2_INDEXES_VALUE == current_value)
			{
				current_value =  KEY2_INDEXES_LONG;
			}
		}
	}
	else
	{
		if((KEY_NO_PRESS==press_flag) && (KEY_NO_PRESS!=old_value))
		{
			//>>zjs:�̰����
			if(r_keyPressDelay_5ms >= KEY_SHOET_DELAY5MS)
			{
				buzz_flag = BUZZ_START;
				if(KEY1_INDEXES_VALUE == old_value)
				{
					current_value =  KEY1_INDEXES_SHORT;
				}
				else if(KEY2_INDEXES_VALUE == old_value)
				{
					current_value =  KEY2_INDEXES_SHORT;
				}
			}
		}
		press_flag = KEY_NO_PRESS;
		old_value = KEY_NO_PRESS;
	}
	
	return current_value;
}

//>>zjs:����������
void BuzzTone(void)
{
	if(BUZZ_ENABLE == buzzRun_flag)
	{
		if(BUZZ_START == buzz_flag)
		{
			BUZZ1_ON();
			buzz_flag = BUZZ_STOP;
			buzzDelay_5ms = 0x00;
		}
		else if(buzzDelay_5ms >= BUZZ_DELAY_X5MS)
		{
			BUZZ1_OFF();
		}
	}
}

//>>zjs:�������� ��ͨ��������
void KeyTest1(void)
{
	while(1)
	{
		switch(Get_KeyValue1())
		{
			case KEY1_INDEXES_VALUE:
			{
				LED2_Toggle();
				break;
			}
			case KEY2_INDEXES_VALUE:
			{
				LED3_Toggle();
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

//>>zjs:��ʱ��������������
void KeyTest2(void)
{
//	r_keyPressDelay_5ms = 0x00;
//	LedToggleDelay_5ms = 0x00;
//	LedToggleDelay2_5ms = 0x00;
	uint8_t func_flag1 = 0x00;
	
	while(1)
	{
		switch(Get_KeyValue2())
		{
			case KEY1_INDEXES_SHORT:
			{
				//LED1_Toggle();
				func_flag1 |= 0x01;
				break;
			}
			case KEY2_INDEXES_SHORT:
			{
				//LED2_Toggle();
				func_flag1 |= 0x02;
				break;
			}
			case KEY1_INDEXES_LONG:
			{
				//LED3_Toggle();
				func_flag1 |= 0x04;
				break;
			}
			case KEY2_INDEXES_LONG:
			{ 
				//LED2_Toggle();
				func_flag1 |= 0x08;
				break;
			}
			default:                               
			{
				break;
			}
		}
		//>>zjs:������
		BuzzTone();
		
		//>>zjs:ִ�о��幦��
		if(0x01 & func_flag1)
		{
			LED1_Toggle();
			func_flag1 &= ~(1<<0);
		}
		if(0x02 & func_flag1)
		{
			LED2_Toggle();
			func_flag1 &= ~(1<<1);
		}
		if(0x04 & func_flag1)
		{
			LED3_Toggle();
			func_flag1 &= ~(1<<2);
		}
		if(0x08 & func_flag1)
		{
			if(BUZZ_ENABLE == buzzRun_flag)
				buzzRun_flag = BUZZ_DISABLE;
			else
				buzzRun_flag = BUZZ_ENABLE;
			BUZZ1_OFF();
			func_flag1 &= ~(1<<3);
		}
	}
}

