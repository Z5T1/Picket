#include <stdlib.h>
#include <string.h>

#include "sessions.h"
#include "zdef.h"

static int session_slots;

/** Initializes the sessions list. This must be called before any other
 * session related functions
 * @param slots		The maximum number of sessions
 */
void session_init(int slots) {
	connected_players = ll_createDynamicCustom(slots);
}

/** Deletes the session list. Do not make any session calls after calling this */
void session_delete() {
	ll_destroy(connected_players);
}

/** Adds a session the list of sessions
 * @param address	The address for the session
 * @param port		The port for the session
 * @param name		The name for the session (the player name). Must be unique
 * @param uuid		The UUID of the player
 * @return 0 on success, -1 on error
 */
int session_put(struct in_addr address, short port, char* name, char* uuid) {
	Player* player = new(Player);
	
	player->connection.ip = address;
	player->connection.port = port;
	strcpy(player->name, name);
	strcpy(player->uuid, uuid);
	
	ll_put(connected_players, player);
}

/** Removes a session from the list of sessions
 * @param address	The address of the session to get
 * @param port		The port of the session to get
 * @return 0 on success, -1 on error
 */
int session_remove_by_addr(struct in_addr address, short port) {
	int i;
	
	ll_foreach(connected_players, i) {
		Player* player = ll_get(connected_players, i);
		if (player != NULL && player->connection.ip.s_addr == address.s_addr && player->connection.port == port) {
			ll_remove(connected_players, i);
			return 0;
		}
	}
	
	return -1;
}

/** Removes a session from the list of sessions
 * @param name		The name of the session to remove
 * @return 0 on success, -1 on error
 */
int session_remove_by_name(char* name) {
	int i;
	
	ll_foreach(connected_players, i) {
		Player* player = ll_get(connected_players, i);
		if (player != NULL && strcmp(player->name, name) == 0) {
			ll_remove(connected_players, i);
			return 0;
		}
	}
	
	return -1;
}

/** Removes a session from the list of sessions
 * @param uuid		The uuid of the session to remove
 * @return 0 on success, -1 on error
 */
int session_remove_by_uuid(char* uuid) {
	int i;
	
	ll_foreach(connected_players, i) {
		Player* player = ll_get(connected_players, i);
		if (player != NULL && strcmp(player->uuid, uuid) == 0) {
			ll_remove(connected_players, i);
			return 0;
		}
	}
	
	return -1;
}

/** Fetches a session from the list of sessions
 * @param address	The address of the session to get
 * @param port		The port of the session to get
 * @return The session fetched, or NULL if it doesn't exist
 */
Player* session_get_by_addr(struct in_addr address, short port) {
	int i;
	
	ll_foreach(connected_players, i) {
		Player* player = ll_get(connected_players, i);
		if (player != NULL && player->connection.ip.s_addr == address.s_addr && player->connection.port == port) {
			return player;
		}
	}
	
	return NULL;
}

/** Fetches a session from the list of sessions
 * @param name		The name of the session to get
 * @return The session fetched, or NULL if it doesn't exist
 */
Player* session_get_by_name(char* name) {
	int i;
	
	ll_foreach(connected_players, i) {
		Player* player = ll_get(connected_players, i);
		if (player != NULL && strcmp(player->name, name) == 0) {
			return player;
		}
	}
	
	return NULL;
}

/** Fetches a session from the list of sessions
 * @param uuid		The uuid of the session to get
 * @return The session fetched, or NULL if it doesn't exist
 */
Player* session_get_by_uuid(char* uuid) {
	int i;
	
	ll_foreach(connected_players, i) {
		Player* player = ll_get(connected_players, i);
		if (player != NULL && strcmp(player->uuid, uuid) == 0) {
			return player;
		}
	}
	
	return NULL;
}
