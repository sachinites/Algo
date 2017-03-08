#include "stdio.h"
#include "stdlib.h"
#include "sort_struct.h"
#include "sorting_algo.h"
#include "memory.h"

#define DS_SIZE	10

int
main(int argc, char **argv){
	int i = 0;
	igmp_snooping_vlan_t src[DS_SIZE] = {
					{22, NULL},
					{10, NULL},
					{40, NULL},
					{30, NULL},
					{50, NULL},
					{22, NULL},
					{13, NULL},
					{42, NULL},
					{36, NULL},
					{54, NULL}};



	aux_struct_t dst[DS_SIZE];
	memset(dst, 0 , DS_SIZE*sizeof(aux_struct_t));
	
	sort_t sort_src;
	IGMP_SNOOPING_VLAN_INIT_SORT(sort_src, src);
	set_sorting_algo(&sort_src, INSERTION_SORT);
	execute_sort(&sort_src, dst, DS_SIZE);

	for(i = 0; i < DS_SIZE; i++){
		printf("dst[%d] = %d\n", i, (int)dst[i].key);
	}

	return 0;
}
