#pragma once

#include "picket.h"
#include "api/PicketAPI.h"

/** @file */

/** The Main Picket Implementation */
PicketImplementation imp;

/** Represents a plugin */
struct plugin {
	void* handler;
	char name[65];
};

struct plugin plugins[PICKET_MAX_HANDLERS];
int plugin_count;

/** Initalizes the implementation */
void imp_init();

/** Loads a plugin
 * @param plugin	The name of the plugin to load
 * @return 0 on success, -1 on error
 */
int load_plugin(char* plugin);
