#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_SIZE 30

int main(int argc, char **argv){
    char name1[NAME_SIZE] = "Abhishek";
    char name2[NAME_SIZE] = {'A', 'b', 'h', '\0', 's', 'h', 'e', 'k'};
    char name2_2[NAME_SIZE] = {'A', 'b', 'h', 'i', 's', 'h', 'e', 'k'};
    char name3[2*NAME_SIZE];
    char *name4 = NULL;
    char dest[NAME_SIZE];

    if((fgets(name3, NAME_SIZE, stdin) == NULL)){
        printf("error in reading from stdin\n");
        return 0;
    }

#if 0 // segmentation fault
    strcpy(name4, name1); 
    printf("name4 = %s\n", name4);
 #endif

    strcpy(dest, name3); 
    printf("dest = %s\n", dest);

    return 0;
}
