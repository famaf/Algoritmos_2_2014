#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdbool.h>
#include "data.h"
#include "index.h"
#include "bst.h"
#include "list.h"
#include "pair.h"


typedef struct _node_t *stack_t;

stack_t vacia(void);
/* Devuelve una pila vacia */


stack_t apilar(stack_t pila, bst_t arbol);
/*Aloja el nuevo elemento en la pila*/


bst_t primero(stack_t pila);
/*Muestra el primer elemento de la pila*/


stack_t desapilar(stack_t pila);
/*Desapila el primer elemento de la pila
* POST: ¬ (es_vacia(pila))
*/


bool es_vacia(stack_t pila);
/*Retorna True si la pila se encuentra vacia,
* caso contrario devuelve False
*/


stack_t destruir_pila(stack_t pila);
/*Destruye la pila
* POST: es_vacia(pila) == True
*/ 



#endif
