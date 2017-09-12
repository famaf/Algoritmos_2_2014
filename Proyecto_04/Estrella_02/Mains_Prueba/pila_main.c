#include <stdio.h>
#include <assert.h>
#include "stack.h"
#include "graph.h"

int main() {
    stack_t pila = stack_empty();
    
    stack_elem_t elemento = NULL;
    
    vertex_t v1 = vertex_create(1);
    vertex_t v2 = vertex_create(2);
    
    vertex_t v3 = vertex_create(3);
    vertex_t v4 = vertex_create(3);
    
    edge_t edge = edge_create(v1, v2, 10);
    
    edge_t edge2 = edge_create(v3, v4, 15);
    
    pila = stack_push(pila, edge);
    
    pila = stack_push(pila, edge2);

    assert(!stack_is_empty(pila));
    
    elemento = stack_top(pila);
    
    assert(elemento!=NULL);
    
    edge_destroy(elemento);
    
    pila = stack_pop(pila);
    pila = stack_pop(pila);
    
    assert(stack_is_empty(pila));

    pila = stack_destroy(pila);
    
    return(0);        
}
