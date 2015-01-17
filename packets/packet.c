#include "packet.h"
#include "generic_packet.h"
#include "connect_packet.h"
#include "chat_packet.h"

/** Gets the packet ID for a packet
 * @param packet The packet to get the ID for
 * @return The packet ID
 */
char get_packet_id(const u_char* packet) {
	return (char) packet[2];
}

/** Gets the length of a packet
 * @param packet The packet to get the length of
 * @return The length
 */
short get_packet_length(const u_char* packet) {
	return (short) packet[0];
}

/** Processes a packet 
 * @param payload	The payload for the packet
 * @param length	The length of the payload
 * @param s_addr	The address of the sender
 * @param d_addr	The address of the receiver
 * @param s_port	The port of the sender
 * @param d_port	The port of the receiver
 */
void process_packet(u_char* payload, int length, struct in_addr s_address, struct in_addr d_address, short s_port, short d_port) {
	struct generic_packet packet;
	struct session* ses;
	
	if (length == 0)
		return;
	
	create_generic_packet(&packet, payload);
	
	ses = session_get_by_addr(s_address, s_port);
	
	if (ses == NULL) {
		if (packet.id == PACKET_CONNECT) {
			process_connect_packet_from_payload(payload, d_address, d_port);
		}
	}
	else {
		switch(packet.id) {
		case PACKET_CHAT:
			process_chat_packet_from_payload(payload, ses);
			break;
		}
	}
	
}
