/*
 * emotePlayer.h
 *
 *  Created on: Aug 7, 2025
 *      Author: hidre
 */

#ifndef INC_EMOTEPLAYER_H_
#define INC_EMOTEPLAYER_H_

#include "command.h"
#include "emote.h"
#include "servo.h"
#include <stdbool.h>

typedef struct EmotePlayerInitStruct
{
	ServoHandle** servos;
	uint8_t servoCount;
} EmotePlayerInit;

typedef enum EmotePlayerState
{
	STATE_STOPPED,
	STATE_PLAYING,
	STATE_ERROR,
} EmotePlayerState;

typedef struct EmotePlayerTrackStruct
{
	Command* commands;
	ServoHandle* servo;
	uint32_t commandIndex;
	CommandType currentCommand;
	uint8_t syncId;
	EmotePlayerState state;
} EmotePlayerTrack;

void InitEmotePlayer(EmotePlayerInit* emoteInit);
EmotePlayerState getPlayerState();
void StartEmote(Command** emote, uint32_t trackCount);

void UpdateEmotePlayer(uint32_t timeStamp);


bool CheckEmoteFinished();

#endif /* INC_EMOTEPLAYER_H_ */
