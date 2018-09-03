
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
int speed_left=0,speed_right=0;		   /*speed=0~5*/
u8 buf[3];
extern u8 mode[3],mode1;
#define ina1 (5+speed_left)				   //取速度差
#define ina2 (5-speed_left)
#define inb1 (5+speed_right)
#define inb2 (5-speed_right)

#define motor0 (46+motor0_angel)		   //定时中断是11us对应舵机的1度，46对应0.5MS，每加1表示转1度
#define motor1 (46+motor1_angel)
#define motor2 (46+motor2_angel)
#define motor3 (46+motor3_angel)
#define motor4 (46+motor4_angel)
#define motor5 (46+motor5_angel)
/*电机宏定义*/
#define left1on GPIO_SetBits(GPIOD,GPIO_Pin_6)
#define left1off GPIO_ResetBits(GPIOD,GPIO_Pin_6)

#define left2on GPIO_SetBits(GPIOG,GPIO_Pin_9)
#define left2off GPIO_ResetBits(GPIOG,GPIO_Pin_9)

#define right1on GPIO_SetBits(GPIOC,GPIO_Pin_11)
#define right1off GPIO_ResetBits(GPIOC,GPIO_Pin_11)

#define right2on GPIO_SetBits(GPIOD,GPIO_Pin_0)
#define right2off GPIO_ResetBits(GPIOD,GPIO_Pin_0)
/*舵机宏定义*/
#define motor0on GPIO_SetBits(GPIOA,GPIO_Pin_0)
#define motor0off GPIO_ResetBits(GPIOA,GPIO_Pin_0)

#define motor1on GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define motor1off GPIO_ResetBits(GPIOA,GPIO_Pin_1)

#define motor2on GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define motor2off GPIO_ResetBits(GPIOA,GPIO_Pin_2)

#define motor3on GPIO_SetBits(GPIOF,GPIO_Pin_8)
#define motor3off GPIO_ResetBits(GPIOF,GPIO_Pin_8)

#define motor4on GPIO_SetBits(GPIOF,GPIO_Pin_9)
#define motor4off GPIO_ResetBits(GPIOF,GPIO_Pin_9)

#define motor5on GPIO_SetBits(GPIOF,GPIO_Pin_10)
#define motor5off GPIO_ResetBits(GPIOF,GPIO_Pin_10)

extern volatile u32 time;
u8 start=0;
u16 time1,time2;
volatile u8 motor0_angel=90,motor1_angel=90,motor2_angel=90,motor3_angel=90,motor4_angel=90,motor5_angel=90;

void TIM2_IRQHandler(void)
{
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
	{	
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);  
		time1++;
		time2++;
		if(time1==50)
		{  
			time1=0;
	  		time++;
			if(time>9)
				time=0;
			if(ina1>time)
				left1on;
			else 	
				left1off;
			if(ina2>time)
				left2on;
			else 	
				left2off;
			if(inb1>time)
				right1on;
			else 	
				right1off;
			if(inb2>time)
				right2on;
			else 	
				right2off;
		}
		if(time2>1818)
			time2=0;
		if(time2<motor0)
			motor0on;
		else
			motor0off;
		if(time2<motor1)
			motor1on;
		else
			motor1off;
		if(time2<motor2)
			motor2on;
		else
			motor2off;
		if(time2<motor3)
			motor3on;
		else
			motor3off;
		if(time2<motor4)
			motor4on;
		else
			motor4off;
		if(time2<motor5)
			motor5on;
		else
			motor5off;
	}		 	
}

void USART3_IRQHandler(void)
{
	unsigned char rec_data;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		/* Read one byte from the receive data register */
		rec_data = USART_ReceiveData(USART3);
		if(start!=0&&rec_data!=0xff)						//如果已收到包头并且当前收到的不是包尾
		{
			buf[start-1]=rec_data;							//缓存数据
			start++;
		}
		else if(start!=0&&rec_data==0xff)					//如果收到包尾
		{
			mode[0]=buf[0];									//给状态存储数组赋值
			mode[1]=buf[1];
			mode[2]=buf[2];
			start=0;
			mode1=1;										//指示主函数循环检测一次
		}
		else if(rec_data==0xff&&start==0)					//如果收到的是包头
			start++;	
	}
}













void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles TIM2 interrupt request.
  * @param  None
  * @retval : None
  */

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
