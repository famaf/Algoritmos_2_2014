#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "bst.h"
#include "list.h"
#include "pair.h"
#include "data.h"
#include "index.h"

int main() {
    bst_t arbol = bst_empty();

    unsigned int resultado;

    index_t palabra1 = index_from_string("18");
    index_t palabra2 = index_from_string("60");
    index_t palabra3 = index_from_string("17");
    index_t palabra4 = index_from_string("04");
    index_t palabra5 = index_from_string("02");
    index_t palabra6 = index_from_string("00");
    index_t palabra7 = index_from_string("99");


    arbol = bst_add(arbol, index_from_string("18"),
        data_from_string("dieciocho"));
    arbol = bst_add(arbol, index_from_string("10"),
        data_from_string("diez"));
    arbol = bst_add(arbol, index_from_string("50"),
        data_from_string("cincuenta"));
    arbol = bst_add(arbol, index_from_string("05"),
        data_from_string("cinco"));
    arbol = bst_add(arbol, index_from_string("15"),
        data_from_string("quince"));
    arbol = bst_add(arbol, index_from_string("20"),
        data_from_string("veinte"));
    arbol = bst_add(arbol, index_from_string("60"),
        data_from_string("sesenta"));
    arbol = bst_add(arbol, index_from_string("02"),
        data_from_string("dos"));
    arbol = bst_add(arbol, index_from_string("08"),
        data_from_string("ocho"));
    arbol = bst_add(arbol, index_from_string("17"),
        data_from_string("diecisiete"));
    arbol = bst_add(arbol, index_from_string("55"),
        data_from_string("cincuenta y cinco"));
    arbol = bst_add(arbol, index_from_string("04"),
        data_from_string("cuatro"));


    resultado = bst_index_greater_count(arbol, palabra1);

    printf("\n\nLa cantidad de nodos mayores a 18 es: %i\n", resultado);

    resultado = bst_index_greater_count(arbol, palabra2);

    printf("La cantidad de nodos mayores a 60 es: %i\n", resultado);

    resultado = bst_index_greater_count(arbol, palabra3);

    printf("La cantidad de nodos mayores a 17 es: %i\n", resultado);

    resultado = bst_index_greater_count(arbol, palabra4);

    printf("La cantidad de nodos mayores a 04 es: %i\n", resultado);

    resultado = bst_index_greater_count(arbol, palabra5);

    printf("La cantidad de nodos mayores a 02 es: %i\n", resultado);

    resultado = bst_index_greater_count(arbol, palabra6);

    printf("La cantidad de nodos mayores a 00 es: %i\n", resultado);

    resultado = bst_index_greater_count(arbol, palabra7);

    printf("La cantidad de nodos mayores a 99 es: %i\n\n", resultado);

    palabra1 = index_destroy(palabra1);
    palabra2 = index_destroy(palabra2);
    palabra3 = index_destroy(palabra3);
    palabra4 = index_destroy(palabra4);
    palabra5 = index_destroy(palabra5);
    palabra6 = index_destroy(palabra6);
    palabra7 = index_destroy(palabra7);

    arbol = bst_destroy(arbol);

    return 0;
}
