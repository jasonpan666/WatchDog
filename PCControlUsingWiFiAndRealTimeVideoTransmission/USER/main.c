#include "stm32f10x.h"
#include "led.h" 
#include "Time_test.h"
#include "uart.h"

extern int speed_left,speed_right;		   /*speed=0~5*/
volatile u32 time; // ms ��ʱ����
extern volatile u8 motor0_angel,motor1_angel,motor2_angel,motor3_angel,motor4_angel,motor5_angel;
u8 mode[3],mode1=0;
/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����	
 */

void dianji(u8 i)
{
	switch(i)
	{
		case 1:					   //ǰ��
		speed_right=4;
		speed_left=4;
		break;

		case 2:					   //����
		speed_right=-4;
		speed_left=-4;
		break;

		case 3:					   //��ת
		speed_right=-2;
		speed_left=4;
		break;

		case 4:					   //��ת
		speed_right=4;
		speed_left=-2;
		break;

		case 0:					   //ֹͣ
		speed_right=0;
		speed_left=0;
		break;

		case 5:					   //��ǰ
		speed_right=2;
		speed_left=5;
		break;

		case 6:					   //��ǰ
		speed_right=5;
		speed_left=1;
		break;

		case 7:					   //���
		speed_right=-2;
		speed_left=-5;
		break;

		case 8:					   //�Һ�
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
		motor0_angel=mode[2];				  //ȡ�Ƕ�
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
		if(mode[1]==0x00)					//ȡ��������
			ledon;									//ȡ����״̬
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
	/* ����ϵͳʱ��Ϊ 72M */  
	SystemInit();	
	/* led �˿����� */ 
	ALL_GPIO_Config();	
	/*usart3 �������� */
	USART3Conf(9600);
	TIM2_NVIC_Configuration();
	//NVIC_Configuration();
	TIM2_Configuration();	
	/* TIM2 ��ʼ��ʱ */
	START_TIME;	
	while(1)
	{
		if(mode1==1)						//ÿ���յ�ָ��ִ��һ��
		{
			mode1=0;
			if(mode[0]==0)					//�жϲ�������
				dianji(mode[1]);
			else if(mode[0]==1)
				duoji(mode[1]);
			else if(mode[0]>=2&&mode[0]<=4)
				other(mode[0]);
		}
	}
}
/*************************************************************************************
Э��涨:
��ͷ   ����λ  ����λ   ����λ    ����λ
0XFF   0X**     OX**    0X**      0XFF

������˵��:
����λ    ����λ   ����λ    ����
0X00       0X01      0X00    ǰ��
0X00       0X02      0X00    ����
0X00       0X03      0X00    ��ת
0X00       0X04      0X00    ��ת
0X00       0X00      0X00    ֹͣ
0X00       0X05      0X00    ��ǰ
0X00       0X06      0X00    ��ǰ
0X00       0X07      0X00    ���
0X00       0X08      0X00    �Һ�

0X01       0X01      �Ƕ�    ���1
0X01       0X02       .      ���2
0X01       0X03       .      ���3
0X01       0X04       .      ���4
0X01       0X05       .      ���5
0X01       0X06       .      ���6


0X02       0X00      0X00    ������
0X02       0X01      0X00    ������

0X03       0X00      0X00    ���ȿ�
0X03       0X01      0X00    ���ȹ�

0X04       0X00      0X00   �Զ��忪
0X04       0X01      0X00   �Զ����
*****************************************************/