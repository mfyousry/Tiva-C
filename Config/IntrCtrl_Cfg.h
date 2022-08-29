#ifndef INTRCTRL_CFG_H
#define INTRCTRL_CFG_H

#define GROUP_PRIORITY_NUMBER_BITS          (2u)
#define SUBGROUP_PRIORITY_NUMBER_BITS       (1u)

#define NUMBER_EXCEPTIONS                  (155u)

#if ( (GROUP_PRIORITY_NUMBER_BITS == 3) && (SUBGROUP_PRIORITY_NUMBER_BITS==0) )
    #define PRIORITY_CONFIGURATION     (0u << 8u)
    #define GROUP_PRIORITY_MASK           (0b111)
    #define SUBGROUP_PRIORITY_MASK        (0b000)

#elif ( (GROUP_PRIORITY_NUMBER_BITS == 2) && (SUBGROUP_PRIORITY_NUMBER_BITS==1) )
    #define PRIORITY_CONFIGURATION     (5u << 8u)
    #define GROUP_PRIORITY_MASK           (0b110)
    #define SUBGROUP_PRIORITY_MASK        (0b001)
	
#elif ( (GROUP_PRIORITY_NUMBER_BITS == 1) && (SUBGROUP_PRIORITY_NUMBER_BITS==2) )
    #define PRIORITY_CONFIGURATION     (6u << 8u)
    #define GROUP_PRIORITY_MASK           (0b100)
    #define SUBGROUP_PRIORITY_MASK        (0b011)

#elif ( (GROUP_PRIORITY_NUMBER_BITS == 0) && (SUBGROUP_PRIORITY_NUMBER_BITS==3) )
    #define PRIORITY_CONFIGURATION      (7u << 8u)
    #define GROUP_PRIORITY_MASK           (0b000)
    #define SUBGROUP_PRIORITY_MASK        (0b111)

#else
    #error Wrong PRIORITY CONFIGURATIONS
#endif





#endif
