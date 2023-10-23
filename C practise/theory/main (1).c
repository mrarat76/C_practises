/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

int main()
{
   int numbers[]={1, 3, 3};
   int *p=numbers;
   
   printf("%d %d %d\n", *p, *(p+1),*(p+2));
   int*pArray[]={numbers, numbers+1,numbers+2};
    printf("%d %d %d", *pArray[0], *(pArray[1]),*(pArray[2]));
    return 0;
}
