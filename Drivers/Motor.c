#include "Motor.h"
#include "button.h"

void motor_up(void)
{
	SET_PIN(MOTOR_PORT,MOTOR_UP_PIN);
	CLEAR_PIN(MOTOR_PORT,MOTOR_DOWN_PIN);

    //MOTOR_PORT->DATA   |=  (1<<MOTOR_UP_PIN);
	//MOTOR_PORT->DATA &= ~(1<<MOTOR_DOWN_PIN);
}


void motor_down(void)
{
	CLEAR_PIN(MOTOR_PORT,MOTOR_UP_PIN);
	SET_PIN(MOTOR_PORT,MOTOR_DOWN_PIN);
	
    //MOTOR_PORT->DATA |=  (1<<MOTOR_DOWN_PIN);
	//MOTOR_PORT->DATA   &= ~(1<<MOTOR_UP_PIN);
}


void motor_stop(void)
{	
	CLEAR_PIN(MOTOR_PORT,MOTOR_UP_PIN);
	CLEAR_PIN(MOTOR_PORT,MOTOR_DOWN_PIN);

    //MOTOR_PORT->DATA   &=~ (1<<MOTOR_UP_PIN);
	//MOTOR_PORT->DATA &=~ (1<<MOTOR_DOWN_PIN);
}

void motor_init(void)
{

	if(MOTOR_UP_PIN > 7 || MOTOR_DOWN_PIN > 7) return;
	
	set_up_output_pin(MOTOR_PORT,MOTOR_UP_PIN);
	set_up_output_pin(MOTOR_PORT,MOTOR_DOWN_PIN);
	
}

void vSendMotorCommandToBack(xQueueHandle* xMotorQueue, MotorState command)
{
	MotorState xMotorCommand = command;
	xQueueSendToBack(*xMotorQueue,&xMotorCommand,portMAX_DELAY);
}

void vSendMotorCommandToFront(xQueueHandle* xMotorQueue, MotorState command)
{
	MotorState xMotorCommand = command;
	xQueueSendToFront(*xMotorQueue,&xMotorCommand,portMAX_DELAY);
}
