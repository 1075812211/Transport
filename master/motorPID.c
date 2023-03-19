#include "motorpid.h"
#include "include.h"
#include "motor.h"
PidTypeDef motor_pid[4];
float motor_target_speed[4]={0};
float motor_speed[4]={0};
float motorpid[3]={15,5,5};//设定PID三个参数

uint8_t MotorPID_ENA=0;


#define DECAY_RATE 0.95f
#define LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }
void PID_Init(PIDControl *pid,float kp,float ki,float kd){
	pid->kp=kp;
	pid->ki=ki;
	pid->kd=kd;
	pid->lastError=0;
	pid->totalError=0;
}
void pid_param_init(PidTypeDef *pid, uint8_t mode, const float PID[3], float max_out, float max_iout,  float I_Separation, float Dead_Zone, float gama, int angle_max, int angle_min)
{
    if (pid == NULL || PID == NULL)
    {
        return;
    }

    pid->mode = mode;
    pid->Kp = PID[0];
    pid->Ki = PID[1];
    pid->Kd = PID[2];
    pid->max_out = max_out;
    pid->max_iout = max_iout;
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    pid->error[0] = pid->error[1] = pid->error[2] = pid->Pout = pid->Iout = pid->Dout = pid->out = 0.0f;
    pid->I_Separation = I_Separation;
    pid->Dead_Zone = Dead_Zone;
    pid->gama = gama;
    pid->angle_max = angle_max;
    pid->angle_min = angle_min;
}
float pid_caculate(PidTypeDef *pid, const float ref, const float set)
{
  	uint8_t index;
	if (pid == NULL)
	{
			return 0.0f;
	}
	pid->error[0] = set - ref;

    if(fabs(pid->error[0])>pid->I_Separation)//误差过大，采用积分分离
    {
    	index=0;
    }
    else
    {
    	index=1;
    }
	pid->set = set;
	pid->fdb = ref;

    if (pid->mode == PID_POSITION)
    {
        pid->Pout = pid->Kp * pid->error[0];
        pid->Iout = index*(pid->Iout+ pid->Ki * pid->error[0]);
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - pid->error[1]);
        pid->Dout=pid->Kd*(1- pid-> gama)*(pid->Dbuf[0])+pid-> gama* pid-> lastdout;
        LimitMax(pid->Iout, pid->max_iout);
        pid->out = pid->Pout + pid->Iout + pid->Dout;
        LimitMax(pid->out, pid->max_out);
    }
    else if (pid->mode == PID_DELTA)
    {
        pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);
        pid->Iout = pid->Ki * pid->error[0];
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
        pid->Dout = pid->Kd * pid->Dbuf[0];
        pid->out += pid->Pout + pid->Iout + pid->Dout;
        LimitMax(pid->out, pid->max_out);
    }

		
	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];
	pid-> lastdout=pid->Dout;
    return pid->out;
}
///////////////////////////////////////////////////////////
float e;
int16_t out;


//电机速度环任务，放在定时器里 10ms
void Motor_PID_Control_Task(void)
{
//判断使能
	if(MotorPID_ENA){
		for(int i=0;i<4;i++){
			//PID计算函数
			motor_speed[i]=pid_caculate(&motor_pid[i],ralspeed[i],speed[i]+adspeed[i]);
			Motor_Set_Speed(i,motor_speed[i]);
		}
	}
	else {//刹车
		for(int i=0;i<4;i++){
			Motor_Set_Speed(i,0);
		}
				HAL_GPIO_WritePin(M1P_GPIO_Port,M1P_Pin,GPIO_PIN_SET);//抱死
				HAL_GPIO_WritePin(M1N_GPIO_Port,M1N_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(M2P_GPIO_Port,M2P_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(M2N_GPIO_Port,M2N_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(M3P_GPIO_Port,M3P_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(M3N_GPIO_Port,M3N_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(M4P_GPIO_Port,M4P_Pin,GPIO_PIN_SET);
				HAL_GPIO_WritePin(M4N_GPIO_Port,M4N_Pin,GPIO_PIN_SET);
	}
}

void Motor_PID_Init(void){
	for(int i=0;i<4;i++){
		pid_param_init(&motor_pid[i],PID_DELTA,motorpid,8000,4000,9999,0,0,0,0);//四个电机的PID结构体初始化
	}
}




