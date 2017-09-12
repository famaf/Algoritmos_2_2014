#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "priority_queue.h"
#include "graph.h"
#include "heap.h"


priority_queue_t priority_queue_empty(unsigned int max_size) {
    priority_queue_t pq = heap_empty(max_size);

    return (pq);
}


priority_queue_t priority_queue_destroy(priority_queue_t pq) {
    pq = heap_destroy(pq);

    return (pq);
}


priority_queue_t priority_queue_enqueue(priority_queue_t pq,
                                        priority_queue_elem_t elem) {
    pq = heap_insert(pq, elem);

    return (pq);
}


priority_queue_elem_t priority_queue_first(priority_queue_t pq) {
    priority_queue_elem_t result = heap_minimum(pq);

    return (result);
}


priority_queue_t priority_queue_dequeue(priority_queue_t pq) {
    pq = heap_remove_minimum(pq);

    return (pq);
}


bool priority_queue_is_empty(priority_queue_t pq) {
    bool result = heap_is_empty(pq);

    return (result);
}


bool priority_queue_is_full(priority_queue_t pq) {
    bool result = heap_is_full(pq);

    return (result);
}


unsigned int priority_queue_size(priority_queue_t pq) {
    unsigned int result = heap_size(pq);

    return (result);
}


void priority_queue_dump(priority_queue_t pq, FILE * fd) {
    heap_dump(pq, fd);
}
