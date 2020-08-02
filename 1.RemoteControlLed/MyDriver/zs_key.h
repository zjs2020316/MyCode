#ifndef _ZS_KEY_H
#define _ZS_KEY_H

#include "stm32f4xx_gpio.h"
#include "zs_led.h"
#include "zs_systick.h"
#include "zs_globalVariable.h"
//#include "zs_spc.h"

//>>zjs:Avoid shake delay function.
#define KEY_DELAY_MS(ms) Delay_xms(ms)

#define KEY_HIGH_LEVEL 1
#define KEY_LOW_LEVEL 0
//>>zjs:key press and no press  
#define KEY_PRESSED 1 
#define KEY_NO_PRESSED 0

//>>zjs:Key correlation param define.
#define KEY1_PIN        GPIO_Pin_0
#define KEY1_PORT       GPIOA
#define KEY1_CLK        RCC_AHB1Periph_GPIOA
#define KEY1_PRESS_VALUE KEY_HIGH_LEVEL  //>>zjs:define pressed valid level
#define GET_KEY1_STATUS() (GPIO_ReadInputDataBit( KEY1_PORT, KEY1_PIN)==KEY1_PRESS_VALUE) ? KEY_PRESSED: KEY_NO_PRESSED//>>zjs:Get key status,to determine key whether or not pressed.
//#define GET_KEY1_STATUS() (PAin(0)==KEY1_PRESS_VALUE) ? KEY_PRESSED: KEY_NO_PRESSED

//>>zjs:Key correlation param define.
#define KEY2_PIN        GPIO_Pin_13
#define KEY2_PORT       GPIOC
#define KEY2_CLK        RCC_AHB1Periph_GPIOC
#define KEY2_PRESS_VALUE KEY_HIGH_LEVEL  //>>zjs:define pressed valid level
#define GET_KEY2_STATUS() (GPIO_ReadInputDataBit( KEY2_PORT, KEY2_PIN)==KEY2_PRESS_VALUE) ? KEY_PRESSED: KEY_NO_PRESSED//>>zjs:Get key status,to determine key whether or not pressed.


//>>zjs:短按和长按按键的延时时间
#define KEY_SHOET_DELAY5MS 5
#define KEY_LONG_DELAY5MS 200

//>>zjs:按键按下的状态枚举
typedef enum 
{
	KEY_NO_PRESS,
	KEY1_INDEXES_VALUE,
	KEY2_INDEXES_VALUE,
	KEY3_INDEXES_VALUE,
	KEY4_INDEXES_VALUE,
	KEY1_INDEXES_SHORT,
	KEY1_INDEXES_LONG,
	KEY2_INDEXES_SHORT,
	KEY2_INDEXES_LONG,
	KEY3_INDEXES_SHORT,
	KEY3_INDEXES_LONG,
	KEY4_INDEXES_SHORT,
	KEY4_INDEXES_LONG
}KeyPressStatus;


//>>zjs:Correlation function statement.
KeyPressStatus Get_KeyValue1(void);
KeyPressStatus Key_Check(void);
void KEY_Init(void);

void KeyTest1(void);
void KeyTest2(void);

#endif
