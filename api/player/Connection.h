#pragma once

#include <netinet/ip.h>

/** @file */

/** Represents a connection to the server */
typedef struct {
	struct in_addr ip;	/** The IP address of the connection */
	short port;			/** The port of the connection */
} Connection;
