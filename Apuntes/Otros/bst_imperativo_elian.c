#include <stdlib.h>
#include "pair.h"
#include "bst.h"
#include "data.h"
#include "index.h"
#include "stack.h"


struct _tree_node_t {
    struct _tree_node_t *izq;
    pair_t par;
    struct _tree_node_t *der;
};

bst_t bst_empty(void) {
    bst_t nuevo = NULL;
    return (nuevo);
}

bst_t bst_destroy(bst_t bst) {
    stack_t stack = stack_empty();
    bst_t aux = NULL, aux1 = NULL, aux2 = NULL;
    if (bst != NULL) {
        push(stack, bst);
        while (!is_empty(stack)) {
            aux = first(stack);
            aux1 = first(stack)->der;
            aux2 = first(stack)->izq;
            pop(stack);

            pair_destroy(aux->par);
            free(aux);

            if (aux1 != NULL) {
                push(stack, bst->der);
            }
            if (aux2 != NULL) {
                push(stack, bst->izq);
            }
        }
    }

    return(bst);
}

unsigned int bst_length(bst_t bst) {
    unsigned int a = 0;
    stack_t stack = stack_empty();
    if (bst != NULL) {
        push(stack, bst);
        while (!is_empty(stack)) {
            pop(stack);
            a++;
            if (aux->der != NULL) {
                push(stack, bst->der);
            }
            if (aux->izq != NULL) {
                push(stack, bst->izq);
            }
        }
    }

    return (a);
}


list_t bst_to_list(bst_t bst, list_t list) {
    stack_t stack = stack_empty();
    bst_t aux = NULL;
    if (bst != NULL) {
        push(stack, bst);
        while (!is_empty(stack)) {
            aux = first(stack);
            pop(stack);
            if (aux->der != NULL) {
                push(stack, bst->der);
            }
            list_append(list, pair_fst(aux->par), pair_snd(aux->par));
            if (aux->izq != NULL) {
                push(stack, bst->izq);
            }
        }
    }

    return (list);
}
