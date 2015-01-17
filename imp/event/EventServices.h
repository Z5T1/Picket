#pragma once

/** @file */

/** An enumeration of all possible Picket events */
typedef enum {
	PLAYER_CONNECT_EVENT,
	PLAYER_CHAT_EVENT
} PicketEvent;

#ifdef __cplusplus
extern "C" {
#endif

/** Subscribes to a certain event, making it so a function is called
 * every time a given event is fired
 * @param event The event to listen for
 * @param function The function to call
 */
void subscribeToPicketEvent(PicketEvent event, void* function);

#ifdef __cplusplus
}
#endif
