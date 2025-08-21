/*
 * emote.h
 *
 *  Created on: Aug 5, 2025
 *      Author: hidre
 */

#ifndef INC_EMOTE_H_
#define INC_EMOTE_H_

#include <stdlib.h>
#include "stm32f4xx_hal.h"
#include "servo.h"
#include "command.h"

//Loading various emotes
void DestroyEmote(Command* emote[], uint32_t count);

Command** LoadWaveEmote(uint32_t* count);
Command** LoadBounceEmote(uint32_t* count);

#endif /* INC_EMOTE_H_ */
