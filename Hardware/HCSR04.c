#include "stm32f10x.h"                  // Device header
#include "HCSR04.h"
#include "ULTPWM.h"
#include "Delay.h"
#include "car.h"
#include "Servo.h"
#include "other.h" 
#include "OLED.h" 

uint16_t a;
uint16_t b;
uint16_t c;

uint16_t Time;
extern uint16_t Data3;

void HCSR04_Init()
{
	RCC_APB2PeriphClockCmd(Trig_RCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = Trig_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Trig_Port, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = Echo_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Echo_Port, &GPIO_InitStruct);
	
	GPIO_ResetBits(Trig_Port, Trig_Pin);
	
}

void HCSR04_Start()
{
	GPIO_SetBits(Trig_Port, Trig_Pin);
	Delay_us(45);
	GPIO_ResetBits(Trig_Port, Trig_Pin);
	Timer_Init();
}

uint16_t HCSR04_GetValue()
{
	HCSR04_Start();
	Delay_ms(100);
	Time=((Time * 0.0001) * 34000) / 2;
//	OLED_ShowNum(1, 10, Time, 3);
//	return ((Time * 0.0001) * 34000) / 2;
	return Time;
}


void Distance_Judging()
{
	if(Data3==0x37)
		{
		//Servo_GetValue();
		Go_Ahead();
		a = HCSR04_GetValue();         //右边为0度，左边为180度，逆时针转动
		if(a<15)
		{
			Car_Stop();
			Servo_SetAngle(0);	//往右看
			Delay_ms(1000);
			b= HCSR04_GetValue();
		
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
				c= HCSR04_GetValue();
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

