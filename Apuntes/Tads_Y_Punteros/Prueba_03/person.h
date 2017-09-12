typedef struct _person_t *person_t;


person_t person_create(unsigned int id, unsigned int age, float weight);


person_t person_destroy(person_t person);


void print_person(person_t person);
