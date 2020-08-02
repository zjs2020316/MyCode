/**
  * @name Systickϵͳ��ʱ��Ӧ����������
  * @brief Systick��ʱ��ʹ��
  * @date 2020-03-02
  * @version 1.0(�汾)
  * @author   zjs(����)
  * @other ... (����)
  */	
#include "zs_systick.h"

static __IO u32 TimingDelay;

/**
  * @name Systick init��ʼ������
  * @brief ���ó�ʼ���⺯�����г�ʼ��
  * @param none
  * @retval none
  * @other ...
  */	
void Systick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if (SysTick_Config(SystemCoreClock / 1000))
	{ 
		/* Capture error */ 
		while (1);
	}
}

/**
  * @name ΢�뼶��ʱ����
  * @brief (uint32_t xus)(��ʱ��ֵ)
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
  * @name ���뼶��ʱ����
  * @brief (uint32_t xms)(��ʱ��ֵ)
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
//void Delay_xms(uint32_t xms)//>>zjs:�����ms��ʱ�滻�����ǲ��Ǻܾ�ȷ
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
  * @brief  ��ȡ���ĳ���
  * @param  ��
  * @retval ��
  * @attention  �� SysTick �жϺ��� SysTick_Handler()����
  */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}

//>>zjs:Systick��ʱ�����Ժ�������
void SystickTest(void)
{
	while(1)
	{
		LED3_Toggle();
		Delay_xms(300);
	}
}



