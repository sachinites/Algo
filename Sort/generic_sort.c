#include "generic_sort.h"
#include "sorting_algo.h"

sort_t
init_sort(void *ds,
          _get_key get_key,
          _compare compare,
          _get_struct_size get_struct_size,
	  _sort_algo sort_algo,
	  _get_key_size get_key_size){
	
	sort_t sort;
	sort.ds 		= ds;
	sort.get_key    	= get_key;
	sort.compare 		= compare;
	sort.get_struct_size 	= get_struct_size;
	sort.sort_algo 		= sort_algo;
	sort.get_key_size 	= get_key_size;
	return sort;
}

void
set_sorting_algo(sort_t *sort_src, int algo_id){
	switch(algo_id){
		case INSERTION_SORT:
			sort_src->sort_algo =  insertion_sort;
			break;
		case MERGE_SORT:
			sort_src->sort_algo =  merge_sort;
			break;
	}
}

void
execute_sort(sort_t *sort, aux_struct_t *targ, int size){
	sort->sort_algo(sort, targ, size);
}

int
isSorted(sort_t *src, int size){
        if(!src || !src->ds) return 1;
        int i = 0;
        void *next_elem = 0, *curr_ptr = src->ds;
        for(i = 0; i < size -1; i++){
                next_elem = (char *)curr_ptr + src->get_struct_size();
                if(src->compare(src->get_key(src->ds), src->get_key(next_elem), src->get_key_size()) <= 0){
                        increment_ptr(curr_ptr, src->get_struct_size());
                        continue;
                }
        	return 0;
        }
        return 1;
}
