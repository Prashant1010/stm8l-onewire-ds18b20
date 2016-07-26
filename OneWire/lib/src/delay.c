//delay.c


#include "stm8l15x.h"


void clk_config(void)
{
  CLK_DeInit();
  CLK_HSICmd(ENABLE);
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
}

void InitTimer(void)
{
  clk_config();
  TIM2_DeInit();
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
  TIM2_TimeBaseInit(TIM2_Prescaler_1, TIM2_CounterMode_Up, 500);
  TIM2_Cmd(ENABLE);
}

void  _delay_(uint16_t delay)
{
    uint16_t i;
    for(i=0; i<delay; i++);
}

void __delay_us(uint16_t delay)
{
    delay = delay * 16;
    uint16_t count = 0;
    
    TIM2_ARRPreloadConfig(DISABLE);
    TIM2_SetAutoreload(delay);
    TIM2_SetCounter(0);
    TIM2_Cmd(ENABLE);
    while(TIM2_GetFlagStatus(TIM2_FLAG_Update) == RESET);
    TIM2_ClearFlag(TIM2_FLAG_Update);
    TIM2_Cmd(DISABLE); 
}