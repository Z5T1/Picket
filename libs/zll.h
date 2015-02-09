#pragma once

#include <stdlib.h>
#include <string.h>

/** @file */

/** This is the struct that stores the linked list.
 * @note The typedef LinkedList should be used for managing linked lists.
 */
struct LinkedList_s {
	/** The number of items the list can hold */
	int size;
	
	/** The index of the first free slot in list */		
	int first_free;
	
	/** The pointer to the list */	
	void** list;
	
	/** Whether the list should automatically grow in size 
	 * If true (nonzero) the list will automatically by auto_size if it
	 *   is overfilled
	 * If false (0) the list will not automatically grow. If it is
	 *   overfilled, it will retrun an error
	 */
	int auto_size;
};

typedef struct LinkedList_s* LinkedList;

/** Convienience macro for looping over a list.
 * Iterates over each value of the list, with i pointing to the current
 * index.
 * @param list list to iterate over
 * @param i the variable to store the current index
 */
#define ll_foreach(list,i) for((i) = 0; i < ll_getMaximumSize(list); (i)++)

/** Creates a new linked list with a constant (static) size. The
 * resulting linked list must be freed with ll_destroy().
 * @param size		The number of slots for this list
 * @return A new linked list
 */
LinkedList ll_create(int size);

/** Creates a new linked list with a variable (dynamic) size. The
 * resulting linked list must be freed with ll_destroy().
 * @return A new linked list
 */
LinkedList ll_createDynamic();

/** Creates a new linked list with a variable (dynamic) size. The
 * resulting linked list must be freed with ll_destroy().
 * @param growth_rate	The ammount by which to grow the list
 * @return A new linked list
 */
LinkedList ll_createDynamicCustom(int growth_rate);

/** Destroys (deallocates) a linked list
 * @param list		The list to be destroyed
 */
void ll_destroy(LinkedList list);

/** Gets the maximum size of a list
 * @param list		The list to get the size of
 * @return The maximum number of items list can hold
 */
static inline int ll_getMaximumSize(LinkedList list) {
	return list->size;
}

/** Gets the first free index of a list
 * @param list		The list to get the index of
 * @return The first free index of list, or -1 if list is full
 */
static inline int ll_getFirstFreeIndex(LinkedList list) {
	return list->first_free;
}

/** Fetches a pointer at an index
 * @param list		The list to fetch from
 * @param index		The index to fetch
 * @return The pointer at index, or NULL if index is unused
 */
static inline void* ll_get(LinkedList list, int index) {
	return list->list[index];
}

/** Removes an item from a list
 * @param list		The list to remove the item from
 * @param index		The index to remove
 */	
static inline void ll_remove(LinkedList list, int index) {
	list->list[index] = NULL;
}

/** Sets the item at an index to a specified value
 * @param list		The list to set the item in
 * @param index		The index to set
 * @param ptr		The pointer to set the index to
 * @return 0 on success, or -1 if the index is out of bounds
 */
int ll_set(LinkedList list, int index, void* ptr);

/** Adds a pointer to a list
 * @param list		The list to add to
 * @param ptr		The pointer to add
 * @return Index of pointer on success, -1 if list is full
 */
int ll_put(LinkedList list, void* ptr);

/** Grows a linked list by a given ammount
 * @param list		The list to grow
 * @param ammount	The ammount by which to grow the list
 */
void ll_grow(LinkedList list, int ammount);
