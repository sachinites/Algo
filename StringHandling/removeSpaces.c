#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void
removeendSpaces(char *str){
    int len = strlen(str), i = 0;
    for(; i < len; i++){
        if(*(str+i) == ' ')
            continue;
    }
     strtok(str+i, " ");
     printf("%s\n", str);
     return;
}
int 
main(int argc, char **argv){
    char str[256] = "   This is it  ";
    removeendSpaces(str);
    return 0;
}
