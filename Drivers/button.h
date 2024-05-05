#include <stdint.h>
#include <TM4C123GH6PM.h>
void set_up_button(GPIOA_Type* GPIOx, uint8_t PIN, uint8_t PUR_EN);
#define read_input(GPIOx,pin) (GPIOx->DATA & (1<<pin))