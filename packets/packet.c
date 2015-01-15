#include "packet.h"
#include "generic_packet.h"

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
 * @param in_addr	The address of the sender
 * @param port		The port of the sender
 */
void process_packet(u_char* payload, int length, struct in_addr address, short port) {
	struct generic_packet packet;
	
	if (length == 0)
		return;
	
	create_generic_packet(&packet, payload);
	
	switch(packet.id) {
	
	}
}
