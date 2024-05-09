#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "Drivers/UART.h"
#include "Drivers/button.h"
#include "Drivers/Motor.h"

SemaphoreHandle_t xJamSemaphore = NULL;
SemaphoreHandle_t xLockSemaphore = NULL;
xQueueHandle xQueue; 

//Shared between tasks to control motor state
MotorState xCurrentMotorState;

//will be unblocked after jam interrupt
static void vJamTask(void* pvParameters){
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
void vLockTask(void* pvParameters){
	xSemaphoreTake(xLockSemaphore,portMAX_DELAY);

	//TO DO
	//Raise driver task priority if lock is on

	//Return driver task priority to normal if lock is off

}

//will poll on driver buttons
void vDriverTask(void* pvParameters){

}

//will poll on passenger buttons
void vPassengerTask(void* pvParameters){

}

//will check for the queue shared between functions and take action based on value
void vMotorAction(void* pvParameters){

	portBASE_TYPE xStatus;
	for(;;){
		//if the queue is empty, task will be blocked until a value is available in the queue
		xStatus = xQueueReceive(xQueue,&xCurrentMotorState,portMAX_DELAY);

		//if we reach here then the task is unblocked and the queue value is saved in xCurrentMotorState
		if(xCurrentMotorState == UP) motor_up();
		else if (xCurrentMotorState == DOWN) motor_down();
		else if (xCurrentMotorState == OFF) motor_stop();
	}
}




int main( void )
{

	INIT_BUTTONS();
	uart_init();
	motor_init();
	
	xQueue = xQueueCreate(3,sizeof(MotorState));

	xJamSemaphore  = xSemaphoreCreateBinary();
	xLockSemaphore = xSemaphoreCreateBinary();

	xTaskCreate(vJamTask, "Jam Task", 64, NULL, 1, NULL);
	
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
		xSemaphoreGiveFromISR(xLockSemaphore,NULL);

	}

	GPIOE_CLEAR_INTERRUPTS();
}