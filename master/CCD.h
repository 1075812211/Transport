#ifndef _CCD_
#define _CCD_
#include "stm32f4xx_hal.h"
#define On_Line ADC_List[64]<1400
#define Middle HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)



void CCD_Init(void);
void CCD_CLK_Handle(void);
extern float CCD_Pos;
extern volatile uint8_t is_line,countline;
extern uint16_t ADC_List[127];

#endif
