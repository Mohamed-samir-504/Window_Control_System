#include "Motor.h"

int duty_cycle = 4999;


// Spin motor in one direction by giving IN1 and IN2 signals to L298N
void Turn_oneDirection(void)
{
		 SYSCTL->RCGCGPIO |= 0x01;                    /* enable clock to PORTF */
	   GPIOA->DIR |= (1<<3)|(1<<2);                 /* pin digital */
     GPIOA->DEN |= (1<<3)|(1<<2);                 /* pin digital */
     GPIOA->DATA |=(1<<2);
		 GPIOA->DATA &=~(1<<3);
}



// Spin motor in other direction by giving IN1 and IN2 signals to L298N
void Turn_OtherDirection(void)
{
		 SYSCTL->RCGCGPIO |= 0x01;                    /* enable clock to PORTF */
	   GPIOA->DIR |= (1<<3)|(1<<2);                 /* pin digital */
     GPIOA->DEN |= (1<<3)|(1<<2);                 /* pin digital */
     GPIOA->DATA |=(1<<3);
		 GPIOA->DATA &=~(1<<2);
}


void PWM_init(void)
{
   
   /* Clock setting for PWM and GPIO PORT */
	
    SYSCTL->RCGCPWM |= 2;       /* Enable clock to PWM1 module */
    SYSCTL->RCGCGPIO |= 0x20;  /* Enable system clock to PORTF */
	  SYSCTL->RCC |= (1<<20);    /* Enable System Clock Divisor function  */
    SYSCTL->RCC |= 0x000E0000; /* Use pre-divider valur of 64 and after that feed clock to PWM1 module*/

   /* Setting of PF2 pin for M1PWM6 channel output pin */
	
   	GPIOF->AFSEL |= (1<<2);          /* PF2 sets a alternate function */
    GPIOF->PCTL &= ~0x00000F00; /*set PF2 as output pin */
    GPIOF->PCTL |= 0x00000500; /* make PF2 PWM output pin */
    GPIOF->DEN |= (1<<2);          /* set PF2 as a digital pin */
    
    PWM1->_3_CTL &= ~(1<<0);   /* Disable Generator 3 counter */
	  PWM1->_3_CTL &= ~(1<<1);   /* select down count mode of counter 3*/
    PWM1->_3_GENA = 0x0000008C;  /* Set PWM output when counter reloaded and clear when matches PWMCMPA */
    PWM1->_3_LOAD = 5000;     /* set load value for 50Hz 16MHz/64 = 250kHz and (250KHz/5000) */
    PWM1->_3_CMPA = 4999;     /* set duty cyle to to minumum value*/
    PWM1->_3_CTL = 1;           /* Enable Generator 3 counter */
    PWM1->ENABLE = 0x40;      /* Enable PWM1 channel 6 output */
}



void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}