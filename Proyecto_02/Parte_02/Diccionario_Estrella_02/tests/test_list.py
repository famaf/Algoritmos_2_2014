from unittest import TestCase

from helpers import skip_if_not_implemented
from list_wrapper import List

testdata = [
    ('a', 'b'), ('foo', 'bar'), ('perro', 'zaraza'),
]


class BaseTestCase(TestCase):

    list_class = List

    def setUp(self):
        super(BaseTestCase, self).setUp()
        self.instance = self.list_class()

    def add_from_sequence(self, sequence=None):
        if sequence is None:
            sequence = testdata
        for i, d in sequence:
            self.instance.append(i, d)

    def remove_from_position(self, position):
        self.add_from_sequence()
        assert len(self.instance) == len(testdata)

        i = testdata[position][0]
        self.instance.remove(i)

        self.assertEqual(len(self.instance), len(testdata) - 1)
        # and all the other stuff is reachable
        for k, v in dict(testdata).iteritems():
            if k != i:
                self.assertEqual(self.instance.search(k), v)
            else:
                self.assertIsNone(self.instance.search(i))


class ListTestCase(BaseTestCase):

    def test_empty(self):
        self.assertEqual(len(self.instance), 0)

    def test_search_on_empty(self):
        self.assertIsNone(self.instance.search('zaraza'))

    def test_search_does_not_exist(self):
        self.add_from_sequence()
        assert 'zaraza' not in dict(testdata)
        self.assertIsNone(self.instance.search('zaraza'))

    def test_search_exists(self):
        self.add_from_sequence()
        for k, v in dict(testdata).iteritems():
            self.assertEqual(self.instance.search(k), v)

    def test_append(self):
        self.instance.append('testing', 'more')

        self.assertEqual(len(self.instance), 1)
        self.assertEqual(self.instance.search('testing'), 'more')

    def test_append_several(self):
        for k, v in dict(testdata).iteritems():
            self.instance.append(k, v)

        self.assertEqual(len(self.instance), len(testdata))

        for k, v in dict(testdata).iteritems():
            self.assertEqual(self.instance.search(k), v)

    def test_append_twice(self):
        self.instance.append('testing', 'more')
        self.instance.append('testing', 'more more')

        self.assertEqual(len(self.instance), 2)
        self.assertEqual(self.instance.search('testing'), 'more')

    def test_append_twice_and_remove_one(self):
        self.instance.append('testing', 'more')
        self.instance.append('testing', 'more again')

        self.instance.remove('testing')

        self.assertEqual(len(self.instance), 1)
        self.assertEqual(self.instance.search('testing'), 'more again')

    def test_remove_first(self):
        self.remove_from_position(0)

    def test_remove_middle(self):
        self.remove_from_position(1)

    def test_remove_last(self):
        self.remove_from_position(-1)

    def test_remove_all(self):
        self.add_from_sequence()

        for k, v in dict(testdata).iteritems():
            self.instance.remove(k)

        self.assertEqual(len(self.instance), 0)

        for k, v in dict(testdata).iteritems():
            self.assertIsNone(self.instance.search(k))

    def test_remove_all_reversed(self):
        self.add_from_sequence()

        for k, v in reversed(dict(testdata).items()):
            self.instance.remove(k)

        self.assertEqual(len(self.instance), 0)

        for k, v in dict(testdata).iteritems():
            self.assertIsNone(self.instance.search(k))

    def test_remove_from_empty(self):
        self.instance.remove('zaraza')
        self.assertEqual(len(self.instance), 0)

    def test_remove_non_existent(self):
        self.add_from_sequence()
        self.instance.remove('zaraza')
        self.assertEqual(len(self.instance), len(testdata))

    def test_copy_empty(self):
        assert len(self.instance) == 0

        other = self.instance.copy()

        self.assertEqual(len(other), 0)
        self.assertEqual(other.to_list(), [])

    def test_copy_single_element(self):
        self.instance.append('something', 'foo bar baz')
        assert len(self.instance) == 1

        other = self.instance.copy()

        self.assertEqual(len(other), 1)
        self.assertEqual(other.to_list(), self.instance.to_list())

    def test_copy_non_empty(self):
        self.add_from_sequence()

        other = self.instance.copy()

        self.assertEqual(len(other), len(self.instance))
        for k, v in dict(testdata).iteritems():
            self.assertEqual(other.search(k), v)
        self.assertEqual(other.to_list(), self.instance.to_list())

    def test_is_equal(self):
        l1 = self.list_class()
        l2 = self.list_class()
        for k, v in dict(testdata).iteritems():
            l1.append(k, v)
            l2.append(k, v)

        self.assertEqual(l1, l2)

    def test_is_equal_both_empty(self):
        l1 = self.list_class()
        l2 = self.list_class()
        self.assertEqual(l1, l2)

    def test_is_not_equal(self):
        l1 = self.list_class()
        l2 = self.list_class()

        for k, v in dict(testdata).iteritems():
            l1.append(k, v)
            l2.append(k * 2, v)

        self.assertNotEqual(l1, l2)

    def test_is_not_equal_non_empty_against_empty(self):
        l1 = self.list_class()
        l1.append('zaraza', 'something')
        l2 = self.list_class()

        self.assertNotEqual(l1, l2)

    def test_is_not_equal_empty_against_non_empty(self):
        l1 = self.list_class()
        l1.append('zaraza', 'something')
        l2 = self.list_class()

        self.assertNotEqual(l2, l1)

    def test_is_not_equal_same_length_different_content(self):
        l1 = self.list_class()
        l2 = self.list_class()

        l1.append('zaraza', 'something')
        l2.append('zaraz', 'something else')

        self.assertNotEqual(l1, l2)

    def test_is_not_equal_same_preffix_one_list_longer(self):
        l1 = self.list_class()
        l2 = self.list_class()
        for i, d in testdata:
            l1.append(i, d)
            l2.append(i, d)
        # add something else
        l2.append('gato', 'miau miau')

        self.assertNotEqual(l1, l2)

    def test_dump(self):
        self.add_from_sequence()
        self.assertEqual(self.instance.to_list(), testdata)
