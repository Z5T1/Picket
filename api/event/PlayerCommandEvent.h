#pragma once

#include "../player/Player.h"

/** @file */

/** Called when a player enters a command */
typedef struct {
	Player player;		/** The player chatting */
	char* command;		/** The command beign entered */
	char* args;			/** Any arguments to the command */
} PlayerCommandEvent;
