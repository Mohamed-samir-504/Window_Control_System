#include <stdint.h>
#include <TM4C123GH6PM.h>
void set_up_input_pin(GPIOA_Type* GPIOx, uint8_t PIN, uint8_t PUR_EN);
void set_up_output_pin(GPIOA_Type* GPIOx, uint8_t PIN);
void set_up_button_interrupt(GPIOA_Type* GPIOx, uint8_t PIN, uint8_t priority, uint8_t both_edges);

#define READ_PIN(GPIOx,pin)     (GPIOx->DATA & (1<<pin))
#define SET_PIN(GPIOx,pin)      (GPIOx->DATA |= (1<<pin))
#define CLEAR_PIN(GPIOx,pin)    (GPIOx->DATA &= ~(1<<pin))

#define READ_PASSENGER_OPEN_BUTTON()   	READ_PIN(GPIOC,4)
#define INIT_PASSENGER_OPEN_BUTTON()   	set_up_input_pin(GPIOC,4,0)

#define READ_PASSENGER_CLOSE_BUTTON()   READ_PIN(GPIOC,5)
#define INIT_PASSENGER_CLOSE_BUTTON()   set_up_input_pin(GPIOC,5,0)

#define READ_DRIVER_OPEN_BUTTON()       READ_PIN(GPIOC,6)
#define INIT_DRIVER_OPEN_BUTTON()       set_up_input_pin(GPIOC,6,0)

#define READ_DRIVER_CLOSE_BUTTON()      READ_PIN(GPIOC,7)
#define INIT_DRIVER_CLOSE_BUTTON()      set_up_input_pin(GPIOC,7,0)

#define READ_LIMIT_SW1()      			READ_PIN(GPIOA,6)
#define INIT_LIMIT_SW1()       			set_up_input_pin(GPIOA,6,0)

#define READ_LIMIT_SW2()      			READ_PIN(GPIOA,7)
#define INIT_LIMIT_SW2()        		set_up_input_pin(GPIOA,7,0)


#define READ_LOCK_SW()               READ_PIN(GPIOE,4)

#define INIT_LOCK_SW()   				set_up_input_pin(GPIOE,4,0);\
												set_up_button_interrupt(GPIOE,4,7,1)

										

#define READ_JAM_BUTTON()               READ_PIN(GPIOE,5)

#define INIT_JAM_BUTTON()   			set_up_input_pin(GPIOE,5,0);\
												set_up_button_interrupt(GPIOE,5,7,0)

#define INIT_BUTTONS() 					INIT_PASSENGER_OPEN_BUTTON();\
												INIT_PASSENGER_CLOSE_BUTTON();\
												INIT_DRIVER_OPEN_BUTTON();\
												INIT_DRIVER_CLOSE_BUTTON();\
												INIT_LIMIT_SW1();\
												INIT_LIMIT_SW2();\
												INIT_LOCK_SW();\
												INIT_JAM_BUTTON()


#define GPIOA_CLEAR_INTERRUPTS()      GPIOA->ICR |= GPIOA->RIS;
#define GPIOA_CLEAR_INTERRUPTS()      GPIOA->ICR |= GPIOA->RIS;
#define GPIOC_CLEAR_INTERRUPTS()      GPIOC->ICR |= GPIOC->RIS;
#define GPIOD_CLEAR_INTERRUPTS()      GPIOD->ICR |= GPIOD->RIS;
#define GPIOE_CLEAR_INTERRUPTS()      GPIOE->ICR |= GPIOE->RIS;
#define GPIOF_CLEAR_INTERRUPTS()      GPIOF->ICR |= GPIOF->RIS;
