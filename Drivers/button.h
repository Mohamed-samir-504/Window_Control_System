#include <stdint.h>
#include <TM4C123GH6PM.h>
void set_up_button(GPIOA_Type* GPIOx, uint8_t PIN, uint8_t PUR_EN);
void set_up_button_interrupt(GPIOA_Type* GPIOx, uint8_t PIN, uint8_t priority);

#define read_input(GPIOx,pin)  (GPIOx->DATA & (1<<pin))

#define READ_PASSENGER_OPEN_BUTTON()   	read_input(GPIOD,0)
#define INIT_PASSENGER_OPEN_BUTTON()   	set_up_button(GPIOD,0,0)

#define READ_PASSENGER_CLOSE_BUTTON()   read_input(GPIOD,1)
#define INIT_PASSENGER_CLOSE_BUTTON()   set_up_button(GPIOD,1,0)

#define READ_DRIVER_OPEN_BUTTON()       read_input(GPIOD,2)
#define INIT_DRIVER_OPEN_BUTTON()       set_up_button(GPIOD,2,0)

#define READ_DRIVER_CLOSE_BUTTON()      read_input(GPIOD,3)
#define INIT_DRIVER_CLOSE_BUTTON()      set_up_button(GPIOD,3,0)

#define READ_LOCK_SW()                  read_input(GPIOE,1)
#define INIT_LOCK_SW()   								set_up_button(GPIOE,1,0);\
																				set_up_button_interrupt(GPIOE,1,3)

#define READ_JAM_BUTTON()               read_input(GPIOE,2)
#define INIT_JAM_BUTTON()   						set_up_button(GPIOE,2,0);\
																				set_up_button_interrupt(GPIOE,2,3)

#define INIT_BUTTONS() 									INIT_PASSENGER_OPEN_BUTTON();\
																				INIT_PASSENGER_CLOSE_BUTTON();\
																				INIT_DRIVER_OPEN_BUTTON();\
																				INIT_DRIVER_CLOSE_BUTTON();\
																				INIT_LOCK_SW();\
																				INIT_JAM_BUTTON();


#define GPIOA_CLEAR_INTERRUPTS()      GPIOA->ICR |= GPIOA->RIS;
#define GPIOB_CLEAR_INTERRUPTS()      GPIOB->ICR |= GPIOB->RIS;
#define GPIOC_CLEAR_INTERRUPTS()      GPIOC->ICR |= GPIOC->RIS;
#define GPIOD_CLEAR_INTERRUPTS()      GPIOD->ICR |= GPIOD->RIS;
#define GPIOE_CLEAR_INTERRUPTS()      GPIOE->ICR |= GPIOE->RIS;
#define GPIOF_CLEAR_INTERRUPTS()      GPIOF->ICR |= GPIOF->RIS;

