#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "Drivers/UART.h"
#include "Drivers/button.h"
#include "Drivers/Motor.h"

SemaphoreHandle_t xJamSemaphore = NULL;
SemaphoreHandle_t xLockSemaphore = NULL; 

//will be unblocked after jam interrupt
static void vJamHandler(void* pvParameters){
	for(;;){
	vPrintString("JAM BUTTON TASK STARTED");
	xSemaphoreTake(xJamSemaphore,portMAX_DELAY);
	vPrintString("JAM BUTTON PRESSED");
	motor_down();
	vTaskDelay(500/portTICK_RATE_MS); // TODO Fix to be 500ms
	motor_stop();
	}
}

//will be unblocked after lock interrupt
void vLockHandler(void* pvParameters){
	xSemaphoreTake(xLockSemaphore,portMAX_DELAY);

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
	xJamSemaphore  = xSemaphoreCreateBinary();
	xLockSemaphore = xSemaphoreCreateBinary();
	xTaskCreate(vJamHandler, "Jam Handler", 64, NULL, 1, NULL);
	vTaskStartScheduler();

	while(1){
		
	}
}


void GPIOE_Handler(){


	// if jam button caused the interrupt
	if (GPIOE->RIS & 0x4) {
	vPrintString("Semaphore given");
	xSemaphoreGiveFromISR(xJamSemaphore,NULL);
	}
	

	//if lock button caused the interrupt
	else if (GPIOE->RIS & 0x2){
		motor_stop();

	}
	GPIOE_CLEAR_INTERRUPTS();
}