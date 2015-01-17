#include <PicketAPI.h>

#include <event/EventServices.h>


/** Subscribes to a certain event, making it so a function is called
 * every time a given event is fired
 * @param event The event to listen for
 * @param function The function to call
 */
void subscribeToPicketEvent(PicketEvent event, void* function) {
	switch(event) {
	case PLAYER_CONNECT_EVENT:
		picketInterface.connect_packet_add_handler(function);
		break;
	case PLAYER_CHAT_EVENT:
		picketInterface.chat_packet_add_handler(function);
		break;
	}
}
