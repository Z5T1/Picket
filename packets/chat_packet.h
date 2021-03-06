#pragma once

#include <stdint.h>
#include <pcap.h>

#include "../sessions.h"

#include "api/event/PlayerChatEvent.h"
#include "api/event/PlayerCommandEvent.h"

/** @file */

/** Type for a basic packet */
struct chat_packet {
	struct session* ses;	// The session issuing this packet
	uint64_t length;		// Packet Length
	uint64_t id;			// Packet ID
	char* message;			// The message being chatted
};

/** Creates a connect packet from a raw payload
 * @param packet	The packet to fill out
 * @param payload	The payload to create the packet from (as created by got_packet())
 */
void create_chat_packet(struct chat_packet* packet, u_char* payload);

/** Processes a connect packet
 * @param packet	The packet to process
 * @param player	The player sending this packet
 */
void process_chat_packet(struct chat_packet* packet, Player* player);

/** Processes a generic packet as though it were a connect packet.
 * A convienience method for create_chat_packet(); process_chat_packet();
 * @param payload	The payload to process (as created by got_packet())
 * @param player	The player sending this packet
 */
void process_chat_packet_from_payload(u_char* payload, Player* player);

/** Adds a function to the list of handler functions
 * @param handler	The handler to add
 */
void chat_packet_add_handler(void* handler);

/** Calls all handlers for PlayerChatEvent 
 * @param evt		The event to pass to the handlers
 */
void chat_packet_call_handlers(PlayerChatEvent* evt);

/** Adds a function to the list of handler functions
 * @param handler	The handler to add
 */
void cmd_packet_add_handler(void* handler);

/** Calls all handlers for PlayercmdEvent 
 * @param evt		The event to pass to the cmd_handlers
 */
void cmd_packet_call_handlers(PlayerCommandEvent* evt);
