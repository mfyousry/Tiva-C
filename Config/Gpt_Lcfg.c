#include "Gpt.h"
#include "Gpt_Cfg.h"
#include "Dio_Cfg.h"

uint32 Elaps = 0;                // counter to count up every 1 millisecond
uint8 state = 0;                 // initial state of LED is OFF
        
void SysTick_Xfunc(void)         // Function called by SysTick_Handler() every 1 millisecond
{
	Elaps++;
	if((state == 1) & (Elaps == Led_ON_Time))
	{
			SysTick_Stop();
			Dio_FlipChannel(DioConf_LED1_CHANNEL_ID_INDEX);   // Toggle led on PORT F Pin No 1 (Red LED)
			Elaps = 0;
		  state = 0;
		  SysTick_Start();                                   // 1 msec system tick
	}
  else if((state == 0) & (Elaps == Led_OFF_Time))
		{
			SysTick_Stop();
			Dio_FlipChannel(DioConf_LED1_CHANNEL_ID_INDEX);  // Toggle led on PORT F Pin No 1 (Red LED)
			Elaps = 0;
      state = 1;
			SysTick_Start();
	  }
}	