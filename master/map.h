#ifndef __MAP_H
#define __MAP_H		
#include "include.h"
//·½Ïò
#define QIAN 1
#define YOU  2
#define HOU  3
#define ZUO  4


void RUN(void);
extern uint16_t SUM_HUAN;
extern uint16_t Direction;
extern  uint16_t AddressX;
extern  uint16_t AddressY;
extern int x,y,daowei,turn_case;
extern uint8_t map[7][9],mapbackup[7][9];
extern uint8_t way_x[],way_y[];
extern int HUAN_pushed;








#endif
