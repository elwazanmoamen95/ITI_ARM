/*
 * RCC_int.h
 *
 *  Created on: Aug 14, 2025
 *      Author: Mo'men Elwazan
 *      Version: 1.0
 */

#ifndef MCAL_RCC_RCC_INT_H_
#define MCAL_RCC_RCC_INT_H_

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_prv.h"
#include "RCC_cfg.h"


void MRCC_vInit(MRCC_ClkSrc clk);
void MRCC_vEnableCLK(MRCC_Bus bus, MRCC_Peripheral peripheral);
void MRCC_vDisableCLK(MRCC_Bus bus, MRCC_Peripheral peripheral);


#endif /* MCAL_RCC_RCC_INT_H_ */
