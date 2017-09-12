#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "bst.h"
#include "stack.h"
#include "pair.h"
#include "data.h"
#include "index.h"


struct _node_t {
    bst_t value;
    stack_t next;
};



stack_t vacia(void) {
    stack_t pila = NULL;

    return(pila);
}

bool es_vacia(stack_t pila) {
    bool resultado;

    resultado = (pila == NULL);

    return (resultado);
}


stack_t apilar(stack_t pila, bst_t arbol) {
    stack_t nodo = NULL;
    nodo = calloc(1, sizeof(struct _node_t));
    nodo->value = arbol;
    nodo->next = pila;
    pila = nodo;

    return(pila);
}


bst_t primero(stack_t pila) {
    assert(!es_vacia(pila));

    bst_t first;
    first = pila->value;

    return(first);
}

stack_t desapilar(stack_t pila) {
    assert(!es_vacia(pila));

    stack_t aux = pila->next;
    free(pila);
    pila = NULL;

    return (aux);
}


stack_t destruir_pila(stack_t pila) {
    while (!es_vacia(pila)) {
        pila = desapilar(pila);
    }

    assert(es_vacia(pila));

    return (pila);
}
