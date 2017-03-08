#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int N = 100;
    int count = 0, a,b,c,d, No_Comparison = 0;
    for(a = 1 ; a <= N; a++)
    {
        for(b = a; b <= N; b++)
        {
            for(c = b; c <= N; c++)
            {
                for(d = c; d <= N; d++)
                {
                    No_Comparison++;
                    if(a+b+c+d == N){
                        printf("a = %d, b = %d, c = %d, d = %d, sum = %d\n", a,b,c,d,a+b+c+d);
                        count++;
                    }
                    }
                }
            }
        }
        printf("Total No of solutions = %d, Total No of Comparisons made = %d\n", count, No_Comparison);
    return 0;
}
