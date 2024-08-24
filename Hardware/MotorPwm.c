#include "stm32f10x.h"                  // Device header
#include "Delay.h"
//一个定时器，四个通道，对应四个电机。使用定时器4（TIM4）
//PB6-CH1,PB7-CH2,PB8-CH3,PB9-CH4



void PWM_Init(void)
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);			
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);			
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);							
																	
	
	
	TIM_InternalClockConfig(TIM4);		
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;    //             
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;               
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);             
	
	
	TIM_OCInitTypeDef TIM_OCInitStructure;							
	TIM_OCStructInit(&TIM_OCInitStructure);                         
	                                                                
	                                                                
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   
	TIM_OCInitStructure.TIM_Pulse = 0;								
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   
	TIM_OCInitStructure.TIM_Pulse = 0;	
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   
	TIM_OCInitStructure.TIM_Pulse = 0;	
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   
	TIM_OCInitStructure.TIM_Pulse = 0;	
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM4, ENABLE);			
}


 void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM4, Compare);		//设置CCR1的值
}

void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM4, Compare);		//设置CCR2的值
}

void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM4, Compare);		//设置CCR3的值
}

void PWM_SetCompare4(uint16_t Compare)
{
	TIM_SetCompare4(TIM4, Compare);		//设置CCR4的值
}

