#include <stdio.h>
#include <stdlib.h>

/* simple iterative soln */
//	http://code.geeksforgeeks.org/wNJdfd

void update_soln(int A[], int size, int *ans_flips, int *curr_flips){
	int i = 0;
	static int n = 0;

	/*Is Alternate*/
	for(; i < size - 1; i++){
		if(A[i] == !A[i+1])
			continue;
		else
			return;
	}

	if(*curr_flips < *ans_flips){
		*ans_flips = *curr_flips;
		printf("possible soln no %d\n", n++);
		for(i = 0; i < size - 1; i++)
			printf("%d ", A[i]);
		printf("\n");
	}
}

void _min_flips(int A[], int lindex, int size, int *ans_flips, int *curr_flips){
	if(lindex == -1){
		update_soln(A, size, ans_flips, curr_flips);
		return;
	}

	(*curr_flips)++;
	A[lindex] = !A[lindex];
	_min_flips(A, lindex -1, size, ans_flips, curr_flips);
	(*curr_flips)--;
	A[lindex] = !A[lindex];
	_min_flips(A, lindex -1, size, ans_flips, curr_flips);
}

int min_flips(int A[], int size){
	// initialisation to max
	int ans_flips = size;
	int curr_flips = 0;
	_min_flips(A, size -1, size, &ans_flips, &curr_flips);
	return ans_flips;
}

int
main(int argc, char **argv){

	//int A[] = {1,0,0,1,0};
	int A[] = {0,0,0,1,0,1,0,1,1,1};

	//int A[] = {1,0,0,1,0,1,0,0};
	int ans = min_flips(A, sizeof(A)/sizeof(int));
	printf("Minimum flips = %d\n", ans);
	int i = 0;
	printf("Original input\n");
	for(i = 0; i < sizeof(A)/sizeof(int) - 1; i++)
		printf("%d ", A[i]);
	printf("\n");
	return 0;
}
