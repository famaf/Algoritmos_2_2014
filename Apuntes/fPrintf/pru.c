#include <stdio.h>

int main() {
    FILE *fd;
    char *palabra = "-coco gay-";
    unsigned int contador = 0;

    fd = fopen ("coco.txt", "w");
    while (contador < 10) {
        fprintf(fd, "%s", palabra);
        contador ++;
    }

    return 0;
}
