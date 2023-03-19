#include "action.h"
#include "map.h"
#include "include.h"


void TURN(float t)
{
	int i,j;
	findline=0;
	adspeed[0]=adspeed[1]=0;
	if(turn_case)
	{
		//后转弯
					speed[0]=speed[1]=speed[3]=speed[2]=20;
			findline=1;
				tr=t/90;
						i=0;
						while(!back_is_line)//灰度不在线上
						{
							HAL_Delay(10);
							i++;
							if(i>1400)
								break; 
						}				
					findline=0;
					speed[0]=speed[1]=speed[3]=speed[2]=-40;
						HAL_Delay(60);
					speed[0]=speed[1]=speed[3]=speed[2]=0;
						HAL_Delay(200);
				if(t/90>0)
				{
					speed[0]=-37;
					speed[1]=14;
					speed[2]=-37;
					speed[3]=14;
					j=1;
				}
				else
				{
					speed[0]=14;
					speed[1]=-37;
					speed[2]=14;
					speed[3]=-37;
					j=2;
				}
				HAL_Delay(600);
				i=0;
				while(readline(j)<2000)//另一头的CCD还未检测到线
				{
						HAL_Delay(10);
							i++;
							if(i>1400)
								break; 
				}
				
		}
		else
		{
			//前转弯
			speed[0]=speed[1]=speed[3]=speed[2]=-14;
				backing=1;
				tr=t/90;
					i=0;
					while(!is_line)
					{
						HAL_Delay(10);
						i++;
						if(i>1400)
							break; 
					}				

				speed[0]=speed[1]=speed[3]=speed[2]=0;
					backing=0;
					HAL_Delay(200);
			if(t/90>0)
			{
				speed[0]=-12;
				speed[1]=44;
				speed[2]=-12;
				speed[3]=44;
				j=5;
			}
			else
			{
				speed[0]=44;
				speed[1]=-12;
				speed[2]=44;
				speed[3]=-12;
				j=6;
			}
			HAL_Delay(600);
			i=0;
			while(readline(j)>GD_White)//灰度未检测到线
			{
					HAL_Delay(10);
						i++;
						if(i>1400)
							break; 
			}
		}
		speed[0]=speed[1]=speed[2]=speed[3]=0;
	HAL_Delay(50);
	speed[0]=speed[1]=speed[2]=speed[3]=30;
		findline=1;
	HAL_Delay(100);
		findline=0;

}


