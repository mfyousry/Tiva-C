#ifndef PORT_H
#define PORT_H

#include "Std_Types.h"
#include "Port_Types.h"
#include "Macros.h"

typedef uint8 Port_PinType;

typedef uint8 Port_PinModeType;          
   
typedef enum             /* Enum to hold PIN direction */
{
    PORT_PIN_IN,PORT_PIN_OUT
}Port_PinDirection;

typedef enum             /* Enum to hold internal resistor type for PIN */
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;


typedef struct 
{
    uint8 port_num;                     // the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
    uint8 pin_num;                      // the number of the pin in the PORT.
    Port_PinDirection direction;        // the direction INPUT or OUTPUT
    Port_InternalResistor resistor;     // internal resistor OFF, Pull up or Pull down
    uint8 pin_mode;
}Port_ConfigPins;

typedef struct
{
	Port_ConfigPins Pins[PORT_NUMBER_OF_PORT_PINS ];      //43 Structure 
}Port_ConfigType;


void Port_Init(const Port_ConfigType *ConfigPtr );

extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */
