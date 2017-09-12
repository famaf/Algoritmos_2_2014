#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "person.h"

struct _person_t {
    unsigned int id;
    unsigned int age;
    float weight;
};


person_t person_create(unsigned int id, unsigned int age, float weight) {
    person_t person = NULL;
    person = calloc(1, sizeof(struct _person_t));

    assert(person != NULL);
    person->id = id;
    person->age = age;
    person->weight = weight;

    return(person);
}


person_t person_destroy(person_t person) {
    free(person);
    person = NULL;

    return(person);
}


void print_person(person_t person) {
    printf("Person %d\n", person->id);
    printf("\tage: %d, weight: %f\n", person->age, person->weight);
}
