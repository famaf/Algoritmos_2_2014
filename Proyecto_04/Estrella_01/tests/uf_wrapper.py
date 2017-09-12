import ctypes

import helpers


# ctypes wrapper
uf_lib = helpers.get_lib('union_find.so')


# TADs

class __UnionFind(ctypes.Structure):
    pass


_UnionFind = ctypes.POINTER(__UnionFind)


# Wrappers

# union_find_t union_find_create(unsigned int max_size)
uf_create = helpers.maybe_implemented(
    uf_lib, 'union_find_create', _UnionFind, [ctypes.c_uint])


# union_find_t union_find_destroy(union_find_t uf)
uf_destroy = helpers.maybe_implemented(
    uf_lib, 'union_find_destroy', _UnionFind, [_UnionFind])


# union_find_t union_find_push(union_find_t uf, union_find_elem_t elem)
uf_push = helpers.maybe_implemented(
    uf_lib, 'union_find_push', _UnionFind, [_UnionFind, ctypes.c_uint])


# union_find_t union_find_union(union_find_t uf,
#                               union_find_class_t class1,
#                               union_find_class_t class2)
uf_union = helpers.maybe_implemented(
    uf_lib, 'union_find_union', _UnionFind,
    [_UnionFind, ctypes.c_uint, ctypes.c_uint])


# union_find_class_t union_find_find(union_find_t uf, union_find_elem_t elem)
uf_find = helpers.maybe_implemented(
    uf_lib, 'union_find_find', ctypes.c_uint, [_UnionFind, ctypes.c_uint])


# unsigned int union_find_class_count(union_find_t uf)
uf_class_count = helpers.maybe_implemented(
    uf_lib, 'union_find_class_count', ctypes.c_uint, [_UnionFind])


class UnionFind(object):

    def __init__(self, max_size):
        self._uf = uf_create(max_size)

    def __del__(self):
        self._uf = uf_destroy(self._uf)

    def __len__(self):
        return uf_class_count(self._uf)

    def add_class(self, uf_class):
        self._uf = uf_push(self._uf, uf_class)

    def find_class(self, elem):
        return uf_find(self._uf, elem)

    def union(self, uf_class1, uf_class2):
        self._uf = uf_union(self._uf, uf_class1, uf_class2)
