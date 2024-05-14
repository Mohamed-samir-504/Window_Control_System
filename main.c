#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "Drivers/button.h"
#include "Drivers/UART.h"
#include "Drivers/Motor.h"


//======================================================== Handles ======================================================================

SemaphoreHandle_t xJamSemaphore = NULL;
SemaphoreHandle_t xLockSemaphore = NULL;
SemaphoreHandle_t xPassengerWindowMutex = NULL;
xQueueHandle xMotorCommandQueue; 
TaskHandle_t xDriverHandle;

//========================================================= Tasks =======================================================================

void vJamTask(void* pvParameters);
void vLockTask(void* pvParameters);
void vDriverTask(void* pvParameters);
void vPassengerTask(void* pvParameters);
void vMotorAction(void* pvParameters);

//===========================================================================================================================================


int main( void )
{
	INIT_BUTTONS();
	uart_init();
	motor_init();
	
	xMotorCommandQueue = xQueueCreate(2,sizeof(MotorState));

	xJamSemaphore  = xSemaphoreCreateBinary();
	xLockSemaphore = xSemaphoreCreateBinary();
	xPassengerWindowMutex = xSemaphoreCreateMutex();

	xTaskCreate(vDriverTask, "Driver Task", 64, NULL, 1, &xDriverHandle);
	xTaskCreate(vPassengerTask, "Passenger Task", 64, NULL, 1, NULL);
	xTaskCreate(vJamTask, "Jam Task", 64, NULL, 3, NULL);
	xTaskCreate(vLockTask, "Lock Task", 64, NULL, 3, NULL);
	xTaskCreate(vMotorAction, "Motor Task", 64, NULL, 4, NULL);
	vTaskStartScheduler();

	while(1){
		
	}
}



// will be unblocked after jam interrupt
void vJamTask(void* pvParameters){
	for(;;){
	xSemaphoreTake(xJamSemaphore,portMAX_DELAY);
	vPrintString("jam task started");
	vSendMotorCommandToBack(&xMotorCommandQueue,DOWN);
	vTaskDelay(1000/portTICK_RATE_MS); // TODO Fix to be 500ms
	vSendMotorCommandToBack(&xMotorCommandQueue,OFF);

	}
}

// will be unblocked after lock interrupt
void vLockTask(void* pvParameters){

	for(;;){
		xSemaphoreTake(xLockSemaphore,portMAX_DELAY);
		//vTaskDelay(50/portTICK_RATE_MS);
		//if lock button is on
		if(READ_LOCK_SW()){
			vPrintString("lock is on");
			SET_PIN(GPIOF,1); //turn on red led as an indicator
			vTaskPrioritySet(xDriverHandle,2); //so that only the driver can control the window
		}

		//if lock button is off
		else{
			vPrintString("lock is off");
			CLEAR_PIN(GPIOF,1); //turn off red led as an indicator
			vTaskPrioritySet(xDriverHandle,1);
		}
	}

}


// handle driver's controls
void vDriverTask(void* pvParameters){
	
	for(;;){

		
		xSemaphoreTake(xPassengerWindowMutex, portMAX_DELAY);
	
		if(READ_DRIVER_OPEN_BUTTON() && READ_DRIVER_CLOSE_BUTTON()) // both buttons shouldn't be pressed together.
		{
			xSemaphoreGive(xPassengerWindowMutex);
			continue; 
		}
		uint8_t button_open_before  =  READ_DRIVER_OPEN_BUTTON();
		uint8_t button_close_before =  READ_DRIVER_CLOSE_BUTTON();

		//Delay_ms(100);
		vTaskDelay(50/portTICK_RATE_MS); // sample and wait to see if the user is still holding the button

		if(!READ_DRIVER_CLOSE_BUTTON() && button_close_before && !READ_LIMIT_SW1()) // if the driver has pressed the close button without holding.
		{
			vPrintString("driver has pressed the close button");
			vSendMotorCommandToBack(&xMotorCommandQueue,UP);
			vPrintString("waiting for sw1");
			while (!READ_LIMIT_SW1());   // while the limit is not reached, wait.
			vPrintString("off");
			vSendMotorCommandToBack(&xMotorCommandQueue,OFF);
		}

		else if (READ_DRIVER_CLOSE_BUTTON() && button_close_before && !READ_LIMIT_SW1()) // if the driver is holding the close button.
		{
			vPrintString("driver is holding the close button");
			vSendMotorCommandToBack(&xMotorCommandQueue,UP);
			vPrintString("waiting for sw1 or user lift");
			while (READ_DRIVER_CLOSE_BUTTON() && !READ_LIMIT_SW1()); // while the driver is pressing the close button and the limit is not reached.
			vSendMotorCommandToBack(&xMotorCommandQueue,OFF);
			vPrintString("off");
		}

		if(!READ_DRIVER_OPEN_BUTTON() && button_open_before&& !READ_LIMIT_SW2()) // if the driver has pressed the open button without holding.
		{	vPrintString("driver has pressed the open button");
			vSendMotorCommandToBack(&xMotorCommandQueue,DOWN);
			vPrintString("waiting for sw2");
			while (!READ_LIMIT_SW2()); // while the limit is not reached, wait.
			vSendMotorCommandToBack(&xMotorCommandQueue,OFF);
			vPrintString("off");
		}

		else if (READ_DRIVER_OPEN_BUTTON() && button_open_before&& !READ_LIMIT_SW2()) // if the driver is holding the open button.
		{
			vPrintString("driver is holding the open button");
			vSendMotorCommandToBack(&xMotorCommandQueue,DOWN);
			vPrintString("waiting for sw2 or user lift");
			while (READ_DRIVER_OPEN_BUTTON() && !READ_LIMIT_SW2()); // while the driver is pressing the open button and the limit is not reached.
			vSendMotorCommandToBack(&xMotorCommandQueue,OFF);
			vPrintString("off");
		}

		xSemaphoreGive(xPassengerWindowMutex);
		taskYIELD();
		
	}
}

