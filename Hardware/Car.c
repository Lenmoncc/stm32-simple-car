#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Delay.h"
#include "pid.h"

//extern struct PID MotorSpeed;
//extern struct PID actrual;

void Car_Init(void)
{
  Motor_Init();
}	

//1，3为左轮；2，4为右轮
void Go_Ahead(void)
{
	//Motor_SetLeftSpeed1(P_realize(&MotorSpeed,speed));
	Motor_SetLeftSpeed1(75);
	Motor_SetRightSpeed2(75);
	Motor_SetLeftSpeed3(75);
	Motor_SetRightSpeed4(75);
}

void Go_Back(void)
{
	Motor_SetLeftSpeed1(-75);
	Motor_SetRightSpeed2(-75);
	Motor_SetLeftSpeed3(-75);
	Motor_SetRightSpeed4(-75);
}

void Turn_Left(void)
{
	Motor_SetLeftSpeed1(0);
	Motor_SetRightSpeed2(75-PID_Output());
	Motor_SetLeftSpeed3(0);
	Motor_SetRightSpeed4(75-PID_Output());
}

void Turn_Right(void)
{
	Motor_SetLeftSpeed1(75+PID_Output());
	Motor_SetRightSpeed2(0);
	Motor_SetLeftSpeed3(75+PID_Output());
	Motor_SetRightSpeed4(0);
}

void Self_Left(void)
{
	Motor_SetLeftSpeed1(-75+PID_Output());
	Motor_SetRightSpeed2(75-PID_Output());
	Motor_SetLeftSpeed3(-75+PID_Output());
	Motor_SetRightSpeed4(75-PID_Output());
}

void Self_Right(void)
{
	Motor_SetLeftSpeed1(75+PID_Output());
	Motor_SetRightSpeed2(-75-PID_Output());
	Motor_SetLeftSpeed3(75+PID_Output());
	Motor_SetRightSpeed4(-75-PID_Output());
}


void Car_Stop(void)
{
	Motor_SetLeftSpeed1(0);
	Motor_SetRightSpeed2(0);
	Motor_SetLeftSpeed3(0);
	Motor_SetRightSpeed4(0);
}
