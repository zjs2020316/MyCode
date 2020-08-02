#ifndef _ZS_LED_H
#define _ZS_LED_H

#include "stm32f4xx_gpio.h"

//>>zjs:底层引脚输出状态宏定义，以后移植其它芯片上时，直接修改这里即可
#define GPIO_PIN_OUT_H(GPIOX,PIN)  GPIO_SetBits(GPIOX,PIN)
#define GPIO_PIN_OUT_L(GPIOX,PIN)  GPIO_ResetBits(GPIOX,PIN)
#define GPIO_PIN_TOGGLE(GPIOX,PIN)  GPIO_ToggleBits(GPIOX,PIN)

#define LED1_PIN        GPIO_Pin_10
#define LED1_PORT       GPIOH
#define LED1_CLK        RCC_AHB1Periph_GPIOH
#define LED1_ON()      GPIO_PIN_OUT_L(GPIOH,LED1_PIN)
#define LED1_OFF()     GPIO_PIN_OUT_H(GPIOH,LED1_PIN)
#define LED1_Toggle()  GPIO_PIN_TOGGLE(GPIOH,LED1_PIN)

#define LED2_PIN        GPIO_Pin_11
#define LED2_PORT       GPIOH
#define LED2_CLK        RCC_AHB1Periph_GPIOH
#define LED2_ON()      GPIO_PIN_OUT_L(GPIOH,LED2_PIN)
#define LED2_OFF()     GPIO_PIN_OUT_H(GPIOH,LED2_PIN)
#define LED2_Toggle()  GPIO_PIN_TOGGLE(GPIOH,LED2_PIN)

#define LED3_PIN        GPIO_Pin_12
#define LED3_PORT       GPIOH
#define LED3_CLK        RCC_AHB1Periph_GPIOH
#define LED3_ON()      GPIO_PIN_OUT_L(GPIOH,LED3_PIN)
#define LED3_OFF()     GPIO_PIN_OUT_H(GPIOH,LED3_PIN)
#define LED3_Toggle()  GPIO_PIN_TOGGLE(GPIOH,LED3_PIN)

#define LED4_PIN        GPIO_Pin_12
#define LED4_PORT       GPIOD
#define LED4_CLK        RCC_AHB1Periph_GPIOD
#define LED4_ON()      GPIO_PIN_OUT_L(LED4_PORT,LED4_PIN)
#define LED4_OFF()     GPIO_PIN_OUT_H(LED4_PORT,LED4_PIN)
#define LED4_Toggle()  GPIO_PIN_TOGGLE(LED4_PORT,LED4_PIN)

#define RST_PIN        GPIO_Pin_2
#define RST_PORT       GPIOD
#define RST_CLK        RCC_AHB1Periph_GPIOD
#define RST_HIGH()      GPIO_PIN_OUT_H(RST_PORT,RST_PIN)
#define RST_LOW()     GPIO_PIN_OUT_L(RST_PORT,RST_PIN)
#define RST_Toggle()  GPIO_PIN_TOGGLE(RST_PORT,RST_PIN)

#define BUZZ1_PIN        GPIO_Pin_11
#define BUZZ1_PORT       GPIOI
#define BUZZ1_CLK        RCC_AHB1Periph_GPIOI
#define BUZZ1_ON()      GPIO_PIN_OUT_H(BUZZ1_PORT,BUZZ1_PIN)
#define BUZZ1_OFF()     GPIO_PIN_OUT_L(BUZZ1_PORT,BUZZ1_PIN)
#define BUZZ1_Toggle()  GPIO_PIN_TOGGLE(BUZZ1_PORT,BUZZ1_PIN)

//>>zjs:LED混合现实的宏定义
//红
#define LED_RED()  \
					LED1_ON();\
					LED2_OFF();\
					LED3_OFF()

//绿
#define LED_GREEN()		\
					LED1_OFF();\
					LED2_ON();\
					LED3_OFF()

//蓝
#define LED_BLUE()	\
					LED1_OFF();\
					LED2_OFF();\
					LED3_ON()

					
//黄(红+绿)					
#define LED_YELLOW()	\
					LED1_ON();\
					LED2_ON();\
					LED3_OFF()
//紫(红+蓝)
#define LED_PURPLE()	\
					LED1_ON();\
					LED2_OFF();\
					LED3_ON()

//青(绿+蓝)
#define LED_CYAN() \
					LED1_OFF();\
					LED2_ON();\
					LED3_ON()
					
//白(红+绿+蓝)
#define LED_WHITE()	\
					LED1_ON();\
					LED2_ON();\
					LED3_ON()
					
//黑(全部关闭)
#define LED_RGBOFF()	\
					LED1_OFF();\
					LED2_OFF();\
					LED3_OFF()


//>>zjs:位带操作相关宏定义
#define BIT_BAND(addr,bit) (((addr&0xf0000000)+0x02000000+((addr&0x000fffff)<<5)+(bit<<2)))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr,bit)	MEM_ADDR( BIT_BAND(addr,bit))

//>>zjs:ODR IDR寄存器映射
#define GPIOH_ODR_ADDR (GPIOH_BASE+0x14)
#define GPIOA_IDR_ADDR (GPIOA_BASE+0x10)

//>>zjs:输入输出位操作
#define PHout(bit) BIT_ADDR(GPIOH_ODR_ADDR,bit)
#define PAin(bit)  BIT_ADDR(GPIOA_IDR_ADDR,bit)


void LED_Init(void);
void CmdControlLed(uint16_t ch);

#endif


