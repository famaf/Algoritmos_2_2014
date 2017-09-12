#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H


#include <stdbool.h>
#include "graph.h"
#include "heap.h"

typedef heap_t priority_queue_t;

/* The priority_queue (http://en.wikipedia.org/wiki/Priority_queue).
*
* A priority_queue is an abstract data type which is like a regular queue
* or stack data structure, but additionally, each element is associated
* with a "priority".
*/


typedef edge_t priority_queue_elem_t;

/* The type of the elements to store in a priority_queue */


priority_queue_t priority_queue_empty(unsigned int max_size);
/*
* Return a new empty priority queue.
* It can hold up to max_size elems.
*
* The caller must call priority_queue_destroy when done using the resulting
* queue, so the resources allocated by this call are freed.
*
* POST: the result is a well-defined priority queue.
*/


priority_queue_t priority_queue_destroy(priority_queue_t pq);
/*
* Free the resources allocated for the given priority_queue,
* and set it to NULL.
*
* PRE: 'pq' must be a well-defined priority queue.
*/


priority_queue_t priority_queue_enqueue(priority_queue_t pq,
                                        priority_queue_elem_t elem);
/*
* Enqueue the given element, according to its priority.
* The queue owns 'elem' after this, consider passing a copy if you
* plan to use 'elem' somewhere else.
*
* PRE: 'pq' must a well-defined priority queue, 'elem' must also be a
* well-defined priority queue element. The given queue should not be full.
*
* POST: the size of the resulting queue is the same as the size of 'pq'
* plus one, and it as the same elements as the given 'pq' plus 'elem'.
*/


priority_queue_elem_t priority_queue_first(priority_queue_t pq);
/*
* Return a copy of the minimum element (according to the priority of the
* elements) of the queue 'pq'.
* This means that the caller owns the resources used by the result, and must
* destroy it once is no longer used.
*
* PRE: 'pq' must be a well-defined priority queue and can not be empty.
*
* POST: the result is the minimum value of the queue 'pq'.
*/


priority_queue_t priority_queue_dequeue(priority_queue_t pq);
/*
* Remove and destroy the minimum value in the queue 'pq'.
*
* PRE: 'pq' must be a well-defined priority queue and can not be empty.
*
* POST: the size of the resulting queue is the same as the size of 'pq'
* minus one, and it as the same elements as the given 'pq' but the minimum.
*/


bool priority_queue_is_empty(priority_queue_t pq);
/*
* Return whether 'pq' is an empty queue.
*
* PRE: 'pq' must be a well-defined priority queue.
*/


bool priority_queue_is_full(priority_queue_t pq);
/*
* Return whether 'pq' is full.
*
* PRE: 'pq' must be a well-defined priority queue.
*/


unsigned int priority_queue_size(priority_queue_t pq);
/*
* Return the current size of the priority queue 'pq'.
*
* PRE: 'pq' must be a well-defined priority queue.
*/


void priority_queue_dump(priority_queue_t pq, FILE * fd);
/*
* Dump the priority queue 'pq' to the given file descriptor.
*
* PRE: 'pq' must be a well-defined priority queue, and 'fd' must be a
* valid file descriptor.
*/


#endif
