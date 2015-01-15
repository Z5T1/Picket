#include "packet.h"
#include "generic_packet.h"
#include "connect_packet.h"

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
	struct session* ses;
	
	if (length == 0)
		return;
	
	create_generic_packet(&packet, payload);
	
	/*if (1) {
		int i;
		
		printf("Length: 0x%X - 0x%X\nID: 0x%X\nPayload: ", length, packet.length, packet.id);
		for (i = 0; i < length; i++) {
			printf("%X ", payload[i]);
		}
		printf("\nText: ");
		for (i = 0; i < length; i++) {
			printf("%c", payload[i]);
		}
		printf("\n\n");
	}*/
	
	ses = session_get_by_addr(address, port);
	
	if (ses == NULL) {
		if (packet.id == 2) {
			int i;
						
			process_connect_packet_from_payload(payload, address, port);
			
			/*if (port == 25565)
				printf("CLIENTBOUND\n");
			else
				printf("SERVERBOUND\n");
			printf("Length: 0x%X - 0x%X\nID: 0x%X\nPayload: ", length, packet.length, packet.id);
			for (i = 0; i < length; i++) {
				printf("%X ", payload[i]);
			}
			printf("\nText: ");
			for (i = 0; i < length; i++) {
				printf("%c", payload[i]);
			}
			printf("\n\n");*/
		}
	}
	else {
		
	}
	
	switch(packet.id) {
	
	}
}
