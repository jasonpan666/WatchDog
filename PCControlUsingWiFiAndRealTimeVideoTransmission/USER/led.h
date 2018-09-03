#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

#define ledon   GPIO_SetBits(GPIOE, GPIO_Pin_12)
#define ledoff  GPIO_ResetBits(GPIOE, GPIO_Pin_12)

#define beepon  GPIO_SetBits(GPIOE, GPIO_Pin_14)
#define beepoff GPIO_ResetBits(GPIOE, GPIO_Pin_14)

#define zidingyion  GPIO_SetBits(GPIOE, GPIO_Pin_10)
#define zidingyioff GPIO_ResetBits(GPIOE, GPIO_Pin_10)

void ALL_GPIO_Config(void);

#endif /* __LED_H */
