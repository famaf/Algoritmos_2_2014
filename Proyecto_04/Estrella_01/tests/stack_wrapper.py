import ctypes

import helpers

from base_wrapper import Edge, _Edge


# ctypes wrapper
stack_lib = helpers.get_lib('stack.so')


# TADs

class __Stack(ctypes.Structure):
    pass


_Stack = ctypes.POINTER(__Stack)


# Wrappers

# stack_t stack_empty(void)
stack_empty = helpers.maybe_implemented(
    stack_lib, 'stack_empty', _Stack, [])


# stack_t stack_destroy(stack_t stack)
stack_destroy = helpers.maybe_implemented(
    stack_lib, 'stack_destroy', _Stack, [_Stack])


# stack_t stack_push(stack_t stack, stack_elem_t elem)
stack_push = helpers.maybe_implemented(
    stack_lib, 'stack_push', _Stack, [_Stack, _Edge])


# stack_t stack_pop(stack_t stack)
stack_pop = helpers.maybe_implemented(
    stack_lib, 'stack_pop', _Stack, [_Stack])


# stack_elem_t stack_top(stack_t stack)
stack_top = helpers.maybe_implemented(
    stack_lib, 'stack_top', _Edge, [_Stack])


# bool stack_is_empty(stack_t stack)
stack_is_empty = helpers.maybe_implemented(
    stack_lib, 'stack_is_empty', ctypes.c_bool, [_Stack])


class Stack(object):

    def __init__(self):
        self._stack = stack_empty()

    def __del__(self):
        self._stack = stack_destroy(self._stack)

    def __nonzero__(self):
        return not stack_is_empty(self._stack)

    def push(self, edge):
        self._stack = stack_push(self._stack, edge)

    def pop(self):
        self._stack = stack_pop(self._stack)

    def top(self):
        _edge = stack_top(self._stack)
        return Edge.from_ptr(_edge)
