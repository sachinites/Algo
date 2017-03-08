#include <stdio.h>
#include <stdlib.h>
int main(){
    char name[30];
    printf("Enter name: ");
    if(fgets(name, 30, stdin) == NULL){
            printf("error occurred\n");
            return 0;
        } 
    puts(name);    //Function to display string.
    return 0;
}
