#pragma once

/** Allocates a new structure. The resulting memory must be freed by the
 * caller.
 * @param type		The datatype to allocate space for
 * @return			The allocated memory
 */
#define new(type) malloc(sizeof(type));

/** Allocates an array of new structures. The resulting memory must be
 * freed by the caller.
 * @param type		The datatype to allocate space for
 * @param count		The number of items to allocate memory for
 * @return			The allocated memory
 */
#define newArray(type,count) malloc(sizeof(type) * (count));
