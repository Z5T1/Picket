#include <string.h>

#include "../picket.h"

#include "connect_packet.h"

static void (*handlers[PICKET_MAX_HANDLERS])(PlayerConnectEvent*);
static int handler_count = 0;

/** Creates a connect packet from a raw payload
 * @param packet	The packet to fill out
 * @param payload	The payload to create the packet from (as created by got_packet())
 */
void create_connect_packet(struct connect_packet* packet, u_char* payload) {
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
	
	// Player UUID
	strlen = decode_unsigned_varint(payload+offset, &bytes_decoded);
	offset += bytes_decoded;
	for (i = 0; i < strlen; i++) {
		packet->uuid[i] = payload[offset+i];
	}
	packet->uuid[i] = 0;
	offset += i;
	
	// Player Name
	strlen = decode_unsigned_varint(payload+offset, &bytes_decoded);
	offset += bytes_decoded;
	for (i = 0; i < strlen; i++) {
		packet->name[i] = payload[offset+i];
	}
	packet->name[i] = 0;
	
}

/** Processes a connect packet
 * @param packet	The packet to process
 * @param in_addr	The address of the sender
 * @param port		The port of the sender
 */
void process_connect_packet(struct connect_packet* packet, struct in_addr address, short port) {
	PlayerConnectEvent evt;
	
	printf("%s (UUID %s) has connected\n", packet->name, packet->uuid);
	session_put(address, port, packet->name);
	
	strcpy(evt.player.name, packet->name);
	strcpy(evt.uuid, packet->uuid);
	evt.player.ip = address;
	
	connect_packet_call_handlers(&evt);
}

/** Processes a generic packet as though it were a connect packet.
 * A convienience method for create_connect_packet(); process_connect_packet();
 * @param payload	The payload to process (as created by got_packet())
 * @param in_addr	The address of the sender
 * @param port		The port of the sender
 */
void process_connect_packet_from_payload(u_char* payload, struct in_addr address, short port) {
	struct connect_packet packet;
	
	create_connect_packet(&packet, payload);
	process_connect_packet(&packet, address, port);
}

/** Adds a function to the list of handler functions
 * @param handler	The handler to add
 */
void connect_packet_add_handler(void* handler) {
	handlers[handler_count] = handler;
	handler_count++;
}

/** Calls all handlers for PlayerConnectEvent 
 * @param evt		The event to pass to the handlers
 */
void connect_packet_call_handlers(PlayerConnectEvent* evt) {
	int i;
	for (i = 0; i < handler_count; i++) {
		if (handlers[i] != NULL)
			(*handlers[i])(evt);
	}
}
