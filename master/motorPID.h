#ifndef _MOTOR_PID_
#define _MOTOR_PID_
#include "stm32f4xx_hal.h"

typedef struct{
	float kp,ki,kd;
	float lastError;
	float totalError;
}PIDControl;
typedef enum
{
    PID_POSITION = 0,//位置式PID
    PID_DELTA, //增量式PID
} PID_MODE;

typedef struct PidTypeDef
{
    float Dead_Zone; //误差死区阈值
    uint8_t mode;
    //PID 三参数
    float Kp;
    float Ki;
    float Kd;

    float max_out;  //最大输出
    float max_iout; //最大积分输出

    float set; //设定值
    float fdb; //反馈值

    float out;
    float lastout;
    float Pout;
    float Iout;
    float Dout;
    float Dbuf[3];  //微分项 0最新 1上一次 2上上次
    float error[3]; //误差项 0最新 1上一次 2上上次
    int angle_max;
    int angle_min;	//角度相邻值 如在一个圆内，0°和360°相邻，则max=360，min=0
    //			在一个电机内 0和8192相邻，则max=8192，min=0
    float I_Separation; //积分分离阈值
    float gama;			//微分先行滤波系数
    float lastdout;		//上一次微分输出


} PidTypeDef;
void Motor_PID_Control_Task(void);
void Motor_PID_Init(void);
extern PidTypeDef motor_pid[4];
extern uint8_t MotorPID_ENA;
float pid_caculate(PidTypeDef *pid, const float ref, const float set);
void pid_param_init(PidTypeDef *pid, uint8_t mode, const float PID[3], float max_out, float max_iout,  float I_Separation, float Dead_Zone, float gama, int angle_max, int angle_min);
extern float motorpid[3];
extern float motor_target_speed[4];
extern float motor_speed[4];

#endif
