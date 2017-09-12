#ifndef _UNION_FIND_H
#define _UNION_FIND_H


typedef int union_find_elem_t;

typedef int union_find_class_t;

typedef struct _union_find_t *union_find_t;


union_find_t union_find_create(unsigned int max_size);
/*
* Return a new disjoint set. It can hold up to max_size initial classes.
*
* The resources allocated for the set returned from this call must be freed
* by calling 'union_find_destroy' once the result is no longer needed.
*
* POST: the result is not NULL.
*/


union_find_t union_find_destroy(union_find_t uf);
/*
* Free all the resources used by 'uf'.
*
* PRE: 'uf' must be not NULL.
*/


union_find_t union_find_push(union_find_t uf, union_find_elem_t elem);
/*
* Update the set 'uf' by enabling the initial class for 'elem'.
*
* Is worth noting that this method has to be idempotent, in the sense that
* if is called more than one time with an element already in it, nothing
* should happen (ie, the count of classes should not change).
*
* PRE: 'uf' must be not NULL, and 'elem' must be a well-defined union find
* element.
*
* POST: the result is not NULL, and is equal to 'uf' except that is updated
* to hold a new initial class for 'elem'.
*/


union_find_t union_find_union(union_find_t uf, union_find_class_t class1,
                              union_find_class_t class2);
/*
* Update the set 'uf' by merging tha classes 'class1' with 'class2'.
*
* PRE: 'uf' must be not NULL, and 'class1' and 'class2' should be
* valid (existing) classes for 'uf'.
*
* POST: the result is not NULL, and is equal to 'uf' except that the given
* classes were merged into one (thus the count of classes of the result is
* the same as the one from 'uf' minus one).
*/


union_find_class_t union_find_find(union_find_t uf, union_find_elem_t elem);
/*
* Return the class for the given element 'elem' in the set 'uf'.
*
* PRE: 'uf' must not be NULL, and 'elem' must be a valid set element that has
* been previously pushed to 'uf'.
*/


unsigned int union_find_class_count(union_find_t uf);
/*
* Return the amount of classes that the given set 'uf' has.
*
* PRE: 'uf' must not be NULL.
*/


#endif
