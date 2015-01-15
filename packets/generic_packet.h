#pragma once

#include <stdint.h>
#include <pcap.h>

#include "../sessions.h"

/** @file */

/** Type for a basic packet */
struct generic_packet {
	struct session* ses;	// The session issuing this packet
	uint64_t length;		// Packet Length
	uint64_t id;			// Packet ID
	const char* data;		// Pointer to the data for the packet
};

/** Creates a generic packet from a raw payload
 * @param packet Pointer to the generic_packet struct to fill out
 * @param payload The payload to create the packet from (as created by got_packet())
 */
void create_generic_packet(struct generic_packet* packet, u_char* payload);

