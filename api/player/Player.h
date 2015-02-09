#pragma once

#include <netinet/ip.h>

#include "Connection.h"

/** @file */

/** Represents a player connected to the server */
typedef struct {
	char name[17];			/** The name of the player */
	char uuid[37];			/** The UUID of the player */
	Connection connection;	/** The IP address of the player */
} Player;
