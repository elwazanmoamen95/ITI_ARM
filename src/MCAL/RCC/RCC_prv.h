/*
 * RCC_prv.h
 *
 *  Created on: Aug 14, 2025
 *      Author: Mo'men Elwazan
 *      Version: 1.0
 */

#ifndef MCAL_RCC_RCC_PRV_H_
#define MCAL_RCC_RCC_PRV_H_

#define RCC_BASE_ADDR		0x40023800U

typedef struct
{
	u32 CR;
	u32 PLLCFGR;
	u32 CFGR;
	u32 CIR;
	u32 AHB1RSTR;
	u32 AHB2RSTR;
	u32 Reserved1;
	u32 Reserved2;
	u32 APB1RSTR;
	u32 APB2RSTR;
	u32 Reserved3;
	u32 Reserved4;
	u32 AHB1ENR;
	u32 AHB2ENR;
	u32 Reserved5;
	u32 Reserved6;
	u32 APB1ENR;
	u32 APB2ENR;
	u32 Reserved7;
	u32 Reserved8;
	u32 AHB1LPENR;
	u32 AHB2LPENR;
	u32 Reserved9;
	u32 Reserved10;
	u32 APB1LPENR;
	u32 APB2LPENR;
	u32 Reserved11;
	u32 Reserved12;
	u32 BDCR;
	u32 CSR;
	u32 Reserved13;
	u32 Reserved14;
	u32 SSCGR;
	u32 PLLI2SCFGR;
	u32 Reserved15;
	u32 DCKCFGR;

}RCC_MemMap;

typedef enum
{
    MRCC_CLK_HSI,
    MRCC_CLK_HSE,
    MRCC_CLK_PLL
} MRCC_ClkSrc;

typedef enum
{
	MRCC_AHB1,
	MRCC_APB1,
	MRCC_APB2
} MRCC_Bus;

typedef enum
{
    /* RCC AHB1 peripheral */
    MRCC_GPIOA = 0,
    MRCC_GPIOB = 1,
    MRCC_GPIOC = 2,
    MRCC_GPIOD = 3,
    MRCC_GPIOE = 4,
    MRCC_GPIOH = 7,
    MRCC_CRC   = 12,
    MRCC_DMA1  = 21,
    MRCC_DMA2  = 22,

    /* RCC APB1 peripheral */
    MRCC_TIM2  = 0,
    MRCC_TIM3  = 1,
    MRCC_TIM4  = 2,
    MRCC_TIM5  = 3,
    MRCC_WWDG  = 11,
    MRCC_SPI2  = 14,
    MRCC_USART2= 17,
    MRCC_I2C1  = 21,
    MRCC_I2C2  = 22,
    MRCC_I2C3  = 23,
    MRCC_PWR   = 28,

    /* RCC APB2 peripheral */
    MRCC_TIM1  = 0,
    MRCC_USART1= 4,
    MRCC_USART6= 5,
    MRCC_ADC1  = 8,
    MRCC_SDIO  = 11,
    MRCC_SPI1  = 12,
    MRCC_SPI4  = 13,
    MRCC_SYSCFG= 14,
    MRCC_TIM9  = 16,
    MRCC_TIM10 = 17,
    MRCC_TIM11 = 18

} MRCC_Peripheral;

#define RCC					((volatile RCC_MemMap*)(RCC_BASE_ADDR))

/*--------------------- ITI LAB-------------------*/
#if 0
#define HSE_CLk 0
#define HSI_CLK 1
#define PLL_CLK 2

#define RC_CLK 0
#define MECHANICAL_CLK 1 

/* Perepherals AHB1*/
#define MRCC_GPIOA 	0
#define MRCC_GPIOB 	1  
#define MRCC_GPIOC 	2
#define MRCC_GPIOD 	3
#define MRCC_GPIOE 	4
#define MRCC_GPIOH 	7
#define MRCC_CRC   	12
#define MRCC_DMA1  	21
#define MRCC_DMA2  	22

/* Perepherals APB1*/
#define MRCC_TIM2  	0
#define MRCC_TIM3  	1
#define MRCC_TIM4  	2
#define MRCC_TIM5  	3
#define MRCC_WWDG  	11
#define MRCC_SPI2  	14
#define MRCC_USART2 17
#define MRCC_I2C1  	21
#define MRCC_I2C2  	22
#define MRCC_I2C3  	23
#define MRCC_PWR   	28

/* Perepherals APB2*/
#define MRCC_TIM1  	0
#define MRCC_USART1 4
#define MRCC_USART6 5
#define MRCC_ADC1  	8
#define MRCC_SDIO  	11   
#define MRCC_SPI1  	12
#define MRCC_SPI4  	13
#define MRCC_SYSCFG 14
#define MRCC_TIM9  	16
#define MRCC_TIM10 	17
#define MRCC_TIM11 	18

/*----------------------------------------*/
#endif /* MCAL_RCC_RCC_PRV_H_ */

#endif
