#include "ccd.h"
#include "adc.h"
#include "tim.h"
uint16_t ADC_Value[8];
uint16_t ADC_List[127];
volatile uint8_t is_line=0,countline=0,last_isline=0;

float CCD_Pos=0;//最后给巡线PID的输入值，在.h中extern
//巡线PID输出给电机PID的目标值可以在电机目标速度基础上左右同时增减，也可以只增不减(场地比较差的情况速度会变得很快)

void CCD_CLK_Handle(void){		//20khz 定时器中断
	static uint8_t step=0;
	static int32_t c=0,p=0,s=0,sum=0;
	switch(step){
		case 0:{
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);//给CCD一定时间高电平信号，表示开始读取
			step++;
		}break;
		case 1:{//再等一个周期
			step++;
		}break;
		case 2:{
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);
			step++;
			c=0;
			p=0;
			s=0;
			sum=0;
		}break;
		case 3:{//127位CCD输出，存在ADC_List，CCD黑色ADC位低，白色为高，可以考虑去掉4096-
			c+=(4096-ADC_Value[0])*(p-63);//直接算出63左右两边的差值，权重由外向内递减
			s+=4096-ADC_Value[0];//记录总和，按照权重值来计算偏差
			ADC_List[p]=ADC_Value[0];
			if(ADC_Value[0]>2000)//记录处于黑或白线当中的ADC数，大于即白线
				sum++;
			if(++p>=127){//舍掉最后一个,应该是最后一个有问题
				step++;
			}
		}break;
		case 4:{
			CCD_Pos=c/(s/1000)/100/3.0;//CCD左右相减的差值作为巡线偏差输入，/100是整除缩小进行滤波，最后输出浮点数x.0不能少
			last_isline=is_line;
			if(sum>40)//处于线中的ADC数超过一定值即为正在经过一条线
			{
				CCD_Pos=0;
				is_line=1;
			}
			else
				is_line=0;
			if(last_isline==0)//数线，表示经过了几条线，在外部给countline赋0
				countline+=is_line;
			step=5;
			p=0;
		}break;
		case 5:{
			if(++p>20){
				step=0;
			}
		}break;
	}

}

void CCD_Init(void){
	HAL_TIM_PWM_Start(&htim11,TIM_CHANNEL_1);//与CCD同步的引脚，控制CCD输出
	HAL_TIM_Base_Start_IT(&htim11);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADC_Value,1);//ADC读取CCD，每次只用读一个，CCD按序输出
}

