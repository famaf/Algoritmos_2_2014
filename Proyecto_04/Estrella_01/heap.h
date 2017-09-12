#ifndef _HEAP_H
#define _HEAP_H


#include <stdbool.h>
#include "graph.h"

/* Heap element abstract data type */

typedef edge_t heap_elem_t;

#define heap_elem_lt edge_lt
#define heap_elem_lte edge_lte
#define heap_elem_copy edge_copy
#define heap_elem_destroy edge_destroy
#define heap_elem_dump edge_dump

/* Heap abstract data type */

typedef struct _heap_t *heap_t;

/* A (min-)heap (http://en.wikipedia.org/wiki/Heap_%28data_structure%29).
*
* A heap is a specialized tree-based data structure that satisfies the heap
* property: if B is a child node of A, then A <= B.
*
*/


heap_t heap_empty(unsigned int max_size);
/*
* Return a newly created heap that can hold up to 'max_size' elements.
*
* The resources allocated for the heap returned from this call must be freed
* by calling 'heap_destroy' once the result is no longer needed.
*
* POST: the result is not NULL and heap_is_empty(result) holds.
*
*/


heap_t heap_destroy(heap_t heap);
/*
* Free all the resources used by 'heap'.
*
* PRE: 'heap' must be not NULL, and must have been returned by a previous
* call to 'heap_empty'.
*/


heap_t heap_insert(heap_t heap, heap_elem_t elem);
/*
* Insert the element 'elem' in the heap 'heap'.
* The heap owns 'elem' after this, consider passing a copy if you
* plan to use 'elem' somewhere else.
*
* PRE: 'heap' must be not NULL and the heap should not be full.
*
* POST: the size of the resulting heap is the same as the size of 'heap'
* plus one, and it as the same elements as the given 'heap' plus 'elem'.
*/


heap_t heap_remove_minimum(heap_t heap);
/*
* Remove and destroy the minumum value in the heap 'heap'.
*
* PRE: 'heap' must be not NULL and 'heap' can not be empty.
*
* POST: the size of the resulting heap is the same as the size of 'heap'
* minus one, and it as the same elements as the given 'heap' but the minimum.
*/


heap_elem_t heap_minimum(heap_t heap);
/*
* Return a copy of the minimum element of the heap 'heap'.
*
* PRE: 'heap' must be not NULL and 'heap' can not be empty.
*
* POST: the result is the minimum value of the heap 'heap'.
*/


bool heap_is_empty(heap_t heap);
/*
* Return whether 'heap' is an empty heap.
*
* PRE: 'heap' must not be NULL.
*/


bool heap_is_full(heap_t heap);
/*
* Return whether 'heap' is full.
*
* PRE: 'heap' must not be NULL.
*/


unsigned int heap_size(heap_t heap);
/*
* Return the size of the heap 'heap'.
*
* PRE: 'heap' must not be NULL.
*/


void heap_dump(heap_t heap, FILE * fd);
/*
* Dump the heap 'heap' to the given file descriptor.
*
* PRE: 'heap' must not be NULL, and 'fd' must be a valid file descriptor.
*/


#endif
