/*
 * servo.h
 *
 *  Created on: Aug 5, 2025
 *      Author: hidre
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct ServoInitStruct
{
	TIM_HandleTypeDef* timer;
	uint8_t channel;
	uint32_t minPulseWidth;
	uint32_t maxPulseWidth;
	float maxAngle;
	float offsetAngle;
	bool inverted;
}ServoInitConfig;

typedef struct ServoHandleStruct
{
	const TIM_HandleTypeDef* timer;
	uint8_t channel;
	uint32_t minPulseWidth;
	uint32_t maxPulseWidth;
	uint32_t timestamp;
	float pulsePerDegree;
	float maxAngle;
	float offsetAngle;
	float currentAngle;
	float targetAngle;
	float currentSpeed;
	float targetSpeed;
	float currentAcceleration;
	bool inverted;
	bool moving;
} ServoHandle;

ServoHandle* InitServo(ServoInitConfig* servoInitConfig);
void DestroyServoHandle(ServoHandle* servoHandle);
void SetServoAngleD0(ServoHandle* servo, float angle);
void SetServoAngleD1(ServoHandle* servo, float angle, float speed);
void SetServoAngleD2(ServoHandle* servo, float angle, float speed, float acceleration);
bool UpdateServoPosition(ServoHandle* servo, uint32_t deltatime);

#endif /* INC_SERVO_H_ */
