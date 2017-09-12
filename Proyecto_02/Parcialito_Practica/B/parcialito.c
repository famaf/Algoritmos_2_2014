#include <stdio.h>
#include <stdlib.h>
#include "pair.h"
#include "index.h"
#include "data.h"
#include "list.h"

int main() {
    list_t list = NULL;

    index_t palabra1, palabra2, palabra3, palabra4;
    unsigned int final1, final2, final3, final4;

    list =
        list_append(list, index_from_string("caza"),
                    data_from_string("Accion de cazar"));
    list =
        list_append(list, index_from_string("casa"),
                    data_from_string("Edificio para habitar"));
    list =
        list_append(list, index_from_string("cielo"),
                    data_from_string
                    ("Esfera aparente azul que rodea la Tierra"));
    list =
        list_append(list, index_from_string("caza"),
                    data_from_string("Conjunto de animales no domesticados"));
    list =
        list_append(list, index_from_string("extraordinario"),
                    data_from_string("Fuera del orden o regla natural"));

    palabra1 = index_from_string("extraordinario");
    palabra2 = index_from_string("caza");
    palabra3 = index_from_string("zaraza");
    palabra4 = index_from_string("cielo");

    final1 = list_count(list, palabra1);
    final2 = list_count(list, palabra2);
    final3 = list_count(list, palabra3);
    final4 = list_count(list, palabra4);

    printf("\nThe count for extraordinario is: %d\n\n", final1);
    printf("The count for caza is: %d\n\n", final2);
    printf("The count for zaraza is: %d\n\n", final3);
    printf("The count for cielo is: %d\n\n", final4);

    palabra1 = index_destroy(palabra1);
    palabra2 = index_destroy(palabra2);
    palabra3 = index_destroy(palabra3);
    palabra4 = index_destroy(palabra4);

    list = list_destroy(list);

    return 0;
}
