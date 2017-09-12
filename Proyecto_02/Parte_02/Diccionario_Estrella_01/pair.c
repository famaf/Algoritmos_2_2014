#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pair.h"
#include "index.h"
#include "data.h"


struct _pair_t {
    data_t dato;
    index_t indice;
};


pair_t pair_from_index_data(index_t index, data_t data) {
    assert(index != NULL && data != NULL);
    pair_t resultado = NULL;
    resultado = calloc(1, sizeof(struct _pair_t));
    resultado->indice = index;
    resultado->dato = data;
    assert(resultado != NULL);
    return (resultado);
}


pair_t pair_destroy(pair_t par) {
    assert(par != NULL);
    par->indice = index_destroy(par->indice);
    par->dato = data_destroy(par->dato);
    free(par);
    par = NULL;
    return (par);
}


index_t pair_fst(pair_t par) {
    assert(par != NULL);
    index_t resultado = NULL;
    resultado = par->indice;
    assert(resultado != NULL);
    return (resultado);
}


data_t pair_snd(pair_t par) {
    assert(par != NULL);
    data_t resultado = NULL;
    resultado = par->dato;
    assert(resultado != NULL);
    return (resultado);
}


bool pair_is_equal(pair_t par, pair_t otro) {
    bool resultado = false;
    bool resultado1;
    bool resultado2;
    assert(par != NULL && otro != NULL);
    resultado1 = index_is_equal(pair_fst(par), pair_fst(otro));
    resultado2 = data_is_equal(pair_snd(par), pair_snd(otro));
    resultado = resultado1 && resultado2;
    return (resultado);
}


pair_t pair_copy(pair_t par) {
    assert(par != NULL);
    pair_t par2 = NULL;
    par2 = calloc(1, sizeof(struct _pair_t));
    par2->indice = index_copy(par->indice);
    par2->dato = data_copy(par->dato);
    assert(par2 != NULL && pair_is_equal(par, par2));
    return (par2);
}
