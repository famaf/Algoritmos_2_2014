#ifndef _SORT_H
#define _SORT_H


void selection_sort(int *a, unsigned int length);
/*
    Sort the array 'a' using the Selection sort algorithm. The resulting sort
    will be ascending.

    The array 'a' must have exactly 'length' elements.

*/

void insertion_sort(int *a, unsigned int length);
/*
    Sort the array 'a' using the Insertion sort algorithm. The resulting sort
    will be ascending.

    The array 'a' must have exactly 'length' elements.

*/

void quick_sort(int *a, unsigned int length);
/*
    Sort the array 'a' using the Quick sort algorithm. The resulting sort
    will be ascending.

    The array 'a' must have exactly 'length' elements.

*/

void rand_quick_sort(int *a, unsigned int length);
/*
    Sort the array 'a' using the Quick sort algorithm
    and by choosing the pivot randomly.

    The array 'a' must have exactly 'length' elements.
*/

void bubble_sort(int *a, unsigned int length);
/*
    Sort the array 'a' using the Bubble sort algorithm.

    The array 'a' must have exactly 'length' elements.
*/

unsigned long int get_comp_counter(void);
/*
    Return the value of the swap counter.
*/

unsigned long int get_swap_counter(void);
/*
    Return the value of the comparison counter.
*/

void reset_counters(void);
/*
    Reset all the counters to be zero.
*/


#endif
