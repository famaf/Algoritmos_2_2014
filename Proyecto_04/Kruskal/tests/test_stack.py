from unittest import TestCase

from base_wrapper import new_edge
from stack_wrapper import Stack


class StackTestCase(TestCase):

    gen_seq = xrange

    def setUp(self):
        super(StackTestCase, self).setUp()
        self.instance = Stack()

    def add_elem(self, elem):
        self.instance.push(elem)

    def add_from_sequence(self, sequence):
        for i in sequence:
            self.add_elem(new_edge(i))

    def get_elem(self):
        elem = self.instance.top()
        self.addCleanup(elem.destroy)
        return elem

    def remove_elem(self):
        self.instance.pop()

    def test_empty(self):
        self.assertEqual(bool(self.instance), False)

    def test_push(self):
        self.add_elem(new_edge())
        self.assertEqual(bool(self.instance), True)

    def test_push_several_and_pop_one(self):
        self.add_elem(new_edge())
        self.assertEqual(bool(self.instance), True)

        self.add_elem(new_edge())
        self.assertEqual(bool(self.instance), True)

        self.remove_elem()
        self.assertEqual(bool(self.instance), True)

    def test_push_and_pop_all(self):
        seq = self.gen_seq(100)
        edges = []
        for i in seq:
            e = new_edge(i)
            self.add_elem(e)
            edges.append(e)

        self.assertEqual(bool(self.instance), True)

        # remove them all, assert order and identity
        for i in seq:
            self.assertEqual(self.get_elem(), edges.pop())
            self.remove_elem()

        self.assertEqual(bool(self.instance), False)

    def test_push_twice(self):
        e = new_edge()
        self.add_elem(e)
        f = e.copy()
        assert e == f
        self.add_elem(f)

        self.assertEqual(self.get_elem(), f)
        self.remove_elem()

        self.assertEqual(self.get_elem(), e)
        self.remove_elem()

        self.assertEqual(bool(self.instance), False)

    def test_top_returns_a_copy(self):
        self.add_elem(new_edge())

        elem1 = self.get_elem()
        elem2 = self.get_elem()

        self.assertNotEqual(elem1.c_address, elem2.c_address)
