import string

from unittest import TestCase

from bst_wrapper import BinarySearchTree


testdata = [
    ('a', 'b'), ('foo', 'bar'), ('perro', 'zaraza'),
    ('aaa', 'something'), ('', 'empty'), ('1234', 'numbers!'),
    ('gato', 'animal que maulla'),
]

letters = ''.join(sorted(string.letters))


class BaseTestCase(TestCase):

    bst_class = BinarySearchTree

    def setUp(self):
        super(BaseTestCase, self).setUp()
        self.instance = BinarySearchTree()

    def add_from_sequence(self, sequence=None):
        if sequence is None:
            sequence = testdata
        for i, d in sequence:
            self.instance.add(i, d)

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


class BinarySearchTreeLengthTestCase(BaseTestCase):

    def test_length_empty_should_be_zero(self):
        self.assertEqual(len(self.instance), 0)

    def test_length_single_node_should_be_one(self):
        self.instance.add('foo', 'bar')
        self.assertEqual(len(self.instance), 1)

    def test_length_root_and_left_node_should_be_two(self):
        self.instance.add('foo', 'bar')
        self.instance.add('azul', 'color del cielo')

        self.assertEqual(len(self.instance), 2)

    def test_length_root_and_right_node_should_be_two(self):
        self.instance.add('foo', 'bar')
        self.instance.add('grey', 'neutral color')

        self.assertEqual(len(self.instance), 2)

    def test_length_root_and_left_and_right_node_should_be_three(self):
        self.instance.add('foo', 'bar')
        self.instance.add('azul', 'color del cielo')
        self.instance.add('grey', 'neutral color')

        self.assertEqual(len(self.instance), 3)

    def test_length_many_nodes(self):
        self.add_from_sequence()
        self.assertEqual(len(self.instance), len(testdata))


class BinarySearchTreeSearchTestCase(BaseTestCase):

    def test_search_on_empty_should_be_none(self):
        self.assertIsNone(self.instance.search('zaraza'))

    def test_search_does_not_exist_on_non_empty_should_be_none(self):
        self.add_from_sequence()
        assert 'zaraza' not in dict(testdata)
        self.assertIsNone(self.instance.search('zaraza'))

    def test_search_exists_on_non_empty(self):
        self.add_from_sequence()
        for k, v in dict(testdata).iteritems():
            self.assertEqual(self.instance.search(k), v)


class BinarySearchTreeAddTestCase(BaseTestCase):

    def test_add_to_empty_length_should_be_one_and_search_returns_data(self):
        self.instance.add('testing', 'more')

        self.assertEqual(len(self.instance), 1)
        self.assertEqual(self.instance.search('testing'), 'more')

    def test_add_several_check_length_and_search_for_all(self):
        for k, v in dict(testdata).iteritems():
            self.instance.add(k, v)

        self.assertEqual(len(self.instance), len(testdata))

        for k, v in dict(testdata).iteritems():
            self.assertEqual(self.instance.search(k), v)

    def test_add_index_in_alphabetical_order_ascending(self):
        data = letters

        for i in data:
            self.instance.add(i, i * 10)

        self.assertEqual(len(self.instance), len(data))

        for i in data:
            self.assertEqual(self.instance.search(i), i * 10)

    def test_add_index_in_alphabetical_order_descending(self):
        data = reversed(letters)

        for i in data:
            self.instance.add(i, i * 10)

        self.assertEqual(len(self.instance), len(letters))

        for i in data:
            self.assertEqual(self.instance.search(i), i * 10)

    def test_add_alternating_left_and_right_check_length_and_to_list(self):
        data = letters

        # add an initial "middle" index
        middle = data[len(data) / 2]
        mdata = 'the root of the tree %s' % middle
        self.instance.add(middle, mdata)
        expected = [(middle, mdata)]

        for i in xrange(10):
            right = data[i]
            rdata = 'some right data %s' % right

            left = data[len(data) - 1 - i]
            ldata = 'some left data %s' % left

            expected.append((right, rdata))
            expected.append((left, ldata))

            self.instance.add(right, rdata)
            self.instance.add(left, ldata)

        self.assertEqual(len(self.instance), 21)
        self.assertEqual(self.instance.to_list(), sorted(expected))


class BinarySearchTreeRemoveTestCase(BaseTestCase):

    def test_remove_from_empty_tree(self):
        self.instance.remove('foo')
        self.assertEqual(len(self.instance), 0)

    def test_remove_first_from_non_empty_tree(self):
        self.remove_from_position(0)

    def test_remove_middle_from_non_empty_tree(self):
        self.remove_from_position(1)

    def test_remove_last_from_non_empty_tree(self):
        self.remove_from_position(-1)

    def test_remove_root_from_non_empty_check_length_and_to_list(self):
        self.instance.add('foo', 'bar')
        self.instance.add('azul', 'color del cielo')
        self.instance.add('grey', 'neutral color')
        self.assertEqual(len(self.instance), 3)

        self.instance.remove('foo')

        self.assertEqual(len(self.instance), 2)
        self.assertEqual(
            self.instance.to_list(),
            [('azul', 'color del cielo'), ('grey', 'neutral color')])

    def test_remove_all_from_non_empty_tree(self):
        self.add_from_sequence()

        for k, v in dict(testdata).iteritems():
            self.instance.remove(k)

        self.assertEqual(len(self.instance), 0)

        for k, v in dict(testdata).iteritems():
            self.assertIsNone(self.instance.search(k))

    def test_remove_non_existent_from_non_empty_tree(self):
        self.add_from_sequence()
        assert 'zaraza' not in testdata

        self.instance.remove('zaraza')

        self.assertEqual(len(self.instance), len(testdata))


