#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "dict.h"
#include "list.h"
#include "pair.h"
#include "index.h"
#include "data.h"
#include "bst.h"



struct _dict_t {
    bst_t arbol;
};


unsigned int dict_length(dict_t diccionario) {
    assert(diccionario != NULL);
    return (bst_length(diccionario->arbol));
}

dict_t dict_empty(void) {
    dict_t result = NULL;
    result = calloc(1, sizeof(struct _dict_t));
    assert(result != NULL);
    result->arbol = bst_empty();
    assert(dict_length(result) == 0);
    return (result);
}


dict_t dict_destroy(dict_t diccionario) {
    assert(diccionario != NULL);
    diccionario->arbol = bst_destroy(diccionario->arbol);
    free(diccionario);
    diccionario = NULL;
    return diccionario;
}

bool dict_is_equal(dict_t diccionario, dict_t otro) {
    bool result = false;
    assert(diccionario != NULL);
    assert(otro != NULL);
    result = bst_is_equal(diccionario->arbol, otro->arbol);

    return (result);
}


bool dict_exists(dict_t diccionario, word_t palabra) {
    bool result = true;
    assert(diccionario != NULL);
    assert(palabra != NULL);
    index_t indice = index_from_string(palabra);
    if ((bst_search(diccionario->arbol, indice)) == NULL) {
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
    result = data_to_string(bst_search(diccionario->arbol, indice));
    indice = index_destroy(indice);
    assert(result != NULL);
    return (result);
}


dict_t dict_add(dict_t dict, word_t word, def_t def) {

    unsigned int n = dict_length(dict);

    assert(dict != NULL);
    assert(word != NULL);
    assert(def != NULL);
    assert(dict_exists(dict, word) != true);

    index_t indice = NULL;
    indice = index_from_string(word);

    data_t definicion = NULL;
    definicion = data_from_string(def);

    dict->arbol = bst_add(dict->arbol, indice, definicion);

    assert(n + 1 == dict_length(dict));

    return (dict);
}


dict_t dict_remove(dict_t dict, word_t word) {

    assert(dict != NULL);
    assert(word != NULL);
    assert(dict_exists(dict, word) == true);

    index_t indice = index_from_string(word);
    dict->arbol = bst_remove(dict->arbol, indice);

    indice = index_destroy(indice);

    return (dict);
}


dict_t dict_copy(dict_t dict) {
    dict_t dict2 = NULL;
    dict2 = calloc(1, sizeof(struct _dict_t));
    dict2->arbol = bst_copy(dict->arbol);
    assert(dict2 != NULL);
    assert(dict_is_equal(dict, dict2));

    return (dict2);
}

//DUDAS
void dict_dump(dict_t dict, FILE * fd) {
    bst_t arbol2 = dict->arbol;
    list_t list = list_empty();
    assert(dict != NULL);
    list = bst_to_list(arbol2, list);
    list_dump(list, fd);
    list = list_destroy(list);
}
