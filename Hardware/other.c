#include "stm32f10x.h"                  // Device header
#include "Car.h"
#include "Motor.h"
#include "Delay.h"
#include "TCRT5000.h"
#include "MotorPwm.h"
#include "Servo.h"
#include "Ultrasonic.h"
#include "pid.h"
#include "Serial.h" 

uint16_t Data1;
int i;
uint16_t Data2;
uint16_t Data3;

//蓝牙通信
//在中断函数里接收数据
void  USART1_IRQHandler(void)
{
	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		Data1=USART_ReceiveData(USART1);
		Data2=USART_ReceiveData(USART1);
		Data3=USART_ReceiveData(USART1);
		if(Data1==0x30)Car_Stop();//48
		if(Data1==0x31)Go_Ahead();
		if(Data1==0x32)Go_Back();
		if(Data1==0x33)Turn_Left();
		if(Data1==0x34)Turn_Right();
		if(Data1==0x35)Self_Left();
		if(Data1==0x36)Self_Right();
		if(Data3==0x37) i=2;//避障
		if(Data1==0x38) i=4;//关
//		if(Data1==0x37)Servo_SetAngle(0);
//		if(Data1==0x42)Servo_SetAngle(90);
//		if(Data1==0x39)Servo_SetAngle(180);
		if(Data2==0x40) i=1;  //自动循迹功能打开
		if(Data1==0x41) i=0;  //自动循迹功能关闭  65
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	
}
