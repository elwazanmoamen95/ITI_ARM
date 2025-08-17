#ifndef MCAL_GPIO_PRV_H
#define MCAL_GPIO_PRV_H

#include "Std_Types.h"

#define GPIOA_BASE_ADDRESS 0x40020000U
#define GPIOB_BASE_ADDRESS 0x40020400U
#define GPIOC_BASE_ADDRESS 0x40020800U
#define GPIOD_BASE_ADDRESS 0x40020C00U
#define GPIOE_BASE_ADDRESS 0x40021000U
#define GPIOH_BASE_ADDRESS 0x40021C00U

typedef struct 
{
    u32 MODER;
    u32 OTYPER;
    u32 OSPEEDR;
    u32 PUPDR;
    u32 IDR; 
    u32 ODR;     
    u32 BSRR;    
    u32 LCKR;    
    u32 AFRL;    
    u32 AFRH;    

}GPIO_MemMap;



#define GPIOA ((volatile GPIO_MemMap *)GPIOA_BASE_ADDRESS)
#define GPIOB ((volatile GPIO_MemMap *)GPIOB_BASE_ADDRESS)
#define GPIOC ((volatile GPIO_MemMap *)GPIOC_BASE_ADDRESS)

#define PUSHPULL 0U
#define OPENDRAIN 1U

#define GPIO_HIGH 1U
#define GPIO_LOW 0U

#endif /* MCAL_GPIO_PRV_H */
