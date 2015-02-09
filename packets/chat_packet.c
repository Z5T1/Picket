#include <string.h>
#include <stdlib.h>

#include "../picket.h"

#include "chat_packet.h"

static void (*handlers[PICKET_MAX_HANDLERS])(PlayerChatEvent*);
static int handler_count = 0;

/** Creates a connect packet from a raw payload
 * @param packet	The packet to fill out
 * @param payload	The payload to create the packet from (as created by got_packet())
 */
void create_chat_packet(struct chat_packet* packet, u_char* payload) {
	int bytes_decoded;
	int offset = 0;
	int strlen;
	int i;
	
	// Length
	packet->length = decode_unsigned_varint(payload, &bytes_decoded);
	offset += bytes_decoded;
	
	// ID
	packet->id = decode_unsigned_varint(payload+offset, &bytes_decoded);
	offset += bytes_decoded;
	
	// Chat Message
	strlen = decode_unsigned_varint(payload+offset, &bytes_decoded);
	offset += bytes_decoded;
	packet->message = malloc(strlen+1);
	for (i = 0; i < strlen; i++) {
		packet->message[i] = payload[offset+i];
	}
	packet->message[i] = 0;
	offset += i;
	
}

/** Processes a connect packet
 * @param packet	The packet to process
 * @param player	The player sending this packet
 */
void process_chat_packet(struct chat_packet* packet, Player* player) {
	PlayerChatEvent evt;
	
	printf("<%s> %s\n", player->name, packet->message);
	
	memcpy(&evt.player, player, sizeof(Player));
	evt.message = packet->message;
	
	chat_packet_call_handlers(&evt);
	
	free(packet->message);
}

/** Processes a generic packet as though it were a connect packet.
 * A convienience method for create_chat_packet(); process_chat_packet();
 * @param payload	The payload to process (as created by got_packet())
 * @param player	The player sending this packet
 */
void process_chat_packet_from_payload(u_char* payload, Player* player) {
	struct chat_packet packet;
	
	create_chat_packet(&packet, payload);
	process_chat_packet(&packet, player);
}

/** Adds a function to the list of handler functions
 * @param handler	The handler to add
 */
void chat_packet_add_handler(void* handler) {
	handlers[handler_count] = handler;
	handler_count++;
}

/** Calls all handlers for PlayerChatEvent 
 * @param evt		The event to pass to the handlers
 */
void chat_packet_call_handlers(PlayerChatEvent* evt) {
	int i;
	for (i = 0; i < handler_count; i++) {
		if (handlers[i] != NULL)
			(*handlers[i])(evt);
	}
}
