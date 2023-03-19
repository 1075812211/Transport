#include "ccd.h"
#include "adc.h"
#include "tim.h"
uint16_t ADC_Value[8];
uint16_t ADC_List[127];
volatile uint8_t is_line=0,countline=0,last_isline=0;

float CCD_Pos=0;//����Ѳ��PID������ֵ����.h��extern
//Ѳ��PID��������PID��Ŀ��ֵ�����ڵ��Ŀ���ٶȻ���������ͬʱ������Ҳ����ֻ������(���رȽϲ������ٶȻ��úܿ�)

void CCD_CLK_Handle(void){		//20khz ��ʱ���ж�
	static uint8_t step=0;
	static int32_t c=0,p=0,s=0,sum=0;
	switch(step){
		case 0:{
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);//��CCDһ��ʱ��ߵ�ƽ�źţ���ʾ��ʼ��ȡ
			step++;
		}break;
		case 1:{//�ٵ�һ������
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
		case 3:{//127λCCD���������ADC_List��CCD��ɫADCλ�ͣ���ɫΪ�ߣ����Կ���ȥ��4096-
			c+=(4096-ADC_Value[0])*(p-63);//ֱ�����63�������ߵĲ�ֵ��Ȩ���������ڵݼ�
			s+=4096-ADC_Value[0];//��¼�ܺͣ�����Ȩ��ֵ������ƫ��
			ADC_List[p]=ADC_Value[0];
			if(ADC_Value[0]>2000)//��¼���ںڻ���ߵ��е�ADC�������ڼ�����
				sum++;
			if(++p>=127){//������һ��,Ӧ�������һ��������
				step++;
			}
		}break;
		case 4:{
			CCD_Pos=c/(s/1000)/100/3.0;//CCD��������Ĳ�ֵ��ΪѲ��ƫ�����룬/100��������С�����˲���������������x.0������
			last_isline=is_line;
			if(sum>40)//�������е�ADC������һ��ֵ��Ϊ���ھ���һ����
			{
				CCD_Pos=0;
				is_line=1;
			}
			else
				is_line=0;
			if(last_isline==0)//���ߣ���ʾ�����˼����ߣ����ⲿ��countline��0
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
	HAL_TIM_PWM_Start(&htim11,TIM_CHANNEL_1);//��CCDͬ�������ţ�����CCD���
	HAL_TIM_Base_Start_IT(&htim11);
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADC_Value,1);//ADC��ȡCCD��ÿ��ֻ�ö�һ����CCD�������
}

