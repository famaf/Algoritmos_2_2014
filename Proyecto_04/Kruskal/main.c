#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "priority_queue.h"
#include "graph.h"
#include "stack.h"
#include "union_find.h"

int main() {
    priority_queue_t pq = NULL;

    union_find_t uf = NULL;

    stack_t mst_edges = NULL;
    stack_t unused_edges = NULL;

    graph_t graph = NULL;
    graph_t mst = NULL;

    edge_t e = NULL;

    union_find_class_t class1 = 0;
    union_find_class_t class2 = 0;

// LEO EL GRAFO DESDE LA ENTRADA ESTANDAR (CONSOLA)
    graph = read_graph_from_file(stdin);

    pq = priority_queue_empty(edges_count(graph));

    uf = union_find_create(vertices_count(graph));

    edge_t *edges = graph_edges(graph);

    unsigned int i = 0;

    while (!priority_queue_is_full(pq) && i < edges_count(graph)) {
        e = edges[i];
        pq = priority_queue_enqueue(pq, e);
        uf = union_find_push(uf, vertex_label(edge_left_vertex(e)));
        uf = union_find_push(uf, vertex_label(edge_right_vertex(e)));
        i = i + 1;
    }

    while (union_find_class_count(uf) > 1 && !priority_queue_is_empty(pq)) {
        e = priority_queue_first(pq);
        pq = priority_queue_dequeue(pq);
        class1 = union_find_find(uf, vertex_label(edge_left_vertex(e)));
        class2 = union_find_find(uf, vertex_label(edge_right_vertex(e)));

        if (class1 != class2) {
            uf = union_find_union(uf, class1, class2);
            mst_edges = stack_push(mst_edges, e);
        } else {
            unused_edges = stack_push(unused_edges, e);
        }
    }

    mst = graph_empty(vertices_count(graph));

// LLENO EL GRAFO DE SALIDA CON LAS ARISTAS PRINCIPALES 
    while (!stack_is_empty(mst_edges)) {
        mst = graph_add_edge(mst, stack_top(mst_edges));
        mst_edges = stack_pop(mst_edges);
    }

// LLENO EL GRAFO DE SALIDA CON LAS ARISTAS SECUNDARIAS
    while (!stack_is_empty(unused_edges)) {
        e = stack_top(unused_edges);
        mst = graph_add_edge(mst, edge_set_primary(e, false));
        unused_edges = stack_pop(unused_edges);
    }

    while (!priority_queue_is_empty(pq)) {
        e = priority_queue_first(pq);
        mst = graph_add_edge(mst, edge_set_primary(e, false));
        pq = priority_queue_dequeue(pq);
    }

// MUESTRO EL GRAFO POR SALIDA ESTANDAR (CONSOLA)
    graph_dump(mst, stdout);

// LIBERO Y DESTRUYO LOS TADS
    free(edges);
    edges = NULL;

    uf = union_find_destroy(uf);

    pq = priority_queue_destroy(pq);

    mst_edges = stack_destroy(mst_edges);

    unused_edges = stack_destroy(unused_edges);

    graph = graph_destroy(graph);

    mst = graph_destroy(mst);

    return 0;
}
