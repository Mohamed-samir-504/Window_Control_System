#include "TM4C123GH6PM.h"

char UART0_Receiver(void)  
{
    char data;
	  while((UART0->FR & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = UART0->DR ;  	/* before giving it another byte */
    return (unsigned char) data; 
}

void UART0_Transmitter(unsigned char data)
{
    while((UART0->FR & (1<<5)) != 0);  /* wait until Tx buffer not full */
    UART0->DR = data;                  /* before giving it another byte */
}

void vPrintString(char *str)
{
  while(*str) UART0_Transmitter(*(str++));
	
	UART0_Transmitter('\n');
}


char* dec(uint32_t x, char *s)
{
    *--s = 0;
    if (!x) *--s = '0';
    for (; x; x/=10) *--s = '0' + x%10;
    return s;
}


void vPrintStringAndNumber(char *str, uint32_t num)
{
	char temp[10];
	while(*str) UART0_Transmitter(*(str++));
	
	char* res = dec(num,&temp[9]);
	
	while(*res) UART0_Transmitter(*(res++));
	
	UART0_Transmitter('\n');
}




void uart_init()
{
	  SYSCTL->RCGCUART |= 0x1;  /* enable clock to UART0 */
    SYSCTL->RCGCGPIO |= 0x1;  /* enable clock to PORTA */
		__ASM("nop");
    GPIOA->DEN = 0x3;     
    GPIOA->AFSEL = 0x3;    /* Use  alternate function */
    GPIOA->AMSEL = 0;    /* Turn off analg function*/
    GPIOA->PCTL = (1<<0) | (1<<4);     /* configure UART */
	
    /* UART0 initialization */
    UART0->CTL &= ~(1<<0);         /* UART0 module disbable */
    UART0->IBRD = 104;      /* for 9600 baud rate, integer = 104 */
    UART0->FBRD = 11;       /* for 9600 baud rate, fractional = 11*/
    UART0->CC = 0;          /*select system clock*/
    UART0->LCRH = (0x3<<5);     /* data lenght 8-bit, not parity bit, no FIFO */
    UART0->CTL = (1<<0) | (1<<8) | (1<<9);     /* Enable UART5 module, Rx and Tx */
		__ASM("nop");
}