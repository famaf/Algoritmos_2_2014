from unittest import TestCase

from base_wrapper import new_edge
from heap_wrapper import Heap

MAX_SIZE = 20


class HeapTestCase(TestCase):

    klass = Heap

    def setUp(self):
        super(HeapTestCase, self).setUp()
        self.instance = self.klass(MAX_SIZE)

    def gen_seq(self, size, ascending=True):
        if ascending:
            return xrange(1, size + 1)
        else:
            return xrange(size, 0, -1)

    def add_elem(self, elem):
        self.instance.insert(elem)

    def add_from_sequence(self, sequence):
        for i in sequence:
            assert 0 < i
            assert i <= MAX_SIZE
            self.add_elem(new_edge(i))

    def get_elem(self):
        elem = self.instance.minimum()
        self.addCleanup(elem.destroy)
        return elem

    def remove_elem(self):
        self.instance.remove_minimum()

    def assert_emptiness(self, expected_size):
        self.assertEqual(len(self.instance), expected_size)
        self.assertEqual(bool(self.instance), expected_size != 0)
        self.assertEqual(self.instance.is_full(), expected_size == MAX_SIZE)

    def test_empty(self):
        self.assert_emptiness(0)

    def test_insert(self):
        self.add_elem(new_edge())
        self.assert_emptiness(1)

    def test_insert_max_size(self):
        seq = self.gen_seq(MAX_SIZE)
        for i in seq:
            self.add_elem(new_edge(i))
        self.assert_emptiness(MAX_SIZE)

    def test_insert_several_and_remove_one(self):
        self.add_elem(new_edge())
        self.assert_emptiness(1)

        self.add_elem(new_edge())
        self.assert_emptiness(2)

        self.remove_elem()
        self.assert_emptiness(1)

    def _test_insert_and_remove_all(self, seq):
        self.assert_emptiness(0)

        edges = []
        for j, i in enumerate(seq):
            e = new_edge(i)
            self.add_elem(e)
            edges.append(e)
            self.assert_emptiness(j + 1)

        # remove them all, assert order and identity
        edges.sort(reverse=True)
        size = len(seq)
        for j in xrange(size, 0, -1):
            e = edges.pop()
            self.assertEqual(self.get_elem(), e)
            self.remove_elem()
            self.assert_emptiness(j - 1)

        self.assert_emptiness(0)

    def test_insert_ascending_and_remove_all(self):
        seq = self.gen_seq(MAX_SIZE, ascending=True)
        self._test_insert_and_remove_all(seq)

    def test_insert_descending_and_remove_all(self):
        seq = self.gen_seq(MAX_SIZE, ascending=False)
        self._test_insert_and_remove_all(seq)

    def test_insert_out_of_order_and_remove_all(self):
        # insert values mixing low and high prio
        seq = [10000, 1, 150, 750, 3, 10001, 50, 100, 1583, 6589, 65536]
        self._test_insert_and_remove_all(seq)

    def test_insert_twice(self):
        e = new_edge()
        self.add_elem(e)
        f = e.copy()
        assert e == f
        self.add_elem(f)

        self.assertEqual(self.get_elem(), f)
        self.remove_elem()

        self.assertEqual(self.get_elem(), e)
        self.remove_elem()

        self.assert_emptiness(0)

    def test_minimum_returns_a_copy(self):
        self.add_elem(new_edge())

        elem1 = self.get_elem()
        elem2 = self.get_elem()

        self.assertNotEqual(elem1.c_address, elem2.c_address)
