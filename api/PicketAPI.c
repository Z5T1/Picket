#include <string.h>

#include "PicketAPI.h"
#include "event/EventServices.h"

/** Sets the main picket interface
 * @param interface The PicketInterface to use as the main interface
 */
void setPicketImplementation(PicketImplementation* imp) {
	// EventServices.h
	subscribeToPicketEvent = imp->subscribeToPicketEvent;
}
