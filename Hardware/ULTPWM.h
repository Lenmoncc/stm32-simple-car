#ifndef __ULT_PWM_H
#define __ULT_PWM_H

#define Trig_Port 		GPIOB
#define Trig_Pin 		GPIO_Pin_15
#define Trig_RCC		RCC_APB2Periph_GPIOB

#define Echo_Port 		GPIOB
#define Echo_Pin 		GPIO_Pin_14
#define Echo_RCC		RCC_APB2Periph_GPIOB

void Timer_Init(void);
void TIM2_IRQHandler(void);

#endif
