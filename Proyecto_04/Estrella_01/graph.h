#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdbool.h>
#include <stdio.h>


/* Vertex abstract data type */

typedef struct _vertex_t *vertex_t;
typedef unsigned int label_t;

vertex_t vertex_create(label_t label);
/*
 * Return a newly created vertex with identifier 'label'.
 *
 * 'vertex_destroy' has to be called on the resulting vertex when is no
 * longer used.
 *
 * POST: the result is not NULL and vertex_label(result) is 'label'.
 */

vertex_t vertex_destroy(vertex_t vertex);
/*
 * Free the resources allocated for 'vertex'.
 *
 * PRE: 'vertex' must not be NULL.
 *
 * POST: the result is NULL.
 */

vertex_t vertex_copy(vertex_t vertex);
/*
 * Return a newly created vertex which is an exact copy of the given 'vertex'.
 *
 * 'vertex_destroy' has to be called on the resulting vertex when is no
 * longer used.
 *
 * PRE: 'vertex' must not be NULL.
 *
 * POST: the result is not NULL and vertex_label(result) is 'label'.
 * POST: the result is not NULL and the label of the result is equal to
 * the label from 'vertex'.
 */

label_t vertex_label(vertex_t vertex);
/*
 * Return the label for 'vertex'.
 *
 * PRE: 'vertex' must not be NULL.
 */


/* Edge abstract data type */

typedef struct _edge_t *edge_t;

edge_t edge_create(vertex_t left, vertex_t right, unsigned int weight);
/*
 * Return a newly created edge.
 *
 * 'edge_destroy' has to be called on the resulting edge when is no
 * longer used.
 *
 * PRE: both 'left' and 'right' must not be NULL.
 *
 * POST: the result is not NULL and 'left' and 'right' are the result vertices.
 * Also, edge_weight(result) is 'weight'.
 */

edge_t edge_destroy(edge_t edge);
/*
 * Free the resources allocated for 'edge'.
 *
 * PRE: 'edge' must not be NULL.
 *
 * POST: the result is NULL.
 */

edge_t edge_copy(edge_t edge);
/*
 * Return a newly created edge which is an exact copy of the given 'edge'.
 *
 * 'edge_destroy' has to be called on the resulting vertex when is no
 * longer used.
 *
 * PRE: 'edge' must not be NULL.
 *
 * POST: the result is not NULL and the left and right vertices are equal to
 * the vertices from 'edge', and so is its weight.
 */

vertex_t edge_left_vertex(edge_t edge);
/*
 * Return the left vertex of 'edge'.
 *
 * PRE: 'edge' must not be NULL.
 *
 * POST: the result is not NULL.
 */

vertex_t edge_right_vertex(edge_t edge);
/*
 * Return the right vertex of 'edge'.
 *
 * PRE: 'edge' must not be NULL.
 *
 * POST: the result is not NULL.
 */

unsigned int edge_weight(edge_t edge);
/*
 * Return the weight of 'edge'.
 *
 * PRE: 'edge' must not be NULL.
 */

bool edge_lt(edge_t edge, edge_t other);
/*
 * Return whether the given 'edge' is strictly less than 'other'.
 *
 * PRE: both 'edge' and 'other' must not be NULL.
 */

bool edge_lte(edge_t edge, edge_t other);
/*
 * Return whether the given 'edge' is less or equal than 'other'.
 *
 * PRE: both 'edge' and 'other' must not be NULL.
 */

bool edge_is_primary(edge_t edge);
/*
 * Return true if the edge is a primary edge.
 *
 * PRE: 'edge' must not be NULL.
 */

edge_t edge_set_primary(edge_t edge, bool is_primary);
/*
 * Return the edge updated.
 *
 * PRE: 'edge' must not be NULL.
 */

void edge_dump(edge_t edge, FILE *fd);
/*
 * Dump the given 'edge' to the given file descriptor 'fd'.
 *
 * PRE: 'edge' must not be NULL, and 'fd' must be a valid file descriptor.
 */


/* Graph abstract data type */

typedef struct _graph_t *graph_t;

graph_t graph_empty(unsigned int num_vertices);
/*
 * Return a newly created graph that will hold up to 'num_vertices'.
 *
 * 'graph_destroy' has to be called on the resulting graph when is no
 * longer used.
 *
 * POST: the result is not NULL and graph_name(result) is 'name'.
 */

graph_t graph_destroy(graph_t graph);
/*
 * Free the resources allocated for 'graph'.
 *
 * PRE: 'graph' must not be NULL.
 *
 * POST: the result is NULL.
 */

graph_t graph_add_edge(graph_t graph, edge_t edge);
/*
 * Add 'edge' to the given 'graph'.
 *
 * PRE: both 'graph' and 'edge' must not be NULL.
 *
 * POST: the result is not NULL and is the same as 'graph' but with the new
 * 'edge' added to the edges list.
 */

graph_t read_graph_from_file(FILE *fd);
/*
 * Return a newly created graph that will be filled with the data in
 * the file descriptor 'fd'.
 *
 * The file format must be as follows:
 *
 * # <num vertices> <num edges>
 * graph <graph name> {
 *     <if of vertex from> -- <id of vertex to> [label=<edge weigth>];
 *     <if of vertex from> -- <id of vertex to> [label=<edge weigth>];
 *     <if of vertex from> -- <id of vertex to> [label=<edge weigth>];
 *     <if of vertex from> -- <id of vertex to> [label=<edge weigth>];
 *     ...
 *     <if of vertex from> -- <id of vertex to> [label=<edge weigth>];
 * }
 *
 * PRE: 'fd' must be a valid file descriptor.
 *
 * POST: the result is not NULL and is a graph that has as many vertices and
 * as many edges as the amount indicated in the input file. Also, the resulting
 * graph's name is the same as the one given in the file descripted by 'fd'.
 */

unsigned int vertices_count(graph_t graph);
/*
 * Return the amount of vertices in the given 'graph'.
 *
 * PRE: 'graph' must be not NULL.
 */

unsigned int edges_count(graph_t graph);
/*
 * Return the amount of edges in the given 'graph'.
 *
 * PRE: 'graph' must be not NULL.
 */

edge_t *graph_edges(graph_t graph);
/*
 * Return an array with a copy of the edges of the given 'graph'.
 *
 * PRE: 'graph' must be not NULL.
 *
 * POST: the result is not NULL and will hold as many edges as
 * 'edges_count(graph)'. The caller must call free on it when done
 * using it.
 */

void graph_dump(graph_t graph, FILE *fd);
/*
 * Dump the given 'graph' to the file descriptor 'fd'.
 *
 * The file format is the same as the one required in read_graph_from_file.
 *
 * PRE: 'graph' must not be NULL and 'fd' must be a valid file descriptor.
 */

#endif
