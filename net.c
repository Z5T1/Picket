#include <stdlib.h>
#include <string.h>

#include "net.h"
#include "packets/packet.h"

/** Got Packet Callback */
void got_packet(u_char* args, const struct pcap_pkthdr* header, const u_char* packet) {
	const struct sniff_ethernet *ethernet; /* The ethernet header */
	const struct sniff_ip *ip; /* The IP header */
	const struct sniff_tcp *tcp; /* The TCP header */
	const char *payload; /* Packet payload */

	u_int size_ip;
	u_int size_tcp;
	
	int length;
	int i;
	u_char* data;

	ethernet = (struct sniff_ethernet*)(packet);
	ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
	size_ip = IP_HL(ip)*4;
	if (size_ip < 20) {
		printf("   * Invalid IP header length: %u bytes\n", size_ip);
		return;
	}
	tcp = (struct sniff_tcp*)(packet + SIZE_ETHERNET + size_ip);
	size_tcp = TH_OFF(tcp)*4;
	if (size_tcp < 20) {
		printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
		return;
	}
	payload = (u_char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);
	length = header->len - (SIZE_ETHERNET + size_ip + size_tcp);
	
	data = malloc(length);
	memcpy(data, payload, length);
	
	process_packet(data, length, ip->ip_src, tcp->th_sport);
	
	free(data);

}
