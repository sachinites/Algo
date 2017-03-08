#include <stdio.h>
#include <stdlib.h>
#define NAME_SIZE 30
#include <string.h>

int main(){
    char name[NAME_SIZE];
    char *addr = NULL;
    char name2 [] = "abhi";
    char name3[] = {'a', 'b', 'h', 'i'};
    printf("Enter name: ");
    if(fgets(name, NAME_SIZE, stdin) == NULL){
            printf("error occurred\n");
            return 0;
        } 
     printf("size of Name = %d\n", strlen(name));
     
      addr = "ok\0";
      printf("size of addr = %d\n", strlen(addr));
      printf("size of name2 = %d\n", strlen(name2));
      printf("size of name3 = %d\n", strlen(name3));
    return 0;
}
