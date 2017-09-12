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
    (void *) elem;
    stack_t next;
};


stack_t vacia(void) {
    stack_t pila = NULL;

    return(pila);
}


stack_t apilar(stack_t pila, (void *) elem) {
    stack_t nodo = NULL;
    nodo = calloc(1, sizeof(struct _node_t));
    nodo->elem = elem;
    nodo->next = pila;
    pila = nodo;

    return(pila);
}

(void *) primero(stack_t pila) {
    assert (!es_vacia(pila));

    (void *) first;
    first = pila->elem;

    return(first);
}

stack_t desapilar(stack_t pila) {
    assert(!es_vacia(pila));

    stack_t aux;
    aux = pila;
    pila = pila->next;
    aux->elem = pair_destroy(aux->elem);
    free(aux);
    aux = NULL;

    return (pila);
}


bool es_vacia(stack_t pila) {
    bool resultado;

    resultado = (pila == NULL);

    return (resultado);
}

stack_t destruir_pila(stack_t pila) {
    while (!es_vacia(pila)) {
        pila = desapilar(pila);
    }

    assert(es_vacia(pila));

    return (pila);
}
