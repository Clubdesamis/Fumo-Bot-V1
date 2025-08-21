/*
 * command.c
 *
 *  Created on: Aug 6, 2025
 *      Author: hidre
 */

#include "command.h"

Command InitHeaderCommand(uint8_t servoCount, uint32_t size)
{
	Command command;
	command.commandType = COMMAND_HEADER;
	command.commandHeader.servoCount = servoCount;
	command.commandHeader.size = size;
	return command;
}

Command InitStartCommand()
{
	Command command;
	command.commandType = COMMAND_START;
	return command;
}

Command InitFinishCommand()
{
	Command command;
	command.commandType = COMMAND_FINISH;
	return command;
}

Command InitSetAngleD0Command(float angle)
{
	Command command;
	command.commandType = COMMAND_SET_ANGLE_D0;
	command.commandSetAngleD0.angle = angle;
	return command;
}

Command InitSetAngleD1Command(float angle, float speed)
{
	Command command;
	command.commandType = COMMAND_SET_ANGLE_D1;
	command.commandSetAngleD1.angle = angle;
	command.commandSetAngleD1.speed = speed;
	return command;
}

Command InitWaitCommand(uint32_t timeMs)
{
	Command command;
	command.commandType = COMMAND_WAIT;
	command.commandWait.timeToSleepMs = timeMs;
	command.commandWait.timeSleptMs = 0;
	return command;
}

Command InitSyncCommand(uint8_t id)
{
	Command command;
	command.commandType = COMMAND_SYNC;
	command.commandSync.id = id;
	return command;
}


