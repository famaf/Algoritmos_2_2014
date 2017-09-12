import test_heap

from pq_wrapper import PriorityQueue


class PriorityQueueTestCase(test_heap.HeapTestCase):

    klass = PriorityQueue

    def add_elem(self, elem):
        self.instance.enqueue(elem)

    def get_elem(self):
        elem = self.instance.first()
        self.addCleanup(elem.destroy)
        return elem

    def remove_elem(self):
        self.instance.dequeue()
