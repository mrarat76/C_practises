/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>



int squareFunction(int a){
    return a*a;
    
}


int doubleFunction(int a){
    return 2*a;
}



int main()
{
    int(*functionPointerArray[])(int a)={squareFunction, doubleFunction};
    
    for (size_t i =0; i<2; i++){
        printf("%dth elemnt\n", functionPointerArray[i](5));
    }
    
    
    printf("Hello World");

    return 0;
}
