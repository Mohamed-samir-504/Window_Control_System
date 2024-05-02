#include <stdint.h>
#include <stdlib.h>
#include "Drivers/UART.h"

int main(void)
{
	UART_Init();
	
	while(1)
	{
	printstring("looooooooooooooool\n");
	Delay(100);
	}
}

