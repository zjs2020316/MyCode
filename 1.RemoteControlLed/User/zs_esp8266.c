#include "zs_esp8266.h"

//>>zjs:�Ʒ������·��Ŀ���ָ���(����) 1-2 3-4 5-6 7-8 (��� �̵� ���� ������)

//>>zjs:�����豸��ָ��
uint8_t connectServer[49] = { 0x10, 0x2F, 0x00, 0x04, 0x4D, 0x51, 0x54, 0x54, 0x04, 0xC0, 0x00, 0x78, 0x00, 0x09,
										 0x35, 0x31, 0x37, 0x32, 0x31, 0x32, 0x30, 0x25, 0x36, 0x00, 0x06, 0x32, 0x31, 0x32,
										 0x38, 0x31, 0x38, 0x00, 0x34, 0x69, 0x56, 0x53, 0x56, 0x31, 0x59, 0x49, 0x41, 0x6B,
										 0x53, 0x44, 0x27, 0x63, 0x39, 0x4E, 0x32};

uint8_t pingCmd[2] = {0xc0, 0x00}; //>>zjs:����ָ��
uint8_t pingOk[2] = {0xd0, 0x00}; //>>zjs:��������ָ���,���سɹ�������

uint8_t disconnectCmd[2] = {0xe0, 0x00};  //>>zjs:�Ͽ�����������ӵ�ָ��

uint8_t connectServerOk[4] = {0x20, 0x02, 0x00, 0x00}; //>>zjs:���������豸ָ����سɹ�������

//>>zjs:led����˸
void BlinkLed(void)
{
	if(LedToggleDelay_5ms >= BLINK_DEALY)
	{
		LedToggleDelay_5ms = 0x00;
		LED4_Toggle();
	}
}

//>>zjs:�������ռ�
void ClearReceiveArray( uint8_t *array, uint16_t len)
{
	uint16_t i = 0x00;
	for( i=0; i<len; i++)
	{
		array[i] = 0x00;
	}
}

//>>zjs:��ʱ����Ping������
void TimingSendPingCmd(void)
{
	if(sendPingCmdDelay_5ms >= SEND_PING_DELAYS) //>>zjs:������Ե���
	{
		sendPingCmdDelay_5ms = 0x00;
		Usart_SendArray2( ESP_USART, pingCmd, 2);
		Delay_xms(10);
		Usart_SendArray2( ESP_USART, pingCmd, 2);
		Delay_xms(10);
	}
}

//>>zjs:Ӳ����λESP8266ģ��
void HandwareResetEspModule(void)
{
	RST_LOW();
	Delay_xms(100);
	RST_HIGH();
	Delay_xms(4000);
	Usart_SendArrayClear1( DEBUG_USART, ReceiveArray, ReveiveIndex);
}

//>>zjs:esp8266���ӵ�OneNET�Ʒ�����
void EspConnectServer(void)
{
	HandwareResetEspModule();//>>zjs:Ӳ����λһ��ģ��
	
	Usart_SendString( ESP_USART, "AT\r\n");
	Delay_xms(1000);
	Usart_SendArrayClear1( DEBUG_USART, ReceiveArray, ReveiveIndex);
	
	//	Usart_SendString( ESP_USART, "AT+RST\r\n");//>>zjs:ǰ����Ӳ����λģ�飬��������Ͳ������λģ����
//	Delay_xms(3000);
	
	Usart_SendString( ESP_USART, "AT+CWJAP=\"wifi name\",\"wifi key\"\r\n");//>>zjs:����wifi
	Delay_xms(4000);
	Usart_SendArrayClear1( DEBUG_USART, ReceiveArray, ReveiveIndex);
	
	Usart_SendString( ESP_USART, "AT+CIPSTART=\"TCP\",\"183.230.40.39\",6002\r\n");//>>zjs:���ӷ�����
	Delay_xms(1000);
	Usart_SendArrayClear1( DEBUG_USART, ReceiveArray, ReveiveIndex);
	
	Usart_SendString( ESP_USART, "AT+CIPMODE=1\r\n"); //>>zjs:����Ϊ͸��ģʽ
	Delay_xms(1000);
	Usart_SendArrayClear1( DEBUG_USART, ReceiveArray, ReveiveIndex);
	
	Usart_SendString( ESP_USART, "AT+CIPSEND\r\n"); //>>zjs:��������
	Delay_xms(1000);
	Usart_SendArrayClear1( DEBUG_USART, ReceiveArray, ReveiveIndex);
	
	Usart_SendArray2( ESP_USART, connectServer, 49); //>>zjs:���ӵ��Լ����豸
	Delay_xms(1000);
	Usart_SendArrayClear1( DEBUG_USART, ReceiveArray, ReveiveIndex);
}

//>>zjs:����ָ�����led����״̬
void CmdControlLedOnOff(uint8_t cmd)
{
	switch(cmd)
	{
		case '1':
		{
			LED1_ON();
			break;
		}
		case '2':
		{
			LED1_OFF();
			break;
		}
		case '3':
		{
			LED2_ON();
			break;
		}
		case '4':
		{
			LED2_OFF();
			break;
		}
		case '5':
		{
			LED3_ON();
			break;
		}
		case '6':
		{
			LED3_OFF();
			break;
		}
		case '7':
		{
			BUZZ1_ON();
			break;
		}
		case '8':
		{
			BUZZ1_OFF();
			break;
		}
		default:
		{
			break;
		}
	}
}

//>>zjs:����Ƿ���ܵ����ݣ����ҽ��н���
void EcodeReveiveData(void)
{
	if(1 == ReceiveFlag)
	{
		if(0x30 == ReceiveArray[0])//>>zjs:����Ƿ������·���ָ������ָ���ִ�������Ӧ�Ķ���
		{
			Delay_xms(200);//>>zjs:��ʱ1s������������ܽ�����һ�δ��ڵ�����
			//Usart_SendArray2( DEBUG_USART, ReceiveArray, ReveiveIndex);
			//DEBUGG_PINFO("");
			CmdControlLedOnOff(ReceiveArray[ReceiveArray[1]+1]);
		}
		else//>>zjs:����PUBLISH��server -> client��������������
		{
			Delay_xms(100);
		}

		//>>zjs:�����Ӧ�ı���
		ReveiveIndex = 0x00;
		ReceiveFlag = 0x00;
		ClearReceiveArray( ReceiveArray, ReveiveIndex);			
	}
}

//>>zjs:Զ�̿���led�Ȳ��Ժ���
void RemoteControlLedTest(void)
{
	EspConnectServer();//>>zjs:���ӷ�����
	
	ClearReceiveArray( ReceiveArray, ReveiveIndex);//>>zjs:��ս��ջ���ռ�
	sendPingCmdDelay_5ms = 0x00;//>>zjs:���㷢��Ping����ʱ����
	ReceiveFlag = 0x00;//>>zjs:���㴮�ڽ��յ����ݵı���
	ReveiveIndex = 0x00;//>>zjs:���㴮�ڽ�����������
	
	while(1)
	{
		EcodeReveiveData();
		BlinkLed();
		TimingSendPingCmd();
	}
}
