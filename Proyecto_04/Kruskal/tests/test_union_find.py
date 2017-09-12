import itertools

from unittest import TestCase

from uf_wrapper import UnionFind

MAX_SIZE = 20


class UnionFindTestCase(TestCase):

    def setUp(self):
        super(UnionFindTestCase, self).setUp()
        self.instance = UnionFind(MAX_SIZE)

    def gen_seq(self, size):
        return xrange(1, size + 1)

    def add_from_sequence(self, sequence):
        for i in sequence:
            assert 0 < i
            assert i <= MAX_SIZE
            self.instance.add_class(i)

    def test_empty(self):
        self.assertEqual(len(self.instance), 0)

    def test_push_max_size(self):
        self.add_from_sequence(self.gen_seq(MAX_SIZE))
        self.assertEqual(len(self.instance), MAX_SIZE)

    def test_push_some(self):
        self.add_from_sequence(self.gen_seq(15))
        self.assertEqual(len(self.instance), 15)

    def test_push_is_idempotent(self):
        self.instance.add_class(5)
        self.instance.add_class(5)
        self.assertEqual(len(self.instance), 1)

    def test_union(self):
        self.add_from_sequence(self.gen_seq(20))
        self.assertEqual(len(self.instance), 20)

        self.instance.union(
            self.instance.find_class(5), self.instance.find_class(10))
        self.instance.union(
            self.instance.find_class(8), self.instance.find_class(13))
        self.assertEqual(len(self.instance), 18)

    def test_union_all(self):
        seq = self.gen_seq(10)
        self.add_from_sequence(seq)

        #  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
        # -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 | -1 |

        self.instance.union(
            self.instance.find_class(3), self.instance.find_class(5))
        self.assertEqual(len(self.instance), 9)

        #  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
        # -1 | -1 | -1 | -1 |  3 | -1 | -1 | -1 | -1 | -1 |

        self.instance.union(
            self.instance.find_class(3), self.instance.find_class(8))
        self.assertEqual(len(self.instance), 8)

        #  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
        # -1 | -1 | -1 | -1 |  3 | -1 | -1 |  3 | -1 | -1 |

        self.instance.union(
            self.instance.find_class(8), self.instance.find_class(2))
        self.assertEqual(len(self.instance), 7)

        #  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
        # -1 |  3 | -1 | -1 |  3 | -1 | -1 |  3 | -1 | -1 |

        self.instance.union(
            self.instance.find_class(5), self.instance.find_class(10))
        self.assertEqual(len(self.instance), 6)

        #  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
        # -1 |  3 | -1 | -1 |  3 | -1 | -1 |  3 | -1 |  3 |

        self.instance.union(
            self.instance.find_class(5), self.instance.find_class(6))
        self.assertEqual(len(self.instance), 5)

        #  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
        # -1 |  3 | -1 | -1 |  3 |  3 | -1 |  3 | -1 |  3 |

        self.instance.union(
            self.instance.find_class(10), self.instance.find_class(9))
        self.assertEqual(len(self.instance), 4)

        #  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
        # -1 |  3 | -1 | -1 |  3 |  3 | -1 |  3 |  3 |  3 |

        self.instance.union(
            self.instance.find_class(2), self.instance.find_class(1))
        self.assertEqual(len(self.instance), 3)

        #  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
        #  3 |  3 | -1 | -1 |  3 |  3 | -1 |  3 |  3 |  3 |

        #self.instance.union(
        #    self.instance.find_class(2), self.instance.find_class(3))
        #self.assertEqual(len(self.instance), 3)

        #  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
        #  3 |  3 | -1 | -1 |  3 |  3 | -1 |  3 |  3 |  3 |

        #self.instance.union(
        #    self.instance.find_class(2), self.instance.find_class(3))
        #self.assertEqual(len(self.instance), 3)  # still 3 classes!

        #  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
        #  3 |  3 | -1 | -1 |  3 |  3 | -1 |  3 |  3 |  3 |

        self.instance.union(
            self.instance.find_class(4), self.instance.find_class(7))
        self.assertEqual(len(self.instance), 2)

        #  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
        #  3 |  3 | -1 | -1 |  3 |  3 |  4 |  3 |  3 |  3 |

        self.instance.union(
            self.instance.find_class(4), self.instance.find_class(5))
        self.assertEqual(len(self.instance), 1)

        #  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 |
        #  3 |  3 | -1 |  3 |  3 |  3 |  4 |  3 |  3 |  3 |

        # union all with all, it should be the same
        #for i, j in itertools.product(seq, seq):
        #    self.instance.union(
        #        self.instance.find_class(i), self.instance.find_class(j))
        #    self.assertEqual(len(self.instance), 1)

    def __test_union_same_class(self):
        seq = self.gen_seq(20)
        self.add_from_sequence(seq)

        for i in seq:
            self.instance.union(i, i)

        self.assertEqual(len(self.instance), 20)

    def __test_union_is_idempotent(self):
        self.add_from_sequence(self.gen_seq(5))

        i = 2
        self.instance.union(i, i)
        self.assertEqual(self.instance.find_class(i), i)

        self.instance.union(i, i)
        self.assertEqual(self.instance.find_class(i), i)

    def test_find_class(self):
        seq = self.gen_seq(13)
        self.add_from_sequence(seq)

        for i in seq:
            self.assertEqual(self.instance.find_class(i), i)

    def test_find_class_after_one_union(self):
        seq = self.gen_seq(10)
        self.add_from_sequence(seq)

        i, j = 3, 8
        self.instance.union(
            self.instance.find_class(i), self.instance.find_class(j))
        self.assertEqual(
            self.instance.find_class(i), self.instance.find_class(j))

    def test_find_class_after_all_unions(self):
        seq = self.gen_seq(10)
        self.add_from_sequence(seq)

        # union all with all, it should be the same
        for i, j in itertools.product(seq, seq):
            c1 = self.instance.find_class(i)
            c2 = self.instance.find_class(j)
            if c1 != c2:
                self.instance.union(c1, c2)
                self.assertEqual(
                    self.instance.find_class(i), self.instance.find_class(j))
