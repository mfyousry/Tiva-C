#include "Port.h"
#include "Port_Cfg.h"
#include "Mcu_Hw.h"

static const Port_ConfigPins * PortConf = NULL_PTR;

void Port_Init(const Port_ConfigType * ConfigPtr )
{
	volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
	volatile uint32 delay = 0;
    
	PortConf = ConfigPtr->Pins;     /*points to the 1st address of the array of structure*/

	uint8 Pin_Index;                /* index to configure each pin (43)*/
    
    
	for (Pin_Index = 0; Pin_Index < PORT_NUMBER_OF_PORT_PINS ; Pin_Index++) 
		{
			switch(PortConf[Pin_Index].port_num)
				{
					case  0: 
						PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
						break; 
					case  1: 
						PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
						break;
					case  2:
						continue;  /* Avoid PORTC for JTAG pins */
						PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
						break;
					case  3: 
						PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
						break;
					case  4: 
						PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
						break;
					case  5: 
						PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
						break;
				}
    
		/* Enable clock for PORT and allow time for clock to start*/
		SYSCTL_REGCGC2_REG |= (1<<PortConf[Pin_Index].port_num);
		delay = SYSCTL_REGCGC2_REG;
    
		if( ((PortConf[Pin_Index].port_num== 3) && (PortConf[Pin_Index].port_num== 7)) || ((PortConf[Pin_Index].port_num == 5) && (PortConf[Pin_Index].port_num == 0)) ) /* PD7 or PF0 */
		{
			*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , PortConf[Pin_Index].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
		}
		else if( (PortConf[Pin_Index].port_num == 2) && (PortConf[Pin_Index].pin_num <= 3) ) /* PC0 to PC3 */
		{
			/* Nothing JTAG pins */
		}
		else
		{
			/* Do Nothing ... No need to unlock the commit register for this pin */
		}
    /* Direction,initial_value,resistor */
    
		if(PortConf[Pin_Index].direction == PORT_PIN_OUT)
		{
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortConf[Pin_Index].pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
		}
		else if(PortConf[Pin_Index].direction == PORT_PIN_IN)
		{
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PortConf[Pin_Index].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        
			if(PortConf[Pin_Index].resistor == PULL_UP)
			{
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , PortConf[Pin_Index].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
			}
			else if(PortConf[Pin_Index].resistor == PULL_DOWN)
			{
				SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PortConf[Pin_Index].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
			}
			else
			{
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , PortConf[Pin_Index].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
				CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PortConf[Pin_Index].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
			}
		}
		else
		{
			/* Do Nothing */
		}
    
		/* Check Mode */
		if(PortConf[Pin_Index].pin_mode==PORT_PIN_MODE_DIO)
		{
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PortConf[Pin_Index].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
			CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PortConf[Pin_Index].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
			*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PortConf[Pin_Index].pin_num * 4));     /* Clear the PMCx bits for this pin */   
			SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PortConf[Pin_Index].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
		}
	}
} 

