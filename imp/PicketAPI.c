#include <string.h>

#include "PicketAPI.h"

/** Sets the main picket interface
 * @param interface The PicketInterface to use as the main interface
 */
void setPicketInterface(PicketInterface* interface) {
	memcpy(&picketInterface, interface, sizeof(PicketInterface));
}
