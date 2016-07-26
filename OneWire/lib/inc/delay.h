//delay.h


#ifndef __delay_h__
#define __delay_h__

#include "stm8l15x.h"

void InitTimer(void);
void clk_config(void);
void __delay_us(uint16_t delay);
void _delay_(uint16_t delay);

#endif