#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "Drivers/UART.h"
#include "Drivers/button.h"
#include "Drivers/Motor.h"

//will be unblocked after jam interrupt
void vJamHandler(void* pvParameters){

}

//will be unblocked after lock interrupt
void vLockHandler(void* pvParameters){

}

//will poll on driver buttons
void vDriverHandler(void* pvParameters){

}

//will poll on passenger buttons
void vPassengerHandler(void* pvParameters){

}

//will check for the queue shared between functions and take action based on value
void vMotorAction(void* pvParameters){

}




int main( void )
{
	INIT_BUTTONS();
	uart_init();
	motor_init();
	

/* pin digital */
		
	while(1){
		
	}
}


void GPIOE_Handler(){
	volatile int x = 3;
	// if jam button caused the interrupt
	if (GPIOE->RIS & 0x4){
		//TO DO
		//give jam semaphore to unblock jam task
	//	Turn_oneDirection();
		motor_up();
		x =4;
	}

	//if lock button caused the interrupt
	else if (GPIOE->RIS & 0x2){
		//TO DO
		//give lock semaphore to unblock lock task
	//	stop_motor();
		motor_stop();
		x=4;
	}
	GPIOE_CLEAR_INTERRUPTS();
}