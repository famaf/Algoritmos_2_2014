#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "stack.h"
#include "graph.h"


struct _node_t {
    stack_elem_t edge;
    stack_t next;
};



stack_t stack_empty(void) {
    stack_t stack = NULL;
    assert(stack_is_empty(stack));
    return (stack);
}


stack_t stack_destroy(stack_t stack) {
    while (!stack_is_empty(stack)) {
        stack = stack_pop(stack);
    }
    assert(stack_is_empty(stack));

    return (stack);
}


stack_t stack_push(stack_t stack, stack_elem_t elem) {
    stack_t nuevo = NULL;
    nuevo = calloc(1, sizeof(struct _node_t));
    nuevo->edge = elem;
    nuevo->next = stack;
    stack = nuevo;

    return (stack);
}


stack_t stack_pop(stack_t stack) {
    assert(!stack_is_empty(stack));

    stack_t tmp = stack;
    stack = stack->next;
    tmp->edge = edge_destroy(tmp->edge);
    free(tmp);
    tmp = NULL;

    return (stack);
}


stack_elem_t stack_top(stack_t stack) {
    assert(!stack_is_empty(stack));

    stack_elem_t elemento = NULL;
    elemento = edge_copy(stack->edge);

    return (elemento);
}


bool stack_is_empty(stack_t stack) {
    bool result;

    result = (stack == NULL);

    return (result);
}
