struct _person_t {
    unsigned int id;
    unsigned int age;
    float weight;
};


typedef struct _person_t person_t;


person_t person_create(unsigned int id, unsigned int age, float weight);


void print_person(person_t person);
