#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    char str[] = "abhishek";
    char str1[20] = "abhishek";
    char str2[]= {'a', 'b', 'h', 'i', 's', 'h', 'e', 'k'};
    char *inputstr1 = NULL;
    char inputstr2[100] ;
    //gets(inputstr1);
    //puts(inputstr1);
    gets(inputstr2);
    printf("%s\n", inputstr2);
    return 0;
}
