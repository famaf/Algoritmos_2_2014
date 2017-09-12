import ctypes

import helpers


# ctypes wrapper
graph_lib = helpers.get_lib('graph.so')


# TADs

class __Vertex(ctypes.Structure):
    pass


_Vertex = ctypes.POINTER(__Vertex)


class __Edge(ctypes.Structure):
    pass


_Edge = ctypes.POINTER(__Edge)


# vertex_t vertex_create(label_t label)
vertex_create = helpers.maybe_implemented(
    graph_lib, 'vertex_create', _Vertex, [ctypes.c_uint])


# vertex_t vertex_destroy(vertex_t vertex)
vertex_destroy = helpers.maybe_implemented(
    graph_lib, 'vertex_destroy', _Vertex, [_Vertex])


# vertex_t vertex_copy(vertex_t vertex)
vertex_copy = helpers.maybe_implemented(
    graph_lib, 'vertex_copy', _Vertex, [_Vertex])


# label_t vertex_label(vertex_t vertex)
vertex_label = helpers.maybe_implemented(
    graph_lib, 'vertex_label', ctypes.c_uint, [_Vertex])


# edge_t edge_create(vertex_t left, vertex_t right, unsigned int weight)
edge_create = helpers.maybe_implemented(
    graph_lib, 'edge_create', _Edge, [_Vertex, _Vertex, ctypes.c_uint])


# edge_t edge_destroy(edge_t edge)
edge_destroy = helpers.maybe_implemented(
    graph_lib, 'edge_destroy', _Edge, [_Edge])


# edge_t edge_copy(edge_t edge)
edge_copy = helpers.maybe_implemented(
    graph_lib, 'edge_copy', _Edge, [_Edge])


# vertex_t edge_left_vertex(edge_t edge)
edge_left_vertex = helpers.maybe_implemented(
    graph_lib, 'edge_left_vertex', _Vertex, [_Edge])


# vertex_t edge_right_vertex(edge_t edge)
edge_right_vertex = helpers.maybe_implemented(
    graph_lib, 'edge_right_vertex', _Vertex, [_Edge])


# unsigned int edge_weight(edge_t edge)
edge_weight = helpers.maybe_implemented(
    graph_lib, 'edge_weight', ctypes.c_uint, [_Edge])


class Base(object):
    _ctypes_cls_ptr = None
    create_ptr = lambda *a, **kw: None
    destroy_ptr = lambda *a, **kw: None

    def __init__(self, *args, **kwargs):
        super(Base, self).__init__()
        self._ptr = self.create_ptr(*args, **kwargs)

    def __neq__(self, other):
        return not (self == other)

    @property
    def _as_parameter_(self):
        # when passed to a ctypes wrapper, pass the inner ptr
        return self._ptr

    @property
    def c_address(self):
        return ctypes.addressof(self._ptr.contents)

    @classmethod
    def null(cls):
        instance = None
        if cls._ctypes_cls_ptr is not None:
            instance = cls.__new__(cls)
            instance._ptr = cls._ctypes_cls_ptr()
        return instance

    def destroy(self):
        assert self._ptr
        # when we need to explicitly destroy a inner ptr...
        self._ptr = self.destroy_ptr(self._ptr)


class Vertex(Base):
    _ctypes_cls_ptr = _Vertex
    create_ptr = vertex_create
    destroy_ptr = vertex_destroy

    def __init__(self, vertex_id):
        super(Vertex, self).__init__(vertex_id)
        self.label = vertex_id

    def __eq__(self, other):
        return isinstance(other, Vertex) and self.label == other.label

    def __repr__(self):
        return "V: %d" % self.label

    def copy(self):
        return Vertex.from_ptr(vertex_copy(self._ptr))

    @classmethod
    def from_ptr(cls, vertex_ptr):
        instance = cls.__new__(cls)

        instance.label = vertex_label(vertex_ptr)
        instance._ptr = vertex_ptr
        return instance


class Edge(Base):
    _ctypes_cls_ptr = _Edge
    create_ptr = edge_create
    destroy_ptr = edge_destroy

    def __init__(self, left, right, weight):
        super(Edge, self).__init__(left, right, weight)
        self.left = left
        self.right = right
        self.weight = weight

    def __gt__(self, other):
        return self.weight > other.weight

    def __ge__(self, other):
        return self.weight >= other.weight

    def __lt__(self, other):
        return self.weight < other.weight

    def __le__(self, other):
        return self.weight <= other.weight

    def __eq__(self, other):
        return (isinstance(other, Edge) and
                self.left == other.left and
                self.right == other.right and
                self.weight == other.weight)

    def __repr__(self):
        return "(L: %d, R: %d, W: %d)" % (
            self.left.label, self.right.label, self.weight)

    def copy(self):
        return Edge.from_ptr(edge_copy(self._ptr))

    @classmethod
    def from_ptr(cls, edge_ptr):
        instance = cls.__new__(cls)

        left_vertex_ptr = edge_left_vertex(edge_ptr)
        right_vertex_ptr = edge_right_vertex(edge_ptr)

        instance.left = Vertex.from_ptr(left_vertex_ptr)
        instance.right = Vertex.from_ptr(right_vertex_ptr)
        instance.weight = edge_weight(edge_ptr)
        instance._ptr = edge_ptr

        return instance


def new_edge(weight=None):
    if weight is None:
        weight = helpers.random_uint()
    return Edge(
        Vertex(helpers.random_uint()), Vertex(helpers.random_uint()), weight)
