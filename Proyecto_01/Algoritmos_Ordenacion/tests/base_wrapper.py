import ctypes

import helpers


# ctypes wrapper
sort_lib = helpers.get_lib('sort.so')


# void selection_sort(int *a, unsigned int length);
selection_sort = helpers.maybe_implemented(
    sort_lib, 'selection_sort', None, [helpers.int_ptr, ctypes.c_uint])

# void insertion_sort(int *a, unsigned int length);
insertion_sort = helpers.maybe_implemented(
    sort_lib, 'insertion_sort', None, [helpers.int_ptr, ctypes.c_uint])

# void quick_sort(int *a, unsigned int length);
quick_sort = helpers.maybe_implemented(
    sort_lib, 'quick_sort', None, [helpers.int_ptr, ctypes.c_uint])

# void rand_quick_sort(int *a, unsigned int length);
rand_quick_sort = helpers.maybe_implemented(
    sort_lib, 'rand_quick_sort', None, [helpers.int_ptr, ctypes.c_uint])

# void bubble_sort(int *a, unsigned int length);
bubble_sort = helpers.maybe_implemented(
    sort_lib, 'bubble_sort', None, [helpers.int_ptr, ctypes.c_uint])

# unsigned long int get_comp_counter(void);
get_comp_counter = helpers.maybe_implemented(
    sort_lib, 'get_comp_counter', ctypes.c_ulong, [])

# unsigned long int get_swap_counter(void);
get_swap_counter = helpers.maybe_implemented(
    sort_lib, 'get_swap_counter', ctypes.c_ulong, [])

# void reset_counters(void);
reset_counters = helpers.maybe_implemented(
    sort_lib, 'reset_counters', None, [])
