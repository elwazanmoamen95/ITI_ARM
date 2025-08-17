/*
 * RCC_prg.c
 *
 *  Created on: Aug 14, 2025
 *      Author: Mo'men Elwazan
 *      Version: 1.0
 */


#include "RCC_int.h"

/*
 * @Fn				- MRCC_vInit
 * @brief 			- Function used to initialize the RCC
 * @param [in]  	- clk: clock source to be used (HSI, HSE, or PLL)
 * @retval 			- none
 * Note 			- define HPRE_NO_DIV, HPRE_DIV_2, HPRE_DIV_4, HPRE_DIV_8, HPRE_DIV_16, HPRE_DIV_64, HPRE_DIV_128, HPRE_DIV_256, or HPRE_DIV_512 to set the AHB prescaler
 *                  - define PPRE1_NO_DIV, PPRE1_DIV_2, PPRE1_DIV_4, PPRE1_DIV_8, PPRE1_DIV_16 to set the APB1 prescaler
 *                  - define PPRE2_NO_DIV, PPRE2_DIV_2, PPRE2_DIV_4, PPRE2_DIV_8, PPRE2_DIV_16 to set the APB2 prescaler
 *                  - define PLL_SRC_HSI or PLL_SRC_HSE to set the PLL source
 *                  - define PLL_HSE_BYPASS to enable HSE bypassing
 *
 */
