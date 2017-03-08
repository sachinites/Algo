#include <memory.h>
#include "sorting_algo.h"

void
merge_sort( sort_t *src,
            aux_struct_t *targ ,
            int size){
}

/* Generic insertion sort algorithm */
void
insertion_sort( sort_t *src,
                aux_struct_t *targ ,
                int size){

        const aux_struct_t *init_addr = targ;
        targ->key = src->get_key(src->ds);
        targ->data_ptr = src->ds;
        increment_ptr(src->ds, src->get_struct_size());
        targ++;
        int i = 0;
        aux_struct_t *temp = NULL;
        for(i = 1; i < size; i++){
                if(src->compare(src->get_key(src->ds), (targ-1)->key, src->get_key_size()) >= 0){
                        targ->key = src->get_key(src->ds);
                        targ->data_ptr = src->ds;
                        increment_ptr(src->ds, src->get_struct_size());
                        targ++;
                        continue;
                }

                temp = targ;
                copy_forward:
                        memcpy(temp, temp -1 , sizeof(aux_struct_t));
                        temp--;
                        if(temp == init_addr){
                                temp->key = src->get_key(src->ds);
                                temp->data_ptr = src->ds;
                                increment_ptr(src->ds, src->get_struct_size());
                                targ++;
                                continue;
                        }
                        if(src->compare(src->get_key(src->ds), (temp-1)->key, src->get_key_size()) >= 0){
                                temp->key = src->get_key(src->ds);
                                temp->data_ptr = src->ds;
                                increment_ptr(src->ds, src->get_struct_size());
                                targ++;
                                continue;
                        }
                        if(temp!=init_addr)
                                goto copy_forward;
        }
}
