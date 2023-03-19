#ifndef __INCLUDE_H
#define __INCLUDE_H		
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"
#include "math.h"
#include "string.h"
#include "bujindianji.h"
#include "map.h"
#include "findline.h"
#include "ccd.h"
#include "motorpid.h"
#include "motor.h"


void ALL_Start(void);

void SUDU_HUAN(void);
void RUN_WAY(void);

int readline(int x);



extern volatile int TargetDuoJi[2],NowDuoJi[2],ZhuaZi_KAI,ZhuaZi_HE,ZhuaZi_SHENG,ZhuaZi_SUO,ZhuaZi_ZHONG;
extern int tr,max,min;;
extern int ralspeed[4],speed[4];
extern int targetspeed[4];
extern PidTypeDef Findline_PID;
extern float findlinepid[3];
extern volatile uint8_t findline;
extern int ralspeed[4], lastline,backing;
extern volatile uint8_t GD_Value[4];
extern volatile uint8_t back_is_line;
extern uint8_t GD_White;
extern int SPEEDMAX;
extern volatile int line[601],
						bline,
						count,
						step,
						half,
						turning,
						lastangle,
						orspeed;//原始速度

#endif
