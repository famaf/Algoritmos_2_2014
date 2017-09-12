from unittest import TestCase

from helpers import IndentMixinTestCase


class MainIndentTestCase(TestCase, IndentMixinTestCase):
    filenames = ('main.c',)


class PriorityQueueIndentTestCase(TestCase, IndentMixinTestCase):
    filenames = ('priority_queue.c', 'priority_queue.h')


class HeapIndentTestCase(TestCase, IndentMixinTestCase):
    filenames = ('heap.c', 'heap.h')


class UnionFindIndentTestCase(TestCase, IndentMixinTestCase):
    filenames = ('union_find.c', 'union_find.h')


class StackIndentTestCase(TestCase, IndentMixinTestCase):
    filenames = ('stack.c', 'stack.h')
