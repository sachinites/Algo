#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[]){
    int i = 0, j = 0, k = 0;
    j = i++ + k++;
    printf("j = %d, i = %d, k = %d\n", j,i, k);
    return 0;
}
