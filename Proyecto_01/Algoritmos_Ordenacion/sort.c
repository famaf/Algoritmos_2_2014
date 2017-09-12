#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "array_helpers.h"
#include "sort.h"

int cont_swaps = 0, cont_comparaciones = 0;

#ifndef NDEBUG

static bool is_valid_position(unsigned int length, unsigned int i) {
    return (i < length);
}

#endif

unsigned long int get_comp_counter(void) {
    /* Needs implementation */

    return (cont_comparaciones);
}

unsigned long int get_swap_counter(void) {
    /* Needs implementation */
    return (cont_swaps);
}

void reset_counters(void) {
    /* Needs implementation */

    cont_comparaciones = 0, cont_swaps = 0;

}

void swap(int *a, unsigned int i, unsigned int j) {
/*
    Swap the value at position 'i' with the value at position 'j' in the
    array 'a'. The values 'i' and 'j' must be valid positions in the array.

*/
#ifndef NDEBUG
    /* Store the original values so later the assert can be made */
    int original_i = a[i], original_j = a[j];
#endif

    /* Needs implementation -- do not use original_i and original_j */

    int tmp;

    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
    cont_swaps++;

#ifndef NDEBUG
    /* Check postconditions */
    assert(original_i == a[j]);
    assert(original_j == a[i]);
#endif
    /* and the rest of the elements have not changed */
}

unsigned int min_pos_from(int *a, unsigned int length, unsigned int i) {
/*
    Return the position of the minimum value in the array 'a' starting
    at position 'i'. The array 'a' must have exactly 'length' elements,
    and 'i' must be a valid position in the array.

*/
    /* Check preconditions */
    assert(array_is_valid(a, length));
    assert(is_valid_position(length, i));

    unsigned int min = 0;

    /* Needs implementation */

    unsigned int minp, j;
    minp = i;

    for (j = i + 1; j < length; j++) {
        if (a[j] < a[minp]) {
            minp = j;
        }
        cont_comparaciones++;
    }

    min = minp;

    /* Check postconditions */
    assert(is_valid_position(length, min));
    return (min);
}

void insert(int *a, unsigned int i) {
    unsigned int j;
    j = i;

    while (j > 0 && a[j] < a[j - 1]) {
        cont_comparaciones++;
        swap(a, j - 1, j);
        j = j - 1;
    }
    if (j > 0) {
        cont_comparaciones++;
    }
}


unsigned int pivot(int *a, bool opcion, int izq, int der) {
    unsigned int i, j, piv, rd;

    if (opcion) {

        srand(time(NULL));

        rd = rand() % (der - izq + 1) + izq;
        swap(a, (int)rd, izq);

    }

    piv = izq;
    i = izq + 1;
    j = der;

    while (i <= j) {
        if (a[i] <= a[piv]) {
            i++;
            cont_comparaciones++;
        } else if (a[j] > a[piv]) {
            j--;
            cont_comparaciones += 2;
        } else {
            cont_comparaciones += 2;
            swap(a, i, j);
            i++;
            j--;
        }
    }

    swap(a, piv, j);
    piv = j;

    return (piv);

}

void quick_sort_rec(int *a, bool opcion, int izq, int der) {
    unsigned int piv;

    if (der > izq) {
        piv = pivot(a, opcion, izq, der);

        quick_sort_rec(a, opcion, izq, piv - 1);
        quick_sort_rec(a, opcion, piv + 1, der);
    }
}

void selection_sort(int *a, unsigned int length) {
    assert(array_is_valid(a, length));

    /* Needs implementation */

    unsigned int minp, i;

    for (i = 0; i + 1 < length; i++) {
        minp = min_pos_from(a, length, i);
        swap(a, i, minp);
    }

    /* Check postconditions */
    assert(array_is_sorted(a, length));
}

void insertion_sort(int *a, unsigned int length) {
    assert(array_is_valid(a, length));

    /* Needs implementation */

    unsigned int i;

    for (i = 1; i < length; i++) {
        insert(a, i);
    }

    /* Check postconditions */
    assert(array_is_sorted(a, length));
}

void quick_sort(int *a, unsigned int length) {
    assert(array_is_valid(a, length));

    /* Needs implementation */
    quick_sort_rec(a, false, 0, length - 1);

    /* Check postconditions */
    assert(array_is_sorted(a, length));
}

void rand_quick_sort(int *a, unsigned int length) {
    assert(array_is_valid(a, length));

    /* Needs implementation */
    quick_sort_rec(a, true, 0, length - 1);

    /* Check postconditions */
    assert(array_is_sorted(a, length));
}

void bubble_sort(int *a, unsigned int length) {
    unsigned int i, j;
    bool swapped;

    swapped = true;
    i = 0;

    while (swapped && i + 1 < length) {
        swapped = false;

        for (j = length - 1; j > 0; j--) {

            if (a[j] < a[j - 1]) {
                swap(a, j, j - 1);
                swapped = true;
            }
            cont_comparaciones++;
        }
        i++;
    }
    assert(array_is_sorted(a, length));
}
