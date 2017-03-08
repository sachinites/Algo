#ifndef _GENERIC_SORT_
#define _GENERIC_SORT_


typedef void* (*_get_key)(void *);
typedef int (*_compare)(void *key1, void *key2, int key_size);
typedef int (*_get_struct_size)(void);
typedef int (*_get_key_size)(void);

typedef struct _aux_struct{
        void *key;
        void *data_ptr;
}aux_struct_t;

typedef struct _sort_t sort_t;

typedef void (*_sort_algo)( sort_t *src, aux_struct_t *targ , int size);

struct _sort_t{
	void *ds;
	_get_key get_key;
	_compare compare;
        _get_struct_size get_struct_size;
	_sort_algo sort_algo;	
	_get_key_size get_key_size;
};




sort_t
init_sort(void *ds, 
	  _get_key get_key, 
	  _compare compare, 
	  _get_struct_size get_struct_size,
	  _sort_algo sort_algo,
	  _get_key_size get_key_size);

void
set_sorting_algo(sort_t *sort_src, int algo_id);

void
execute_sort(sort_t *sort, aux_struct_t *targ, int size);

#define increment_ptr(ptr, size)	(ptr = (char *)ptr + size)

#endif
