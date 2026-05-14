#ifndef HAL_7SEG_INT_H_
#define HAL_7SEG_INT_H_

#include"../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_int.h"

/*
  //Table for common cathode

Digit	A	B	C	D	E	F	G
0		1	1	1	1	1	1	0
1		0	1	1	0	0	0	0
2		1	1	0	1	1	0	1
3		1	1	1	1	0	0	1
4		0	1	1	0	0	1	1
5		1	0	1	1	0	1	1
6		1	0	1	1	1	1	1
7		1	1	1	0	0	0	0
8		1	1	1	1	1	1	1
9		1	1	1	1	0	1	1
 */

// Segment encoding (Common Cathode by default)
static const u8 G_u8SSD_CC_Num[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

typedef enum {
    SSD_CC,
    SSD_CA
} SSD_Type;

typedef struct {
    GPIOx_MemMap_t* Port;               // GPIOx 
    u8 Pin;                // GPIOx Pin
} SSD_PinConfig_t;

typedef struct {
    SSD_Type Type;
    SSD_PinConfig_t Segments[7];

} SSD_Config_t;

void HSSD_vInit(SSD_Config_t* ssd);
void HSSD_vDisplay(SSD_Config_t* ssd, u8 A_u8Number);
void HSSD_vClear(SSD_Config_t* ssd);
void HSSD_vCountUp(SSD_Config_t* ssd, u8 A_u8Number);
void HSSD_vCountdown(SSD_Config_t* ssd, u8 A_u8Number);


#endif /* HAL_7SEG_INT_H_ */