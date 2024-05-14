#include "TM4C123GH6PM.h"

#ifndef __UART_H_
#define __UART_H_
void vPrintString(char *str);
void vPrintStringAndNumber(char *str, uint32_t num);
void uart_init();
#endif