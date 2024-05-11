#include "TM4C123GH6PM.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
typedef enum {UP, DOWN, OFF} MotorState;
void motor_up(void);
void motor_down(void);
void motor_stop(void);
void motor_init(void);
void vSendMotorCommandToBack(xQueueHandle* xMotorQueue, MotorState command);
void vSendMotorCommandToFront(xQueueHandle* xMotorQueue, MotorState command);

#define MOTOR_UP_PORT    GPIOF
#define MOTOR_UP_PIN     2

#define MOTOR_DOWN_PORT    GPIOF
#define MOTOR_DOWN_PIN     3


