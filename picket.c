#include <stdio.h>
#include <string.h>
#include <pcap.h>

#include "picket.h"
#include "sessions.h"
#include "net.h"

int main(int argc, char** argv) {
	
	/***** Variable Declaration *****/
	// Pcap Variables
	pcap_t* handle;
	char errbuf[PCAP_ERRBUF_SIZE];
	bpf_u_int32 netmask;
	bpf_u_int32 netaddr;
	struct bpf_program filter;
	struct pcap_pkthdr packet_header;
	const u_char* packet_data;
	
	// Option Variables
	int slots = 20;
	int port = 25565;
	char* dev = "lo";
	
	// Misc
	int i;
	
	/***** Parse Arguments *****/
	for (i = 0; i < argc; i++) {
		// Help
		if (strcmp(argv[i], "--help") == 0) {
			fprintf(stderr,
					"--help             Display this message\n"
					"-i <interface>     Specifies the device to listen on (default lo)\n"
					"-p <port>          Specifies the port to listen on\n"
					"-x <players>       Specifies the maximum number of players that can connect\n");
			return 0;
		}
		// Interface
		if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--interface") == 0) {
			i++;
			if (i < argc) {
				dev = argv[i];
			}
			else {
				fprintf(stderr, "Error:\t-i - no interface specified\n");
				return 2;
			}
		}
		// Port
		if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0) {
			i++;
			if (i < argc) {
				port = atoi(argv[i]);
			}
			else {
				fprintf(stderr, "Error:\t-p - no port specified\n");
				return 2;
			}
		}
		// Max Player Slots
		if (strcmp(argv[i], "-x") == 0 || strcmp(argv[i], "--max-players") == 0) {
			i++;
			if (i < argc) {
				slots = atoi(argv[i]);
			}
			else {
				fprintf(stderr, "Error:\t-x no player cound specified\n");
				return 2;
			}
		}
	}
	
	/***** Device Initialiazation *****/
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
