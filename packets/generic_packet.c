#include "generic_packet.h"
#include "libs/varint.h"

/** Creates a generic packet struct from a raw packet
 * @param packet Pointer to the generic_packet struct to fill out
 * @param rawpacket Pointer to the raw packet data
 */
void create_generic_packet(struct generic_packet* packet, u_char* rawpacket) {
	int bytes_decoded;
	int offset = 0;
	
	packet->length = decode_unsigned_varint(rawpacket, &bytes_decoded);
	
	offset += bytes_decoded;
	
	packet->id = decode_unsigned_varint(rawpacket+offset, &bytes_decoded);
	
	packet->data = rawpacket+offset+bytes_decoded;
	
}
