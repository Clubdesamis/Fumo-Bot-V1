/*
 * command.h
 *
 *  Created on: Aug 6, 2025
 *      Author: hidre
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_

#include "stm32f4xx_hal.h"

typedef enum CommandType
{
	COMMAND_HEADER = 1,
	COMMAND_START,
	COMMAND_FINISH,
	COMMAND_SET_ANGLE_D0,
	COMMAND_SET_ANGLE_D1,
	COMMAND_WAIT,
	COMMAND_SYNC,
} CommandType;

typedef struct CommandHeaderStruct
{
	uint8_t servoCount;
	uint32_t size;
} CommandHeader;

typedef struct CommandStartStruct
{

} CommandStart;

typedef struct CommandFinishStruct
{

} CommandFinish;

typedef struct CommandSetAngleD0Struct
{
	float angle;
} CommandSetAngleD0;

typedef struct CommandSetAngleD1Struct
{
	float angle;
	float speed;
} CommandSetAngleD1;

typedef struct CommandWaitStruct
{
	uint32_t timeToSleepMs;
	uint32_t timeSleptMs;
} CommandWait;

typedef struct CommandSyncStruct
{
	uint8_t id;
} CommandSync;

typedef struct CommandStruct
{
	CommandType commandType;
	union
	{
		CommandHeader commandHeader;
		CommandStart commandStart;
		CommandFinish commandFinish;
		CommandSetAngleD0 commandSetAngleD0;
		CommandSetAngleD1 commandSetAngleD1;
		CommandWait commandWait;
		CommandSync commandSync;
	};
} Command;

Command InitHeaderCommand(uint8_t trackCount, uint32_t size);
Command InitStartCommand();
Command InitFinishCommand();
Command InitSetAngleD0Command(float angle);
Command InitSetAngleD1Command(float angle, float speed);
Command InitWaitCommand(uint32_t timeMs);
Command InitSyncCommand(uint8_t id);

#endif /* INC_COMMAND_H_ */
