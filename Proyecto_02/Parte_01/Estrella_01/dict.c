#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "list.h"
#include "index.h"
#include "data.h"
#include "dict.h"

struct _dict_t {
    list_t lista;
    index_t lastword;
    data_t lastdef;
    int length;
};

dict_t dict_empty(void) {

    dict_t result = NULL;

    result = calloc(1, sizeof(struct _dict_t));

    result->lista = list_empty();
    result->lastword = NULL;
    result->lastdef = NULL;

    assert(result != NULL);

    return (result);
}

dict_t dict_destroy(dict_t dict) {

    dict->lista = list_destroy(dict->lista);
    dict->lastword = index_destroy(dict->lastword);

    free(dict);
    dict = NULL;

    return (dict);
}

unsigned int dict_length(dict_t dict) {

    assert(dict != NULL);

    unsigned int length = 0;

    length = dict->length;

    return (length);
}

bool dict_is_equal(dict_t dict, dict_t other) {

    assert((dict != NULL) && (other != NULL));

    bool result = false;

    result = list_is_equal(dict->lista, other->lista);

    return (result);
}

bool dict_exists(dict_t dict, word_t word) {

    assert((dict != NULL) && (word != NULL));

    bool result = false;
    data_t defi = NULL;
    index_t theword = index_from_string(word);

    if (dict->lastword != NULL) {
        if (index_is_equal(theword, dict->lastword)) {
            result = true;
        } else {
            defi = list_search(dict->lista, theword);
            if (defi != NULL) {
                result = true;
            }
        }
    } else {
        defi = list_search(dict->lista, theword);
        if (defi != NULL) {
            result = true;
        }
    }

    index_destroy(theword);

    return (result);
}

def_t dict_search(dict_t dict, word_t word) {

    assert((dict != NULL) && (word != NULL));
    assert(dict_exists(dict, word));

    def_t result = NULL;
    data_t defi = NULL;
    index_t theword = index_from_string(word);

    if (dict->lastword != NULL) {
        if (index_is_equal(theword, dict->lastword)) {
            result = data_to_string(dict->lastdef);
            index_destroy(theword);
        } else {
            defi = list_search(dict->lista, theword);
            result = data_to_string(defi);
            dict->lastword = index_destroy(dict->lastword);
            dict->lastword = theword;
            dict->lastdef = defi;
        }
    } else {
        defi = list_search(dict->lista, theword);
        result = data_to_string(defi);
        dict->lastword = theword;
        dict->lastdef = defi;
    }

    assert(result != NULL);
    return (result);
}

dict_t dict_add(dict_t dict, word_t word, def_t def) {

    assert((dict != NULL) && (word != NULL) && (def != NULL));

    index_t theword = index_from_string(word);
    data_t defi = data_from_string(def);

    dict->lista = list_append(dict->lista, theword, defi);
    dict->length = dict->length + 1;
    return (dict);
}

dict_t dict_remove(dict_t dict, word_t word) {

    assert((dict != NULL) && (word != NULL));
    assert(dict_exists(dict, word));

    index_t theword = index_from_string(word);

    if (dict->lastword != NULL) {
        if (index_is_equal(theword, dict->lastword)) {
            dict->lista = list_remove(dict->lista, theword);
            dict->lastword = index_destroy(dict->lastword);
            dict->lastdef = NULL;
        } else {
            dict->lista = list_remove(dict->lista, theword);
        }
    } else {

        dict->lista = list_remove(dict->lista, theword);

    }

    index_destroy(theword);
    dict->length = dict->length - 1;
    return (dict);
}

dict_t dict_copy(dict_t dict) {

    dict_t newdict = calloc(1, sizeof(struct _dict_t));

    newdict->lista = list_copy(dict->lista);

    assert(newdict != NULL);
    assert(dict_is_equal(dict, newdict));
    return (newdict);
}

void dict_dump(dict_t dict, FILE * fd) {

    assert(dict != NULL);
    list_dump(dict->lista, fd);

}
