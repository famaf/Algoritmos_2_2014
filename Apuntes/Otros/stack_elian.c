#include <stdlib.h>
#include "bst.h"
#include "stack.h"


struct _stack_t {
    bst_t elem;
    struct _stack_t *next;
};


stack_t stack_empty(void) {
    stack_t nuevo = NULL;
    return (nuevo);
}

stack_t push(stack_t stack, bst_t elem) {
    stack_t nuevo = NULL;
    nuevo = calloc(1, sizeof(struct _stack_t));
    nuevo->elem = elem;
    nuevo->next = stack;
    return (nuevo);
}

stack_t pop(stack_t stack) {
    stack_t aux = stack->next;
    free(stack);
    return (aux);
}

bool is_empty(stack_t stack) {
    bool b = (stack == NULL);
    return (b);
}

bst_t stack_first(stack_t stack) {
    bst_t bst = stack->elem;
    return (bst);
}

stack_t stack_destroy(stack_t stack) {
    while (!is_empty(stack)) {
        stack = pop(stack);
    }
    return (stack);
}
