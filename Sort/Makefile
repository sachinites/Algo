target:exe 
CC = gcc
%.o:%.c
	${CC} -g -c -I . $<
exe:main.o sorting_algo.o generic_sort.o sort_struct.o
	${CC} -g main.o sorting_algo.o generic_sort.o sort_struct.o -o exe	
clean:
	rm *.o exe
