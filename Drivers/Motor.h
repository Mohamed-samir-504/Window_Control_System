#include "TM4C123GH6PM.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "project_config.h"

#ifndef __MOTOR_H_
#define __MOTOR_H_

typedef enum {UP, DOWN, OFF} MotorState;
void motor_up(void);
void motor_down(void);
void motor_stop(void);
void motor_init(void);
void vSendMotorCommandToBack(xQueueHandle* xMotorQueue, MotorState command);
void vSendMotorCommandToFront(xQueueHandle* xMotorQueue, MotorState command);
#endif
 