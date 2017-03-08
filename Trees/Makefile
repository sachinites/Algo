exe:./../Stack/stack.o ./../Queue/Queue.o tree.o
	gcc -g ./../Stack/stack.o ./../Queue/Queue.o tree.o -o exe
stack.o:./../Stack/stack.c
	gcc -g -c ./../Stack/stack.c -o ./../Stack/stack.o
Queue.o:./../Queue/Queue.c
	gcc -g -c ./../Queue/Queue.c -o ./../Queue/Queue.o
tree.o:tree.c
	gcc -g -c tree.c -o tree.o
clean:
	rm ./../Stack/stack.o
	rm ./../Queue/Queue.o
	rm tree.o
	rm exe

