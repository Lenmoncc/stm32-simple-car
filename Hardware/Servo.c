#include "stm32f10x.h"                  // Device header
#include "ServoPwm.h"
#include "Delay.h"

float Angal;

void Servo_Init(void)
{
	ServoPWM_Init();									//初始化舵机的底层PWM
}


void Servo_SetAngle(float Angle)
{
	ServoPWM_SetCompare1(Angle / 180 * 2000 + 500);	//设置占空比
												//将角度线性变换，对应到舵机要求的占空比范围上
}

void Servo_GetValue()
{
	for(Angal=0; ;Angal+=90)
	{
		if(Angal>180)
		{
			Angal=0;
		}
		Servo_SetAngle(Angal);
		Delay_ms(500);
	}
}