void pick(void)
{
	int i;
		if(SUM_HUAN<3&&map[AddressX][AddressY]=='o')
		{
			TargetDuoJi[1]=ZhuaZi_SUO;
			if(SUM_HUAN<3)
			{
					speed[0]=speed[1]=speed[3]=speed[2]=7;	
				findline=1;
					orspeed=20;
				}

			SUM_HUAN++;
				HAL_Delay(300);
				findline=0;
				HAL_Delay(150);
				speed[0]=speed[1]=speed[3]=speed[2]=findline=0;
			BJ_TO_CM(0.6);
			if(high>5)
			{
				HAL_Delay(500);
				speed[0]=speed[1]=speed[3]=speed[2]=findline=0;
				HAL_Delay(50);
			}
			i=0;
			while(high>4)
			{
					HAL_Delay(10);
					i++;
					if(i>4000)
						break; 
			}
				TargetDuoJi[0]=ZhuaZi_KAI;
			HAL_Delay(200);
//						if(high>3.6)
//						{
//							findline=0;
//							adspeed[0]=adspeed[1]=0;
//							speed[0]=speed[1]=speed[3]=speed[2]=0;
//						}
					i=0;
					while(high>0.8f)
					{
						HAL_Delay(10);
						i++;
						if(i>200)
							break; 
					
					}		
					if(way_x[step]!=5 && way_y[step]!=2)
					speed[0]=speed[1]=speed[3]=speed[2]=6;
					HAL_Delay(150);
					TargetDuoJi[0]=ZhuaZi_KAI-13;
					i=0;
					while(TargetDuoJi[0]!=NowDuoJi[0])
					{
						HAL_Delay(10);
						i++;
						if(i>400)
							break; 
					
					}		
					i=0;
					TargetDuoJi[1]=ZhuaZi_SHENG+10;
					findline=1;
					
					HAL_Delay(50);
					while(TargetDuoJi[1]!=NowDuoJi[1])
					{
						HAL_Delay(10);
						i++;
						if(i>400)
							break; 
					
					}
					HAL_Delay(50);					
					BJ_TO_CM(0);
					TargetDuoJi[1]=ZhuaZi_SHENG;
					HAL_Delay(100);
					i=0;
					while(bjdj)
					{
						HAL_Delay(10);
						i++;
						if(i>4000)
							break; 
					}		
				TargetDuoJi[0]=ZhuaZi_HE;
				i=0;
					while(TargetDuoJi[0]!=NowDuoJi[0])
					{
						HAL_Delay(10);
						i++;
						if(i>400)
							break; 
					
					}
					HAL_Delay(200);
					BJ_TO_CM(4);
					i=0;
					while(high<1)
					{
						HAL_Delay(10);
						i++;
						if(i>200)
							break; 
					
					}		
				TargetDuoJi[1]=ZhuaZi_SUO;
				HAL_Delay(100);
				
				while(high<2);
				findline=1;
//					if(SUM_HUAN==3)
//					{
//						BJ_TO_CM(22);
//						TargetDuoJi[1]=ZhuaZi_SHENG; 
//					}
			}
		else
		{
			HUAN_pushed++;
		}
		map[AddressX][AddressY]='+';
}

