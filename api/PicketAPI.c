#include <string.h>

#include "PicketAPI.h"
#include "event/EventServices.h"
#include "Console.h"

/** Sets the main picket interface
 * @param interface The PicketInterface to use as the main interface
 */
void setPicketImplementation(PicketImplementation* imp) {
	// event/EventServices.h
	subscribeToPicketEvent = imp->subscribeToPicketEvent;
	
	// Console.h
	runCommand = imp->runCommand;
	
	// PicketAPI.h
	picketScreen = imp->picketScreen;
}
