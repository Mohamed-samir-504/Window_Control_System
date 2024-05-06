#include "FreeRTOS.h"
#include "task.h"
#include "Drivers/UART.h"
#include "Drivers/button.h"
#include <TM4C123GH6PM.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"



int main( void )
{
	INIT_MANUAL_OPEN_BUTTON();
	INIT_MANUAL_CLOSE_BUTTON();
	INIT_LOCK_SW();
	INIT_JAM_BUTTON();
	while(1);
}
