#include <stdlib.h>
#include "person.h"

int main(void) {
    person_t p = NULL;
    p = person_create(1, 23, 80.5);
    print_person(p);
    p = person_destroy(p);

    return(0);
}
