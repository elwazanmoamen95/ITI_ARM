#ifndef MCAL_GPIO_PRV_H
#define MCAL_GPIO_PRV_H 

#include "Std_Types.h"
#include "MGPIO_prv.h"

void MGPIO_vSetMode(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8Mode);
void MGPIO_vSetOutputType(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8OutputType);
void MGPIO_vOutputSpeed(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8SOutputSpeed);
void MGPIO_vSetPushPull(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8PushPull);
void MGPIO_vSetPinValue(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8Value);
u8 MGPIO_u8GetPinValue(u8 A_u8PortID, u8 A_u8PinNum);
void MGPIO_vSetAlternateFunction(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8AlternateFunction);


#endif /* MCAL_GPIO_PRV_H */
