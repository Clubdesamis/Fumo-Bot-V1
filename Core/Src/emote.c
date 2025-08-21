/*
 * emote.c
 *
 *  Created on: Aug 5, 2025
 *      Author: hidre
 */

#include "emote.h"

void DestroyEmote(Command* emote[], uint32_t count)
{
	for(uint32_t i = 0; i < count; i++)
	{
		free(emote[i]);
	}

	free(emote);
}

Command** LoadBounceEmote(uint32_t* count)
{
	Command armRightCommands[] =
	{
		InitHeaderCommand(1, 0),
		InitStartCommand(),

		InitWaitCommand(300),
		InitSetAngleD1Command(160, 200),
		InitSetAngleD1Command(90, 200),
		InitWaitCommand(100),
		InitSetAngleD1Command(160, 200),
		InitSetAngleD1Command(90, 200),
		InitWaitCommand(100),
		InitSetAngleD1Command(160, 200),
		InitSetAngleD1Command(90, 200),
		InitWaitCommand(100),
		InitSetAngleD1Command(160, 200),
		InitSetAngleD1Command(90, 200),
		InitWaitCommand(500),

		InitFinishCommand(),
	};

	Command armLeftCommands[] =
	{
			InitHeaderCommand(1, 0),
			InitStartCommand(),

			InitWaitCommand(300),
			InitSetAngleD1Command(160, 200),
			InitSetAngleD1Command(90, 200),
			InitWaitCommand(100),
			InitSetAngleD1Command(160, 200),
			InitSetAngleD1Command(90, 200),
			InitWaitCommand(100),
			InitSetAngleD1Command(160, 200),
			InitSetAngleD1Command(90, 200),
			InitWaitCommand(100),
			InitSetAngleD1Command(160, 200),
			InitSetAngleD1Command(90, 200),
			InitWaitCommand(500),

			InitFinishCommand(),
	};

	Command bounceRightCommands[] =
	{
			InitHeaderCommand(1, 0),
			InitStartCommand(),
			/*
			InitSetAngleD1Command(130, 150),
			InitWaitCommand(500),
			InitSetAngleD1Command(90, 150),
			InitWaitCommand(500),
			InitSetAngleD1Command(130, 150),
			InitWaitCommand(500),
			InitSetAngleD1Command(90, 150),
			InitWaitCommand(500),

			InitWaitCommand(300),
			InitSetAngleD1Command(140, 200),
			InitSetAngleD1Command(90, 200),
			InitWaitCommand(100),
			InitSetAngleD1Command(140, 200),
			InitSetAngleD1Command(90, 200),
			InitWaitCommand(100),
			InitSetAngleD1Command(140, 200),
			InitSetAngleD1Command(90, 200),
			InitWaitCommand(100),
			InitSetAngleD1Command(140, 200),
			InitSetAngleD1Command(90, 200),
			InitWaitCommand(500),
			*/
			InitFinishCommand(),
	};

	Command bounceLeftCommands[] =
	{
			InitHeaderCommand(1, 0),
			InitStartCommand(),
			/*
			InitSetAngleD1Command(90, 150),
			InitWaitCommand(500),
			InitSetAngleD1Command(130, 150),
			InitWaitCommand(500),
			InitSetAngleD1Command(90, 150),
			InitWaitCommand(500),
			InitSetAngleD1Command(130, 150),
			InitWaitCommand(500),
			InitWaitCommand(300),
			InitSetAngleD1Command(90, 200),
			InitSetAngleD1Command(140, 200),
			InitWaitCommand(100),
			InitSetAngleD1Command(90, 200),
			InitSetAngleD1Command(140, 200),
			InitWaitCommand(100),
			InitSetAngleD1Command(90, 200),
			InitSetAngleD1Command(140, 200),
			InitWaitCommand(100),
			InitSetAngleD1Command(90, 200),
			InitSetAngleD1Command(140, 200),
			InitWaitCommand(500),
			*/

			InitFinishCommand(),
	};

	armRightCommands[0].commandHeader.size = sizeof(armRightCommands) / sizeof(Command);
	armLeftCommands[0].commandHeader.size = sizeof(armLeftCommands) / sizeof(Command);
	bounceRightCommands[0].commandHeader.size = sizeof(bounceRightCommands) / sizeof(Command);
	bounceLeftCommands[0].commandHeader.size = sizeof(bounceLeftCommands) / sizeof(Command);


	Command* armRightBuffer = malloc(sizeof(armRightCommands));
	Command* armLeftBuffer = malloc(sizeof(armLeftCommands));
	Command* bounceRightBuffer = malloc(sizeof(bounceRightCommands));
	Command* bounceLeftBuffer = malloc(sizeof(bounceLeftCommands));

	memcpy(armRightBuffer, armRightCommands, sizeof(armRightCommands));
	memcpy(armLeftBuffer, armLeftCommands, sizeof(armLeftCommands));
	memcpy(bounceRightBuffer, bounceRightCommands, sizeof(bounceRightCommands));
	memcpy(bounceLeftBuffer, bounceLeftCommands, sizeof(bounceLeftCommands));

	Command** commands = malloc(4 * sizeof(Command*));
	commands[0] = armRightBuffer;
	commands[1] = armLeftBuffer;
	commands[2] = bounceRightBuffer;
	commands[3] = bounceLeftBuffer;


	*count = 4;
	return commands;
}

