#include <stdio.h>
#include <stdlib.h>

double pow(double x, double y){
    double res = 1.0, i =0.0;
    for(; i < y ; i++){
        res *=  x;
    }
    return res;
}

unsigned int
get_digit_count(unsigned int n){
    unsigned int count = 0;
    while(n){
        n = n /10;
        count++;
    }
    return count;
}

unsigned char
get_first_digit(unsigned int N, unsigned int d){
    double exp = pow(10.0, (double)d-1);
    return (unsigned char)(N/exp);
}

unsigned char
get_last_digit(unsigned int N){
    return N - ((N/10)*10);
}

void
strip(int *N, int *d){
    *N = *N/10;
    unsigned int temp1 = ((unsigned int)(*N/pow(10.0, (double)(*d -2))));
    double temp2 = pow(10.0, (double)(*d-2));
    double M = temp1 * temp2;
    *N = *N - (unsigned int )M;
    *d -= 2;
}

unsigned char
isPalindrome(unsigned int N){
    unsigned int d = get_digit_count(N),
                 i = 0;
    if(d == 1 || d == 0)
        return 1;
    if(d == 2){
        if(get_first_digit(N, d) == get_last_digit(N)) 
            return 1;
         else
            return 0;
    }
    COMPARE:

        if(get_first_digit(N, d) !=
                    get_last_digit(N))
            return 0;
         strip(&N,&d);
         if(d >= 2) goto COMPARE;
         return 1;
}

int
main(int argc, char **argv){
    unsigned int N = 0, d = 0, i =0, M = 0;
    printf("Enter Number = ");
    scanf("%d", &N);
    isPalindrome(N) ? printf("Palindrome\n") : printf("Not Palindrome\n");
    return 0;
}
