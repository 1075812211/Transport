#include "include.h"
#include "map.h"
#include "action.h"
#include "findline.h"

uint16_t  SUM_HUAN=0;//当前爪子夹了环的个数，爪子上最多只能夹4个环
int HUAN_pushed=0;//挡板推的环的个数，爪子上夹满就会存进推的里面，如果有，需要先在单倍区停下，会自己推进去
uint16_t Direction=QIAN;//车头方向
uint16_t AddressX=1;//初值为初始坐标
uint16_t AddressY=0;
int x,y,daowei=0,turn_case=0;



//////////路线坐标，除了最初的出发点，每一个坐标是一条直线的终点，终点处如果在柱子边上就会自行套环
///////敌方的柱子也可标注上，重新写偷环程序
/////大'O'表示只推不夹，在pick函数里
uint8_t way_x[]={3,5,5,5,5,5,3,3,5,5,1,1,5,5,5,1,1,5,5,2,2,5,5,5,3,3}, 
				way_y[]={7,7,5,4,2,1,1,6,6,7,7,5,5,6,1,1,3,3,2,2,3,3,4,1,1,0};
uint8_t map[9][11]={
	
	//↓X
	/*列0*/	'x',    'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'    ,'x'  ,
	

	/*列1*/ 'Z',    '+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'+'  ,'+'  ,'x'  ,'+'    ,'x'  ,

	/*列2*/ 'x',    '+'  ,'+'  ,'x'  ,'+'  ,'+'  ,'+'  ,'+'  ,'+'  ,'x'    ,'x'  ,

	/*列3*/ 'x',    '+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'+'  ,'+'    ,'x'  ,

	/*列4*/ 'x',    '+'  ,'+'  ,'+'  ,'+'  ,'h'  ,'+'  ,'+'  ,'+'  ,'+'    ,'x'  ,

	/*列5*/ 'x',    '+'  ,'+'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'    ,'x'  ,

	/*列6*/ 'v',    '+'  ,'+'  ,'+'  ,'+'  ,'+'  ,'+'  ,'V'  ,'+'  ,'+'    ,'x'  ,

	/*列7*/ 'x',    'w'  ,'+'  ,'+'  ,'+'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'    ,'x'  ,

	
	/*列8*/	'x',    'x'  ,'v'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'    ,'x'
	//Y→// 行0     行1   行2   行3   行4   行5   行6   行7   行8   行9     行10
	 };
/////////地图备份和原图一模一样，运行的时候会改图上的值，最后回家停下后一段时候会重新从最开始运行
uint8_t mapbackup[9][11]={
	
	//↓X
	/*列0*/	'x',    'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'    ,'x'  ,
	

	/*列1*/ 'Z',    '+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'+'  ,'+'  ,'x'  ,'+'    ,'x'  ,

	/*列2*/ 'x',    '+'  ,'+'  ,'x'  ,'+'  ,'+'  ,'+'  ,'+'  ,'+'  ,'x'    ,'x'  ,

	/*列3*/ 'x',    '+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'+'  ,'+'    ,'x'  ,

	/*列4*/ 'x',    '+'  ,'+'  ,'+'  ,'+'  ,'h'  ,'+'  ,'+'  ,'+'  ,'+'    ,'x'  ,

	/*列5*/ 'x',    '+'  ,'+'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'    ,'x'  ,

	/*列6*/ 'v',    '+'  ,'+'  ,'+'  ,'+'  ,'+'  ,'+'  ,'V'  ,'+'  ,'+'    ,'x'  ,

	/*列7*/ 'x',    'w'  ,'+'  ,'+'  ,'+'  ,'+'  ,'o'  ,'+'  ,'o'  ,'+'    ,'x'  ,

	
	/*列8*/	'x',    'x'  ,'v'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'  ,'x'    ,'x'
	//Y→// 行0     行1   行2   行3   行4   行5   行6   行7   行8   行9     行10
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
					
	if(map[AddressX][AddressY]=='o'||map[AddressX][AddressY]=='O')//捡环，捡环时速度降低，但是不能停下
	{
		pick();
	}
	if(way_x[step]==AddressX&&way_y[step]==AddressY)//到达目标点，扫描车周围有没有特殊点，有就将车转向特殊点，以进行下一步动作
	{
		arrive_point();
	}
	
	
	//判断当前点车前是什么，执行相应动作
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
	//到达目标点判断下一个点在哪，自动转弯
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
	 
	 
	 



