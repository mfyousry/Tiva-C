#ifndef DIO_H
#define DIO_H

#include "Std_Types.h"
#include "Dio_Cfg.h"
#include "Macros.h"

typedef uint8 Dio_ChannelType;

typedef uint8 Dio_PortType;

typedef uint8 Dio_LevelType;

typedef uint8 Dio_PortLevelType;

typedef struct
{ 
  uint8 mask;              /* Mask which defines the positions of the channel group */
  uint8 offset;            /* Position of the group from LSB */
  Dio_PortType PortIndex;  /* This shall be the port ID which the Channel group is defined. */
} Dio_ChannelGroupType;

typedef struct
{
	Dio_PortType Port_Num;      /* Member contains the ID of the Port that this channel belongs to */
	Dio_ChannelType Ch_Num;     /* Member contains the ID of the Channel*/
}Dio_ConfigChannel;


typedef struct Dio_ConfigType    /* Data Structure required for initializing the Dio Driver */
{
	Dio_ConfigChannel Channels[DIO_CONFIGURED_CHANNLES];
} Dio_ConfigType;

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

void Dio_Init(const Dio_ConfigType * ConfigPtr);

extern const Dio_ConfigType Dio_Configuration;

#endif /* DIO_H */
