#pragma once

#include <stdint.h>
#include <pcap.h>

#include "../sessions.h"

#include "api/event/PlayerConnectEvent.h"

/** @file */

/** Type for a basic packet */
struct connect_packet {
	struct session* ses;	// The session issuing this packet
	uint64_t length;		// Packet Length
	uint64_t id;			// Packet ID
	char uuid[40];			// The UUID for this login
	char name[17];			// The name for this login
};

/** Creates a connect packet from a raw payload
 * @param packet	The packet to fill out
 * @param payload	The payload to create the packet from (as created by got_packet())
 */
void create_connect_packet(struct connect_packet* packet, u_char* payload);

/** Processes a connect packet
 * @param packet	The packet to process
 * @param in_addr	The address of the sender
 * @param port		The port of the sender
 */
void process_connect_packet(struct connect_packet* packet, struct in_addr address, short port);

/** Processes a generic packet as though it were a connect packet.
 * A convienience method for create_connect_packet(); process_connect_packet();
 * @param payload	The payload to process (as created by got_packet())
 * @param in_addr	The address of the sender
 * @param port		The port of the sender
 */
void process_connect_packet_from_payload(u_char* payload, struct in_addr address, short port);

/** Adds a function to the list of handler functions
 * @param handler	The handler to add
 */
void connect_packet_add_handler(void* handler);

/** Calls all handlers for PlayerConnectEvent 
 * @param evt		The event to pass to the handlers
 */
void connect_packet_call_handlers(PlayerConnectEvent* evt);
