#include "include.h"
#include "map.h"
#include "action.h"
#include "findline.h"

uint16_t  SUM_HUAN=0;//��ǰצ�Ӽ��˻��ĸ�����צ�������ֻ�ܼ�4����
int HUAN_pushed=0;//�����ƵĻ��ĸ�����צ���ϼ����ͻ����Ƶ����棬����У���Ҫ���ڵ�����ͣ�£����Լ��ƽ�ȥ
uint16_t Direction=QIAN;//��ͷ����
uint16_t AddressX=1;//��ֵΪ��ʼ����
uint16_t AddressY=0;
int x,y,daowei=0,turn_case=0;



//////////·�����꣬��������ĳ����㣬ÿһ��������һ��ֱ�ߵ��յ㣬�յ㴦��������ӱ��Ͼͻ������׻�
///////�з�������Ҳ�ɱ�ע�ϣ�����д͵������
/////��'O'��ʾֻ�Ʋ��У���pick������
uint8_t way_x[]={3,5,5,5,5,5,3,3,5,5,1,1,5,5,5,1,1,5,5,2,2,5,5,5,3,3}, 
				way_y[]={7,7,5,4,2,1,1,6,6,7,7,5,5,6,1,1,3,3,2,2,3,3,4,1,1,0};
uint8_t map[9][11]={
	
	//��X
	/*��0*/	'x',    'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'    ,'x'  ,
	

	/*��1*/ 'Z',    '+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'+'  ,'+'  ,'x'  ,'+'    ,'x'  ,

	/*��2*/ 'x',    '+'  ,'+'  ,'x'  ,'+'  ,'+'  ,'+'  ,'+'  ,'+'  ,'x'    ,'x'  ,

	/*��3*/ 'x',    '+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'+'  ,'+'    ,'x'  ,

	/*��4*/ 'x',    '+'  ,'+'  ,'+'  ,'+'  ,'h'  ,'+'  ,'+'  ,'+'  ,'+'    ,'x'  ,

	/*��5*/ 'x',    '+'  ,'+'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'    ,'x'  ,

	/*��6*/ 'v',    '+'  ,'+'  ,'+'  ,'+'  ,'+'  ,'+'  ,'V'  ,'+'  ,'+'    ,'x'  ,

	/*��7*/ 'x',    'w'  ,'+'  ,'+'  ,'+'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'    ,'x'  ,

	
	/*��8*/	'x',    'x'  ,'v'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'    ,'x'
	//Y��// ��0     ��1   ��2   ��3   ��4   ��5   ��6   ��7   ��8   ��9     ��10
	 };
/////////��ͼ���ݺ�ԭͼһģһ�������е�ʱ����ͼ�ϵ�ֵ�����ؼ�ͣ�º�һ��ʱ������´��ʼ����
uint8_t mapbackup[9][11]={
	
	//��X
	/*��0*/	'x',    'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'    ,'x'  ,
	

	/*��1*/ 'Z',    '+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'+'  ,'+'  ,'x'  ,'+'    ,'x'  ,

	/*��2*/ 'x',    '+'  ,'+'  ,'x'  ,'+'  ,'+'  ,'+'  ,'+'  ,'+'  ,'x'    ,'x'  ,

	/*��3*/ 'x',    '+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'+'  ,'+'    ,'x'  ,

	/*��4*/ 'x',    '+'  ,'+'  ,'+'  ,'+'  ,'h'  ,'+'  ,'+'  ,'+'  ,'+'    ,'x'  ,

	/*��5*/ 'x',    '+'  ,'+'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'    ,'x'  ,

	/*��6*/ 'v',    '+'  ,'+'  ,'+'  ,'+'  ,'+'  ,'+'  ,'V'  ,'+'  ,'+'    ,'x'  ,

	/*��7*/ 'x',    'w'  ,'+'  ,'+'  ,'+'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'    ,'x'  ,

	
	/*��8*/	'x',    'x'  ,'v'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'    ,'x'
	//Y��// ��0     ��1   ��2   ��3   ��4   ��5   ��6   ��7   ��8   ��9     ��10
	 };
	 