class BinarySearchTreeCopyTestCase(BaseTestCase):

    def test_copy_empty_tree_check_length_and_search_returns_none(self):
        other = self.instance.copy()

        self.assertEqual(len(self.instance), 0)
        self.assertEqual(len(other), 0)

        self.assertIsNone(self.instance.search('foo'))
        self.assertIsNone(other.search('bar'))

    def test_copy_root_only_tree(self):
        self.instance.add('root', 'do not break')
        self.assertEqual(len(self.instance), 1)

        other = self.instance.copy()
        self.assertEqual(len(self.instance), len(other))

        self.assertEqual(other.to_list(), [('root', 'do not break')])

    def test_copy_non_empty_tree(self):
        self.add_from_sequence()
        self.assertEqual(len(self.instance), len(testdata))

        other = self.instance.copy()

        self.assertEqual(len(self.instance), len(other))

        for k, v in dict(testdata).iteritems():
            self.assertEqual(self.instance.search(k), v)
            self.assertEqual(other.search(k), v)

    def test_copy_tree_single_left_branch(self):
        data = '123456789'

        for i in data:
            self.instance.add(i, i * 10)
        self.assertEqual(len(self.instance), len(data))

        other = self.instance.copy()
        self.assertEqual(len(self.instance), len(other))

        self.assertEqual(self.instance.to_list(), other.to_list())

    def test_add_index_in_alphabetical_order_descending(self):
        data = '987654321'

        for i in data:
            self.instance.add(i, i * 10)
        self.assertEqual(len(self.instance), len(data))

        other = self.instance.copy()
        self.assertEqual(len(self.instance), len(other))

        self.assertEqual(self.instance.to_list(), other.to_list())


class BinarySearchTreeIsEqualTestCase(BaseTestCase):

    def test_is_equal_both_non_empty(self):
        other = BinarySearchTree()
        another = BinarySearchTree()
        for k, v in dict(testdata).iteritems():
            other.add(k, v)
            another.add(k, v)

        self.assertEqual(other, another)

    def test_is_equal_both_empty(self):
        other = BinarySearchTree()
        another = BinarySearchTree()
        self.assertEqual(other, another)

    def test_is_not_equal_both_non_empty(self):
        other = BinarySearchTree()
        another = BinarySearchTree()

        for k, v in dict(testdata).iteritems():
            other.add(k, v)
            another.add(k * 2, v)

        self.assertNotEqual(other, another)

    def test_is_not_equal_against_empty(self):
        other = BinarySearchTree()
        other.add('zaraza', 'something')
        another = BinarySearchTree()

        self.assertNotEqual(other, another)

    def test_is_not_equal_from_empty(self):
        other = BinarySearchTree()
        other.add('zaraza', 'something')
        another = BinarySearchTree()

        self.assertNotEqual(another, other)

    def test_is_not_equal_both_non_empty_but_same_length(self):
        other = BinarySearchTree()
        other.add('zaraza', 'something')
        another = BinarySearchTree()
        another.add('zaraz', 'something else')
        self.assertEqual(len(other), len(another))

        self.assertNotEqual(other, another)


class BinarySearchTreeToListTestCase(BaseTestCase):

    def test_to_list_empty_tree(self):
        self.assertEqual(self.instance.to_list(), [])

    def test_to_list_only_root(self):
        self.instance.add('root', 'do not break')
        self.assertEqual(len(self.instance), 1)

        self.assertEqual(self.instance.to_list(), [('root', 'do not break')])

    def test_to_list_only_root_and_right_tree(self):
        self.instance.add('root', 'do not break')
        self.instance.add('testme', 'a lot')
        self.assertEqual(len(self.instance), 2)

        self.assertEqual(
            self.instance.to_list(),
            [('root', 'do not break'), ('testme', 'a lot')])

    def test_to_list_only_root_and_leftt_tree(self):
        self.instance.add('root', 'do not break')
        self.instance.add('perro', 'animal que ladra')
        self.assertEqual(len(self.instance), 2)

        self.assertEqual(
            self.instance.to_list(),
            [('perro', 'animal que ladra'), ('root', 'do not break')])

    def test_to_list_generates_a_sorted_list(self):
        self.add_from_sequence()
        self.assertEqual(self.instance.to_list(), sorted(testdata))
