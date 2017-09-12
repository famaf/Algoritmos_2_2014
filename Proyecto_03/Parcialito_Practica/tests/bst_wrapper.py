import ctypes

import base_wrapper
import helpers
import list_wrapper


# ctypes wrapper
bst_lib = helpers.get_lib('bst.so')


# TADs

class __BST(ctypes.Structure):
    pass
_BST = ctypes.POINTER(__BST)


# bst_t bst_empty(void);
bst_empty = helpers.maybe_implemented(bst_lib, 'bst_empty', _BST, [])


# bst_t bst_destroy(bst_t bst);
bst_destroy = helpers.maybe_implemented(bst_lib, 'bst_destroy', _BST, [_BST])


# unsigned int bst_length(bst_t bst);
bst_length = helpers.maybe_implemented(
    bst_lib, 'bst_length', ctypes.c_uint, [_BST])


# bool bst_is_equal(bst_t bst, bst_t other);
bst_is_equal = helpers.maybe_implemented(
    bst_lib, 'bst_is_equal', ctypes.c_bool, [_BST, _BST])


# data_t bst_search(bst_t bst, index_t index);
bst_search = helpers.maybe_implemented(
    bst_lib, 'bst_search', base_wrapper._Data, [_BST, base_wrapper._Index])


# bst_t bst_add(bst_t bst, index_t index, data_t data);
bst_add = helpers.maybe_implemented(
    bst_lib, 'bst_add', _BST, [_BST, base_wrapper._Index, base_wrapper._Data])


# bst_t bst_remove(bst_t bst, index_t index);
bst_remove = helpers.maybe_implemented(
    bst_lib, 'bst_remove', _BST, [_BST, base_wrapper._Index])


# bst_t bst_copy(bst_t bst);
bst_copy = helpers.maybe_implemented(bst_lib, 'bst_copy', _BST, [_BST])


# list_t bst_to_list(bst_t bst);
bst_to_list = helpers.maybe_implemented(
    bst_lib, 'bst_to_list', list_wrapper._List, [_BST, list_wrapper._List])


class BinarySearchTree(object):

    def __init__(self):
        self._bst = bst_empty()

    def __del__(self):
        self._bst = bst_destroy(self._bst)

    def __contains__(self, i):
        i = base_wrapper.index_from_string(i)
        result = bool(bst_search(self._bst, i))
        base_wrapper.index_destroy(i)
        return result

    def __iter__(self):
        raise NotImplementedError()

    def __len__(self):
        return bst_length(self._bst)

    def __eq__(self, other):
        return (isinstance(other, BinarySearchTree) and
                bst_is_equal(self._bst, other._bst))

    def __ne__(self, other):
        return not (self == other)

    def __str__(self):
        return str(self.to_list())

    def __repr__(self):
        return repr(self.to_list())

    def add(self, i, d):
        assert i not in self
        i = base_wrapper.index_from_string(i)
        d = base_wrapper.data_from_string(d)
        self._bst = bst_add(self._bst, i, d)

    def copy(self):
        result = BinarySearchTree()
        bst_destroy(result._bst)
        result._bst = bst_copy(self._bst)
        return result

    def remove(self, i):
        i = base_wrapper.index_from_string(i)
        self._bst = bst_remove(self._bst, i)
        base_wrapper.index_destroy(i)

    def search(self, i):
        i = base_wrapper.index_from_string(i)
        d = bst_search(self._bst, i)
        base_wrapper.index_destroy(i)
        if d:
            return base_wrapper.data_to_string(d)

    def to_list(self):
        linkedlist = list_wrapper.List()
        linkedlist._l = bst_to_list(self._bst, linkedlist._l)
        return linkedlist.to_list()
