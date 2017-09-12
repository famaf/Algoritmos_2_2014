#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "dict.h"
#include "list.h"
#include "pair.h"
#include "index.h"
#include "data.h"



struct _dict_t {
    list_t lista;
};


unsigned int dict_length(dict_t diccionario) {
    assert(diccionario != NULL);
    return (list_length(diccionario->lista));
}

dict_t dict_empty(void) {
    dict_t result = NULL;
    result = calloc(1, sizeof(struct _dict_t));
    assert(result != NULL);
    result->lista = list_empty();
    assert(dict_length(result) == 0);
    return (result);
}


dict_t dict_destroy(dict_t diccionario) {
    assert(diccionario != NULL);
    diccionario->lista = list_destroy(diccionario->lista);
    free(diccionario);
    diccionario = NULL;
    return diccionario;
}

bool dict_is_equal(dict_t diccionario, dict_t otro) {
    bool result = false;
    assert(diccionario != NULL);
    assert(otro != NULL);
    result = list_is_equal(diccionario->lista, otro->lista);

    return (result);
}


bool dict_exists(dict_t diccionario, word_t palabra) {
    bool result = true;
    assert(diccionario != NULL);
    assert(palabra != NULL);
    index_t indice = index_from_string(palabra);
    if ((list_search(diccionario->lista, indice)) == NULL) {
        result = false;
    }

    indice = index_destroy(indice);

    return (result);
}

def_t dict_search(dict_t diccionario, word_t palabra) {
    assert(diccionario != NULL);
    assert(palabra != NULL);
    assert(dict_exists(diccionario, palabra) == true);

    def_t result = NULL;
    index_t indice = index_from_string(palabra);
    result = data_to_string(list_search(diccionario->lista, indice));
    indice = index_destroy(indice);
    assert(result != NULL);
    return (result);
}


dict_t dict_add(dict_t dict, word_t word, def_t def) {
    unsigned int n = dict_length(dict);

    list_t lista = dict->lista;

    assert(dict != NULL);
    assert(word != NULL);
    assert(def != NULL);
    assert(dict_exists(dict, word) != true);

    index_t indice = NULL;
    indice = index_from_string(word);

    data_t definicion = NULL;
    definicion = data_from_string(def);

    dict->lista = list_append(lista, indice, definicion);

    assert(n + 1 == dict_length(dict));

    return (dict);
}


dict_t dict_remove(dict_t dict, word_t word) {
    list_t lista = dict->lista;
    assert(dict != NULL);
    assert(word != NULL);
    assert(dict_exists(dict, word) == true);

    index_t indice = index_from_string(word);
    dict->lista = list_remove(lista, indice);

    indice = index_destroy(indice);

    return (dict);
}


dict_t dict_copy(dict_t dict) {
    dict_t dict2 = NULL;
    dict2 = calloc(1, sizeof(struct _dict_t));
    dict2->lista = list_copy(dict->lista);
    assert(dict2 != NULL);
    assert(dict_is_equal(dict, dict2));

    return (dict2);
}


void dict_dump(dict_t dict, FILE * fd) {
    list_t lista = dict->lista;
    assert(dict != NULL);
    list_dump(lista, fd);
}
