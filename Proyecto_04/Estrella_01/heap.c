#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "heap.h"
#include "graph.h"


struct _heap_t {
    heap_elem_t *array;
    unsigned int size;
    unsigned int max_size;
};

//-----------------------------------------------------------------------------
//                  FUNCIONES AUXILIARES

// ENCUENTRA HIJO IZQUIERDO
unsigned int left(unsigned int pos_father) {

    unsigned int hijo_izq = (2 * pos_father);

    return (hijo_izq);
}


// ENCUENTRA HIJO DERECHO
unsigned int right(unsigned int pos_father) {

    unsigned int hijo_der = (2 * pos_father) + 1;

    return (hijo_der);
}


// ENCUENTRA EL PADRE
unsigned int parent(unsigned int algun_hijo) {

    unsigned int padre = (algun_hijo / 2);

    return (padre);
}


// ¿ TIENE HIJOS ?
bool has_children(heap_t heap, unsigned int pos_father) {

    bool result = (left(pos_father) <= heap->size);

    return (result);
}


// ¿ TIENE PADRE ?
bool has_parent(unsigned int pos_son) {

    bool result = (pos_son != 1);

    return (result);
}


// EL HIJO MAS CHICO
unsigned int min_child(heap_t heap, unsigned int pos_father) {

    unsigned int result = 0;

    assert(has_children(heap, pos_father));

    if (right(pos_father) <= heap->size) {
        if (heap_elem_lte
            (heap->array[right(pos_father)], heap->array[left(pos_father)])) {
            result = right(pos_father);
        } else {
            result = left(pos_father);
        }
    } else {
        result = left(pos_father);
    }

    return (result);
}




// ASCENDER ELEMENTO
heap_t lift(heap_t heap, unsigned int pos) {

    unsigned int padre = parent(pos);
    heap_elem_t tmp = NULL;

    tmp = heap->array[pos];
    heap->array[pos] = heap->array[padre];
    heap->array[padre] = tmp;

    return (heap);
}


// ¿ TIENE QUE ASCENDER ?
bool must_lift(heap_t heap, unsigned int pos) {
    bool result;

    result = heap_elem_lt(heap->array[pos], heap->array[parent(pos)]);

    return (result);
}


// FLOTAR ELEMENTO
heap_t floatt(heap_t heap) {
    unsigned int aux = heap->size;

    while (has_parent(aux) && must_lift(heap, aux)) {
        heap = lift(heap, aux);
        aux = parent(aux);
    }

    return (heap);
}


// HUNDIR ELEMENTO
heap_t sink(heap_t heap) {
    unsigned int aux = 1;

    while (has_children(heap, aux)
           && must_lift(heap, min_child(heap, aux))) {
        aux = min_child(heap, aux);
        heap = lift(heap, aux);
    }

    return (heap);
}

//-----------------------------------------------------------------------------

heap_t heap_empty(unsigned int max_size) {
    heap_t heap = NULL;

    heap = calloc(1, sizeof(struct _heap_t));
    heap->array = calloc(max_size + 1, sizeof(heap_elem_t));
    heap->max_size = max_size;
    heap->size = 0;

    return (heap);
}


heap_t heap_destroy(heap_t heap) {

    assert(heap != NULL);

    while (heap->size != 0) {
        heap->array[heap->size] = heap_elem_destroy(heap->array[heap->size]);
        heap->size = heap->size - 1;
    }

    free(heap->array);
    heap->array = NULL;
    free(heap);
    heap = NULL;

    return (heap);
}


heap_t heap_insert(heap_t heap, heap_elem_t elem) {
    heap->size = heap->size + 1;
    heap->array[heap->size] = elem;
    heap = floatt(heap);

    return (heap);
}


heap_t heap_remove_minimum(heap_t heap) {

    assert(heap != NULL);

    heap->array[1] = heap_elem_destroy(heap->array[1]);

    heap->array[1] = heap->array[heap->size];

    heap->size = heap->size - 1;

    heap = sink(heap);

    return (heap);
}


heap_elem_t heap_minimum(heap_t heap) {
    assert(heap != NULL);

    heap_elem_t minimo = NULL;

    minimo = heap_elem_copy(heap->array[1]);

    return (minimo);
}


bool heap_is_empty(heap_t heap) {
    bool resultado = (heap->size == 0);

    return (resultado);
}


bool heap_is_full(heap_t heap) {
    assert(heap != NULL);

    bool resultado = (heap->size == heap->max_size);

    return (resultado);
}


unsigned int heap_size(heap_t heap) {
    unsigned int resultado = heap->size;

    return (resultado);
}


void heap_dump(heap_t heap, FILE * fd) {
    assert(heap != NULL);
    unsigned int i;

    for (i = 1; i <= heap->size; i++) {
        heap_elem_dump(heap->array[i], fd);
    }

}