void arrive_point(void)
{
		daowei=1;
		findline=0;
		speed[0]=speed[1]=speed[3]=speed[2]=0;
		HAL_Delay(100);
		if(map[AddressX-1][AddressY]=='h')
		{
			turn_case=1;
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
		else if(map[AddressX+1][AddressY]=='h')
		{
			turn_case=1;
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
		else if(map[AddressX][AddressY+1]=='h')
		{
			turn_case=1;
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
		else if(map[AddressX][AddressY-1]=='h')
		{
			turn_case=1;
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
		else if(map[AddressX+1][AddressY]=='V')
		{
			BJ_TO_CM(22);
			turn_case=1;
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
		else if(map[AddressX+1][AddressY]=='v')
		{
			BJ_TO_CM(14);
			turn_case=1;
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
		else if(map[AddressX+1][AddressY]=='w')
		{
			BJ_TO_CM(22);
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
		turn_case=0;
		speed[0]=speed[1]=speed[3]=speed[2]=0;
		HAL_Delay(100);
}

void ZengYi(void)
{
	int i;
			speed[0]=speed[1]=speed[3]=speed[2]=0;
			TargetDuoJi[1]=ZhuaZi_SHENG;
			if(SUM_HUAN>0)
			{
				BJ_TO_CM(22);////////////
				TargetDuoJi[0]=ZhuaZi_HE;
				i=0;
				while(high<21)
				{
					HAL_Delay(10);
					i++;
					if(i>5000)
						break; 
				}				
			}
			else
			{
				BJ_TO_CM(13);
				TargetDuoJi[0]=ZhuaZi_KAI;
				i=0;
				while(high<10)
				{
					HAL_Delay(10);
					i++;
					if(i>5000)
						break; 
				}		
			}
					speed[0]=speed[1]=speed[3]=speed[2]=15;
					findline=1;
//					ExpectAngle=Angle[2];
//					findline=1;
						i=0;
						while(!back_is_line)
						{
							HAL_Delay(10);
							i++;
							if(i>4000)
								break; 
						}
					HAL_Delay(800);
					speed[0]=speed[1]=speed[3]=speed[2]=0;
					findline=0;
					BJ_TO_CM(10);
				i=0;
				while(high>14)
				{
					HAL_Delay(10);
					i++;
					if(i>4000)
						break; 
				}		
						TargetDuoJi[0]=ZhuaZi_KAI;
				i=0;
				while(high>12)
				{
					HAL_Delay(10);
					i++;
					if(i>10000)
						break; 
				}		
				if(SUM_HUAN>0)
					TargetDuoJi[0]=ZhuaZi_HE+10;
				
				i=0;
				while(bjdj)
				{
					HAL_Delay(10);
					i++;
					if(i>4000)
						break; 
				}		
				TargetDuoJi[0]=ZhuaZi_HE;
				HAL_Delay(200);
				BJ_TO_CM(22);
				i=0;
				while(bjdj)
				{
					HAL_Delay(10);
					i++;
					if(i>500)
						break; 
				}		
				speed[0]=speed[1]=speed[3]=speed[2]=-15;
				backing=1;
				i=0;
						while(!back_is_line)
						{
							HAL_Delay(10);
							i++;
							if(i>4000)
								break; 
						}

//					speed[0]=speed[1]=speed[3]=speed[2]=orspeed=20;
//					HAL_Delay(100);
					speed[0]=speed[1]=speed[3]=speed[2]=0;
					backing=0;
					HAL_Delay(100);
					SUM_HUAN++;
					map[AddressX+x][AddressY+y]='x';
}

void Three_Score(void)
{
			int i;
				BJ_TO_CM(22);
			TargetDuoJi[1]=ZhuaZi_SHENG;
				i=0;
				while(bjdj)
				{
					HAL_Delay(10);
					i++;
					if(i>5000)
						break; 
				}		
					speed[0]=speed[1]=speed[3]=speed[2]=15;
					findline=1;
					i=0;
						while(!back_is_line)
						{
							HAL_Delay(10);
							i++;
							if(i>4000)
								break; 
						}
						HAL_Delay(700);
					speed[0]=speed[1]=speed[3]=speed[2]=0;
					findline=0;
					HAL_Delay(80);
						
						if(step<9)
						{
							BJ_TO_CM(12);
						}
						else
						{
							BJ_TO_CM(17);
						}
					i=0;
				while(bjdj)
				{
					HAL_Delay(10);
					i++;
					if(i>10000)
						break; 
				}		
					TargetDuoJi[0]=ZhuaZi_KAI;
						if(step<9)
						{
							BJ_TO_CM(13.2);
							SUM_HUAN-=2;
						}
						else if(step<19)
						{
							BJ_TO_CM(15.4);
							SUM_HUAN-=1;
						}
						else
						{
							SUM_HUAN=0;
						}
//				i=0;
//				while(high<14.2)
//				{
//					HAL_Delay(10);
//					i++;
//					if(i>10000)
//						break; 
//				}		
//				TargetDuoJi[0]=ZhuaZi_HE+10;
				i=0;
				while(bjdj)
				{
					HAL_Delay(10);
					i++;
					if(i>5000)
						break; 
				}		
						
				if(SUM_HUAN==0)
				{
					HAL_Delay(300);
				}
				else
				{
					TargetDuoJi[0]=ZhuaZi_HE;
					HAL_Delay(200);
					BJ_TO_CM(22);
				}
				i=0;
				while(bjdj)
				{
					HAL_Delay(10);
					i++;
					if(i>10000)
						break; 
				}		
					TargetDuoJi[1]=ZhuaZi_SUO;
					speed[0]=speed[1]=speed[3]=speed[2]=-15;
				backing=1;
					findline=0;
				i=0;
						while(!back_is_line)
						{
							HAL_Delay(10);
							i++;
							if(i>4000)
								break; 
						}
				BJ_TO_CM(4);

//				speed[0]=speed[1]=speed[3]=speed[2]=orspeed=20;
//				HAL_Delay(100);
				speed[0]=speed[1]=speed[3]=speed[2]=0;
				backing=0;
				HAL_Delay(100);

}

void Two_Score(void)
{
			int i;
				SUM_HUAN=0;
				BJ_TO_CM(14);
			TargetDuoJi[1]=ZhuaZi_SHENG;
				i=0;
				while(bjdj)
				{
					HAL_Delay(10);
					i++;
					if(i>5000)
						break; 
				}		
					speed[0]=speed[1]=speed[3]=speed[2]=15;
					findline=1;
					i=0;
						while(!back_is_line)
						{
							HAL_Delay(10);
							i++;
							if(i>4000)
								break; 
						}
						HAL_Delay(800);
					speed[0]=speed[1]=speed[3]=speed[2]=0;
					findline=0;
					HAL_Delay(80);
				BJ_TO_CM(9);
						
				i=0;
				while(bjdj)
				{
					HAL_Delay(10);
					i++;
					if(i>10000)
						break; 
				}		
//				
//					TargetDuoJi[0]=ZhuaZi_KAI;
//				BJ_TO_CM(14);
//				i=0;
//				while(bjdj)
//				{
//					HAL_Delay(10);
//					i++;
//					if(i>10000)
//						break; 
//				}				
				TargetDuoJi[0]=ZhuaZi_KAI;
				HAL_Delay(200);
				TargetDuoJi[1]=ZhuaZi_SUO;
					speed[0]=speed[1]=speed[3]=speed[2]=-15;
				backing=1;
					findline=0;
				i=0;
						while(!back_is_line)
						{
							HAL_Delay(10);
							i++;
							if(i>4000)
								break; 
						}

				BJ_TO_CM(3.4);
//				speed[0]=speed[1]=speed[3]=speed[2]=orspeed=20;
//				HAL_Delay(100);
				speed[0]=speed[1]=speed[3]=speed[2]=0;
				backing=0;
				HAL_Delay(100);
}


void One_Score(void)
{
			int i;
				HUAN_pushed=0;
				speed[0]=speed[1]=speed[3]=speed[2]=20;
				findline=1;
				i=0;
				while(!is_line)
				{
					HAL_Delay(10);
					i++;
					if(i>300)
						break; 
				}
				findline=0;
				HAL_Delay(550);

				speed[0]=speed[1]=speed[3]=speed[2]=-15;
				backing=1;
						i=0;
						while(!back_is_line)
						{
							HAL_Delay(10);
							i++;
							if(i>190)
								break; 
						}

				speed[0]=speed[1]=speed[3]=speed[2]=0;
				backing=0;
				HAL_Delay(100);
			
}

void Home(void)
{
				int i;
				if(step>sizeof(&way_x[0])/4-2)
				{
					TURN(90);
					TURN(90);
					findline=0;
					backing=1;
					speed[0]=speed[1]=speed[3]=speed[2]=-20;
						i=0;
							while(!is_line)
							{
								HAL_Delay(10);
								i++;
								if(i>4000)
									break; 
							}
							HAL_Delay(300);
							i=0;
				while(!is_line)
				{
					HAL_Delay(10);
					i++;
					if(i>1500)
						break; 
				}

					HAL_Delay(300);
				
				 speed[0]=speed[1]=speed[3]=speed[2]=0;
					backing=0;
					HAL_Delay(10000);
					daowei=0;
					Direction=QIAN;
					for(int j=0;j<7;j++)
					{
						for(i=0;i<9;i++)
							map[j][i]=mapbackup[j][i];
					}
					step=0;
					AddressX=3;
					findline=1;
				speed[0]=speed[1]=speed[3]=speed[2]=orspeed=SPEEDMAX;
					AddressY=0;
					i=0;
					
				while(!back_is_line)
				{
					HAL_Delay(10);
					i++;
					if(i>1400)
						break; 
				}
				i=0; 
						while(is_line)
						{
							HAL_Delay(10);
							i++;
							if(i>12)
							{
								break; 
							}
						}
				}
}

