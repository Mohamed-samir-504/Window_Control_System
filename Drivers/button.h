#include <stdint.h>
#include <TM4C123GH6PM.h>
#include "project_config.h"

#ifndef __BUTTON_H_
#define __BUTTON_H_

void set_up_input_pin(GPIOA_Type* GPIOx, uint8_t PIN, uint8_t PUR_EN);
void set_up_output_pin(GPIOA_Type* GPIOx, uint8_t PIN);
void set_up_button_interrupt(GPIOA_Type* GPIOx, uint8_t PIN, uint8_t priority, uint8_t both_edges);

#define READ_PIN(GPIOx,pin)     (GPIOx->DATA & (1<<pin))
#define SET_PIN(GPIOx,pin)      (GPIOx->DATA |= (1<<pin))
#define CLEAR_PIN(GPIOx,pin)    (GPIOx->DATA &= ~(1<<pin))

#define GPIOA_CLEAR_INTERRUPTS()      GPIOA->ICR |= GPIOA->RIS;
#define GPIOA_CLEAR_INTERRUPTS()      GPIOA->ICR |= GPIOA->RIS;
#define GPIOC_CLEAR_INTERRUPTS()      GPIOC->ICR |= GPIOC->RIS;
#define GPIOD_CLEAR_INTERRUPTS()      GPIOD->ICR |= GPIOD->RIS;
#define GPIOE_CLEAR_INTERRUPTS()      GPIOE->ICR |= GPIOE->RIS;
#define GPIOF_CLEAR_INTERRUPTS()      GPIOF->ICR |= GPIOF->RIS;

#define READ_PASSENGER_OPEN_BUTTON()   	READ_PIN(PASSENGER_PORT,PASSENGER_OPEN_PIN)
#define INIT_PASSENGER_OPEN_BUTTON()   	set_up_input_pin(PASSENGER_PORT,PASSENGER_OPEN_PIN,PULLDOWN_RESISTOR_EN)

#define READ_PASSENGER_CLOSE_BUTTON()   READ_PIN(PASSENGER_PORT,PASSENGER_CLOSE_PIN)
#define INIT_PASSENGER_CLOSE_BUTTON()   set_up_input_pin(PASSENGER_PORT,PASSENGER_CLOSE_PIN,PULLDOWN_RESISTOR_EN)

#define READ_DRIVER_OPEN_BUTTON()       READ_PIN(DRIVER_PORT,DRIVER_OPEN_PIN)
#define INIT_DRIVER_OPEN_BUTTON()       set_up_input_pin(DRIVER_PORT,DRIVER_OPEN_PIN,PULLDOWN_RESISTOR_EN)

#define READ_DRIVER_CLOSE_BUTTON()      READ_PIN(DRIVER_PORT,DRIVER_CLOSE_PIN)
#define INIT_DRIVER_CLOSE_BUTTON()      set_up_input_pin(DRIVER_PORT,DRIVER_CLOSE_PIN,PULLDOWN_RESISTOR_EN)

#define READ_LIMIT_SW1()      			READ_PIN(LIMIT_SWITCH_PORT,LIMIT_SWITCH1_PIN)
#define INIT_LIMIT_SW1()       			set_up_input_pin(LIMIT_SWITCH_PORT,LIMIT_SWITCH1_PIN,PULLDOWN_RESISTOR_EN)

#define READ_LIMIT_SW2()      			READ_PIN(LIMIT_SWITCH_PORT,LIMIT_SWITCH2_PIN)
#define INIT_LIMIT_SW2()        		set_up_input_pin(LIMIT_SWITCH_PORT,LIMIT_SWITCH2_PIN,PULLDOWN_RESISTOR_EN)


#define READ_LOCK_SW()               	READ_PIN(JAM_LOCK_PORT,LOCK_BUTTON_PIN)

#define INIT_LOCK_SW()   				set_up_input_pin(JAM_LOCK_PORT,LOCK_BUTTON_PIN,PULLDOWN_RESISTOR_EN);\
																set_up_button_interrupt(JAM_LOCK_PORT,LOCK_BUTTON_PIN,7,1)

									
#define READ_JAM_BUTTON()               READ_PIN(JAM_LOCK_PORT,JAM_BUTTON_PIN)

#define INIT_JAM_BUTTON()   			set_up_input_pin(JAM_LOCK_PORT,JAM_BUTTON_PIN,PULLDOWN_RESISTOR_EN);\
															set_up_button_interrupt(JAM_LOCK_PORT,JAM_BUTTON_PIN,7,0)



#define INIT_BUTTONS() 							INIT_PASSENGER_OPEN_BUTTON();\
												INIT_PASSENGER_CLOSE_BUTTON();\
												INIT_DRIVER_OPEN_BUTTON();\
												INIT_DRIVER_CLOSE_BUTTON();\
												INIT_LIMIT_SW1();\
												INIT_LIMIT_SW2();\
												INIT_LOCK_SW();\
												INIT_JAM_BUTTON()




#endif