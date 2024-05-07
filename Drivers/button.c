#include "button.h"



/*
	set up a GPIO pin to be used as an input button.
	
	@parameters
	GPIOx : must be a value from GPIOA -> GPIOF.
	PIN : must be from 0 to 7 or withdraw ASAP.
	PUR_EN : this is set to 0 then only pull down resistor is enabled, if this is set to 1 then only pull up resistor is enabled.
	
	@note
	There are some GPIO pins that has special considerations (need CR and unlocking w bta3 fa fakes) at page 671 in DATA SHEET (PA[5:0], PB[3:2], PC[3:0],PD[7], PF[0]).
	
*/

void set_up_button(GPIOA_Type* GPIOx, uint8_t PIN, uint8_t PUR_EN)
{
	if(PIN>7) return;
	
	if     (GPIOx == GPIOA) SYSCTL->RCGCGPIO |= 0x01; // Enable clock for PORTA
	else if(GPIOx == GPIOB) SYSCTL->RCGCGPIO |= 0x02; // Enable clock for PORTB
	else if(GPIOx == GPIOC) SYSCTL->RCGCGPIO |= 0x04; // Enable clock for PORTC
	else if(GPIOx == GPIOD) SYSCTL->RCGCGPIO |= 0x08; // Enable clock for PORTD
	else if(GPIOx == GPIOE) SYSCTL->RCGCGPIO |= 0x10; // Enable clock for PORTE
	else if(GPIOx == GPIOF) SYSCTL->RCGCGPIO |= 0x20; // Enable clock for PORTF
	else return;
	
	
	if(PUR_EN){
	 GPIOx->PDR &= ~(1<<PIN); 					// Disable Pull down resistor for PIN.
   GPIOx->PUR |=  (1<<PIN);           // Enable Pull Up resistor for PIN.
	}
	else
	{
	 GPIOx->PUR &= ~(1<<PIN); 					// Disable Pull up resistor for PIN.
   GPIOx->PDR |=  (1<<PIN);           // Enable Pull down resistor for PIN.
	}
	
   GPIOx->DIR &= ~(1<<PIN);           // set PIN as an input (button). 
   GPIOx->DEN |=  (1<<PIN);           // digital enable GPIO pin.
}



void set_up_button_interrupt(GPIOA_Type* GPIOx, uint8_t PIN, uint8_t priority)
{
	if(priority>7 || PIN>7) return;
		
	if (GPIOx == GPIOA) 
	{
		NVIC->IP[0] = priority << 5;
		NVIC->ISER[0] |= 1<< GPIOA_IRQn;
	}
	
	else if (GPIOx == GPIOB)
	{
		NVIC->IP[0] = priority << 13;
		NVIC->ISER[0] |= 1<< GPIOB_IRQn;
	}
	else if (GPIOx == GPIOC)
	{
		NVIC->IP[0] = priority << 21;
		NVIC->ISER[0] |= 1<< GPIOC_IRQn;
	}
	else if (GPIOx == GPIOD)
	{
		NVIC->IP[0] = priority << 29;
		NVIC->ISER[0] |= 1<< GPIOD_IRQn;
	}
	else if (GPIOx == GPIOE)
	{
		NVIC->IP[1] = priority << 5;
		NVIC->ISER[0] |= 1<< GPIOE_IRQn;
	}
	else if (GPIOx == GPIOF) 
	{
		NVIC->IP[7] = priority << 21;
		NVIC->ISER[0] |= 1<< GPIOF_IRQn;
	}
	else return;
	
	
	GPIOx->IS  &= ~(1<<PIN);
	GPIOx->IBE &= ~(1<<PIN);
	GPIOx->IEV |=  (1<<PIN);
	GPIOx->ICR |=  (1<<PIN);
	GPIOx->IM  |=  (1<<PIN);

}






