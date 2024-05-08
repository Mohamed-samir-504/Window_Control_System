#include "Motor.h"


void motor_up(void)
{
     MOTOR_UP_PORT->DATA   |=  (1<<MOTOR_UP_PIN);
		 MOTOR_DOWN_PORT->DATA &= ~(1<<MOTOR_DOWN_PIN);
}


void motor_down(void)
{
     MOTOR_DOWN_PORT->DATA |=  (1<<MOTOR_DOWN_PIN);
		 MOTOR_UP_PORT->DATA   &= ~(1<<MOTOR_UP_PIN);
}


void motor_stop(void)
{	
     MOTOR_UP_PORT->DATA   &=~ (1<<MOTOR_UP_PIN);
		 MOTOR_DOWN_PORT->DATA &=~ (1<<MOTOR_DOWN_PIN);
}

void motor_init(void)
{
	if     (MOTOR_UP_PORT == GPIOA || MOTOR_DOWN_PORT == GPIOA) SYSCTL->RCGCGPIO |= 0x01; // Enable clock for PORTA
	else if(MOTOR_UP_PORT == GPIOB || MOTOR_DOWN_PORT == GPIOB) SYSCTL->RCGCGPIO |= 0x02; // Enable clock for PORTB
	else if(MOTOR_UP_PORT == GPIOC || MOTOR_DOWN_PORT == GPIOC) SYSCTL->RCGCGPIO |= 0x04; // Enable clock for PORTC
	else if(MOTOR_UP_PORT == GPIOD || MOTOR_DOWN_PORT == GPIOD) SYSCTL->RCGCGPIO |= 0x08; // Enable clock for PORTD
	else if(MOTOR_UP_PORT == GPIOE || MOTOR_DOWN_PORT == GPIOE) SYSCTL->RCGCGPIO |= 0x10; // Enable clock for PORTE
	else if(MOTOR_UP_PORT == GPIOF || MOTOR_DOWN_PORT == GPIOF) SYSCTL->RCGCGPIO |= 0x20; // Enable clock for PORTF
	else return;
	
	if(MOTOR_UP_PIN > 7 || MOTOR_DOWN_PIN>7) return;
	
	MOTOR_UP_PORT->DIR   |= (1<MOTOR_UP_PIN);
	MOTOR_DOWN_PORT->DIR |= (1<<MOTOR_DOWN_PIN);
	
  MOTOR_UP_PORT->DEN   |= (1<<MOTOR_UP_PIN);
	MOTOR_DOWN_PORT->DEN |=	(1<<MOTOR_DOWN_PIN); 
	
}