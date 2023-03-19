#ifndef _MOTOR_
#define _MOTOR_

#include "stm32f4xx_hal.h"
#include "main.h"
//����ǶȺ궨��
//#define Gimbal_Compare_0 970 //��̨
//#define Gimbal_Compare_Catch_left 1870
//#define Gimbal_Compare_90 1630
//#define Gimbal_Compare_Catch_right 1360
//#define Gimbal_Compare_180 2245
//#define Arm_Compare_min 1260 //��
//#define Arm_Compare_Catch_middle 1465//ץ��� �м�
//#define Arm_Compare_Catch_beside 1690 //����
//#define Arm_Compare_max 1925 
//#define Arm_Compare_0 Arm_Compare_min+64
//#define Arm_Compare_1 Arm_Compare_min+49


//#define Claw_Compare_min 1900 //צ��
//#define Claw_Compare_middle 1535
//#define Claw_Compare_max 1010

//#define Claw_Compare_1 Claw_Compare_max+200 //�����
//#define Claw_Compare_2 Claw_Compare_max+90  //װ��

//#define Wrist_Compare_0 550 //��
//#define Wrist_Compare_180 2500

//#define Gimbal 3
//#define Arm    2
//#define Wrist  1
//#define Claw   0


int16_t Motor_Get_Speed(uint8_t ch);
void Motor_Set_Speed(uint8_t ch,int16_t speed);
void Motor_Encoder_Init(void);
void Motor_Set_Speed_X_Y_Yaw(int16_t x,int16_t y,int16_t yaw);
void Motor_Encoder_Task(void);


#endif
