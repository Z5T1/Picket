#pragma once

#include <netinet/ip.h>

/** Type for an established session */
struct session {
	struct in_addr address;
	short port;
	char name[17];
};

/** A list storing all the currently established sessions */
struct session** sessions;

/** Initializes the sessions list. This must be called before any other
 * session related functions
 * @param slots		The maximum number of sessions
 */
void session_init(int slots);

/** Deletes the session list. Do not make any session calls after calling this */
void session_delete();

/** Adds a session the list of sessions
 * @param address	The address for the session
 * @param port		The port for the session
 * @param name		The name for the session (the player name). Must be unique
 * @return 0 on success, -1 on error
 */
int session_put(struct in_addr address, short port, char* name);

/** Removes a session from the list of sessions
 * @param address	The address of the session to get
 * @param port		The port of the session to get
 * @return 0 on success, -1 on error
 */
int session_remove_by_addr(struct in_addr address, short port);

/** Removes a session from the list of sessions
 * @param name		The name of the session to remove
 * @return 0 on success, -1 on error
 */
int session_remove_by_name(char* name);

/** Fetches a session from the list of sessions
 * @param address	The address of the session to get
 * @param port		The port of the session to get
 * @return The session fetched, or NULL if it doesn't exist
 */
struct session* session_get_by_addr(struct in_addr address, short port);

/** Fetches a session from the list of sessions
 * @param name		The name of the session to get
 * @return The session fetched, or NULL if it doesn't exist
 */
struct session* session_get_by_name(char* name);
