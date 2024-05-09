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
		
	GPIOx->IS  &= ~(1<<PIN);
	GPIOx->IBE &= ~(1<<PIN);
	GPIOx->IEV |=  (1<<PIN);
	GPIOx->ICR |=  (1<<PIN);
	GPIOx->IM  |=  (1<<PIN);

		
	if (GPIOx == GPIOA) 
	{
		NVIC_EnableIRQ(GPIOA_IRQn);
		NVIC_SetPriority(GPIOA_IRQn,priority);
	}
	
	else if (GPIOx == GPIOB)
	{
		NVIC_EnableIRQ(GPIOB_IRQn);
		NVIC_SetPriority(GPIOB_IRQn,priority);
	}
	else if (GPIOx == GPIOC)
	{
		NVIC_EnableIRQ(GPIOC_IRQn);
		NVIC_SetPriority(GPIOC_IRQn,priority);
	}
	else if (GPIOx == GPIOD)
	{
		NVIC_EnableIRQ(GPIOD_IRQn);
		NVIC_SetPriority(GPIOD_IRQn,priority);
	}
	else if (GPIOx == GPIOE)
	{
		NVIC_EnableIRQ(GPIOE_IRQn);
		NVIC_SetPriority(GPIOE_IRQn,priority);
	

	}
	else if (GPIOx == GPIOF) 
	{
		NVIC_EnableIRQ(GPIOF_IRQn);
		NVIC_SetPriority(GPIOF_IRQn,priority);
	}
	else return;
	

}






