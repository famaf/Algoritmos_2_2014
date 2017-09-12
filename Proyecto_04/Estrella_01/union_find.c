#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "union_find.h"


struct _union_find_t {
    union_find_class_t *array;
    unsigned int cantidad_clases;
};


// ES REPRESENTANTE
bool is_rep(union_find_t uf, union_find_elem_t elem) {
    bool b;
    b = (uf->array[elem] == elem);

    return (b);
}


union_find_t union_find_create(unsigned int max_size) {
    union_find_t resultado = NULL;

    resultado = calloc(1, sizeof(struct _union_find_t));
    resultado->array = calloc(max_size + 1, sizeof(union_find_class_t));
    resultado->cantidad_clases = 0;

    assert(resultado->array != NULL);

    return (resultado);
}


union_find_t union_find_destroy(union_find_t uf) {
    assert(uf != NULL);
    free(uf->array);
    uf->array = NULL;
    free(uf);
    uf = NULL;

    return (uf);
}


union_find_t union_find_push(union_find_t uf, union_find_elem_t elem) {
    if (elem != uf->array[elem]) {
        uf->cantidad_clases = uf->cantidad_clases + 1;
    }

    uf->array[elem] = elem;

    return (uf);
}


union_find_t union_find_union(union_find_t uf, union_find_class_t class1,
                              union_find_class_t class2) {
    uf->array[class1] = class2;

    if (class1 != class2) {
        uf->cantidad_clases = uf->cantidad_clases - 1;
    }
    return (uf);
}


union_find_class_t union_find_find(union_find_t uf, union_find_elem_t elem) {
    union_find_class_t resultado;

    union_find_elem_t j;
    union_find_elem_t k;

    j = elem;

    while (!is_rep(uf, j)) {
        j = uf->array[j];
    }

    resultado = j;

    j = elem;

    while (!is_rep(uf, j)) {
        k = uf->array[j];
        uf->array[j] = resultado;
        j = k;
    }

    return (resultado);
}


unsigned int union_find_class_count(union_find_t uf) {
    unsigned int resultado;
    resultado = uf->cantidad_clases;

    return (resultado);
}