// Handle passenger's control
void vPassengerTask(void* pvParameters){
	
	for(;;){

		xSemaphoreTake(xPassengerWindowMutex, portMAX_DELAY);

		if(READ_PASSENGER_OPEN_BUTTON() && READ_PASSENGER_CLOSE_BUTTON()) // both buttons shouldn't be pressed together.
		{
			xSemaphoreGive(xPassengerWindowMutex);
			continue; 
		}

		uint8_t button_open_before  =  READ_PASSENGER_OPEN_BUTTON();
		uint8_t button_close_before =  READ_PASSENGER_CLOSE_BUTTON();
		vTaskDelay(50/portTICK_RATE_MS);
		//vTaskDelay(50/portTICK_RATE_MS); // sample and wait to see if the user is still holding the button

		if(!READ_PASSENGER_CLOSE_BUTTON() && button_close_before && !READ_LIMIT_SW1()) // if the passenger has pressed the close button without holding.
		{
			vPrintString("pass has pressed the close button");
			vSendMotorCommandToBack(&xMotorCommandQueue,UP);
			while (!READ_LIMIT_SW1());   // while the limit is not reached, wait.
			vSendMotorCommandToBack(&xMotorCommandQueue,OFF);
		}

		else if (READ_PASSENGER_CLOSE_BUTTON() && button_close_before && !READ_LIMIT_SW1()) // if the passenger is holding the close button.
		{
			vPrintString("pass has hold the close button");
			vSendMotorCommandToBack(&xMotorCommandQueue,UP);
			while (READ_PASSENGER_CLOSE_BUTTON() && !READ_LIMIT_SW1()); // while the passenger is pressing the close button and the limit is not reached.
			vSendMotorCommandToBack(&xMotorCommandQueue,OFF);
		}

		if(!READ_PASSENGER_OPEN_BUTTON() && button_open_before&& !READ_LIMIT_SW2()) // if the passenger has pressed the open button without holding.
		{	
			vPrintString("pass has pressed the open button");
			vSendMotorCommandToBack(&xMotorCommandQueue,DOWN);
			while (!READ_LIMIT_SW2()); // while the limit is not reached, wait.
			vSendMotorCommandToBack(&xMotorCommandQueue,OFF);
		}

		else if (READ_PASSENGER_OPEN_BUTTON() && button_open_before&& !READ_LIMIT_SW2()) // if the passenger is holding the open button.
		{
			vPrintString("pass has hold the open button");
			vSendMotorCommandToBack(&xMotorCommandQueue,DOWN);
			while (READ_PASSENGER_OPEN_BUTTON() && !READ_LIMIT_SW2()); // while the passenger is pressing the open button and the limit is not reached.
			vSendMotorCommandToBack(&xMotorCommandQueue,OFF);
		}
		
		xSemaphoreGive(xPassengerWindowMutex);
		taskYIELD();
	}

}

// check for the queue shared between functions and take action.
void vMotorAction(void* pvParameters){
	portBASE_TYPE xStatus;
	MotorState xCurrentMotorState;

	for(;;){

		// if the queue is empty, the task will be blocked until a value is available in the queue.
		xStatus = xQueueReceive(xMotorCommandQueue,&xCurrentMotorState,portMAX_DELAY);

		// if the task is unblocked and the queue contains actions, take the first in the queue.
		if		(xCurrentMotorState == UP   && !READ_LIMIT_SW1())  motor_up();
		else if (xCurrentMotorState == DOWN && !READ_LIMIT_SW2())  motor_down();
		else if (xCurrentMotorState == OFF)  motor_stop();
		
	}
}


//========================================================== Interrupt Handlers ========================================================================

void GPIOE_Handler(){
	vPrintString("interrupt");
	
	// if jam button caused the interrupt
	if (GPIOE->RIS & (1<<4)) xSemaphoreGiveFromISR(xLockSemaphore,NULL);
	else if(GPIOE->RIS & (1<<5)) xSemaphoreGiveFromISR(xJamSemaphore,NULL);

	GPIOE_CLEAR_INTERRUPTS();
}
