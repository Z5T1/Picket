#pragma once

#include <netinet/ip.h>

/** @file */

typedef struct {
	char name[17];		/** The name of the player */
	struct in_addr ip;	/** The IP address of the player */
} Player;
