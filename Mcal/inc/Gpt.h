#ifndef GPT_H
#define GPT_H

#include "Std_Types.h"

void SysTick_SetCallBack(void (*Ptr2Func)(void));

void SysTick_Start(void);   

void SysTick_Stop(void);    

#endif
