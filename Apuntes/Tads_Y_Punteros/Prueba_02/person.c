#include <stdio.h>
#include "person.h"

person_t person_create(unsigned int id, unsigned int age, float weight) {
    person_t person;
    person.id = id;
    person.age = age;
    person.weight = weight;

    return(person);
}


void print_person(person_t person) {
    printf("Person %d\n", person.id);
    printf("\tage: %d, weight: %f\n", person.age, person.weight);
}