void MRCC_vInit(MRCC_ClkSrc clk)
{
    switch (clk)
    {
        case MRCC_CLK_HSI:
            /*
            Enable HSI clock
            RCC clock control register (RCC_CR)
            --------------------------------------------------------
            Bit 1 HSIRDY: Internal high-speed clock ready flag
            Set by hardware to indicate that the HSI oscillator is stable. After the HSION bit is cleared,
            HSIRDY goes low after 6 HSI clock cycles.
            0: HSI oscillator not ready
            1: HSI oscillator ready

            Bit 0 HSION: Internal high-speed clock enable
            Set and cleared by software.
            Set by hardware to force the HSI oscillator ON when leaving the Stop or Standby mode or in
            case of a failure of the HSE oscillator used directly or indirectly as the system clock. This bit
            cannot be cleared if the HSI is used directly or indirectly as the system clock.
            0: HSI oscillator OFF
            1: HSI oscillator ON
            --------------------------------------------------------
            */
            SET_BIT(RCC->CR, 0);                // Set HSION bit
            while(GET_BIT(RCC->CR, 1) == 0);    // Wait until HSI is ready

            /*
            Configure prescaler
            RCC configuration register (RCC_CFGR)
            --------------------------------------------------------
            Bits 7:4 HPRE: AHB prescaler
            Set and cleared by software to control AHB clock division factor.
            Caution: The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after
            HPRE write.
            0xxx: system clock not divided
            1000: system clock divided by 2
            1001: system clock divided by 4
            1010: system clock divided by 8
            1011: system clock divided by 16
            1100: system clock divided by 64
            1101: system clock divided by 128
            1110: system clock divided by 256
            1111: system clock divided by 512

            Bits 15:13 PPRE2: APB high-speed prescaler (APB2)
            Set and cleared by software to control APB high-speed clock division factor.
            Caution: The software has to set these bits correctly not to exceed 84 MHz on this domain.
            The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after
            PPRE2 write.
            0xx: AHB clock not divided
            100: AHB clock divided by 2
            101: AHB clock divided by 4
            110: AHB clock divided by 8
            111: AHB clock divided by 16

            Bits 12:10 PPRE1: APB Low speed prescaler (APB1)
            Set and cleared by software to control APB low-speed clock division factor.
            Caution: The software has to set these bits correctly not to exceed 42 MHz on this domain.
            The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after
            PPRE1 write.
            0xx: AHB clock not divided
            100: AHB clock divided by 2
            101: AHB clock divided by 4
            110: AHB clock divided by 8
            111: AHB clock divided by 16
            --------------------------------------------------------
            */

            #if defined(HPRE_NO_DIV)               // (no division)
                ClR_BIT(RCC->CFGR, 7);          // Clear HPRE bit7
            #elif defined(HPRE_DIV_2)              // (division by 2)
                ClR_BIT(RCC->CFGR, 4);          // Clear HPRE bit4
                ClR_BIT(RCC->CFGR, 5);          // Clear HPRE bit5
                ClR_BIT(RCC->CFGR, 6);          // Clear HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_4)              // (division by 4)
                SET_BIT(RCC->CFGR, 4);          // Set HPRE bit4
                ClR_BIT(RCC->CFGR, 5);          // Clear HPRE bit5
                ClR_BIT(RCC->CFGR, 6);          // Clear HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_8)              // (division by 8)
                ClR_BIT(RCC->CFGR, 4);          // Clear HPRE bit4
                SET_BIT(RCC->CFGR, 5);          // Set HPRE bit5
                ClR_BIT(RCC->CFGR, 6);          // Clear HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_16)             // (division by 16)
                SET_BIT(RCC->CFGR, 4);          // Set HPRE bit4
                SET_BIT(RCC->CFGR, 5);          // Set HPRE bit5
                ClR_BIT(RCC->CFGR, 6);          // Clear HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_64)             // (division by 64)
                ClR_BIT(RCC->CFGR, 4);          // Clear HPRE bit4
                ClR_BIT(RCC->CFGR, 5);          // Clear HPRE bit5
                SET_BIT(RCC->CFGR, 6);          // Set HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_128)            // (division by 128)
                SET_BIT(RCC->CFGR, 4);          // Set HPRE bit4
                ClR_BIT(RCC->CFGR, 5);          // Clear HPRE bit5
                SET_BIT(RCC->CFGR, 6);          // Set HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_256)            // (division by 256)
                ClR_BIT(RCC->CFGR, 4);          // Clear HPRE bit4
                SET_BIT(RCC->CFGR, 5);          // Set HPRE bit5
                SET_BIT(RCC->CFGR, 6);          // Set HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_512)            // (division by 512)
                SET_BIT(RCC->CFGR, 4);          // Set HPRE bit4
                SET_BIT(RCC->CFGR, 5);          // Set HPRE bit5
                SET_BIT(RCC->CFGR, 6);          // Set HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #else                                  // (no division)
                ClR_BIT(RCC->CFGR, 7);          // Clear HPRE bit7
            #endif

            #if defined(PPRE1_NO_DIV)               // (no division)
                ClR_BIT(RCC->CFGR, 12);          // Clear PPRE1 bit15
            #elif defined(PPRE1_DIV_2)              // (division by 2)
                ClR_BIT(RCC->CFGR, 10);          // Clear PPRE1 bit13
                ClR_BIT(RCC->CFGR, 11);          // Clear PPRE1 bit14
                SET_BIT(RCC->CFGR, 12);          // Set PPRE1 bit15
            #elif defined(PPRE1_DIV_4)              // (division by 4)
                SET_BIT(RCC->CFGR, 10);          // Set PPRE1 bit13
                ClR_BIT(RCC->CFGR, 11);          // Clear PPRE1 bit14
                SET_BIT(RCC->CFGR, 12);          // Set PPRE1 bit15
            #elif defined(PRE1_DIV_8)               // (division by 8)
                ClR_BIT(RCC->CFGR, 10);          // Clear PPRE1 bit13
                SET_BIT(RCC->CFGR, 11);          // Set PPRE1 bit14
                SET_BIT(RCC->CFGR, 12);          // Set PPRE1 bit15
            #elif defined(PPRE1_DIV_16)             // (division by 16)
                SET_BIT(RCC->CFGR, 10);          // Set PPRE1 bit13
                SET_BIT(RCC->CFGR, 11);          // Set PPRE1 bit14
                SET_BIT(RCC->CFGR, 12);          // Set PPRE1 bit15
            #else                                   // (no division)
                ClR_BIT(RCC->CFGR, 12);          // Clear PPRE1 bit15
            #endif

            #if defined(PPRE2_NO_DIV)               // (no division)
                ClR_BIT(RCC->CFGR, 15);          // Clear PPRE2 bit15
            #elif defined(PPRE2_DIV_2)              // (division by 2)
                ClR_BIT(RCC->CFGR, 13);          // Clear PPRE2 bit13
                ClR_BIT(RCC->CFGR, 14);          // Clear PPRE2 bit14
                SET_BIT(RCC->CFGR, 15);          // Set PPRE2 bit15
            #elif defined(PPRE2_DIV_4)              // (division by 4)
                SET_BIT(RCC->CFGR, 13);          // Set PPRE2 bit13
                ClR_BIT(RCC->CFGR, 14);          // Clear PPRE2 bit14
                SET_BIT(RCC->CFGR, 15);          // Set PPRE2 bit15
            #elif defined(PPRE2_DIV_8)              // (division by 8)
                ClR_BIT(RCC->CFGR, 13);          // Clear PPRE2 bit13
                SET_BIT(RCC->CFGR, 14);          // Set PPRE2 bit14
                SET_BIT(RCC->CFGR, 15);          // Set PPRE2 bit15
            #elif defined(PPRE2_DIV_16)             // (division by 16)
                SET_BIT(RCC->CFGR, 13);          // Ser PPRE2 bit13
                SET_BIT(RCC->CFGR, 14);          // Set PPRE2 bit14
                SET_BIT(RCC->CFGR, 15);          // Set PPRE2 bit15
            #else                                   // (no division)
                ClR_BIT(RCC->CFGR, 15);          // Clear PPRE2 bit15
            #endif

            /*
            Switch clock
            --------------------------------------------------------
            Bits 3:2 SWS: System clock switch status
            Set and cleared by hardware to indicate which clock source is used as the system clock.
            00: HSI oscillator used as the system clock
            01: HSE oscillator used as the system clock
            10: PLL used as the system clock
            11: not applicable

            Bits 1:0 SW: System clock switch
            Set and cleared by software to select the system clock source.
            Set by hardware to force the HSI selection when leaving the Stop or Standby mode or in
            case of failure of the HSE oscillator used directly or indirectly as the system clock.
            00: HSI oscillator selected as system clock
            01: HSE oscillator selected as system clock
            10: PLL selected as system clock
            11: not allowed
            --------------------------------------------------------
            */
            // Set SW bits to select HSI as system clock
            ClR_BIT(RCC->CFGR, 0)                 // Clear SW bit0
            ClR_BIT(RCC->CFGR, 1);                // Clear SW bit1
            while(((RCC->CFGR >> 2) & 0x3) != 0); // Wait until SWS bits are updated to 00 (HSI selected)
            // while(!((GET_BIT(RCC->CFGR, 2) == 0) && !(GET_BIT(RCC->CFGR, 3) == 0)));  // Wait until SWS bits are updated

            break;

        case MRCC_CLK_HSE:
            /*
            Enable/Disable bypassing HSE clock
            Enable HSE clock
            RCC clock control register (RCC_CR)
            --------------------------------------------------------
            Bit 18 HSEBYP: HSE clock bypass
            Set and cleared by software to bypass the oscillator with an external clock. The external
            clock must be enabled with the HSEON bit, to be used by the device.
            The HSEBYP bit can be written only if the HSE oscillator is disabled.
            0: HSE oscillator not bypassed
            1: HSE oscillator bypassed with an external clock

            Bit 17 HSERDY: HSE clock ready flag
            Set by hardware to indicate that the HSE oscillator is stable. After the HSEON bit is cleared,
            HSERDY goes low after 6 HSE oscillator clock cycles.
            0: HSE oscillator not ready
            1: HSE oscillator ready

            Bit 16 HSEON: HSE clock enable
            Set and cleared by software.
            Cleared by hardware to stop the HSE oscillator when entering Stop or Standby mode. This
            bit cannot be reset if the HSE oscillator is used directly or indirectly as the system clock.
            0: HSE oscillator OFF
            1: HSE oscillator ON
            --------------------------------------------
            */
            ClR_BIT(RCC->CR, 16);                   // Set HSEOFF bit before HSEBYP
            #if defined(HSE_BYPASS)
                SET_BIT(RCC->CR, 18);               // Set HSEBYP bit (bypass enabled)
            #else
                ClR_BIT(RCC->CR, 18);               // Clear HSEBYP bit (not bypassed)
            #endif
            SET_BIT(RCC->CR, 16);                   // Set HSEON bit
            while(GET_BIT(RCC->CR, 17) == 0);       // Wait until HSE is ready

            /*
            Configure prescaler
            RCC configuration register (RCC_CFGR)
            --------------------------------------------------------
            Bits 7:4 HPRE: AHB prescaler
            Set and cleared by software to control AHB clock division factor.
            Caution: The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after
            HPRE write.
            0xxx: system clock not divided
            1000: system clock divided by 2
            1001: system clock divided by 4
            1010: system clock divided by 8
            1011: system clock divided by 16
            1100: system clock divided by 64
            1101: system clock divided by 128
            1110: system clock divided by 256
            1111: system clock divided by 512

            Bits 15:13 PPRE2: APB high-speed prescaler (APB2)
            Set and cleared by software to control APB high-speed clock division factor.
            Caution: The software has to set these bits correctly not to exceed 84 MHz on this domain.
            The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after
            PPRE2 write.
            0xx: AHB clock not divided
            100: AHB clock divided by 2
            101: AHB clock divided by 4
            110: AHB clock divided by 8
            111: AHB clock divided by 16

            Bits 12:10 PPRE1: APB Low speed prescaler (APB1)
            Set and cleared by software to control APB low-speed clock division factor.
            Caution: The software has to set these bits correctly not to exceed 42 MHz on this domain.
            The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after
            PPRE1 write.
            0xx: AHB clock not divided
            100: AHB clock divided by 2
            101: AHB clock divided by 4
            110: AHB clock divided by 8
            111: AHB clock divided by 16
            --------------------------------------------------------
            */

            #if defined(HPRE_NO_DIV)               // (no division)
                ClR_BIT(RCC->CFGR, 7);          // Clear HPRE bit7
            #elif defined(HPRE_DIV_2)              // (division by 2)
                ClR_BIT(RCC->CFGR, 4);          // Clear HPRE bit4
                ClR_BIT(RCC->CFGR, 5);          // Clear HPRE bit5
                ClR_BIT(RCC->CFGR, 6);          // Clear HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_4)              // (division by 4)
                SET_BIT(RCC->CFGR, 4);          // Set HPRE bit4
                ClR_BIT(RCC->CFGR, 5);          // Clear HPRE bit5
                ClR_BIT(RCC->CFGR, 6);          // Clear HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_8)              // (division by 8)
                ClR_BIT(RCC->CFGR, 4);          // Clear HPRE bit4
                SET_BIT(RCC->CFGR, 5);          // Set HPRE bit5
                ClR_BIT(RCC->CFGR, 6);          // Clear HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_16)             // (division by 16)
                SET_BIT(RCC->CFGR, 4);          // Set HPRE bit4
                SET_BIT(RCC->CFGR, 5);          // Set HPRE bit5
                ClR_BIT(RCC->CFGR, 6);          // Clear HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_64)             // (division by 64)
                ClR_BIT(RCC->CFGR, 4);          // Clear HPRE bit4
                ClR_BIT(RCC->CFGR, 5);          // Clear HPRE bit5
                SET_BIT(RCC->CFGR, 6);          // Set HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_128)            // (division by 128)
                SET_BIT(RCC->CFGR, 4);          // Set HPRE bit4
                ClR_BIT(RCC->CFGR, 5);          // Clear HPRE bit5
                SET_BIT(RCC->CFGR, 6);          // Set HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_256)            // (division by 256)
                ClR_BIT(RCC->CFGR, 4);          // Clear HPRE bit4
                SET_BIT(RCC->CFGR, 5);          // Set HPRE bit5
                SET_BIT(RCC->CFGR, 6);          // Set HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_512)            // (division by 512)
                SET_BIT(RCC->CFGR, 4);          // Set HPRE bit4
                SET_BIT(RCC->CFGR, 5);          // Set HPRE bit5
                SET_BIT(RCC->CFGR, 6);          // Set HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #else                                  // (no division)
                ClR_BIT(RCC->CFGR, 7);          // Clear HPRE bit7
            #endif

            #if defined(PPRE1_NO_DIV)               // (no division)
                ClR_BIT(RCC->CFGR, 12);          // Clear PPRE1 bit15
            #elif defined(PPRE1_DIV_2)              // (division by 2)
                ClR_BIT(RCC->CFGR, 10);          // Clear PPRE1 bit13
                ClR_BIT(RCC->CFGR, 11);          // Clear PPRE1 bit14
                SET_BIT(RCC->CFGR, 12);          // Set PPRE1 bit15
            #elif defined(PPRE1_DIV_4)              // (division by 4)
                SET_BIT(RCC->CFGR, 10);          // Set PPRE1 bit13
                ClR_BIT(RCC->CFGR, 11);          // Clear PPRE1 bit14
                SET_BIT(RCC->CFGR, 12);          // Set PPRE1 bit15
            #elif defined(PRE1_DIV_8)               // (division by 8)
                ClR_BIT(RCC->CFGR, 10);          // Clear PPRE1 bit13
                SET_BIT(RCC->CFGR, 11);          // Set PPRE1 bit14
                SET_BIT(RCC->CFGR, 12);          // Set PPRE1 bit15
            #elif defined(PPRE1_DIV_16)             // (division by 16)
                SET_BIT(RCC->CFGR, 10);          // Set PPRE1 bit13
                SET_BIT(RCC->CFGR, 11);          // Set PPRE1 bit14
                SET_BIT(RCC->CFGR, 12);          // Set PPRE1 bit15
            #else                                   // (no division)
                ClR_BIT(RCC->CFGR, 12);          // Clear PPRE1 bit15
            #endif

            #if defined(PPRE2_NO_DIV)               // (no division)
                ClR_BIT(RCC->CFGR, 15);          // Clear PPRE2 bit15
            #elif defined(PPRE2_DIV_2)              // (division by 2)
                ClR_BIT(RCC->CFGR, 13);          // Clear PPRE2 bit13
                ClR_BIT(RCC->CFGR, 14);          // Clear PPRE2 bit14
                SET_BIT(RCC->CFGR, 15);          // Set PPRE2 bit15
            #elif defined(PPRE2_DIV_4)              // (division by 4)
                SET_BIT(RCC->CFGR, 13);          // Set PPRE2 bit13
                ClR_BIT(RCC->CFGR, 14);          // Clear PPRE2 bit14
                SET_BIT(RCC->CFGR, 15);          // Set PPRE2 bit15
            #elif defined(PPRE2_DIV_8)              // (division by 8)
                ClR_BIT(RCC->CFGR, 13);          // Clear PPRE2 bit13
                SET_BIT(RCC->CFGR, 14);          // Set PPRE2 bit14
                SET_BIT(RCC->CFGR, 15);          // Set PPRE2 bit15
            #elif defined(PPRE2_DIV_16)             // (division by 16)
                SET_BIT(RCC->CFGR, 13);          // Ser PPRE2 bit13
                SET_BIT(RCC->CFGR, 14);          // Set PPRE2 bit14
                SET_BIT(RCC->CFGR, 15);          // Set PPRE2 bit15
            #else                                   // (no division)
                ClR_BIT(RCC->CFGR, 15);          // Clear PPRE2 bit15
            #endif

            /*
            Switch clock
            --------------------------------------------------------
            Bits 3:2 SWS: System clock switch status
            Set and cleared by hardware to indicate which clock source is used as the system clock.
            00: HSI oscillator used as the system clock
            01: HSE oscillator used as the system clock
            10: PLL used as the system clock
            11: not applicable

            Bits 1:0 SW: System clock switch
            Set and cleared by software to select the system clock source.
            Set by hardware to force the HSI selection when leaving the Stop or Standby mode or in
            case of failure of the HSE oscillator used directly or indirectly as the system clock.
            00: HSI oscillator selected as system clock
            01: HSE oscillator selected as system clock
            10: PLL selected as system clock
            11: not allowed
            --------------------------------------------------------
            */
            // Set SW bits to select HSE as system clock
            SET_BIT(RCC->CFGR, 0)               // Set SW bit0
            ClR_BIT(RCC->CFGR, 1);              // Clear SW bit1
            while(((RCC->CFGR >> 2) & 0x3) != 1); // Wait until SWS bits are updated to 01 (HSE selected)
            // while(!((GET_BIT(RCC->CFGR, 2) == 1) && (GET_BIT(RCC->CFGR, 3) == 0)));  // Wait until SWS bits are updated
            break;

        case MRCC_CLK_PLL:
            /*
            Enable clock src
            HSE or HSI clock must be enabled before enabling PLL clock src
            HSE bypass or not must be configured before enabling PLL clock src
            Enable PLL clock src
            This bit can be written only when PLL and PLLI2S are disabled.
            RCC PLL configuration register (RCC_PLLCFGR)
            --------------------------------------------------------
            Bit 22 PLLSRC: Main PLL(PLL) and audio PLL (PLLI2S) entry clock source
            Set and cleared by software to select PLL and PLLI2S clock source. This bit can be written
            only when PLL and PLLI2S are disabled.
            0: HSI clock selected as PLL and PLLI2S clock entry
            1: HSE oscillator clock selected as PLL and PLLI2S clock entry
            ---------------------------------------------------------
            */
            ClR_BIT(RCC->CR, 24));                      // Clear PLLON bit (disable PLL)
            while(GET_BIT(RCC->CR, 25) != 0);           // Wait until PLLRDY=0
            #if defined(PLL_SRC_HSE)
                #if defined(PLL_HSE_BYPASS)
                ClR_BIT(RCC->CR, 16);                   // Set HSEOFF bit before HSEBYP
                SET_BIT(RCC->CR, 18);                   // Set HSEBYP bit (bypass enabled)
                #else
                    ClR_BIT(RCC->CR, 18);               // Clear HSEBYP bit (not bypassed)
                #endif
                SET_BIT(RCC->CR, 16);                   // Set HSEON bit
                while(GET_BIT(RCC->CR, 17) == 0);       // Wait until HSE is ready
                SET_BIT(RCC->PLLCFGR, 22);              // Set PLLSRC bit (HSE selected as PLL clock source)
            #else
                SET_BIT(RCC->CR, 0);                    // Set HSION bit
                while(GET_BIT(RCC->CR, 1) == 0);        // Wait until HSI is ready
                ClR_BIT(RCC->PLLCFGR, 22);              // Clear PLLSRC bit (HSI selected as PLL clock source)
            #endif

            /*
            Configure prescaler
            RCC PLL configuration register (RCC_CFGR)
            --------------------------------------------------------
            Bits 7:4 HPRE: AHB prescaler
            Set and cleared by software to control AHB clock division factor.
            Caution: The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after
            HPRE write.
            0xxx: system clock not divided
            1000: system clock divided by 2
            1001: system clock divided by 4
            1010: system clock divided by 8
            1011: system clock divided by 16
            1100: system clock divided by 64
            1101: system clock divided by 128
            1110: system clock divided by 256
            1111: system clock divided by 512

            Bits 15:13 PPRE2: APB high-speed prescaler (APB2)
            Set and cleared by software to control APB high-speed clock division factor.
            Caution: The software has to set these bits correctly not to exceed 84 MHz on this domain.
            The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after
            PPRE2 write.
            0xx: AHB clock not divided
            100: AHB clock divided by 2
            101: AHB clock divided by 4
            110: AHB clock divided by 8
            111: AHB clock divided by 16

            Bits 12:10 PPRE1: APB Low speed prescaler (APB1)
            Set and cleared by software to control APB low-speed clock division factor.
            Caution: The software has to set these bits correctly not to exceed 42 MHz on this domain.
            The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after
            PPRE1 write.
            0xx: AHB clock not divided
            100: AHB clock divided by 2
            101: AHB clock divided by 4
            110: AHB clock divided by 8
            111: AHB clock divided by 16
            --------------------------------------------------------
            */

            #if defined(HPRE_NO_DIV)               // (no division)
                ClR_BIT(RCC->CFGR, 7);          // Clear HPRE bit7
            #elif defined(HPRE_DIV_2)              // (division by 2)
                ClR_BIT(RCC->CFGR, 4);          // Clear HPRE bit4
                ClR_BIT(RCC->CFGR, 5);          // Clear HPRE bit5
                ClR_BIT(RCC->CFGR, 6);          // Clear HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_4)              // (division by 4)
                SET_BIT(RCC->CFGR, 4);          // Set HPRE bit4
                ClR_BIT(RCC->CFGR, 5);          // Clear HPRE bit5
                ClR_BIT(RCC->CFGR, 6);          // Clear HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_8)              // (division by 8)
                ClR_BIT(RCC->CFGR, 4);          // Clear HPRE bit4
                SET_BIT(RCC->CFGR, 5);          // Set HPRE bit5
                ClR_BIT(RCC->CFGR, 6);          // Clear HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_16)             // (division by 16)
                SET_BIT(RCC->CFGR, 4);          // Set HPRE bit4
                SET_BIT(RCC->CFGR, 5);          // Set HPRE bit5
                ClR_BIT(RCC->CFGR, 6);          // Clear HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_64)             // (division by 64)
                ClR_BIT(RCC->CFGR, 4);          // Clear HPRE bit4
                ClR_BIT(RCC->CFGR, 5);          // Clear HPRE bit5
                SET_BIT(RCC->CFGR, 6);          // Set HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_128)            // (division by 128)
                SET_BIT(RCC->CFGR, 4);          // Set HPRE bit4
                ClR_BIT(RCC->CFGR, 5);          // Clear HPRE bit5
                SET_BIT(RCC->CFGR, 6);          // Set HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_256)            // (division by 256)
                ClR_BIT(RCC->CFGR, 4);          // Clear HPRE bit4
                SET_BIT(RCC->CFGR, 5);          // Set HPRE bit5
                SET_BIT(RCC->CFGR, 6);          // Set HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #elif defined(HPRE_DIV_512)            // (division by 512)
                SET_BIT(RCC->CFGR, 4);          // Set HPRE bit4
                SET_BIT(RCC->CFGR, 5);          // Set HPRE bit5
                SET_BIT(RCC->CFGR, 6);          // Set HPRE bit6
                SET_BIT(RCC->CFGR, 7);          // Set HPRE bit7
            #else                                  // (no division)
                ClR_BIT(RCC->CFGR, 7);          // Clear HPRE bit7
            #endif

            #if defined(PPRE1_NO_DIV)               // (no division)
                ClR_BIT(RCC->CFGR, 12);          // Clear PPRE1 bit15
            #elif defined(PPRE1_DIV_2)              // (division by 2)
                ClR_BIT(RCC->CFGR, 10);          // Clear PPRE1 bit13
                ClR_BIT(RCC->CFGR, 11);          // Clear PPRE1 bit14
                SET_BIT(RCC->CFGR, 12);          // Set PPRE1 bit15
            #elif defined(PPRE1_DIV_4)              // (division by 4)
                SET_BIT(RCC->CFGR, 10);          // Set PPRE1 bit13
                ClR_BIT(RCC->CFGR, 11);          // Clear PPRE1 bit14
                SET_BIT(RCC->CFGR, 12);          // Set PPRE1 bit15
            #elif defined(PRE1_DIV_8)               // (division by 8)
                ClR_BIT(RCC->CFGR, 10);          // Clear PPRE1 bit13
                SET_BIT(RCC->CFGR, 11);          // Set PPRE1 bit14
                SET_BIT(RCC->CFGR, 12);          // Set PPRE1 bit15
            #elif defined(PPRE1_DIV_16)             // (division by 16)
                SET_BIT(RCC->CFGR, 10);          // Set PPRE1 bit13
                SET_BIT(RCC->CFGR, 11);          // Set PPRE1 bit14
                SET_BIT(RCC->CFGR, 12);          // Set PPRE1 bit15
            #else                                   // (no division)
                ClR_BIT(RCC->CFGR, 12);          // Clear PPRE1 bit15
            #endif

            #if defined(PPRE2_NO_DIV)               // (no division)
                ClR_BIT(RCC->CFGR, 15);          // Clear PPRE2 bit15
            #elif defined(PPRE2_DIV_2)              // (division by 2)
                ClR_BIT(RCC->CFGR, 13);          // Clear PPRE2 bit13
                ClR_BIT(RCC->CFGR, 14);          // Clear PPRE2 bit14
                SET_BIT(RCC->CFGR, 15);          // Set PPRE2 bit15
            #elif defined(PPRE2_DIV_4)              // (division by 4)
                SET_BIT(RCC->CFGR, 13);          // Set PPRE2 bit13
                ClR_BIT(RCC->CFGR, 14);          // Clear PPRE2 bit14
                SET_BIT(RCC->CFGR, 15);          // Set PPRE2 bit15
            #elif defined(PPRE2_DIV_8)              // (division by 8)
                ClR_BIT(RCC->CFGR, 13);          // Clear PPRE2 bit13
                SET_BIT(RCC->CFGR, 14);          // Set PPRE2 bit14
                SET_BIT(RCC->CFGR, 15);          // Set PPRE2 bit15
            #elif defined(PPRE2_DIV_16)             // (division by 16)
                SET_BIT(RCC->CFGR, 13);          // Ser PPRE2 bit13
                SET_BIT(RCC->CFGR, 14);          // Set PPRE2 bit14
                SET_BIT(RCC->CFGR, 15);          // Set PPRE2 bit15
            #else                                   // (no division)
                ClR_BIT(RCC->CFGR, 15);          // Clear PPRE2 bit15
            #endif

            /*
            Enable PLL clock
            RCC clock control register (RCC_CR)
            --------------------------------------------------------
            Bit 24 PLLRDY: PLL clock ready flag
            Set by hardware to indicate that the PLL is ready. After the PLLON bit is cleared, PLLRDY
            goes low after 6 HSI clock cycles.
            0: PLL not ready
            1: PLL ready
            Bit 25 PLLON: PLL clock enable
            Set and cleared by software.
            Set by hardware to force the HSI selection when leaving the Stop or Standby mode or in
            case of failure of the HSE oscillator used directly or indirectly as the system clock. This
            bit cannot be reset if the PLL is used directly or indirectly as the system clock.
            0: PLL OFF
            1: PLL ON
            --------------------------------------------------------*/
            SET_BIT(RCC->CR, 24);               // Set PLLON bit
            while(GET_BIT(RCC->CR, 25) == 0);   // Wait until PLL is ready

            /*
            Switch clock
            --------------------------------------------------------
            Bits 3:2 SWS: System clock switch status
            Set and cleared by hardware to indicate which clock source is used as the system clock.
            00: HSI oscillator used as the system clock
            01: HSE oscillator used as the system clock
            10: PLL used as the system clock
            11: not applicable

            Bits 1:0 SW: System clock switch
            Set and cleared by software to select the system clock source.
            Set by hardware to force the HSI selection when leaving the Stop or Standby mode or in
            case of failure of the HSE oscillator used directly or indirectly as the system clock.
            00: HSI oscillator selected as system clock
            01: HSE oscillator selected as system clock
            10: PLL selected as system clock
            11: not allowed
            --------------------------------------------------------*/
            // Set SW bits to select PLL as system clock
            SET_BIT(RCC->CFGR, 0)               // Set SW bit0
            SET_BIT(RCC->CFGR, 1);              // Set SW bit1
            while(((RCC->CFGR >> 2) & 0x3) != 2); // Wait until SWS bits are updated to 10 (PLL selected)
            // while(!((GET_BIT(RCC->CFGR, 2) == 0) && (GET_BIT(RCC->CFGR, 3) == 1)));  // Wait until SWS bits are updated
            break;

    }
}

