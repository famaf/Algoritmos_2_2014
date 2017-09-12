#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "index.h"
#include "pair.h"
#include "list.h"

void print(list_t list) {
    list_dump(list, stdout);
    printf("\n============\n");
}

int main() {
    list_t lista;
    lista = list_empty();

    lista =
        list_append(lista, index_from_string("perro"),
                    data_from_string("guau"));
    lista =
        list_append(lista, index_from_string("gato"),
                    data_from_string("miau"));
    lista =
        list_append(lista, index_from_string("loro"),
                    data_from_string("prrrr"));
    lista =
        list_append(lista, index_from_string("perro"),
                    data_from_string("super guau"));

    printf("\n");

    print(lista);

    lista = list_remove_first(lista);

    print(lista);

    lista = list_remove_first(lista);

    print(lista);

    lista = list_remove_first(lista);

    print(lista);

    lista = list_remove_first(lista);

    print(lista);

    lista = list_remove_first(lista);

    print(lista);

    printf("\n");

    return 0;
}
