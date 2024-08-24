#include "stm32f10x.h"                  // Device header
#include "pid.h"


float Kp=20;//设置为全局变量,Kp>0
float Ki=3;
float Kd=17;
//pid:比例项过大时，积分项不宜过小
//uint16_t state[4];
//读取红外管电平的状态
//S1，2左边；S3，3右边

int s1,s2,s3,s4;


float PID_Output(void)
{
    static float cur_error;
    static float last_error;
    static float integral;
//    int8_t output;
	float output;

    //uint_8 state[4];
	//左边
	s1=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
	s2=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
	//右边
	s3=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10);
	s4=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);

	//左转
    if(s1==s3==s4==0&&s2==1) cur_error=-1;//0100
    else if(s1==s2==1&&s3==s4==0) cur_error=-2;//1100
    else if(s1==1&&s2==s3==s4==0) cur_error=-6;//1000
	//右转     
    else if(s1==s2==s4==0&&s3==1) cur_error=1;//0010
    else if(s1==s2==0&&s3==s4==1) cur_error=2;//0011
    else if(s1==s2==s3==0&&s4==1) cur_error=6;//0001
	
    else  cur_error=0;

    integral += cur_error;
	//积分限幅
	if(integral>80) integral=80;
	else if(integral<-80) integral=-80;
	else integral=integral;
	
    output=(uint16_t)(Kp*cur_error+Ki*integral+Kd*(cur_error-last_error));
//	  output=Kp*cur_error+Ki*integral+Kd*(cur_error-last_error);
    last_error=cur_error;

    return output;

}



//float PID_realize(PID*pid,float actrual)
//{
//	pid->actrual=actrual;
//	pid->err_current=pid->target-pid->actrual;
//	pid->err_sum+=pid->err_current;
//	pid->actrual=pid->Kp*pid->err_current+pid->Ki*pid->err_sum+pid->Kd*(pid->err_current-pid->err_last);
//	pid->err_last=pid->err_current;
//	return pid->actrual;
//}


