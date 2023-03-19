#include "include.h"
#include "bujindianji.h"
int  pwmzt=1,bjdj=0,bjfx=0;
volatile int maichong=0,fd;
volatile float high=0;

void BJ_START(void)
{
		if(bjdj)
		{
			maichong++;
			if(maichong>fd)
				bjdj=0;

//共阴极接法
//PUL+ 脉冲PC13
//DIR+ 方向PC14
//ENA+ 使能PC15
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_RESET);
			if(bjfx==1)
			{
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,GPIO_PIN_RESET);
			}
			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
			high+=bjfx*2.0/16000;
			
			//16细分8导程

		}
		else
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,GPIO_PIN_SET);
		}
		
}

void BJ_TO_CM(float x)
{
//	while(maichong<fd);
	bjdj=0;
	if(x-high<0)
	{
		bjfx=-1;
		fd=(high-x)*8000;
		maichong=0;
	}
	else
	{
		bjfx=1;
		fd=(x-high)*8000;
		maichong=0;
	}
	bjdj=1;
}
