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
    bst_t arbol;
    arbol = bst_empty();

    unsigned int resultado;

    resultado = bst_leaf_count(arbol);
    printf("\nLa cantidad de hojas es: %i\n", resultado);

    arbol =
        bst_add(arbol, index_from_string("18"), data_from_string("dieciocho"));

    resultado = bst_leaf_count(arbol);
    printf("La cantidad de hojas es: %i\n", resultado);

    arbol = bst_add(arbol, index_from_string("10"), data_from_string("diez"));

    resultado = bst_leaf_count(arbol);
    printf("La cantidad de hojas es: %i\n", resultado);

    arbol =
        bst_add(arbol, index_from_string("50"), data_from_string("cincuenta"));

    resultado = bst_leaf_count(arbol);
    printf("La cantidad de hojas es: %i\n", resultado);

    arbol = bst_add(arbol, index_from_string("05"), data_from_string("cinco"));

    resultado = bst_leaf_count(arbol);
    printf("La cantidad de hojas es: %i\n", resultado);

    arbol =
        bst_add(arbol, index_from_string("15"), data_from_string("quince"));

    resultado = bst_leaf_count(arbol);
    printf("La cantidad de hojas es: %i\n", resultado);

    arbol =
        bst_add(arbol, index_from_string("20"), data_from_string("veinte"));

    resultado = bst_leaf_count(arbol);
    printf("La cantidad de hojas es: %i\n", resultado);

    arbol =
        bst_add(arbol, index_from_string("60"), data_from_string("sesenta"));

    resultado = bst_leaf_count(arbol);
    printf("La cantidad de hojas es: %i\n", resultado);

    arbol = bst_add(arbol, index_from_string("02"), data_from_string("dos"));

    resultado = bst_leaf_count(arbol);
    printf("La cantidad de hojas es: %i\n", resultado);

    arbol = bst_add(arbol, index_from_string("08"), data_from_string("ocho"));

    resultado = bst_leaf_count(arbol);
    printf("La cantidad de hojas es: %i\n", resultado);

    arbol =
        bst_add(arbol, index_from_string("17"),
                data_from_string("diecisiete"));

    resultado = bst_leaf_count(arbol);
    printf("La cantidad de hojas es: %i\n", resultado);

    arbol =
        bst_add(arbol, index_from_string("55"),
                data_from_string("cincuenta y cinco"));

    resultado = bst_leaf_count(arbol);
    printf("La cantidad de hojas es: %i\n\n", resultado);

    arbol = bst_destroy(arbol);

    return 0;
}
