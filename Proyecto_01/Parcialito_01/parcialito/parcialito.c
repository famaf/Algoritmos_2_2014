#include <stdlib.h>
#include <stdio.h>
#include "sort.h"
#include "array_helpers.h"


char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        printf("Please enter a filename pointing to an array file.\n");
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

int main(int argc, char *argv[]) {
    unsigned int length = 0;
    int *array = NULL;
    char *filename = parse_filepath(argc, argv);

    /* Needs implementation */

    int limite = 0;
    int scanf_result = 0;
    int suma_parcial = 0;
    int i;
    printf("\nIngrese un numero NO negativo: ");
    scanf_result = scanf("%d", &limite);

    if (scanf_result != 1) {
        printf("Error, usted no ingreso un numero\n\n");
        return 1;
    }

    if (limite < 0) {
        printf("You should enter a non-negative number.\n\n");
        return 1;
    }



    /* 1. Read a single integer from stdin, if negative show an error and exit
       with failure. If zero or positive, store it in a 'limit' variable. */

    /* Create an array from file */
    array = array_from_file(filename, &length);

    if (length == 0) {
        printf("0\n\n"); //Parte A (parcialito)
        printf("%d\n\n", suma_parcial - limite); //Parte B (parcialito)
        return 0;
    }

    /* 2. Sort the 'array' re-using a sorting algorithm of your choice. */

    selection_sort(array, length);

    if (limite == 0) {
        printf("%d\n", array[length - 1]);
    }

    i = length - 1;

    while (suma_parcial < limite && i >= 0) {
        printf("%d ", array[i]);
        suma_parcial = suma_parcial + array[i];
        i--;
    }

    if (limite > suma_parcial) {
        printf("%d\n", suma_parcial); //Parte A (parcialito)
        printf ("%d\n", suma_parcial - limite); //Parte B (parcialito)
    }
    printf("\n");

    /* 3. Iterate over 'array', starting from the last position and going
       towards the first position, and print on stdout as many values as
       possible to sum up to 'limit'. */

    array_destroy(array);
    return (0);
}
