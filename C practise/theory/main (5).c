/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
int f1(){
    printf("f1 called\n");
}

int f2(){
    printf("f2 called\n");
    
}



int main(void)
{
    
    int(*pFunc)();
    pFunc= f1;
    pFunc();
    pFunc=&f2;
    pFunc();
    return 0;
}