Command** LoadWaveEmote(uint32_t* count)
{
	Command armRightCommands[] =
	{
		InitHeaderCommand(1, 0),
		InitStartCommand(),
		InitWaitCommand(300),
		InitSetAngleD1Command(160, 350),
		InitSetAngleD1Command(90, 350),
		InitSetAngleD1Command(160, 350),
		InitSetAngleD1Command(90, 350),
		InitSetAngleD1Command(160, 350),
		InitSetAngleD1Command(70, 350),
		InitWaitCommand(1000),
		InitFinishCommand(),
	};

	Command armLeftCommands[] =
	{
		InitHeaderCommand(1, 0),
		InitStartCommand(),
		InitFinishCommand(),
	};

	Command bounceRightCommands[] =
	{
		InitHeaderCommand(1, 0),
		InitStartCommand(),
		InitSetAngleD1Command(140, 200),
		InitWaitCommand(1100),
		InitSetAngleD1Command(90, 200),
		InitFinishCommand(),
	};

	Command bounceLeftCommands[] =
	{
		InitHeaderCommand(1, 0),
		InitStartCommand(),
		//InitSetAngleD1Command(120, 120),
		InitFinishCommand(),
	};

	armRightCommands[0].commandHeader.size = sizeof(armRightCommands) / sizeof(Command);
	armLeftCommands[0].commandHeader.size = sizeof(armLeftCommands) / sizeof(Command);
	bounceRightCommands[0].commandHeader.size = sizeof(bounceRightCommands) / sizeof(Command);
	bounceLeftCommands[0].commandHeader.size = sizeof(bounceLeftCommands) / sizeof(Command);


	Command* armRightBuffer = malloc(sizeof(armRightCommands));
	Command* armLeftBuffer = malloc(sizeof(armLeftCommands));
	Command* bounceRightBuffer = malloc(sizeof(bounceRightCommands));
	Command* bounceLeftBuffer = malloc(sizeof(bounceLeftCommands));

	memcpy(armRightBuffer, armRightCommands, sizeof(armRightCommands));
	memcpy(armLeftBuffer, armLeftCommands, sizeof(armLeftCommands));
	memcpy(bounceRightBuffer, bounceRightCommands, sizeof(bounceRightCommands));
	memcpy(bounceLeftBuffer, bounceLeftCommands, sizeof(bounceLeftCommands));

	Command** commands = malloc(4 * sizeof(Command*));
	commands[0] = armRightBuffer;
	commands[1] = armLeftBuffer;
	commands[2] = bounceRightBuffer;
	commands[3] = bounceLeftBuffer;


	*count = 4;
	return commands;
}


