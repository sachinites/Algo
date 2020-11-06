#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <stdbool.h>

#define MAX_SET_SIZE	10
typedef struct set_{

	int set[MAX_SET_SIZE];
} set_t;

void
init_set(set_t *set){

	memset(set, 0, sizeof(set_t));
}

void
copy_set(set_t *dst, set_t *src){

	int i ;
	
	for(i = 0; i < MAX_SET_SIZE; i++){
		
		if(dst->set[i]) continue;
		break;
	}

	if (i == MAX_SET_SIZE) {

		assert(0);
	}

	int k = i;

	for(i = 0; i < MAX_SET_SIZE; i++){

		if(k == MAX_SET_SIZE) assert(0);

		if(src->set[i]) {
			dst->set[k] = src->set[i];
			k++;
			continue;
		}
		return;
	}
}

bool
set_is_elem_preset(set_t *set, int elem) {

	int i;

	for ( i = 0; i < MAX_SET_SIZE; i++) {

		if(set->set[i] == elem) {
			return true;
		}
	}
	return false;
}

void
add_to_set(set_t *set, int n){

	int i ;

	if(set_is_elem_preset(set, n))
		return;

	for ( i = 0; i < MAX_SET_SIZE; i++) {

		if(set->set[i]) continue;
		set->set[i] = n;
		return;
	}
	assert(0);
}

void
print_set(set_t *set){

	int i ;

	for ( i = 0; i < MAX_SET_SIZE; i++) {

		if(set->set[i]){
			printf("%d ", set->set[i]);
		}
		else break;
	}
}

void
print_array(int *arr, int arr_size){

	int i = 0;

	while(i < arr_size){
		
		printf("%d ", arr[i]);
		i++;
	}
}

bool
arry_is_elem_present(int *arr, int arr_size, int elem){

	int i ;

	for( i = 0; i < arr_size; i++) {
		
		if (arr[i] == elem)
			return true;
	}
	return false;
}


int arr[] = {3, 34, 4, 12, 5, 2};

bool
subset_sum(int *arr, int arr_size, int sum, set_t *set);


bool
subset_sum(int *arr, int arr_size, int sum, set_t *set){

	/* base condns */
	if(arr_size == 0) return false;
	if(arr_size == 1) {
		
		if(arr[0] == sum) {
			add_to_set(set, sum);
			return true;	
		}
		else return false;
	}

	if (sum == 0) {
		return true;
	}

	set_t set_inclusion;
	set_t set_exclusion;
	init_set(&set_inclusion);
	init_set(&set_exclusion);

	add_to_set(&set_inclusion, arr[arr_size-1]);

	bool res_include = subset_sum(arr, arr_size-1, 
			sum - arr[arr_size-1], &set_inclusion);

	bool res_exclude = subset_sum(arr, arr_size-1, 
			sum, &set_exclusion);

	if(res_include) {
		copy_set(set, &set_inclusion);
		return true;	
	}

	if(res_exclude) {
		copy_set(set, &set_exclusion);
		return true;
	}
	
	return false;
}

int
main(int argc, char **argv) {

	set_t set;
	init_set(&set);
	
	bool res = subset_sum(arr, (sizeof(arr)/sizeof(arr[0])), 34, &set);

	if(res) {
		print_set(&set);
		printf("\n");
	}
	else{
		printf("No Solution Found\n"); 
	}
	return 0;
}

