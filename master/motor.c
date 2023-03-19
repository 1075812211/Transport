#include "motor.h"
#include "main.h"
#include "motorpid.h"
#include "include.h"
int ralspeed[4],speed[4],backing=0;

void Motor_Set_Speed(uint8_t ch,int16_t speed){
	if(speed>1000)speed=1000;
	if(speed<-1000)speed=-1000;
	switch(ch){//GPIO_Port连接电机驱动方向控制的两个引脚
		case 0:{
			if(speed>0){
				TIM1->CCR1=speed;//pwm占空比
				HAL_GPIO_WritePin(M1P_GPIO_Port,M1P_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(M1N_GPIO_Port,M1N_Pin,GPIO_PIN_SET);
			}else{
				TIM1->CCR1=-speed;
				HAL_GPIO_WritePin(M1P_GPIO_Port,M1P_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(M1N_GPIO_Port,M1N_Pin,GPIO_PIN_RESET);
			}
		}break;
		case 1:{
			if(speed>0){
				TIM1->CCR2=speed;
				HAL_GPIO_WritePin(M2P_GPIO_Port,M2P_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(M2N_GPIO_Port,M2N_Pin,GPIO_PIN_RESET);
			}else{
				TIM1->CCR2=-speed;
				HAL_GPIO_WritePin(M2P_GPIO_Port,M2P_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(M2N_GPIO_Port,M2N_Pin,GPIO_PIN_SET);
			}
		}break;
		case 2:{
			if(speed>0){
				TIM1->CCR3=speed;
				HAL_GPIO_WritePin(M3P_GPIO_Port,M3P_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(M3N_GPIO_Port,M3N_Pin,GPIO_PIN_SET);
			}else{
				TIM1->CCR3=-speed;
				HAL_GPIO_WritePin(M3P_GPIO_Port,M3P_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(M3N_GPIO_Port,M3N_Pin,GPIO_PIN_RESET);
			}
		}break;
		case 3:{
			if(speed>0){
				TIM1->CCR4=speed;
				HAL_GPIO_WritePin(M4P_GPIO_Port,M4P_Pin,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(M4N_GPIO_Port,M4N_Pin,GPIO_PIN_SET);
			}else{
				TIM1->CCR4=-speed;
				HAL_GPIO_WritePin(M4P_GPIO_Port,M4P_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(M4N_GPIO_Port,M4N_Pin,GPIO_PIN_RESET);
			}
		}break;
	}
	
} 


//读取编码器任务，放在定时器里，在PID函数之前 10ms
void Motor_Encoder_Task(void){
	ralspeed[0]=(int16_t)(TIM2->CNT)-30000;
	ralspeed[1]=(int16_t)(TIM3->CNT)-30000;
	ralspeed[2]=(int16_t)(TIM4->CNT)-30000;
	ralspeed[3]=(int16_t)(TIM5->CNT)-30000;

	TIM2->CNT=30000;
	TIM3->CNT=30000;
	TIM4->CNT=30000;
	TIM5->CNT=30000;	
}
//定时器编码器模式初始化
void Motor_Encoder_Init(void){
	TIM2->CNT=30000;
	TIM3->CNT=30000;
	TIM4->CNT=30000;
	TIM5->CNT=30000;	
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_ALL);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
}



int16_t Motor_Get_Speed(uint8_t ch){
	return ralspeed[ch];
}




////全向轮解算，非全向轮直接给motor_target_speed赋值
void Motor_Set_Speed_X_Y_Yaw(int16_t x,int16_t y,int16_t yaw){
	motor_target_speed[0]=-y+yaw;
	motor_target_speed[1]=x+yaw;
	motor_target_speed[2]=y+yaw;
	motor_target_speed[3]=-x+yaw;
}





