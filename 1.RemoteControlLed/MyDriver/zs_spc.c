/**
  * @name spc应用驱动程序
  * @brief 串口通讯的应用
  * @date 2020-03-02
  * @version 1.0(版本)
  * @author   zjs(作者)
  * @other ... (其它)
  */	
#include "zs_spc.h"


 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* 抢断优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级为1 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
	 /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = ESP_USART_IRQ;
//  /* 抢断优先级为1 */
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  /* 子优先级为1 */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* 使能中断 */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @name UART初始化配置
  * @brief 配置UART的TX RX引脚，波特率，缓存大小
  * @param none
  * @retval none
  * @other ...
  */
void UART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* -----------------------------串口相关的GPIO初始化-------------------------------------- */	
	RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK|DEBUG_USART_TX_GPIO_CLK | ESP_USART_TX_GPIO_CLK | ESP_USART_RX_GPIO_CLK,ENABLE);
	/* 使能 USART 时钟 */
	RCC_APB2PeriphClockCmd(DEBUG_USART_CLK | ESP_USART_CLK, ENABLE);

	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	//>>zjs:DEBUG_USART引脚配置
	/* 配置Tx引脚为复用功能  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_PIN  ;  
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚为复用功能 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_PIN;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT,DEBUG_USART_RX_SOURCE,DEBUG_USART_RX_AF);
	/*  连接 PXx 到 USARTx__Rx*/
	GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT,DEBUG_USART_TX_SOURCE,DEBUG_USART_TX_AF);
	
	//>>zjs:ESP_USART引脚配置
	/* 配置Tx引脚为复用功能  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = ESP_USART_TX_PIN  ;  
	GPIO_Init(ESP_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚为复用功能 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = ESP_USART_RX_PIN;
	GPIO_Init(ESP_USART_RX_GPIO_PORT, &GPIO_InitStructure);

	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(ESP_USART_RX_GPIO_PORT,ESP_USART_RX_SOURCE,ESP_USART_RX_AF);
	/*  连接 PXx 到 USARTx__Rx*/
	GPIO_PinAFConfig(ESP_USART_TX_GPIO_PORT,ESP_USART_TX_SOURCE,ESP_USART_TX_AF);

	/* -----------------------------串口配置-------------------------------------- */	

	/* 配置串DEBUG_USART 模式 */
	/* 波特率设置：DEBUG_USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	/* 字长(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成USART初始化配置 */
	USART_Init(DEBUG_USART, &USART_InitStructure);
	
	/* 配置串ESP_USART 模式 */
	/* 波特率设置：ESP_USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = ESP_USART_BAUDRATE;
	/* 字长(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成USART初始化配置 */
	USART_Init(ESP_USART, &USART_InitStructure);

	/* 配置串口的接收中断 */
	NVIC_Configuration();

	/* 使能串口接收中断 */
	USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);
	USART_ITConfig(ESP_USART, USART_IT_RXNE, ENABLE);

	/* 使能串口 */
	USART_Cmd(DEBUG_USART, ENABLE);
	USART_Cmd(ESP_USART, ENABLE);
}

/*****************  发送一个字符 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  发送一个16位数 **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  发送字符串 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
}

//>>zjs:发送一个字符数组
void Usart_SendArray1( USART_TypeDef * pUSARTx, uint8_t *array)
{
	uint16_t index = 0x00;
	while((array[index] != '#') && (index < ReveiveIndex))
	{
		Usart_SendByte( pUSARTx, array[index++]);
	}
}

//>>zjs:发送一个定长数组
void Usart_SendArray2( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t len)
{
	uint16_t index = 0x00;
	while(index < len)
	{
		Usart_SendByte( pUSARTx, array[index++]);
	}
}

//>>zjs:发送一个定长数组，并清除这个数组的数据
void Usart_SendArrayClear1( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t len)
{
	uint16_t index = 0x00;
	while(index < len)
	{
		Usart_SendByte( pUSARTx, array[index]);
		array[index] = 0x00;
		index++;
	}
	ReveiveIndex = 0x00;//>>zjs:清零数组索引值
}

//>>zjs:查找str1中是否含有str2
uint8_t CheckString(uint8_t *str1, uint16_t str1Len, uint8_t *str2)
{
	uint16_t str1Index = 0x00;
	uint8_t str2Index = 0x00;
	uint8_t str2Len = strlen((char*)str2);
	uint8_t matchLen = 0x00;
	
	while(str1Index < str1Len)
	{
		if(str1[str1Index] == str2[0])
		{
			for( str2Index=0, matchLen=0; (str2Index<str2Len)&&((str1Index+str2Index)<str1Len); str2Index++)
			{
				if(str1[str1Index+str2Index] == str2[str2Index])
					matchLen++;
				else
					str2Index = str2Len;
			}
			if(matchLen >= (str2Len-1))
			{
				return 1;
			}
		}
		str1Index++;
	}
	return 0;
}



///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(DEBUG_USART, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USART);
}

