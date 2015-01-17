#pragma once

/** @file */

/** The Interface for connecting with the picket server */
/* IMPORTANT NOTE TO DEVELOPERS:
 * When adding to this struct, make sure to add new items AFTER all the
 * pre-existing ones. Failure to do this will result in breaking every
 * single Picket plugin in existence.
 */
typedef struct {
	void* subscribeToPicketEvent; // From EventServices.h
} PicketImplementation;

#ifdef __cplusplus
extern "C" {
#endif

/** Sets the main picket interface
 * @param interface The PicketInterface to use as the main interface
 */
void setPicketImplementation(PicketImplementation* imp);

#ifdef __cplusplus
}
#endif
