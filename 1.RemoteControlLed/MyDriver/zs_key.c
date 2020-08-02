/**
  * @name key按键应用驱动程序
  * @brief 主要用于检测按键按下，获取相关的索引值
  * @date 2020-03-02
  * @version 1.0(版本)
  * @author   zjs(作者)
  * @other ... (其它)
  */	
#include "zs_key.h"

static uint8_t key_flag = 0x00;

/**
  * @name GPIO初始化配置
  * @brief 配置对应的GPIO引脚为输入模式
  * @param none
  * @retval  none
  * @other ...
  */
void KEY_GPIO_Config( void )
{
	GPIO_InitTypeDef GPIO_InitStruct;

	// 打开KEY_GPIO的时钟
	RCC_AHB1PeriphClockCmd(KEY1_CLK | KEY2_CLK,ENABLE);
	// 配置为输入
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;	
	// 配置下拉
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;

	// 选定KEY_GPIO，就是具体的引脚号
	GPIO_InitStruct.GPIO_Pin = KEY1_PIN;	
	GPIO_Init(KEY1_PORT,&GPIO_InitStruct);

	// 选定KEY_GPIO，就是具体的引脚号
	GPIO_InitStruct.GPIO_Pin = KEY2_PIN;
	GPIO_Init(KEY2_PORT,&GPIO_InitStruct);
}

/**
  * @name key初始化函数
  * @brief 初始化key相关配置
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

//>>zjs:定时器消抖，并实现长按和短按按键 
KeyPressStatus Get_KeyValue2(void)
{
	KeyPressStatus current_value = KEY_NO_PRESS;//>>zjs:保存当前的按键值
	static uint8_t old_value = KEY_NO_PRESS;//>>zjs:保存上一次的按键值
	static uint8_t press_flag = KEY1_INDEXES_VALUE;//>>zjs:记录是否有效按下，初值不为KEY_NO_PRESS，防止开机前就有按键按下
	
	//>>zjs:获取按键的输入值，如果按键没有硬件消抖电路，
	//>>zjs:那么最好在这里加一个优先判断上一次状态的程序，可以用switch实现，否则按按键还是会出现不稳定的情况
	if(KEY_PRESSED == GET_KEY1_STATUS())
	{
		current_value = KEY1_INDEXES_VALUE;
	}
	else if(KEY_PRESSED == GET_KEY2_STATUS())
	{
		current_value = KEY2_INDEXES_VALUE;
	}
	
	if(KEY_NO_PRESS != current_value)//>>zjs:如果有按键按下
	{
		if(current_value != old_value)//>>zjs:第一次按键按下则清零计数值
		{
			old_value = current_value;
			r_keyPressDelay_5ms = 0x00;
		}
		//>>zjs:长按检测 大于设定的延时时间则判断为长按
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
			//>>zjs:短按检测
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

//>>zjs:产生按键音
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

//>>zjs:按键测试 普通按键消抖
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

//>>zjs:定时器按键消抖测试
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
		//>>zjs:按键音
		BuzzTone();
		
		//>>zjs:执行具体功能
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

