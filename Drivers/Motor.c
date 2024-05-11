#include "Motor.h"
#include "button.h"

/*
@brief Send a command for the motor to go up.
@note motor_init() must be called in main before using this API.
*/
void motor_up(void)
{
	SET_PIN(MOTOR_PORT,MOTOR_UP_PIN);
	CLEAR_PIN(MOTOR_PORT,MOTOR_DOWN_PIN);

    //MOTOR_PORT->DATA   |=  (1<<MOTOR_UP_PIN);
	//MOTOR_PORT->DATA &= ~(1<<MOTOR_DOWN_PIN);
}


/*
@brief Send a command for the motor to go down.
@note motor_init() must be called in main before using this API.
*/
void motor_down(void)
{
	CLEAR_PIN(MOTOR_PORT,MOTOR_UP_PIN);
	SET_PIN(MOTOR_PORT,MOTOR_DOWN_PIN);
	
    //MOTOR_PORT->DATA |=  (1<<MOTOR_DOWN_PIN);
	//MOTOR_PORT->DATA   &= ~(1<<MOTOR_UP_PIN);
}

/*
@brief Send a command for the motor to stop.
@note motor_init() must be called in main before using this API.
*/

void motor_stop(void)
{	
	CLEAR_PIN(MOTOR_PORT,MOTOR_UP_PIN);
	CLEAR_PIN(MOTOR_PORT,MOTOR_DOWN_PIN);

    //MOTOR_PORT->DATA   &=~ (1<<MOTOR_UP_PIN);
	//MOTOR_PORT->DATA &=~ (1<<MOTOR_DOWN_PIN);
}
/*
@brief Initialize the motor.
@note This API must be called in main before using any of the other Motor APIs.
*/
void motor_init(void)
{

	if(MOTOR_UP_PIN > 7 || MOTOR_DOWN_PIN > 7) return;
	
	set_up_output_pin(MOTOR_PORT,MOTOR_UP_PIN);
	set_up_output_pin(MOTOR_PORT,MOTOR_DOWN_PIN);
	
}
/*
@brief Send a command to the end of the motor queue.
@param xMotorQueue pointer to the handld of the motor of the queue.
@param command the command to be sent.
*/
void vSendMotorCommandToBack(xQueueHandle* xMotorQueue, MotorState command)
{
	MotorState xMotorCommand = command;
	xQueueSendToBack(*xMotorQueue,&xMotorCommand,portMAX_DELAY);
}

/*
@brief Send a command to the front of the motor queue to be executed next.
@param xMotorQueue pointer to the handld of the motor of the queue.
@param command the command to be sent.
@note  This function must be used only in emergency cases (ie. when a jam occurs). 
	   To send a normal command to the motor queue please use vSendMotorCommandToBack().
*/
void vSendMotorCommandToFront(xQueueHandle* xMotorQueue, MotorState command)
{
	MotorState xMotorCommand = command;
	xQueueSendToFront(*xMotorQueue,&xMotorCommand,portMAX_DELAY);
}
