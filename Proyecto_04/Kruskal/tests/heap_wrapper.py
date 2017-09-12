import ctypes

import helpers

from base_wrapper import Edge, _Edge


# ctypes wrapper
heap_lib = helpers.get_lib('heap.so')


# TADs

class __Heap(ctypes.Structure):
    pass


_Heap = ctypes.POINTER(__Heap)


# heap_t heap_empty(unsigned int max_size)
heap_empty = helpers.maybe_implemented(
    heap_lib, 'heap_empty', _Heap, [ctypes.c_uint])


# heap_t heap_destroy(heap_t heap)
heap_destroy = helpers.maybe_implemented(
    heap_lib, 'heap_destroy', _Heap, [_Heap])


# heap_t heap_insert(heap_t heap, heap_elem_t elem)
heap_insert = helpers.maybe_implemented(
    heap_lib, 'heap_insert', _Heap, [_Heap, _Edge])


# heap_t heap_remove_minimum(heap_t heap)
heap_remove_minimum = helpers.maybe_implemented(
    heap_lib, 'heap_remove_minimum', _Heap, [_Heap])


# heap_elem_t heap_minimum(heap_t heap)
heap_minimum = helpers.maybe_implemented(
    heap_lib, 'heap_minimum', _Edge, [_Heap])


# bool heap_is_empty(heap_t heap)
heap_is_empty = helpers.maybe_implemented(
    heap_lib, 'heap_is_empty', ctypes.c_bool, [_Heap])


# bool heap_is_full(heap_t heap)
heap_is_full = helpers.maybe_implemented(
    heap_lib, 'heap_is_full', ctypes.c_bool, [_Heap])


# unsigned int heap_size(heap_t heap)
heap_size = helpers.maybe_implemented(
    heap_lib, 'heap_size', ctypes.c_uint, [_Heap])


# void heap_dump(heap_t heap, FILE *fd)
heap_dump = helpers.maybe_implemented(
    heap_lib, 'heap_dump', None, [_Heap, helpers.FILE_ptr])


# parcialito G
# void heap_sort(heap_elem_t *array, unsigned int size);
heap_sort = helpers.maybe_implemented(
    heap_lib, 'heap_sort', None, [ctypes.POINTER(_Edge), ctypes.c_uint])


# parcialito H
# bool array_is_heap(heap_elem_t *array, unsigned int size);
array_is_heap = helpers.maybe_implemented(
    heap_lib, 'array_is_heap', ctypes.c_bool,
    [ctypes.POINTER(_Edge), ctypes.c_uint])


def _array_from_seq(sequence):
    sequence = [None] + sequence
    return helpers.make_array_from_iterable(_Edge, sequence)


class Heap(object):

    def __init__(self, max_size):
        self._heap = heap_empty(max_size)

    def __del__(self):
        self._heap = heap_destroy(self._heap)

    def __len__(self):
        return heap_size(self._heap)

    def __nonzero__(self):
        return not heap_is_empty(self._heap)

    def is_full(self):
        return heap_is_full(self._heap)

    def insert(self, edge):
        self._heap = heap_insert(self._heap, edge)

    def minimum(self):
        _edge = heap_minimum(self._heap)
        return Edge.from_ptr(_edge)

    def remove_minimum(self):
        self._heap = heap_remove_minimum(self._heap)

    @staticmethod
    def sort(sequence):
        array = _array_from_seq(sequence)
        heap_sort(array, len(sequence))
        # transform back array to another sequence, drop the first elem
        return [Edge.from_ptr(p) for p in array if bool(p)]

    @staticmethod
    def is_heap(sequence):
        array = _array_from_seq(sequence)
        return array_is_heap(array, len(sequence))
