#include "zs_esp8266.h"

//>>zjs:云服务器下发的开关指令对(开关) 1-2 3-4 5-6 7-8 (红灯 绿灯 蓝灯 蜂鸣器)

//>>zjs:连接设备的指令
uint8_t connectServer[49] = { 0x10, 0x2F, 0x00, 0x04, 0x4D, 0x51, 0x54, 0x54, 0x04, 0xC0, 0x00, 0x78, 0x00, 0x09,
										 0x35, 0x31, 0x37, 0x32, 0x31, 0x32, 0x30, 0x25, 0x36, 0x00, 0x06, 0x32, 0x31, 0x32,
										 0x38, 0x31, 0x38, 0x00, 0x34, 0x69, 0x56, 0x53, 0x56, 0x31, 0x59, 0x49, 0x41, 0x6B,
										 0x53, 0x44, 0x27, 0x63, 0x39, 0x4E, 0x32};

uint8_t pingCmd[2] = {0xc0, 0x00}; //>>zjs:心跳指令
uint8_t pingOk[2] = {0xd0, 0x00}; //>>zjs:发送心跳指令后,返回成功的数据

uint8_t disconnectCmd[2] = {0xe0, 0x00};  //>>zjs:断开与服务器连接的指令

uint8_t connectServerOk[4] = {0x20, 0x02, 0x00, 0x00}; //>>zjs:发送连接设备指令，返回成功的数据

//>>zjs:led等闪烁
void BlinkLed(void)
{
	if(LedToggleDelay_5ms >= BLINK_DEALY)
	{
		LedToggleDelay_5ms = 0x00;
		LED4_Toggle();
	}
}

//>>zjs:清除缓存空间
void ClearReceiveArray( uint8_t *array, uint16_t len)
{
	uint16_t i = 0x00;
	for( i=0; i<len; i++)
	{
		array[i] = 0x00;
	}
}

//>>zjs:定时发送Ping心跳包
void TimingSendPingCmd(void)
{
	if(sendPingCmdDelay_5ms >= SEND_PING_DELAYS) //>>zjs:这里可以调整
	{
		sendPingCmdDelay_5ms = 0x00;
		Usart_SendArray2( ESP_USART, pingCmd, 2);
		Delay_xms(10);
		Usart_SendArray2( ESP_USART, pingCmd, 2);
		Delay_xms(10);
	}
}

//>>zjs:硬件复位ESP8266模块
void HandwareResetEspModule(void)
{
	RST_LOW();
	Delay_xms(100);
	RST_HIGH();
	Delay_xms(4000);
	Usart_SendArrayClear1( DEBUG_USART, ReceiveArray, ReveiveIndex);
}

//>>zjs:esp8266连接到OneNET云服务器
void EspConnectServer(void)
{
	HandwareResetEspModule();//>>zjs:硬件复位一下模块
	
	Usart_SendString( ESP_USART, "AT\r\n");
	Delay_xms(1000);
	Usart_SendArrayClear1( DEBUG_USART, ReceiveArray, ReveiveIndex);
	
	//	Usart_SendString( ESP_USART, "AT+RST\r\n");//>>zjs:前面有硬件复位模块，所以这里就不软件复位模块了
//	Delay_xms(3000);
	
	Usart_SendString( ESP_USART, "AT+CWJAP=\"wifi name\",\"wifi key\"\r\n");//>>zjs:连接wifi
	Delay_xms(4000);
	Usart_SendArrayClear1( DEBUG_USART, ReceiveArray, ReveiveIndex);
	
	Usart_SendString( ESP_USART, "AT+CIPSTART=\"TCP\",\"183.230.40.39\",6002\r\n");//>>zjs:连接服务器
	Delay_xms(1000);
	Usart_SendArrayClear1( DEBUG_USART, ReceiveArray, ReveiveIndex);
	
	Usart_SendString( ESP_USART, "AT+CIPMODE=1\r\n"); //>>zjs:设置为透传模式
	Delay_xms(1000);
	Usart_SendArrayClear1( DEBUG_USART, ReceiveArray, ReveiveIndex);
	
	Usart_SendString( ESP_USART, "AT+CIPSEND\r\n"); //>>zjs:发送数据
	Delay_xms(1000);
	Usart_SendArrayClear1( DEBUG_USART, ReceiveArray, ReveiveIndex);
	
	Usart_SendArray2( ESP_USART, connectServer, 49); //>>zjs:连接到自己的设备
	Delay_xms(1000);
	Usart_SendArrayClear1( DEBUG_USART, ReceiveArray, ReveiveIndex);
}

//>>zjs:根据指令控制led开关状态
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

//>>zjs:检测是否接受到数据，并且进行解码
void EcodeReveiveData(void)
{
	if(1 == ReceiveFlag)
	{
		if(0x30 == ReceiveArray[0])//>>zjs:如果是服务器下发的指令，则解析指令，并执行命令对应的动作
		{
			Delay_xms(200);//>>zjs:延时1s，正常情况都能接收完一次串口的数据
			//Usart_SendArray2( DEBUG_USART, ReceiveArray, ReveiveIndex);
			//DEBUGG_PINFO("");
			CmdControlLedOnOff(ReceiveArray[ReceiveArray[1]+1]);
		}
		else//>>zjs:不是PUBLISH（server -> client）的数据则抛弃
		{
			Delay_xms(100);
		}

		//>>zjs:清零对应的变量
		ReveiveIndex = 0x00;
		ReceiveFlag = 0x00;
		ClearReceiveArray( ReceiveArray, ReveiveIndex);			
	}
}

//>>zjs:远程控制led等测试函数
void RemoteControlLedTest(void)
{
	EspConnectServer();//>>zjs:连接服务器
	
	ClearReceiveArray( ReceiveArray, ReveiveIndex);//>>zjs:清空接收缓存空间
	sendPingCmdDelay_5ms = 0x00;//>>zjs:清零发送Ping的延时变量
	ReceiveFlag = 0x00;//>>zjs:清零串口接收到数据的变量
	ReveiveIndex = 0x00;//>>zjs:清零串口接收数据索引
	
	while(1)
	{
		EcodeReveiveData();
		BlinkLed();
		TimingSendPingCmd();
	}
}
