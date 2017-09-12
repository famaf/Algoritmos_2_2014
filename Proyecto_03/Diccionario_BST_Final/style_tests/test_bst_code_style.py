from unittest import TestCase

from helpers import IndentMixinTestCase


class BSTIndentTestCase(TestCase, IndentMixinTestCase):
    filenames = ('bst.c', 'bst.h')
