/**
  * @name spcӦ����������
  * @brief ����ͨѶ��Ӧ��
  * @date 2020-03-02
  * @version 1.0(�汾)
  * @author   zjs(����)
  * @other ... (����)
  */	
#include "zs_spc.h"


 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* �������ȼ�Ϊ1 */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ�Ϊ1 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
	 /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = ESP_USART_IRQ;
//  /* �������ȼ�Ϊ1 */
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//  /* �����ȼ�Ϊ1 */
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//  /* ʹ���ж� */
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @name UART��ʼ������
  * @brief ����UART��TX RX���ţ������ʣ������С
  * @param none
  * @retval none
  * @other ...
  */
void UART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* -----------------------------������ص�GPIO��ʼ��-------------------------------------- */	
	RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK|DEBUG_USART_TX_GPIO_CLK | ESP_USART_TX_GPIO_CLK | ESP_USART_RX_GPIO_CLK,ENABLE);
	/* ʹ�� USART ʱ�� */
	RCC_APB2PeriphClockCmd(DEBUG_USART_CLK | ESP_USART_CLK, ENABLE);

	/* GPIO��ʼ�� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	//>>zjs:DEBUG_USART��������
	/* ����Tx����Ϊ���ù���  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_PIN  ;  
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	/* ����Rx����Ϊ���ù��� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_PIN;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

	/* ���� PXx �� USARTx_Tx*/
	GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT,DEBUG_USART_RX_SOURCE,DEBUG_USART_RX_AF);
	/*  ���� PXx �� USARTx__Rx*/
	GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT,DEBUG_USART_TX_SOURCE,DEBUG_USART_TX_AF);
	
	//>>zjs:ESP_USART��������
	/* ����Tx����Ϊ���ù���  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = ESP_USART_TX_PIN  ;  
	GPIO_Init(ESP_USART_TX_GPIO_PORT, &GPIO_InitStructure);

	/* ����Rx����Ϊ���ù��� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = ESP_USART_RX_PIN;
	GPIO_Init(ESP_USART_RX_GPIO_PORT, &GPIO_InitStructure);

	/* ���� PXx �� USARTx_Tx*/
	GPIO_PinAFConfig(ESP_USART_RX_GPIO_PORT,ESP_USART_RX_SOURCE,ESP_USART_RX_AF);
	/*  ���� PXx �� USARTx__Rx*/
	GPIO_PinAFConfig(ESP_USART_TX_GPIO_PORT,ESP_USART_TX_SOURCE,ESP_USART_TX_AF);

	/* -----------------------------��������-------------------------------------- */	

	/* ���ô�DEBUG_USART ģʽ */
	/* ���������ã�DEBUG_USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	/* �ֳ�(����λ+У��λ)��8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* ֹͣλ��1��ֹͣλ */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* У��λѡ�񣺲�ʹ��У�� */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* Ӳ�������ƣ���ʹ��Ӳ���� */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* ���USART��ʼ������ */
	USART_Init(DEBUG_USART, &USART_InitStructure);
	
	/* ���ô�ESP_USART ģʽ */
	/* ���������ã�ESP_USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = ESP_USART_BAUDRATE;
	/* �ֳ�(����λ+У��λ)��8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* ֹͣλ��1��ֹͣλ */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* У��λѡ�񣺲�ʹ��У�� */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* Ӳ�������ƣ���ʹ��Ӳ���� */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USARTģʽ���ƣ�ͬʱʹ�ܽ��պͷ��� */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* ���USART��ʼ������ */
	USART_Init(ESP_USART, &USART_InitStructure);

	/* ���ô��ڵĽ����ж� */
	NVIC_Configuration();

	/* ʹ�ܴ��ڽ����ж� */
	USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);
	USART_ITConfig(ESP_USART, USART_IT_RXNE, ENABLE);

	/* ʹ�ܴ��� */
	USART_Cmd(DEBUG_USART, ENABLE);
	USART_Cmd(ESP_USART, ENABLE);
}

/*****************  ����һ���ַ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
}

//>>zjs:����һ���ַ�����
void Usart_SendArray1( USART_TypeDef * pUSARTx, uint8_t *array)
{
	uint16_t index = 0x00;
	while((array[index] != '#') && (index < ReveiveIndex))
	{
		Usart_SendByte( pUSARTx, array[index++]);
	}
}

//>>zjs:����һ����������
void Usart_SendArray2( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t len)
{
	uint16_t index = 0x00;
	while(index < len)
	{
		Usart_SendByte( pUSARTx, array[index++]);
	}
}

//>>zjs:����һ���������飬�����������������
void Usart_SendArrayClear1( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t len)
{
	uint16_t index = 0x00;
	while(index < len)
	{
		Usart_SendByte( pUSARTx, array[index]);
		array[index] = 0x00;
		index++;
	}
	ReveiveIndex = 0x00;//>>zjs:������������ֵ
}

//>>zjs:����str1���Ƿ���str2
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



///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USART, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USART);
}

