#include "include.h"
#include "findline.h" 
struct pidad adpid;
int adspeed[4]={0};
float lin[4];

float findlinepid[3]={1.7,0.05,1.1};
PidTypeDef Findline_PID;
volatile uint8_t findline=0;

volatile uint8_t GD_Value[4];
volatile uint8_t back_is_line=0;
uint8_t GD_White=0;//反电平光电，黑色为1
/*
灰度排列
			头
	 0 1 2 3
	 7 6 5 4
			尾
*/

void Find_Line()
{
	GD_Value[0]=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_12);
	GD_Value[1]=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15);
	GD_Value[2]=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4);
	GD_Value[3]=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5);
	if(GD_Value[0]==GD_White&&GD_Value[3]==GD_White)
	{
		back_is_line=1;
	}
	else
	{
		back_is_line=0;
	}
					if(backing)//倒车使用后灰度巡线
					{
					/////光电不用pid

						if(GD_Value[2]==1&&GD_Value[1]==1)
						{
							adspeed[0]=adspeed[1]=adspeed[2]=adspeed[3]=0;
						}
						else
						{
							adspeed[1]=adspeed[0]=(GD_Value[3]-GD_Value[0])*25
																	 +(GD_Value[2]-GD_Value[1])*15;
							adspeed[2]=adspeed[3]=-1*adspeed[0];
						}		
					}
					else if(findline)
					{
						adspeed[1]=adspeed[0]=pid_caculate(&Findline_PID,-CCD_Pos,0);
						adspeed[2]=adspeed[3]=-1*adspeed[0];
//						//第二种模式，只增不减
//						adspeed[0]=pid_caculate(&Findline_PID,-CCD_Pos,0);
//						if(adspeed[0]>0)
//						{
//							adspeed[1]=adspeed[0];
//							adspeed[2]=adspeed[3]=0;
//						}
//						else
//						{
//							adspeed[2]=adspeed[3]=-1*adspeed[0];
//							adspeed[1]=adspeed[0]=0;
//						}
						
						
						
						//老版不规范，PID没放结构体
						//灰度模块线性转化
//////							lin[0]=(int)(readline(0)-readline(3));
//////							lin[1]=(int)(readline(1)-readline(2));
//////							if(lin[0]>500||lin[0]<-500)
//////							{
//////								lin[0]=lin[0]/500.0;
//////								if(lin[1]>500||lin[1]<-500)
//////								{
//////									lin[1]=((3000*fabs(lin[1])/lin[1])-lin[1])/500.0;
//////								}
//////								else
//////								{
//////									lin[1]=6*fabs(lin[0])/lin[0];
////////									lin[0]=lin[0];
//////								}
//////							}
//////							else
//////							{
//////								lin[0]=0;
//////								if(lin[1]>500||lin[1]<-500)
//////									lin[1]=lin[1]/500.0;
//////								else
//////									lin[1]=0;
//////							}
//////							adpid.aderr =lin[0]+lin[1];

					}
					else
					{
						adspeed[0]=adspeed[1]=adspeed[2]=adspeed[3]=0;
					}
}
