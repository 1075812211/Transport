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
    PID_POSITION = 0,//λ��ʽPID
    PID_DELTA, //����ʽPID
} PID_MODE;

typedef struct PidTypeDef
{
    float Dead_Zone; //���������ֵ
    uint8_t mode;
    //PID ������
    float Kp;
    float Ki;
    float Kd;

    float max_out;  //������
    float max_iout; //���������

    float set; //�趨ֵ
    float fdb; //����ֵ

    float out;
    float lastout;
    float Pout;
    float Iout;
    float Dout;
    float Dbuf[3];  //΢���� 0���� 1��һ�� 2���ϴ�
    float error[3]; //����� 0���� 1��һ�� 2���ϴ�
    int angle_max;
    int angle_min;	//�Ƕ�����ֵ ����һ��Բ�ڣ�0���360�����ڣ���max=360��min=0
    //			��һ������� 0��8192���ڣ���max=8192��min=0
    float I_Separation; //���ַ�����ֵ
    float gama;			//΢�������˲�ϵ��
    float lastdout;		//��һ��΢�����


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
