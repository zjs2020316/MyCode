#ifndef _ZS_SPC_H
#define _ZS_SPC_H

//#include "stm32f4xx_usart.h"
//#include "stm32f4xx_gpio.h"
//#include "misc.h"

#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>
#include "zs_globalVariable.h"

//引脚定义
/*******************************************************/
#define DEBUG_USART                             USART1
#define DEBUG_USART_CLK                         RCC_APB2Periph_USART1
#define DEBUG_USART_BAUDRATE                    9600  //串口波特率

#define DEBUG_USART_RX_GPIO_PORT                GPIOA
#define DEBUG_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART_RX_PIN                      GPIO_Pin_10
#define DEBUG_USART_RX_AF                       GPIO_AF_USART1
#define DEBUG_USART_RX_SOURCE                   GPIO_PinSource10

#define DEBUG_USART_TX_GPIO_PORT                GPIOA
#define DEBUG_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART_TX_PIN                      GPIO_Pin_9
#define DEBUG_USART_TX_AF                       GPIO_AF_USART1
#define DEBUG_USART_TX_SOURCE                   GPIO_PinSource9

#define DEBUG_USART_IRQHandler                  USART1_IRQHandler
#define DEBUG_USART_IRQ                 				USART1_IRQn
/************************************************************/
#define ESP_USART                             USART6
#define ESP_USART_CLK                         RCC_APB2Periph_USART6
#define ESP_USART_BAUDRATE                    9600  //串口波特率

#define ESP_USART_RX_GPIO_PORT                GPIOG
#define ESP_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOG
#define ESP_USART_RX_PIN                      GPIO_Pin_9
#define ESP_USART_RX_AF                       GPIO_AF_USART6
#define ESP_USART_RX_SOURCE                   GPIO_PinSource9

#define ESP_USART_TX_GPIO_PORT                GPIOC
#define ESP_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOC
#define ESP_USART_TX_PIN                      GPIO_Pin_6
#define ESP_USART_TX_AF                       GPIO_AF_USART6
#define ESP_USART_TX_SOURCE                   GPIO_PinSource6

#define ESP_USART_IRQHandler                  USART6_IRQHandler
#define ESP_USART_IRQ                 				USART6_IRQn
/************************************************************/


//>>zjs:串口打印调试信息宏定义
#define DEBUGG_MODE 1
//#define RELEASE_MODE 1

#if(DEBUGG_MODE)
#define DEBUGG_PINFO(str) Usart_SendString( DEBUG_USART,str);Usart_SendString( DEBUG_USART,"\r\n");
#else
#define DEBUGG_PINFO(str)  
#endif

//>>zjs:相关函数声明
void UART_Init(void);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendArray1( USART_TypeDef * pUSARTx, uint8_t *array);
void Usart_SendArray2( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t len);
void Usart_SendArrayClear1( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t len);

uint8_t CheckString(uint8_t *str1, uint16_t str1Len, uint8_t *str2);

#endif

