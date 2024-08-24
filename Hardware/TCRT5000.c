#include "stm32f10x.h"                  // Device header
#include "Car.h"
#include "Delay.h"
#include "other.h"

extern uint16_t Data2;

void TCRT5000_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING ;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	

}
//接收到红外光，DO输出低电平--0——离黑线较远
//黑色胶布吸收红外光，DO输出高电平--1——离黑线较近
//遇到黑线灯灭，返回高电平
//10，11为右边；12，13为左边
//中间为0，10为右1，11为右2；13为左1，12为左2
//3种状态，0为正常行驶，即线在正中间；-1为左的状态，有2种情况
void TCRTtrack_Init()
{
	if(Data2==0x40)
	{
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1)
		{
			Go_Ahead();
		}
		else if
			(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1)
		{
			Car_Stop();
		}
		else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1)//大转弯
		{
			Delay_ms(100);
		   Self_Right();
		}
		else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0)//大转弯
		{
//			Turn_Right();
			Self_Right();
		}
		else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==1&&         //两次调用Turn_Right()，因为黑线的角度不同（程度）
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0)
		{
			Turn_Right();
//			Self_Right();
		}
		else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==1&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0&&
			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0)
		{
//			Turn_Right();
			Self_Right();
		}
		else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==1&&
		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0&&
		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1&&
		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1)
		{
			Delay_ms(100);
			Self_Left();
		}
		else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==0&&
		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0&&
		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1&&
		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1)
		{
//			Turn_Left();
			Self_Left();
		}
		else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==0&&
		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0&&
		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==1&&
		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0)
		{
//			Turn_Left();
			Self_Left();
		}
		else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==0&&
		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0&&
		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0&&
		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==1)
		{
			Turn_Left();
//			Self_Left();
		}
//		else if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)==0&&
//		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0&&
//		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0&&
//		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0)
//		{
//			Car_Stop();
//			Delay_ms(1000);
//		}
	}
		
}


