from unittest import TestCase

import base_wrapper

from helpers import (
    IndentMixinTestCase,
    make_int_array_from_iterable,
    skip_if_not_implemented,
)

SORT_ERROR = (
    'The array was not properly sorted when using %s.\n'
    'The INITIAL array was: %s\n'
    'The EXPECTED array is: %s\n'
    'The RESULTING array is: %s'
)
COUNTER_ERROR = (
    'When sorting the array %s, the value for the %s counter is not correct.\n'
    'The EXPECTED value is: %s\n'
    'The RESULTING counter is: %s'
)

FIVE_FIVES = [5] * 5
MANY_SORTED_ASC = range(-10, 10)
MANY_SORTED_DESC = list(reversed(range(-10, 10)))
MANY_UNSORTED = [
    -7, 7, 0, 9, -5, 3, -6, 2, 4, -4, -1, -3, -8, 8, 1, -2, 6, -9, 5, -10]
TWO_ELEMS = [42, 13]
TWO_MAX_MIN_ELEMS = [2147483647, -2147483648]
THREE_ELEMS = [42, 13, 101]
THREE_NEGATIVE_ELEMS = [-13, -13, -13]


class IndentSortTestCase(TestCase, IndentMixinTestCase):
    filenames = ('sort.c',)


class SelectionSortTestCase(TestCase):

    sort_func = base_wrapper.selection_sort

    def setUp(self):
        super(SelectionSortTestCase, self).setUp()
        base_wrapper.reset_counters()

    @skip_if_not_implemented
    def sort(self, iterable):
        iterable = list(iterable)
        if iterable:
            length = len(iterable)
            array = make_int_array_from_iterable(iterable)
        else:
            length = 0
            array = None

        self.sort_func(array, length)

        if array is None:
            array = []
        else:
            array = [i for i in array]

        return array

    def get_counters(self, initial):
        n = len(initial)
        return (n * (n - 1)) / 2, max(n - 1, 0)

    def assert_array_sorted(self, actual, initial):
        expected = sorted(initial)
        # assert array is sorted
        self.assertEqual(
            actual, expected,
            SORT_ERROR % (self.sort_func.__name__, initial, expected, actual))

        # assert counters
        comps, swaps = self.get_counters(initial)

        # assert comp counter is correct
        if comps is not None:
            actual = base_wrapper.get_comp_counter()
            self.assertEqual(
                actual, comps,
                COUNTER_ERROR % (initial, 'comparison', comps, actual))

        # assert swap counter is correct
        if swaps is not None:
            actual = base_wrapper.get_swap_counter()
            self.assertEqual(
                actual, swaps,
                COUNTER_ERROR % (initial, 'swap', swaps, actual))

    def test_sort_an_empty_array(self):
        initial = []
        actual = self.sort(initial)
        self.assert_array_sorted(actual, initial)

    def test_sort_array_one_element(self):
        initial = [42]
        actual = self.sort(initial)
        self.assert_array_sorted(actual, initial)

    def test_sort_array_two_elements(self):
        initial = TWO_ELEMS
        actual = self.sort(initial)
        self.assert_array_sorted(actual, initial)

    def test_sort_array_three_elements(self):
        initial = THREE_ELEMS
        actual = self.sort(initial)
        self.assert_array_sorted(actual, initial)

    def test_sort_a_sorted_asc_array(self):
        initial = MANY_SORTED_ASC
        actual = self.sort(initial)
        self.assert_array_sorted(actual, initial)

    def test_sort_a_sorted_desc_array(self):
        initial = MANY_SORTED_DESC
        actual = self.sort(initial)
        self.assert_array_sorted(actual, initial)

    def test_sort_a_unsorted_array(self):
        initial = MANY_UNSORTED
        actual = self.sort(initial)

        self.assert_array_sorted(actual, initial)

    def test_sort_array_all_elements_equal_0(self):
        initial = [0]
        actual = self.sort(initial)
        self.assert_array_sorted(actual, initial)

    def test_sort_array_all_elements_equal_5(self):
        initial = FIVE_FIVES
        actual = self.sort(initial)
        self.assert_array_sorted(actual, initial)

    def test_sort_array_all_elements_equal_negative(self):
        initial = THREE_NEGATIVE_ELEMS
        actual = self.sort(initial)
        self.assert_array_sorted(actual, initial)

    def test_sort_array_int_max_and_min(self):
        initial = TWO_MAX_MIN_ELEMS
        actual = self.sort(initial)
        self.assert_array_sorted(actual, initial)


class InsertionSortTestCase(SelectionSortTestCase):

    sort_func = base_wrapper.insertion_sort
    counters = {
        id(FIVE_FIVES): (4, 0),
        id(MANY_SORTED_ASC): (19, 0),
        id(MANY_SORTED_DESC): (190, 190),
        id(MANY_UNSORTED): (122, 106),
        id(THREE_ELEMS): (2, 1),
        id(THREE_NEGATIVE_ELEMS): (2, 0),
        id(TWO_ELEMS): (1, 1),
        id(TWO_MAX_MIN_ELEMS): (1, 1),
    }

    def get_counters(self, initial):
        if len(initial) < 2:
            return (0, 0)
        return self.counters[id(initial)]


class QuickSortTestCase(InsertionSortTestCase):

    sort_func = base_wrapper.quick_sort
    counters = {
        id(FIVE_FIVES): (10, 4),
        id(MANY_SORTED_ASC): (380, 19),
        id(MANY_SORTED_DESC): (280, 19),
        id(MANY_UNSORTED): (127, 23),
        id(THREE_ELEMS): (3, 1),
        id(THREE_NEGATIVE_ELEMS): (3, 2),
        id(TWO_ELEMS): (1, 1),
        id(TWO_MAX_MIN_ELEMS): (1, 1),
    }


class RandQuickSortTestCase(SelectionSortTestCase):

    sort_func = base_wrapper.rand_quick_sort

    def get_counters(self, initial):
        # Do not assert on counters because the random pivot makes counters
        # not guessable
        return None, None


class BubbleSortTestCase(SelectionSortTestCase):

    sort_func = base_wrapper.bubble_sort

    def get_counters(self, initial):
        # Do not assert on counters because different alg. can be implemented
        return None, None
