#ifndef __FINDLINE_H
#define __FINDLINE_H		
#include "include.h"

struct pidad{
	float aderr,lastaderr1,lastaderr2,adspeed;
};
extern int adspeed[4],lastline;
extern float lin[4];
extern struct pidad adpid;





void Find_Line(void);











#endif

