#include "TM4C123GH6PM.h"
void motor_up(void);
void motor_down(void);
void motor_stop(void);
void motor_init(void);

#define MOTOR_UP_PORT    GPIOF
#define MOTOR_UP_PIN     2

#define MOTOR_DOWN_PORT    GPIOF
#define MOTOR_DOWN_PIN     3

typedef enum {UP, DOWN, OFF}MotorState;

