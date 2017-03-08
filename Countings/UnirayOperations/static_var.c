#include <stdlib.h>
#include <stdio.h>

void fun(){
    static int  i = 0;
    i++;
    printf("%s(): i = %d , Addr = 0x%x\n", __FUNCTION__, i, &i);
    return;
}

void fun2(){
    static int  i = 0;
    i++;
    printf("%s(): i = %d, Addr = 0x%x\n", __FUNCTION__, i, &i);
    return;
}
int
main(int argc, char *argv[]){
    fun();    
    fun();    
    fun();    
    fun();    
    fun();    
    fun2();    
    fun2();    
    fun2();    
    fun2();    
    fun2();    
    return 0;
}
