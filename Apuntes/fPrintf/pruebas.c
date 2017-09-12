#include <stdio.h>

int main(void) {
    FILE *archivo = NULL;

    archivo = fopen("prueba.txt", "w");
    fprintf(archivo, "Hola mundo\n");
    fclose(archivo);

    return 0;
}
