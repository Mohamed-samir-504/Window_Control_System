#include "Motor.h"
#include "button.h"


void motor_up(void)
{
	SET_PIN(MOTOR_PORT,MOTOR_UP_PIN);
	CLEAR_PIN(MOTOR_PORT,MOTOR_DOWN_PIN);
	GPIOF->DATA |= (1<<2);
	GPIOF->DATA &= ~(1<<3);
}


/*
@brief Send a command for the motor to go down.
@note motor_init() must be called in main before using this API.
*/
void motor_down(void)
{
	CLEAR_PIN(MOTOR_PORT,MOTOR_UP_PIN);
	SET_PIN(MOTOR_PORT,MOTOR_DOWN_PIN);
	GPIOF->DATA |= (1<<3);
	GPIOF->DATA &= ~(1<<2);
	
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

	GPIOF->DATA &= ~(1<<2);
	GPIOF->DATA &= ~(1<<3);
}

void motor_init(void)
{
	SYSCTL->RCGCGPIO |= 0x20;

	if     (MOTOR_PORT == GPIOA) SYSCTL->RCGCGPIO |= 0x01; // Enable clock for PORTA
	else if( MOTOR_PORT == GPIOB) SYSCTL->RCGCGPIO |= 0x02; // Enable clock for PORTB
	else if( MOTOR_PORT == GPIOC) SYSCTL->RCGCGPIO |= 0x04; // Enable clock for PORTC
	else if( MOTOR_PORT == GPIOD) SYSCTL->RCGCGPIO |= 0x08; // Enable clock for PORTD
	else if( MOTOR_PORT == GPIOE) SYSCTL->RCGCGPIO |= 0x10; // Enable clock for PORTE
	else if(MOTOR_PORT == GPIOF) SYSCTL->RCGCGPIO |= 0x20; // Enable clock for PORTF
	else return;
	
	if(MOTOR_UP_PIN > 7 || MOTOR_DOWN_PIN>7) return;
	
	MOTOR_PORT->DIR   |= (1<<MOTOR_UP_PIN);
	MOTOR_PORT->DIR |= (1<<MOTOR_DOWN_PIN);
	
  	MOTOR_PORT->DEN   |= (1<<MOTOR_UP_PIN);
	MOTOR_PORT->DEN |=	(1<<MOTOR_DOWN_PIN);

	GPIOF->DIR |= ((1<<1)|(1<<2)|(1<<3));
	GPIOF->DEN |= ((1<<1)|(1<<2)|(1<<3));

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
