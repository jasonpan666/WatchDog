/******************** (C) COPYRIGHT 2012 WildFire Team ***************************
 * �ļ���  ��usart1.c
 * ����    ����printf�����ض���USART1�������Ϳ�����printf��������Ƭ��������
 *           ��ӡ��PC�ϵĳ����ն˻򴮿ڵ������֡�         
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ�------------------------
 *          | PA9  - USART1(Tx)      |
 *          | PA10 - USART1(Rx)      |
 *           ------------------------
 * ��汾  ��ST3.5.0
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/	
#include "usart1.h"
#include "misc.h"
/*
 * ��������USART1_Config
 * ����  ��USART1 GPIO ����,����ģʽ����
 * ����  ����
 * ���  : ��
 * ����  ���ⲿ����
 */
void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef 	NVIC_InitStruct;//?����?��???����???D??��??��11��?	
	
	/* config USART3 clock */
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3 | RCC_APB2Periph_GPIOB, ENABLE);
	
	/* USART3 GPIO config */
	/* Configure USART3 Tx (PB.10) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);    
	/* Configure USART3 Rx (PB.11) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* USART3 mode config */
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART3, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//�䨰?a???D??
	NVIC_Init(&NVIC_InitStruct);
}


void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}



/*
 * ��������fputc
 * ����  ���ض���c�⺯��printf��USART1
 * ����  ����
 * ���  ����
 * ����  ����printf����
 */
int fputc(int ch, FILE *f)
{
	/* ��Printf���ݷ������� */
	USART_SendData(USART1, (unsigned char) ch);
	while (!(USART1->SR & USART_FLAG_TXE));
	
	return (ch);
}

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

