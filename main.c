#include "stm32f10x.h"                  // Device header
#include "Car.h"
#include "Motor.h"
#include "Delay.h"
#include "TCRT5000.h"
#include "MotorPwm.h"
#include "Servo.h"
#include "ULTPWM.h"
#include "pid.h"
#include "Serial.h" 
#include "other.h" 
#include "HCSR04.h"



int main(void)
{
	Car_Init();
	Servo_Init();
	HCSR04_Init();
	HCSR04_Start();
	Timer_Init();
	Serial_Init();
	PID_Output();
	//HCSR04_GetValue();
	
	
	while (1)
	{
		TCRTtrack_Init();
		Distance_Judging();

	}
	
}


