/**
  * @name Systick系统定时器应用驱动程序
  * @brief Systick定时的使用
  * @date 2020-03-02
  * @version 1.0(版本)
  * @author   zjs(作者)
  * @other ... (其它)
  */	
#include "zs_systick.h"

static __IO u32 TimingDelay;

/**
  * @name Systick init初始化配置
  * @brief 调用初始化库函数进行初始化
  * @param none
  * @retval none
  * @other ...
  */	
void Systick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (SysTick_Config(SystemCoreClock / 1000))
	{ 
		/* Capture error */ 
		while (1);
	}
}

/**
  * @name 微秒级延时函数
  * @brief (uint32_t xus)(延时数值)
  * @param none
  * @retval none
  * @other ...
  */
//void Delay_10us(uint32_t xus)
//{
//	TimingDelay = xus;	

//	while(TimingDelay != 0);
//}

/**
  * @name 毫秒级延时函数
  * @brief (uint32_t xms)(延时数值)
  * @param none
  * @retval none
  * @other ...
  */
void Delay_xms(uint32_t xms)
{
  	//Delay_10us(xms*100);
	
	TimingDelay = xms;	
	while(TimingDelay != 0);
}
//void Delay_xms(uint32_t xms)//>>zjs:用软件ms延时替换，但是不是很精确
//{
//  uint16_t i = 0;
//	uint32_t j = 0;
//	
//	for(j=0;j<xms;j++)
//	{
//	  	for(i=0;i<24000;i++)
//		{}
//	}
//}

/**
  * @brief  获取节拍程序
  * @param  无
  * @retval 无
  * @attention  在 SysTick 中断函数 SysTick_Handler()调用
  */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}

//>>zjs:Systick定时器测试函数测试
void SystickTest(void)
{
	while(1)
	{
		LED3_Toggle();
		Delay_xms(300);
	}
}



