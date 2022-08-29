#include "Dio.h"
#include "Port.h"
#include "Gpt.h"
#include "IntrCtrl.h"

int main(void)
{
	Port_Init(&Port_Configuration);
	Dio_Init(&Dio_Configuration);
	IntrCtrl_voidInit();
	SysTick_Start();                // Start systick timer for first time.
	
	while(1)
	{
 
	}
	return 1;
}
