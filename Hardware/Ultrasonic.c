#include "stm32f10x.h"                  // Device header
#include "Delay.h"
//#include "other.h"
#include "car.h"
#include "Servo.h"

uint16_t a;
uint16_t b;
uint16_t c;

uint16_t Cnt;
uint16_t OverCnt;

extern uint16_t Data3;

void Ultrasound_Init(){
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//trig
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//echo
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM1);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 60000 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

}
float Test_Distance()
{
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
	Delay_us(20);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);              //RESET——0；SET——!0
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==RESET){
	};
	TIM_Cmd(TIM1, ENABLE);
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)==SET){
	};
	TIM_Cmd(TIM1, DISABLE);
	Cnt=TIM_GetCounter(TIM1);
	float distance=(Cnt*1.0/10*0.34)/2;
	TIM1->CNT=0;
	Delay_ms(100);
	return distance;
}


void Distance_Judging()
{
	if(Data3==0x37)
		{
		//Servo_GetValue();
		Go_Ahead();
		a = Test_Distance();                //右边为0度，左边为180度，逆时针转动
		if(a<15)
		{
			Car_Stop();
			Servo_SetAngle(0);	//往右看
			Delay_ms(1000);
			b= Test_Distance();
		
			if(b>15)
			{
				Servo_SetAngle(90);
				Delay_ms(1000);
				Self_Right();
				Delay_ms(1000);
				Go_Ahead();
			
			}
			else 
			{
				Servo_SetAngle(180);
				Delay_ms(1000);
				c= Test_Distance();
				if(c>15)
				{	
					Servo_SetAngle(90);
					Delay_ms(1000);
					Self_Left();
					Delay_ms(1000);
					Go_Ahead();
				}
				else
			    {
					Servo_SetAngle(90);
					while(1){};
				}
			}
		}
		Delay_ms(100);
	}
		else 
		{
			Servo_SetAngle(90);
		}
}


