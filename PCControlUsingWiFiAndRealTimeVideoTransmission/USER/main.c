#include "stm32f10x.h"
#include "led.h" 
#include "Time_test.h"
#include "uart.h"

extern int speed_left,speed_right;		   /*speed=0~5*/
volatile u32 time; // ms 计时变量
extern volatile u8 motor0_angel,motor1_angel,motor2_angel,motor3_angel,motor4_angel,motor5_angel;
u8 mode[3],mode1=0;
/*
 * 函数名：main
 * 描述  ：主函数
 * 输入  ：无
 * 输出  ：无	
 */

void dianji(u8 i)
{
	switch(i)
	{
		case 1:					   //前进
		speed_right=4;
		speed_left=4;
		break;

		case 2:					   //后退
		speed_right=-4;
		speed_left=-4;
		break;

		case 3:					   //左转
		speed_right=-2;
		speed_left=4;
		break;

		case 4:					   //右转
		speed_right=4;
		speed_left=-2;
		break;

		case 0:					   //停止
		speed_right=0;
		speed_left=0;
		break;

		case 5:					   //左前
		speed_right=2;
		speed_left=5;
		break;

		case 6:					   //右前
		speed_right=5;
		speed_left=1;
		break;

		case 7:					   //左后
		speed_right=-2;
		speed_left=-5;
		break;

		case 8:					   //右后
		speed_right=-5;
		speed_left=-2;
		break;
	}
}

void duoji(u8 i)
{
	if(mode[2]>180)
		mode[2]=180;
	switch(i)
	{
		case 1:					   
		motor0_angel=mode[2];				  //取角度
		break;

		case 2:					   
		motor1_angel=mode[2];		
		break;

		case 3:					
		motor2_angel=mode[2];		   
		break;

		case 4:					   
		motor3_angel=mode[2];		
		break;

		case 5:					   
		motor4_angel=mode[2];		
		break;

		case 6:					   
		motor5_angel=mode[2];		
		break;
	}
}

void other(u8 i)
{
	switch(i)
	{
		case 2:	
		if(mode[1]==0x00)					//取操作对象
			ledon;									//取操作状态
		else if(mode[1]==0x01)
			ledoff;   		
		break;

		case 3:	
		if(mode[1]==0x00)
			beepon;
		else if(mode[1]==0x01)
			beepoff;   						   
		break;

		case 4:				
		if(mode[1]==0x00)
			zidingyion;
		else if(mode[1]==0x01)
			zidingyioff;   			   
		break;
	}
}

int main(void)
{
	/* 配置系统时钟为 72M */  
	SystemInit();	
	/* led 端口配置 */ 
	ALL_GPIO_Config();	
	/*usart3 串口配置 */
	USART3Conf(9600);
	TIM2_NVIC_Configuration();
	//NVIC_Configuration();
	TIM2_Configuration();	
	/* TIM2 开始计时 */
	START_TIME;	
	while(1)
	{
		if(mode1==1)						//每次收到指令执行一次
		{
			mode1=0;
			if(mode[0]==0)					//判断操作对象
				dianji(mode[1]);
			else if(mode[0]==1)
				duoji(mode[1]);
			else if(mode[0]>=2&&mode[0]<=4)
				other(mode[0]);
		}
	}
}
/*************************************************************************************
协议规定:
包头   类型位  数据位   数据位    结束位
0XFF   0X**     OX**    0X**      0XFF

各命令说明:
类型位    数据位   数据位    功能
0X00       0X01      0X00    前进
0X00       0X02      0X00    后退
0X00       0X03      0X00    左转
0X00       0X04      0X00    右转
0X00       0X00      0X00    停止
0X00       0X05      0X00    左前
0X00       0X06      0X00    右前
0X00       0X07      0X00    左后
0X00       0X08      0X00    右后

0X01       0X01      角度    舵机1
0X01       0X02       .      舵机2
0X01       0X03       .      舵机3
0X01       0X04       .      舵机4
0X01       0X05       .      舵机5
0X01       0X06       .      舵机6


0X02       0X00      0X00    车灯亮
0X02       0X01      0X00    车灯灭

0X03       0X00      0X00    喇叭开
0X03       0X01      0X00    喇叭关

0X04       0X00      0X00   自定义开
0X04       0X01      0X00   自定义关
*****************************************************/