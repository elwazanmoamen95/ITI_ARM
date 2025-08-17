/*
 * BIT_MATH.h
 *
 *  Created on: Aug 14, 2025
 *      Author: Mo'men Elwazan
 *      Version: 1.0
 */

#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

#define ClR_BIT(reg, bitN) (reg &= ~(1<<bitN))
#define SET_sBIT(reg, bitN) (reg |= (1<<bitN))
#define TOG_BIT(reg, bitN) (reg ^= (1<<bitN))
#define GET_BIT(reg, bitN) (((reg >> bitN) & 1)

#endif /* LIB_BIT_MATH_H_ */
