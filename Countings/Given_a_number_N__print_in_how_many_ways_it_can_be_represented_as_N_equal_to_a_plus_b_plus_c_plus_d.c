#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int N = 100;
    int count = 0, a,b,c,d, No_Comparison = 0;
    for(a = 1 ; a <= N/4; a++)
    {
        for(b = a; b <= ((N-a)/3)+1; b++)
        {
            for(c = b; c <= ((N-b)/2)+1; c++)
            {
                for(d = c; d <= ((N-c))+1; d++)
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
