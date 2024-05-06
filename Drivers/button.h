#include <stdint.h>
#include <TM4C123GH6PM.h>
void set_up_button(GPIOA_Type* GPIOx, uint8_t PIN, uint8_t PUR_EN);


#define read_input(GPIOx,pin)  (GPIOx->DATA & (1<<pin))

#define READ_MANUAL_OPEN_BUTTON()  read_input(GPIOD,0)
#define INIT_MANUAL_OPEN_BUTTON()  set_up_button(GPIOD,0,0)

#define READ_MANUAL_CLOSE_BUTTON() read_input(GPIOD,1)
#define INIT_MANUAL_CLOSE_BUTTON() set_up_button(GPIOD,1,0)

#define READ_LOCK_SW()             read_input(GPIOD,2)
#define INIT_LOCK_SW()   				   set_up_button(GPIOD,2,0)

#define READ_JAM_BUTTON()          read_input(GPIOD,3)
#define INIT_JAM_BUTTON()   			 set_up_button(GPIOD,3,0)


