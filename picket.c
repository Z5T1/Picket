#include <stdio.h>
#include <pcap.h>

#include "picket.h"
#include "sessions.h"
#include "net.h"

int main(int argc, char** argv) {
	
	// Variable Declaration
	pcap_t* handle;
	char* dev = argv[1];
	char errbuf[PCAP_ERRBUF_SIZE];
	bpf_u_int32 netmask;
	bpf_u_int32 netaddr;
	struct bpf_program filter;
	struct pcap_pkthdr packet_header;
	const u_char* packet_data;
	
	const int slots = 20;
	
	// Device Initialiazation
	// Device Lookup
	if (pcap_lookupnet(dev, &netaddr, &netmask, errbuf) < 0) {
		fprintf(stderr, "libpcap error looking up device %s: %s\n", dev, errbuf);
		return (1);
	}
	// Open the Session
	handle = pcap_open_live(dev, BUFSIZ, 0, PICKET_TIMEOUT, errbuf);
	if (handle == NULL) {
		fprintf(stderr, "libpcap error opening device: %s\n", errbuf);
		return (1);
	}
	// Compile Filter
	if (pcap_compile(handle, &filter, "port 25565", 0, netmask) < 0) {
		fprintf(stderr, "libpcap error processing filter: %s\n", pcap_geterr(handle));
		return (1);
	}
	// Apply Filter
	if (pcap_setfilter(handle, &filter) < 0) {
		fprintf(stderr, "libpcap error applying filter: %s\n", pcap_geterr(handle));
		return (1);
	}
	
	// Init Sessions List
	session_init(slots);
	
	// Main Loop
	pcap_loop(handle, -1, got_packet, NULL);
	
	// Cleanup
	pcap_close(handle);
	session_delete();
	
	return 0;
}
