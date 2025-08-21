/*
 * usercode.c
 *
 *  Created on: Jul 27, 2025
 *      Author: hidre
 */

#include "usercode.h"

//Global private variables
//Static data handles
static Handlers handlers;
static SensorStatus sensorStatus = FAR;
//Heap allocated handles
static ServoHandle* servoArmRight;
static ServoHandle* servoArmLeft;
static ServoHandle* servoBounceRight;
static ServoHandle* servoBounceLeft;
static Command** waveEmote;
static Command** bounceEmote;
static uint32_t waveEmoteServoCount;
static uint32_t bounceEmoteServoCount;
static uint32_t time1 = 0;
static uint32_t time2 = 0;
static uint32_t deltatime = 0;
static uint32_t farReadCount = 0;
static uint32_t middleReadCount = 0;
static uint32_t closeReadCount = 0;
static bool doMiddleEmote = false;
static bool doCloseEmote = false;


void InitHandlers(const Handlers* _handlers)
{
	handlers = *_handlers;
}

void InitServos()
{


	ServoInitConfig armRightConfig =
	{
		.timer = handlers.htim2,
		.channel = SERVO_ARM_RIGHT,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.maxAngle = 180.0,
		.offsetAngle = 0.0,
		.inverted = true
	};

	servoArmRight = InitServo(&armRightConfig);

	ServoInitConfig armLeftConfig =
	{
		.timer = handlers.htim2,
		.channel = SERVO_ARM_LEFT,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.maxAngle = 180.0,
		.offsetAngle = 0.0,
		.inverted = false
	};

	servoArmLeft = InitServo(&armLeftConfig);

	ServoInitConfig bounceRightConfig =
	{
		.timer = handlers.htim2,
		.channel = SERVO_BOUNCE_RIGHT,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.maxAngle = 180.0,
		.offsetAngle = 0.0,
		.inverted = false
	};

	servoBounceRight = InitServo(&bounceRightConfig);

	ServoInitConfig bounceLeftConfig =
	{
		.timer = handlers.htim2,
		.channel = SERVO_BOUNCE_LEFT,
		.minPulseWidth = PW_MIN,
		.maxPulseWidth = PW_MAX,
		.maxAngle = 180.0,
		.offsetAngle = 0.0,
		.inverted = true
	};

	servoBounceLeft = InitServo(&bounceLeftConfig);

	SetServoAngleD0(servoArmRight, 90);
	SetServoAngleD0(servoArmLeft, 90);
	SetServoAngleD0(servoBounceRight, 90);
	SetServoAngleD0(servoBounceLeft, 90);

	HAL_Delay(500);
	//SetServoAngleD0(servoArmRight, 60);
	//SetServoAngleD0(servoArmLeft, 60);
	//HAL_Delay(1000);
	//SetServoAngleD1(servoArmRight, 120, 30);
	//SetServoAngleD1(servoArmRight, 120, 30);
	//SetServoAngleD1(servoArmLeft, 120, 30);
	SetServoAngleD1(servoArmLeft, 120, 30);
}

void InitEmoteplayer()
{
	waveEmote = LoadWaveEmote(&waveEmoteServoCount);
	bounceEmote = LoadBounceEmote(&bounceEmoteServoCount);

	ServoHandle* servos[4] = {servoArmRight, servoArmLeft, servoBounceRight, servoBounceLeft};

	EmotePlayerInit emotePlayerInit =
	{
		.servos = servos,
		.servoCount = 4
	};

	InitEmotePlayer(&emotePlayerInit);

	//StartEmote(waveEmote, 4);

}

void UserLoop()
{
	time1 = HAL_GetTick();


	///////////Insert all loop code here/////////////////////////////

	UpdateEmotePlayer(deltatime);

	HAL_ADC_PollForConversion(handlers.hadc1, 1000);
	uint16_t readValue = HAL_ADC_GetValue(handlers.hadc1);
	HAL_ADC_Start(handlers.hadc1);


	if(getPlayerState() == STATE_STOPPED)
	{
		if(readValue > 600)
		{
			middleReadCount = 0;
			farReadCount = 0;

			closeReadCount++;
			if(closeReadCount >= 10)
			{
				doCloseEmote = true;
				sensorStatus = CLOSE;
				closeReadCount = 0;
			}
		}
		else if(readValue > 150 && readValue < 600)
		{
			closeReadCount = 0;
			farReadCount = 0;

			middleReadCount++;
			if(middleReadCount >= 10)
			{
				//StartEmote(waveEmote, 4);
				if(sensorStatus == FAR)
				{
					doMiddleEmote = true;
				}

				sensorStatus = MIDDLE;
				middleReadCount = 0;
			}
		}
		else if(readValue < 150)
		{
			closeReadCount = 0;
			middleReadCount = 0;

			farReadCount++;
			if(farReadCount >= 10)
			{
				sensorStatus = FAR;
				farReadCount = 0;
			}
		}
	}

	if(doMiddleEmote)
	{
		StartEmote(waveEmote, 4);
		doMiddleEmote = false;
	}
	else if(doCloseEmote)
	{
		//StartEmote(bounceEmote, 4);
		doCloseEmote = false;
	}

	/////////////////////////////////////////////////////////////////
	HAL_Delay(10);
	time2 = HAL_GetTick();
	deltatime = time2 - time1;
	time1 = time2;
	//UpdateServoPosition(servoArmLeft, deltatime);
	//UpdateEmote();
}

void Dispose()
{
	DestroyServoHandle(servoArmRight);
	DestroyServoHandle(servoArmLeft);
	DestroyServoHandle(servoBounceRight);
	DestroyServoHandle(servoBounceLeft);
}
