#include "include.h"
#include "main.h"

/*
���ù��GD_Value[0-3] A12 A15 B4 B5
CCD�ź� B8
CCD��ȡADC A4
CCDʱ��CLK B9

���PWM A8-11
������� B0B1 B2B10 B12B13 B14B15
������TIM2-5  A5B3 A6A7 B6B7 A0A1

���TIM9 A2 A3

��������������ӷ�
PUL+ ���� PC13
DIR+ ���� PC14
ENA+ ʹ�� PC15


*/



volatile int ZhuaZi_KAI=123,
						 ZhuaZi_HE=92,
						 ZhuaZi_UnStart=150,

						 ZhuaZi_SHENG=103,
						 ZhuaZi_SUO=69,
						 ZhuaZi_ZHONG=69;

volatile int TargetDuoJi[2]={95,105},NowDuoJi[2]={95,105};
volatile int bline,
		count=0,
		step=0,
		turning=0,
		lastangle,
		half=0,
		orspeed;

int tr=1,max,min;
int targetspeed[4]={0};
int SPEEDMAX;

int readline(int x)//��CCD�ֳ�4�� �� Ҳ���Ը�һ�Ķ�ȡcountline
{
	if(x<4)
	{
		int ti,sum=0;
	//	0-30 32-62 64-94 96--126 
		for(ti = x*32 ; ti <= x*32+30 ; ti++)
			sum+=ADC_List[ti];
		return sum/15;
	}
	else
	{
		return GD_Value[x-4];
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==&htim11)
	{
		CCD_CLK_Handle();
		BJ_START();
	}
	if(htim==&htim10)
	{ uint32_t TIM_CHANNEL_[2]={TIM_CHANNEL_1,TIM_CHANNEL_2};
		int i;
		for(i=0;i<2;i++)//����Ƕ��趨�������仯
		{
			if(NowDuoJi[i]<TargetDuoJi[i])
			{
				NowDuoJi[i]++;
				__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_[i],NowDuoJi[i]);
			}
			else if(NowDuoJi[i]>TargetDuoJi[i])
			{
				NowDuoJi[i]--;
				__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_[i],NowDuoJi[i]);
			}
		} 
		
		Motor_Encoder_Task();
		Find_Line();
		Motor_PID_Control_Task();
	}
	

}



void ALL_Start()
{
	
	HAL_Delay(10);

	CCD_Init();
	
	//������
	Motor_Encoder_Init();
	
	HAL_TIM_Base_Start_IT(&htim10);
	HAL_TIM_Base_Start_IT(&htim11);

	BJ_TO_CM(2);
	HAL_Delay(500);
	//��� ��ǰ��ʼ״̬
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);
	NowDuoJi[1]=TargetDuoJi[1]=ZhuaZi_SHENG;
	NowDuoJi[0]=TargetDuoJi[0]=ZhuaZi_UnStart;

	speed[0]=speed[1]=speed[2]=speed[3]=0;
	Motor_PID_Init();//���pid
	pid_param_init(&Findline_PID,PID_POSITION,findlinepid,30,20,30,0.5,0,0,0);//Ѳ��PID
		
	while(0);//io�����꣬����ͨ�����CCDֵ�������տ�ʼ��ֽ��ס
	
	BJ_TO_CM(4);
	TargetDuoJi[0]=ZhuaZi_HE;
	TargetDuoJi[1]=ZhuaZi_SHENG;
}


