#include "stdio.h"
#include "stdlib.h"
#include "sort_struct.h"
#include "sorting_algo.h"
#include "memory.h"

#define DS_SIZE	5

int
main(int argc, char **argv){
	int i = 0;
	igmp_snooping_vlan_t src[DS_SIZE] = {
					{21, NULL},
#if 1
					{10, NULL},
					{40, NULL},
					{25, NULL},
					{50, NULL}};
#endif

	aux_struct_t dst[DS_SIZE];
	memset(dst, 0 , DS_SIZE*sizeof(aux_struct_t));
	
	sort_t sort_src;
	IGMP_SNOOPING_VLAN_INIT_SORT(sort_src, src);
	set_sorting_algo(&sort_src, INSERTION_SORT);
	execute_sort(&sort_src, dst, DS_SIZE);
	if(isSorted(&sort_src, DS_SIZE))
		printf("Array is already sorted\n");
	else
		printf("Array is not Sorted\n");
	
	for(i = 0; i < DS_SIZE; i++){
		printf("dst[%d] = %d, src[%d] = %d, %p\n", i, (int)dst[i].key, i, src[i].vlan_id, src[i].data_ptr);
	}

	return 0;
}
