#include "person.h"

int main(void) {
    person_t p;
    p = person_create(1, 23, 80.5);
    print_person(p);

    return(0);
}
