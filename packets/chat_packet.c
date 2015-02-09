#include <string.h>
#include <stdlib.h>

#include "../picket.h"

#include "chat_packet.h"

static void (*chat_handlers[PICKET_MAX_HANDLERS])(PlayerChatEvent*);
static int chat_handler_count = 0;

static void (*cmd_handlers[PICKET_MAX_HANDLERS])(PlayerCommandEvent*);
static int cmd_handler_count = 0;

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
	printf("<%s> %s\n", player->name, packet->message);
	
	// Command
	if (packet->message[0] == '/') {
		PlayerCommandEvent evt;
		
		memcpy(&evt.player, player, sizeof(Player));
		evt.command = packet->message+1;
		evt.args = strtok(evt.command, " ");
		
		cmd_packet_call_handlers(&evt);
		
		free(packet->message);
	}
	// Chat
	else {
		PlayerChatEvent evt;
		
		memcpy(&evt.player, player, sizeof(Player));
		evt.message = packet->message;
		
		chat_packet_call_handlers(&evt);
		
		free(packet->message);
	}
	
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
	chat_handlers[chat_handler_count] = handler;
	chat_handler_count++;
}

/** Calls all handlers for PlayerChatEvent 
 * @param evt		The event to pass to the chat_handlers
 */
void chat_packet_call_handlers(PlayerChatEvent* evt) {
	int i;
	for (i = 0; i < chat_handler_count; i++) {
		if (chat_handlers[i] != NULL)
			(*chat_handlers[i])(evt);
	}
}

/** Adds a function to the list of handler functions
 * @param handler	The handler to add
 */
void cmd_packet_add_handler(void* handler) {
	cmd_handlers[cmd_handler_count] = handler;
	cmd_handler_count++;
}

/** Calls all handlers for PlayercmdEvent 
 * @param evt		The event to pass to the cmd_handlers
 */
void cmd_packet_call_handlers(PlayerCommandEvent* evt) {
	int i;
	for (i = 0; i < cmd_handler_count; i++) {
		if (cmd_handlers[i] != NULL)
			(*cmd_handlers[i])(evt);
	}
}

