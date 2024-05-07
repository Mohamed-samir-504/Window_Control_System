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

//will be unblocked after jam interrupt
void Jam(void* pvParameters){

}

//will be unblocked after lock interrupt
void Lock(void* pvParameters){

}

//will poll on driver buttons
void Driver(void* pvParameters){

}

//will poll on passenger buttons
void Passenger(void* pvParameters){

}

//will check for the queue shared between functions and take action based on value
void MotorAction(void* pvParameters){

}




int main( void )
{
	INIT_MANUAL_OPEN_BUTTON();
	INIT_MANUAL_CLOSE_BUTTON();
	INIT_LOCK_SW();
	INIT_JAM_BUTTON();
	while(1);
}


void GPIOE_Handler(){

	// if jam button caused the interrupt
	if (READ_JAM_BUTTON()){
		//TO DO
		//give jam semaphore to unblock jam task
	}

	//if lock button caused the interrupt
	else if (READ_LOCK_SW()){
		//TO DO
		//give lock semaphore to unblock lock task
	}
}
