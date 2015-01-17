#pragma once

#include <stdio.h>
#include <pcap.h>
#include <netinet/ip.h>

#include "libs/varint.h"

/** @file */

/* Packet IDs */
#define PACKET_CONNECT 2
#define PACKET_CHAT 1

/** Gets the packet ID for a packet
 * @param packet The packet to get the ID for
 * @return The packet ID
 */
char get_packet_id(const u_char* packet);

/** Gets the length of a packet
 * @param packet The packet to get the length of
 * @return The length
 */
short get_packet_length(const u_char* packet);

/** Processes a packet 
 * @param payload	The payload for the packet
 * @param length	The length of the payload
 * @param s_addr	The address of the sender
 * @param d_addr	The address of the receiver
 * @param s_port	The port of the sender
 * @param d_port	The port of the receiver
 */
void process_packet(u_char* payload, int length, struct in_addr s_address, struct in_addr d_address, short s_port, short d_port);