/*
 * @Fn				- MRCC_vEnableCLK
 * @brief 			- Function used to enable the clock for a specific peripheral
 * @param [in]  	- peripheral: peripheral to enable clock for
 * @param [in]  	- bus: bus type (AHB1, APB1, APB2)
 * @retval 			- none
 * Note 			- none
 */
void MRCC_vEnableCLK(MRCC_Bus bus, MRCC_Peripheral peripheral)
{
   switch(bus)
   {
       case MRCC_AHB1: SET_BIT(RCC->AHB1ENR, peripheral); break;
       case MRCC_APB1: SET_BIT(RCC->APB1ENR, peripheral); break;
       case MRCC_APB2: SET_BIT(RCC->APB2ENR, peripheral); break;
   }
}

/*
 * @Fn				- MRCC_vDisableCLK
 * @brief 			- Function used to disable the clock for a specific peripheral
 * @param [in]  	- peripheral: peripheral to disable clock for
 * @param [in]  	- bus: bus type (AHB1, APB1, APB2)
 * @retval 			- none
 * Note 			- none
 */
void MRCC_vDisableCLK(MRCC_Bus bus, MRCC_Peripheral peripheral)
{
   switch(bus)
   {
       case MRCC_AHB1: ClR_BIT(RCC->AHB1ENR, peripheral); break;
       case MRCC_APB1: ClR_BIT(RCC->APB1ENR, peripheral); break;
       case MRCC_APB2: ClR_BIT(RCC->APB2ENR, peripheral); break;
   }
}
}