void position(void)
{
	int i;
	if(!is_line)
				{
					adspeed[0]=adspeed[1]=0;
					if(tr==1)
					{
						speed[0]=-0.5*orspeed;
						speed[1]=orspeed;
						speed[2]=-0.5*orspeed;
						speed[3]=orspeed;	
					}
					else
					{
						speed[0]=orspeed;
						speed[1]=-0.5*orspeed;
						speed[2]=orspeed;
						speed[3]=-0.5*orspeed;	
					}
				}
				else
				{
					if(countline>0)
					{
						count++;

						i=0;
						while(is_line)
						{
							HAL_Delay(1);
							i++;
							if(i>300)
							{
								count--;
								break; 
							}
						}
						countline=0;
					}
					if(count>0)
					{
							switch(Direction)
							{
								case QIAN:
									AddressY++;
								break;
								case HOU:
									AddressY--;
								break;
								case ZUO:
									AddressX--;
								break;
								case YOU:
									AddressX++;
								break;
							}
							count=0;
					}

					if(readline(0)>2000||readline(1)>2000)
						tr=1;
					else if(readline(2)>2000||readline(3)>2000)
						tr=-1;
				}
}
	 
void RUN()
{
					if((fabs(way_x[step]-AddressX)+fabs(way_y[step]-AddressY)<2)||map[AddressX+x][AddressY+y]=='o')
					{
						speed[0]=speed[1]=speed[2]=speed[3]=SPEEDMAX*7/12;
						if(fabs(way_x[step]-AddressX)+fabs(way_y[step]-AddressY)<2)
							speed[0]=speed[1]=speed[2]=speed[3]=SPEEDMAX*5/12;
						if((fabs(way_x[step]-AddressX)+fabs(way_y[step]-AddressY)<2)&&HUAN_pushed>1)
							speed[0]=speed[1]=speed[2]=speed[3]=15;
					}
					else if(step<sizeof(way_x)/4-1)
					{
						speed[0]=speed[1]=speed[2]=speed[3]=orspeed=SPEEDMAX;
					}
					
	if(map[AddressX][AddressY]=='o'||map[AddressX][AddressY]=='O')//�񻷣���ʱ�ٶȽ��ͣ����ǲ���ͣ��
	{
		pick();
	}
	if(way_x[step]==AddressX&&way_y[step]==AddressY)//����Ŀ��㣬ɨ�賵��Χ��û������㣬�оͽ���ת������㣬�Խ�����һ������
	{
		arrive_point();
	}
	
	
	//�жϵ�ǰ�㳵ǰ��ʲô��ִ����Ӧ����
	switch(Direction)
	{
		case QIAN:
			y=1;
			x=0;
		break;
		case HOU:
			y=-1;
			x=0;
		break;
		case ZUO:
			x=-1;
			y=0;
		break;
		case YOU:
			x=1;
			y=0;
		break;
	}
		switch(map[AddressX+x][AddressY+y])
		{
			case 'h':
				ZengYi();
				break;
			case 'V':
				Three_Score();
				break;
			case 'v':
				Two_Score();
				break;
			case 'w':
				One_Score();
				break;
			case 'Z':
				Home();
				break;
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//����Ŀ����ж���һ�������ģ��Զ�ת��
	if(daowei)
	{
		step++;
		if(way_x[step]-AddressX==0)
		{
			if(way_y[step]-AddressY>0)
			{
				switch(Direction)
				{
					case YOU:
						TURN(90);
					break;
					case ZUO:
						TURN(-90);
					break;
					case HOU:
						TURN(90);
						TURN(90);
					break;
				}
				Direction=QIAN;
			}
			else if(way_y[step]-AddressY<0)
			{
				switch(Direction)
				{
					case ZUO:
						TURN(90);
					break;
					case YOU:
						TURN(-90);
					break;
					case QIAN:
						TURN(90);
						TURN(90);
					break;
				}
				Direction=HOU;	
			}
			speed[0]=speed[1]=speed[3]=speed[2]=0;

		}
		else if(way_x[step]-AddressX>0)
		{
			switch(Direction)
				{
					case QIAN:
						TURN(-90);
					break;
					case HOU:
						TURN(90);
					break;
					case ZUO:
						TURN(90);
						TURN(90);
					break;
				}
				Direction=YOU;
		}
		else if(way_x[step]-AddressX<0)
		{
			switch(Direction)
				{
					case QIAN:
						TURN(90);
					break;
					case HOU:
						TURN(-90);
					break;
					case YOU:
						TURN(90);
						TURN(90);
					break;
				}
				Direction=ZUO;
		}
			speed[0]=speed[1]=speed[3]=speed[2]=0;
			HAL_Delay(50);
		daowei=0;
		findline=1;
	}

//	if(SUM_HUAN==0)
//	{
//		TargetDuoJi[0]=ZhuaZi_KAI;
//		BJ_TO_CM(1);
//		TargetDuoJi[1]=ZhuaZi_SUO;
//	}
}
	 
	 
	 



