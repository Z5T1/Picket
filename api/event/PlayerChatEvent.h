#pragma once

#include <netinet/ip.h>

#include "../player/Player.h"

/** @file */

typedef struct {
	Player player;		/** The player connecting */
	char uuid[40];		/** The UUID of the player connecting */
} PlayerConnectEvent;
