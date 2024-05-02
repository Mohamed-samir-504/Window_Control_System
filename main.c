#include <stdint.h>
#include <stdlib.h>
#include "Drivers/UART.h"

int main(void)
{
	UART_Init();
	
	//3.6 was here
	while(1)
	{
	printstring("lol\n");
	Delay(100);
	}

}

