#ifndef _BST_H
#define _BST_H

#include <stdio.h>
#include <stdbool.h>
#include "data.h"
#include "index.h"
#include "list.h"
//#include "stack.h"


typedef struct _tree_node_t *bst_t;


bst_t bst_empty(void);
/*
* Return a newly created, empty binary search tree (BST).
*
* The caller must call bst_destroy when done using the resulting BST,
* so the resources allocated by this BST constructor are freed.
*
* POST: the result is a valid BST pointer, and bst_length(result) is 0.
*/


bst_t bst_destroy(bst_t bst);
/*
* Free the resources allocated for the given ’bst’, and set it to NULL.
*/


unsigned int bst_length(bst_t bst);
/*
* Return the amount of elements in the given ’bst’.
* This method has a linear order complexity. For reference, see:
* http://en.wikipedia.org/wiki/Linear_time#Linear_time
*
* PRE: ’bst’ is a valid BST pointer.
*/


bool bst_is_equal(bst_t bst, bst_t other);
/*
* Return whether the given ’bst’ is equal to ’other’.
*
* Equality is defined by comparing both BSTs, node by node, and ensuring that
* each node is equal as a whole (ie, that both pairs are equal).
*
* PRE: ’bst’ and ’other’ are valid BST pointers.
*/


data_t bst_search(bst_t bst, index_t index);
/*
* Return the data associated to the given ’index’ in the given ’bst’,
* or NULL if the ’index’ is not in ’bst’.
*
* The caller must NOT free the resources allocated for the result when done
* using it.
*
* PRE: ’bst’ and ’index’ are valid pointers.
*/


bst_t bst_add(bst_t bst, index_t index, data_t data);
/*
* Return the given ’bst’ with the pair (’index’, ’data’) added to it.
*
* The given ’index’ and ’data’ are inserted in the BST,
* so they can not be destroyed by the caller (they will be destroyed when
* bst_destroy is called).
*
* PRE: all ’bst’, ’index’ and ’data’ are valid pointers.
* Also, there is no pair in the given BST such as its index is equal to
* ’index’ (this means, bst_search for ’index’ must be NULL).
*
* POST: the length of the result is the same as the length of ’bst’
* plus one. The elements of the result are the same as the one in ’bst’
* with the new pair (’index’, ’data’) added accordingly (see:
* http://en.wikipedia.org/wiki/Binary_search_tree
* for specifications about behavior).
*/


bst_t bst_remove(bst_t bst, index_t index);
/*
* Return the given ’bst’ with the pair which index is equal to ’index’
* removed.
*
* Please note that ’index’ may not be in the BST (thus an unchanged
* BST is returned).
*
* PRE: both ’bst’ and ’index’ are valid pointers.
*
* POST: the length of the result is the same as the length of ’bst’
* minus one if ’index’ existed in ’bst’. The elements of the result are
* the same as the ones in ’bst’ with the entry for ’index’ removed.
*/


bst_t bst_copy(bst_t bst);
/*
* Return a newly created copy of the given ’bst’.
*
* The caller must call bst_destroy when done using the resulting BST,
* so the resources allocated by this BST contructor are freed.
*
* POST: the result is a valid BST pointer and it is an exact copy of ’bst’.
* In particular, bst_is_equal(result, bst) holds.
*/


list_t bst_to_list(bst_t bst, list_t list);
/*
* Return a sequence that is a flatten representation of ’bst’.
*
* PRE: ’bst’ is a valid BST pointer, ’list’ is a valid list pointer
*
* POST: the result is a valid list, and the result’s length is the same
* as the given BST’s length. Every pair in the BST exists in the returned
* list, and the BST ordering is preserved.
*
* In other words, the resulting list has to be in ascending ordered, not
* because a sorting algorithm was applied to the list, but because it was
* built in a way that elements are ordered.
*
*/


#endif
