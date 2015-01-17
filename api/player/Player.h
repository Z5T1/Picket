#pragma once

#include <netinet/ip.h>

/** @file */

/** Represents a player connected to the server */
typedef struct {
	char name[17];		/** The name of the player */
	struct in_addr ip;	/** The IP address of the player */
} Player;
