#include "Gpt.h"
#include "Mcu_Hw.h"

static void (*g_SysTick_Call_Back_Ptr)(void) = NULL_PTR;  // Global pointer to function used to point upper

void SysTick_Handler(void)
{
	SysTick_Xfunc();
}

void SysTick_Start(void)                 /* 1 millisec SysTick_Start */
{
    SYSTICK_CTRL_REG    = 0;             /* Disable the SysTick Timer by Clear the ENABLE Bit */
    SYSTICK_RELOAD_REG  = 15999;         /* Set the Reload value to count n miliseconds */
    SYSTICK_CURRENT_REG = 0;             /* Clear the Current Register value */

    SYSTICK_CTRL_REG   |= 0x07;          /* Enable the SysTick, Interrupt, choose Clock source */
}

void SysTick_Stop(void)
{
    SYSTICK_CTRL_REG = 0;      /* Disable the SysTick Timer by Clear the ENABLE Bit */
}

void SysTick_SetCallBack(void(*Ptr2Func)(void))
{
    g_SysTick_Call_Back_Ptr = Ptr2Func;
}