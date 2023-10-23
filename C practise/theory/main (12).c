/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

int callbackImp1(){
    printf("callbackImp1 worked\n");
}


void writesomething(void (*callback)()){
    
    callback();
    
    printf("callbackImp2 worked\n");
    
}




int main()
{
    
    
    writesomething(callbackImp1);
    printf("Hello World");

    return 0;
}
