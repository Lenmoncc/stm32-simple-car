#include "stm32f10x.h"                  // Device header
#include "MotorPwm.h"

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//外设时钟GPIOA使能
	
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_12|GPIO_Pin_11;//选中5/4号口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//目的是为了打开
	
	PWM_Init();//继承PWM的功能
	
}

void Motor_SetLeftSpeed1(int8_t Speed)//参数要是一个带符号的速度变量
{                                        //通道一对应左上车轮
	if(Speed>=0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		PWM_SetCompare1(Speed);
		
	}
	else if(Speed==0)//制动效果
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		PWM_SetCompare1(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		PWM_SetCompare1(-Speed);
		
	}
}

void Motor_SetRightSpeed2(int8_t Speed)//参数要是一个带符号的速度变量
{                                        //通道二对应右上车轮
	if(Speed>=0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		PWM_SetCompare2(Speed);
		
	}
	else if(Speed==0)//制动效果
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		PWM_SetCompare2(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		PWM_SetCompare2(-Speed);
		
	}
}

void Motor_SetLeftSpeed3(int8_t Speed)//参数要是一个带符号的速度变量
{                                       //通道三对应左下车轮
	if(Speed>=0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_12);  //输出高电平 1
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
		PWM_SetCompare3(Speed);
		
	}
	else if(Speed==0)//制动效果
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_12);
		GPIO_SetBits(GPIOA,GPIO_Pin_11);
		PWM_SetCompare3(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);
		GPIO_SetBits(GPIOA,GPIO_Pin_11);
		PWM_SetCompare3(-Speed);
		
	}
}

void Motor_SetRightSpeed4(int8_t Speed)//参数要是一个带符号的速度变量
{                                       //通道四对应右下车轮
	if(Speed>=0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);  //输出高电平 1
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);
		PWM_SetCompare4(Speed);
		
	}
	else if(Speed==0)//制动效果
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
		PWM_SetCompare4(Speed);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		GPIO_SetBits(GPIOA,GPIO_Pin_3);
		PWM_SetCompare4(-Speed);
		
	}
}
