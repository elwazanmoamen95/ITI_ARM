#include "RCC_int.h"
#include "MGPIO_int.h"

int main(void)
{

	MRCC_vInit(); // Initialize RCC with HSI clock
	MRCC_vEnableCLK(MRCC_AHB1, MRCC_GPIOA); // Enable clock for GPIOA

	MGPIO_vSetMode(GPIOA);
	MGPIO_vSetOutputType();
	MGPIO_vOutputSpeed();
	MGPIO_vSetPushPull();
	MGPIO_vSetPinValue();

	while(1)
	{

	}

	return 0;
}
