import ctypes

import helpers

from base_wrapper import Edge, _Edge


# ctypes wrapper
pq_lib = helpers.get_lib('priority_queue.so')


# TADs

class __PriorityQueue(ctypes.Structure):
    pass


_PriorityQueue = ctypes.POINTER(__PriorityQueue)


# Wrappers


# priority_queue_t priority_queue_empty(unsigned int max_size)
pq_empty = helpers.maybe_implemented(
    pq_lib, 'priority_queue_empty', _PriorityQueue, [ctypes.c_uint])


# priority_queue_t priority_queue_destroy(priority_queue_t pq)
pq_destroy = helpers.maybe_implemented(
    pq_lib, 'priority_queue_destroy', _PriorityQueue, [_PriorityQueue])


# priority_queue_t priority_queue_enqueue(priority_queue_t pq,
#                                         priority_queue_elem_t elem)
pq_enqueue = helpers.maybe_implemented(
    pq_lib, 'priority_queue_enqueue', _PriorityQueue,
    [_PriorityQueue, _Edge])


# priority_queue_elem_t priority_queue_first(priority_queue_t pq)
pq_first = helpers.maybe_implemented(
    pq_lib, 'priority_queue_first', _Edge, [_PriorityQueue])


# priority_queue_t priority_queue_dequeue(priority_queue_t pq)
pq_dequeue = helpers.maybe_implemented(
    pq_lib, 'priority_queue_dequeue', _PriorityQueue, [_PriorityQueue])


# bool priority_queue_is_empty(priority_queue_t pq)
pq_is_empty = helpers.maybe_implemented(
    pq_lib, 'priority_queue_is_empty', ctypes.c_bool, [_PriorityQueue])


# bool priority_queue_is_full(priority_queue_t pq)
pq_is_full = helpers.maybe_implemented(
    pq_lib, 'priority_queue_is_full', ctypes.c_bool, [_PriorityQueue])


# unsigned int priority_queue_size(priority_queue_t pq)
pq_size = helpers.maybe_implemented(
    pq_lib, 'priority_queue_size', ctypes.c_uint, [_PriorityQueue])


# void priority_queue_dump(priority_queue_t pq, FILE *fd)
pq_dump = helpers.maybe_implemented(
    pq_lib, 'priority_queue_dump', None, [_PriorityQueue, helpers.FILE_ptr])


class PriorityQueue(object):

    def __init__(self, max_size):
        self._pq = pq_empty(max_size)

    def __del__(self):
        self._pq = pq_destroy(self._pq)

    def __len__(self):
        return pq_size(self._pq)

    def __nonzero__(self):
        return not pq_is_empty(self._pq)

    def is_full(self):
        return pq_is_full(self._pq)

    def enqueue(self, edge):
        self._pq = pq_enqueue(self._pq, edge)

    def dequeue(self):
        self._pq = pq_dequeue(self._pq)

    def first(self):
        _edge = pq_first(self._pq)
        return Edge.from_ptr(_edge)
