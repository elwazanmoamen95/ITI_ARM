/*
 * RCC_cfg.h
 *
 *  Created on: Aug 14, 2025
 *      Author: Mo'men Elwazan
 *      Version: 1.0
 */

#ifndef MCAL_RCC_RCC_CFG_H_
#define MCAL_RCC_RCC_CFG_H_

/*
    options
    -- HSE
    -- HSI
    -- PLL
*/
#define RCC_SYS_CLK HSE_CLK

/*
    options
    -- RC_CLK
    -- MECHANICAL_CLK
*/
#define HSE_BYP RC_CLK

/* Busses*/
#define MRCC_AHB1 0
#define MRCC_APB1 1 
#define MRCC_APB2 2



#endif /* MCAL_RCC_RCC_CFG_H_ */
