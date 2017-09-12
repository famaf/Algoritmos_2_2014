#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "bst.h"
//#include "stack.h"
#include "list.h"
#include "pair.h"
#include "data.h"
#include "index.h"



struct _tree_node_t {
    bst_t izquierda;
    pair_t elem;
    bst_t derecha;
};

//----------------------------------------------
//funcion auxiliar (calcula el maximo elemento del arbol derecho)

pair_t max_elem(bst_t arbol) {
    assert(arbol != NULL);
    pair_t resultado = NULL;
    bst_t arbol_der = arbol->derecha;
    bst_t aux = arbol;

    while (arbol_der != NULL) {
        aux = arbol_der;
        arbol_der = arbol_der->derecha;
    }

    resultado = aux->elem;

    return (resultado);
}

//----------------------------------------------
//funcion auxiliar (elimina el maximo elemento del arbol derecho)

bst_t delete_max(bst_t arbol) {
    bst_t aux = arbol;
    bst_t tmp = arbol;

    if (arbol->derecha == NULL) {
        arbol = arbol->izquierda;
        aux->elem = pair_destroy(aux->elem);
        free(aux);
        aux = NULL;
    }
    else {
        while (tmp->derecha != NULL) {
            aux = tmp;
            tmp = tmp->derecha;
        }
        aux->derecha = tmp->izquierda;
        tmp->izquierda = NULL;
        tmp->elem = pair_destroy(tmp->elem);
        free(tmp);
        tmp = NULL;
    }

    return (arbol);

}

//----------------------------------------------

bst_t bst_empty(void) {
    bst_t arbol = NULL;
    assert(bst_length(arbol) == 0);
    return (arbol);
}


bst_t bst_destroy(bst_t arbol) {
    if (arbol != NULL) {
        bst_destroy(arbol->izquierda);
        bst_destroy(arbol->derecha);
        arbol->elem = pair_destroy(arbol->elem);
        free(arbol);
        arbol = NULL;
    }

    return (arbol);
}


unsigned int bst_length(bst_t arbol) {
    unsigned int largo = 0;

    stack_t pila = vacia();
    bst_t aux = NULL;
    pila = apilar(pila, arbol);

    while (!es_vacia(pila)) {
        aux = primero(pila);
        pila = desapilar(pila);
        pila = apilar(pila, aux->izquierda);
        pila = apilar(pila, aux->derecha);
        largo = largo + 1;
    }
    pila = destruir_pila(pila);

    return (largo);
}


bool bst_is_equal(bst_t arbol, bst_t otro) {
    bool resultado;

    if (arbol == NULL && otro == NULL) {
        resultado = true;
    }
    else if ((arbol != NULL && otro == NULL)
               || (arbol == NULL && otro != NULL)) {
        resultado = false;
    }
    else {
        resultado = pair_is_equal(arbol->elem, otro->elem);
        resultado = resultado
            && bst_is_equal(arbol->izquierda, otro->izquierda)
            && bst_is_equal(arbol->derecha, otro->derecha);
    }

    return (resultado);
}


data_t bst_search(bst_t arbol, index_t index) {
    data_t resultado = NULL;

    while (arbol != NULL && !index_is_equal(pair_fst(arbol->elem), index)) {
        if (index_is_less_than(index, pair_fst(arbol->elem))) {
            arbol = arbol->izquierda;
        }
        else {
            arbol = arbol->derecha;
        }
    }

    if (arbol != NULL) {
        resultado = pair_snd(arbol->elem);
    }

    return (resultado);
}


bst_t bst_add(bst_t arbol, index_t index, data_t data) {
    bst_t nodo = NULL;
    bst_t aux = NULL;
    bst_t tmp = NULL;

    nodo = calloc(1, sizeof(struct _tree_node_t));
    pair_t par_nuevo = pair_from_index_data(index, data);
    nodo->elem = par_nuevo;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;

    if (arbol == NULL) {
        arbol = nodo;
    }
    else {
        tmp = arbol;

        while (tmp != NULL) {
            aux = tmp;

            // index < indice del arbol
            if (index_is_less_than(index, pair_fst(tmp->elem))) {
                tmp = tmp->izquierda;
            }
            // index > indice del arbol
            else {
                tmp = tmp->derecha;
            }
        }

        if (index_is_less_than(index, pair_fst(aux->elem))) {
            aux->izquierda = nodo;
        }
        else {
            aux->derecha = nodo;
        }
    }

    return (arbol);
}


bst_t bst_remove(bst_t arbol, index_t index) {
    bst_t resultado;
    bst_t aux = arbol;

    if (arbol == NULL) {
        resultado = arbol;
    }
    else {
        if (index_is_less_than(index, pair_fst(arbol->elem))) {
            arbol->izquierda = bst_remove(arbol->izquierda, index);
            resultado = arbol;
        }
        else if (index_is_equal(index, pair_fst(arbol->elem))
                   && (arbol->izquierda == NULL)) {
            arbol = arbol->derecha;
            pair_destroy(aux->elem);
            free(aux);
            aux = NULL;
            resultado = arbol;
        }
        else if (index_is_equal(index, pair_fst(arbol->elem))
                   && (arbol->izquierda != NULL)) {
            arbol->elem = pair_destroy(arbol->elem);
            arbol->elem = pair_copy(max_elem(arbol->izquierda));
            arbol->izquierda = delete_max(arbol->izquierda);

            resultado = arbol;
        }
        else {
            arbol->derecha = bst_remove(arbol->derecha, index);
            resultado = arbol;
        }
    }

    return (resultado);
}


bst_t bst_copy(bst_t arbol) {
    bst_t copia = NULL;
    copia = bst_empty();

    if (arbol != NULL) {
        index_t index_new = index_copy(pair_fst(arbol->elem));
        data_t data_new = data_copy(pair_snd(arbol->elem));

        copia = bst_add(copia, index_new, data_new);

        copia->izquierda = bst_copy(arbol->izquierda);

        copia->derecha = bst_copy(arbol->derecha);
    }

    return (copia);
}


list_t bst_to_list(bst_t arbol, list_t lista) {
    if (arbol != NULL) {
        lista = bst_to_list(arbol->izquierda, lista);
        lista = list_append(lista, index_copy(pair_fst(arbol->elem)), data_copy(pair_snd(arbol->elem)));
        lista = bst_to_list(arbol->derecha, lista);
    }

    return (lista);
}
