#include <stdlib.h>
#include <string.h>

#include "sessions.h"

/** Initializes the sessions list. This must be called before any other
 * session related functions
 * @param slots		The maximum number of sessions
 */
void session_init(int slots) {
	sessions = malloc(sizeof(struct session*) * slots);
	memset(sessions, 0, sizeof(struct session*) * slots);
	session_slots = slots;
}

/** Deletes the session list. Do not make any session calls after calling this */
void session_delete() {
	free(sessions);
}

/** Adds a session the list of sessions
 * @param address	The address for the session
 * @param port		The port for the session
 * @param name		The name for the session (the player name). Must be unique
 * @return 0 on success, -1 on error
 */
int session_put(struct in_addr address, short port, char* name) {
	int i;
	
	for (i = 0; i < session_slots; i++) {
		if (sessions[i] == NULL) {
			sessions[i] = malloc(sizeof(struct session));
			sessions[i]->address = address;
			sessions[i]->port = port;
			strcpy(sessions[i]->name, name);
			return 0;
		}
	}
	
	return -1;
}

/** Removes a session from the list of sessions
 * @param address	The address of the session to get
 * @param port		The port of the session to get
 * @return 0 on success, -1 on error
 */
int session_remove_by_addr(struct in_addr address, short port) {
	int i;
	
	for (i = 0; i < session_slots; i++) {
		if (sessions[i] != NULL && sessions[i]->address.s_addr == address.s_addr && sessions[i]->port == port) {
			free(sessions[i]);
			sessions[i] = NULL;
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
	
	for (i = 0; i < session_slots; i++) {
		if (sessions[i] != NULL && strcmp(sessions[i]->name, name) == 0) {
			free(sessions[i]);
			sessions[i] = NULL;
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
struct session* session_get_by_addr(struct in_addr address, short port) {
	int i;
	
	for (i = 0; i < session_slots; i++) {
		if (sessions[i] != NULL && sessions[i]->address.s_addr == address.s_addr && sessions[i]->port == port) {
			return sessions[i];
		}
	}
	
	return NULL;
}

/** Fetches a session from the list of sessions
 * @param name		The name of the session to get
 * @return The session fetched, or NULL if it doesn't exist
 */
struct session* session_get_by_name(char* name) {
	int i;
	
	for (i = 0; i < session_slots; i++) {
		if (sessions[i] != NULL && strcmp(sessions[i]->name, name) == 0) {
			return sessions[i];
		}
	}
	
	return NULL;
}
