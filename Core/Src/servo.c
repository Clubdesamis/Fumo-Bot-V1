/*
 * servo.c
 *
 *  Created on: Aug 5, 2025
 *      Author: hidre
 */

#include "servo.h"

ServoHandle* InitServo(ServoInitConfig* servoInitConfig)
{
	ServoHandle handle =
	{
		.timer = servoInitConfig->timer,
		.channel = servoInitConfig->channel,
		.minPulseWidth = servoInitConfig->minPulseWidth,
		.maxPulseWidth = servoInitConfig->maxPulseWidth,
		.timestamp = 0,
		.pulsePerDegree = ((float)servoInitConfig->maxPulseWidth - (float)servoInitConfig->minPulseWidth) / servoInitConfig->maxAngle,
		.maxAngle = servoInitConfig->maxAngle,
		.offsetAngle = servoInitConfig->offsetAngle,
		.currentAngle = 0,
		.targetAngle = 0,
		.currentSpeed = 0,
		.targetSpeed = 0,
		.currentAcceleration = 0,
		.inverted = servoInitConfig->inverted,
		.moving = false,
	};

	ServoHandle* _handle = malloc(sizeof(ServoHandle));
	memcpy(_handle, &handle, sizeof(ServoHandle));
	HAL_TIM_PWM_Start(servoInitConfig->timer, servoInitConfig->channel);
	return _handle;
}

void DestroyServoHandle(ServoHandle* servoHandle)
{
	free(servoHandle);
}

void SetServoAngleD0(ServoHandle* servo, float angle)
{
	uint32_t pulse;
	if(servo->inverted)
	{
		pulse = servo->maxPulseWidth - servo->pulsePerDegree * angle - servo->pulsePerDegree * servo->offsetAngle;
	}
	else
	{
		pulse = servo->minPulseWidth + servo->pulsePerDegree * angle + servo->pulsePerDegree * servo->offsetAngle;
	}

	if(pulse > servo->maxPulseWidth)
	{
		pulse = servo->maxPulseWidth;
	}
	else if(pulse < servo->minPulseWidth)
	{
		pulse = servo->minPulseWidth;
	}

	if(angle < servo->maxAngle)
	{
		if(angle > 0)
		{
			servo->currentAngle = angle;
		}
		else
		{
			servo->currentAngle = 0;
		}
	}
	else
	{
		servo->currentAngle = servo->maxAngle;
	}

	__HAL_TIM_SET_COMPARE(servo->timer, servo->channel, pulse);
}

void SetServoAngleD1(ServoHandle* servo, float angle, float speed)
{
	if(angle + servo->offsetAngle > servo->maxAngle)
	{
		servo->targetAngle = servo->maxAngle;
	}
	else if(angle + servo->offsetAngle < 0)
	{
		servo->targetAngle = 0;
	}
	else
	{
		servo->targetAngle = angle;
	}

	servo->currentSpeed = speed;
	servo->moving = true;
	servo->timestamp = HAL_GetTick();
}

bool UpdateServoPosition(ServoHandle* servo, uint32_t deltatime)
{
	if(servo->moving)
	{
		//uint32_t deltaTime = timestamp - servo->timestamp;
		//servo->timestamp = timestamp;
		float deltaAngle = ((float)deltatime * servo->currentSpeed) / 1000;

		//Going down
		if(servo->currentAngle > servo->targetAngle)
		{
			if(servo->currentAngle - deltaAngle < servo->targetAngle)
			{
				SetServoAngleD0(servo, servo->targetAngle);
				servo->currentSpeed = 0.0;
				servo->moving = false;
				return true;
			}
			else
			{
				SetServoAngleD0(servo, servo->currentAngle - deltaAngle);
			}
		}
		//Going up
		else if(servo->currentAngle < servo->targetAngle)
		{
			if(servo->currentAngle + deltaAngle > servo->targetAngle)
			{
				SetServoAngleD0(servo, servo->targetAngle);
				servo->currentSpeed = 0.0;
				servo->moving = false;
				return true;
			}
			else
			{
				SetServoAngleD0(servo, servo->currentAngle + deltaAngle);

			}
		}
	}

	return false;
}


