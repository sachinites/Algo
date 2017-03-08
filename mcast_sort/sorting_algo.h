#ifndef __SORTING_ALGO__
#define __SORTING_ALGO__

#include "generic_sort.h"

#define INSERTION_SORT 1
#define MERGE_SORT     2


void
insertion_sort( sort_t *src,
                aux_struct_t *targ ,
                int size);


void
merge_sort( sort_t *src,
            aux_struct_t *targ ,
            int size);

#endif
