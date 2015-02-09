#pragma once

#include "../player/Player.h"

/** @file */

/** Called when a player chats */
typedef struct {
	Player player;		/** The player chatting */
	char* message;		/** The message being chatted */
} PlayerChatEvent;
