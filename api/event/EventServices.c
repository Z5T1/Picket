#include "EventServices.h"

#include "../../packets/connect_packet.h"
#include "../../packets/chat_packet.h"

/** Subscribes to a certain event, making it so a function is called
 * every time a given event is fired
 * @param event The event to listen for
 * @param function The function to call
 */
void subscribeToPicketEvent(PicketEvent event, void* function) {
	switch(event) {
	case PLAYER_CONNECT_EVENT:
		connect_packet_add_handler(function);
		break;
	case PLAYER_CHAT_EVENT:
		chat_packet_add_handler(function);
		break;
	}
}
