/* 
 * link : https://www.geeksforgeeks.org/maximum-subsequence-sum-such-that-no-three-are-consecutive/
 * */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <assert.h>

#define max(a,b) (a > b ? a : b)

int
max_sum(int p[], int arr_size, bool included){

/* Boundry conditions 
 */
	
	assert(arr_size >= 0);

	if(arr_size == 0)
		return 0;

	if(arr_size == 1) {
		return p[0];
	}

	if(arr_size == 2) {
		/* consider both include and exclude case, it all
 		 * boils down to returning the max of the two */
		return max(p[0], p[1]);
	}

	int incl_sum = included ? max_sum(p, arr_size -2, false) : 
							  max_sum(p, arr_size -1, true);

	int excl_sum = max_sum(p, arr_size -1, false);

	return max(incl_sum + p[arr_size-1], excl_sum);	
}

int
main(int argc, char **argv){

	int p[] = {2, 6, 9, 8, 5, 7};
	int rc = max_sum(p, sizeof(p)/sizeof(p[0]), false);
	printf("Ans = %d\n", rc);
	return 0;
}
