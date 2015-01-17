#pragma once

#include <netinet/ip.h>

#include "../player/Player.h"

/** @file */

/** Called when a player chats or enters a command. If message begins with
 * a / the player is entering a command. Otherwise, he's chatting. */
typedef struct {
	Player player;		/** The player connecting */
	char* message;		/** The message being chatted */
} PlayerChatEvent;
