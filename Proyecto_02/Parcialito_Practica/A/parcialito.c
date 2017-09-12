#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "data.h"
#include "index.h"
#include "pair.h"
#include "list.h"

/*struct _node_t {
    pair_t elem;
    list_t next;
};*/

int main() {
    list_t lista = NULL;

    int final1, final2, final3, final4;

    lista =
        list_append(lista, index_from_string("caza"),
                    data_from_string("Accion de cazar"));
    lista =
        list_append(lista, index_from_string("casa"),
                    data_from_string("Edificio para habitar"));
    lista =
        list_append(lista, index_from_string("cielo"),
                    data_from_string
                    ("Esfera aparente azul que rodea la tierra"));
    lista =
        list_append(lista, index_from_string("caza"),
                    data_from_string("Conjunto de animales no domesticados"));
    lista =
        list_append(lista, index_from_string("extraordinario"),
                    data_from_string("Fuera del orden o regla natural"));

    index_t palabra1 = index_from_string("extraordinario");
    index_t palabra2 = index_from_string("caza");
    index_t palabra3 = index_from_string("zaraza");
    index_t palabra4 = index_from_string("cielo");

    final1 = list_position(lista, palabra1);
    final2 = list_position(lista, palabra2);
    final3 = list_position(lista, palabra3);
    final4 = list_position(lista, palabra4);

    printf("\nThe position for extraordinario is: %d\n\n", final1);
    printf("\nThe position for caza is: %d\n\n", final2);
    printf("\nThe position for zaraza is: %d\n\n", final3);
    printf("\nThe position for cielo is: %d\n\n", final4);

    palabra1 = index_destroy(palabra1);
    palabra2 = index_destroy(palabra2);
    palabra3 = index_destroy(palabra3);
    palabra4 = index_destroy(palabra4);

    lista = list_destroy(lista);

    return 0;
}
