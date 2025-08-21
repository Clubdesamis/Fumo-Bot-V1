/*
 * emotePlayer.c
 *
 *  Created on: Aug 7, 2025
 *      Author: hidre
 */

#include "emotePlayer.h"

static uint32_t servoCount = 0;
static ServoHandle** servoHandles;
static Command** currentEmote;
static EmotePlayerTrack* tracks;
static EmotePlayerState playerState;

void ResetEmoteTracks()
{
	for(uint32_t i = 0; i < servoCount; i++)
	{
		tracks[i].commandIndex = 0;
		tracks[i].currentCommand = COMMAND_HEADER;
		tracks[i].state = STATE_STOPPED;
		tracks[i].syncId = 0;
		tracks[i].commands = NULL;
		//tracks[i].servo = servoHandles[i];
	}
}

void InitEmotePlayer(EmotePlayerInit* emoteInit)
{
	servoCount = emoteInit->servoCount;
	servoHandles = emoteInit->servos;
	playerState = STATE_STOPPED;
	tracks = malloc(sizeof(EmotePlayerTrack) * servoCount);
	for(uint32_t i = 0; i < servoCount; i++)
	{
		tracks[i].commandIndex = 0;
		tracks[i].currentCommand = COMMAND_HEADER;
		tracks[i].state = STATE_STOPPED;
		tracks[i].syncId = 0;
		tracks[i].commands = NULL;
		tracks[i].servo = emoteInit->servos[i];
	}
}

EmotePlayerState getPlayerState()
{
	return playerState;
}

void DestroyEmotePlayer()
{
	free(tracks);
}

void StartEmote(Command** emote, uint32_t trackCount)
{
	if(trackCount != servoCount)
	{
		playerState = STATE_ERROR;
		return;
	}

	currentEmote = emote;
	playerState = STATE_PLAYING;

	for(uint32_t i = 0; i < servoCount; i++)
	{
		tracks[i].commands = emote[i];
		tracks[i].state = STATE_PLAYING;
	}
}

void HandleCommandHeader(EmotePlayerTrack* track, uint32_t deltatime)
{
	if(track->commands[track->commandIndex].commandType == COMMAND_HEADER)
	{
		//Read header if necessary
		track->commandIndex++;
	}
	else
	{
		track->state = STATE_ERROR;
	}
}

void HandleCommandStart(EmotePlayerTrack* track, uint32_t deltatime)
{
	if(track->state == STATE_PLAYING)
	{
		track->commandIndex++;
	}
	else
	{
		track->state = STATE_ERROR;
	}
}

void HandleCommandFinish(EmotePlayerTrack* track, uint32_t deltatime)
{
	track->state = STATE_STOPPED;
}

void HandleCommandSetAngleD0(EmotePlayerTrack* track, uint32_t deltatime)
{
	SetServoAngleD0(track->servo, track->commands[track->commandIndex].commandSetAngleD0.angle);
}

void HandleCommandSetAngleD1(EmotePlayerTrack* track, uint32_t deltatime)
{
	/*
	uint32_t count = track->commands[0].commandHeader.size;
	for(uint32_t j = 0; j < count; j++)
	{
		if(tracks->commands[j].commandType == COMMAND_SET_ANGLE_D1)
		{
			float speed = tracks->commands[j].commandSetAngleD1.speed;
			speed++;
			speed--;
		}
	}
	*/

	if(track->servo->moving)
	{
		if(UpdateServoPosition(track->servo, deltatime))
		{
			track->commandIndex++;
		}
	}
	else
	{
		SetServoAngleD1(track->servo, track->commands[track->commandIndex].commandSetAngleD1.angle, track->commands[track->commandIndex].commandSetAngleD1.speed);
	}
}

void HandleCommandWait(EmotePlayerTrack* track, uint32_t deltatime)
{
	track->commands[track->commandIndex].commandWait.timeSleptMs += deltatime;
	if(track->commands[track->commandIndex].commandWait.timeSleptMs >= track->commands[track->commandIndex].commandWait.timeToSleepMs)
	{
		track->commands[track->commandIndex].commandWait.timeSleptMs = 0;
		track->commandIndex++;
	}
}

void HandleCommandSync(EmotePlayerTrack* track, uint32_t deltatime)
{

}

void UpdateEmotePlayer(uint32_t deltatime)
{
	if(playerState == STATE_PLAYING)
	{
		bool finished = true;
		for(uint32_t i = 0; i < servoCount; i++)
		{
			if(tracks[i].state == STATE_PLAYING)
			{
				switch(tracks[i].commands[tracks[i].commandIndex].commandType)
				{
					case COMMAND_HEADER:
						HandleCommandHeader(&tracks[i], deltatime);
					break;
					case COMMAND_START:
						HandleCommandStart(&tracks[i], deltatime);
					break;
					case COMMAND_FINISH:
						HandleCommandFinish(&tracks[i], deltatime);
					break;
					case COMMAND_SET_ANGLE_D0:
						HandleCommandSetAngleD0(&tracks[i], deltatime);
					break;
					case COMMAND_SET_ANGLE_D1:
						HandleCommandSetAngleD1(&tracks[i], deltatime);
					break;
					case COMMAND_WAIT:
						HandleCommandWait(&tracks[i], deltatime);
					break;
					case COMMAND_SYNC:
						HandleCommandSync(&tracks[i], deltatime);
					break;
					default:
						playerState = STATE_ERROR;
					break;
				}

				finished = false;
			}
		}

		if(finished)
		{
			playerState = STATE_STOPPED;
			ResetEmoteTracks();
		}
	}
}

