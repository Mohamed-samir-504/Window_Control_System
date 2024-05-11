#include <stdint.h>
#include <TM4C123GH6PM.h>
void set_up_input_pin(GPIOA_Type* GPIOx, uint8_t PIN, uint8_t PUR_EN);
void set_up_output_pin(GPIOA_Type* GPIOx, uint8_t PIN);
void set_up_button_interrupt(GPIOA_Type* GPIOx, uint8_t PIN, uint8_t priority);

#define READ_PIN(GPIOx,pin)     (GPIOx->DATA & (1<<pin))
#define SET_PIN(GPIOx,pin)      (GPIOx->DATA |= (1<<pin))
#define CLEAR_PIN(GPIOx,pin)    (GPIOx->DATA &= ~(1<<pin))

#define READ_PASSENGER_OPEN_BUTTON()   	READ_PIN(GPIOD,0)
#define INIT_PASSENGER_OPEN_BUTTON()   	set_up_input_pin(GPIOD,0,0)

#define READ_PASSENGER_CLOSE_BUTTON()   READ_PIN(GPIOD,1)
#define INIT_PASSENGER_CLOSE_BUTTON()   set_up_input_pin(GPIOD,1,0)

#define READ_DRIVER_OPEN_BUTTON()       READ_PIN(GPIOD,2)
#define INIT_DRIVER_OPEN_BUTTON()       set_up_input_pin(GPIOD,2,0)

#define READ_DRIVER_CLOSE_BUTTON()      READ_PIN(GPIOD,3)
#define INIT_DRIVER_CLOSE_BUTTON()      set_up_input_pin(GPIOD,3,0)

#define READ_LIMIT_SW1()      			READ_PIN(GPIOB,0)
#define INIT_LIMIT_SW1()       			set_up_input_pin(GPIOB,0,0)

#define READ_LIMIT_SW2()      			READ_PIN(GPIOB,1)
#define INIT_LIMIT_SW2()        		set_up_input_pin(GPIOB,1,0)


#define READ_LOCK_SW()                  READ_PIN(GPIOE,1)

#define INIT_LOCK_SW()   				set_up_input_pin(GPIOE,1,0);\
												set_up_button_interrupt(GPIOE,1,7)

#define INIT_LOCK_LED()                 set_up_output_pin(GPIOF,1)

#define READ_JAM_BUTTON()               READ_PIN(GPIOE,2)

#define INIT_JAM_BUTTON()   			set_up_input_pin(GPIOE,2,0);\
												set_up_button_interrupt(GPIOE,2,7)

#define INIT_BUTTONS() 					INIT_PASSENGER_OPEN_BUTTON();\
												INIT_PASSENGER_CLOSE_BUTTON();\
												INIT_DRIVER_OPEN_BUTTON();\
												INIT_DRIVER_CLOSE_BUTTON();\
												INIT_LIMIT_SW1();\
												INIT_LIMIT_SW2();\
												INIT_LOCK_SW();\
												INIT_LOCK_LED();\
												INIT_JAM_BUTTON()


#define GPIOA_CLEAR_INTERRUPTS()      GPIOA->ICR |= GPIOA->RIS;
#define GPIOB_CLEAR_INTERRUPTS()      GPIOB->ICR |= GPIOB->RIS;
#define GPIOC_CLEAR_INTERRUPTS()      GPIOC->ICR |= GPIOC->RIS;
#define GPIOD_CLEAR_INTERRUPTS()      GPIOD->ICR |= GPIOD->RIS;
#define GPIOE_CLEAR_INTERRUPTS()      GPIOE->ICR |= GPIOE->RIS;
#define GPIOF_CLEAR_INTERRUPTS()      GPIOF->ICR |= GPIOF->RIS;

