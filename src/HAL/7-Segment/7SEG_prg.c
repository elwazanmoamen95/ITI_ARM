#include "7SEG_int.h"

void wait(uint32_t time){
	for(uint32_t i=0 ; i<time ; i++){
		for(uint32_t j=0 ; j<255 ; j++);
	}
}

void HSSEG_vInit(SSD_Config_t* ssd)
{
    // Initialize each segment pin based on the configuration
    for (int i = 0; i < 7; i++) {
    GPIOx_PinConfig_t pinConfig;

    pinConfig.Port      = ssd->Segments[i].Port;   // Port
    pinConfig.Pin       = ssd->Segments[i].Pin;    // Pin
    pinConfig.Mode      = GPIO_MODE_OUTPUT_PP;     // Output, push-pull

    if (ssd->Type == SSD_CC) {
        pinConfig.PullType = GPIO_PULL_DOWN;       // Common Cathode → Pull-Down
    } else {
        pinConfig.PullType = GPIO_PULL_UP;         // Common Anode → Pull-Up
    }

    // Enable clock for this GPIO port
    MRCC_vEnableClk(RCC_AHB1, ssd->Segments[i].Port);

    // Initialize GPIO
    MGPIO_vPinInit(&pinConfig);
}
}

void HSSD_vDisplay(SSD_Config_t* ssd, u8 A_u8Number)
{
    if (A_u8Number > 9) return;
    
    uint8_t pattern = G_u8SSD_CC_Num[A_u8Number];
    
    for (int i = 0; i < 7; i++) {
        uint8_t bit = (pattern >> (6-i)) & 0x1;
        
        if (ssd->type == SSD_CC) {
            if (bit)
                MGPIO_vSetPinValue(ssd->Segments[i].Port, ssd->Segments[i].Pin, GPIO_HIGH);     // ON
            else
                MGPIO_vSetPinValue(ssd->Segments[i].Port, ssd->Segments[i].Pin, GPIO_LOW);      // OFF
        } else { // Common Anode
            if (bit)
                MGPIO_vSetPinValue(ssd->Segments[i].Port, ssd->Segments[i].Pin, GPIO_LOW);      // ON
            else
                MGPIO_vSetPinValue(ssd->Segments[i].Port, ssd->Segments[i].Pin, GPIO_HIGH);     // OFF
        }
    }
}

void HSSD_vClear(SSD_Config_t* ssd)
{
    for (int i = 0; i < 7; i++) {
        if (ssd->type == SSD_CC)
            MGPIO_vSetPinValue(ssd->Segments[i].Port, ssd->Segments[i].Pin, GPIO_LOW);  // OFF
        else
            MGPIO_vSetPinValue(ssd->Segments[i].Port, ssd->Segments[i].Pin, GPIO_HIGH); // OFF
    }
}

void HSSD_vCountUp(SSD_Config_t* ssd, u8 A_u8Number)
{
    for (uint8_t counter = A_u8Number; counter <= 9; counter++) {
        HSSD_vDisplay(ssd, counter);
        wait(1000);
    }
}

void HSSD_vCountdown(SSD_Config_t* ssd, u8 A_u8Number)
{
    for (int8_t counter = A_u8Number; counter >= 0; counter--) {
        HSSD_vDisplay(ssd, counter);
        wait(1000);
    }
}

