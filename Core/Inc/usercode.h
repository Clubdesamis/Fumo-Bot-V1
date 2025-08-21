/*
 * usercode.h
 *
 *  Created on: Jul 27, 2025
 *      Author: hidre
 */

#ifndef INC_USERCODE_H_
#define INC_USERCODE_H_

//Includes
#include "stm32f4xx_hal.h"
#include "servo.h"
#include "command.h"
#include "emote.h"
#include "emotePlayer.h"
#include <stdbool.h>

//Defines
#define ANGLE_MAX 180

#define PW_WHOLE 1680000.0
#define PW_MIN 42000.0
#define PW_MAX 210000.0
#define PW_PER_DEGREE (PW_MAX - PW_MIN) / ANGLE_MAX

#define SERVO_1 TIM_CHANNEL_1
#define SERVO_2 TIM_CHANNEL_2
#define SERVO_3 TIM_CHANNEL_3
#define SERVO_4 TIM_CHANNEL_4

#define SERVO_ARM_RIGHT SERVO_1
#define SERVO_ARM_LEFT SERVO_2
#define SERVO_BOUNCE_RIGHT SERVO_3
#define SERVO_BOUNCE_LEFT SERVO_4

#define ARM_RIGHT_OFFSET = 0
#define ARM_LEFT_OFFSET = 0
#define BOUNCE_RIGHT_OFFSET = 0
#define BOUNCE_LEFT_OFFSET = 0

#define ARM_RIGHT_SIGN = -1
#define ARM_LEFT_SIGN = 1
#define BOUNCE_RIGHT_SIGN = -1
#define BOUNCE_LEFT_SIGN = 1

//Structures and typedefs

typedef struct HandlerStruct
{
	TIM_HandleTypeDef* htim2;
	UART_HandleTypeDef* huart2;
	ADC_HandleTypeDef* hadc1;
} Handlers;

typedef enum SensorStatusStruct
{
	FAR,
	MIDDLE,
	CLOSE
} SensorStatus;

//Initialization functions

void InitHandlers(const Handlers* _handlers);

void InitServos(void);

void InitEmoteplayer(void);

//Loop
void UserLoop(void);

//General code
void Dispose(void);
//Callbacks

#endif /* INC_USERCODE_H_ */
