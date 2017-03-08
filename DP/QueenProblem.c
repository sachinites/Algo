/* Copyright by Moritz Lenz (C) 2006. */
/* You may use this file under the terms of the MIT license */
#include <stdio.h>
#include <stdlib.h>

typedef signed short int field_type;

int N = 8;
unsigned long int Count = 0;

int collision(field_type *field, field_type row){
	field_type i = 0;
	field_type tmp = 0;
	for(i = 0; i < row; i++){
		tmp = field[i] - field[row];
		if (tmp == 0 || tmp == i - row || tmp == row - i){
			return 1;
		}
	}
	return 0;
}

void search(field_type *field, field_type row){
	field_type i = 0;
	if (row == N){
		Count++;
		return;
	}

	for (i = 0; i < N; i++){
		field[row] = i;
		if (! collision(field, row)){
			search(field, row + 1);
		}
	}
}


int main(int argc, char** argv){
	if (argc == 2) {
		/* Die Groesse des Feldes wurde auf der Kommandozeile */
		/* angegeben */
		N = atoi(argv[1]);
		if (N < 4 || N % 2 == 1){
			printf("%s: Warning: Ignoring count '%d' since it " 
					"must be an event integer > 3", 
					argv[0], N);
			N = 8;
		}
	}

	field_type field[N];
	field_type i = 0;
	for (i = 0; i < N ; i++){
		field[0] = i;
		search(field, 1);
	}
	printf("Number of solutions: %ld (with %d queens)\n",  Count, N);
	return 0;
}
