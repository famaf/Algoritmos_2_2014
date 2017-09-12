
/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "dict.h"
#include "dict_helpers.h"
#include "helpers.h"

#define TAMANO 'z'
#define BUSCAR 's'
#define AGREGAR 'a'
#define BORRAR 'd'
#define VACIAR 'e'
#define MOSTRAR 'h'
#define DUPLICAR 'c'
#define CARGAR 'l'
#define GUARDAR 'u'
#define FINALIZAR 'q'


char print_menu(void) {
    char result = '\0', discard = '\0';
    int scanf_result = 0;

    printf("\nElija lo que quiera hacer. Las opciones son:\n\n"
           "*****************************************************************\n"
           "*\tz: Mostrar el tamaño del diccionario en uso.    \t*\n"
           "*\ts: Buscar una definicion para una palabra dada. \t*\n"
           "*\ta: Agregar una palabra con su definicion.       \t*\n"
           "*\td: Borrar una palabra.                          \t*\n"
           "*\te: Vaciar el diccionario.                       \t*\n"
           "*\th: Mostrar el diccionario actual.               \t*\n"
           "*\tc: Duplicar el diccionario actual.              \t*\n"
           "*\tl: Cargar un nuevo diccionario desde un archivo.\t*\n"
           "*\tu: Guardar el diccionario actual en un archivo. \t*\n"
           "*\tq: Finalizar                                    \t*\n"
           "*****************************************************************\n\n"
           "Introduzca su elección: ");

    scanf_result = scanf("%c", &result);
    if (scanf_result != 1) {
        result = '\0';
    }

    /* Consume everything left in the stdin buffer */
    while (discard != '\n') {
        scanf_result = scanf("%c", &discard);
    }

    return (result);
}


int main(void) {
    char option = '\0';
    char *filename = NULL;
    unsigned int length = 0;
    dict_t dict = dict_empty();
    dict_t dict2 = NULL;
    word_t word;
    def_t def;

    do {
        option = print_menu();
        switch (option) {
            case TAMANO:
                length = dict_length(dict);
                printf("\t-> El tamaño es: %o.\n\n", length);
                break;

            case BUSCAR:
                printf
                    ("\tPor favor, ingrese la palabra a buscar en el diccionario: ");
                word = readline_from_stdin();
                if (dict_exists(dict, word)) {
                    def_t definicion = dict_search(dict, word);
                    printf("\t-> La definicion de '%s' es: '%s'\n\n", word,
                           definicion);
                    free(definicion);
                    definicion = NULL;
                } else {
                    printf
                        ("\t->La palabra '%s' no existe en el diccionario\n\n",
                         word);
                }
                free(word);
                word = NULL;
                break;

            case AGREGAR:
                printf
                    ("\tPor favor, ingrese la palabra a añadir al diccionario: ");
                word = readline_from_stdin();
                if (dict_exists(dict, word)) {
                    printf("\t-> La palabra '%s' ya existe.\n\n", word);
                } else {
                    printf("\t-> Por favor, ingrese la definicion: ");
                    def = readline_from_stdin();
                    dict_add(dict, word, def);
                    printf
                        ("\t-> La palabra y su definición fueron agregadas\n\n");
                    free(def);
                    def = NULL;
                }
                free(word);
                word = NULL;
                break;

            case BORRAR:
                printf
                    ("\tPor favor, ingrese la palabra que desea eliminar del diccionario: ");
                word = readline_from_stdin();
                if (dict_exists(dict, word)) {
                    dict_remove(dict, word);
                    printf("\t-> La palabra fue eliminada exitosamente.\n\n");
                    free(def);
                    def = NULL;
                } else {
                    printf("\t-> la palabra '%s' no existe.\n\n", word);
                }
                free(word);
                word = NULL;
                break;

            case VACIAR:
                dict = dict_destroy(dict);
                dict = dict_empty();
                printf("\t-> El diccionario fue vaciado.\n\n");
                break;

            case MOSTRAR:
                printf("{\n");
                if (dict != NULL) {
                    dict_dump(dict, stdout);
                } else {
                    dict = dict_empty();
                }
                printf("}\n");
                break;

            case DUPLICAR:
                printf
                    ("\tEl diccionario fue duplicado. Mostrando el diccionario duplicado:\n\n");
                dict2 = dict_copy(dict);
                printf("{\n");
                dict_dump(dict2, stdout);
                printf("}\n");
                dict2 = dict_destroy(dict2);
                break;

            case CARGAR:
                printf
                    ("\tPor favor, ingrese el nombre del diccionario a cargar: ");
                filename = readline(stdin);
                dict_destroy(dict);
                dict = dict_from_file(filename);
                if (dict != NULL) {
                    printf("\tEl diccionario fue cargado exitosamente.\n\n");
                } else {
                    printf
                        ("\tNo puede cargar el diccionario del archivo '%s'\n\n",
                         filename);
                }
                free(filename);
                filename = NULL;
                break;

            case GUARDAR:
                printf("\t\n¿Como quiere llamar el archivo a guardar?: ");
                filename = readline_from_stdin();
                dict_to_file(dict, filename);
                printf("\t-> El diccionario fue guardado exitosamente.\n\n");
                free(filename);
                filename = NULL;
                break;

            case FINALIZAR:
                printf("\tFinalizando...\n\n");
                dict_destroy(dict);
                return (EXIT_SUCCESS);
            default:
                printf
                    ("\n\"%c\" no es valido. Por Favor, ingrese una opcion valida.\n\n",
                     option);
        }
    } while (option != FINALIZAR);



    return (EXIT_SUCCESS);
}
