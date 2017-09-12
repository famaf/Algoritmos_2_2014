#ifndef _STACK_H
#define _STACK_H


#include <stdbool.h>
#include "graph.h"

/* Stack element abstract data type */

typedef edge_t stack_elem_t;

#define stack_elem_copy edge_copy
#define stack_elem_destroy edge_destroy

/* Stack abstract data type */

typedef struct _node_t *stack_t;


stack_t stack_empty(void);
/*
* Return an empty, newly created stack.
*
* The resources allocated for the stack returned from this call must be freed
* by calling 'stack_destroy' once the result is no longer needed.
*
* POST: the result is a well-defined stack and stack_is_empty(result) holds.
*
*/


stack_t stack_destroy(stack_t stack);
/*
* Free all the resources used by 'stack'.
*
* PRE: the given 'stack' must be a well-defined stack.
*/


stack_t stack_push(stack_t stack, stack_elem_t elem);
/*
* Push 'elem' to the top of the given 'stack'.
* The stack owns 'elem' after this, consider passing a copy if you
* plan to use 'elem' somewhere else.
*
* PRE: 'elem' must be a well-defined stack element.
*
* POST: the resulting stack will have the same elements as 'stack' plus 'elem'
* in the top of the stack.
*/


stack_t stack_pop(stack_t stack);
/*
* Pop and destroy the element at the top of the given 'stack'.
*
* PRE: 'stack' must not be empty.
*
* POST: the resulting stack will have the same elements as 'stack' minus the
* element in the top of the stack.
*/


stack_elem_t stack_top(stack_t stack);
/*
* Return a copy of the element at the top of the given 'stack'.
*
* PRE: 'stack' must not be empty.
*
* POST: the given 'stack' does not change, and the resulting element is a
* valid stack element and is the one at the top of the stack.
*/


bool stack_is_empty(stack_t stack);
/*
* Return whether the given 'stack' is empty or not.
*/


#endif
