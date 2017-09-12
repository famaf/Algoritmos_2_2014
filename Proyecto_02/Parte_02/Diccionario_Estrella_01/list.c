#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "data.h"
#include "index.h"
#include "pair.h"
#include "list.h"


struct _node_t {
    pair_t elem;
    list_t next;
};


list_t list_empty(void) {
    list_t lista = NULL;
    assert(list_length(lista) == 0);
    return (lista);
}


list_t list_destroy(list_t list) {
    list_t tmp = NULL;
    list_t actual = list;
    while (actual != NULL) {
        tmp = actual->next;
        pair_destroy(actual->elem);
        free(actual);
        actual = tmp;
    }

    list = actual;

    return (list);
}

unsigned int list_length(list_t list) {
    unsigned int contador = 0;
    list_t tmp = list;
    while (tmp != NULL) {
        contador = contador + 1;
        tmp = tmp->next;
    }
    return (contador);
}

bool list_is_equal(list_t list, list_t other) {
    bool resultado = (list_length(list) == list_length(other));
    list_t tmp = list;
    list_t tmp2 = other;
    while (resultado && tmp != NULL && tmp2 != NULL) {
        resultado = pair_is_equal((tmp->elem), (tmp2->elem));
        tmp = tmp->next;
        tmp2 = tmp2->next;
    }
    return (resultado);
}

data_t list_search(list_t list, index_t index) {
    data_t resultado = NULL;
    list_t tmp = list;
    while (tmp != NULL && !index_is_equal(index, pair_fst(tmp->elem))) {
        tmp = tmp->next;
    }

    if (tmp != NULL) {
        resultado = pair_snd(tmp->elem);
    }

    return (resultado);
}

list_t list_append(list_t list, index_t index, data_t data) {
    list_t tmp = list;
    list_t nodo = NULL;
    nodo = calloc(1, sizeof(struct _node_t));
    pair_t par_nuevo = pair_from_index_data(index, data);
    nodo->elem = par_nuevo;
    nodo->next = NULL;
    if (tmp == NULL) {
        list = nodo;
    } else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = nodo;
    }
    return (list);
}

list_t list_remove(list_t list, index_t index) {
    list_t tmp = list;
    list_t aux = NULL;

    while (tmp != NULL && !index_is_equal(pair_fst(tmp->elem), index)) {
        aux = tmp;
        tmp = tmp->next;
    }

    if (tmp != NULL && index_is_equal(pair_fst(tmp->elem), index)) {
        if (aux == NULL) {
            list = list->next;
            pair_destroy(tmp->elem);
            free(tmp);
            tmp = NULL;
        } else {
            aux->next = tmp->next;
            pair_destroy(tmp->elem);
            free(tmp);
            tmp = NULL;
        }
    }
    return (list);
}

list_t list_copy(list_t list) {
    list_t aux = list;
    list_t lista_copiada = list_empty();
    index_t indice_2 = NULL;
    data_t dato_2 = NULL;
    while (aux != NULL) {
        indice_2 = index_copy(pair_fst(aux->elem));
        dato_2 = data_copy(pair_snd(aux->elem));
        lista_copiada = list_append(lista_copiada, indice_2, dato_2);
        aux = aux->next;

    }

    return (lista_copiada);
}


void list_dump(list_t list, FILE * fd) {
    list_t aux = list;
    char *palabra = NULL;
    char *definicion = NULL;
    while (aux != NULL) {
        palabra = index_to_string(pair_fst(aux->elem));
        definicion = data_to_string(pair_snd(aux->elem));
        fprintf(fd, "%s: %s\n", palabra, definicion);

        free(palabra);
        palabra = NULL;
        free(definicion);
        definicion = NULL;

        aux = aux->next;
    }
}
