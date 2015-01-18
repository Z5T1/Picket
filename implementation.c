#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "implementation.h"

#include "imp/Console.h"
#include "imp/event/EventServices.h"

/** Initalizes the implementation */
void imp_init() {
	plugin_count = 0;
	memset(plugins, 0, sizeof(void*) * PICKET_MAX_HANDLERS);
	
	imp.subscribeToPicketEvent = subscribeToPicketEvent;
	imp.runCommand = runCommand;
	imp.picketScreen = picketScreen;
}

/** Loads a plugin
 * @param plugin	The name of the plugin to load
 * @return 0 on success, -1 on error
 */
int load_plugin(char* plugin) {
	// Variables
	void* handler;
	char* plugin_path;
	
	// Function Pointers
	void (*setImp)(PicketImplementation* imp);
	void (*onLoad)();
	
	plugin_path = malloc(strlen(plugin) + 12);
	sprintf(plugin_path, "plugins/%s.so", plugin);
	
	// Load the Shared Object
	handler = dlopen(plugin_path, RTLD_LAZY);
	if (handler == NULL) {
		fprintf(stderr, "Error loading plugin %s: %s\n", plugin, dlerror());
		return -1;
	}
	
	// Set the Implementation
	setImp = dlsym(handler, "setPicketImplementation");
	if (setImp == NULL) {
		fprintf(stderr, "Error setting plugin implementation %s: %s\n\tDid you link against libpicket?\n", plugin, dlerror());
		return -1;
	}
	setImp(&imp);
	
	// Call the Plugin's onLoad() function
	onLoad = dlsym(handler, "onLoad");
	if (setImp == NULL) {
		fprintf(stderr, "Error starting plugin %s: %s\n\tCould not find function onLoad\n", plugin, dlerror());
		return -1;
	}
	printf("Loading %s\n", plugin);
	onLoad();
	
	// Add Plugin handler to the list
	plugins[plugin_count].handler = handler;
	strcpy(plugins[plugin_count].name, plugin);
	plugin_count++;
	
	// Cleanup
	free(plugin_path);
	
}
